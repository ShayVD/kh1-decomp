#!/usr/bin/env python3
"""Summarise a PCSX2 GS dump (Tools > Save Single Frame GS Dump) of the user's own game:
which GIF paths carry what, the GS state every draw runs under, the vertex formats,
texture uploads and the display registers.

  python3 -I tools/vu/gsdump.py DUMP.gs.zst [--draws] [--uploads]

Reads .gs (raw) or .gs.zst (through the `zstandard` module if installed, else the `zstd`
command). PCSX2 2.x dump layout: u32 0xFFFFFFFF, u32 header size, a header of 9 u32
(state version/size, serial offset/size, CRC, screenshot w/h/offset/size), the serial and
screenshot, the GS freeze state (not decoded here), the 8 KB privileged registers, then
packets: 0 = transfer (u8 path, u32 size, data), 1 = vsync (u8 field), 2 = FIFO read
(u32 size), 3 = privileged registers (8 KB). Path: 0 = PATH1 (old: data ends at VU1
memory end), 1 = PATH2, 2 = PATH3, 3 = PATH1. PCSX2 2.8 writes the merged GIF stream with
byte 3 for everything, so the label says nothing about the real path.

General GS registers set before the dump starts live in the freeze state, which this tool
does not parse: a draw before the first write of a register shows that register as "?".

Prints decoded register values, counts and formats only. Output derives from the user's
game: never commit it.
"""
from __future__ import annotations

import argparse
import collections
import shutil
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gs_packets import GSREG, PSM, bits, decode, prim_str  # noqa: E402

PATHS = {0: "PATH1", 1: "PATH2", 2: "PATH3", 3: "PATH1"}
# PACKED register descriptors (REGS nibbles)
PACKED = {0x0: "PRIM", 0x1: "RGBAQ", 0x2: "ST", 0x3: "UV", 0x4: "XYZF2", 0x5: "XYZ2",
          0x6: "TEX0_1", 0x7: "TEX0_2", 0x8: "CLAMP_1", 0x9: "CLAMP_2", 0xA: "FOG",
          0xC: "XYZF3", 0xD: "XYZ3", 0xE: "A+D", 0xF: "NOP"}
STATE = ("TEX0", "TEX1", "CLAMP", "ALPHA", "TEST", "FRAME", "ZBUF", "XYOFFSET", "SCISSOR", "FBA")
GLOBAL = ("FOGCOL", "TEXA", "DTHE", "COLCLAMP", "PABE", "PRMODECONT", "TEXCLUT", "DIMX", "SCANMSK")


def load(path: Path) -> bytes:
    raw = path.read_bytes()
    if not path.name.endswith(".zst"):
        return raw
    try:
        import zstandard  # type: ignore
        return zstandard.ZstdDecompressor().stream_reader(raw).read()
    except ImportError:
        if not shutil.which("zstd"):
            sys.exit("error: .zst dump needs the zstandard module or the zstd command")
        return subprocess.run(["zstd", "-dc"], input=raw, capture_output=True, check=True).stdout


def parse(d: bytes):
    if struct.unpack_from("<I", d, 0)[0] != 0xFFFFFFFF:
        sys.exit("error: not a PCSX2 2.x GS dump (no 0xFFFFFFFF marker)")
    hsize = struct.unpack_from("<I", d, 4)[0]
    h = struct.unpack_from("<9I", d, 8)
    ver, ssize, soff, slen, crc, sw, sh, shoff, shlen = h
    # Offsets in the header are from its start (byte 8): serial, then the screenshot (RGBA8).
    serial = d[8 + soff:8 + soff + slen].decode("latin1", "replace")
    p = 8 + hsize
    state = d[p:p + ssize]
    p += ssize
    regs = d[p:p + 8192]
    p += 8192
    pkts = []
    while p < len(d):
        t = d[p]
        p += 1
        if t == 0:
            path, n = d[p], struct.unpack_from("<I", d, p + 1)[0]
            pkts.append(("xfer", path, d[p + 5:p + 5 + n]))
            p += 5 + n
        elif t == 1:
            pkts.append(("vsync", d[p], b""))
            p += 1
        elif t == 2:
            p += 4
            pkts.append(("fifo", 0, b""))
        elif t == 3:
            pkts.append(("regs", 0, d[p:p + 8192]))
            p += 8192
        else:
            sys.exit(f"error: unknown packet type {t} at {p - 1:#x}")
    return dict(version=ver, crc=crc, serial=serial, shot=(sw, sh), state=state, regs=regs, pkts=pkts)


