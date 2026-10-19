#!/usr/bin/env python3
"""Static check of every R_MIPS_LO16 in a shift link (docs/shiftable-plan.md,
"Session 14: LO16 base check").

  python3 -I tools/shift/lo16_check.py [--link out/shift] [--examples 5]

shift_cmp.py and ovl_proof.py prove that every relocated field maps back; a
relocation that is wrong but self-consistent passes them (session 14: a struct
load `lw $v0,0($a0)` exported as `%lo(D_00570000)($a0)` because a lui in a
branch-likely delay slot was taken to reach the not-taken path). It shows only
at run time, and only when .bss moves by an amount that is not a multiple of
64 KiB. This check reads the linked ELF (ld -q keeps the relocations) and, for
every LO16, walks the control flow backwards from the instruction along every
path until the base register is written:

- the write must be a `lui` that carries an R_MIPS_HI16 (`addu/daddu rX,rX,rY`
  keeps the %hi, as in jump-table indexing, `move rX,rY` passes it on, and a
  load from the stack restores what a store to the same slot spilled: the walk
  continues through them);
- a path that reaches the function entry, crosses a call while the register is
  caller-saved, or ends in any other write is a finding (code nothing reaches,
  such as the nop after an unconditional branch, is not a path);
- a LO16 on an instruction that takes no base register (not addiu/ori/load/store)
  is a finding.

Control flow per function (= .text input section of the link map): delay slots
flow only from their branch (likely branches: delay slot on the taken path
only), jal/jalr/bal return to k+2 with caller-saved registers clobbered, `jr`
other than `jr $ra` goes to every in-function address an R_MIPS_32 relocation
points at (jump tables). Findings are listed per source file; exit status 1 if
there are any (--warn-only: always 0)."""
from __future__ import annotations

import argparse
import bisect
import collections
import struct
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TOOLS / "shift"))
import kh1tool as K  # noqa: E402
import mips  # noqa: E402
from asm_export import BRANCH_LIKELY, CALLER_SAVED, gpr_written  # noqa: E402
from elf32 import R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16, Elf  # noqa: E402
from shift_cmp import read_map, source_of  # noqa: E402

CALLER = set(CALLER_SAVED)
SP = 29
SPILL_LOADS = {0x23, 0x37, mips.OP_LQ}    # lw ld lq from the stack: a restored spill
SPILL_STORES = {0x2B, 0x3F, mips.OP_SQ}   # sw sd sq to the stack
BASE_OPS = {0x09, 0x0D} | mips.OP_LOADS | mips.OP_STORES | mips.OP_VU_MEM | {mips.OP_LQ, mips.OP_SQ}


def is_move(w: int) -> int | None:
    """Source register of `move rd, rs` (addu/daddu/or rd, rs, $zero), else None."""
    if mips.op(w) == 0 and mips.funct(w) in (0x21, 0x2D, 0x25) and mips.rt(w) == 0 and mips.rs(w):
        return mips.rs(w)
    return None


