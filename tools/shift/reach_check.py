#!/usr/bin/env python3
"""Find code that reaches a floated variable through another object's address (phase 4).

  python3 -I tools/shift/reach_check.py [--ld out/shift/m12-float/kh1-shift.ld] [--out FILE]
                                        [--elf SLPS_251.98] [--overlays out/overlays] [--all]

cover_check.py only sees names. Code also reaches fields by displacement from a
base it built with lui/addiu: `addiu a0,%lo(D_00575940)` then `lb a1,0x66(a0)`
reads D_005759A6 even though no relocation names it. When the base and the field
end up in different pieces of the float layout (a floated variable or run, or the
part that stays in place), the relocated base no longer leads to the field.

Each function of the original ELF (layout.tsv) gets a forward constant
propagation over its control-flow graph (registers holding a known address;
calls clobber the caller-saved ones). Every load, store or `addiu` from a known
base B at B+d is an access; it is a hazard when B and B+d are in different
pieces. A base that is added to an unknown register is an indexed access: listed
with --all when B is in a floated piece (its real extent is unknown).

The overlays (out/overlays/*.x, loaded at 0x00F20000 with their code
self-relative) are scanned the same way, as one straight-line region each.

Output: one line per (base, target) pair with the functions that use it. Only
addresses and names are printed, no game bytes."""
from __future__ import annotations

import argparse
import bisect
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import mips  # noqa: E402
from elf32 import Elf  # noqa: E402

BLOB_START, BSS_START, IMAGE_END = 0x00272C70, 0x00494080, 0x00675018
CALLER_SAVED = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 31}
WIDTH = {0x20: 1, 0x24: 1, 0x28: 1, 0x21: 2, 0x25: 2, 0x29: 2, 0x23: 4, 0x27: 4, 0x2B: 4, 0x31: 4,
         0x39: 4, 0x22: 1, 0x26: 1, 0x2A: 1, 0x2E: 1, 0x37: 8, 0x3F: 8, 0x1A: 1, 0x1B: 1, 0x2C: 1, 0x2D: 1,
         0x35: 8, 0x3D: 8, 0x1E: 16, 0x1F: 16, 0x36: 16, 0x3E: 16}
def _mul(st, a, b):
    x, y = st.get(a), st.get(b)
    return x * y if isinstance(x, int) and isinstance(y, int) else None


# jal target -> [(pointer register, byte count from the register state)]
BLOCK_CALLS = {
    0x0024FFA4: [(4, lambda st: st.get(6)), (5, lambda st: st.get(6))],  # memcpy(dst, src, n)
    0x00250054: [(4, lambda st: st.get(6))],  # memset(dst, c, n)
    0x0011EFA8: [(4, lambda st: 16), (5, lambda st: _mul(st, 6, 7))],  # pool init(hdr, items, size, count)
}
ARG = "arg"  # ("arg", k, off): argument k on entry + off
IDX = "idx"  # register = known base + offset: ("idx", base, upper bound of the offset or None)
UB = "ub"  # a small value with an upper bound: ("ub", U)
LT = "lt"  # a comparison result: ("lt", r, N) = register r < N
HI = "hi"  # register = a lui alone: ("hi", value); its %lo users are relocated fields


def pieces_from_ld(ld: Path, sizes: dict[str, int]):
    """[(orig start, orig end, piece id)] of every floated variable; a bss run is one piece."""
    out, run = [], None
    for ln in ld.read_text().splitlines():
        m = re.match(r"\s*(__float_run\d+) = \.;", ln)
        if m:
            run = m.group(1)
            continue
        if "__float_data_start" in ln:
            run = None
        m = re.search(r"\(\.data\.(\w+)\)\)\s*/\* was 0x([0-9a-f]+) \*/", ln)
        if m:
            name, a = m.group(1), int(m.group(2), 16)
            out.append((a, a + sizes[name], run or name, name))
    return sorted(out)


ARG_REGS = (4, 5, 6, 7, 8, 9, 10, 11)  # a0-a3, t0-t3: the EE's eight argument registers


def _ub(v):
    """Upper bound of a small value: an exact int below 0x10000 or ("ub", U); else None."""
    if isinstance(v, int) and -0x10000 < v < 0x10000:
        return v
    if isinstance(v, tuple) and v[0] == UB:
        return v[1]
    return None