def priv(regs: bytes) -> list[str]:
    q = lambda off: struct.unpack_from("<Q", regs, off)[0]  # noqa: E731
    pm = q(0x00)
    out = [f"PMODE   EN1={bits(pm, 0, 1)} EN2={bits(pm, 1, 1)} CRTMD={bits(pm, 2, 3)} MMOD={bits(pm, 5, 1)} "
           f"AMOD={bits(pm, 6, 1)} SLBG={bits(pm, 7, 1)} ALP={bits(pm, 8, 8)}"]
    s1 = q(0x10)
    out.append(f"SMODE2  INT={bits(q(0x20), 0, 1)} FFMD={bits(q(0x20), 1, 1)} DPMS={bits(q(0x20), 2, 2)}   "
               f"SMODE1 {s1:#x}")
    for i, (fb, dp) in enumerate(((0x70, 0x80), (0x90, 0xA0)), 1):
        f, x = q(fb), q(dp)
        out.append(f"DISPFB{i} FBP={bits(f, 0, 9) * 2048 * 4:#x} FBW={bits(f, 9, 6) * 64} "
                   f"PSM={PSM.get(bits(f, 15, 5), '?')} DBX={bits(f, 32, 11)} DBY={bits(f, 43, 11)}   "
                   f"DISPLAY{i} DX={bits(x, 0, 12)} DY={bits(x, 12, 11)} MAGH={bits(x, 23, 4) + 1} "
                   f"MAGV={bits(x, 27, 2) + 1} DW={bits(x, 32, 12) + 1} DH={bits(x, 44, 11) + 1}")
    bg = q(0xE0)
    out.append(f"BGCOLOR ({bits(bg, 0, 8)},{bits(bg, 8, 8)},{bits(bg, 16, 8)})")
    return out


