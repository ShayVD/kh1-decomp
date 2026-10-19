#!/usr/bin/env python3
"""Decode the static GS setup packets of the user's SLPS_251.98: walk a DMA
chain (or one REFE/CNT tag) for the GIF channel and print the GS registers
its GIF A+D packets write, decoded field by field.

  python3 -I tools/vu/gs_packets.py [--elf SLPS_251.98] ADDR [ADDR ...]
  python3 -I tools/vu/gs_packets.py --callers [--layout layout.tsv]

ADDR is what the game passes to its GIF send wrapper func_00106b18 (a DMA
tag in the image). --callers lists every lui/addiu pair in code that builds
an address of a tag immediately before a jal to func_00106b18 and decodes
them all.

Standalone (Python >= 3.10, stdlib only). Prints register names and decoded
fields (the game's GS state), never raw packet bytes. Output is derived from
the user's ELF at run time: do not commit it.
"""
from __future__ import annotations

import argparse
import bisect
import struct
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
VERBOSE = False

GSREG = {0x00: "PRIM", 0x01: "RGBAQ", 0x02: "ST", 0x03: "UV", 0x04: "XYZF2", 0x05: "XYZ2",
         0x06: "TEX0_1", 0x07: "TEX0_2", 0x08: "CLAMP_1", 0x09: "CLAMP_2", 0x0A: "FOG",
         0x0C: "XYZF3", 0x0D: "XYZ3", 0x0E: "A+D", 0x0F: "NOP",
         0x14: "TEX1_1", 0x15: "TEX1_2", 0x16: "TEX2_1", 0x17: "TEX2_2",
         0x18: "XYOFFSET_1", 0x19: "XYOFFSET_2", 0x1A: "PRMODECONT", 0x1B: "PRMODE",
         0x1C: "TEXCLUT", 0x22: "SCANMSK", 0x34: "MIPTBP1_1", 0x35: "MIPTBP1_2",
         0x36: "MIPTBP2_1", 0x37: "MIPTBP2_2", 0x3B: "TEXA", 0x3D: "FOGCOL", 0x3F: "TEXFLUSH",
         0x40: "SCISSOR_1", 0x41: "SCISSOR_2", 0x42: "ALPHA_1", 0x43: "ALPHA_2", 0x44: "DIMX",
         0x45: "DTHE", 0x46: "COLCLAMP", 0x47: "TEST_1", 0x48: "TEST_2", 0x49: "PABE",
         0x4A: "FBA_1", 0x4B: "FBA_2", 0x4C: "FRAME_1", 0x4D: "FRAME_2", 0x4E: "ZBUF_1",
         0x4F: "ZBUF_2", 0x50: "BITBLTBUF", 0x51: "TRXPOS", 0x52: "TRXREG", 0x53: "TRXDIR",
         0x54: "HWREG", 0x60: "SIGNAL", 0x61: "FINISH", 0x62: "LABEL"}
PSM = {0x00: "PSMCT32", 0x01: "PSMCT24", 0x02: "PSMCT16", 0x0A: "PSMCT16S", 0x13: "PSMT8",
       0x14: "PSMT4", 0x1B: "PSMT8H", 0x24: "PSMT4HL", 0x2C: "PSMT4HH", 0x30: "PSMZ32",
       0x31: "PSMZ24", 0x32: "PSMZ16", 0x3A: "PSMZ16S"}
PRIMS = ["POINT", "LINE", "LINESTRIP", "TRI", "TRISTRIP", "TRIFAN", "SPRITE", "?"]
ATST = ["NEVER", "ALWAYS", "LESS", "LEQUAL", "EQUAL", "GEQUAL", "GREATER", "NOTEQUAL"]
ZTST = ["NEVER", "ALWAYS", "GEQUAL", "GREATER"]
ABCD = ["Cs", "Cd", "0", "?"]


def bits(v: int, lo: int, n: int) -> int:
    return v >> lo & ((1 << n) - 1)


def prim_str(v: int) -> str:
    f = [PRIMS[v & 7]]
    for b, n in ((3, "IIP"), (4, "TME"), (5, "FGE"), (6, "ABE"), (7, "AA1"), (8, "FST"), (9, "CTXT2"), (10, "FIX")):
        if v >> b & 1:
            f.append(n)
    return "|".join(f)


