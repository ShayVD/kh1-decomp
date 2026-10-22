#!/usr/bin/env python3
"""Drop casts of a pointer piece's value (or its elements) that C does not need (session 28).

  python3 -I tools/shift/s28types/s28_trim.py [--apply] D_X ...

For a piece declared `void *D_X[n]` (or another pointer array), session 26 casts gave
users their own pointer type back: `((T *)D_X[i])` for a `T *D_X[]` user and
`(*(T **)&D_X)` for a scalar `T *D_X` user.  A `void *` element converts to any
object pointer by itself, so where the context does not need the type (an
assignment, a comparison, a prototyped argument) the cast can go:
`((T *)D_X[i])` -> `D_X[i]`, `(*(T **)&D_X)` -> `D_X[0]` (or `D_X` for a scalar pointer
piece), and `((T *)D_X)` not followed by `->` or `[` -> `D_X`.  Each removal is kept only
when the file's -S stays the same as HEAD and no new warning appears (s27_trim's
check: first all of a file's candidates, else one by one).
"""
import re, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402
import s27_fold as F  # noqa: E402
import s27_trim as T  # noqa: E402
import s27_ctext as C  # noqa: E402

TY = r"(?:volatile\s+|const\s+)*\w+\s*"


def cands(text, N):
    ct = C.strip_comments(text)
    out = []
    # ((T *)N[expr])
    for m in re.finditer(r"\(\(\s*" + TY + r"\*\s*\)\s*" + N + r"\s*\[", ct):
        try:
            e = C.match_brace(ct, m.end() - 1, "[", "]")
        except ValueError:
            continue
        k = e
        while k < len(ct) and ct[k] in " \t":
            k += 1
        if k < len(ct) and ct[k] == ")":
            inner = ct[ct.index(N, m.start()):e]
            out.append((m.start(), k + 1, inner))
    # (*(T **)&N)
    arr = is_array(N)
    for m in re.finditer(r"\(\s*\*\s*\(\s*" + TY + r"\*\s*\*\s*\)\s*&\s*" + N + r"\s*\)", ct):
        out.append((m.start(), m.end(), N + "[0]" if arr else N))
    # ((T *)N) of a pointer piece where the value is only compared or passed on (not -> or [])
    if not arr:
        for m in re.finditer(r"\(\(\s*" + TY + r"\*\s*\)\s*" + N + r"\s*\)(?!\s*(?:->|\[))", ct):
            out.append((m.start(), m.end(), N))
    return sorted(set(out))


def is_array(N):
    h = L.ROOT / f"include/data/pieces/{N}.h"
    if not h.exists():
        return True
    m = re.search(r"^extern [^\n]*\b" + N + r"\b\s*(\[)?", h.read_text(), re.M)
    return bool(m and m.group(1))


def trim_file(rel, N):
    text = (L.ROOT / rel).read_text()
    cs = cands(text, N)
    if not cs:
        return rel, text, 0, 0
    base = L.head_compile(rel)
    cur = L.compile_s(rel, text)
    if not (cur[0] is not None and L.same_asm(cur[0], base[0])):
        return rel, text, 0, len(cs)
    base = (base[0], cur[1])
    if T.ok(rel, T.apply_some(text, cs), base):
        return rel, T.apply_some(text, cs), len(cs), len(cs)
    keep_out = []
    for c in cs:
        if T.ok(rel, T.apply_some(text, keep_out + [c]), base):
            keep_out.append(c)
    return rel, T.apply_some(text, keep_out), len(keep_out), len(cs)


def main(argv):
    apply = "--apply" in argv
    names = [a for a in argv if a.startswith("D_")]
    L.head_tree()
    total = [0, 0]
    for N in names:
        users = F.users_of(N)
        with ThreadPoolExecutor(L.JOBS) as ex:
            for rel, t, k, n in ex.map(lambda r: trim_file(r, N), sorted(users)):
                if n:
                    print(f"{N} {rel}: {k} of {n} casts out", flush=True)
                total[0] += k; total[1] += n
                if apply and k:
                    (L.ROOT / rel).write_text(t)
    print(f"# {total[0]} of {total[1]} casts out")


if __name__ == "__main__":
    main(sys.argv[1:])
