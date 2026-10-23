#!/usr/bin/env python3
"""-S diff of a candidate text of a source file against HEAD (session 29).

  python3 -I tools/shift/s29types/s29_asmdiff.py FILE.c [CANDIDATE.c]

CANDIDATE defaults to the work tree's FILE.c.  Prints a unified diff of the
label-canonical asm (s27lib), or SAME.
"""
import difflib, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402


def main(argv):
    rel = argv[0]
    text = Path(argv[1]).read_text() if len(argv) > 1 else None
    a, da = L.compile_s(rel, text)
    h, dh = L.head_compile(rel)
    if a is None:
        print("NOCOMPILE", da[:5])
        return 1
    if L.same_asm(a, h):
        print("SAME")
        return 0
    sys.stdout.writelines(difflib.unified_diff(L.canon_labels(h).splitlines(True),
                                               L.canon_labels(a).splitlines(True), "head", "new", n=2))
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