def _idx(v):
    """(base, offset upper bound or None) of an address value: an exact address or IDX."""
    if isinstance(v, int) and v > 0x10000:
        return v, 0
    if isinstance(v, tuple) and v[0] == IDX:
        return v[1], v[2]
    return None


def analyse(insns: list[mips.Insn], starts: set[int] | None = None, args: bool = False):
    """Yield (pc, base, disp, width, kind) for accesses from a known base. kind: 'mem',
    'addr' (addiu to a new register), 'idx' (load/store through base + unknown; disp is
    the largest offset from base the access can reach, or None if unbounded),
    'call:T:' (a block function's byte count), and with args=True also
    ('argmem', k, off, width) for an access at off from argument k on entry and
    ('pass', T, j, value) for argument j of a call to T holding an address or an argument.

    Index bounds (session 19): small values carry an upper bound (UB) from `andi`, `slti`
    and `sltiu` tests on the branch edge they guard, byte/halfword loads, shifts and
    multiplies by constants, and loop counters whose growth a guarded back edge caps.
    A pointer walk (base, then base + stride on the back edge) is IDX with the largest
    offset seen; a `sltu p, END` guard caps it. Anything that keeps growing is widened
    to unbounded."""
    n = len(insns)
    if not n:
        return
    a0 = insns[0].addr
    index = lambda addr: (addr - a0) // 4
    entry = {0: 0}
    if args:
        entry.update({r: (ARG, k, 0) for k, r in enumerate(ARG_REGS)})
    states: dict[int, dict] = {0: entry}
    work = [0]
    seen_out = set()
    grow: dict[tuple, int] = {}

    def join(i, k, v, u):
        if u == v:
            return v
        a, b = _idx(v), _idx(u)
        if a is not None and b is not None and abs(a[0] - b[0]) < 0x10000:
            base = min(a[0], b[0])
            if a[1] is None or b[1] is None:
                return (IDX, base, None)
            hi = max(a[0] + a[1], b[0] + b[1]) - base
            # a pointer walking a table (p = D; ... p += 0x2c in a loop): base + bounded offset
            return (IDX, base, hi)
        x, y = _ub(v), _ub(u)
        if x is not None and y is not None:
            return (UB, max(x, y))
        return None

    def merge(i, st):
        if not (0 <= i < n):
            return
        old = states.get(i)
        if old is None:
            states[i] = dict(st)
            work.append(i)
            return
        new = {}
        for k, v in old.items():
            j = join(i, k, v, st.get(k))
            if j is None:
                continue
            # widening: a bound that grows twice at the same point is dropped
            if j != v and isinstance(j, tuple) and j[0] in (IDX, UB):
                c = grow[(i, k)] = grow.get((i, k), 0) + 1
                if c > 2:
                    j = (IDX, j[1], None) if j[0] == IDX else None
                    if j is None:
                        continue
            new[k] = j
        if new != old:
            states[i] = new
            work.append(i)

    def refine(st, cond, taken):
        """Apply a `bne/beq t, $0` edge: cond = the branch's (register, sense)."""
        reg, ne = cond
        v = st.get(reg)
        if not (isinstance(v, tuple) and v[0] == LT):
            return
        _lt, r, lim = v
        if ne != taken:  # this edge has t == 0: r >= lim, no upper bound to add
            return
        cur = st.get(r)
        a = _idx(cur)
        if a is not None:
            if lim > a[0] and lim - a[0] < 0x100000:  # sltu p, END
                hi = lim - 1 - a[0]
                if a[1] is None or a[1] > hi:
                    st[r] = (IDX, a[0], hi)
            return
        if -0x10000 < lim < 0x10000 and (cur is None or _ub(cur) is not None):
            u = _ub(cur)
            if u is None or u > lim - 1:
                st[r] = (UB, lim - 1)

    def step(ins, st):
        w = ins.word
        o, s, t, d = mips.op(w), mips.rs(w), mips.rt(w), mips.rd(w)
        ev = []
        before = dict(st)
        if o == mips.OP_LUI:
            st[t] = (HI, (w & 0xFFFF) << 16)
        elif o in (0x09, 0x19):  # addiu / daddiu
            b = st.get(s)
            if isinstance(b, tuple) and b[0] == HI:  # %hi + %lo: a relocated address (shift_cmp maps it)
                st[t] = (b[1] + mips.imm(w)) & 0xFFFFFFFF
            elif isinstance(b, int):
                v = (b + mips.imm(w)) & 0xFFFFFFFF
                if (w & 0xFFFF) != 0 or s != t:
                    ev.append((ins.addr, b, mips.imm(w), 0, "addr"))
                st[t] = v if b > 0x10000 or not (b + mips.imm(w)) < 0 else b + mips.imm(w)
            elif isinstance(b, tuple) and b[0] == ARG:
                st[t] = (ARG, b[1], b[2] + mips.imm(w))
            elif isinstance(b, tuple) and b[0] == IDX:
                st[t] = (IDX, b[1], None if b[2] is None else b[2] + mips.imm(w))
            elif isinstance(b, tuple) and b[0] == UB:
                st[t] = (UB, b[1] + mips.imm(w))
            else:
                st.pop(t, None)
        elif o == 0x0D:  # ori
            b = st.get(s)
            if isinstance(b, tuple) and b[0] == HI:
                st[t] = b[1] | (w & 0xFFFF)
            elif isinstance(b, int):
                st[t] = b | (w & 0xFFFF)
            else:
                st.pop(t, None)
        elif o == 0x0C:  # andi: 0 <= v <= imm
            b = st.get(s)
            st[t] = (b & (w & 0xFFFF)) if isinstance(b, int) else (UB, w & 0xFFFF)
        elif o in (0x0A, 0x0B):  # slti / sltiu
            st[t] = (LT, s, mips.imm(w) if o == 0x0A else mips.imm(w) & 0xFFFFFFFF) if s not in (0, t) else (UB, 1)
        elif o in WIDTH:
            b = st.get(s)
            if isinstance(b, int):
                ev.append((ins.addr, b, mips.imm(w), WIDTH[o], "mem"))
            elif isinstance(b, tuple) and b[0] == IDX:
                ev.append((ins.addr, b[1], None if b[2] is None else b[2] + mips.imm(w), WIDTH[o], "idx"))
            elif isinstance(b, tuple) and b[0] == ARG:
                ev.append(("argmem", b[1], b[2] + mips.imm(w), WIDTH[o]))
            if ins.is_load and o not in (0x31, 0x35, 0x36):  # gpr destination
                if o == 0x24:  # lbu
                    st[t] = (UB, 0xFF)
                elif o == 0x25:  # lhu
                    st[t] = (UB, 0xFFFF)
                else:
                    st.pop(t, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x21, 0x2D, 0x20, 0x2C, 0x25):  # addu daddu add dadd or
            x, y = st.get(s), st.get(t)
            x = None if isinstance(x, tuple) and x[0] in (HI, LT) else x
            y = None if isinstance(y, tuple) and y[0] in (HI, LT) else y
            if t == 0 or s == 0:  # a move
                v = x if t == 0 else y
                if v is None:
                    st.pop(d, None)
                else:
                    st[d] = v
            elif isinstance(x, int) and isinstance(y, int):
                st[d] = (x + y) & 0xFFFFFFFF if mips.funct(w) != 0x25 else x | y
            elif _idx(x) is not None or _idx(y) is not None:
                a, other = (_idx(x), y) if _idx(x) is not None else (_idx(y), x)
                u = _ub(other)
                if mips.funct(w) == 0x25 or a[1] is None or u is None:
                    st[d] = (IDX, a[0], None)
                else:
                    st[d] = (IDX, a[0], a[1] + u)
            elif _ub(x) is not None and _ub(y) is not None and mips.funct(w) != 0x25:
                st[d] = (UB, _ub(x) + _ub(y))
            else:
                st.pop(d, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x23, 0x2F):  # subu dsubu
            x = st.get(s)
            if _idx(x) is not None and d != 0:
                st[d] = (IDX, _idx(x)[0], None)
            else:
                st.pop(d, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x00, 0x38, 0x3C):  # sll dsll dsll32
            x = _ub(st.get(t))
            sh = ((w >> 6) & 31) + (32 if mips.funct(w) == 0x3C else 0)
            if isinstance(st.get(t), int) and d != 0:
                st[d] = (st[t] << sh) & 0xFFFFFFFF if mips.funct(w) == 0x00 else st[t] << sh
            elif x is not None and x >= 0 and sh < 16 and d != 0:
                st[d] = (UB, x << sh)
            else:
                st.pop(d, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x2A, 0x2B):  # slt sltu: t = s < t
            lim = st.get(t)
            if isinstance(lim, int) and d != 0 and s not in (0, d):
                st[d] = (LT, s, lim)
            elif d != 0:
                st[d] = (UB, 1)
            else:
                st.pop(d, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x18, 0x19):  # mult/multu (EE: rd too)
            x, y = st.get(s), st.get(t)
            c, u = (x, _ub(y)) if isinstance(x, int) and 0 <= x < 0x10000 else (y, _ub(x))
            if d != 0 and isinstance(c, int) and 0 <= c < 0x10000 and u is not None and u >= 0:
                st[d] = (UB, u * c)
            else:
                st.pop(d, None)
        elif ins.is_jal or ins.is_jalr:
            for r in CALLER_SAVED:
                st.pop(r, None)
        else:
            # anything else that writes a gpr: forget it
            if o == mips.OP_SPECIAL or o == mips.OP_MMI:
                st.pop(d, None)
            elif o in (0x08, 0x0E, 0x18):
                st.pop(t, None)
            elif o in (0x10, 0x11, 0x12) and s in (0x00, 0x01, 0x02):  # mfc, dmfc, cfc
                st.pop(t, None)
        st[0] = 0
        # a comparison result describes its operand only until that register changes
        changed = {k for k in set(before) | set(st) if before.get(k) != st.get(k)}
        if changed:
            for k, v in list(st.items()):
                if isinstance(v, tuple) and v[0] == LT and v[1] in changed and k not in changed:
                    del st[k]
        return ev

    def call_events(ins, st, target):
        ev = []
        # a known block function: its pointer arguments with their byte counts
        for ptr, size in BLOCK_CALLS.get(target, ()):
            b, n_ = st.get(ptr), size(st)
            if isinstance(b, int) and isinstance(n_, int) and 0 < n_ <= 0x100000:
                ev.append((ins.addr, b, 0, n_, f"call:{target:08x}:"))
        if True:
            for j, r in enumerate(ARG_REGS):
                v = st.get(r)
                if (isinstance(v, int) and v > 0x10000) or (isinstance(v, tuple) and v[0] == ARG):
                    ev.append(("pass", target, j, v, ins.addr))
        return ev

    while work:
        i = work.pop()
        st = dict(states[i])
        ins = insns[i]
        ev = []
        if ins.is_branch or ins.is_j or ins.is_jr or ins.is_jal or ins.is_jalr:
            likely = mips.op(ins.word) in (0x14, 0x15, 0x16, 0x17) or (
                mips.op(ins.word) == mips.OP_REGIMM and mips.rt(ins.word) in (0x02, 0x03, 0x12, 0x13))
            call = ins.is_jal or ins.is_jalr
            w = ins.word
            cond = None
            if mips.op(w) in (0x04, 0x05, 0x14, 0x15) and (mips.rt(w) == 0) != (mips.rs(w) == 0):
                cond = (mips.rs(w) or mips.rt(w), mips.op(w) in (0x05, 0x15))  # (t, branch-if-nonzero)
            if i + 1 < n:
                st_d = dict(st)
                ev += step(insns[i + 1], st_d)
            else:
                st_d = st
            tail = ins.is_j and not (a0 <= ins.jump_target < a0 + 4 * n)
            if (ins.is_jal or tail):
                ev += call_events(ins, st_d, ins.jump_target)
            if tail:
                pass
            elif call:
                for r in CALLER_SAVED:
                    st_d.pop(r, None)
                merge(i + 2, st_d)
            elif ins.is_branch:
                st_t = dict(st_d)
                if cond and cond[0] in st and st.get(cond[0]) == st_d.get(cond[0]):
                    refine(st_t, cond, True)
                merge(index(ins.branch_target), st_t)
                always = (mips.op(w) == 0x04 and mips.rs(w) == mips.rt(w)) or (
                    mips.op(w) == mips.OP_REGIMM and mips.rt(w) in (0x01, 0x11) and mips.rs(w) == 0)
                if not always:  # `b` is beq $0,$0 (or bgez $0): no fall-through
                    st_f = dict(st if likely else st_d)
                    if cond and cond[0] in st and st.get(cond[0]) == st_f.get(cond[0]):
                        refine(st_f, cond, False)
                    merge(i + 2, st_f)
            elif ins.is_j:
                merge(index(ins.jump_target), st_d)
            elif ins.is_jr and not ins.is_jr_ra and starts:
                for j in starts:  # a switch: any label may be a case
                    merge(index(j), st_d)
        else:
            ev += step(ins, st)
            merge(i + 1, st)
        for e in ev:
            if e not in seen_out:
                seen_out.add(e)
                yield e
        if not work and starts:
            # unreached code: start fresh at the next listed label
            for j in sorted(starts):
                k = index(j)
                if 0 <= k < n and k not in states:
                    states[k] = {0: 0}
                    work.append(k)
                    break