def decode(reg: int, v: int) -> str:
    n = GSREG.get(reg, f"reg{reg:#x}")
    if n == "PRIM":
        return prim_str(v)
    if n.startswith("FRAME"):
        return (f"FBP={bits(v, 0, 9):#x} (addr {bits(v, 0, 9) * 8192:#x}) FBW={bits(v, 16, 6) * 64} "
                f"PSM={PSM.get(bits(v, 24, 6), hex(bits(v, 24, 6)))} FBMSK={bits(v, 32, 32):#x}")
    if n.startswith("ZBUF"):
        return (f"ZBP={bits(v, 0, 9):#x} (addr {bits(v, 0, 9) * 8192:#x}) "
                f"PSM={PSM.get(bits(v, 24, 4) | 0x30, hex(bits(v, 24, 4)))} ZMSK={bits(v, 32, 1)}")
    if n.startswith("TEST"):
        return (f"ATE={bits(v, 0, 1)} ATST={ATST[bits(v, 1, 3)]} AREF={bits(v, 4, 8)} AFAIL={bits(v, 12, 2)} "
                f"DATE={bits(v, 14, 1)} DATM={bits(v, 15, 1)} ZTE={bits(v, 16, 1)} ZTST={ZTST[bits(v, 17, 2)]}")
    if n.startswith("ALPHA"):
        a, b, c, d = (bits(v, 0, 2), bits(v, 2, 2), bits(v, 4, 2), bits(v, 6, 2))
        cc = ["As", "Ad", "FIX"][c] if c < 3 else "?"
        return f"({ABCD[a]}-{ABCD[b]})*{cc}>>7+{ABCD[d]} FIX={bits(v, 32, 8)}"
    if n.startswith("SCISSOR"):
        return f"x {bits(v, 0, 11)}..{bits(v, 16, 11)} y {bits(v, 32, 11)}..{bits(v, 48, 11)}"
    if n.startswith("XYOFFSET"):
        return f"OFX={bits(v, 0, 16) / 16:g} OFY={bits(v, 32, 16) / 16:g}"
    if n.startswith("TEX0"):
        return (f"TBP0={bits(v, 0, 14):#x} TBW={bits(v, 14, 6) * 64} PSM={PSM.get(bits(v, 20, 6), hex(bits(v, 20, 6)))} "
                f"TW={1 << bits(v, 26, 4)} TH={1 << bits(v, 30, 4)} TCC={bits(v, 34, 1)} TFX={bits(v, 35, 2)} "
                f"CBP={bits(v, 37, 14):#x} CPSM={PSM.get(bits(v, 51, 4), hex(bits(v, 51, 4)))} CSM={bits(v, 55, 1)} "
                f"CSA={bits(v, 56, 5)} CLD={bits(v, 61, 3)}")
    if n.startswith("TEX1"):
        return (f"LCM={bits(v, 0, 1)} MXL={bits(v, 2, 3)} MMAG={bits(v, 5, 1)} MMIN={bits(v, 6, 3)} "
                f"MTBA={bits(v, 9, 1)} L={bits(v, 19, 2)} K={bits(v, 32, 12)}")
    if n.startswith("CLAMP"):
        m = ["REPEAT", "CLAMP", "REGION_CLAMP", "REGION_REPEAT"]
        return f"WMS={m[bits(v, 0, 2)]} WMT={m[bits(v, 2, 2)]} MINU={bits(v, 4, 10)} MAXU={bits(v, 14, 10)}"
    if n == "FOGCOL":
        return f"rgb=({bits(v, 0, 8)},{bits(v, 8, 8)},{bits(v, 16, 8)})"
    if n == "TEXA":
        return f"TA0={bits(v, 0, 8)} AEM={bits(v, 15, 1)} TA1={bits(v, 32, 8)}"
    if n in ("RGBAQ",):
        return f"rgba=({bits(v, 0, 8)},{bits(v, 8, 8)},{bits(v, 16, 8)},{bits(v, 24, 8)})"
    if n in ("PRMODECONT", "DTHE", "COLCLAMP", "PABE", "FBA_1", "FBA_2", "TEXFLUSH"):
        return f"{v:#x}"
    if n == "BITBLTBUF":
        return (f"SBP={bits(v, 0, 14):#x} SBW={bits(v, 16, 6)} SPSM={PSM.get(bits(v, 24, 6), '?')} "
                f"DBP={bits(v, 32, 14):#x} DBW={bits(v, 48, 6)} DPSM={PSM.get(bits(v, 56, 6), '?')}")
    if n == "TRXREG":
        return f"w={bits(v, 0, 12)} h={bits(v, 32, 12)}"
    if n == "TRXPOS":
        return f"src=({bits(v, 0, 11)},{bits(v, 16, 11)}) dst=({bits(v, 32, 11)},{bits(v, 48, 11)})"
    if n == "TRXDIR":
        return ["host->local", "local->host", "local->local", "off"][v & 3]
    if n in ("XYZ2", "XYZF2", "XYZ3", "XYZF3"):
        return f"x={bits(v, 0, 16) / 16:g} y={bits(v, 16, 16) / 16:g} z={bits(v, 32, 32)}"
    if n == "UV":
        return f"u={bits(v, 0, 14) / 16:g} v={bits(v, 16, 14) / 16:g}"
    return f"{v:#x}"


