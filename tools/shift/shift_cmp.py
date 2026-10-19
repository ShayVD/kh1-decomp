#!/usr/bin/env python3
"""Inverse-map comparator for the moved shiftable links (docs/shiftable-plan.md, step 8).

  python3 -I tools/shift/shift_cmp.py --ref out/shift --new out/shift/m1 [--examples 3]

REF is the M0 link (original addresses, verified byte-identical to the
original ELF by `shift_elf.py verify`), NEW an M1 (code rotated) or M2 (data
and bss moved) link of the same objects. Both are linked with `ld -q`, so the
relocations stay in the output. The address map old -> new is built from the
two link maps: every input section (function, blob chunk, rodata block) is a
piece with its REF and NEW address; padding after a piece moves with it;
.bss moves with D_BSS; anything outside the image does not move.

Checks, each failure attributed to the source file of its input section:

1. relocated fields: every R_MIPS_32 / R_MIPS_26 / HI16+LO16 pair of REF,
   read at its NEW place, must be the REF value mapped through old -> new
   (an address at a piece boundary may map with either neighbour);
2. every other byte of every piece must be identical;
3. position-dependent code: unrelocated j/jal, and unrelocated lui + addiu/
   ori/load/store pairs, whose address moved (the field should have been a
   relocation: hand-written asm, hard-coded addresses in C);
4. (informational) unrelocated data words whose value is an address that
   moved: pointers data_relocs.tsv rejected or never saw, grouped by its
   reason code. A real pointer among them is a run-time bug the static
   checks cannot see.

Exit status 1 if 1-3 find anything."""
from __future__ import annotations

import argparse
import bisect
import collections
import re
import struct
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import kh1tool as K  # noqa: E402
import mips  # noqa: E402
from elf32 import R_MIPS_26, R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16, Elf  # noqa: E402

IMAGE_LO, IMAGE_HI = 0x00100000, 0x00675018
MAP_ONE = re.compile(r"^ (\.\S+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)$")
MAP_NAME = re.compile(r"^ (\.\S+)$")
MAP_REST = re.compile(r"^\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)$")
MAP_OUT = re.compile(r"^(\.\S+|/DISCARD/)\b")


def read_map(path: Path, outs: tuple[str, ...] = (".text", ".data")) -> dict[tuple[str, str], tuple[int, int, str]]:
    """(object, input section) -> (address, size, output section), for .text and .data.
    Each mode has its own blob.o; it is keyed as `out/shift/blob.o`."""
    out = Norm()
    cur_out, pending = None, None
    for line in path.read_text().splitlines():
        m = MAP_OUT.match(line)
        if m:
            cur_out = m.group(1)
            pending = None
            continue
        if cur_out not in outs:
            continue
        m = MAP_ONE.match(line)
        if m:
            out[(m.group(4), m.group(1))] = (int(m.group(2), 16), int(m.group(3), 16), cur_out)
            pending = None
            continue
        m = MAP_NAME.match(line)
        if m:
            pending = m.group(1)
            continue
        m = MAP_REST.match(line)
        if m and pending:
            out[(m.group(3), pending)] = (int(m.group(1), 16), int(m.group(2), 16), cur_out)
        pending = None
    return out


class Norm(dict):
    def __setitem__(self, key, value):
        obj, sec = key
        if obj.startswith("out/shift/") and obj.endswith("/blob.o"):
            obj = "out/shift/blob.o"
        if obj.startswith("out/shift/") and "/variants/" in obj:
            # KH1_SHIFTABLE / KH1_OVL_FIXUPS variant objects (out/shift/[<mode>/]variants/<obj>)
            # stand in for <obj>: key them as the object they replace, so the same input
            # section matches whether or not a mode builds a variant of its file
            obj = obj.split("/variants/", 1)[1]
        super().__setitem__((obj, sec), value)


def source_of(obj: str) -> str:
    s = obj
    for pre in ("out/shift/variants/", "out/build/"):
        if s.startswith(pre):
            s = s[len(pre):]
    if s.startswith("out/shift/asm/"):
        s = "asm export " + s[len("out/shift/asm/"):]  # SHIFT_ASM_DIR/<name>.s, or the temporary unplaced.s
    if s.startswith("out/shift") and s.endswith("blob.o"):
        return "data blob"
    return s[:-2] if s.endswith(".o") else s


