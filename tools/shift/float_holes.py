#!/usr/bin/env python3
"""Find stale writes into the holes floated variables leave (phase 4, session 18).

  python3 -I tools/shift/float_holes.py STATE.p2s [--out-dir out/shift/m12-float]

A SHIFT_FLOAT build leaves each floated variable's old place as a zero gap (crt0
clears it with the rest of .bss). Code that still reaches the old place, through a
base no relocation names (an array indexed past its declared end into the next
name, a field reached from another object), writes there. Run the build in PCSX2
until it misbehaves, save a state to a file (System > Save State > Save To File),
and pass it here: every hole with non-zero bytes is printed, with the bytes count
at the variable's new place (usually 0: the writes went to the old one).

The state is a zip of zstd members; eeMemory.bin is read with the `zstd` tool.
Prints addresses, names and counts only, never memory contents."""
from __future__ import annotations

import argparse
import re
import struct
import subprocess
import sys
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/shift"))
from elf32 import Elf  # noqa: E402
from reach_check import BSS_START, pieces_from_ld  # noqa: E402


def ee_memory(p2s: Path) -> bytes:
    """PCSX2's zip members use zstd (method 93), which zipfile cannot read: copy the raw member."""
    z = zipfile.ZipFile(p2s)
    info = z.getinfo("eeMemory.bin")
    with open(p2s, "rb") as f:
        f.seek(info.header_offset)
        h = f.read(30)
        n, e = struct.unpack("<HH", h[26:30])
        f.seek(info.header_offset + 30 + n + e)
        raw = f.read(info.compress_size)
    if info.compress_type == 0:
        return raw
    return subprocess.run(["zstd", "-d", "-c"], input=raw, capture_output=True, check=True).stdout


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("state", type=Path)
    ap.add_argument("--out-dir", type=Path, default=ROOT / "out/shift/m12-float")
    a = ap.parse_args()
    sizes = {}
    for ln in (ROOT / "out/gen/data.tsv").read_text().splitlines()[1:]:
        f = ln.split("\t")
        sizes[f[1]] = int(f[3], 16)
    pcs = pieces_from_ld(a.out_dir / "kh1-shift.ld", sizes)
    syms = {s.name: s.value for s in Elf.load(a.out_dir / "kh1-shift.linked.elf").symbols()}
    d_bss, d_blob = syms["D_BSS"] - BSS_START, syms["D_BLOB"] - 0x00272C70
    ee = ee_memory(a.state)
    n = 0
    for start, end, run, name in pcs:
        d = d_bss if start >= BSS_START else d_blob
        hole = ee[start + d:end + d]
        nz = [i for i, b in enumerate(hole) if b]
        if not nz:
            continue
        n += 1
        new = syms.get(name)
        at_new = sum(1 for b in ee[new:new + end - start] if b) if new else -1
        print(f"{name}\tsize 0x{end - start:x}\t{run if run != name else ''}\thole: {len(nz)} non-zero bytes "
              f"at +0x{nz[0]:x}..+0x{nz[-1]:x}\tnew place 0x{new:08x}: {at_new} non-zero")
    print(f"# {n} of {len(pcs)} floated variables have writes in their old place", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