class Image:
    def __init__(self, path: Path):
        d = path.read_bytes()
        phoff = struct.unpack_from("<I", d, 0x1C)[0]
        phentsize, phnum = struct.unpack_from("<HH", d, 0x2A)
        self.d, self.segs = d, []
        for i in range(phnum):
            t, off, va, _pa, fs, _ms = struct.unpack_from("<6I", d, phoff + i * phentsize)
            if t == 1:
                self.segs.append((va, off, fs))

    def ok(self, a: int, n: int = 16) -> bool:
        return any(v <= a and a + n <= v + f for v, _o, f in self.segs)

    def q(self, a: int) -> tuple[int, int]:
        for v, o, f in self.segs:
            if v <= a < v + f:
                lo, hi = struct.unpack_from("<QQ", self.d, o + a - v)
                return lo, hi
        raise KeyError(hex(a))


def gif_payload(img: Image, a: int, n: int, out: list[str]) -> None:
    """Decode GIF packets in n qwords at a."""
    end = a + 16 * n
    while a < end:
        lo, hi = img.q(a)
        nloop, eop, pre, prim = bits(lo, 0, 15), bits(lo, 15, 1), bits(lo, 46, 1), bits(lo, 47, 11)
        flg, nreg = bits(lo, 58, 2), bits(lo, 60, 4) or 16
        regs = [bits(hi, 4 * i, 4) for i in range(nreg)]
        head = f"  {a:08x} GIFtag NLOOP={nloop} EOP={eop} FLG={['PACKED', 'REGLIST', 'IMAGE', 'IMAGE'][flg]}"
        if pre:
            head += f" PRIM={prim_str(prim)}"
        if flg < 2:
            head += " REGS=" + ",".join(GSREG.get(r, hex(r)) for r in regs)
        out.append(head)
        a += 16
        if flg == 0:
            if regs == [0xE] * nreg:
                for _ in range(nloop * nreg):
                    if a >= end:
                        break
                    v, r = img.q(a)
                    out.append(f"    {GSREG.get(r & 0xFF, hex(r & 0xFF)):11s} {decode(r & 0xFF, v)}")
                    a += 16
            else:
                a += 16 * nloop * nreg
        elif flg == 1:
            words = []
            for k in range((nloop * nreg + 1) // 2):
                lo2, hi2 = img.q(a + 16 * k)
                words += [lo2, hi2]
            if VERBOSE:
                for k in range(min(nloop, 4)):
                    vals = words[k * nreg:(k + 1) * nreg]
                    out.append("    " + "; ".join(f"{GSREG.get(r, hex(r))} {decode(r, v)}" for r, v in zip(regs, vals)))
                if nloop > 4:
                    out.append(f"    ... {nloop - 4} more")
            a += ((nloop * nreg + 1) // 2) * 16
        else:
            out.append(f"    (IMAGE data, {nloop} qwords)")
            a += 16 * nloop
        if nloop == 0 and flg != 2 and not eop:
            continue


def walk(img: Image, head: int) -> list[str]:
    out, a, seen, stack = [], head, set(), []
    for _ in range(256):
        if a in seen or not img.ok(a):
            break
        seen.add(a)
        lo, _hi = img.q(a)
        qwc, tid, addr = lo & 0xFFFF, lo >> 28 & 7, lo >> 32 & 0x7FFFFFFF
        out.append(f" tag {a:08x} {['REFE', 'CNT', 'NEXT', 'REF', 'REFS', 'CALL', 'RET', 'END'][tid]} qwc={qwc} addr={addr:08x}")
        if tid in (0, 3, 4):
            if img.ok(addr, 16 * qwc) and qwc:
                gif_payload(img, addr, qwc, out)
            if tid == 0:
                break
            a += 16
        elif tid in (1, 7):
            if qwc:
                gif_payload(img, a + 16, qwc, out)
            if tid == 7:
                break
            a += 16 + 16 * qwc
        elif tid == 2:
            if qwc:
                gif_payload(img, a + 16, qwc, out)
            a = addr
        elif tid == 5:
            stack.append(a + 16 + 16 * qwc)
            a = addr
        elif tid == 6:
            if not stack:
                break
            a = stack.pop()
    return out


def callers(img: Image, layout: Path, target: int = 0x00106B18):
    """(call site, function, tag address) for every jal target whose a0 was built with lui/addiu."""
    rows = []
    for line in layout.read_text().splitlines():
        if line and line[0] not in "#a":
            p = line.split("\t")
            rows.append((int(p[0], 16), int(p[1], 16)))
    res = []
    jal = 3 << 26 | (target >> 2)
    for s, e in rows:
        hi, a0 = {}, None
        for a in range(s, e, 4):
            w = struct.unpack_from("<I", img.d, a - 0x100000 + 0x80)[0]
            o, rs, rt, im = w >> 26, w >> 21 & 31, w >> 16 & 31, w & 0xFFFF
            if o == 0x0F:
                hi[rt] = im << 16
            elif o == 0x09 and rs in hi:
                v = (hi[rs] + (im - 0x10000 if im & 0x8000 else im)) & 0xFFFFFFFF
                if rt == 4:
                    a0 = (a, v)
            if w in (jal, 2 << 26 | (target >> 2)) and a0:
                # the delay slot may set a0 too
                d = struct.unpack_from("<I", img.d, a + 4 - 0x100000 + 0x80)[0]
                if d >> 26 == 0x09 and (d >> 16 & 31) == 4 and (d >> 21 & 31) in hi:
                    im = d & 0xFFFF
                    a0 = (a + 4, (hi[d >> 21 & 31] + (im - 0x10000 if im & 0x8000 else im)) & 0xFFFFFFFF)
                res.append((a, s, a0[1]))
                a0 = None
    return res


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("addr", nargs="*", type=lambda s: int(s, 16))
    ap.add_argument("--elf", default=str(REPO / "SLPS_251.98"))
    ap.add_argument("--layout", default=str(REPO / "layout.tsv"))
    ap.add_argument("--callers", action="store_true")
    ap.add_argument("--adtable", nargs=3, metavar=("REGS", "VALUES", "N"),
                    help="decode N u64 register numbers at REGS with N u64 values at VALUES (hex addresses)")
    ap.add_argument("-v", action="store_true", help="also decode REGLIST data (first 4 loops)")
    args = ap.parse_args()
    global VERBOSE
    VERBOSE = args.v
    img = Image(Path(args.elf))
    if args.adtable:
        ra, va, n = (int(x, 16) for x in args.adtable[:2]), None, int(args.adtable[2], 0)
        ra, va = (int(x, 16) for x in args.adtable[:2])
        for i in range(n):
            r = img.q(ra + 8 * i)[0] if (ra + 8 * i) % 16 == 0 else img.q(ra + 8 * i - 8)[1]
            v = img.q(va + 8 * i)[0] if (va + 8 * i) % 16 == 0 else img.q(va + 8 * i - 8)[1]
            print(f"  {GSREG.get(r & 0xFF, hex(r)):11s} {decode(r & 0xFF, v)}")
        return
    heads = [(None, None, a) for a in args.addr]
    if args.callers:
        heads += callers(img, Path(args.layout))
    for site, fn, a in heads:
        where = f" (passed at {site:08x} in func_{fn:08x})" if site else ""
        print(f"== packet {a:08x}{where}")
        if not img.ok(a):
            print("  not in the image (run-time buffer)")
            continue
        print("\n".join(walk(img, a)))


if __name__ == "__main__":
    main()
