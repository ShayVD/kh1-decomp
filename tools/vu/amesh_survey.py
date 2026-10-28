#!/usr/bin/env python3
"""Decode and check every renderer A mesh (VU1 programs P0-P7) in the map files
extracted from the user's own disc, and print what they hold, counted.

  python3 -I tools/vu/amesh_survey.py DIR_OR_FILES... [--per-file] [--regs]

Each argument is a map file `<ww>00_<nn>.bin` (tools/shift/extract_kingdom.py)
or a directory searched for them. For every file it walks:

  * section 1 (the grid, renderer-spec section 4.14): the cell boxes, entry 0
    (the chains' GIF template) and every cell's mesh A and mesh B REF;
  * sections 2 and 3 (the far meshes, func_00108cf8, P4): the +0x80 and +0x90
    tags of each mesh header.

It emulates the VIF1 side of each REF (STCYCL / UNPACK / FLUSH / DIRECT /
MSCNT; V2 unpacks repeat x and y in z and w, as PCSX2 does) into a VU memory
image, and at each MSCNT reads the batch the way P0-P7 do (renderer-spec
section 2.2): qw0 = GIF tag (NLOOP & 0x7FFF = n vertices, upper REGS word =
the clipped fans' PRIM), then n x {xyz + strip flag, RGBA, ST}. The DIRECT
(PATH2) packets are decoded as GIF packets: A+D register writes and IMAGE
transfers. Checks: every batch's n equals its UNPACK counts, the strip flags
are 0 / +-1, nothing but the codes above occurs. Prints counts and value
histograms of flags and GS register fields, never vertex or texture data.

--per-file  one summary line per file as well
--regs      every distinct A+D value per register (decoded), with counts

Standalone (Python >= 3.10, stdlib + gs_packets.py beside it), read-only.
Output derives from the user's own files: never commit it.
See docs/renderer-spec.md section 2.2 "Map meshes on the disc".
"""
from __future__ import annotations

import argparse
import collections
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gs_packets import GSREG, PSM, decode, prim_str  # noqa: E402

C = collections.Counter
MAPNAME = re.compile(r"^[a-z]{2}00_\d\d\.bin$")


def f32(w: int) -> float:
    return struct.unpack("<f", struct.pack("<I", w))[0]


def s32(w: int) -> int:
    return w - (1 << 32) if w & 0x80000000 else w


class Stats:
    def __init__(self) -> None:
        self.c: dict[str, C] = collections.defaultdict(C)
        self.errors: list[str] = []

    def add(self, key: str, val, n: int = 1) -> None:
        self.c[key][val] += n


