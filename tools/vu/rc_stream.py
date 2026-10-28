#!/usr/bin/env python3
"""Decode and check the Gummi engine's mesh batches (renderer C, the five VU1
programs C0-C4 that gb.x and wm.x upload; docs/renderer-spec.md section 2.5)
in the model archives extracted from the user's own disc.

  python3 -I tools/vu/rc_stream.py FILE... [--per-model] [-v]

FILE is a "TARC" archive of "MOPB" models (gumi/gumi.aml, the Gummi stage
files) or a single "MOPB" model. Each model's mesh groups (+0x98 count, +0x9C
offset; 0x28-byte records {parts, offset, bbox}) list parts (0x28 bytes:
{chain offset, bone, bbox}); each chain is a DMA CNT ... RET list of VIF
codes that upload one batch per MSCNT. The batch is checked against what
the VU code reads: the header, the position / normal ranges, the command
list, and every index qword.

Standalone (Python >= 3.10, stdlib only), read-only. Prints counts and
histograms only, not file contents. Output derives from the user's files:
never commit it.
"""
from __future__ import annotations

import argparse
import struct
import sys
from collections import Counter
from pathlib import Path

DMA_ID = ["REFE", "CNT", "NEXT", "REF", "REFS", "CALL", "RET", "END"]
PRIMS = ["POINT", "LINE", "LINE_STRIP", "TRI", "TRI_STRIP", "TRI_FAN", "SPRITE", "?"]
OUT_QW = 0x130          # one output buffer (qwords); a run's space must fit


def prim_str(p: int) -> str:
    s = PRIMS[p & 7]
    for bit, name in ((3, "IIP"), (4, "TME"), (5, "FGE"), (6, "ABE"), (7, "AA1"), (8, "FST"), (9, "CTXT2")):
        if p >> bit & 1:
            s += "+" + name
    return s


class Stats:
    def __init__(self) -> None:
        self.c: dict[str, Counter] = {}
        self.errors: list[str] = []

    def add(self, key: str, val, n: int = 1) -> None:
        self.c.setdefault(key, Counter())[val] += n


