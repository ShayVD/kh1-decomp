#!/usr/bin/env python3
"""Decode and check renderer B mesh command streams (VU1 programs P10-P20) in a
character model from the user's own disc, or in an EE RAM dump.

  python3 -I tools/vu/rb_stream.py FILE --mobj OFF [--ram] [-v]
  python3 -I tools/vu/rb_stream.py FILE --mesh OFF --g G [--ram] [-v]
  python3 -I tools/vu/rb_stream.py eeMemory.bin --scan --ram

--mobj OFF  walk every part of both part tables of the MOBJ chunk at byte
            offset OFF (in a .mdls, the MOBJ starts at section 1, usually 0x80)
--mesh OFF  walk one part's mesh chain (OFF = its first DMA tag); --g is the
            part record's byte +2 (it selects the record layout, below)
--ram       FILE is a 32 MB EE RAM dump (PCSX2 eeMemory.bin): the MOBJ offset
            fields and part chain pointers are absolute addresses (relocated in
            place at load); without it they are file-relative (MOBJ fields
            relative to the chunk, part chains relative to their part table)
--scan      walk every 16-byte aligned MOBJ/MENV chunk found in FILE
-v          print every record, not only the per-part summary

Record rule (docs/renderer-spec.md section 2.3, settled in session 17 from
func_0015fd20 and the P10-P20 code). A mesh chain is DMA CNT packets (the last
one may be END), each `STCYCL 1,1; UNPACK V4-32 n +TOPS; MSCNT`; the n unpacked
qwords are a list of records whose first qword is {u32 op, u32 arg, u32 z,
u32 w}:
  op 0       matrix slot: arg = bone, z = slot 0-2, w = palette mark (skinned
             programs). Length 1 + 4 qwords when g & 2, else 1 + 7 (lit or not).
  op 1       vertex group: arg = record length in bytes, z = vertex count,
             w = strip winding parity. Then a GIF tag and the vertices.
  op 2       bone index list (skinned programs only): arg = length in bytes.
  op 0x8000  end of this packet: arg = bytes to the next packet's first record
             (48: this qword, the MSCNT qword, the next DMA tag), 0 = last.
Vertex layouts checked here: g & 2 -> 1 qword (xyz, w = matrix slot; XYZ2-only
strips); g & 3 == 0 -> 3 qwords (normal + slot in w, position, STQ); g & 1 ->
skinned (1 + k + 1 qwords, k = influences in the first qword's w).

Standalone (Python >= 3.10, stdlib only), read-only. Prints offsets, opcodes
and counts, never vertex or matrix data. Output derives from the user's own
files: never commit it.
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

END_OP = 0x8000


class Mem:
    def __init__(self, data: bytes):
        self.d = data

    def u32(self, o: int) -> int:
        return struct.unpack_from("<I", self.d, o)[0]

    def s16(self, o: int) -> int:
        return struct.unpack_from("<h", self.d, o)[0]

    def q(self, o: int) -> tuple[int, int, int, int]:
        return struct.unpack_from("<4I", self.d, o)


def vertex_qwords(m: Mem, p: int, z: int, g: int) -> int | None:
    """Qwords of z vertices at p, or None if the layout does not fit."""
    if g & 2:
        return z
    if not g & 1:
        return 3 * z
    n = 0
    for _ in range(z):
        k = m.u32(p + n * 16 + 12)
        if not 1 <= k <= 8:
            return None
        n += k + 2
    return n


def walk_mesh(m: Mem, tag: int, g: int, verbose: bool, ind: str = "  ") -> tuple[dict, list[str]]:
    """Walk a mesh chain twice: by DMA tags and by the EE rule; cross-check."""
    stats = {"packets": 0, "records": 0, "op0": 0, "op1": 0, "op2": 0, "verts": 0}
    errs: list[str] = []
    op0_len = 5 if g & 2 else 8
    # 1. Packets by DMA tag.
    packets = []
    t = tag
    for _ in range(4096):
        lo, _hi, v0, v1 = m.q(t)
        qwc, tid = lo & 0xFFFF, lo >> 28 & 7
        if tid not in (1, 7):
            errs.append(f"tag {t:#x}: DMA id {tid}, expected CNT or END")
            break
        num = (v1 >> 16 & 0xFF) or 256
        if v0 != 0x01000101 or (v1 >> 24) & 0x7F != 0x6C or not v1 & 0x8000:
            errs.append(f"tag {t:#x}: VIF words {v0:08x} {v1:08x}, expected STCYCL 1,1; UNPACK V4-32 +TOPS")
        packets.append((t, qwc, num, tid))
        t += 16 + qwc * 16
        if tid == 7:
            break
    stats["packets"] = len(packets)
    # 2. Records by the EE rule (func_0015fd20), one pass over all packets.
    pi, p = 0, tag + 16
    bound = lambda i: packets[i][0] + 16 + packets[i][2] * 16  # end of unpacked data
    while pi < len(packets):
        op, arg, z, w = m.q(p)
        rel = p - packets[pi][0] - 16
        stats["records"] += 1
        line = f"{ind}  {p:08x} +{rel:#06x} "
        if op == 0:
            stats["op0"] += 1
            line += f"op 0 matrix: bone {arg}, slot {z}" + (f", w {w}" if w else "")
            if z > 2:
                errs.append(f"{p:#x}: op 0 slot {z} > 2")
            nxt = p + op0_len * 16
        elif op in (1, 2):
            stats[f"op{op}"] += 1
            if arg == 0 or arg & 15:
                errs.append(f"{p:#x}: op {op} length {arg:#x} not a positive qword multiple")
                break
            nxt = p + arg
            if op == 1:
                stats["verts"] += z
                gif = m.u32(p + 16)
                nv = vertex_qwords(m, p + 32, z, g)
                line += f"op 1 vertices: {z}, length {arg:#x}, parity {w}, GIF NLOOP {gif & 0x7FFF}"
                if gif & 0x7FFF != z:
                    errs.append(f"{p:#x}: GIF NLOOP {gif & 0x7FFF} != vertex count {z}")
                if nv is None or 2 + nv != arg // 16:
                    errs.append(f"{p:#x}: {z} vertices (g={g:#x}) do not fill {arg:#x} bytes")
                elif not g & 1:
                    step = 1 if g & 2 else 3
                    slots = {m.u32(p + 32 + 16 * step * j + 12) for j in range(z)}
                    if any(2 < s < 0x100 for s in slots):
                        errs.append(f"{p:#x}: vertex matrix slots {sorted(slots)} outside 0-2 / >= 0x100")
                if w > 1:
                    errs.append(f"{p:#x}: op 1 parity {w} > 1")
            else:
                line += f"op 2 bone indices: {z} qwords, length {arg:#x}"
                if arg // 16 != 1 + z:
                    errs.append(f"{p:#x}: op 2 length {arg:#x} != 1 + {z} qwords")
        elif op == END_OP:
            line += f"end, next +{arg:#x}" if arg else "end of mesh"
            if p + 16 != bound(pi):
                errs.append(f"{p:#x}: end record is not the last unpacked qword of packet {packets[pi][0]:#x}")
            if verbose:
                print(line)
            if arg == 0:
                if pi != len(packets) - 1:
                    errs.append(f"{p:#x}: end of mesh but {len(packets) - 1 - pi} packets remain")
                break
            pi += 1
            if pi >= len(packets):
                errs.append(f"{p:#x}: end jumps past the last packet")
                break
            nxt = p + arg
            if nxt != packets[pi][0] + 16:
                errs.append(f"{p:#x}: end jumps to {nxt:#x}, next packet data at {packets[pi][0] + 16:#x}")
            p = nxt
            continue
        else:
            errs.append(f"{p:#x}: unknown op {op:#x} (func_0015fd20 would spin)")
            break
        if verbose:
            print(line)
        if nxt > bound(pi):
            errs.append(f"{p:#x}: record runs past the packet's unpacked data")
            break
        p = nxt
    else:
        errs.append("walk ended without an end-of-mesh record")
    return stats, errs


def walk_mobj(m: Mem, h: int, ram: bool, verbose: bool) -> int:
    if m.d[h:h + 4] not in (b"MOBJ", b"MENV"):
        sys.exit(f"{h:#x}: not a MOBJ/MENV chunk")
    bad = 0
    for name, k in (("part table", 0x20), ("alt part table", 0x28)):
        if k == 0x28 and m.u32(h + 0x2C) == 0:
            continue
        t = m.u32(h + k) if ram else h + m.u32(h + k)
        nparts = m.u32(t + 0xC)
        print(f"{name} at {t:#x}: {nparts} parts")
        for i in range(nparts):
            r = t + 0x10 + 16 * i
            fl, pid, g = m.d[r], m.d[r + 1], m.d[r + 2]
            c = m.u32(r + 12) if ram else t + m.u32(r + 12)
            if verbose:
                print(f"  part {i}: chain {c:#x}")
            st, errs = walk_mesh(m, c, g, verbose)
            bad += len(errs)
            print(f"  part {i}: flags {fl:#x} id {pid} g {g:#x} chain {c:#x}: {st['packets']} packets, "
                  f"{st['records']} records (op0 {st['op0']}, op1 {st['op1']}, op2 {st['op2']}), "
                  f"{st['verts']} vertices, {'OK' if not errs else f'{len(errs)} errors'}")
            for e in errs[:8]:
                print("    " + e)
    return bad


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file", type=Path)
    ap.add_argument("--mobj", type=lambda s: int(s, 16))
    ap.add_argument("--mesh", type=lambda s: int(s, 16))
    ap.add_argument("--g", type=lambda s: int(s, 0), default=0)
    ap.add_argument("--ram", action="store_true")
    ap.add_argument("--scan", action="store_true")
    ap.add_argument("-v", action="store_true")
    a = ap.parse_args()
    m = Mem(a.file.read_bytes())
    if a.scan:
        bad = n = 0
        for tag in (b"MOBJ", b"MENV"):
            o = m.d.find(tag)
            while o >= 0:
                if o % 16 == 0:
                    print(f"== {tag.decode()} at {o:#x}")
                    bad += walk_mobj(m, o, a.ram, a.v)
                    n += 1
                o = m.d.find(tag, o + 4)
        print(f"{n} chunks, {bad} errors")
        return 1 if bad else 0
    if a.mobj is not None:
        return 1 if walk_mobj(m, a.mobj, a.ram, a.v) else 0
    if a.mesh is not None:
        st, errs = walk_mesh(m, a.mesh, a.g, a.v)
        print(st)
        for e in errs:
            print(e)
        return 1 if errs else 0
    ap.error("give --mobj or --mesh")
    return 2


if __name__ == "__main__":
    sys.exit(main())
