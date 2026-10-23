#!/usr/bin/env python3
"""-S check of every source that includes a header, directly or through other
include/ headers (session 30).

  python3 -I tools/shift/s30types/s30_hdrdiff.py HEADER [HEADER ...]

HEADER is a path under include/ (data/pieces/D_002A6238.h).  Each includer's
work-tree -S is compared with HEAD's (s27lib, label-canonical); prints SAME /
CODE / NOCOMPILE per file and exits 1 unless all are SAME.  A quick check before
`make` when a shared header changes (make stays the final check).
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402

INC = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)


def includers(hdrs):
    """the include/ headers that pull in any of hdrs (closure), then the .c files"""
    inc = L.ROOT / "include"
    texts = {str(p.relative_to(inc)): p.read_text(errors="replace") for p in inc.rglob("*.h")}
    want = set(hdrs)
    while True:
        more = {h for h, t in texts.items() if h not in want and want & set(INC.findall(t))}
        if not more:
            break
        want |= more
    out = []
    for p in sorted((L.ROOT / "src").rglob("*.c")):
        if want & set(INC.findall(p.read_text(errors="replace"))):
            out.append(str(p.relative_to(L.ROOT)))
    return out


def main(argv):
    if not argv:
        print(__doc__)
        return 2
    rc = 0
    rec = L.recipes()
    for rel in includers(argv):
        if rel not in rec:
            continue
        a, d = L.compile_s(rel)
        h, _ = L.head_compile(rel)
        st = "NOCOMPILE" if a is None else ("SAME" if L.same_asm(a, h) else "CODE")
        rc |= st != "SAME"
        print(f"{st}\t{rel}")
    return rc


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
