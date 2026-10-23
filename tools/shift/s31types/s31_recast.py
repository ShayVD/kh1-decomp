#!/usr/bin/env python3
"""Cast a piece to its shared type instead of a file's alias of it (session 31).

  python3 -I tools/shift/s31types/s31_recast.py [--apply] FILE.c VIEW SHARED D_X [D_Y ..]

After s29_retype made VIEW `typedef SHARED VIEW;`, the casts `(VIEW *)&D_X`,
`(VIEW **)&D_X`, `(volatile VIEW *)&D_X`, `(VIEW *)D_X` ... of the given pieces
name SHARED instead (the same type, so the survey counts them as shared).  When
VIEW is then used nowhere but its own typedef, the typedef goes.  The result is
-S checked against HEAD (s27lib); --apply writes it when SAME.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402


def recast(t, view, shared, pieces):
    n = 0
    for D in pieces:
        pat = re.compile(r"\(\s*((?:const\s+|volatile\s+)*)" + view + r"(\s*\*[\s\*]*)\)(\s*&?\s*)" + D + r"\b")
        t, k = pat.subn(lambda m: "(" + m.group(1) + shared + m.group(2) + ")" + m.group(3) + D, t)
        n += k
    td = re.compile(r"^typedef\s+" + shared + r"\s+" + view + r"\s*;[ \t]*\n", re.M)
    rest = td.sub("", t)
    if td.search(t) and not re.search(r"\b" + view + r"\b", rest):
        t = rest
    return t, n


def main(argv):
    apply = "--apply" in argv
    argv = [a for a in argv if a != "--apply"]
    rel, view, shared, pieces = argv[0], argv[1], argv[2], argv[3:]
    src = (L.ROOT / rel).read_text()
    new, n = recast(src, view, shared, pieces)
    if new == src:
        print("no change")
        return 0
    a, da = L.compile_s(rel, new)
    h, _ = L.head_compile(rel)
    if a is None:
        print("NOCOMPILE", da[:5])
        return 1
    if not L.same_asm(a, h):
        print(f"CODE ({n} casts)")
        return 1
    print(f"SAME ({n} casts)")
    if apply:
        (L.ROOT / rel).write_text(new)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
