#!/usr/bin/env python3
"""Checks of the game's C that need its syntax tree (phase 5, docs/vita-port-plan.md
5.1e; portability.md rules 10 and 11). Asks clang for the tree of every game file
(and every draft of shift/drafts.tsv) with the host census's flags.

Calls through pointers (rule 10). argcheck.py reads direct calls in the text; a
call through a pointer (a table, a struct field, a local loaded from either) has
no name to look up, and on the EE `fn()` still hands the target the caller's
a0-a3 (func_0013e558's class handler call, session 64). For each call whose
callee is not a function name after casts this lists the arguments it passes
and what its callee expression reads, and finds the targets in:

- data tables: the `.word` entries of src/data/*.s pieces, C initializers, and
  for `.incbin` pieces the user's ELF (an indexed array: its words from the
  start while they are functions or 0);
- functions assigned to data or to a struct field (`Record.field`), and
  functions passed as arguments, followed through setters and parameters to a
  fixpoint (`@func#i` is function func's parameter i);
- a local, through what the same function assigns to it.

Verdicts: SHORT (a known target takes more than the call passes), SHORT? (the
same, found only through a struct field), OK, ?def (targets known, none defined
in C), ? (none found), and READ / OVERLAY from the table below (read by hand).

Argument classes (rule 11): every declaration a file sees (headers, struct
typedefs, `()` declarations, block-scope externs) and every m2c cast at a call,
against the definition (ABI rows), and every f32 an unprototyped call promotes
to double where the definition takes f32 (PROMO rows). CLANG rows are clang's
errors: a builtin called with fewer arguments than it takes, or a file clang
cannot parse (gcc nested functions), whose calls are not listed.

    python3 -I tools/host/indcheck.py [--all] [--tsv out/host/indcheck.tsv]

prints the rows to act on (SHORT, SHORT?, ABI, PROMO, CLANG), with --all every
row. A heuristic: a call through a table can reach any entry (the index is not
read); check each hit by hand. Needs clang (the census builds with gcc; the
syntax is the same).
"""
import argparse
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import argcheck  # noqa: E402

ROOT = argcheck.ROOT
CFLAGS = ["-m32", "-malign-double", "-std=gnu89", "-w", "-fno-strict-aliasing", "-DKH1_HOST",
          "-Iinclude", "-Isrc", "-Wno-error=implicit-function-declaration", "-Wno-error=int-conversion",
          "-Wno-error=incompatible-pointer-types", "-Wno-error=implicit-int", "-Wno-return-type", "-fsyntax-only",
          "-Xclang", "-ast-dump=json"]