def anchor_addrs(elf_path: Path) -> set[int]:
    """Addresses of every D_ name of the M0 link (out/shift/kh1-shift.linked.elf)."""
    if not elf_path.exists():
        return set()
    e = Elf.load(elf_path)
    return {s_.value for s_ in e.symbols() if re.match(r"D_[0-9A-F]{8}$", s_.name)
            and BLOB_START <= s_.value < IMAGE_END}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--ld", type=Path, help="a SHIFT_FLOAT link script: its floated variables and runs are "
                    "the pieces (default: every C-defined variable is a piece of its own)")
    ap.add_argument("--out", type=Path, help="write the floated names a hazard involves (--float-skip-file)")
    ap.add_argument("--elf", type=Path, default=ROOT / "SLPS_251.98")
    ap.add_argument("--overlays", type=Path, default=ROOT / "out/overlays")
    ap.add_argument("--all", action="store_true", help="also list indexed accesses from floated bases")
    ap.add_argument("--anchors-elf", type=Path, default=ROOT / "out/shift/kh1-shift.linked.elf",
                    help="the M0 link, for the addresses of every D_ name")
    ap.add_argument("--no-bounds", action="store_true",
                    help="ignore index bounds: every indexed base keeps the next name (session 18 rule)")
    ap.add_argument("--debug", type=lambda x: int(x, 16), help="print the call sites passing this address")
    a = ap.parse_args()

    sizes = {}
    for ln in (ROOT / "out/gen/data.tsv").read_text().splitlines()[1:]:
        f = ln.split("\t")
        sizes[f[1]] = int(f[3], 16) if f[3].startswith("0x") else int(f[3], 16)
    if a.ld:
        pcs = pieces_from_ld(a.ld, sizes)
    else:
        pcs = []
        for ln in (ROOT / "out/gen/data.tsv").read_text().splitlines()[1:]:
            f = ln.split("\t")
            ad = int(f[0], 16)
            pcs.append((ad, ad + int(f[3], 16), f[1], f[1]))
        pcs.sort()
    starts = [p[0] for p in pcs]

    def piece(addr: int):
        i = bisect.bisect_right(starts, addr) - 1
        if i >= 0 and addr < pcs[i][1]:
            return pcs[i][2], pcs[i][3]
        return None, None

    elf = Elf.load(a.elf)
    funcs = []
    for ln in (ROOT / "layout.tsv").read_text().splitlines():
        if ln.startswith("#") or ln.startswith("addr"):
            continue
        f = ln.split("\t")
        funcs.append((int(f[0], 16), int(f[1], 16), f[3]))
    regions = []
    for s, e, name in funcs:
        regions.append((name, mips.decode(s, elf.read(s, e - s))))
    for p in sorted(a.overlays.glob("*.x")) if a.overlays.is_dir() else []:
        body = p.read_bytes()
        regions.append((p.name, mips.decode(0x00F20000, body[: len(body) & ~3])))

    hits: dict[tuple, set] = {}
    idx: dict[int, set] = {}
    idx_all: dict[int, set] = {}
    idx_end: dict[int, int | None] = {}  # indexed base -> end of the furthest bounded access (None: unbounded)
    own: dict[int, dict[int, list[int]]] = {}  # function -> arg -> [lo, hi) reached from it
    passes: dict[int, list] = {}  # function -> [(callee, j, ("arg", k, off))]
    sites: list = []  # (caller name, callee, j, address)

    def check(name, base, disp, width, kind):
        pb, nb = piece(base)
        tgt = (base + disp) & 0xFFFFFFFF
        last = (tgt + max(width, 1) - 1) & 0xFFFFFFFF
        pt, nt = piece(tgt)
        pl, _nl = piece(last)
        if pb != pt or pt != pl:
            hits.setdefault((base, nb, tgt, nt, kind, width), set()).add(name)

    for name, insns in regions:
        if not insns:
            continue
        fstart = insns[0].addr
        labels = {i.branch_target for i in insns if i.is_branch} | {i.jump_target for i in insns if i.is_j}
        is_func = not name.endswith(".x")
        for e in analyse(insns, set(x for x in labels if x), args=is_func):
            if e[0] == "argmem":
                _k, k, off, width = e
                r = own.setdefault(fstart, {}).setdefault(k, [off, off + width])
                r[0], r[1] = min(r[0], off), max(r[1], off + width)
                continue
            if e[0] == "pass":
                _p, callee, j, v, _pc = e
                if isinstance(v, tuple):
                    passes.setdefault(fstart, []).append((callee, j, v[1], v[2]))
                elif BLOB_START <= v < IMAGE_END + 0x10000:
                    sites.append((name, callee, j, v))
                continue
            pc, base, disp, width, kind = e
            if not (BLOB_START <= base < IMAGE_END + 0x10000):
                continue
            if kind == "idx":
                idx_all.setdefault(base, set()).add(name)
                end = None if disp is None else base + disp + width
                if base not in idx_end or (idx_end[base] is not None and (end is None or end > idx_end[base])):
                    idx_end[base] = end
                if piece(base)[0] is not None:
                    idx.setdefault(base, set()).add(name)
                continue
            check(name, base, disp, width, kind)
    # Each function's reach from its arguments includes what its callees reach from them.
    reach = {f: {k: list(v) for k, v in d.items()} for f, d in own.items()}
    for _round in range(12):
        changed = False
        for f, ps in passes.items():
            for callee, j, k, off in ps:
                c = reach.get(callee, {}).get(j)
                if not c:
                    continue
                lo, hi = c[0] + off, c[1] + off
                if hi - lo > 0x40000:
                    continue
                r = reach.setdefault(f, {}).setdefault(k, [lo, hi])
                if lo < r[0] or hi > r[1]:
                    r[0], r[1] = min(r[0], lo), max(r[1], hi)
                    changed = True
        if not changed:
            break
    fname = {s_: n_ for s_, _e, n_ in funcs}
    for name, callee, j, v in sites:
        c = reach.get(callee, {}).get(j)
        if callee in BLOCK_CALLS:  # their own byte count is checked at the call
            continue
        if c and c[1] - c[0] <= 0x40000:
            check(name, v, c[0], c[1] - c[0], f"arg{j}:{fname.get(callee, hex(callee))}:")
    # An array indexed from B may run past the next name: D_00550400[i] for i < 64 (0x48-byte
    # entries) covers D_005512A0, which is entries 52..63 under its own name (session 18,
    # found from the stale writes in a RAM dump). A floated variable that is the next name
    # after an indexed base in another piece stays with it.
    anchors = sorted(anchor_addrs(a.anchors_elf) | {p_[0] for p_ in pcs})
    bounded = []
    for base, fs in sorted(idx_all.items()):
        i = bisect.bisect_right(anchors, base)
        if i >= len(anchors):
            continue
        nxt = anchors[i]
        pn, nn = piece(nxt)
        if a.no_bounds is False and idx_end.get(base) is not None and idx_end[base] <= nxt:
            bounded.append((base, nxt, idx_end[base]))
            continue  # every indexed access from base is bounded and ends before the next name
        if pn is not None and pn != piece(base)[0] and nxt - base <= 0x10000:
            hits.setdefault((base, piece(base)[1], nxt, nn, "idx-next", 0), set()).update(fs)
    for (base, nb, tgt, nt, kind, width), fs in sorted(hits.items()):
        print(f"{base:08x} ({nb or 'in place'}) -> {tgt:08x} ({nt or 'in place'})\t{kind}{width or ''}\t"
              + " ".join(sorted(fs)[:6]) + (f" +{len(fs) - 6}" if len(fs) > 6 else ""))
    if a.out:
        names = sorted({n for (_b, nb, _t, nt, _k, _w) in hits for n in (nb, nt) if n})
        a.out.write_text("".join(n + "\n" for n in names))
    if a.all:
        for base, fs in sorted(idx.items()):
            print(f"{base:08x} ({piece(base)[1]}) indexed\t" + " ".join(sorted(fs)[:6]))
    if a.debug:
        for name, callee, j, v in sites:
            if v == a.debug:
                print(f"debug: {name} passes {v:08x} as arg{j} to {fname.get(callee, hex(callee))}: "
                      f"reach {reach.get(callee, {}).get(j)}")
    print(f"# {len(bounded)} indexed bases have bounded accesses that end before the next name",
          file=sys.stderr)
    print(f"# {len(reach)} functions reach from their arguments, {len(sites)} call sites pass an address",
          file=sys.stderr)
    print(f"# {len(pcs)} floated variables, {len(hits)} cross-piece accesses, {len(idx)} indexed floated bases",
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
