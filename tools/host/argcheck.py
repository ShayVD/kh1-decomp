#!/usr/bin/env python3
"""Find the calls that work on the EE only because of its registers (phase 5,
docs/vita-port-plan.md section 5.1b "Register passthrough").

m2c and the matching drafts sometimes leave a call with fewer arguments than
the callee takes, through an unprototyped declaration (`T f();`) or cast
(`#define f ((T (*)()) f)`): on the EE the caller's own a0-a3 are still in the
registers, so the callee reads the right values; on x86 or ARM it reads
garbage. The same for a function defined `void` whose callers use its value
(v0 still holds the last call's result on the EE). Both are wrong C that the
PS2 build cannot see, so this reads the source:

    python3 -I tools/host/argcheck.py [--tsv out/host/argcheck.tsv]

lists (file, line, callee, args passed, params defined) for calls with fewer
arguments than the definition in src/ (or a draft of shift/drafts.tsv), and the
calls of void-defined functions whose value is used (assigned, returned,
compared, passed on).
Variadic definitions and `(void)` are understood; K&R definitions count their
identifier list. A heuristic over the text: check each hit by hand.
"""
import argparse
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

DEF_RX = re.compile(r"^(?!\s)(?:static\s+)?(?:const\s+)?(KH1_V0\(\w+\)\s*|[A-Za-z_][\w \t\*]*?)\b(func_[0-9a-f]{8}|[A-Za-z_]\w*)\s*\(([^;{)]*)\)\s*(?:\{|$)", re.M)
CALL_RX = re.compile(r"\b(func_[0-9a-f]{8})\s*\(")

# Hits read by hand and left as they are (file, callee): the reason.
BENIGN = {
    ("src/game/dkmovie.c", "func_0024b138"):
        "func_00111238 names the disc / IPU calls and is never called (no jal, j or pointer to it)",
    # Value uses whose value nobody reads (session 63): the caller returns it, and
    # every caller of that caller drops it.
    ("src/menu/loadmenu.c", "func_00207bb0"):
        "a window callback returns it, and src/text/textwin.c calls window callbacks as void",
    ("src/menu/party.c", "func_00207bb0"):
        "a window callback returns it, and src/text/textwin.c calls window callbacks as void",
    ("src/menu/savemenu.c", "func_00207bb0"):
        "a window callback returns it, and src/text/textwin.c calls window callbacks as void",
    ("src/menu/choice.c", "func_00205938"):
        "a window callback returns it, and src/text/textwin.c calls window callbacks as void",
    ("src/menu/choice2.c", "func_00205938"):
        "a window callback returns it, and src/text/textwin.c calls window callbacks as void",
    ("src/menu/journal_s0.c", "func_0010edb0"):
        "a window callback returns it, and src/text/textwin.c calls window callbacks as void",
    ("src/menu/journal_s1.c", "func_0010edb0"):
        "a window callback returns it, and src/text/textwin.c calls window callbacks as void",
    ("src/game/trinity.nostrict.c", "func_00158af0"):
        "returned by func_00158b88 (plctl.nostrict.c), whose callers call it as a statement",
    ("src/obj/areabox.c", "func_00142058"):
        "returned by func_0014f1b8 (roomobj.c), whose callers call it as a statement",
    ("src/obj/roomobj.nostrict.c", "func_0013b9c8"):
        "returned by func_001323a0 (actor.nostrict.c), whose callers call it as a statement",
    ("src/obj/class1b.nostrict.c", "func_001337e0"):
        "returned by func_001519c0 (plctl.nostrict.c), whose callers call it as a statement",
}


def files():
    out = []
    for d, _, fs in os.walk(os.path.join(ROOT, "src")):
        rel = os.path.relpath(d, ROOT)
        if rel == "src/sdk" or rel.startswith("src/sdk/"):
            continue
        out += [os.path.join(rel, f) for f in fs if f.endswith(".c")]
    for l in open(os.path.join(ROOT, "shift", "drafts.tsv")):
        f = l.rstrip("\n").split("\t")
        if len(f) >= 2 and f[0].startswith("func_"):
            out.append(f[1])
    return sorted(out)


def strip_comments(s):
    s = re.sub(r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), s, flags=re.S)
    return re.sub(r"//[^\n]*", "", s)


def nparams(p):
    p = p.strip()
    if p in ("", "void"):
        return 0, False
    parts = [x for x in p.split(",") if x.strip()]
    var = parts[-1].strip() == "..."
    return len(parts) - (1 if var else 0), var


def call_args(s, i):
    """Count the arguments of the call whose '(' is at s[i]; None if unbalanced."""
    depth, n, empty = 0, 0, True
    j = i
    while j < len(s):
        c = s[j]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return 0 if empty else n + 1
        elif c == "," and depth == 1:
            n += 1
        elif depth >= 1 and not c.isspace():
            empty = False
        j += 1
    return None


