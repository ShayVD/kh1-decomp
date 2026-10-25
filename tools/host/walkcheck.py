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

Session 87 adds two siblings. Index walks (idx): an integer a loop steps (`i++`, `n += k`)
and a later loop uses as an array index (`a[i]`, `p + i`) with no assignment in between,
`for (i = 0; i < n; i++) ...; for (; i < m; i++) a[i]`: a count that runs on from one
list into the next. Builder results (call): a pointer assigned the result of a builder
(a function that returns a pointer one of its loops stepped, or another builder's
result) that a later loop steps on from, `p = skip(p, 1); n = *p++; for (...) *p++`.
Their hand-read rows go in IDX_REVIEWED and CALL_REVIEWED.

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

# Index walks (file, function, variable): an integer a loop steps and a later loop indexes with.
# Session 87 on.
IDX_REVIEWED = {
    ("src/gummi/ship.c", "func_001bb580", "i"):
        "the block table D_00377848 (160 entries of 0x1C): the 64 held kinds, then the run of 64 empty "
        "ones; the second loop stops at entry 128 (type 9), read from the disc's ELF",
    ("src/gummi/ship.c", "func_001bb880", "i"):
        "the ten saved ships: the packed ones, then the rest cleared up to i < 10",
    ("src/gummi/ship.c", "func_001bd470", "k"):
        "the preset ships of held blocks 71-118 (k <= 48), then the ten saved ones at p[k + 1 + i]: up to "
        "D_00623E40[58] of 64 (0x1800 bytes before D_00625640)",
    ("src/menu/journal_s2.c", "func_0021dc40", "i"):
        "one count through the three journal lists, 0-48, 49-126, 127-183: D_003F50E0 holds 184 words; "
        "the lists D_00643128 / D_00643160 / D_006431B0 / D_00643210 hold 56 / 80 / 64 / 60 >= 49 / 78 / 57 / 57",
    ("src/menu/journal_s3.nofill.c", "func_00220c28", "k"):
        "the 50 cells of the left grid (goto at 50), then the right 7 x 7: k < 99, D_00643430 holds 99 words",
    ("src/menu/savemenu.c", "func_00228588", "j"):
        "buf[4] (j <= 4). The fill steps j by 2: one member found leaves buf[3] unset, none leaves buf[2] "
        "unset, and func_0013c778 puts a stack byte < 10 into the party (the PS2 does the same: "
        "vita-port-plan 5.1aa)",
    ("src/model/motion.nostrict.c", "func_00164f18", "n"):
        "a count of the key records; each store into out[n - 1] is behind n++ < max",
    ("src/msgwin/msgwin.c", "func_001cb7d0", "i"):
        "the digits (n <= 10) then 12 bytes of D_003C5650 (16): at most 22 of D_0062A1F0's 32",
    ("src/ppp/kemat.nostrict.c", "pppKeTkFadeDraw", "i"):
        "indexes only buf->tbl[i & 0x1F]",
    ("src/ppp/kemdltfd.c", "func_001a9460", "i"):
        "indexes only tb[i & 0x1f]",
    ("src/text/text.nofill.c", "func_001f18e8", "n"):
        "dig[12]: at most 10 digits, or nd with padding; func_001f2d68 passes 10, nothing else in the "
        "main ELF calls it",
    ("src/text/textwin.c", "func_001f82b0", "n"):
        "list[24]: the open text windows, all from the pool D_0063F758[24]",
    ("src/text/wintext.nostrict.c", "func_001fbcd8", "n"):
        "dig[12]: at most 10 digits, or nd with padding; the main ELF passes nd 0, 2 or 5 "
        "(shopgummi.c, func_001fbcb0)",
    ("src/text/wintext.nostrict_nogcse.c", "func_001fb428", "n"):
        "dig[12]: at most 10 digits, or nd with padding; literal nd 0-4 in the main ELF, but "
        "wintext.nostrict.c's message code 11 passes the message's byte s[2] (> 12 overruns dig on the "
        "PS2 too: check the real disc's messages); func_001fb3e0 / func_001fbb50 have no main-ELF caller",
}

