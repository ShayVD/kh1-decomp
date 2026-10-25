#!/usr/bin/env python3
"""Counts kept across functions (phase 5, docs/vita-port-plan.md 5.1ab; portability.md rule 12).

walkcheck.py's idx rows follow an integer inside one function. A count can also live in a
global: one function steps it (`D_00643200[k]++`, `n = D_x++`, `D_x += 1`), another indexes
an array with it (`list[D_x]`, `p + D_x`). If nothing bounds the count, the index runs past
the array, on the PS2 into the next variable and on the host into whatever the linker put
there. layoutcheck.py's idx-next rows see some of these from the linked ELF, as indexes it
cannot bound; this lists them from the C, with the function that steps the count.

For each game file (and each draft of shift/drafts.tsv) this asks clang for the syntax tree
(indcheck.py's flags) and records, by global name (`G`, `G[]` for an element of an array, `G.f`
for a field):
  steps    `++` / `--` / `+=` / `-=` / `G = G + k` on an integer global
  indexes  an array subscript or pointer offset whose index holds the global, directly or
           through a local assigned from it (`n = G; a[n]`, `n = G++`)
  bounds   comparisons of the global with a constant, `% k` / `& k` on it, and plain stores
A row is (counter, the function that steps it, a function elsewhere that indexes with it,
the array and its size when the type has one, the largest constant it is compared with).
Rows read by hand go in REVIEWED with what bounds them.

    python3 -I tools/host/countcheck.py [--all] [--tsv out/host/countcheck.tsv]

--all also prints the REVIEWED rows.
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
import indcheck  # noqa: E402
import walkcheck  # noqa: E402

ROOT = argcheck.ROOT
STRIP = ("ImplicitCastExpr", "ParenExpr", "CStyleCastExpr")
CMP = ("<", "<=", ">", ">=", "==", "!=")

# (counter, indexing file): what bounds it, read by hand (every indexing function of that file).
# DATA rows are bounded only by what the disc's files hold, on the PS2 as well: a port-only build
# can cap them or count the high-water mark on a real-disc run. Session 88 on.
REVIEWED = {
    ("D_002C12C4", "src/coll/mapcoll.c"):
        "DATA: the collision candidate list D_002BD250[2048] (ids / polygon pointers), reset per query "
        "(func_00116368 / func_00117db0 / func_001191c8), one entry per polygon of the map's grid cells the "
        "query box touches that the filter keeps; no bound check: a query over more than 2048 polygons runs "
        "into the next variable on the PS2 too (layoutcheck idx-next)",
    ("D_0052528C", "src/game/cmdmenu.nostrict_nofill.c"):
        "the lock-on target ring D_00524F80[97] (8-byte (actor, point) pairs): func_0012f5c0 appends only what "
        "func_0012f3d0 finds, and it skips every pair already in the list, so the list holds distinct "
        "targets in range; 97 is reached only with 97 lock-on points around the player",
    ("D_0029B2FC", "src/gfx/grideff.nostrict.c"):
        "DATA: renderer A's grid lists (renderer-spec 4.14), reset each frame in func_00107548, one entry "
        "per visible cell of the room's grid (D_00494BB0, map section 1): the chains hold 0x4000 bytes "
        "(about 1020 entries) and the z buffers 1024 floats, so a room with more than about 1020 cells "
        "on one side overruns (read the real disc's largest cell count)",
    ("D_0029B2F4", "src/gfx/grideff.nostrict.c"): "as D_0029B2FC (the other half of the lists)",
    ("D_006305CC", "src/list/list.c"):
        "the paged list's page 0..4 (stepped only below 4, func_001e5198 / func_001e65d0 turn 4 into 3), "
        "10 a page: l3[50] and D_006305D0[50][10] (the 50-entry fill of func_001e4b08)",
    ("D_00642CDC", "src/menu/customize.nostrict.c"):
        "the cursor in a member's list D_003F40F8[k] (0 .. n - 1, wrapping; 0 when the member changes); "
        "a list with n = 0 would give -1 on UP at 0 (customize.c func_00216890) and a NULL p: in the ELF "
        "(D_003F40F8, {p, n} x 10) members 1-3 and 5-9 hold 4 to 6 entries, members 0 and 4 none (Sora, "
        "who the cursor skips, and member 4: check that it never joins the party; a NULL read crashes the "
        "host, not the PS2)",
    ("D_00641B98", "src/menu/items.c"):
        "the Gummi kinds held, counted over D_00623210->n = 160 (D_00377848, from the ELF) into buf[192]",
    ("D_00643200[]", "src/menu/journal_s2.c"):
        "the journal's three lists, filled by fixed loops (49, 78, 57 of D_003F50E0[184]) into D_00643128[56], "
        "D_00643160[80], D_006431B0[64] (session 87's IDX_REVIEWED row)",
    ("D_0046A540", "src/menu/nameentry.c"):
        "the name entry's page 0..4 (wraps at 5) into D_0046A568[6]; c[page == k] is a 0 / 1 index",
    ("D_00669A58", "src/menu/nameentry.c"):
        "the name's next character 0..7 (held at 7) into D_00669A40[8]",
    ("D_003F3870", "src/menu/partymdl.c"):
        "the party models loaded, 0..3 (three tries); with 0, D_003F31D0[-1] is read (the word before the "
        "4-pointer table) and not used (the loop runs 0 times). The draws index the slots by count, not "
        "by slot: a missing member 1 with a member 2 draws slots 0 and 1 (the PS2 the same)",
    ("D_0055C698.x8", "src/model/mdldraw.nostrict.c"):
        "DATA: renderer B's per-frame lists, reset each frame (func_00160370): models pr[2][72], objects "
        "obj[2][78], part draws dsl[2][480]; no bound check: a frame with more than 480 visible parts "
        "writes into the other frame's list (dsl[x0 + 1]) or, for frame 1, past the 0xDA58-byte block "
        "(layoutcheck idx-next); count the high-water mark on a real-disc run",
    ("D_00389C80", "src/msgwin/msgwin.c"):
        "DATA: the message pointer table D_00388480[273]: func_001c2d20 fills the event file's messages "
        "(its count word, no bound) and the script commands func_001cb120 / func_001cb738 / func_001cb7d0 "
        "append one each; no bound check (not in layoutcheck: a table of pointers it sees as one name). "
        "Read the real disc's event files: count + appended <= 273",
    ("D_00389C90.cnt[]", "src/msgwin/msgwin.c"):
        "DATA: a window's message list tbl[k][256], reset when the window opens (msgwin.c lines 100, 114, "
        "180); one entry per script command: inside D_00389C90 (the host keeps the struct whole)",
    ("D_0037A154", "src/util/memstack.c"):
        "the memory stack's 4-deep save stack D_00623200[4]: func_001bb480 / func_001bb4b0 have no "
        "main-ELF caller (an overlay's; check the depth in the overlay inventory)",
    ("D_00389C90.nbox", "src/vm/vm_lib.c"):
        "DATA: the script's trigger boxes box[10] (func_001d6250 adds, func_001d63e8 removes, reset in "
        "script_vm.c func_001c2ec8), no bound check: an event adding more than 10 overruns inside D_00389C90",
}


def strip(n):
    while n.get("kind") in STRIP and n.get("inner"):
        n = n["inner"][0]
    return n


def gkey(n, globs):
    """the global an lvalue names: "G", "G[]" (an element), "G.f" (a field), or None"""
    n = strip(n)
    k = n.get("kind")
    if k == "DeclRefExpr":
        d = n.get("referencedDecl", {})
        if d.get("kind") == "VarDecl" and d.get("id") in globs:
            return d.get("name")
        return None
    if k == "UnaryOperator" and n.get("opcode") in ("*", "&") and n.get("inner"):
        return gkey(n["inner"][0], globs)
    if k == "ArraySubscriptExpr" and n.get("inner"):
        g = gkey(n["inner"][0], globs)
        return g + "[]" if g else None
    if k == "MemberExpr" and n.get("inner"):
        g = gkey(n["inner"][0], globs)
        return g + "." + n.get("name", "?") if g else None
    return None


def int_lvalue(n):
    return walkcheck.int_type(n)


def int_lit(n):
    n = strip(n)
    if n.get("kind") == "IntegerLiteral":
        try:
            return int(n.get("value"), 0)
        except (TypeError, ValueError):
            return None
    return None


def array_size(base):
    """N when the subscript's base is an array of N (before its decay), else None"""
    b = base
    while b.get("kind") in STRIP and b.get("inner"):
        q = b.get("type", {}).get("qualType", "")
        m = re.match(r"[^\[]*\[(\d*)\]", q)
        if m and b.get("kind") != "ImplicitCastExpr":
            return int(m.group(1)) if m.group(1) else None
        b = b["inner"][0]
    # the outer dimension: "T [N][M]" is N; "T [][M]" (an extern of unknown size) has none
    m = re.match(r"[^\[]*\[(\d*)\]", b.get("type", {}).get("qualType", ""))
    return int(m.group(1)) if m and m.group(1) else None