def enclosing_ret(s, pos):
    """The return type of the function definition that contains pos (None if not found)."""
    last = None
    for m in DEF_RX.finditer(s, 0, pos):
        last = m
    return last.group(1).strip() if last else None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tsv")
    a = ap.parse_args()
    alias = {}
    for l in open(os.path.join(ROOT, "functions.tsv")):
        f = l.split("\t")
        if len(f) >= 2 and not l.startswith("#") and f[1].split():
            alias[f[0]] = "func_" + f[1].split()[0].lower()[-8:]
    srcs = {f: strip_comments(open(os.path.join(ROOT, f), errors="replace").read()) for f in files()}
    defs = {}  # func_ name -> (params, variadic, rettype, file)
    for f, s in srcs.items():
        for m in DEF_RX.finditer(s):
            ret, name, p = m.group(1).strip(), m.group(2), m.group(3)
            if ret in ("return", "else", "if", "while", "for", "switch") or "define" in ret:
                continue
            if name in alias:
                name = alias[name]
            if not name.startswith("func_"):
                continue
            # a definition: '{' follows (on this line or the next non-blank one)
            rest = s[m.end() - 1:m.end() + 200]
            if not (rest.startswith("{") or re.match(r"\s*(\w[^;{]*;\s*)*\{", s[m.end():m.end() + 400])):
                continue
            n, var = nparams(p)
            defs.setdefault(name, (n, var, ret, f))
    rows = []
    for f, s in sorted(srcs.items()):
        for m in CALL_RX.finditer(s):
            name = m.group(1)
            if name not in defs:
                continue
            line_start = s.rfind("\n", 0, m.start()) + 1
            line = s[line_start:s.find("\n", m.start())]
            if re.match(r"\s*(#define|extern\b|[A-Za-z_][\w \t\*]*\b" + name + r"\s*\(\s*\)\s*;)", line):
                continue
            # a prototype at file level (`void f(void);`, `void f(), g();`): only the calls matter
            if re.match(r"[A-Za-z_][^=]*;\s*$", line) and not re.match(r"(return|else|do)\b", line):
                continue
            if (f, name) in BENIGN:
                continue
            n = call_args(s, m.end() - 1)
            pn, var, ret, df = defs[name]
            if n is not None and n < pn:
                rows.append(("args", f, s.count("\n", 0, m.start()) + 1, name, n, pn, df))
    voids = {n for n, d in defs.items() if d[2] == "void"}
    for f, s in sorted(srcs.items()):
        for m in CALL_RX.finditer(s):
            name = m.group(1)
            if name not in voids or defs[name][3] == f:
                continue
            before = s[:m.start()].rstrip()
            # a value use: assigned, returned, compared, negated or passed on
            if re.search(r"(=|\breturn|[(,!<>+\-*/&|?:])$", before) and not re.search(r"\(\s*\*\s*\)\s*\(\s*\)\s*\)$|\)\s*\($", before):
                # `if (f(...))` and `g(f(...))` are uses; `((f(...)` is most likely a cast's
                if re.search(r"\(\s*\($", before):
                    continue
                # a statement after `case X:`, `default:` or a label is not a use
                seg = before[max(before.rfind(";"), before.rfind("{"), before.rfind("}")) + 1:].strip()
                if re.match(r"(case\b[^?]*|default|[A-Za-z_]\w*)\s*:$", seg):
                    continue
                line_start = s.rfind("\n", 0, m.start()) + 1
                line = s[line_start:s.find("\n", m.start())]
                if re.match(r"[A-Za-z_][^=]*;\s*$", line) and not re.match(r"(return|else|do)\b", line):
                    continue  # a prototype
                if before.endswith("return") and enclosing_ret(s, m.start()) == "void":
                    continue  # `return f();` in a void function passes nothing on
                if (f, name) in BENIGN:
                    continue
                rows.append(("ret", f, s.count("\n", 0, m.start()) + 1, name, "value used", "void", defs[name][3]))
    for r in rows:
        print("\t".join(str(x) for x in r))
    print("%d calls with too few arguments, %d value uses of a void function"
          % (sum(1 for r in rows if r[0] == "args"), sum(1 for r in rows if r[0] == "ret")), file=sys.stderr)
    if a.tsv:
        os.makedirs(os.path.dirname(a.tsv), exist_ok=True)
        with open(a.tsv, "w") as fh:
            fh.write("kind\tfile\tline\tcallee\tpassed\tdefined\tdefinition\n")
            for r in rows:
                fh.write("\t".join(str(x) for x in r) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
