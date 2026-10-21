#!/usr/bin/env python3
"""Drop basic-type casts of a piece's name that its users no longer need (session 27).

  python3 -I tools/shift/s27types/s27_trim.py [--apply] D_X ...

A cast `((T)D_X)`, `((T *)&D_X)` or `(*(T *)&D_X)` with T a basic type (void,
s32, u8 *, M2C_UNK *, ...) is taken out when the file's -S stays the same as HEAD
and no new warning appears: first all of a file's candidates at once, else one by
one (each kept out only if the file still matches).  Without --apply nothing is
written.
"""
import re, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import s27lib as L  # noqa: E402
import s27_fold as F  # noqa: E402

BT = r"(?:volatile\s+|const\s+)*(?:unsigned\s+)?(?:void|s8|u8|s16|u16|s32|u32|s64|u64|f32|int|char|M2C_UNK)"


def cands(text, N):
    pats = [
        (re.compile(r"\(\(\s*" + BT + r"\s*\**\s*(?:volatile\s*)?\)\s*" + N + r"\s*\)"), N),
        (re.compile(r"\(\*\(\s*" + BT + r"\s*\*+\s*\)\s*&\s*" + N + r"\s*\)"), N),
        (re.compile(r"\(\(\s*" + BT + r"\s*\*+\s*\)\s*&\s*" + N + r"\s*\)"), "&" + N),
    ]
    out = []
    for p, rep in pats:
        for m in p.finditer(text):
            out.append((m.start(), m.end(), rep))
    return sorted(out)


def apply_some(text, cs):
    for a, b, rep in sorted(cs, reverse=True):
        text = text[:a] + rep + text[b:]
    return text


def ok(rel, text, base):
    asm, d = L.compile_s(rel, text)
    return asm is not None and L.same_asm(asm, base[0]) and not (L.warnings(d) - L.warnings(base[1]))


def trim_file(rel, N):
    text = (L.ROOT / rel).read_text()
    cs = cands(text, N)
    if not cs:
        return rel, text, 0, 0
    base = L.head_compile(rel)
    cur = (L.compile_s(rel, text))
    if not (cur[0] is not None and L.same_asm(cur[0], base[0])):
        return rel, text, 0, len(cs)  # not SAME now: leave it
    base = (base[0], cur[1])  # warnings as they are now
    if ok(rel, apply_some(text, cs), base):
        return rel, apply_some(text, cs), len(cs), len(cs)
    keep_out = []
    for c in cs:
        if ok(rel, apply_some(text, keep_out + [c]), base):
            keep_out.append(c)
    return rel, apply_some(text, keep_out), len(keep_out), len(cs)


def main(argv):
    apply = "--apply" in argv
    names = [a for a in argv if a.startswith("D_")]
    L.head_tree()
    total = [0, 0]
    for N in names:
        users = F.users_of(N)
        with ThreadPoolExecutor(3) as ex:
            for rel, t, k, n in ex.map(lambda r: trim_file(r, N), sorted(users)):
                if n:
                    print(f"{N} {rel}: {k} of {n} casts out", flush=True)
                total[0] += k; total[1] += n
                if apply and k:
                    (L.ROOT / rel).write_text(t)
    print(f"# {total[0]} of {total[1]} casts out")


if __name__ == "__main__":
    main(sys.argv[1:])