def base_name(base, globs):
    b = strip(base)
    g = gkey(b, globs)
    if g:
        return g
    if b.get("kind") == "DeclRefExpr":
        return b.get("referencedDecl", {}).get("name", "?")
    if b.get("kind") == "MemberExpr":
        return "." + b.get("name", "?")
    return "?"


def keys_in(n, globs, locs):
    """the globals an index expression reads: direct, or through a local assigned from one; with
    whether a % or & constant bounds that use"""
    out = []

    def f(m, bounded):
        k = m.get("kind")
        if k == "BinaryOperator" and m.get("opcode") in ("%", "&") and any(int_lit(c) is not None
                                                                       for c in m.get("inner", ())):
            bounded = True
        g = gkey(m, globs) if k in ("DeclRefExpr", "ArraySubscriptExpr", "MemberExpr") else None
        if g:
            out.append((g, bounded))
            return
        if k == "DeclRefExpr":
            v = m.get("referencedDecl", {}).get("id")
            for g2 in locs.get(v, ()):
                out.append((g2, bounded))
            return
        for c in m.get("inner", ()):
            if isinstance(c, dict):
                f(c, bounded)
    f(n, False)
    return out


def scan_file(path):
    p = subprocess.run(["clang"] + indcheck.CFLAGS + [path], cwd=ROOT, capture_output=True, text=True)
    if not p.stdout.strip():
        return path, None
    tu = json.loads(p.stdout)
    with open(os.path.join(ROOT, path), "rb") as fh:
        src = fh.read()

    def lineof(o):
        return src.count(b"\n", 0, o) + 1 if o is not None else None
    globs = {d["id"] for d in tu.get("inner", ()) if d.get("kind") == "VarDecl"}
    res = {"steps": [], "index": [], "bounds": []}
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

    def scan_fn(fd):
        fn = fd["name"]
        locs = {}  # local id -> {globals it was assigned from}

        def assigned(v, rhs):
            gs = {g for g, _ in keys_in(rhs, globs, locs)}
            if gs:
                locs.setdefault(v, set()).update(gs)

        def visit(n):
            k = n.get("kind")
            inner = [c for c in n.get("inner", ()) if isinstance(c, dict)]
            if k == "UnaryOperator" and n.get("opcode") in ("++", "--") and inner:
                g = gkey(inner[0], globs)
                if g and int_lvalue(inner[0]):
                    res["steps"].append((g, fn, lineof(walkcheck.offset(n, "begin"))))
            elif k == "CompoundAssignOperator" and n.get("opcode") in ("+=", "-=") and inner:
                g = gkey(inner[0], globs)
                if g and int_lvalue(inner[0]):
                    res["steps"].append((g, fn, lineof(walkcheck.offset(n, "begin"))))
            elif k == "BinaryOperator" and n.get("opcode") == "=" and len(inner) == 2:
                g = gkey(inner[0], globs)
                if g and int_lvalue(inner[0]):
                    if any(gkey(c, globs) == g for c in strip(inner[1]).get("inner", ())
                           if isinstance(c, dict)) and strip(inner[1]).get("opcode") in ("+", "-"):
                        res["steps"].append((g, fn, lineof(walkcheck.offset(n, "begin"))))
                    else:
                        lit = int_lit(inner[1])
                        res["bounds"].append((g, fn, "store", lit))
                v = walkcheck.ref(inner[0])
                if v is not None:
                    assigned(v, inner[1])
            elif k == "VarDecl" and inner:
                assigned(n["id"], inner[0])
            elif k == "BinaryOperator" and n.get("opcode") in CMP and len(inner) == 2:
                for a, b in ((inner[0], inner[1]), (inner[1], inner[0])):
                    for g, _ in keys_in(a, globs, locs):
                        res["bounds"].append((g, fn, "cmp", int_lit(b)))
            elif k == "ArraySubscriptExpr" and len(inner) == 2:
                for g, bounded in keys_in(inner[1], globs, locs):
                    if gkey(n, globs) == g:
                        continue
                    res["index"].append((g, fn, lineof(walkcheck.offset(n, "begin")), base_name(inner[0], globs),
                                         array_size(inner[0]), bounded))
            elif k == "BinaryOperator" and n.get("opcode") in ("+", "-") and "*" in n.get("type", {}).get("qualType", ""):
                for c in inner:
                    if "*" not in c.get("type", {}).get("qualType", ""):
                        for g, bounded in keys_in(c, globs, locs):
                            other = [d for d in inner if d is not c]
                            res["index"].append((g, fn, lineof(walkcheck.offset(n, "begin")),
                                                 base_name(other[0], globs) if other else "?", None, bounded))
            for c in inner:
                visit(c)
        visit(fd)

    for d in tu.get("inner", ()):
        locfile(d)
        if d.get("kind") == "FunctionDecl" and any(c.get("kind") == "CompoundStmt" for c in d.get("inner", ())) \
                and cur[0] and os.path.normpath(cur[0]) == os.path.normpath(path):
            scan_fn(d)
        indcheck.walk(d, locfile)
    return path, res


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tsv")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()
    with ThreadPoolExecutor(a.j) as ex:
        res = list(ex.map(scan_file, argcheck.files()))
    failed = [path for path, r in res if r is None]
    steps = {}   # counter -> {(file, fn)}
    bounds = {}  # counter -> [constants compared with]
    for path, r in res:
        if r is None:
            continue
        for g, fn, line in r["steps"]:
            steps.setdefault(g, set()).add((path, fn))
        for g, fn, how, lit in r["bounds"]:
            if how == "cmp" and lit is not None:
                bounds.setdefault(g, []).append(lit)
    rows = {}
    for path, r in res:
        if r is None:
            continue
        for g, fn, line, arr, size, bounded in r["index"]:
            if g not in steps or bounded:
                continue
            others = sorted({f for p, f in steps[g] if (p, f) != (path, fn)})
            if not others:
                continue
            key = (g, path, fn)
            if key in rows:
                continue
            cmax = max(bounds.get(g, [None]), key=lambda x: -1 if x is None else x)
            note = REVIEWED.get(key) or REVIEWED.get((g, path))
            rows[key] = (g, ",".join(others), path, fn, line, arr, size, cmax,
                         "REVIEWED: " + note if note else "COUNT")
    out = sorted(rows.values(), key=lambda r: (r[2], r[4] or 0))
    shown = [r for r in out if a.all or r[8] == "COUNT"]
    for g, st, path, fn, line, arr, size, cmax, note in shown:
        print("%s:%s %s: %s[%s] (size %s), %s stepped in %s, largest compared constant %s  %s"
              % (path, line, fn, arr, g, size if size is not None else "?", g, st,
                 cmax if cmax is not None else "none", note))
    if a.tsv:
        os.makedirs(os.path.dirname(os.path.abspath(a.tsv)), exist_ok=True)
        with open(a.tsv, "w") as f:
            for r in out:
                f.write("\t".join(str(x) for x in r) + "\n")
    print("countcheck: %d files, %d stepped globals, %d rows (%d COUNT, %d REVIEWED), %d files clang could not read%s"
          % (len(res), len(steps), len(out), sum(1 for r in out if r[8] == "COUNT"),
             sum(1 for r in out if r[8] != "COUNT"), len(failed), (": " + ", ".join(failed)) if failed else ""))


if __name__ == "__main__":
    main()