class Image:
    def __init__(self, elf: Elf):
        self.secs = [(s.addr, elf.section_bytes(s)) for s in elf.sections
                     if s.flags & 2 and s.type != 8 and s.size and s.name in (".text", ".data")]
        self.secs.sort()

    def word(self, addr: int) -> int | None:
        for a, b in self.secs:
            if a <= addr and addr + 4 <= a + len(b):
                return struct.unpack_from("<I", b, addr - a)[0]
        return None

    def bytes(self, addr: int, n: int) -> bytes:
        for a, b in self.secs:
            if a <= addr and addr + n <= a + len(b):
                return b[addr - a: addr - a + n]
        raise ValueError(f"0x{addr:08x}+0x{n:x} not in the image")


class AddrMap:
    def __init__(self, pieces: list[tuple[int, int, int]], ends: list[tuple[int, int, int]]):
        """pieces: (ref start, ref end of the covered range, new start)."""
        self.p = sorted(pieces)
        self.starts = [x[0] for x in self.p]
        self.ends = ends  # inclusive end pieces: (ref end, new end) for boundary values
        self.extra: dict[int, int] = {}  # boundary values with one more valid image (_end, SHIFT_FLOAT)

    def fwd(self, a: int) -> set[int]:
        if a in self.extra:
            return self._fwd(a) | {self.extra[a]}
        return self._fwd(a)

    def _fwd(self, a: int) -> set[int]:
        i = bisect.bisect_right(self.starts, a) - 1
        out = set()
        if i >= 0 and a < self.p[i][1]:
            out.add((a - self.p[i][0] + self.p[i][2]) & 0xFFFFFFFF)
            if a == self.p[i][0] and i > 0 and self.p[i - 1][1] == a:
                out.add((a - self.p[i - 1][0] + self.p[i - 1][2]) & 0xFFFFFFFF)
            return out
        if i >= 0 and a == self.p[i][1]:  # end of the last piece of a region
            return {(a - self.p[i][0] + self.p[i][2]) & 0xFFFFFFFF}
        return {a}

    def moved(self, a: int) -> bool:
        return a not in self.fwd(a)



class Links:
    """The REF (M0) and NEW links and the old -> new address map between them
    (also used by tools/shift/ovl_proof.py)."""

    def __init__(self, ref: Path, new: Path):
        self.ref_elf, self.new_elf = (Elf.load(d / "kh1-shift.linked.elf") for d in (ref, new))
        self.ref_map, self.new_map = (read_map(d / "kh1-shift.map") for d in (ref, new))
        # SHIFT_DRAFTS: a draft's .text.<name> stands in for the asm export's section of
        # that name (drafts.tsv, written by shift_ld.py); it is mapped, never compared.
        self.drafted: dict[tuple[str, str], str] = {}
        dt = new / "drafts.tsv"
        if dt.exists():
            for line in dt.read_text().splitlines()[1:]:
                name, _addr, status, draft, asm = line.split("\t")[:5]
                key = (draft, f".text.{name}")
                if status == "linked" and key in self.new_map:
                    self.new_map[(asm, key[1])] = self.new_map.pop(key)
                    self.drafted[(asm, key[1])] = draft
        self.ref_img, self.new_img = Image(self.ref_elf), Image(self.new_elf)
        self.rsym = rsym = {s.name: s.value for s in self.ref_elf.symbols() if s.name}
        self.nsym = nsym = {s.name: s.value for s in self.new_elf.symbols() if s.name}
        missing = [k for k in self.ref_map if k not in self.new_map]
        if missing:
            raise ValueError(f"{len(missing)} input sections of the M0 link are not in this link, e.g. {missing[:3]}")
        secs = sorted((r[0], r[1], self.new_map[k][0], k, r[2]) for k, r in self.ref_map.items() if r[1])
        out_end = {}
        for s in self.ref_elf.sections:
            if s.name in (".text", ".data"):
                out_end[s.name] = s.addr + s.size
        pieces = []
        for i, (ra, size, na, key, osec) in enumerate(secs):
            nxt = secs[i + 1][0] if i + 1 < len(secs) and secs[i + 1][4] == osec else out_end[osec]
            pieces.append((ra, max(nxt, ra + size), na))
        pieces.append((rsym["_edata"], rsym["D_BSS"], nsym["_edata"]))
        # .bss moves with D_BSS, except variables C defines that NEW links elsewhere
        # (SHIFT_FLOAT): each is its own piece, and the rest of .bss is split around them.
        rb, nb = (read_map(d / "kh1-shift.map", (".bss",)) for d in (ref, new))
        delta = nsym["D_BSS"] - rsym["D_BSS"]
        floated = sorted((r[0], r[0] + r[1], nb[k][0]) for k, r in rb.items()
                         if r[1] and k in nb and nb[k][0] - r[0] != delta)
        cur = rsym["D_BSS"]
        for fa, fe, na in floated:
            if fa > cur:
                pieces.append((cur, fa, cur + delta))
            pieces.append((fa, fe, na))
            cur = fe
        pieces.append((cur, rsym["_end"], cur + delta))
        self.floated_bss = floated
        self.secs = secs
        self.amap = AddrMap(pieces, [])
        if floated:  # the floated variables sit before the new _end (crt0's clear end, heap start)
            self.amap.extra[rsym["_end"]] = nsym["_end"]


