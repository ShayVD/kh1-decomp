#!/usr/bin/env python3
"""Undo a session 27 fold of a pointer piece, back to cast form, so it can be folded again (session 27).

  python3 -I tools/shift/s27types/s27_unfold.py D_X [REF]

REF (default a5c8821, the base of session 27) gives the piece header to go back to.
Each user that names the header's struct types gets local copies of them (`<T>_v`,
placed where the piece header is included), its type names are renamed to the
copies, and each plain use of D_X is cast to the root copy (`((S_v *)D_X)`).
The -S check (s27_check.py) must then be SAME; the fold can run again.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import s27lib as L  # noqa: E402
import s27_ctext as C  # noqa: E402
import s27_fold as F  # noqa: E402


def main(argv):
    N = argv[0]
    ref = argv[1] if len(argv) > 1 else "a5c8821"
    hp = L.ROOT / f"include/data/pieces/{N}.h"
    cur = hp.read_text()
    old = L.git("show", f"{ref}:include/data/pieces/{N}.h")
    m = re.search(r"^extern\s+(\w+)\s*\*\s*" + N + r"\s*;", cur, re.M)
    if not m:
        print("not a folded pointer piece"); return 1
    root = m.group(1)
    ct = C.strip_comments(cur)
    defs = []
    for dm in re.finditer(r"typedef struct \{.*?\n\} (\w+);", cur, re.S):
        defs.append((dm.group(1), dm.group(0)))
    names = [n for n, _ in defs]
    ren = {n: n + "_v" for n in names}

    def rn(t):
        return re.sub(r"\b(" + "|".join(map(re.escape, names)) + r")\b", lambda m: ren[m.group(1)], t)
    local = "\n".join(rn(d) for _, d in defs)
    inc = f'#include "data/pieces/{N}.h"'
    for rel, t in F.users_of(N).items():
        if not re.search(r"\b(" + "|".join(names) + r")\b", t) and not re.search(N + r"\s*->", t):
            continue
        t = rn(t)
        # plain uses of N (not already cast) -> cast to the root copy
        ctt = C.strip_comments(t)
        pos = []
        for mm in re.finditer(r"\b" + N + r"\b", ctt):
            pre = ctt[:mm.start()].rstrip()
            addr = pre.endswith("&") and not pre.endswith("&&")
            castp = pre.endswith(")") and re.search(r"\(\s*[\w\s]+\*+\s*\)$", pre)
            if addr or castp or re.search(r"#\s*include", ctt[ctt.rfind("\n", 0, mm.start()):mm.start()]):
                continue
            post = ctt[mm.end():].lstrip()
            if post.startswith("=") and not post.startswith("=="):
                continue
            pos.append(mm.start())
        for p in reversed(pos):
            t = t[:p] + f"(({root}_v *){N})" + t[p + len(N):]
        i = t.find(inc)
        e = t.find("\n", i)
        t = t[:e + 1] + local + "\n" + t[e + 1:]
        (L.ROOT / rel).write_text(t)
        print("unfolded", rel)
    hp.write_text(old)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