# Builder results walked on (file, function, variable, builder). Session 87 on.
CALL_REVIEWED = {
    ("src/ppp/pppsys.c", "func_00180c20", "p", "func_001803c0"):
        "a ppp file's count-prefixed sections: func_001803c0 skips one, then a count and that many words "
        "(the file format, as func_001763f0)",
    ("src/ppp/pppsys.c", "func_00180ce0", "p", "func_001803c0"): "as func_00180c20",
    ("src/ppp/pppsys.c", "func_00180d50", "p", "func_001803c0"): "as func_00180c20",
    ("src/ppp/pppsys.c", "func_00180e10", "p", "func_001803c0"): "as func_00180c20",
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


INT_WORDS = ("int", "char", "short", "long", "unsigned", "signed", "s8", "u8", "s16", "u16", "s32", "u32",
             "s64", "u64", "size_t")


def int_type(n):
    q = n.get("type", {}).get("qualType", "")
    if any(c in q for c in "*[(") or any(w in q for w in ("float", "double", "struct", "union", "enum")):
        return False
    return any(w in INT_WORDS for w in q.replace("const", "").replace("volatile", "").split())


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


def callee(n):
    """the function a call (through casts and parens) names, or None"""
    while n.get("kind") in ("ImplicitCastExpr", "ParenExpr", "CStyleCastExpr") and n.get("inner"):
        n = n["inner"][0]
    if n.get("kind") != "CallExpr" or not n.get("inner"):
        return None
    f = n["inner"][0]
    while f.get("kind") in ("ImplicitCastExpr", "ParenExpr") and f.get("inner"):
        f = f["inner"][0]
    if f.get("kind") == "DeclRefExpr" and f.get("referencedDecl", {}).get("kind") == "FunctionDecl":
        return f["referencedDecl"].get("name")
    return None


def refs_in(n, vs):
    """[(var, offset)] for every DeclRefExpr of a var in vs inside n"""
    out = []

    def f(m):
        if m.get("kind") == "DeclRefExpr":
            v = ref(m)
            if v in vs:
                out.append((v, offset(m, "begin")))
    indcheck.walk(n, f)
    return out


def scan_function(fd, lineof):
    """{"ptr": [(var, first loop line, later loop line)], "idx": [...], "call": [(var, callee, line of the
    assignment, loop line)], "returns": {"walked": bool, "calls": set of callees whose result is returned}}

    ptr: a pointer a loop steps and a later loop reads. idx: an integer a loop steps and a later loop
    uses as an array index (a[i], p + i). call: a pointer assigned a call's result and then stepped in
    a loop before anything else is assigned to it (kept only when the callee is a builder: it returns a
    pointer one of its loops stepped, main() decides). returns: what this function returns."""
    names = {}
    ptrs = set()
    ints = set()

    def decls(n):
        if n.get("kind") in ("VarDecl", "ParmVarDecl"):
            if ptr_type(n):
                names[n["id"]] = n.get("name", "?")
                ptrs.add(n["id"])
            elif int_type(n):
                names[n["id"]] = n.get("name", "?")
                ints.add(n["id"])
    indcheck.walk(fd, decls)
    out = {"ptr": [], "idx": [], "call": [], "returns": {"walked": False, "calls": set()}}
    if not ptrs and not ints:
        return out
    tracked = ptrs | ints
    steps = []    # (var, offset)
    assigns = []  # (var, offset)
    calls = []    # (var, offset, callee): p = f(...)
    reads = []    # (var, offset): pointers, any read
    idxuse = []   # (var, offset): integers, used as an index
    rets = []     # return expressions

    loops = []  # (begin, end, line, branches, ends): branches = {IfStmt id: branch}, ends = falls off no further

    def visit(n, path):
        k = n.get("kind")
        if k == "UnaryOperator" and n.get("opcode") in ("++", "--") and n.get("inner"):
            v = ref(n["inner"][0])
            if v in tracked:
                steps.append((v, offset(n, "begin")))
        elif k == "CompoundAssignOperator" and n.get("opcode") in ("+=", "-=") and n.get("inner"):
            v = ref(n["inner"][0])
            if v in tracked:
                steps.append((v, offset(n, "begin")))
        elif k == "BinaryOperator" and n.get("opcode") == "=" and n.get("inner"):
            v = ref(n["inner"][0])
            if v in tracked:
                # p = p + n (or p = (T *)((u8 *)p + n)) is a step; anything else starts over (a
                # list's p = p->next, an iterator's p = next(p) and a packet builder's
                # p = put(..., p) are not walks along one array)
                (steps if arith(n["inner"][1], v) else assigns).append((v, offset(n, "begin")))
                c = callee(n["inner"][1])
                if c and v in ptrs:
                    calls.append((v, offset(n, "begin"), c))
        elif k == "VarDecl" and n["id"] in tracked and n.get("inner"):
            assigns.append((n["id"], offset(n, "begin")))
            c = callee(n["inner"][0])
            if c and n["id"] in ptrs:
                calls.append((n["id"], offset(n, "begin"), c))
        elif k == "DeclRefExpr":
            v = ref(n)
            if v in ptrs:
                reads.append((v, offset(n, "begin")))
        elif k == "ArraySubscriptExpr" and len(n.get("inner", ())) == 2:
            idxuse.extend(refs_in(n["inner"][1], ints))
        elif k == "BinaryOperator" and n.get("opcode") in ("+", "-") and "*" in n.get("type", {}).get("qualType", ""):
            for c in n.get("inner", ()):
                if "*" not in c.get("type", {}).get("qualType", ""):
                    idxuse.extend(refs_in(c, ints))
        elif k == "ReturnStmt" and n.get("inner"):
            rets.append(n["inner"][0])
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
                loops.append((b, e, lineof(b), branches, ends))
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

    def outermost(ls):
        out = []
        for L in sorted(ls, key=lambda L: (L[0], -L[1])):
            if out and L[0] >= out[-1][0] and L[1] <= out[-1][1]:
                continue
            out.append(L)
        return out

    def later(v, use, after, L1=None, among=None):
        """the first loop of `among` (default: the top loops) after offset `after` that uses v before
        an assignment, or None"""
        asg = sorted(o for w, o in assigns if w == v and o is not None)
        rd = sorted(o for w, o in use if w == v and o is not None)
        for L2 in (top if among is None else among):
            if L2[0] < after or (L1 and exclusive(L1, L2)):
                continue
            if L1 and L1[4]:
                return None
            u = [o for o in rd if L2[0] <= o < L2[1]]
            if not u:
                continue
            # an assignment between the loops, or in L2 before its first read (a for init)
            if any(after <= o <= min(u) for o in asg if L1 or o != after):
                continue
            return L2
        return None

    for kind, vs, use in (("ptr", ptrs, reads), ("idx", ints, idxuse)):
        rows = []
        for v in vs:
            st = [o for w, o in steps if w == v and o is not None]
            for L1 in [L for L in top if any(L[0] <= o < L[1] for o in st)]:
                L2 = later(v, use, L1[1], L1)
                if L2:
                    rows.append((names[v], L1[2], L2[2]))
        out[kind] = sorted(set(rows), key=lambda r: (r[1] or 0, r[0]))
    for v, o, c in calls:
        if o is None:
            continue
        # the loops after the call: inside the loop that holds it (to its end), or after it
        inside = [L for L in loops if L[0] <= o < L[1]]
        end = min((L[1] for L in inside), default=None)
        L2 = later(v, reads, o, among=outermost([L for L in loops if L[0] > o and (end is None or L[1] <= end)]))
        # walked on: the loop steps it (a loop that only reads a field of it is a wait or a use)
        if L2 and any(w == v and o2 is not None and L2[0] <= o2 < L2[1] for w, o2 in steps):
            out["call"].append((names[v], c, lineof(o), L2[2]))
    # a builder returns a pointer one of its loops stepped (or the result of another builder)
    for r in rets:
        v = ref(r)
        if v is None:
            while r.get("kind") in ("ImplicitCastExpr", "ParenExpr", "CStyleCastExpr") and r.get("inner"):
                r = r["inner"][0]
            if r.get("kind") == "BinaryOperator" and r.get("opcode") in ("+", "-"):
                v = next((ref(c) for c in r.get("inner", ()) if ref(c) in ptrs), None)
        if v in ptrs:
            if any(w == v and o is not None and any(L[0] <= o < L[1] for L in top) for w, o in steps):
                out["returns"]["walked"] = True
            out["returns"]["calls"] |= {c for w, o, c in calls if w == v}
        c = callee(r)
        if c:
            out["returns"]["calls"].add(c)
    return out


def scan_file(path):
    p = subprocess.run(["clang"] + indcheck.CFLAGS + [path], cwd=ROOT, capture_output=True, text=True)
    if not p.stdout.strip():
        return path, None, []
    tu = json.loads(p.stdout)
    with open(os.path.join(ROOT, path), "rb") as f:
        src = f.read()

    def lineof(o):
        return src.count(b"\n", 0, o) + 1 if o is not None else None
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
            out.append((d["name"], scan_function(d, lineof)))
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
    failed = [path for path, ok, out in res if ok is None]
    # builders: functions returning a pointer one of their loops stepped, or another builder's result
    builders = {fn for path, ok, out in res for fn, r in out if r["returns"]["walked"]}
    grew = True
    while grew:
        more = {fn for path, ok, out in res for fn, r in out if r["returns"]["calls"] & builders}
        grew = bool(more - builders)
        builders |= more
    rows = []
    for path, ok, out in res:
        for fn, r in out:
            for var, l1, l2 in r["ptr"]:
                note = REVIEWED.get((path, fn, var))
                rows.append((path, fn, "ptr", var, l1, l2, "REVIEWED: " + note if note else "WALK"))
            for var, l1, l2 in r["idx"]:
                note = IDX_REVIEWED.get((path, fn, var))
                rows.append((path, fn, "idx", var, l1, l2, "REVIEWED: " + note if note else "WALK"))
            for var, c, l1, l2 in r["call"]:
                if c not in builders:
                    continue
                note = CALL_REVIEWED.get((path, fn, var, c))
                rows.append((path, fn, "call " + c, var, l1, l2, "REVIEWED: " + note if note else "WALK"))
    shown = [r for r in rows if a.all or r[6] == "WALK"]
    for r in shown:
        if r[2] == "ptr":
            what = "`%s` walked in the loop at line %s, read on in the loop at line %s" % (r[3], r[4], r[5])
        elif r[2] == "idx":
            what = "index `%s` stepped in the loop at line %s, indexes on in the loop at line %s" % (r[3], r[4], r[5])
        else:
            what = "`%s` = builder %s() at line %s, walked on in the loop at line %s" % (r[3], r[2][5:], r[4], r[5])
        print("%s:%s %s: %s  %s" % (r[0], r[4], r[1], what, r[6]))
    if a.tsv:
        os.makedirs(os.path.dirname(os.path.abspath(a.tsv)), exist_ok=True)
        with open(a.tsv, "w") as f:
            for r in rows:
                f.write("\t".join(str(x) for x in r) + "\n")
    for kind in ("ptr", "idx", "call"):
        k = [r for r in rows if r[2].split()[0] == kind]
        print("walkcheck %s: %d rows (%d WALK, %d REVIEWED)"
              % (kind, len(k), sum(1 for r in k if r[6] == "WALK"), sum(1 for r in k if r[6] != "WALK")))
    print("walkcheck: %d files, %d builders, %d rows (%d WALK, %d REVIEWED), %d files clang could not read%s"
          % (len(res), len(builders), len(rows), sum(1 for r in rows if r[6] == "WALK"),
             sum(1 for r in rows if r[6] != "WALK"), len(failed), (": " + ", ".join(failed)) if failed else ""))


if __name__ == "__main__":
    main()
