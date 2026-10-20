#!/usr/bin/env python3
"""Find data names that code or data uses as the base of another name (session 21).

  python3 -I tools/shift/addend_check.py [--link out/shift] [--out FILE]

A matched function can name a variable through its neighbour: func_00105288 reads
D_002A6278 as `((s32 *)&D_002A6274)[1]`, which assembles to %hi/%lo(D_002A6274+4).
Every static check sees a correct relocation against D_002A6274, so when the float
build moves D_002A6274 alone the load reads 4 bytes past its new place (session 21:
Sora walks through Agrabah's walls). This check reads the m0 link (ld -q keeps the
relocations) and, for every HI16/LO16 and R_MIPS_32 against a D_ name, works out the
addend; when the address lands outside [name, next name) both the base name and the
name at the address are printed, one per line, for the float build to keep in place."""
from __future__ import annotations

import argparse
import bisect
import struct
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
from elf32 import R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16, Elf  # noqa: E402

SHT_PROGBITS = 1

ROOT = TOOLS.parent


def sx16(v: int) -> int:
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--link", default=str(ROOT / "out/shift"))
    ap.add_argument("--out")
    args = ap.parse_args()
    elf = Elf.load(Path(args.link) / "kh1-shift.linked.elf")
    syms = elf.symbols()
    names = sorted({(s.value, s.name) for s in syms if s.name.startswith("D_") and s.shndx})
    addrs = [a for a, _n in names]
    keep: dict[str, str] = {}
    for sec in elf.sections:
        if sec.type != SHT_PROGBITS or not sec.addr:
            continue
        data = elf.section_bytes(sec)
        rels = elf.relocations(sec)
        last_hi: dict[int, int] = {}
        for off, typ, si in rels:
            if typ == R_MIPS_HI16:
                last_hi[si] = off
                continue
            s = syms[si]
            if not s.name.startswith("D_") or s.name == "D_BLOB" or typ not in (R_MIPS_LO16, R_MIPS_32):
                continue
            pos = off - sec.addr
            if not 0 <= pos <= len(data) - 4:
                continue
            w = struct.unpack_from("<I", data, pos)[0]
            if typ == R_MIPS_32:
                target = w
            else:
                # the paired HI16 holds the carry: target = %hi << 16 + sext(lo)
                hi = last_hi.get(si)
                if hi is None:
                    continue
                hw = struct.unpack_from("<I", data, hi - sec.addr)[0]
                target = ((hw & 0xFFFF) << 16) + sx16(w)
            target &= 0xFFFFFFFF
            i = bisect.bisect_right(addrs, s.value) - 1
            nxt = addrs[i + 1] if i + 1 < len(addrs) else 1 << 32
            if s.value <= target < nxt:
                continue
            j = bisect.bisect_right(addrs, target) - 1
            other = names[j][1] if j >= 0 else "?"
            why = f"{s.name}{target - s.value:+#x} at {off:#010x} is {other}"
            keep.setdefault(s.name, why)
            keep.setdefault(other, why)
    lines = [f"{n}\t# {why}" for n, why in sorted(keep.items())]
    print("\n".join(lines))
    if args.out:
        Path(args.out).write_text("".join(n + "\n" for n in sorted(keep)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
