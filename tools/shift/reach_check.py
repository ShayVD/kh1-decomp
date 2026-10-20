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
IDX = "idx"  # register = known base + unknown offset: ("idx", base)
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


def analyse(insns: list[mips.Insn], starts: set[int] | None = None, args: bool = False):
    """Yield (pc, base, disp, width, kind) for accesses from a known base. kind: 'mem',
    'addr' (addiu to a new register), 'idx' (load/store through base + unknown),
    'call:T:' (a block function's byte count), and with args=True also
    ('argmem', k, off, width) for an access at off from argument k on entry and
    ('pass', T, j, value) for argument j of a call to T holding an address or an argument."""
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
            u = st.get(k)
            if u == v:
                new[k] = v
                continue
            # a pointer walking a table (p = D; ... p += 0x2c in a loop): base + unknown
            bv = v if isinstance(v, int) else (v[1] if isinstance(v, tuple) and v[0] == IDX else None)
            bu = u if isinstance(u, int) else (u[1] if isinstance(u, tuple) and u[0] == IDX else None)
            if bv is not None and bu is not None and bv > 0x10000 and bu > 0x10000 and abs(bv - bu) < 0x10000:
                new[k] = (IDX, min(bv, bu))
        if new != old:
            states[i] = new
            work.append(i)

    def step(ins, st):
        w = ins.word
        o, s, t, d = mips.op(w), mips.rs(w), mips.rt(w), mips.rd(w)
        ev = []
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
                st[t] = v
            elif isinstance(b, tuple) and b[0] == ARG:
                st[t] = (ARG, b[1], b[2] + mips.imm(w))
            elif isinstance(b, tuple) and b[0] == IDX:
                st[t] = b
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
        elif o in WIDTH:
            b = st.get(s)
            if isinstance(b, int):
                ev.append((ins.addr, b, mips.imm(w), WIDTH[o], "mem"))
            elif isinstance(b, tuple) and b[0] == IDX:
                ev.append((ins.addr, b[1], mips.imm(w), WIDTH[o], "idx"))
            elif isinstance(b, tuple) and b[0] == ARG:
                ev.append(("argmem", b[1], b[2] + mips.imm(w), WIDTH[o]))
            if ins.is_load and o not in (0x31, 0x35, 0x36):  # gpr destination
                st.pop(t, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x21, 0x2D, 0x20, 0x2C, 0x25):  # addu daddu add dadd or
            x, y = st.get(s), st.get(t)
            x = None if isinstance(x, tuple) and x[0] == HI else x
            y = None if isinstance(y, tuple) and y[0] == HI else y
            if t == 0 or s == 0:  # a move
                v = x if t == 0 else y
                if v is None:
                    st.pop(d, None)
                else:
                    st[d] = v
            elif isinstance(x, int) and isinstance(y, int):
                st[d] = (x + y) & 0xFFFFFFFF if mips.funct(w) != 0x25 else x | y
            elif isinstance(x, int) and x > 0x10000:
                st[d] = (IDX, x)
            elif isinstance(y, int) and y > 0x10000:
                st[d] = (IDX, y)
            elif isinstance(x, tuple) and x[0] == IDX:
                st[d] = x
            elif isinstance(y, tuple) and y[0] == IDX:
                st[d] = y
            else:
                st.pop(d, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x23, 0x2F):  # subu dsubu
            x = st.get(s)
            if isinstance(x, int) and x > 0x10000 and d != 0:
                st[d] = (IDX, x)
            elif isinstance(x, tuple) and x[0] == IDX and d != 0:
                st[d] = x
            else:
                st.pop(d, None)
        elif ins.is_jal or ins.is_jalr:
            for r in CALLER_SAVED:
                st.pop(r, None)
        else:
            # anything else that writes a gpr: forget it
            if o == mips.OP_SPECIAL or o == mips.OP_MMI:
                st.pop(d, None)
            elif o in (0x08, 0x0A, 0x0B, 0x0C, 0x0E, 0x18):
                st.pop(t, None)
            elif o in (0x10, 0x11, 0x12) and s in (0x00, 0x01, 0x02):  # mfc, dmfc, cfc
                st.pop(t, None)
        st[0] = 0
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
                merge(index(ins.branch_target), st_d)
                w = ins.word
                always = (mips.op(w) == 0x04 and mips.rs(w) == mips.rt(w)) or (
                    mips.op(w) == mips.OP_REGIMM and mips.rt(w) in (0x01, 0x11) and mips.rs(w) == 0)
                if not always:  # `b` is beq $0,$0 (or bgez $0): no fall-through
                    merge(i + 2, st if likely else st_d)
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
    for base, fs in sorted(idx_all.items()):
        i = bisect.bisect_right(anchors, base)
        if i >= len(anchors):
            continue
        nxt = anchors[i]
        pn, nn = piece(nxt)
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
    print(f"# {len(reach)} functions reach from their arguments, {len(sites)} call sites pass an address",
          file=sys.stderr)
    print(f"# {len(pcs)} floated variables, {len(hits)} cross-piece accesses, {len(idx)} indexed floated bases",
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