# Indirect calls read by hand (file, caller): what they reach. READ means the targets
# take no more than the call passes (or the call was fixed); OVERLAY means only an
# overlay can set the pointer (no writer, or a setter with no caller, in the main ELF):
# check it against the overlay inventories (docs/vita-port-plan.md 5.2).
READ = {
    ("src/gfx/objwin.c", "func_0010ba98"):
        "READ: Win.cb at the close (state 5) passed nothing and a0 = a1 = the window on the EE; the "
        "close callbacks (func_0010bd90's, msgwin.c's func_001cae20(id, win)) read the window: the "
        "host passes (w, w) (session 65); the open call passes Fade's (cnt, arg)",
    ("src/game/summon.nostrict.c", "func_0013be00"):
        "READ: the steps come from D_00304B48 (func_0013bde8 copies it): func_0013b050, func_0013b3d0, "
        "func_0013b740, func_0013b8f0, all (void)",
    ("src/game/memberfile.c", "func_001330e8"):
        "READ: W32Chan.x18 is func_001331d8's cb (func_001d75a0, void)",
    ("src/game/objreq.nostrict.c", "func_00146998"):
        "READ: LdTask.cb / arg are func_00146a68's cb / arg; its cb targets take one argument",
    ("src/text/fldtext.c", "func_0010e430"):
        "READ: Fade.cb is func_0010ef70's third argument: msgwin.c's (id, win) callbacks and void ones",
    ("src/util/task.c", "func_001bffa0"):
        "OVERLAY: the task's fn is set only by func_001c06c0, which nothing in the main ELF calls",
    ("src/game/objreq.c", "func_001468b0"):
        "OVERLAY: x38 is set only by func_001468f8, which nothing in the main ELF calls",
    ("src/game/cmdmenu.nostrict.c", "func_0012d930"):
        "OVERLAY: D_00524F74 is set only by func_0012cab8, which nothing in the main ELF calls",
    ("src/game/summon.c", "func_0013ab08"):
        "OVERLAY: D_00304B6C is 0 in the ELF and src/ only clears it",
    ("src/gummi/gumisave.c", "func_001b9c10"):
        "OVERLAY: the gummi overlay's entry, called with nothing: on the EE a0 is still FlushCache's 2 "
        "(if the kernel keeps it) and a1 what func_001207f8 left; check what the entry reads",
    ("src/gummi/gumisave.c", "func_001b9c60"):
        "OVERLAY: the gummi overlay's entry, called with nothing: on the EE a0 is still FlushCache's 2 "
        "(if the kernel keeps it) and a1 = D_00F20000 (s0); check what the entry reads",
    ("src/sound/objse.c", "func_001570d0"):
        "READ (session 64): the +0x10 callback gets whatever func_001ecfd8 left in a0; no handler can rely on it",
}
VM_HOOKS = "OVERLAY: src/vm/vm_lib.c's hooks D_0037733C ... D_003773E8 are 0 in the ELF and nothing in src/ sets them"


def strip(n):
    """Skip casts and parentheses around an expression node."""
    while n.get("kind") in ("ImplicitCastExpr", "CStyleCastExpr", "ParenExpr") and n.get("inner"):
        n = n["inner"][0]
    return n


def dname(name):
    """D_00525368_001330e8 (a file's own extern of D_00525368) -> D_00525368."""
    m = re.match(r"(D_[0-9A-Fa-f]{8})_\w+$", name)
    return m.group(1) if m else name


def member(n):
    """A MemberExpr as RecordType.field (the type its base points at), so that two
    structs' fields of one name stay apart."""
    t = ""
    if n.get("inner"):
        t = n["inner"][0].get("type", {}).get("qualType", "")
    t = re.sub(r"\b(struct|union|const|volatile)\b|\*|\[.*?\]", " ", t).split()
    return "%s.%s" % (t[0] if t else "?", n.get("name", "?"))


def tclass(t):
    """The argument class of a clang type node: i32, i64, f32, f64, q128, rec, void."""
    q = t.get("qualType", "")
    d = t.get("desugaredQualType", q)
    if "*" in d or "[" in d or "(" in d or "*" in q:
        return "i32"
    if "128" in q or "128" in d:
        return "q128"
    d = re.sub(r"\b(const|volatile|signed|unsigned)\b", " ", d).split()
    d = " ".join(d)
    d = {"f32": "float", "f64": "double", "s64": "long long", "u64": "long long"}.get(d, d)
    if d == "float":
        return "f32"
    if d in ("double", "long double"):
        return "f64"
    if d in ("long long", "long long int"):
        return "i64"
    if d.startswith(("struct ", "union ")):
        return "rec"
    if d == "void":
        return "void"
    return "i32"


def fsig(fd):
    """(return class, [parameter classes] or None when unprototyped, variadic) of a FunctionDecl."""
    t = fd.get("type", {})
    q = t.get("desugaredQualType", t.get("qualType", ""))
    m = re.match(r"(.*?)\s*\((.*)\)$", q)
    ret = tclass({"qualType": m.group(1)}) if m else "?"
    ps = [tclass(c.get("type", {})) for c in fd.get("inner", ()) if c.get("kind") == "ParmVarDecl"]
    proto = not (m and m.group(2).strip() == "" and not ps)
    return ret, (ps if proto else None), "..." in q


def split_top(s):
    out, depth, cur = [], 0, ""
    for c in s:
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        if c == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += c
    if cur.strip():
        out.append(cur.strip())
    return out


