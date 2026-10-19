#!/usr/bin/env python3
"""Walk a static VIF1/VIF0 DMA chain in the user's SLPS_251.98 and print its
DMA tags and VIF commands (STCYCL, UNPACK layout, MPG, MSCAL/MSCNT, BASE,
OFFSET, ITOP, DIRECT...), one per line.

  python3 -I tools/vu/vif_chain.py [--elf SLPS_251.98] [--one] ADDR [ADDR ...]

  python3 -I tools/vu/vif_chain.py --file MODEL --rel BASE [--one] OFF [OFF ...]

--file walks a chain inside a model or map file extracted from the user's disc
(tools/shift/extract_kingdom.py): OFF is a file offset, and the address word of
each REF/NEXT/CALL tag is taken relative to BASE (the game adds the address of
the mesh header it relocates, docs/structs.md "Model files"). --stream decodes
OFF as bare VIF codes (no DMA tags) up to --end. Renderer B mesh chains
(the command stream inside the UNPACK data) are decoded by rb_stream.py.
--one decodes only the tag at ADDR (for REF fragments the game splices
into bigger chains, e.g. 00486300). ADDR is the address of the first DMA tag (what the game writes to D1_TADR
or passes to sceDmaSend, e.g. 0048c630, 0048c770, 00272cf0, 00272e20).
Source-chain rules: CNT/NEXT/END/CALL/RET carry their data after the tag,
REF/REFS/REFE point at it; the tag's upper 64 bits always reach the VIF as
two VIF codes (that is where dvp-as puts the MPG code of a program).

Standalone (Python >= 3.10, stdlib only). Prints addresses, tag types and
decoded VIF commands only, never data words. Tags whose target lies in the
code range are placeholders the game patches at run time; they are listed
and not followed. Output is derived from the user's ELF: do not commit it.
See docs/renderer-spec.md.
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
CODE_END = 0x00272C70
TAGS = ["REFE", "CNT", "NEXT", "REF", "REFS", "CALL", "RET", "END"]
UNPACK = {0: "S-32", 1: "S-16", 2: "S-8", 4: "V2-32", 5: "V2-16", 6: "V2-8", 8: "V3-32",
          9: "V3-16", 10: "V3-8", 12: "V4-32", 13: "V4-16", 14: "V4-8", 15: "V4-5"}
SIMPLE = {0x10: "FLUSHE", 0x11: "FLUSH", 0x13: "FLUSHA"}


class Image:
    def __init__(self, path: Path):
        d = path.read_bytes()
        if d[:4] != b"\x7fELF":
            sys.exit(f"{path}: not an ELF")
        phoff, = struct.unpack_from("<I", d, 0x1C)
        phentsize, phnum = struct.unpack_from("<HH", d, 0x2A)
        self.d, self.segs = d, []
        for i in range(phnum):
            t, off, va, _pa, fs, _ms = struct.unpack_from("<6I", d, phoff + i * phentsize)
            if t == 1:
                self.segs.append((va, off, fs))

    def ok(self, a: int) -> bool:
        return any(v <= a < v + f for v, _o, f in self.segs)

    def w(self, a: int) -> int:
        for v, o, f in self.segs:
            if v <= a < v + f:
                return struct.unpack_from("<I", self.d, o + a - v)[0]
        raise KeyError(hex(a))


class FlatImage(Image):
    """A model/map file: offset 0 = address 0; no code range."""

    def __init__(self, path: Path):  # noqa: super().__init__ reads an ELF
        self.d = path.read_bytes()
        self.segs = [(0, 0, len(self.d))]


class Vif:
    def __init__(self):
        self.cl = self.wl = 1

    def stream(self, img: Image, a: int, end: int, out: list[str]) -> None:
        """Decode VIF codes in [a, end)."""
        while a < end and img.ok(a):
            c = img.w(a)
            cmd, imm, num = c >> 24 & 0x7F, c & 0xFFFF, c >> 16 & 0xFF
            irq = " [i]" if c >> 31 else ""
            at, a = a, a + 4
            if cmd == 0:
                continue
            if cmd == 1:
                self.cl, self.wl = imm & 0xFF, imm >> 8
                s = f"STCYCL cl={self.cl} wl={self.wl}"
            elif cmd in (2, 3, 4):
                s = f"{['', '', 'OFFSET', 'BASE', 'ITOP'][cmd]} {imm & 0x3FF}"
            elif cmd == 5:
                s = f"STMOD {imm & 3}"
            elif cmd == 6:
                s = f"MSKPATH3 {imm >> 15 & 1}"
            elif cmd == 7:
                s = f"MARK {imm:#x}"
            elif cmd in SIMPLE:
                s = SIMPLE[cmd]
            elif cmd in (0x14, 0x15):
                s = f"{'MSCAL' if cmd == 0x14 else 'MSCALF'} @{imm:#x}"
            elif cmd == 0x17:
                s = "MSCNT"
            elif cmd == 0x20:
                s, a = "STMASK", a + 4
            elif cmd in (0x30, 0x31):
                s, a = ("STROW" if cmd == 0x30 else "STCOL"), a + 16
            elif cmd == 0x4A:
                n = num or 256
                s, a = f"MPG {n} instr -> micro @{imm:#x}", a + n * 8
            elif cmd in (0x50, 0x51):
                n = imm or 0x10000
                s, a = f"{'DIRECT' if cmd == 0x50 else 'DIRECTHL'} {n} qw (GIF PATH2)", a + n * 16
            elif cmd >= 0x60:
                vnvl, n = cmd & 0xF, num or 256
                vn, vl = vnvl >> 2, vnvl & 3
                bits = 16 if vnvl == 15 else [32, 16, 8][vl] * (vn + 1)
                cl, wl = self.cl, self.wl
                elems = n if wl <= cl else cl * (n // wl) + min(n % wl, cl)
                flags = (" masked" if cmd & 0x10 else "") + (" usn" if imm & 0x4000 else "") + \
                        (" +TOPS" if imm & 0x8000 else "")
                s = f"UNPACK {UNPACK.get(vnvl, '?')} num={n} -> vu @{imm & 0x3FF}{flags} (cl={cl} wl={wl})"
                a += (elems * bits + 31) // 32 * 4
            else:
                s = f"unknown VIF code {cmd:#x}"
            out.append(f"{at:08x}  {s}{irq}")


def walk(img: Image, t: int, max_tags: int = 256, rel: int | None = None) -> None:
    """rel: address words are offsets from rel (a file walked with --file)."""
    code_end = CODE_END if rel is None else -1
    vif, stack = Vif(), []
    for _ in range(max_tags):
        lo, hi = img.w(t), img.w(t + 4)
        qwc, tid, addr = lo & 0xFFFF, lo >> 28 & 7, hi & 0x7FFFFFF0
        if rel is not None and tid in (2, 3, 4, 5):
            addr += rel
        out: list[str] = []
        inline = tid in (1, 2, 5, 6, 7)
        print(f"{t:08x} tag {TAGS[tid]} qwc={qwc}" + ("" if inline else f" addr={addr:08x}"))
        if inline:
            vif.stream(img, t + 8, t + 16 + qwc * 16, out)
        else:
            vif.stream(img, t + 8, t + 16, out)
            if addr < code_end:
                out.append("(target is a placeholder patched at run time; not followed)")
            else:
                vif.stream(img, addr, addr + qwc * 16, out)
        for s in out:
            print("    " + s)
        if tid in (0, 7):
            return
        if tid == 1:
            t += 16 + qwc * 16
        elif tid in (3, 4):
            t += 16
        elif tid == 2:
            t = addr
        elif tid == 5:
            stack.append(t + 16 + qwc * 16)
            t = addr
        elif tid == 6:
            if not stack:
                return
            t = stack.pop()
        if not img.ok(t) or t < code_end:
            print(f"    (next tag {t:08x} is outside the static image; stop)")
            return
    if max_tags > 1:
        print("    (tag limit reached)")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=str(REPO / "SLPS_251.98"))
    ap.add_argument("--one", action="store_true", help="decode only the tag at ADDR")
    ap.add_argument("--file", help="a model/map file instead of the ELF (offsets, see above)")
    ap.add_argument("--rel", default="0", help="--file: base the tags' address words are relative to (hex)")
    ap.add_argument("--stream", action="store_true", help="decode bare VIF codes from ADDR to --end")
    ap.add_argument("--end", default=None, help="--stream: end offset (hex)")
    ap.add_argument("addr", nargs="+", help="address of the first DMA tag (hex)")
    args = ap.parse_args()
    img = FlatImage(Path(args.file)) if args.file else Image(Path(args.elf))
    if args.stream:
        for a in args.addr:
            out: list[str] = []
            Vif().stream(img, int(a, 16), int(args.end, 16) if args.end else len(img.d), out)
            print("\n".join(out[:400]) + ("\n(400 codes shown)" if len(out) > 400 else ""))
        return
    for a in args.addr:
        if args.file:
            print(f"== chain at file offset {int(a, 16):08x} (addresses relative to {int(args.rel, 16):#x})")
            walk(img, int(a, 16), 1 if args.one else 256, int(args.rel, 16))
            continue
        print(f"== chain {int(a, 16):08x}")
        walk(img, int(a, 16), 1 if args.one else 256)


if __name__ == "__main__":
    main()
