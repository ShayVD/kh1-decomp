#!/usr/bin/env python3
"""List the cast uses of the session-26 cast-unified pieces (session 27).

  python3 -I tools/shift/s27types/s27_survey.py [--files] [D_X ...]

For each piece header include/data/pieces/D_X.h: its declaration, how many cast
uses of D_X (a cast `(T)` right before `D_X` or `&D_X`) there are in src/, in how
many files, and the distinct cast types.  Sorted by cast count.
"""
import re, sys
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
TYPE = re.compile(r"^\s*(?:(?:const|volatile|struct|union|unsigned|signed)\s+)*[A-Za-z_]\w*"
                  r"(?:\s*(?:const|volatile))*[\s\*]*(?:\(\s*\*\s*\)\s*(?:\[[^\]]*\])+)?\s*$")
BASIC = re.compile(r"^\s*(s8|u8|s16|u16|s32|u32|s64|u64|f32|int|char|M2C_UNK|uintptr_t|void)\s*$")


def back_paren(t, j):
    """t[j] == ')': index of the matching '('"""
    d = 0
    for k in range(j, -1, -1):
        if t[k] == ")":
            d += 1
        elif t[k] == "(":
            d -= 1
            if d == 0:
                return k
    return -1


def casts(t, N):
    out = []
    for m in re.finditer(r"\b" + N + r"\b", t):
        j = m.start() - 1
        while j >= 0 and t[j] in " \t":
            j -= 1
        if j >= 0 and t[j] == "&":
            j -= 1
            while j >= 0 and t[j] in " \t":
                j -= 1
        if j < 0 or t[j] != ")":
            continue
        k = back_paren(t, j)
        if k <= 0:
            continue
        inner = t[k + 1:j]
        if (TYPE.match(inner) and not re.match(r"^\s*\w+\s*$", inner)) or BASIC.match(inner):
            out.append((t.count("\n", 0, m.start()) + 1, re.sub(r"\s+", " ", inner.strip())))
    return out


def main(argv):
    files_flag = "--files" in argv
    names = [a for a in argv if a.startswith("D_")]
    hdrs = sorted((ROOT / "include/data/pieces").glob("D_*.h"))
    if names:
        hdrs = [h for h in hdrs if h.stem in names]
    srcs = {p: p.read_text() for p in (ROOT / "src").rglob("*.c")
            if not str(p).startswith(str(ROOT / "src/sdk"))}
    rows = []
    for h in hdrs:
        N = h.stem
        ht = h.read_text()
        dm = re.search(r"^extern [^\n]*\b" + N + r"\b[^\n]*;", ht, re.M)
        decl = dm.group(0) if dm else "?"
        per = defaultdict(list)
        users = 0
        for p, t in srcs.items():
            if N not in t:
                continue
            users += 1
            for ln, ty in casts(t, N):
                per[str(p.relative_to(ROOT))].append((ln, ty))
        n = sum(len(v) for v in per.values())
        if n:
            rows.append((n, N, decl, users, per))
    rows.sort(key=lambda r: -r[0])
    for n, N, decl, users, per in rows:
        tys = Counter(ty for v in per.values() for _, ty in v)
        print(f"{N}\t{n} casts\t{len(per)}/{users} files\t{decl}\t"
              + "; ".join(f"{t} x{c}" for t, c in tys.most_common()))
        if files_flag:
            for f, v in sorted(per.items()):
                print(f"    {f}: " + ", ".join(f"{ln}:{ty}" for ln, ty in v))
    print(f"# {len(rows)} pieces, {sum(r[0] for r in rows)} casts", file=sys.stderr)


if __name__ == "__main__":
    main(sys.argv[1:])