def castsig(t):
    """fsig of a cast to a function pointer type (m2c's `#define f ((T (*)(...)) f)`)."""
    q = t.get("desugaredQualType", t.get("qualType", ""))
    m = re.match(r"(.*?)\s*\(\*\)\s*\((.*)\)$", q)
    if not m:
        return None
    ps = split_top(m.group(2))
    var = "..." in ps
    ps = [x for x in ps if x != "..."]
    if ps == ["void"]:
        ps = []
    return tclass({"qualType": m.group(1)}), ([tclass({"qualType": x}) for x in ps] if ps or "void" in m.group(2) else None), var


def walk(n, fn):
    fn(n)
    for c in n.get("inner", ()):
        if isinstance(c, dict):
            walk(c, fn)


class FileScan:
    def __init__(self, path):
        self.path = path
        self.defs = {}      # name -> (nparams, variadic)
        self.calls = []     # (caller, line, nargs, bases, fields, locals, type)
        self.inits = {}     # data name -> [function names] (C initializers, assignments)
        self.fields = {}    # struct field -> [function names] assigned to it
        self.param_sets = []  # (data name or field, function, parameter index) set from a parameter
        self.fnargs = {}    # (callee, argument index) -> [function names] passed
        self.fwd = []       # (callee, argument index, caller, caller's parameter index) passed on
        self.line = 0
        self.file = None
        self.in_main = True
        self.errors = []
        self.defsig = {}    # name -> fsig of the definition
        self.decls = []     # (name, file, line, fsig) of each declaration (not a definition)
        self.promos = []    # (callee, argument index, line, caller): an f32 promoted to double

    def loc(self, n):
        for key in ("loc", "range"):
            l = n.get(key)
            if not l:
                continue
            if key == "range":
                l = l.get("begin", {})
            l = l.get("expansionLoc", l)
            if "file" in l:
                self.file = l["file"]
                self.in_main = os.path.normpath(l["file"]) == os.path.normpath(self.path)
            if "line" in l:
                self.line = l["line"]

    def run(self):
        p = subprocess.run(["clang"] + CFLAGS + [self.path], cwd=ROOT, capture_output=True, text=True)
        # clang refuses what gcc only warns about: a call with fewer arguments than a
        # prototype (or a K&R definition) names is the same passthrough, so report it
        self.errors = [l for l in p.stderr.splitlines() if ": error: " in l]
        if not p.stdout.strip():
            return self
        tu = json.loads(p.stdout)
        for d in tu.get("inner", ()):
            self.loc(d)
            if d.get("kind") == "FunctionDecl":
                if any(c.get("kind") == "CompoundStmt" for c in d.get("inner", ())):
                    self.defsig[d["name"]] = fsig(d)
                elif self.file and not os.path.isabs(self.file) and not d.get("isImplicit"):
                    self.decls.append((d["name"], self.file, self.line, fsig(d)))
            if d.get("kind") == "FunctionDecl" and any(c.get("kind") == "CompoundStmt" for c in d.get("inner", ())):
                ps = [c for c in d.get("inner", ()) if c.get("kind") == "ParmVarDecl"]
                var = d.get("variadic", False) or "..." in d.get("type", {}).get("qualType", "")
                self.defs[d["name"]] = (len(ps), var)
                if self.in_main:
                    self.func(d)
            elif d.get("kind") == "VarDecl" and d.get("inner") and self.in_main:
                names = []
                walk(d, lambda n: names.append(n["referencedDecl"]["name"]) if n.get("kind") == "DeclRefExpr"
                     and n.get("referencedDecl", {}).get("kind") == "FunctionDecl" else None)
                if names:
                    self.inits.setdefault(dname(d["name"]), []).extend(names)
            # keep the file / line state of the dump's order (it names a file only when it changes)
            walk(d, self.loc)
        return self

    def func(self, fd):
        assigns = {}  # local id -> [rhs nodes]

        params = [c["id"] for c in fd.get("inner", ()) if c.get("kind") == "ParmVarDecl"]
        local_ids = set()
        walk(fd, lambda n: local_ids.add(n["id"]) if n.get("kind") == "VarDecl" else None)

        def fnref(e):
            e = strip(e)
            if e.get("kind") == "UnaryOperator" and e.get("opcode") == "&":
                e = strip(e["inner"][0])
            if e.get("kind") == "DeclRefExpr" and e["referencedDecl"].get("kind") == "FunctionDecl":
                return e["referencedDecl"]["name"]
            return None

        def store(lhs, rhs):
            """lhs = rhs outside the locals: remember a function (or a parameter) stored in data or a field."""
            f = fnref(rhs)
            r = strip(rhs)
            pidx = None
            if r.get("kind") == "DeclRefExpr" and r["referencedDecl"].get("id") in params:
                pidx = params.index(r["referencedDecl"]["id"])
            if f is None and pidx is None:
                return
            keys = []

            def g(n):
                k = n.get("kind")
                if k == "DeclRefExpr" and n["referencedDecl"].get("kind") == "VarDecl" \
                        and n["referencedDecl"]["id"] not in local_ids:
                    keys.append(dname(n["referencedDecl"]["name"]))
                elif k == "MemberExpr":
                    keys.append("." + member(n))
            walk(lhs, g)
            for key in keys[:1] + [k for k in keys[1:] if k.startswith(".")][-1:]:
                if f is not None:
                    (self.fields.setdefault(key[1:], []) if key.startswith(".") else
                     self.inits.setdefault(key, [])).append(f)
                else:
                    self.param_sets.append((key, fd["name"], pidx))

        def collect(n):
            self.loc(n)
            k = n.get("kind")
            if k == "VarDecl" and n.get("inner"):
                assigns.setdefault(n["id"], []).append(n["inner"][0])
            elif k == "BinaryOperator" and n.get("opcode") == "=":
                lhs = strip(n["inner"][0])
                if lhs.get("kind") == "DeclRefExpr" and lhs["referencedDecl"].get("id") in local_ids:
                    assigns.setdefault(lhs["referencedDecl"]["id"], []).append(n["inner"][1])
                else:
                    store(n["inner"][0], n["inner"][1])
            elif k == "CallExpr":
                c = strip(n["inner"][0])
                if c.get("kind") == "DeclRefExpr":
                    for i, arg in enumerate(n["inner"][1:]):
                        f = fnref(arg)
                        if f:
                            self.fnargs.setdefault((c["referencedDecl"]["name"], i), []).append(f)
                        r = strip(arg)
                        if r.get("kind") == "DeclRefExpr" and r["referencedDecl"].get("id") in params:
                            self.fwd.append((c["referencedDecl"]["name"], i, fd["name"],
                                             params.index(r["referencedDecl"]["id"])))
        walk(fd, collect)

        def reads(e, seen):
            bases, fields, locs = set(), set(), set()

            def f(n):
                k = n.get("kind")
                if k == "DeclRefExpr":
                    r = n["referencedDecl"]
                    if r.get("kind") == "VarDecl":
                        if r["id"] in assigns and r["id"] not in seen:
                            locs.add(r["name"])
                            seen.add(r["id"])
                            for rhs in assigns[r["id"]]:
                                b2, f2, l2 = reads(rhs, seen)
                                bases.update(b2)
                                fields.update(f2)
                                locs.update(l2)
                        elif r["id"] not in assigns:
                            bases.add(dname(r["name"]))
                    elif r.get("kind") == "ParmVarDecl":
                        locs.add(r["name"] + "(param)")
                        # the parameter itself is the pointer called (not a struct it points at)
                        if r["id"] in params and strip(e) is n:
                            bases.add("@%s#%d" % (fd["name"], params.index(r["id"])))
                elif k == "MemberExpr":
                    fields.add(member(n))
                elif k == "ArraySubscriptExpr":
                    b = strip(n["inner"][0])
                    if b.get("kind") == "DeclRefExpr" and b["referencedDecl"].get("kind") == "VarDecl" \
                            and "[" in b["referencedDecl"].get("type", {}).get("qualType", ""):
                        bases.add(dname(b["referencedDecl"]["name"]) + "[]")
            walk(e, f)
            return bases, fields, locs

        def visit(n):
            self.loc(n)
            if n.get("kind") == "FunctionDecl" and n is not fd and self.file and not os.path.isabs(self.file):
                self.decls.append((n["name"], self.file, self.line, fsig(n)))  # a block-scope extern
            if n.get("kind") == "CallExpr":
                callee = strip(n["inner"][0])
                c2 = callee
                if c2.get("kind") == "UnaryOperator" and c2.get("opcode") in ("*", "&"):
                    c2 = strip(c2["inner"][0])
                direct = c2.get("kind") == "DeclRefExpr" and c2["referencedDecl"].get("kind") == "FunctionDecl"
                cast = n["inner"][0]
                while cast.get("kind") in ("ImplicitCastExpr", "ParenExpr") and cast.get("inner"):
                    cast = cast["inner"][0]
                if direct and cast.get("kind") == "CStyleCastExpr":
                    sig = castsig(cast.get("type", {}))
                    if sig:
                        self.decls.append((c2["referencedDecl"]["name"], self.path, self.line, sig))
                for i, arg in enumerate(n["inner"][1:]):
                    # an unprototyped call (or a `()` cast) promotes an f32 to double
                    if arg.get("kind") == "ImplicitCastExpr" and arg.get("castKind") == "FloatingCast" \
                            and arg.get("type", {}).get("qualType") == "double" and arg.get("inner") \
                            and tclass(arg["inner"][0].get("type", {})) == "f32":
                        self.promos.append((c2["referencedDecl"]["name"] if direct else None, i, self.line,
                                            fd["name"]))
                if not (c2.get("kind") == "DeclRefExpr" and c2["referencedDecl"].get("kind") == "FunctionDecl"):
                    b, fl, lc = reads(callee, set())
                    self.calls.append((fd["name"], self.line, len(n["inner"]) - 1, sorted(b), sorted(fl),
                                       sorted(lc), n["inner"][0].get("type", {}).get("qualType", "")))
            for c in n.get("inner", ()):
                if isinstance(c, dict):
                    visit(c)
        self.line = 0
        self.loc(fd)
        visit(fd)


