#!/usr/bin/env python3
"""Find C-defined variables that sit inside another declared object (phase 4).

  python3 -I tools/shift/cover_check.py [-j N] [--out FILE]

A name like D_005759A6 can be both a variable of its own and a field of a larger
object another file declares (`extern Cam D_00575940;`, sizeof 0x67, covers
0x575940..0x5759A6). Defining it in C is fine for `make`, but SHIFT_FLOAT moves
it away from the struct and the code that reads the field through the struct no
longer sees it (session 17: this hung the float build at boot).

For every C file outside src/sdk/, every file-scope `extern` of a D_ name with a
complete type gets its size from the compiler (one probe compile per file, like
define_vars.py). Every variable of out/gen/data.tsv that lies strictly inside
such an object is printed with the object, its size and the declaring file.
These must stay at their place: `--out` writes their names, one per line, and
the SHIFT_FLOAT build passes the file to shift_ld.py (--float-skip-file), so they
stay at their D_BSS / blob offset while the rest floats."""
from __future__ import annotations

import argparse
import re
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/shift"))
from define_vars import parse_extern, probe_sizes  # noqa: E402

NAME = re.compile(r"\bD_([0-9A-F]{8})\b")


def file_objects(src: Path):
    exprs = {}
    for ln in src.read_text(errors="replace").splitlines():
        if not ln.startswith("extern"):
            continue
        for m in NAME.finditer(ln):
            n = m.group(0)
            pe = parse_extern(ln, n)
            if not pe:
                continue
            d = pe[1][pe[2]]
            if re.search(r"\[\s*\]", d) or "(" in d:
                continue
            exprs[n] = n
    if not exprs:
        return []
    try:
        sizes = probe_sizes(src, exprs)
    except RuntimeError:
        return []
    return [(int(n[2:], 16), sz, n, str(src.relative_to(ROOT))) for n, sz in sizes.items() if sz]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("-j", type=int, default=8)
    ap.add_argument("--out", help="write the covered names here (shift_ld.py --float-skip-file)")
    a = ap.parse_args()
    files = sorted(p for p in (ROOT / "src").rglob("*.c") if "sdk" not in p.relative_to(ROOT / "src").parts[:1])
    with ThreadPoolExecutor(a.j) as ex:
        objs = [o for r in ex.map(file_objects, files) for o in r]
    defined = []
    for ln in (ROOT / "out/gen/data.tsv").read_text().splitlines()[1:]:
        f = ln.split("\t")
        defined.append((int(f[0], 16), f[1], int(f[3], 16), f[2]))
    hits = []
    for addr, name, size, obj in sorted(defined):
        for base, sz, oname, ofile in objs:
            if base < addr < base + sz:
                print(f"{name}\t{size:#x}\tinside {oname} (sizeof {sz:#x}, {ofile})\t{obj}")
                hits.append(name)
                break
    # The name just below must have a known size too: one only asm names, or that every
    # C file declares as `T D[]`, may be a larger object reaching into this variable.
    sized = {n for _b, _s, n, _f in objs} | {n for _a, n, _s, _o in defined}
    anchors = sorted((int(l.split("\t")[0], 16), l.split("\t")[1])
                     for l in (ROOT / "out/shift/data_owners.tsv").read_text().splitlines()[1:])
    addrs = [x[0] for x in anchors]
    import bisect
    for addr, name, size, obj in sorted(defined):
        if name in hits:
            continue
        i = bisect.bisect_left(addrs, addr) - 1
        if i >= 0 and anchors[i][1] not in sized:
            print(f"{name}\t{size:#x}\tafter {anchors[i][1]}, whose size no C declaration gives\t{obj}")
            hits.append(name)
    if a.out:
        Path(a.out).write_text("".join(n + "\n" for n in hits))
    print(f"# {len(defined)} C-defined variables, {len(objs)} declared objects, {len(hits)} inside another",
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