def sext(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ref", type=Path, default=K.OUT / "shift")
    ap.add_argument("--new", type=Path, required=True)
    ap.add_argument("--data-relocs", type=Path, default=K.ROOT / "data_relocs.tsv")
    ap.add_argument("--examples", type=int, default=3)
    a = ap.parse_args()
    mode = a.new.name.upper()
    try:
        L = Links(a.ref, a.new)
    except ValueError as e:
        print(f"{mode} FAIL: {e}")
        return 1
    ref_elf, new_elf, ref_map, new_map = L.ref_elf, L.new_elf, L.ref_map, L.new_map
    ref_img, new_img, rsym, nsym, secs, amap = L.ref_img, L.new_img, L.rsym, L.nsym, L.secs, L.amap

    # ---- relocations of REF, per input section
    relocs = []
    for s in ref_elf.sections:
        if s.name in (".text", ".data"):
            relocs += ref_elf.relocations(s)
    relocs.sort()
    roffs = [r[0] for r in relocs]

    def src_of_addr(ref_addr: int) -> str:
        i = bisect.bisect_right(secs, (ref_addr, 1 << 40)) - 1
        return source_of(secs[i][3][0]) if i >= 0 else "?"

    # Input sections whose size differs from M0 (a shift-only hook that grew a
    # function) cannot be compared; they are listed. The KH1_OVL_FIXUPS hook does not
    # grow anything: it swaps a jal FlushCache for a jal kh1_ovl_flush0 (accepted below).
    hooked = [(ra, key[1]) for ra, size, na, key, osec in secs if new_map[key][1] != size]
    hook_from, hook_to = rsym.get("FlushCache"), nsym.get("kh1_ovl_flush0")
    hooked = [(ra, n) for ra, n in hooked if not any(k[1] == n for k in L.drafted)]
    drafted_at = {ra for ra, size, na, key, osec in secs if key in L.drafted}
    hooked_at = {ra for ra, _n in hooked} | drafted_at
    bad_fields = collections.defaultdict(list)
    bad_bytes = collections.defaultdict(list)
    absolute = collections.defaultdict(list)
    checked = collections.Counter()
    unpaired = 0
    consts = 0
    for ra, size, na, (obj, isec), osec in secs:
        if ra in hooked_at:
            continue
        src = source_of(obj)
        lo_i, hi_i = bisect.bisect_left(roffs, ra), bisect.bisect_left(roffs, ra + size)
        rs_ = relocs[lo_i:hi_i]
        rb = bytearray(ref_img.bytes(ra, size))
        nb = bytearray(new_img.bytes(na, size))
        fields: dict[int, int] = {}  # offset in piece -> mask
        his = [(off, si) for off, typ, si in rs_ if typ == R_MIPS_HI16]

        def hi_reg(ho: int) -> int:
            return mips.rt(struct.unpack_from("<I", rb, ho - ra)[0])
        for off, typ, si in rs_:
            o = off - ra
            if o + 4 > size:
                continue
            rw = struct.unpack_from("<I", rb, o)[0]
            nw = struct.unpack_from("<I", nb, o)[0]
            ok, what = True, ""
            if typ == R_MIPS_32:
                fields[o] = 0xFFFFFFFF
                ok = nw in amap.fwd(rw)
                what = f"word 0x{rw:08x} -> 0x{nw:08x}"
            elif typ == R_MIPS_26:
                fields[o] = 0x03FFFFFF
                rt_ = ((off + 4) & 0xF0000000) | ((rw & 0x3FFFFFF) << 2)
                nt_ = ((na + o + 4) & 0xF0000000) | ((nw & 0x3FFFFFF) << 2)
                ok = nt_ in amap.fwd(rt_)
                what = f"jump 0x{rt_:08x} -> 0x{nt_:08x}"
                if not ok and hook_to is not None and rt_ == hook_from and nt_ == hook_to:
                    # the argument (delay slot or the word before) passes the request
                    # instead of 0: move a0,zero -> move a0,rX
                    for ao in (o + 4, o - 4):
                        if 0 <= ao and ao + 4 <= size:
                            rd_ = struct.unpack_from("<I", rb, ao)[0]
                            nd_ = struct.unpack_from("<I", nb, ao)[0]
                            if rd_ == 0x0000202D and nd_ & ~(0x1F << 21) == 0x0000202D:
                                fields[ao] = 0xFFFFFFFF
                                checked["KH1_OVL_FIXUPS hook (jal FlushCache(0) -> kh1_ovl_flush0(req))"] += 1
                                ok = True
                                break
                    if ok:
                        continue
            elif typ == R_MIPS_HI16:
                fields[o] = 0xFFFF
                continue  # checked through its low halves
            elif typ == R_MIPS_LO16:
                fields[o] = 0xFFFF
                reg = mips.rs(rw)
                # its HI16: same symbol and register (latest before it, else after it),
                # then same symbol, then same register
                before = [h for h in reversed(his) if h[0] < off]
                after = [h for h in his if h[0] > off]
                hi = None
                for test in (lambda h: h[1] == si and hi_reg(h[0]) == reg, lambda h: h[1] == si,
                             lambda h: hi_reg(h[0]) == reg):
                    hi = next((h[0] for h in before + after if test(h)), None)
                    if hi is not None:
                        break
                if hi is None:
                    unpaired += 1
                    continue
                rh = struct.unpack_from("<I", rb, hi - ra)[0]
                nh = struct.unpack_from("<I", nb, hi - ra)[0]
                rfull = (((rh & 0xFFFF) << 16) + sext(rw & 0xFFFF)) & 0xFFFFFFFF
                nfull = (((nh & 0xFFFF) << 16) + sext(nw & 0xFFFF)) & 0xFFFFFFFF
                ok = nfull in amap.fwd(rfull)
                what = f"%hi/%lo 0x{rfull:08x} -> 0x{nfull:08x}"
            else:
                checked[f"type {typ} (not checked)"] += 1
                fields[o] = 0xFFFFFFFF
                continue
            checked[{R_MIPS_32: "R_MIPS_32", R_MIPS_26: "R_MIPS_26", R_MIPS_LO16: "HI16/LO16"}[typ]] += 1
            if not ok:
                bad_fields[src].append(f"0x{off:08x}->0x{na + o:08x} {what}")
        # 2: everything else identical
        for o, mask in fields.items():
            for buf in (rb, nb):
                w = struct.unpack_from("<I", buf, o)[0] & ~mask & 0xFFFFFFFF
                struct.pack_into("<I", buf, o, w)
        if rb != nb:
            n_diff = sum(1 for o in range(0, size - size % 4, 4) if rb[o:o + 4] != nb[o:o + 4])
            first = next(o for o in range(0, size) if rb[o] != nb[o])
            bad_bytes[src].append(f"{isec}: {n_diff} words differ, first at 0x{ra + first:08x}")
        # 3: position-dependent code
        if osec == ".text":
            words = struct.unpack_from(f"<{size // 4}I", ref_img.bytes(ra, size - size % 4))
            for k, w in enumerate(words):
                o = 4 * k
                if o in fields:
                    continue
                op = mips.op(w)
                if op in (mips.OP_J, mips.OP_JAL):
                    t = ((ra + o + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                    if IMAGE_LO <= t < IMAGE_HI and amap.moved(t):
                        absolute[src].append(f"0x{ra + o:08x} {'jal' if op == 3 else 'j'} 0x{t:08x}")
                elif op == mips.OP_LUI and IMAGE_LO >> 16 <= (w & 0xFFFF) <= IMAGE_HI >> 16:
                    reg = mips.rt(w)
                    for j in range(k + 1, min(k + 9, len(words))):
                        u = words[j]
                        if 4 * j in fields:
                            continue
                        uo = mips.op(u)
                        if mips.rs(u) == reg and uo != 0 and (uo in (0x09, 0x0D) or uo in mips.OP_LOADS or uo in mips.OP_STORES
                                                  or uo in (mips.OP_LQ, mips.OP_SQ) or uo in mips.OP_VU_MEM):
                            full = ((w & 0xFFFF) << 16) + (u & 0xFFFF if uo == 0x0D else sext(u & 0xFFFF))
                            if uo == 0x0D and (not src.endswith(".s") or full % 4):
                                consts += 1  # gcc never builds an address with ori: a constant
                            elif IMAGE_LO <= full <= IMAGE_HI and amap.moved(full):
                                kind = "lui/ori" if uo == 0x0D else ("lui/addiu" if uo == 0x09 else "lui/mem")
                                absolute[src].append(f"0x{ra + o:08x} {kind} 0x{full:08x}")
                            break
                        if uo == 0 and mips.funct(u) in (0x21, 0x2D) and mips.rd(u) == reg \
                                and reg in (mips.rs(u), mips.rt(u)):
                            continue  # addu rX,rX,index keeps the %hi (table indexing)
                        if (uo in K.GPR_RT_WRITERS and mips.rt(u) == reg) or (uo == 0 and mips.rd(u) == reg):
                            break

    # 4: data words left absolute although their value moved
    reasons = {}
    if a.data_relocs.exists():
        for line in a.data_relocs.read_text().splitlines():
            if line and not line.startswith(("#", "offset")):
                p = line.split("\t")
                reasons[rsym["D_BLOB"] + int(p[0], 16)] = (p[4], p[5])
    loose = collections.Counter()
    loose_ex = collections.defaultdict(list)
    for ra, size, na, (obj, isec), osec in secs:
        if osec != ".data" or not isec.startswith(".blob."):
            continue
        lo_i, hi_i = bisect.bisect_left(roffs, ra), bisect.bisect_left(roffs, ra + size)
        rel_at = {r[0] for r in relocs[lo_i:hi_i]}
        first = ra + (-ra % 4)
        for x in range(first, ra + size - 3, 4):
            if x in rel_at:
                continue
            v = ref_img.word(x)
            for hb in (0, 0x20000000, 0x30000000):
                t = v - hb
                if IMAGE_LO <= t <= IMAGE_HI and amap.moved(t):
                    tier, why = reasons.get(x, ("-", "not listed (unaligned-target noise or not a candidate)"))
                    key = why if tier == "-" else f"rejected: {why}"
                    if tier not in ("x", "-"):
                        key = f"tier {tier} above SHIFT_RELOC_TIER: {why}"
                    if hb:
                        key += f", through the 0x{hb:08x} mirror"
                    elif t % 4:
                        key += ", unaligned target"
                    loose[key] += 1
                    if len(loose_ex[key]) < a.examples:
                        loose_ex[key].append(f"0x{x:08x}")
                    break

    # ---- report
    ok = not bad_fields and not bad_bytes and not absolute
    ent_ok = new_elf.entry in amap.fwd(ref_elf.entry)
    sym_ok = all(nsym[n] in amap.fwd(rsym[n]) for n in ("_gp", "D_BLOB", "D_BSS", "_end"))
    ok = ok and ent_ok and sym_ok
    moved = sum(1 for ra, size, na, *_ in secs if ra != na)
    print(f"{mode} {'OK' if ok else 'FAIL'}: {len(secs)} input sections ({moved} moved), "
          f"relocated fields checked: " + ", ".join(f"{k} {v}" for k, v in sorted(checked.items()))
          + (f"; {unpaired} LO16 without a HI16 (skipped)" if unpaired else ""))
    print(f"  entry 0x{ref_elf.entry:08x} -> 0x{new_elf.entry:08x} {'ok' if ent_ok else 'WRONG'}; "
          f"_gp 0x{rsym['_gp']:08x} -> 0x{nsym['_gp']:08x}, D_BSS 0x{rsym['D_BSS']:08x} -> 0x{nsym['D_BSS']:08x}"
          f"{'' if sym_ok else ' WRONG'}")

    def group(title: str, d: dict[str, list[str]]) -> None:
        if not d:
            print(f"  {title}: none")
            return
        print(f"  {title}: {sum(len(v) for v in d.values())} in {len(d)} files")
        for src, items in sorted(d.items(), key=lambda kv: -len(kv[1])):
            print(f"    {len(items):6d}  {src}: " + "; ".join(items[:a.examples]))
    if hooked:
        print(f"  not compared (KH1_OVL_FIXUPS hook added, size differs from M0 by design): "
              + ", ".join(n for _a, n in hooked))
    if L.drafted:
        print(f"  not compared (SHIFT_DRAFTS: near-miss C drafts in place of their asm exports, never matched; "
              f"static diff by tools/shift/drafts.py report): {len(L.drafted)} functions")
    group("relocated fields that do not map back", bad_fields)
    group("other bytes differing", bad_bytes)
    group("position-dependent code (unrelocated address that moved)", absolute)
    if consts:
        print(f"  ({consts} unrelocated lui/ori pairs ignored as constants: in C (gcc builds addresses with addiu), "
              f"or an unaligned value in asm)")
    total = sum(loose.values())
    print(f"  data words not relocated whose value is a moved address: {total} (informational)")
    for k, n in loose.most_common():
        print(f"    {n:6d}  {k}: e.g. {', '.join(loose_ex[k])}")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
