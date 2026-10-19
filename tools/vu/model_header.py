#!/usr/bin/env python3
"""Print the header structure of a Kingdom Hearts Final Mix model or map file
extracted from the user's own disc (tools/shift/extract_kingdom.py).

  python3 -I tools/vu/model_header.py FILE [--kind mdls|mobj|bin|ard|amesh] [--at OFF]

Kinds (auto-detected when --kind is omitted; layouts in docs/structs.md,
"Model files (session 16, static)"):
  mdls   character/object model container (*.mdls), relocated by func_00155b70
  mobj   a chunk chain starting with "MOBJ"/"MENV"/"MMTN"/"TEXA"/"BONE"/"URSL"
         (func_00161a08 / func_001681b8)
  bin    map file <ww>00_<nn>.bin (func_001012e0); its entries 2 and 3 are
         renderer A mesh headers
  ard    area object set <ww><nn>.ard (func_00132790)
  amesh  one renderer A mesh header (8 bbox corners + 2 DMA tags, func_001089f8)
--at OFF parses the structure at byte offset OFF inside FILE.

Standalone (Python >= 3.10, stdlib only), read-only. Prints offsets, sizes,
counts, tags and decoded DMA tag types, not file contents in bulk. Output
derives from the user's files: never commit it.
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

TAGS = {b"MOBJ", b"MENV", b"MMTN", b"TEXA", b"BONE", b"URSL"}
DMA_ID = ["REFE", "CNT", "NEXT", "REF", "REFS", "CALL", "RET", "END"]


class Buf:
    def __init__(self, data: bytes):
        self.d = data

    def u32(self, o: int) -> int:
        return struct.unpack_from("<I", self.d, o)[0]

    def s32(self, o: int) -> int:
        return struct.unpack_from("<i", self.d, o)[0]

    def u16(self, o: int) -> int:
        return struct.unpack_from("<H", self.d, o)[0]

    def u8(self, o: int) -> int:
        return self.d[o]

    def f32(self, o: int) -> float:
        return struct.unpack_from("<f", self.d, o)[0]

    def ok(self, o: int, n: int = 4) -> bool:
        return 0 <= o and o + n <= len(self.d)


def dma_tag(b: Buf, o: int) -> str:
    w0, w1 = b.u32(o), b.u32(o + 4)
    qwc, tid = w0 & 0xFFFF, (w0 >> 28) & 7
    return f"{DMA_ID[tid]} qwc={qwc} addr=+0x{w1:X}"


def chunks(b: Buf, o: int):
    """func_001681b8: {u32 tag, u32 size, data[size]}, next at +size+8."""
    while b.ok(o, 8) and b.d[o:o + 4] in TAGS:
        tag, size = b.d[o:o + 4].decode(), b.u32(o + 4)
        yield o, tag, size
        o += size + 8


def show_mobj(b: Buf, h: int, ind: str = "") -> None:
    tag = b.d[h:h + 4].decode("latin-1")
    print(f"{ind}{tag} chunk at 0x{h:X}, size 0x{b.u32(h + 4):X}")
    if tag not in ("MOBJ", "MENV"):
        return
    names = {0x08: "texture records (16 B each)", 0x10: "pixel data", 0x18: "CLUT data (1024 B per texture)",
             0x20: "part table", 0x28: "alt part table", 0x30: "object list"}
    for k in range(0x08, 0x38, 8):
        print(f"{ind}  +0x{k:02X} off 0x{b.u32(h + k):X}  +0x{k + 4:02X} 0x{b.u32(h + k + 4):X}  {names[k]}")
    tb, ntex = h + b.u32(h + 0x08), b.u32(h + 0x0C) >> 4
    print(f"{ind}  textures: {ntex}")
    for j in range(min(ntex, 64)):
        r = tb + 16 * j
        if not b.ok(r, 16):
            break
        print(f"{ind}    tex {j}: qwc={b.u16(r)} tw={b.u8(r + 2)} th={b.u8(r + 3)} "
              f"w={b.u16(r + 4)} h={b.u16(r + 6)}")
    for name, k in (("part table", 0x20), ("alt part table", 0x28)):
        if k == 0x28 and b.u32(h + 0x2C) == 0:
            continue
        t = h + b.u32(h + k)
        if not b.ok(t, 16):
            continue
        nb, nparts = b.s32(t) & 0xFFFF, b.s32(t + 0xC)
        print(f"{ind}  {name} at 0x{t:X}: bones={nb} (u16 +2 = {b.u16(t + 2)}) "
              f"bone table +0x{b.u32(t + 4):X} x8 +0x{b.u32(t + 8):X} parts={nparts}")
        for i in range(min(max(nparts, 0), 128)):
            e = t + 0x10 + 16 * i
            if not b.ok(e, 16):
                break
            print(f"{ind}    part {i}: flags=0x{b.u8(e):02X} id={b.u8(e + 1)} g={b.u8(e + 2)} "
                  f"b3={b.u8(e + 3)} tex={b.u8(e + 4)} clut={b.s32(e + 8)} chain=+0x{b.u32(e + 12):X}")


def show_chain(b: Buf, o: int, ind: str = "") -> None:
    found = False
    for co, tag, size in chunks(b, o):
        found = True
        if tag in ("MOBJ", "MENV"):
            show_mobj(b, co, ind)
        else:
            print(f"{ind}{tag} chunk at 0x{co:X}, size 0x{size:X}")
    if not found:
        print(f"{ind}no model chunk at 0x{o:X}")


def show_mdls(b: Buf, o: int) -> None:
    offs = [b.u32(o + 4 * i) for i in range(7)]
    print(f"mdls container at 0x{o:X}: {offs[0]} sections, offsets " + " ".join(f"0x{x:X}" for x in offs[1:]))
    roles = {1: "model chunk chain (func_00162058)", 2: "ppp effect program (func_001763f0)",
             5: "attachment/hit table (func_0015c9f8)"}
    for i in range(1, 6):
        size = offs[i + 1] - offs[i]
        print(f"  section {i}: 0x{offs[i]:X} size 0x{max(size, 0):X}  {roles.get(i, '?')}")
    show_chain(b, o + offs[1], "  ")


def show_amesh(b: Buf, o: int, ind: str = "") -> None:
    print(f"{ind}renderer A mesh header at 0x{o:X}")
    xs = [[b.f32(o + 16 * i + 4 * k) for k in range(3)] for i in range(8)]
    lo = [min(p[k] for p in xs) for k in range(3)]
    hi = [max(p[k] for p in xs) for k in range(3)]
    print(f"{ind}  bbox corners 0-7 (+0x00..+0x7F): min ({lo[0]:.1f}, {lo[1]:.1f}, {lo[2]:.1f}) "
          f"max ({hi[0]:.1f}, {hi[1]:.1f}, {hi[2]:.1f})")
    for k in (0x80, 0x90):
        print(f"{ind}  +0x{k:02X} DMA tag: {dma_tag(b, o + k)} (addr relocated by +file base)")


def show_bin(b: Buf, o: int) -> None:
    ver = b.s32(o)
    print(f"map .bin at 0x{o:X}: version {ver}")
    roles = ["collision mesh A (func_00105288)", "texture/GS packet set (func_00106ed0)",
             "renderer A mesh 0 (func_00108cf8 slot 0)", "renderer A mesh 1 (func_00108cf8 slot 1)",
             "16-byte vector table D_002A3F48", "ppp effects (func_001763f0), ver>=6",
             "D_0029B414, ver>=6", "ppp effects (func_001763f0), ver>=8", "D_0029B41C, ver>=8",
             "collision mesh B (func_00105d88), ver>=10"]
    for i in range(10):
        off, size = b.u32(o + 0x10 + 8 * i), b.u32(o + 0x14 + 8 * i)
        print(f"  e[{i}] off 0x{off:X} size 0x{size:X}  {roles[i]}")
    for i in (2, 3):
        off = b.u32(o + 0x10 + 8 * i)
        if b.ok(o + off, 0xA0):
            show_amesh(b, o + off, "  ")


def show_ard(b: Buf, o: int) -> None:
    offs = [b.s32(o + 4 * i) for i in range(40)]
    print(f"area set at 0x{o:X}: off[0..39] " + " ".join(f"{x:X}" for x in offs))
    for n, role in ((1, "character models (func_00132678 each)"), (2, "props (func_00132718 each)")):
        if offs[n + 1] - offs[n] > 0:
            lst = o + offs[n]
            cnt = b.s32(lst)
            print(f"  section {n}: {cnt} {role}")
            for i in range(min(cnt, 64)):
                print(f"    [{i}] at 0x{lst + b.s32(lst + 4 + 4 * i):X}")
    if offs[7] - offs[6] > 0:
        nb = o + offs[6]
        print(f"  section 6 (32-byte file names): {(offs[7] - offs[6]) // 32} entries")
        for i in range((offs[7] - offs[6]) // 32):
            s = b.d[nb + 32 * i:nb + 32 * i + 32].split(b"\0")[0]
            print(f"    [{i}] {s.decode('latin-1')}")


def detect(b: Buf, o: int) -> str:
    if b.d[o:o + 4] in TAGS:
        return "mobj"
    w = [b.u32(o + 4 * i) for i in range(8)]
    if b.ok(o + w[1], 4) and b.d[o + w[1]:o + w[1] + 4] in TAGS:
        return "mdls"
    if 0 < w[0] <= 16 and all(b.ok(o + b.u32(o + 0x10 + 8 * i), 0) for i in range(10)):
        return "bin"
    return "ard"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("file", type=Path)
    ap.add_argument("--kind", choices=["mdls", "mobj", "bin", "ard", "amesh"])
    ap.add_argument("--at", type=lambda s: int(s, 0), default=0)
    a = ap.parse_args()
    b = Buf(a.file.read_bytes())
    kind = a.kind or detect(b, a.at)
    try:
        {"mdls": show_mdls, "mobj": show_chain, "bin": show_bin, "ard": show_ard,
         "amesh": show_amesh}[kind](b, a.at)
    except struct.error as e:
        print(f"truncated or not a {kind} file: {e}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
