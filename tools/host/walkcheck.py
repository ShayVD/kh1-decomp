#!/usr/bin/env python3
"""Pointer walks that survive into a later loop (phase 5, docs/vita-port-plan.md 5.1z;
portability.md rule 12).

layoutcheck.py and relcheck.py see an access through a name: a base and an offset, or a
bounded index. Neither follows a pointer that a loop moves along an array and that a
later loop then moves on from where the first one stopped: snd_rpc.c's func_001ecb08
walks the 24 SE entries of the status block in one of three wildcard loops and, when it
finds nothing, its exact-match loop runs on from entry 24, 0x114 bytes past the block
(docs/sound-spec.md 3). On the PS2 those bytes are the next variable; on the host,
whatever the linker put there.

For each function of each game file (and each draft of shift/drafts.tsv) this asks
clang for the syntax tree (indcheck.py's flags) and lists every pointer variable that
a loop steps (`p++`, `p += n`, `p = p + n`, ...) and a later loop reads, with no plain
assignment to it in between (a `for (p = base; ...)` init is one). A row is a
candidate, not a bug: most are parsers that read a buffer in order (a header, then the
records after it). Rows read by hand go in REVIEWED with what bounds them.

    python3 -I tools/host/walkcheck.py [--all] [--tsv out/host/walkcheck.tsv]

--all also prints the REVIEWED rows.
"""
import argparse
import json
import os
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import argcheck  # noqa: E402
import indcheck  # noqa: E402

ROOT = argcheck.ROOT
LOOPS = ("ForStmt", "WhileStmt", "DoStmt")

# (file, function, variable): what was read. Sessions 86 on.
REVIEWED = {
    ("src/sound/snd_rpc.c", "func_001ecb08", "p"):
        "the status block's 24 SE entries, then 24 more at 0xB4 after a wildcard loop finds nothing: "
        "up to D_0063D640 + 0x2118. Since session 86 the piece (src/data/data_0063.s) holds the message "
        "buffer D_0063F640 (to +0x2100) and the host adds 0x18 zero bytes (census.py HOST_TAIL)",
    ("src/hud/cmdmenu.nostrict.c", "func_0023aed0", "idx"):
        "the sprite index list of one menu kind, read in order: as many entries as the kind's sprites "
        "(the counts func_0023aed0 is passed, session 70)",
    ("src/hud/notice.nostrict.c", "func_00243508", "p"):
        "the 9 sprites of one notice set (7 + 2, 0xC0 each): D_00656230_sets[k][9] (session 68)",
    ("src/ppp/kemat.nostrict.c", "pppKeTkFadeDraw", "p"):
        "the 256-entry CLUT: entries 0..n-1 in one colour, then n..255 as a fade (CSM1 order); n <= 255",
    ("src/ppp/kemdltfd.c", "func_001a9460", "p"):
        "the 256-entry CLUT, as pppKeTkFadeDraw: entries 0..n-1, then n..255",
    ("src/ppp/pppapi.c", "func_001763f0", "p"):
        "a loaded file's relocation header: h->n 0x20-byte entries, then a count and that many offsets "
        "(the file format, read in order)",
    ("src/text/fldtext.nostrict_nogcse.c", "func_0010e610", "b"):
        "the caller's 16-word output, four rows of four",
    ("src/util/task.c", "func_001bfcd8", "p"):
        "the task area func_001bfe50 hands it: 448 + 15 x 0x81C0 + 384 x 0x9C0 = 0x163C00 bytes of "
        "contexts and stacks, below the task table at +0x16BC00",
    ("src/util/vmath.c", "func_001be820", "p"):
        "memset: head bytes to 8-alignment, words, tail; n bytes in all",
    ("src/util/vmath.c", "func_001bef40", "d"):
        "strcat into the caller's buffer: s, then t",
}


def offset(n, which):
    r = n.get("range", {}).get(which, {})
    r = r.get("expansionLoc", r)
    o = r.get("offset")
    if o is not None and which == "end":
        o += r.get("tokLen", 0)
    return o


