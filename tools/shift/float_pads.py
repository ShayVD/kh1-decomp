#!/usr/bin/env python3
"""Find writes past the end of floated variables (phase 4, session 22).

  python3 -I tools/shift/float_pads.py STATE.p2s [--out-dir out/shift/m12-float] [--pad 0x40] [--words]

A float build made with SHIFT_FLOAT_PAD=N (shift_ld --float-pad) puts N bytes after each
floated data variable (the word FLOAT_PAD_WORD repeated) and after each floated bss run
(zero, cleared by crt0), each starting at a symbol __fpad_<name>. Run the build in PCSX2
until it misbehaves, save a state to a file and pass it here: every pad whose bytes changed
is printed with the variable before it, so the overrunning object is named without
bisection. A pad that reads past the end (no write) does not show up here.

The state is read like float_holes.py does. Prints addresses, names and counts; --words also
prints the changed words of each pad (runtime values, for a local look; do not commit them)."""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/shift"))
from elf32 import Elf  # noqa: E402
from float_holes import ee_memory  # noqa: E402
from shift_ld import FLOAT_PAD_WORD  # noqa: E402


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("state", type=Path)
    ap.add_argument("--out-dir", type=Path, default=ROOT / "out/shift/m12-float")
    ap.add_argument("--pad", type=lambda x: int(x, 0), default=0x40, help="SHIFT_FLOAT_PAD of the build")
    ap.add_argument("--bss-pad", type=lambda x: int(x, 0), default=None, help="SHIFT_FLOAT_BSS_PAD (default --pad)")
    ap.add_argument("--words", action="store_true", help="print the changed words")
    a = ap.parse_args()
    syms = {s.name: s.value for s in Elf.load(a.out_dir / "kh1-shift.linked.elf").symbols()}
    bss0 = syms.get("__float_bss_start", 1 << 32)
    pads = sorted((v, k[len("__fpad_"):]) for k, v in syms.items() if k.startswith("__fpad_"))
    if not pads:
        sys.exit(f"error: no __fpad_ symbols in {a.out_dir}: build with SHIFT_FLOAT_PAD=N")
    ee = ee_memory(a.state)
    bpad = a.pad if a.bss_pad is None else a.bss_pad
    fill = struct.pack("<I", FLOAT_PAD_WORD) * (a.pad // 4)
    hit = 0
    for addr, name in pads:
        n = bpad if addr >= bss0 else a.pad
        want = bytes(n) if addr >= bss0 else fill
        got = ee[addr & 0x1FFFFFF:(addr & 0x1FFFFFF) + n]
        diff = [i for i in range(n) if got[i] != want[i]]
        if not diff:
            continue
        hit += 1
        kind = "bss" if addr >= bss0 else "data"
        print(f"{name}\t{kind}\tpad 0x{addr:08x}\t{len(diff)} bytes changed at +0x{diff[0]:x}..+0x{diff[-1]:x}"
              f"\tvar 0x{syms.get(name, 0):08x}")
        if a.words:
            for i in range(diff[0] & ~3, diff[-1] + 1, 4):
                print(f"\t+0x{i:02x}: {struct.unpack_from('<I', got, i)[0]:08x}")
    print(f"# {hit} of {len(pads)} pads changed ({sum(1 for p, _ in pads if p < bss0)} data, "
          f"{sum(1 for p, _ in pads if p >= bss0)} bss)", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