class Vif:
    """Enough of VIF1 for the map streams. VU memory is batch-relative (TOPS = 0)."""

    def __init__(self, st: Stats, kind: str, where: str) -> None:
        self.st, self.kind, self.where = st, kind, where
        self.cl = self.wl = 1
        self.mem: dict[int, list[int]] = {}
        self.written: dict[int, int] = {}   # qword -> bitmask of the words written since the last MSCNT
        self.unpacks: list[tuple[int, int, int]] = []  # (vu addr, num, vnvl)
        self.textures = 0

    def err(self, msg: str) -> None:
        self.st.errors.append(f"{self.where}: {msg}")

    def put(self, addr: int, vals: list[int], mask: int) -> None:
        q = self.mem.setdefault(addr, [0, 0, 0, 0])
        for k in range(4):
            if mask >> k & 1:
                q[k] = vals[k] & 0xFFFFFFFF
        self.written[addr] = self.written.get(addr, 0) | mask

    def unpack(self, d: bytes, a: int, cmd: int, imm: int, num: int) -> int:
        vnvl = cmd & 0xF
        vn, vl = vnvl >> 2, vnvl & 3
        if cmd & 0x10:
            self.err("masked UNPACK")
        if vnvl == 15:
            self.err("V4-5 UNPACK")
            return a + (num * 2 + 3) // 4 * 4
        usn = imm >> 14 & 1
        size = [4, 2, 1][vl]
        nel = vn + 1
        base = imm & 0x3FF
        if self.wl > self.cl:
            self.err(f"filling write cycle cl={self.cl} wl={self.wl}")
        fmt = {4: "<i", 2: "<h", 1: "<b"}[size] if not usn else {4: "<I", 2: "<H", 1: "<B"}[size]
        p = a
        for i in range(num):
            vals = []
            for _k in range(nel):
                vals.append(struct.unpack_from(fmt, d, p)[0])
                p += size
            if vn == 0:
                vals = vals * 4
                mask = 0xF
            elif vn == 1:
                vals = vals + vals          # PCSX2: z, w repeat x, y
                mask = 0xF
            elif vn == 2:
                vals = vals + [0]
                mask = 0x7
            else:
                mask = 0xF
            addr = base + (i // self.wl) * self.cl + i % self.wl
            self.put(addr, vals, mask)
        self.unpacks.append((base, num, vnvl))
        return a + (p - a + 3) // 4 * 4

    def fields(self, reg: int, v: int) -> None:
        """Per-field histograms of the registers the meshes set."""
        k = self.kind
        if reg in (6, 7):
            self.st.add(f"{k} TEX0 PSM/CPSM", (PSM.get(v >> 20 & 0x3F, "?"), PSM.get(v >> 51 & 0xF, "?")))
            self.st.add(f"{k} TEX0 TW x TH", (1 << (v >> 26 & 0xF), 1 << (v >> 30 & 0xF)))
            self.st.add(f"{k} TEX0 TCC/TFX", (v >> 34 & 1, ["MODULATE", "DECAL", "HIGHLIGHT", "HIGHLIGHT2"][v >> 35 & 3]))
            self.st.add(f"{k} TEX0 CLD/CSM/CSA", (v >> 61 & 7, v >> 55 & 1, v >> 56 & 0x1F))
            self.st.add(f"{k} TEX0 TBW", (v >> 14 & 0x3F) * 64)
            self.st.add(f"{k} TEX0 TBP0 range", (v & 0x3FFF) // 0x400 * 0x400)
            self.st.add(f"{k} TEX0 CBP range", (v >> 37 & 0x3FFF) // 0x100 * 0x100)
        elif reg in (8, 9):
            m = ["REPEAT", "CLAMP", "REGION_CLAMP", "REGION_REPEAT"]
            self.st.add(f"{k} CLAMP WMS/WMT", (m[v & 3], m[v >> 2 & 3]))

    def direct(self, d: bytes, a: int, nq: int) -> None:
        end = a + nq * 16
        while a < end:
            lo, hi = struct.unpack_from("<QQ", d, a)
            a += 16
            nloop, eop = lo & 0x7FFF, lo >> 15 & 1
            pre, prim, flg, nreg = lo >> 46 & 1, lo >> 47 & 0x7FF, lo >> 58 & 3, lo >> 60 & 0xF
            nreg = nreg or 16
            regs = [hi >> (4 * k) & 0xF for k in range(nreg)]
            if pre:
                self.st.add(f"{self.kind} DIRECT PRIM (PRE)", prim_str(prim))
            if flg == 0:
                for _ in range(nloop):
                    for r in regs:
                        if r == 0xE:
                            v, reg = struct.unpack_from("<QB", d, a)
                            self.st.add(f"{self.kind} A+D", reg)
                            self.st.add(f"{self.kind} A+D {reg:#x}", v)
                            self.fields(reg, v)
                        else:
                            self.st.add(f"{self.kind} PACKED reg", r)
                        a += 16
            elif flg == 2:
                self.st.add(f"{self.kind} IMAGE qwords", "sum", nloop)
                self.textures += 1
                a += nloop * 16
            else:
                self.err(f"REGLIST GIF tag in DIRECT")
                a += nloop * nreg * 8
            if eop and a < end:
                # several packets in one DIRECT are fine; keep reading
                pass
        if a != end:
            self.err(f"DIRECT data ends at {a - end:+d} bytes from its size")

    def mscnt(self) -> None:
        st, k = self.st, self.kind
        if 0 not in self.mem:
            self.err("MSCNT with no batch header")
            return
        hdr = self.mem[0]
        lo = hdr[0] | hdr[1] << 32
        n = lo & 0x7FFF
        prim = lo >> 47 & 0x7FF
        st.add(f"{k} batch tag PRE", lo >> 46 & 1)
        st.add(f"{k} batch tag PRIM", prim_str(prim))
        st.add(f"{k} batch tag NREG/FLG", (lo >> 60 & 0xF, lo >> 58 & 3))
        st.add(f"{k} batch tag EOP", lo >> 15 & 1)
        st.add(f"{k} batch tag w (fan PRIM word)", f"{hdr[3]:#010x} {prim_str(hdr[3] >> 15 & 0x7FF) if hdr[3] else ''}")
        st.add(f"{k} batch tag z (REGS)", f"{hdr[2]:#x}")
        if self.kind in ("template", "far +0x80"):
            # the clipped-output template (qw48), uploaded by the second init block: no vertices
            st.add(f"{k} template NLOOP", n)
            self.mem.clear()
            self.unpacks.clear()
            self.written.clear()
            return
        st.add(f"{k} batches", "n")
        st.add(f"{k} vertices", "n", n)
        nums = [num for base, num, _ in self.unpacks if base in (1, 2, 3)]
        if any(x != n for x in nums):
            self.err(f"batch of {n} vertices with UNPACK counts {nums}")
        st.add(f"{k} batch size", min(n // 8 * 8, 96))
        fmts = tuple(sorted({(base, vnvl) for base, _, vnvl in self.unpacks}))
        st.add(f"{k} unpack layout", fmts)
        flags = C()
        for v in range(n):
            q0 = self.mem.get(1 + 3 * v)
            q1 = self.mem.get(2 + 3 * v)
            q2 = self.mem.get(3 + 3 * v)
            if q0 is None or q1 is None or q2 is None:
                self.err("vertex qword not written")
                return
            st.add(f"{k} strip w raw", f"{q0[3]:#x}")
            sf = s32(q0[3])
            flags[sf] += 1
            st.add(f"{k} RGBA alpha", min(q1[3], 0x100) // 16 * 16)
            st.add(f"{k} RGBA rgb>0x80", any(q1[c] > 0x80 for c in range(3)))
            st.add(f"{k} ST.w (P3 flag)", s32(q2[3]) & 0xFFFF if self.unpacks and any(
                base == 3 and vnvl == 13 for base, _, vnvl in self.unpacks) else "n/a (V2)")
            if v < 2 and sf != 0:
                self.err(f"strip flag {sf} on vertex {v} of a batch")
        for f, c in flags.items():
            st.add(f"{k} strip flag", f if f in (0, 1, -1) else "other", c)
        self.mem.clear()
        self.unpacks.clear()
        self.written.clear()

    def run(self, d: bytes, a: int, end: int) -> None:
        while a < end:
            c = struct.unpack_from("<I", d, a)[0]
            cmd, imm, num = c >> 24 & 0x7F, c & 0xFFFF, c >> 16 & 0xFF
            a += 4
            if cmd == 0:
                continue
            self.st.add(f"{self.kind} VIF code", f"{cmd:#04x}" if cmd < 0x60 else "UNPACK")
            if cmd == 1:
                self.cl, self.wl = imm & 0xFF, imm >> 8
                self.st.add(f"{self.kind} STCYCL", (self.cl, self.wl))
            elif cmd in (0x10, 0x11, 0x13):
                pass
            elif cmd == 0x17:
                self.mscnt()
            elif cmd == 0x50:
                n = imm or 0x10000
                self.direct(d, a, n)
                a += n * 16
            elif cmd >= 0x60:
                a = self.unpack(d, a, cmd, imm, num or 256)
            else:
                self.err(f"unexpected VIF code {cmd:#x}")
                return
        if self.unpacks:
            self.err("UNPACKs after the last MSCNT")


def walk_ref(st: Stats, d: bytes, kind: str, where: str, tag_lo: int, addr: int) -> Vif:
    tid, qwc = tag_lo >> 28 & 7, tag_lo & 0xFFFF
    st.add(f"{kind} DMA tag", ["REFE", "CNT", "NEXT", "REF", "REFS", "CALL", "RET", "END"][tid])
    v = Vif(st, kind, where)
    if addr + qwc * 16 > len(d):
        v.err("REF past the end of the file")
        return v
    v.run(d, addr, addr + qwc * 16)
    st.add(f"{kind} textures per mesh", v.textures)
    return v


def survey(path: Path, st: Stats, per_file: bool) -> None:
    d = path.read_bytes()
    u32 = lambda o: struct.unpack_from("<I", d, o)[0]  # noqa: E731
    name = path.name
    ver = u32(0)
    st.add("map version", ver)
    s1 = u32(0x18)
    n, et = u32(s1), u32(s1 + 4)
    st.add("cells per map", min(n // 128 * 128, 1024))
    if n > 1024:
        st.errors.append(f"{name}: {n} cells > 1024")
    t0, a0 = u32(s1 + et), u32(s1 + et + 4)
    tv = walk_ref(st, d, "template", name, t0, s1 + a0)
    del tv
    # cell boxes: 16 + 128 i, corners' w words carry the per-cell values (func_00106ed0)
    for i in range(n):
        b = s1 + 16 + 128 * i
        w = [f32(u32(b + 16 * c + 12)) for c in range(8)]
        st.add("cell w0 (nonzero = has values)", w[0] != 0.0)
        st.add("cell w4 (group bit t)", w[4])
        if i == 0:
            st.add("cell 0 w6 (anim frames + 20, 1.0 = none)", w[6])
    na = nb = 0
    for i in range(n):
        e = s1 + et + 16 * (i + 1)
        a, aa, b, bb = struct.unpack_from("<4I", d, e)
        for kind, lo, ad in (("A", a, aa), ("B", b, bb)):
            if lo:
                walk_ref(st, d, f"cell {kind}", f"{name} cell {i} {kind}", lo, s1 + ad)
        na += a != 0
        nb += b != 0
        st.add("cell has A/B", (a != 0, b != 0))
    for sec in (2, 3):
        o, size = u32(0x10 + 8 * sec), u32(0x14 + 8 * sec)
        if size == 0:
            st.add("far mesh sections present", (sec, False))
            continue
        st.add("far mesh sections present", (sec, True))
        for t in (0x80, 0x90):
            lo, ad = u32(o + t), u32(o + t + 4)
            walk_ref(st, d, f"far +{t:#x}", f"{name} sec{sec} +{t:#x}", lo, o + ad)
    if per_file:
        print(f"{name}: version {ver}, {n} cells ({na} with mesh A, {nb} with mesh B), "
              f"far meshes {[u32(0x14 + 8 * s) != 0 for s in (2, 3)]}")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("paths", nargs="+", type=Path)
    ap.add_argument("--per-file", action="store_true")
    ap.add_argument("--regs", action="store_true")
    a = ap.parse_args()
    files: list[Path] = []
    for p in a.paths:
        if p.is_dir():
            files += sorted(x for x in p.iterdir() if MAPNAME.match(x.name))
        else:
            files.append(p)
    st = Stats()
    for f in files:
        survey(f, st, a.per_file)
    print(f"{len(files)} map files")
    for key in sorted(st.c):
        if " A+D 0x" in key:
            continue
        items = st.c[key].most_common(12)
        more = len(st.c[key]) - len(items)
        print(f"{key}: " + ", ".join(f"{v}: {c}" for v, c in items) + (f" (+{more} more)" if more > 0 else ""))
    for key in sorted(k for k in st.c if " A+D 0x" in k):
        reg = int(key.rsplit(" ", 1)[1], 16)
        rn = GSREG.get(reg, hex(reg))
        vals = st.c[key]
        print(f"{key.rsplit(' ', 2)[0]} {rn}: {len(vals)} distinct values, {sum(vals.values())} writes")
        if a.regs:
            for v, c in vals.most_common(40):
                print(f"    {c:7}  {decode(reg, v)}")
    print(f"{len(st.errors)} errors")
    for e in st.errors[:40]:
        print("  " + e)
    return 1 if st.errors else 0


if __name__ == "__main__":
    sys.exit(main())