def data_tables():
    """PIECE name -> function names in its .word entries, from the src .s files, and
    every piece's (start, size)."""
    tabs, pieces = {}, []
    for d, _, fs in os.walk(os.path.join(ROOT, "src")):
        for f in fs:
            if not f.endswith(".s"):
                continue
            cur = None
            for l in open(os.path.join(d, f), errors="replace"):
                m = re.match(r"\s*PIECE(?:_BEGIN)?\s+(D_([0-9A-Fa-f]{8})),\s*(0x[0-9a-fA-F]+|\d+)", l)
                if m:
                    pieces.append((int(m.group(2), 16), int(m.group(3), 0), m.group(1)))
                m = re.match(r"\s*PIECE(?:_BEGIN)?\s+(\w+)", l) or re.match(r"(\w+):", l)
                if m:
                    cur = m.group(1)
                    continue
                m = re.match(r"\s*\.word\s+([A-Za-z_]\w*)\s*$", l)
                if m and cur and not m.group(1).startswith(("D_", "jtbl", ".L")):
                    tabs.setdefault(cur, []).append(m.group(1))
    return tabs, sorted(pieces)


def elf_words(pieces):
    """A function that gives the functions an address range of the user's ELF points at
    (the bytes a PIECE copies from it: pointers that were not written as .word)."""
    elf_path = os.path.join(ROOT, "SLPS_251.98")
    starts = set()
    for l in open(os.path.join(ROOT, "layout.tsv")):
        f = l.split("\t")
        if f and re.match(r"[0-9a-fA-F]{8}$", f[0]):
            starts.add(int(f[0], 16))
    if not os.path.exists(elf_path):
        print("indcheck: no SLPS_251.98, data pieces are read from their .word entries only", file=sys.stderr)
        return lambda name: []
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    from elf32 import Elf  # noqa: E402
    from pathlib import Path
    elf = Elf.load(Path(elf_path))
    import bisect
    keys = [p[0] for p in pieces]

    def look(name):
        m = re.match(r"D_([0-9A-Fa-f]{8})(\[\])?$", name)
        if not m:
            return []
        addr = int(m.group(1), 16)
        if m.group(2):
            # an indexed table: the words from its start while they are functions or 0
            out = []
            for j in range(256):
                b = elf.read(addr + 4 * j, 4)
                w = int.from_bytes(b, "little") if b else -1
                if w in starts:
                    out.append("func_%08x" % w)
                elif w != 0:
                    break
            return out
        i = bisect.bisect_right(keys, addr) - 1
        if i >= 0 and pieces[i][0] <= addr < pieces[i][0] + pieces[i][1]:
            lo, size = pieces[i][0], pieces[i][1]
        else:
            lo, size = addr, 4
        b = elf.read(lo, size) or b""
        out = []
        for j in range(0, len(b) - 3, 4):
            w = int.from_bytes(b[j:j + 4], "little")
            if w in starts:
                out.append("func_%08x" % w)
        return out
    return look


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tsv")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()
    alias = {}
    for l in open(os.path.join(ROOT, "functions.tsv")):
        f = l.split("\t")
        if len(f) >= 2 and not l.startswith("#") and f[1].split():
            alias[f[0]] = "func_" + f[1].split()[0].lower()[-8:]
    norm = lambda s: alias.get(s, s)  # noqa: E731
    with ThreadPoolExecutor(a.j) as ex:
        scans = list(ex.map(lambda p: FileScan(p).run(), argcheck.files()))
    defs = {}
    for s in scans:
        for k, v in s.defs.items():
            defs.setdefault(norm(k), v)
    tabs, pieces = data_tables()
    tabs = {k: [norm(x) for x in v] for k, v in tabs.items()}
    look = elf_words(pieces)
    fnargs, fields = {}, {}
    for s in scans:
        for k, v in s.inits.items():
            tabs.setdefault(k, []).extend(norm(x) for x in v)
        for k, v in s.fnargs.items():
            fnargs.setdefault((norm(k[0]), k[1]), []).extend(norm(x) for x in v)
        for k, v in s.fields.items():
            fields.setdefault(k, []).extend(norm(x) for x in v)
    # Functions passed as arguments flow into the callee's parameter (@func#i), on through
    # the parameters it passes to other calls, and into the data or fields a parameter is
    # stored in: follow the edges to a fixpoint.
    edges = []
    for (fn, i), v in fnargs.items():
        tabs.setdefault("@%s#%d" % (fn, i), []).extend(v)
    for s in scans:
        for callee, i, caller, j in s.fwd:
            edges.append(("@%s#%d" % (norm(caller), j), "@%s#%d" % (norm(callee), i)))
        for key, fn, i in s.param_sets:
            edges.append(("@%s#%d" % (norm(fn), i), key))
    sets = {k: set(v) for k, v in tabs.items()}
    changed = True
    while changed:
        changed = False
        for a_, b_ in edges:
            add = sets.get(a_, set()) - sets.get(b_, set())
            if add:
                sets.setdefault(b_, set()).update(add)
                changed = True
    for k, v in sets.items():
        if k.startswith("."):
            fields.setdefault(k[1:], []).extend(v)
        else:
            tabs[k] = sorted(v)
    rows = []
    for s in scans:
        for caller, line, nargs, bases, flds, locs, ty in s.calls:
            bases = [b.replace("@%s#" % caller, "@%s#" % norm(caller)) for b in bases]
            # a table defined in C or as .word entries is read from there, else from the ELF
            targets = {t for b in bases for t in (tabs.get(b.rstrip("[]")) or look(b))}
            weak = {t for f in flds for t in fields.get(f, ())} - targets
            # a field name is only a name: its targets count when the data names none
            src_targets = targets or weak
            targets = sorted(src_targets)
            known = [defs[t][0] for t in targets if t in defs and not defs[t][1]]
            most = max(known) if known else None
            if most is not None and most > nargs:
                verdict = "SHORT?" if src_targets is weak else "SHORT"
            elif most is not None:
                verdict = "OK"
            elif targets:
                verdict = "?def"  # targets known, none defined in C (assembly, the SDK)
            else:
                verdict = "?"
            note = READ.get((s.path, caller))
            if note is None and s.path == "src/vm/vm_lib.c" and any(re.match(r"D_003773[0-9A-F]{2}$", b) for b in bases):
                note = VM_HOOKS
            if note and verdict != "OK":
                verdict = note.split()[0].rstrip(":")
            short = [t for t in targets if t in defs and defs[t][0] > nargs]
            rows.append((verdict, s.path, line, caller, nargs, most if most is not None else "?",
                         ",".join(b for b in bases if not b.endswith("[]")) or "-", ",".join(flds) or "-", ",".join(locs) or "-",
                         "%d/%d" % (len(short), len(targets)), ",".join(short[:6]) or "-", ty,
                         ",".join(targets[:6]) or "-", note or ""))
    # Argument and return classes (portability rule 11) from the syntax trees: every
    # declaration a file sees (headers, struct typedefs, `()` declarations, block-scope
    # externs) against the definition, and every f32 an unprototyped call promotes.
    defsig = {}
    for s in scans:
        for k, v in s.defsig.items():
            defsig.setdefault(norm(k), v)
    wide = ("f32", "f64", "i64", "q128", "rec")
    seen = set()
    for s in scans:
        for name, f, line, (ret, ps, var) in s.decls:
            d = defsig.get(norm(name))
            if not d or (f, line, name) in seen:
                continue
            seen.add((f, line, name))
            why = []
            # a 64-bit return read as 32 bits (or dropped) is its low word on x86 and ARM alike
            if ret != d[0] and (ret in wide or d[0] in wide) and "?" not in (ret, d[0]) \
                    and not ({ret, d[0]} <= {"i64", "i32", "void"}):
                why.append("returns %s, defined %s" % (ret, d[0]))
            if ps is not None and d[1] is not None and not d[2] and not var:
                for i, (a_, b_) in enumerate(zip(ps, d[1])):
                    if a_ != b_ and (a_ in wide or b_ in wide):
                        why.append("parameter %d %s, defined %s" % (i + 1, a_, b_))
            if why:
                rows.append(("ABI", f, line, "-", "-", "-", "-", "-", "-", "-", "-", name + ": " + "; ".join(why),
                             "-", ""))
        for callee, i, line, caller in s.promos:
            d = defsig.get(norm(callee)) if callee else None
            if d and d[1] is not None and i < len(d[1]) and d[1][i] == "f32":
                rows.append(("PROMO", s.path, line, caller, "-", "-", "-", "-", "-", "-", "-",
                             "%s: argument %d is an f32 passed as double (no prototype), defined f32"
                             % (callee, i + 1), "-", ""))
    for s in scans:
        for e in s.errors:
            rows.append(("CLANG", s.path, e.split(":")[1], "-", "-", "-", "-", "-", "-", "-", "-",
                         e.split(": error: ", 1)[1], "-", ""))
    shown = [r for r in rows if a.all or r[0] in ("SHORT", "SHORT?", "CLANG", "ABI", "PROMO")]
    for r in shown:
        print("\t".join(str(x) for x in r))
    n = {}
    for r in rows:
        n[r[0]] = n.get(r[0], 0) + 1
    print("%d rows (indirect calls, ABI and PROMO declarations, CLANG errors): %s"
          % (len(rows), ", ".join("%s %d" % kv for kv in sorted(n.items()))), file=sys.stderr)
    if a.tsv:
        os.makedirs(os.path.dirname(a.tsv), exist_ok=True)
        with open(a.tsv, "w") as fh:
            fh.write("verdict\tfile\tline\tcaller\tpassed\ttakes\tdata\tfields\tlocals\tshort/targets\tshort\ttype\ttargets\tnote\n")
            for r in rows:
                fh.write("\t".join(str(x) for x in r) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