def ptr_type(n):
    return "*" in n.get("type", {}).get("qualType", "") and "(*)" not in n.get("type", {}).get("qualType", "")


def ref(n):
    """the local / parameter id a DeclRefExpr (after casts and parens) names, or None"""
    while n.get("kind") in ("ImplicitCastExpr", "ParenExpr", "CStyleCastExpr") and n.get("inner"):
        n = n["inner"][0]
    if n.get("kind") == "DeclRefExpr" and n.get("referencedDecl", {}).get("kind") in ("VarDecl", "ParmVarDecl"):
        return n["referencedDecl"]["id"]
    return None


def arith(n, v):
    """n is v + k or v - k (through casts and parens)"""
    while n.get("kind") in ("ImplicitCastExpr", "ParenExpr", "CStyleCastExpr") and n.get("inner"):
        n = n["inner"][0]
    if n.get("kind") == "BinaryOperator" and n.get("opcode") in ("+", "-"):
        return any(ref(c) == v or arith(c, v) for c in n.get("inner", ()))
    return False


def has_loop(n):
    found = []
    indcheck.walk(n, lambda m: found.append(1) if m.get("kind") in LOOPS else None)
    return bool(found)


def scan_function(fd):
    """[(var name, first loop line, later loop line)]"""
    names = {}
    ptrs = set()

    def decls(n):
        if n.get("kind") in ("VarDecl", "ParmVarDecl") and ptr_type(n):
            names[n["id"]] = n.get("name", "?")
            ptrs.add(n["id"])
    indcheck.walk(fd, decls)
    if not ptrs:
        return []
    steps = []    # (var, offset)
    assigns = []  # (var, offset)
    reads = []    # (var, offset)

    loops = []  # (begin, end, line, branches, ends): branches = {IfStmt id: branch}, ends = falls off no further

    def visit(n, path):
        k = n.get("kind")
        if k == "UnaryOperator" and n.get("opcode") in ("++", "--") and n.get("inner"):
            v = ref(n["inner"][0])
            if v in ptrs:
                steps.append((v, offset(n, "begin")))
        elif k == "CompoundAssignOperator" and n.get("opcode") in ("+=", "-=") and n.get("inner"):
            v = ref(n["inner"][0])
            if v in ptrs:
                steps.append((v, offset(n, "begin")))
        elif k == "BinaryOperator" and n.get("opcode") == "=" and n.get("inner"):
            v = ref(n["inner"][0])
            if v in ptrs:
                # p = p + n (or p = (T *)((u8 *)p + n)) is a step; anything else starts over (a
                # list's p = p->next, an iterator's p = next(p) and a packet builder's
                # p = put(..., p) are not walks along one array)
                (steps if arith(n["inner"][1], v) else assigns).append((v, offset(n, "begin")))
        elif k == "VarDecl" and n["id"] in ptrs and n.get("inner"):
            assigns.append((n["id"], offset(n, "begin")))
        elif k == "DeclRefExpr":
            v = ref(n)
            if v in ptrs:
                reads.append((v, offset(n, "begin")))
        if k in LOOPS:
            b, e = offset(n, "begin"), offset(n, "end")
            if b is not None and e is not None:
                branches = {}
                ends = False
                for i, (anc, child) in enumerate(path):
                    if anc.get("kind") == "IfStmt":
                        kids = [c for c in anc.get("inner", ()) if isinstance(c, dict)]
                        branches[anc["id"]] = kids.index(child) if child in kids else -1
                # the walk stops here if a return (or goto) follows the loop in a block around it
                # before anything else can run on: the loop's own block, or the blocks of the ifs
                # and blocks between it and the function body
                for anc, child in reversed(path):
                    if anc.get("kind") in LOOPS:
                        break
                    if anc.get("kind") == "CompoundStmt":
                        kids = anc.get("inner", ())
                        after = kids[kids.index(child) + 1:] if child in kids else []
                        for c in after:
                            if c.get("kind") in ("ReturnStmt", "GotoStmt"):
                                ends = True
                                break
                            if has_loop(c):
                                break
                        if after:
                            break
                rb = n.get("range", {}).get("begin", {})
                loops.append((b, e, rb.get("expansionLoc", rb).get("line"), branches, ends))
        for c in n.get("inner", ()):
            if isinstance(c, dict):
                visit(c, path + [(n, c)])
    visit(fd, [])
    # outermost loops only: a nested loop is part of its parent's walk
    top = []
    for L in sorted(loops, key=lambda L: (L[0], -L[1])):
        if top and L[0] >= top[-1][0] and L[1] <= top[-1][1]:
            continue
        top.append(L)

    def exclusive(L1, L2):
        return any(k in L2[3] and L2[3][k] != v for k, v in L1[3].items())
    rows = []
    for v in ptrs:
        st = [o for w, o in steps if w == v and o is not None]
        asg = sorted(o for w, o in assigns if w == v and o is not None)
        rd = sorted(o for w, o in reads if w == v and o is not None)
        walked = [L for L in top if any(L[0] <= o < L[1] for o in st)]
        for i, L1 in enumerate(walked):
            for L2 in top:
                if L2[0] < L1[1] or exclusive(L1, L2):
                    continue
                if L1[4]:
                    break
                use = [o for o in rd if L2[0] <= o < L2[1]]
                if not use:
                    continue
                first_use = min(use)
                # an assignment between the loops, or in L2 before its first read (a for init)
                if any(L1[1] <= o <= first_use for o in asg):
                    continue
                # the first read in L2 must not be the target of an assignment that starts over
                rows.append((names[v], L1[2], L2[2]))
                break
    return sorted(set(rows), key=lambda r: (r[1] or 0, r[0]))