def successors(words: list[int], base: int, jt) -> list[list[tuple[int, bool]]]:
    """jt(k): the in-function targets of the `jr` at word k (its jump table)."""
    n = len(words)
    succ: list[list[tuple[int, bool]]] = [[] for _ in range(n)]
    slot = False
    for k, w in enumerate(words):
        a = base + 4 * k
        i = mips.Insn(a, w)
        o = mips.op(w)
        is_ct = i.is_branch or o in (mips.OP_J, mips.OP_JAL) or i.is_jr or i.is_jalr
        in_slot, slot = slot, is_ct
        if not is_ct:
            if o == 0x10 and (w & 0x3F) == 0x18 and mips.rs(w) == 0x10:  # eret
                continue
            if k + 1 < n and not in_slot:
                succ[k].append((k + 1, False))
            continue
        d = k + 1
        likely = o in BRANCH_LIKELY or (o == mips.OP_REGIMM and mips.rt(w) in (0x02, 0x03, 0x12, 0x13)) or \
            (o in (0x11, 0x12) and mips.rs(w) == 0x08 and mips.rt(w) & 2)
        if d < n:
            succ[k].append((d, False))
        if likely and k + 2 < n:
            succ[k].append((k + 2, False))
        if d >= n:
            continue
        outs: list[tuple[int, bool]] = []
        uncond = (o == 0x04 and mips.rs(w) == 0 and mips.rt(w) == 0) or \
            (o == mips.OP_REGIMM and mips.rt(w) == 0x01 and mips.rs(w) == 0)
        if i.branch_target is not None:
            t = (i.branch_target - base) // 4
            if 0 <= t < n:
                outs.append((t, False))
            if o == mips.OP_REGIMM and mips.rt(w) in (0x10, 0x11, 0x12, 0x13):  # bal: a call
                outs = [(k + 2, True)] if k + 2 < n else []
            elif not uncond and not likely and k + 2 < n:
                outs.append((k + 2, False))
        elif o == mips.OP_J:
            t = (i.jump_target - base) // 4
            if 0 <= t < n:
                outs.append((t, False))
        elif o == mips.OP_JAL or i.is_jalr:
            if k + 2 < n:
                outs.append((k + 2, True))
        elif i.is_jr and not i.is_jr_ra:
            outs += [((t - base) // 4, False) for t in jt(k)]
        succ[d] += outs
    return succ


def check_function(words: list[int], base: int, jt, lo_at: dict[int, int],
                   hi_at: set[int]) -> list[tuple[int, str]]:
    """Findings (address, what) for the LO16 fields at word indices lo_at (index -> reloc)."""
    n = len(words)
    succ = successors(words, base, jt)
    pred: list[list[tuple[int, bool]]] = [[] for _ in range(n)]
    for k, ss in enumerate(succ):
        for s, clob in ss:
            pred[s].append((k, clob))
    out = []
    for k in sorted(lo_at):
        w = words[k]
        if mips.op(w) not in BASE_OPS:
            out.append((base + 4 * k, f"LO16 on an instruction with no base register (0x{w:08x})"))
            continue
        reg = mips.rs(w)
        why = None
        seen = set()
        # walk back from the instruction before k (its own write happens after the read)
        stack = [(p, reg, clob) for p, clob in pred[k]]
        if k == 0:
            why = f"${reg} at the function entry (no lui on some path)"
        while stack and why is None:
            j, r, clob = stack.pop()
            if clob and not isinstance(r, tuple) and r in CALLER:
                why = f"${r} clobbered by the call returning to 0x{base + 4 * (j + 1):08x} on some path"
                break
            if (j, r) in seen:
                continue
            seen.add((j, r))
            wj = words[j]
            o = mips.op(wj)
            if isinstance(r, tuple):  # a stack slot holding the %hi (spilled, restored later)
                if o in SPILL_STORES and mips.rs(wj) == SP and mips.imm(wj) == r[1]:
                    r = mips.rt(wj)
            elif o == mips.OP_LUI and mips.rt(wj) == r:
                if j not in hi_at:
                    why = f"${r} from an unrelocated lui at 0x{base + 4 * j:08x}"
                continue
            elif o in SPILL_LOADS and mips.rs(wj) == SP and mips.rt(wj) == r:
                r = ("sp", mips.imm(wj))
            else:
                wr, keep = gpr_written(wj)
                src = is_move(wj)
                if wr == r and src is not None:
                    r = src
                elif wr == r and not keep:
                    why = f"${r} written by 0x{wj:08x} at 0x{base + 4 * j:08x} on some path"
                    break
            if j == 0:
                why = f"{r if isinstance(r, tuple) else '$%d' % r} at the function entry (no lui on some path)"
                break
            stack += [(p, r, c) for p, c in pred[j]]
        if why:
            out.append((base + 4 * k, why))
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--link", type=Path, default=K.OUT / "shift", help="a shift link directory (kh1-shift.linked.elf, .map)")
    ap.add_argument("--examples", type=int, default=5)
    ap.add_argument("--warn-only", action="store_true")
    a = ap.parse_args()
    elf = Elf.load(a.link / "kh1-shift.linked.elf")
    secs = sorted((v[0], v[1], k) for k, v in read_map(a.link / "kh1-shift.map").items()
                  if v[2] == ".text" and v[1] and k[1].startswith(".text"))
    text = elf.section(".text")
    tbytes = elf.section_bytes(text)
    relocs = collections.defaultdict(list)
    jt_all = []
    r32 = {}  # relocated word address -> value
    for s in elf.sections:
        if s.name not in (".text", ".data"):
            continue
        sb = elf.section_bytes(s)
        for off, typ, _si in elf.relocations(s):
            if s.name == ".text":
                relocs[typ].append(off)
            if typ == R_MIPS_32:
                r32[off] = struct.unpack_from("<I", sb, off - s.addr)[0]
                jt_all.append(r32[off])
    jt_all.sort()
    lo_all = sorted(relocs[R_MIPS_LO16])
    hi_all = set(relocs[R_MIPS_HI16])
    findings = collections.defaultdict(list)
    n_lo = 0
    for addr, size, (obj, _isec) in secs:
        i, j = bisect.bisect_left(lo_all, addr), bisect.bisect_left(lo_all, addr + size)
        if i == j:
            continue
        words = list(struct.unpack_from(f"<{size // 4}I", tbytes, addr - text.addr))
        lo_at = {(x - addr) // 4: x for x in lo_all[i:j]}
        hi_at = {(x - addr) // 4 for x in hi_all if addr <= x < addr + size}
        ji, jj = bisect.bisect_right(jt_all, addr), bisect.bisect_left(jt_all, addr + size)
        every = sorted({t for t in jt_all[ji:jj] if t % 4 == 0 and t != addr})  # not the start: a function pointer

        def jt(k: int, words=words, addr=addr, size=size, every=every) -> list[int]:
            """The table of `lui rB,%hi(T); [addu rB,rB,idx;] lw rJ,%lo(T)(rB); jr rJ`:
            its relocated words that point into this function (else every such target)."""
            rj = mips.rs(words[k])
            for m in range(k - 1, max(k - 6, -1), -1):
                lw = words[m]
                if mips.op(lw) == 0x23 and mips.rt(lw) == rj:
                    rb = mips.rs(lw)
                    for n in range(m - 1, max(m - 8, -1), -1):
                        u = words[n]
                        if mips.op(u) == mips.OP_LUI and mips.rt(u) == rb:
                            t = (((u & 0xFFFF) << 16) + (lw & 0xFFFF) - (0x10000 if lw & 0x8000 else 0)) & 0xFFFFFFFF
                            out = []
                            while t in r32 and addr < r32[t] < addr + size:
                                out.append(r32[t])
                                t += 4
                            return out or every
                    break
            return every
        n_lo += len(lo_at)
        for fa, why in check_function(words, addr, jt, lo_at, hi_at):
            findings[source_of(obj)].append(f"0x{fa:08x} {why}")
    total = sum(len(v) for v in findings.values())
    print(f"LO16 check ({a.link}): {n_lo} LO16 fields in {len(secs)} functions, "
          f"{total} whose base register is not the paired lui's result on every path"
          + (f" ({len(findings)} files)" if total else ""))
    for src, items in sorted(findings.items(), key=lambda kv: -len(kv[1])):
        print(f"  {len(items):5d}  {src}")
        for it in items[:a.examples]:
            print(f"           {it}")
    return 1 if total and not a.warn_only else 0


if __name__ == "__main__":
    sys.exit(main())
