#!/usr/bin/env python3
"""Symbolic asm export of every function the normal build does not place
(layout.tsv minus out/gen/placements.tsv, so run `make` first), one file per
function: shift/unmatched/func_XXXXXXXX.s. Only the shiftable build reads
shift/; the normal build and `make progress` only see src/, so these never
count as matched. Files of functions that are placed now are removed.

  python3 -I tools/shift/export_unmatched.py [--out shift/unmatched]
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import asm_export  # noqa: E402
import kh1tool as K  # noqa: E402

HEADER = ("/* {name}: not matched yet (C drafts, if any, in nonmatchings/). Original code as words with "
          "relocations (tools/asm_export.py --symbolic) for the shiftable build only: the normal build "
          "never reads shift/ (docs/shiftable-plan.md). Regenerate with tools/shift/export_unmatched.py. */")


def unmatched() -> list[K.Func]:
    if not K.PLACEMENTS.exists():
        sys.exit("error: out/gen/placements.tsv missing; run `make` first")
    placed = {a for a, *_ in K.load_placements()}
    return [f for f in K.load_layout() if f.addr not in placed]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", default=str(K.ROOT / "shift" / "unmatched"))
    a = ap.parse_args()
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    funcs = unmatched()
    want = {f"func_{f.addr:08x}.s" for f in funcs}
    for old in out.glob("func_*.s"):
        if old.name not in want:
            old.unlink()
            print(f"removed {old} (placed by the normal build now)")
    report: list[str] = []
    for f in funcs:
        name = f"func_{f.addr:08x}"
        (out / f"{name}.s").write_text(asm_export.export([name], HEADER.format(name=name), symbolic=True,
                                                         report=report))
    for r in report:
        print(f"note: {r}", file=sys.stderr)
    print(f"export_unmatched: {len(funcs)} functions, {sum(f.size for f in funcs)} bytes -> {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