class Vif:
    """VIF1 as the Gummi chains use it: STCYCL, STMASK, STROW, masked UNPACKs
    relative to TOPS (taken as 0), FLUSHA and MSCNT."""

    def __init__(self, st: Stats, where: str) -> None:
        self.st, self.where = st, where
        self.cl = self.wl = 1
        self.mask = 0
        self.row = [0, 0, 0, 0]
        self.mem: dict[int, list[int]] = {}
        self.batches = 0
        self.group = -1

    def err(self, msg: str) -> None:
        self.st.errors.append(f"{self.where}: {msg}")

    def unpack(self, d: bytes, a: int, cmd: int, imm: int, num: int) -> int:
        vn, vl = cmd >> 2 & 3, cmd & 3
        if vl == 3:
            self.err("V4-5 UNPACK")
            return a + (num * 2 + 3) // 4 * 4
        if not imm & 0x8000:
            self.err("UNPACK without FLG (absolute VU address)")
        usn = imm >> 14 & 1
        size = [4, 2, 1][vl]
        fmt = {4: "<i", 2: "<h", 1: "<b"}[size] if not usn else {4: "<I", 2: "<H", 1: "<B"}[size]
        self.st.add("UNPACK format", f"V{vn + 1}-{[32, 16, 8][vl]}{' usn' if usn else ''}{' masked' if cmd & 0x10 else ''}")
        if self.wl > self.cl:
            self.err(f"filling write cycle cl={self.cl} wl={self.wl}")
        base = imm & 0x3FF
        p = a
        for i in range(num):
            vals = []
            for _ in range(vn + 1):
                vals.append(struct.unpack_from(fmt, d, p)[0] & 0xFFFFFFFF)
                p += size
            if vn == 1:
                vals = vals + vals
            elif vn == 0:
                vals = vals * 4
            elif vn == 2:
                vals = vals + [0]
            addr = base + (i // self.wl) * self.cl + i % self.wl
            q = self.mem.setdefault(addr, [None] * 4)
            cyc = min(i % self.wl, 3)
            for k in range(4):
                m = self.mask >> (2 * k + 8 * cyc) & 3 if cmd & 0x10 else 0
                if m == 0 and not (vn == 2 and k == 3):     # V3 leaves w alone unless masked
                    q[k] = vals[k]
                elif m == 1:
                    q[k] = self.row[k]
                elif m == 2:
                    self.err("UNPACK mask selects STCOL")
        return a + (p - a + 3) // 4 * 4

    def run(self, d: bytes, a: int, end: int) -> None:
        while a < end:
            c = struct.unpack_from("<I", d, a)[0]
            cmd, imm, num = c >> 24 & 0x7F, c & 0xFFFF, c >> 16 & 0xFF
            a += 4
            if cmd >= 0x60:
                a = self.unpack(d, a, cmd, imm, num or 256)
                continue
            self.st.add("VIF code", f"{cmd:#04x}")
            if cmd == 0:
                pass
            elif cmd == 0x01:
                self.cl, self.wl = imm & 0xFF, imm >> 8
                self.st.add("STCYCL cl,wl", (self.cl, self.wl))
            elif cmd == 0x20:
                self.mask = struct.unpack_from("<I", d, a)[0]
                self.st.add("STMASK", f"{self.mask:#010x}")
                a += 4
            elif cmd == 0x30:
                self.row = list(struct.unpack_from("<4I", d, a))
                self.st.add("STROW", tuple(f"{x:#x}" for x in self.row))
                a += 16
            elif cmd in (0x10, 0x11, 0x13):
                pass
            elif cmd == 0x17:
                self.batch()
                self.mem.clear()
            else:
                self.err(f"unexpected VIF code {c:#010x}")
                return
        if self.mem:
            self.err("UNPACKs after the last MSCNT")

    def q(self, addr: int) -> list[int] | None:
        v = self.mem.get(addr)
        return v if v is not None and None not in v else None

    def batch(self) -> None:
        st = self.st
        self.batches += 1
        st.add("batches", "n")
        h = self.mem.get(0)
        if h is None or None in h:
            self.err("MSCNT with no header")
            return
        nx, ny, nz, cl = h
        st.add("header x (leading qwords)", nx)
        st.add("vertices (y) per batch", min(ny // 16 * 16, 128))
        st.add("positions", "n", ny)
        st.add("normals", "n", nz)
        pos = range(1 + nx, 1 + nx + ny)
        nrm = range(1 + nx + ny, 1 + nx + ny + nz)
        for r, what in ((pos, "position"), (nrm, "normal")):
            for i in r:
                if self.q(i) is None:
                    self.err(f"{what} qword {i} not written")
                    return
        # C0-C2 store each position's outcode in the w of qword (position + y)
        if pos and pos[-1] + ny >= cl:
            self.err(f"outcode slots reach the command list (pos end {pos[-1]} + {ny} >= {cl})")
        st.add("positions' w", "1.0" if all(self.mem[i][3] == 0x3F800000 for i in pos) else "other")
        a = cl
        groups = 0
        while True:
            g = self.q(a)
            if g is None:
                self.err(f"command list qword {a} not written")
                return
            runs, mat, dbl, _ = g
            a += 1
            if runs == 0:
                break
            groups += 1
            st.add("group material m", mat)
            st.add("group double-sided (z)", f"{dbl:#x}")
            uv = self.q(a)
            if uv is None:
                self.err(f"UV-slot qword {a} not written")
                return
            st.add("group UV-scroll slot", uv[0])
            a += 1
            if mat:
                t0, t1 = self.q(a), self.q(a + 1)
                if t0 is None or t1 is None:
                    self.err("material qwords not written")
                    return
                lo = t0[0] | t0[1] << 32
                regs = t0[2] | t0[3] << 32
                st.add("material qword 0 (GIF tag) NLOOP/NREG/FLG/EOP",
                       (lo & 0x7FFF, lo >> 60 & 0xF, lo >> 58 & 3, lo >> 15 & 1))
                st.add("material qword 0 REGS", f"{regs:#x}")
                tex0 = t1[0] | t1[1] << 32
                psm = {0: "CT32", 2: "CT16", 0x13: "T8", 0x14: "T4"}.get(tex0 >> 20 & 0x3F, "?")
                st.add("material TEX0 PSM / TW x TH", (psm, 1 << (tex0 >> 26 & 0xF), 1 << (tex0 >> 30 & 0xF)))
                st.add("material TEX0 TCC/TFX/CLD", (tex0 >> 34 & 1, tex0 >> 35 & 3, tex0 >> 61 & 7))
                a += 2
            for _ in range(runs):
                rq = self.q(a)
                tag = self.q(a + 1)
                if rq is None or tag is None:
                    self.err(f"run qwords at {a} not written")
                    return
                nv, ns, space, total = rq
                a += 2
                lo = tag[0] | tag[1] << 32
                regs = tag[2] | tag[3] << 32
                prim = lo >> 47 & 0x7FF
                st.add("run GIF tag PRIM", prim_str(prim) if lo >> 46 & 1 else "no PRE")
                st.add("mesh group / run PRIM", (self.group, prim_str(prim)))
                st.add("run GIF tag REGS (NREG)", f"{regs & ((1 << 4 * (lo >> 60 & 0xF)) - 1):#x} ({lo >> 60 & 0xF})")
                st.add("group m / run REGS", (mat, f"{regs & 0xFFF:#x}"))
                st.add("run strip length", nv)
                if lo & 0x7FFF != nv:
                    self.err(f"run GIF NLOOP {lo & 0x7FFF} != strip length {nv}")
                if total != nv * ns:
                    self.err(f"run w {total} != {nv} x {ns}")
                st.add("run space z - (6 x strip length + 1)", space - (6 * nv + 1))
                if space > OUT_QW:
                    self.err(f"run space {space} > one output buffer")
                for _k in range(nv * ns):
                    iq = self.q(a)
                    if iq is None:
                        self.err(f"index qword {a} not written")
                        return
                    p, c, s, m = iq
                    if p not in pos:
                        self.err(f"position index {p} outside {pos.start}..{pos.stop - 1}")
                    if c not in nrm:
                        self.err(f"colour index {c} outside the normals {nrm.start}..{nrm.stop - 1}")
                    for v, what in ((s, "ST"), (m, "multiplier")):
                        if self.q(v) is None:
                            self.err(f"{what} index {v} not a written qword")
                        elif v in pos or v in nrm:
                            st.add(f"{what} index inside positions/normals", "yes")
                        elif v >= cl:
                            st.add(f"{what} index after the command list", "yes")
                        elif v <= nx:
                            st.add(f"{what} index in", "leading")
                        else:
                            st.add(f"{what} index in", "after the normals")
                    a += 1
        st.add("groups per batch", groups)
        st.add("index qwords end -> next upload", "ok")


def walk_chain(st: Stats, d: bytes, mb: int, off: int, where: str, group: int) -> None:
    v = Vif(st, where)
    v.group = group
    a = mb + off
    for _ in range(4096):
        if a + 16 > len(d):
            v.err("chain runs past the file")
            return
        w0, w1 = struct.unpack_from("<II", d, a)
        tid, qwc = w0 >> 28 & 7, w0 & 0xFFFF
        st.add("DMA tag", DMA_ID[tid])
        if tid == 1:
            v.run(d, a + 8, a + 16 + qwc * 16)      # the tag's upper words are VIF codes too
            a += 16 + qwc * 16
        elif tid == 6:
            v.run(d, a + 8, a + 16)
            st.add("batches per part", min(v.batches, 8))
            return
        else:
            v.err(f"DMA {DMA_ID[tid]} in a chain")
            return
    v.err("chain without RET")


def walk_model(st: Stats, d: bytes, mb: int, where: str) -> None:
    ng, go = struct.unpack_from("<II", d, mb + 0x98)
    nb = struct.unpack_from("<I", d, mb + 0x90)[0]
    st.add("models", "n")
    st.add("bones per model", min(nb, 64))
    st.add("mesh groups per model", min(ng, 64))
    for gi in range(ng):
        np_, po = struct.unpack_from("<II", d, mb + go + 0x28 * gi)
        st.add("parts per group", min(np_, 16))
        st.add("mesh group used", (gi, np_ > 0))
        for pi in range(np_):
            co, bone = struct.unpack_from("<Ii", d, mb + po + 0x28 * pi)
            if not 0 <= bone < max(nb, 1):
                st.errors.append(f"{where} group {gi} part {pi}: bone {bone} of {nb}")
            walk_chain(st, d, mb, co, f"{where} group {gi} part {pi}", gi)


def walk_tarc(st: Stats, d: bytes, base: int, where: str) -> int:
    """TARC: {"TARC", 1, 0, 0x18, count, ...} then count {offset, size} pairs at +0x18
    (offsets from the archive); entries are MOPB models or nested TARCs."""
    n = struct.unpack_from("<I", d, base + 0x10)[0]
    models = 0
    for i in range(n):
        o, _size = struct.unpack_from("<II", d, base + 0x18 + 8 * i)
        o += base
        tag = d[o:o + 4]
        if tag == b"MOPB":
            walk_model(st, d, o, f"{where}[{i}]")
            models += 1
        elif tag == b"TARC":
            models += walk_tarc(st, d, o, f"{where}[{i}]")
        else:
            st.add("other TARC entries", tag.decode("latin-1"))
    return models


def survey(path: Path, st: Stats) -> int:
    d = path.read_bytes()
    if d[:4] == b"MOPB":
        walk_model(st, d, 0, path.name)
        return 1
    if d[:4] != b"TARC":
        st.errors.append(f"{path.name}: neither TARC nor MOPB")
        return 0
    return walk_tarc(st, d, 0, path.name)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("paths", nargs="+", type=Path)
    ap.add_argument("--per-model", action="store_true", help="print each file's model count")
    ap.add_argument("-v", action="store_true", help="print every error, not the first 20")
    a = ap.parse_args()
    st = Stats()
    for p in a.paths:
        n = survey(p, st)
        if a.per_model:
            print(f"{p.name}: {n} models")
    for k in sorted(st.c):
        items = sorted(st.c[k].items(), key=lambda kv: (-kv[1], str(kv[0])))
        print(f"{k}: " + ", ".join(f"{v}: {c}" for v, c in items[:16]) + (" ..." if len(items) > 16 else ""))
    for e in st.errors[: None if a.v else 20]:
        print("error:", e)
    print(f"{len(st.errors)} errors")
    return 1 if st.errors else 0


if __name__ == "__main__":
    sys.exit(main())