class Gs:
    """Track GIF tags across transfers and record every vertex kick with its GS state."""

    def __init__(self):
        self.reg: dict[str, int] = {}
        self.prim = None
        self.draws = collections.Counter()      # state key -> kicks
        self.formats = collections.Counter()    # (path, mode, regs) -> tags
        self.uploads = collections.Counter()    # (dpsm, w, h) -> count
        self.upload_bytes = 0
        self.globals: dict[str, set] = collections.defaultdict(set)
        self.seq: list[tuple] = []              # per-draw-call (state key, kicks) in order
        self._last = None
        self.empty = 0                          # NLOOP=0 tags
        self.pending: dict[int, bytes] = {}     # path -> start of a tag still waiting for data

    def set(self, name: str, v: int):
        if name == "PRIM":
            self.prim = v
            return
        if name == "PRMODE":
            self.reg["PRMODE"] = v
            return
        self.reg[name] = v
        base = name.rsplit("_", 1)[0]
        if base in GLOBAL or name in GLOBAL:
            self.globals[name].add(decode(next(k for k, n in GSREG.items() if n == name), v))

    def key(self) -> tuple:
        p = self.prim if self.prim is not None else -1
        ctx = 2 if p >= 0 and p >> 9 & 1 else 1
        st = []
        for r in STATE:
            n = f"{r}_{ctx}"
            v = self.reg.get(n)
            st.append((n, None if v is None else v))
        return (p,) + tuple(st) + (("FOGCOL", self.reg.get("FOGCOL")),)

    def kick(self):
        k = self.key()
        self.draws[k] += 1
        if self.seq and self.seq[-1][0] == k:
            self.seq[-1][1] += 1
        else:
            self.seq.append([k, 1])

    def write(self, name: str, v: int, adc: bool = False):
        self.set(name, v)
        if name in ("XYZ2", "XYZF2") and not adc:
            self.kick()

    def run(self, path: int, data: bytes):
        """Feed one transfer. A GIF packet can be split across transfers of the same path,
        so a tag whose data has not all arrived waits in a per-path buffer."""
        data = self.pending.pop(path, b"") + data
        p = 0
        while p + 16 <= len(data):
            lo, hi = struct.unpack_from("<QQ", data, p)
            nloop, eop, pre, prim, flg, nreg = (bits(lo, 0, 15), bits(lo, 15, 1), bits(lo, 46, 1),
                                                 bits(lo, 47, 11), bits(lo, 58, 2), bits(lo, 60, 4) or 16)
            need = 16 * (nloop * nreg if flg == 0 else -(-nloop * nreg // 2) if flg == 1 else nloop)
            if p + 16 + need > len(data):
                self.pending[path] = data[p:]
                return
            p += 16
            if nloop == 0:
                # No data follows. The real GS reads these too: the VU1 strip programs leave
                # one vertex qword past NLOOP, which then parses as an empty tag (EOP set).
                self.empty += 1
                continue
            regs = [hi >> (4 * i) & 15 for i in range(nreg)]
            if flg == 0:
                if pre:
                    self.set("PRIM", prim)
                self.formats[(PATHS.get(path, "?"), "PACKED", tuple(PACKED.get(r, "?") for r in regs),
                              prim_str(prim) if pre else "")] += 1
                for _ in range(nloop):
                    for r in regs:
                        a, b = struct.unpack_from("<QQ", data, p)
                        p += 16
                        self.packed(r, a, b)
            elif flg == 1:
                if pre:
                    self.set("PRIM", prim)
                self.formats[(PATHS.get(path, "?"), "REGLIST", tuple(GSREG.get(r, "?") for r in regs),
                              prim_str(prim) if pre else "")] += 1
                n = nloop * nreg
                for i in range(n):
                    v = struct.unpack_from("<Q", data, p)[0]
                    p += 8
                    r = regs[i % nreg]
                    if r != 0xE and r != 0xF:
                        self.write(GSREG.get(r, f"reg{r:#x}"), v)
                if n & 1:
                    p += 8
            else:
                self.formats[(PATHS.get(path, "?"), "IMAGE", (), "")] += 1
                self.upload_bytes += nloop * 16
                b = self.reg.get("BITBLTBUF", 0)
                t = self.reg.get("TRXREG", 0)
                self.uploads[(PSM.get(bits(b, 56, 6), "?"), bits(t, 0, 12), bits(t, 32, 12))] += 1
                p += nloop * 16

    def packed(self, r: int, a: int, b: int):
        if r == 0x0:
            self.set("PRIM", a & 0x7FF)
        elif r == 0x1:
            self.set("RGBAQ", a & 0xFF | (a >> 32 & 0xFF) << 8 | (b & 0xFF) << 16 | (b >> 32 & 0xFF) << 24)
        elif r == 0x2:
            self.set("ST", a)
        elif r == 0x3:
            self.set("UV", a & 0x3FFF | (a >> 32 & 0x3FFF) << 16)
        elif r in (0x4, 0x5):
            adc = bool(b >> 47 & 1)
            self.write("XYZF2" if r == 4 else "XYZ2", a & 0xFFFF | (a >> 32 & 0xFFFF) << 16, adc)
        elif r == 0xE:
            n = GSREG.get(b & 0xFF, f"reg{b & 0xFF:#x}")
            if n == "XYZ2" or n == "XYZF2":
                self.write(n, a)
            else:
                self.set(n, a)
        elif r in (0x6, 0x7, 0x8, 0x9, 0xA, 0xC, 0xD):
            self.set(PACKED[r], a)


def show_state(k: tuple) -> list[str]:
    p = k[0]
    out = [f"  PRIM {prim_str(p) if p >= 0 else '?'}"]
    for n, v in k[1:]:
        if n.startswith(("XYOFFSET", "SCISSOR", "FRAME", "ZBUF", "FBA")):
            continue
        reg = next((r for r, nm in GSREG.items() if nm == n), None)
        out.append(f"    {n:8} {'?' if v is None else decode(reg, v)}")
    return out


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("dump", type=Path)
    ap.add_argument("--draws", action="store_true", help="print the draw sequence (state changes in order)")
    ap.add_argument("--top", type=int, default=12, help="how many GS states to print in full")
    a = ap.parse_args()
    d = parse(load(a.dump))
    paths = collections.Counter()
    vs = 0
    gs = Gs()
    frame = 0
    for kind, path, data in d["pkts"]:
        if kind == "xfer":
            paths[PATHS.get(path, "?")] += len(data)
            gs.run(path, data)
        elif kind == "vsync":
            vs += 1
    print(f"dump: serial {d['serial']} crc {d['crc']:#010x} state v{d['version']} ({len(d['state'])} bytes), "
          f"{len(d['pkts'])} packets, {vs} vsyncs")
    print("transfers by path: " + ", ".join(f"{k} {v} bytes" for k, v in sorted(paths.items())))
    print("\nprivileged registers at the start:")
    for line in priv(d["regs"]):
        print("  " + line)
    print("\nGIF tag formats (path, mode, registers, PRIM if PRE): tags")
    for (path, mode, regs, prim), n in gs.formats.most_common():
        print(f"  {n:6}  {path} {mode:7} {' '.join(regs)}  {prim}")
    print(f"  {gs.empty:6}  empty tags (NLOOP=0)")
    print(f"\nglobal registers written: " + ("none" if not gs.globals else ""))
    for n, vals in sorted(gs.globals.items()):
        print(f"  {n}: {'; '.join(sorted(vals))}")
    print(f"\nuploads (IMAGE): {sum(gs.uploads.values())}, {gs.upload_bytes} bytes; by DPSM and size:")
    for (psm, w, h), n in gs.uploads.most_common(16):
        print(f"  {n:4}  {psm} {w}x{h}")
    total = sum(gs.draws.values())
    print(f"\nvertex kicks: {total} under {len(gs.draws)} distinct GS states; {len(gs.seq)} state runs")
    prims = collections.Counter()
    for k, n in gs.draws.items():
        prims[prim_str(k[0]) if k[0] >= 0 else "?"] += n
    for p, n in prims.most_common():
        print(f"  {n:7}  {p}")
    print(f"\ntop {a.top} GS states by kicks:")
    for k, n in gs.draws.most_common(a.top):
        print(f"{n:7} kicks")
        for line in show_state(k):
            print(line)
    if a.draws:
        print("\ndraw sequence (kicks, PRIM, TEX0 TBP/PSM, ALPHA, TEST ZTST):")
        for k, n in gs.seq:
            st = dict(k[1:])
            ctx = 2 if k[0] >= 0 and k[0] >> 9 & 1 else 1
            t0, al, te = st.get(f"TEX0_{ctx}"), st.get(f"ALPHA_{ctx}"), st.get(f"TEST_{ctx}")
            tx = "-" if t0 is None else f"{bits(t0, 0, 14):#x}/{PSM.get(bits(t0, 20, 6), '?')}"
            print(f"  {n:6}  {prim_str(k[0]) if k[0] >= 0 else '?':22} {tx:16} "
                  f"{'-' if al is None else decode(0x42, al):28} {'-' if te is None else decode(0x47, te)}")


if __name__ == "__main__":
    main()
