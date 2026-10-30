#!/usr/bin/env python3
"""tools/ovl/gcsebucket.py (wwm2, session 141 round 55): show gcse's expression hash table for a draft.

  python3 tools/ovl/gcsebucket.py draft.c [draft2.c ...] [--all] [--grep=REGEX]

Compiles each hand.py-style draft (include/ovl.h put in front; a NAME.<mode>.c draft gets that
kh1.toml mode's cflags) with ee-gcc -dG and prints, from the dump of gcse's first pass, the
expression table's bucket count, the max_cuid range that bucket count implies, and the
index and bucket ("hash value") of each expression that names a symbol (--all: every
expression; --grep: those whose RTL matches REGEX).

Why it matters (docs/overlays.md "gcse's hash table size as a register lever"): gcse
(gcc 2.96 PRE) gives each redundant expression its reaching pseudo in pre_delete, which
walks the table bucket by bucket. So two %hi (or constant) pseudos that differ only in
which s register they get usually swap when their buckets swap. The bucket is the
expression's content hash mod the table size, and the size is max_cuid / 2 | 1, so it moves
with the number of insns the function has at gcse time. Two drafts that print the same
order here get the same pseudo order; change the insn count (see the docs entry for how
to do it in plain C) until the order flips.
"""
from __future__ import annotations

import re
import subprocess
import sys
import tempfile
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
GCC = ROOT / "tools" / "toolchain" / "ee-gcc2.96" / "bin" / "ee-gcc"


def mode_cflags(draft: Path) -> list[str]:
    mode = draft.suffixes[-2][1:] if len(draft.suffixes) > 1 else ""
    cfg = tomllib.loads((ROOT / "kh1.toml").read_text())
    if mode:
        for o in cfg["toolchain"].get("override", []):
            if o.get("mode") == mode:
                return o["cflags"].split() + o.get("ccflags", "").split()
        sys.exit(f"error: no kh1.toml mode {mode!r} for {draft}")
    return cfg["toolchain"]["cflags"].split()


def table(draft: Path) -> tuple[int, int, list[tuple[int, int, str]]]:
    with tempfile.TemporaryDirectory() as d:
        src = Path(d) / "d.c"
        src.write_text('#include "ovl.h"\n' + draft.read_text())
        r = subprocess.run([str(GCC), "-c", "-x", "c", *mode_cflags(draft), f"-I{ROOT / 'include'}", "-dG", "d.c"],
                           cwd=d, capture_output=True, text=True)
        dumps = sorted(Path(d).glob("d.c.*.gcse"))
        if r.returncode or not dumps:
            sys.exit(f"error: {draft} does not compile:\n{r.stderr[-2000:]}")
        text = dumps[0].read_text()
    m = re.search(r"Expression hash table \((\d+) buckets, (\d+) entries\)\n(.*?)\n\n", text, re.S)
    if not m:
        sys.exit(f"error: no expression hash table in the gcse dump of {draft}")
    exprs = []
    for e in re.finditer(r"Index (\d+) \(hash value (\d+)\)\n((?:  .*\n?)+)", m.group(3) + "\n"):
        exprs.append((int(e.group(1)), int(e.group(2)), " ".join(e.group(3).split())))
    return int(m.group(1)), int(m.group(2)), exprs


def main() -> int:
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    show_all = "--all" in sys.argv
    pat = next((re.compile(a.split("=", 1)[1]) for a in sys.argv[1:] if a.startswith("--grep=")), None)
    if not args:
        sys.exit(__doc__)
    for a in args:
        size, n, exprs = table(Path(a))
        lo = (size - 1) * 2
        print(f"{a}: {size} buckets, {n} expressions, max_cuid {lo}..{lo + 3}")
        for idx, h, rtl in sorted(exprs, key=lambda x: (x[1], x[0])):
            if show_all or (pat.search(rtl) if pat else "symbol_ref" in rtl):
                print(f"  bucket {h:3}  index {idx:3}  {rtl}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