def scan_file(path):
    p = subprocess.run(["clang"] + indcheck.CFLAGS + [path], cwd=ROOT, capture_output=True, text=True)
    if not p.stdout.strip():
        return path, None, []
    tu = json.loads(p.stdout)
    out = []
    cur = [None]

    def locfile(n):
        for key in ("loc", "range"):
            l = n.get(key)
            if not l:
                continue
            if key == "range":
                l = l.get("begin", {})
            l = l.get("expansionLoc", l)
            if "file" in l:
                cur[0] = l["file"]
    for d in tu.get("inner", ()):
        locfile(d)
        if d.get("kind") == "FunctionDecl" and any(c.get("kind") == "CompoundStmt" for c in d.get("inner", ())) \
                and cur[0] and os.path.normpath(cur[0]) == os.path.normpath(path):
            for row in scan_function(d):
                out.append((d["name"],) + row)
        indcheck.walk(d, locfile)
    return path, True, out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tsv")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()
    with ThreadPoolExecutor(a.j) as ex:
        res = list(ex.map(scan_file, argcheck.files()))
    rows, failed = [], []
    for path, ok, out in res:
        if ok is None:
            failed.append(path)
        for fn, var, l1, l2 in out:
            note = REVIEWED.get((path, fn, var))
            rows.append((path, fn, var, l1, l2, "REVIEWED: " + note if note else "WALK"))
    shown = [r for r in rows if a.all or r[5] == "WALK"]
    for r in shown:
        print("%s:%s %s: `%s` walked in the loop at line %s, read on in the loop at line %s  %s"
              % (r[0], r[3], r[1], r[2], r[3], r[4], r[5]))
    if a.tsv:
        os.makedirs(os.path.dirname(os.path.abspath(a.tsv)), exist_ok=True)
        with open(a.tsv, "w") as f:
            for r in rows:
                f.write("\t".join(str(x) for x in r) + "\n")
    print("walkcheck: %d files, %d rows (%d WALK, %d REVIEWED), %d files clang could not read%s"
          % (len(res), len(rows), sum(1 for r in rows if r[5] == "WALK"), sum(1 for r in rows if r[5] != "WALK"),
             len(failed), (": " + ", ".join(failed)) if failed else ""))


if __name__ == "__main__":
    main()
