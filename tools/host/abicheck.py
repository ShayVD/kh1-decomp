#!/usr/bin/env python3
"""Find declarations whose argument types only work on the EE (phase 5,
docs/vita-port-plan.md section 5.1c, portability.md rule 11).

The EE passes the first eight integer arguments in a0-a7 and the float ones in
$f12-$f19, each in its own sequence, and a 64-bit value in one register. So a
caller's prototype or cast that orders the float and integer parameters
differently from the definition (`f(s32, f32, s32)` for `f(s32, s32, f32)`),
or passes an s32 where the definition takes a u64, still works there. On x86
and ARM every argument has its place in one sequence (or on the stack), and a
64-bit argument takes two: the callee reads the wrong values. A float return
declared as an integer return (or the other way) works on the EE when the
caller drops the value, but on x86 it leaves the x87 stack unbalanced.

    python3 -I tools/host/abicheck.py [--tsv out/host/abicheck.tsv]

compares every prototype (`T f(...);`) and m2c cast (`#define f ((T (*)(...)) f)`)
of a func_ name in src/ with the definition, parameter by parameter, by class:
32-bit integer or pointer, 64-bit integer, f32, f64, 128-bit. Unknown typedefs
(structs passed by value, or typedefs this does not resolve) are skipped, as
are unprototyped `()` declarations (argcheck.py covers those).
Declarations in an `#ifdef KH1_PS2` branch are the EE's own and are skipped:
when reordering a call changes the PS2 code, the file keeps the EE's order
there and gives the host the definition's order and a macro that reorders the
calls (`#define f(a1, a2, a3) (f)(a1, a3, a2)`, rule 11).
A heuristic over the text: check each hit by hand.
"""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import argcheck  # noqa: E402

ROOT = argcheck.ROOT
PROTO_RX = re.compile(r"^[ \t]*(?:extern\s+)?([A-Za-z_][\w \t\*]*?)\b(func_[0-9a-f]{8}|[A-Za-z_]\w*)\s*\(([^;{()]*)\)\s*;", re.M)
CAST_RX = re.compile(r"^#define\s+(func_[0-9a-f]{8}|[A-Za-z_]\w*)\s+\(\(\s*([\w \t\*]+?)\s*\(\s*\*\s*\)\s*\(([^()]*)\)\s*\)\s*\1\s*\)", re.M)
INT32 = re.compile(r"(unsigned |signed )?(int|char|short|long|short int|long int)|[su](8|16|32)|M2C_UNK(8|16|32)?|size_t|unsigned|signed|BOOL|bool|vs32|vu32")


def cls(t):
    """The ABI class of a parameter or return type: i32, i64, f32, f64, q128, void, or None (unknown)."""
    t = re.sub(r"\b(const|volatile|register|struct|union|enum|extern|static|inline|__inline__|CONTEXT_ONLY)\b", " ", t)
    if "*" in t or "[" in t:
        return "i32"
    w = t.split()
    if not w:
        return None
    # drop a parameter name: the last word, unless the type is all keywords
    if len(w) > 1 and w[-1] not in ("int", "char", "short", "long", "double", "float", "unsigned", "signed"):
        w = w[:-1]
    s = " ".join(w)
    if s in ("u64", "s64", "long long", "unsigned long long", "long long int", "long long unsigned int"):
        return "i64"
    if s in ("f64", "double"):
        return "f64"
    if s in ("f32", "float"):
        return "f32"
    if s in ("u128", "s128", "kh1_u128", "kh1_s128"):
        return "q128"
    if s == "void":
        return "void"
    if INT32.fullmatch(s):
        return "i32"
    return None


def params(p):
    p = p.strip()
    if p in ("", "void"):
        return None if p == "" else []
    return [x for x in p.split(",")]


def compare(dret, dps, ret, ps):
    out = []
    a, b = cls(ret), cls(dret)
    # an integer return the caller drops or reads the low half of is the same on both
    if a and b and a != b and {a, b} - {"i32", "void"} and not (a in ("i32", "void") and b == "i64"):
        out.append("return %s, defined %s" % (a, b))
    if ps is None or dps is None:
        return out
    for k in range(min(len(ps), len(dps))):
        if ps[k].strip() == "..." or dps[k].strip() == "...":
            break
        a, b = cls(ps[k]), cls(dps[k])
        if a and b and a != b:
            out.append("arg %d %s, defined %s" % (k + 1, a, b))
    return out


def ps2_only(s):
    """The spans of `#ifdef KH1_PS2` branches (to their #else or #endif): the EE's own
    declarations, which the host's branch replaces."""
    out = []
    for m in re.finditer(r"^#\s*ifdef\s+KH1_PS2\b", s, re.M):
        e = re.compile(r"^#\s*(else|endif)\b", re.M).search(s, m.end())
        out.append((m.start(), e.start() if e else len(s)))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tsv")
    a = ap.parse_args()
    srcs = {f: argcheck.strip_comments(open(os.path.join(ROOT, f), errors="replace").read())
            for f in argcheck.files()}
    defs = {}  # name -> (ret, params, file); a name defined twice (file-local copies) is skipped
    twice = set()
    for f, s in srcs.items():
        for m in argcheck.DEF_RX.finditer(s):
            ret, name, p = m.group(1).strip(), m.group(2), m.group(3)
            if ret in ("return", "else", "if", "while", "for", "switch") or "define" in ret or ret.startswith("static"):
                continue
            if "CONTEXT_ONLY" in s[max(0, m.start() - 40):m.start() + len(ret)]:
                continue
            ret = re.sub(r"KH1_V0\((\w+)\)", r"\1", ret)
            if name in defs and defs[name][2] != f:
                twice.add(name)
            defs[name] = (ret, params(p), f)
    rows = []
    for f, s in sorted(srcs.items()):
        decls = [(m.start(), m.group(1), m.group(2), m.group(3)) for m in PROTO_RX.finditer(s)]
        decls += [(m.start(), m.group(2), m.group(1), m.group(3)) for m in CAST_RX.finditer(s)]
        skip = ps2_only(s)
        for pos, ret, name, p in decls:
            if any(a <= pos < b for a, b in skip):
                continue
            if name not in defs or name in twice or defs[name][2] == f or ret.strip() in ("return", "else"):
                continue
            dret, dps, df = defs[name]
            for d in compare(dret, dps, ret, params(p)):
                rows.append((f, s.count("\n", 0, pos) + 1, name, d, df))
    for r in rows:
        print("\t".join(str(x) for x in r))
    print("%d declarations whose argument or return classes differ from the definition" % len(rows), file=sys.stderr)
    if a.tsv:
        os.makedirs(os.path.dirname(a.tsv), exist_ok=True)
        with open(a.tsv, "w") as fh:
            fh.write("file\tline\tcallee\tdifference\tdefined in\n")
            for r in rows:
                fh.write("\t".join(str(x) for x in r) + "\n")


if __name__ == "__main__":
    main()
