#!/usr/bin/env python3
"""New compiler warnings of the files that use a name, against HEAD (session 31).

  python3 -I tools/shift/s31types/s31_warndiff.py NAME|FILE.c ..

For every src/ .c file that mentions NAME (or each FILE.c given), compiles the
work tree's text and HEAD's (s27lib recipes) and prints the warnings only the
work tree has, by line.  A retype that keeps the code can still make gcc warn
(a pointer given to an s32 parameter, distinct pointer types compared).
"""
import re, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "s27types"))
import s27lib as L  # noqa: E402


def one(rel):
    a, da = L.compile_s(rel)
    h, dh = L.head_compile(rel)
    old = L.warnings(dh)
    return rel, [(ln, m) for ln, m in da if m not in old and "warning" in m]


def main(argv):
    rels = []
    for a in argv:
        if a.endswith(".c"):
            rels.append(a)
        else:
            rels += sorted(str(p.relative_to(L.ROOT)) for p in (L.ROOT / "src").rglob("*.c")
                           if re.search(r"\b" + a + r"\b", p.read_text())
                           and str(p.relative_to(L.ROOT)) in L.recipes())
    n = 0
    with ThreadPoolExecutor(L.JOBS) as ex:
        for rel, new in ex.map(one, sorted(set(rels))):
            for ln, m in new:
                print(f"{rel}:{ln}: {m}")
                n += 1
    print(f"# {n} new warnings", file=sys.stderr)


if __name__ == "__main__":
    main(sys.argv[1:])
