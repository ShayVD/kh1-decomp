#!/usr/bin/env python3
"""Print the data names that split a pointed-at object off the middle (session 22).

  python3 -I tools/shift/split_check.py

The data pieces in src/data/*.s are cut at every name a function or table uses, so one object
of the original (a GIF packet, a record) can be two or more pieces. When a .word in a piece
points at one of them and the next piece starts at an address that is not a multiple of 16,
the two are most likely one object: a DMA tag or a record table points at the head, and the
reader walks past its end into the next piece. Floating either side leaves the reader with the
wrong bytes. Prints both names of every such pair (one per line); the float build keeps them.

Found in PCSX2 (session 22): D_0048BFD0 (0x8) + D_0048BFD8 (0x88), a record the object tables
point at (Agrabah's alley sky, a hang loading save 06); and GIF packets whose colour register
C writes after the packet's head: with D_002A6178 and D_002A6658 floated (heads D_002A6120 and
D_002A65D0, which DMA tags point at), the DMA sends the old colour and the title is never drawn
(data budget 0x6000). D_002B6668 and D_002BC918 have the same shape."""
from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PIECE = re.compile(r"\s*PIECE(?:_BEGIN)?\s+(D_([0-9A-F]{8})),\s*(0x[0-9a-f]+)")
WORD = re.compile(r"\.word\s+(D_[0-9A-F]{8})\b")


def main() -> None:
    pointed: set[str] = set()
    runs: list[list[tuple[str, int, int]]] = []
    for p in sorted((ROOT / "src/data").glob("*.s")):
        run = []
        for ln in p.read_text().splitlines():
            m = PIECE.match(ln)
            if m:
                run.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
            pointed.update(WORD.findall(ln))
        runs.append(run)
    out: set[str] = set()
    for run in runs:
        for (q, qa, qs), (n, na, _) in zip(run, run[1:]):
            if qa + qs == na and na % 16 and (q in pointed or n in pointed):
                out |= {q, n}
    print("\n".join(sorted(out)))


if __name__ == "__main__":
    main()
