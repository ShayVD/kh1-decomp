#!/usr/bin/env python3
"""Load-time fixups for the EE overlays (docs/shiftable-plan.md, "Session 13:
overlay fixups").

  python3 -I tools/shift/overlay_relocs.py [--overlays out/overlays] [--out-dir out/shift]
      [--tier 3] [--report] [--debug]

Every EE overlay (.x, raw code + data loaded at 0x00F20000, entry = first
byte) is linked against the main ELF's absolute addresses. This reads the
user's overlays (extracted from their own disc into out/overlays by
tools/shift/extract_kingdom.py; never committed) and finds every reference
into the main image 0x00100000-0x00675018:

  * code: recursive descent from the entry (branches, jal/j inside the
    overlay, jump tables), then overlay-internal code pointers (built with
    %hi/%lo or held in the overlay's data) that decode as whole functions,
    then the non-zero gaps of the code span that decode cleanly;
  * jal / j into the main text  -> J26 fixups (mid-function targets are
    listed: they map through the containing function + offset);
  * %hi/%lo pairs (reaching definitions over each function's control flow:
    delay slots, likely branches, jump tables, calls clobbering caller-saved
    registers; checked against a linear tracker) -> HI16 + LO16 fixups;
  * aligned words of the overlay's data (everything that is not code) whose
    value is in the image, classified like tools/shift/find_data_relocs.py
    (tiers 1/2/3 accepted, x rejected with a reason; numbers rejected).

Writes (all under --out-dir, which must be inside out/; nothing is committed):

  ovl_fixups.s      the table the KH1_OVL_FIXUPS hook (shift/ovl_fixup.c)
                    applies: per overlay its name hash (func_001200f8), the
                    file size, entries (kind, target index, word offset) and
                    targets as `.word sym+addend` (new address, resolved by
                    the linker) plus the original address (`.word 0x...`, a
                    main-ELF address used to verify the field before
                    patching). Only offsets, kinds, symbols and main-ELF
                    addresses: no overlay bytes. Empty (no overlay) when the
                    overlay directory is missing.
  ovl_labels.txt    main-ELF function starts the table names (`__dr_XXXXXXXX`
                    labels shift_ld.py defines next to each function)
  ovl_fixups.json   the analysis for the static proof (tools/shift/ovl_proof.py):
                    per overlay hash, size, fixups with their old targets and
                    the hi/lo pairing
  ovl_report.txt    counts per overlay and kind, mid-function targets, the
                    ambiguous remainder
  ovl_debug.tsv     (--debug) every candidate word with its value: holds
                    overlay-derived bytes, out/ only

Table format (little-endian u32, offsets in bytes from the table start):

  header      'KHOF' (0x464F484B), version 1, n_overlays
  n x         hash, size, n_entries, entries_offset, n_targets, targets_offset
  entries     kind << 30 | target index << 18 | word offset in the overlay
              kinds: 0 J26 (jal/j field), 1 WORD (32-bit word), 2 HI16,
              3 LO16 followed by one extra word: the word offset of its lui.
              Per overlay: J26, WORD, then all HI16 before all LO16 (a LO16
              is computed against its lui as already patched).
  targets     per index: new address (.word sym+addend), original address"""
from __future__ import annotations

import argparse
import bisect
import collections
import json
import re
import struct
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TOOLS / "shift"))
import kh1tool as K  # noqa: E402
import mips  # noqa: E402
import find_data_relocs as FDR  # noqa: E402
from extract_kingdom import OVERLAYS, kh_hash  # noqa: E402

BASE = 0x00F20000
IMAGE_LO, IMAGE_HI = 0x00100000, 0x00675018   # inclusive end (crt0's _end)
DATA_LO, DATA_HI = 0x00272C70, 0x00494050
BSS_LO = 0x00494080
MIRRORS = (0x20000000, 0x30000000)
MAGIC, VERSION = 0x464F484B, 1
J26, WORD, HI16, LO16 = 0, 1, 2, 3
KIND_NAME = {J26: "J26", WORD: "WORD", HI16: "HI16", LO16: "LO16"}
MAX_TIDX, MAX_WOFF = 1 << 12, 1 << 18

# ------------------------------------------------------------------ decoding

SPECIAL_OK = {0x00, 0x02, 0x03, 0x04, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11,
              0x12, 0x13, 0x14, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
              0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34,
              0x36, 0x38, 0x3A, 0x3B, 0x3C, 0x3E, 0x3F}
REGIMM_OK = {0x00, 0x01, 0x02, 0x03, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0E, 0x10, 0x11, 0x12, 0x13, 0x18, 0x19}
OP_BAD = {0x13, 0x1D, 0x30, 0x32, 0x34, 0x35, 0x38, 0x3A, 0x3B, 0x3C, 0x3D}
BRANCH_LIKELY = {0x14, 0x15, 0x16, 0x17}
UNK = frozenset([-1])  # flow pairing: "not a lui value" on some path
CALLER_SAVED = frozenset(r for r in range(1, 32) if not (16 <= r <= 23 or r in (28, 29, 30)))
LO_OPS = {0x09, 0x0D} | mips.OP_LOADS | mips.OP_STORES | mips.OP_VU_MEM | {mips.OP_LQ, mips.OP_SQ}


def valid(w: int) -> bool:
    """A plausible R5900 instruction (gcc output): known opcode/function."""
    o = w >> 26
    if o in OP_BAD:
        return False
    if o == 0:
        return (w & 0x3F) in SPECIAL_OK
    if o == 1:
        return ((w >> 16) & 0x1F) in REGIMM_OK
    return True


def likely(w: int) -> bool:
    o = mips.op(w)
    return o in BRANCH_LIKELY or (o == mips.OP_REGIMM and mips.rt(w) in (0x02, 0x03, 0x12, 0x13)) or \
        (o in (0x11, 0x12) and mips.rs(w) == 0x08 and mips.rt(w) & 2)


def uncond(w: int) -> bool:
    o = mips.op(w)
    return (o == 0x04 and mips.rs(w) == 0 and mips.rt(w) == 0) or \
        (o == mips.OP_REGIMM and mips.rt(w) == 0x01 and mips.rs(w) == 0)


def is_bal(w: int) -> bool:
    return mips.op(w) == mips.OP_REGIMM and mips.rt(w) in (0x10, 0x11, 0x12, 0x13)


def is_move(w: int) -> bool:
    """move rd, rs: addu/daddu/or rd, rs, $zero (either operand)."""
    return mips.op(w) == 0 and mips.funct(w) in (0x21, 0x2D, 0x25) and 0 in (mips.rs(w), mips.rt(w))


def gpr_written(w: int) -> tuple[int | None, bool]:
    """(GPR written, keeps_hi): as tools/asm_export.py (addu rX,rX,rY keeps rX's %hi)."""
    o = mips.op(w)
    if o in (0x11, 0x12):
        return (mips.rt(w), False) if mips.rs(w) in (0, 1, 2) else (None, False)
    if o in K.GPR_RT_WRITERS:
        return mips.rt(w), False
    if o == mips.OP_MMI:
        return mips.rd(w), False
    if o == mips.OP_JAL or is_bal(w):
        return 31, False
    if o == mips.OP_SPECIAL:
        if mips.funct(w) in (0x21, 0x2D) and mips.rd(w) == mips.rs(w):
            return mips.rd(w), True
        if mips.funct(w) in (0x08, 0x0C, 0x0D, 0x0F, 0x11, 0x13, 0x18, 0x19, 0x1A, 0x1B, 0x29) or \
                0x30 <= mips.funct(w) <= 0x36:
            return None, False
        return mips.rd(w), False
    return None, False


# ------------------------------------------------------------------ main ELF facts

class Main:
    def __init__(self):
        cfg = K.load_config()
        orig = K.require_orig(cfg)
        seg = next(s for s in orig.segments if s.type == 1)
        self.load = seg.vaddr
        self.image = orig.data[seg.offset: seg.offset + seg.filesz]
        self.layout = K.load_layout()
        self.starts = [f.addr for f in self.layout]
        self.startset = set(self.starts)
        self.text_hi = self.layout[-1].end
        self.cf = FDR.scan_code(self.image, self.load, self.layout)
        symld = K.GEN / "symbols.ld"
        if symld.exists():
            for m in re.finditer(r"PROVIDE\(D_[0-9A-Fa-f]{8} = 0x([0-9a-f]{8})\)", symld.read_text()):
                self.cf.refs.add(int(m.group(1), 16))
        self.blob = FDR.Blob(self.image, self.load)

    def func_of(self, v: int) -> K.Func | None:
        i = bisect.bisect_right(self.starts, v) - 1
        return self.layout[i] if i >= 0 and v < max(self.layout[i].end, self.layout[i].addr + 4) else None

    def kind(self, v: int) -> str | None:
        if IMAGE_LO <= v < self.text_hi:
            return "text"
        if DATA_LO <= v < DATA_HI:
            return "data"
        if DATA_HI <= v <= IMAGE_HI:
            return "bss"
        return None

    def symbolic(self, v: int) -> tuple[str, int, str]:
        """(symbol, addend, note) for an image address, as the shift link names it."""
        k = self.kind(v)
        if k == "text":
            i = bisect.bisect_right(self.starts, v) - 1
            f = self.layout[i]
            note = "" if v == f.addr else ("inside" if v < f.end else "padding")
            return f"__dr_{f.addr:08x}", v - f.addr, note
        if k == "data":
            return "D_BLOB", v - DATA_LO, ""
        return "D_BSS", v - BSS_LO, ""

    def name(self, v: int) -> str:
        k = self.kind(v)
        if k == "text":
            i = bisect.bisect_right(self.starts, v) - 1
            f = self.layout[i]
            return f.name if v == f.addr else f"{f.name}+0x{v - f.addr:x}"
        return f"D_{v:08X}"


# ------------------------------------------------------------------ overlay analysis

class Overlay:
    def __init__(self, path: Path, main: Main):
        self.path, self.name = path, path.name
        raw = path.read_bytes()
        self.size = len(raw)
        self.data = raw + bytes(-len(raw) % 4)
        self.n = len(self.data) // 4
        self.words = struct.unpack(f"<{self.n}I", self.data)
        self.end = BASE + self.size
        self.main = main
        self.hash = kh_hash(self.name)
        self.funcs: dict[int, set[int]] = {}       # function start -> instruction addresses
        self.code: set[int] = set()
        self.calls_in: set[int] = set()            # overlay addresses called (jal/bal)
        self.jtbl_words: dict[int, int] = {}       # overlay jump-table word -> its function
        self.unresolved_jr: list[int] = []
        self.notes: list[str] = []
        self.seed_kind: dict[int, str] = {}
        self._jt: dict[int, list[int]] = {}       # jump table base -> entries
        self._jt_targets: set[int] = set()
        self.jr_sites: set[int] = set()            # jr whose table is known

    def w(self, a: int) -> int | None:
        if BASE <= a and a + 4 <= BASE + 4 * self.n and a % 4 == 0:
            return self.words[(a - BASE) >> 2]
        return None

    def in_ovl(self, a: int) -> bool:
        return BASE <= a < self.end

    # ---- descent
    def walk(self, start: int, extra: set[int] | None = None) -> tuple[set[int], str | None, set[int]]:
        """Instructions reached from `start` (calls are not followed). Returns
        (reached, error, called overlay targets)."""
        reached: set[int] = set(extra or ())
        calls: set[int] = set()
        stack = [start]
        while stack:
            a = stack.pop()
            while True:
                if a in reached:
                    break
                w = self.w(a)
                if w is None or not self.in_ovl(a):
                    return reached, f"runs out of the overlay at 0x{a:08x}", calls
                if not valid(w):
                    return reached, f"invalid instruction at 0x{a:08x}", calls
                reached.add(a)
                i = mips.Insn(a, w)
                o = mips.op(w)
                ct = i.is_branch or o in (mips.OP_J, mips.OP_JAL) or i.is_jr or i.is_jalr
                if not ct:
                    if o == 0x10 and (w & 0x3F) == 0x18 and mips.rs(w) == 0x10:  # eret
                        break
                    a += 4
                    continue
                d = self.w(a + 4)
                if d is None or not valid(d):
                    return reached, f"bad delay slot at 0x{a + 4:08x}", calls
                reached.add(a + 4)
                if i.is_branch:
                    t = i.branch_target
                    if is_bal(w):
                        if self.in_ovl(t):
                            calls.add(t)
                        a += 8
                        continue
                    if not self.in_ovl(t):
                        return reached, f"branch out of the overlay at 0x{a:08x}", calls
                    stack.append(t)
                    if uncond(w):
                        break
                    a += 8
                    continue
                if o == mips.OP_J:
                    t = i.jump_target
                    if self.in_ovl(t) and t not in self.funcs and t not in self.code:  # else a tail call
                        stack.append(t)
                    break
                if o == mips.OP_JAL:
                    t = i.jump_target
                    if self.in_ovl(t):
                        calls.add(t)
                    a += 8
                    continue
                if i.is_jalr:
                    a += 8
                    continue
                break  # jr
        return reached, None, calls

    def add_function(self, start: int, kind: str) -> str | None:
        reached, err, calls = self.walk(start)
        if err:
            return err
        self.funcs.setdefault(start, set()).update(reached)
        self.code |= reached
        self.seed_kind.setdefault(start, kind)
        for c in calls:
            self.calls_in.add(c)
        return None

    def extend_function(self, fstart: int, starts: list[int]) -> str | None:
        have = self.funcs[fstart]
        for s in starts:
            reached, err, calls = self.walk(s, have)
            if err:
                return err
            have |= reached
            self.code |= reached
            self.calls_in |= calls
        return None

    def discover(self) -> None:
        err = self.add_function(BASE, "entry")
        if err:
            self.notes.append(f"entry: {err}")
        self.settle_calls()
        # overlay-internal code pointers: built with %hi/%lo or held in data. Strong
        # starts (8-aligned prologue) first, then jump tables again (their cases also
        # look like starts after a `b`), and only then a weak start (after a function end)
        rounds = 0
        while rounds < 200:
            rounds += 1
            changed = self.jump_tables()
            self.settle_calls()
            if changed:
                continue
            ptrs = {t: why for t, why in self.internal_pointers().items()
                    if t not in self.funcs and t not in self.code and self.looks_like_start(t)}
            strong = [t for t in sorted(ptrs) if self.prologue(t)]
            added = False
            for t in strong or sorted(ptrs):
                if t in self.code:
                    continue
                reached, err, _c = self.walk(t)
                if err:
                    continue
                self.add_function(t, ptrs[t])
                added = True
                if not strong:
                    break  # one weak start at a time, then jump tables again
            self.settle_calls()
            if not added:
                break
        # gaps of the code span, and functions right after its end
        self.fill_gaps()
        self.settle_calls()
        self.extend_tail()
        self.settle_calls()
        self.jump_tables()
        self.settle_calls()

    def settle_calls(self) -> None:
        while True:
            todo = [c for c in self.calls_in if c not in self.funcs]
            if not todo:
                return
            for c in todo:
                err = self.add_function(c, "jal")
                if err:
                    self.notes.append(f"call target 0x{c:08x}: {err}")
                    self.funcs.setdefault(c, set())

    def after_end(self, t: int) -> bool:
        """t follows the end of a function (jr ra / j and its delay slot), maybe
        after zero padding."""
        p = t - 4
        while p >= BASE and self.w(p) == 0 and p not in self.code:
            p -= 4
        if p < BASE:
            return True
        prev = self.w(p - 4) if p - 4 >= BASE else None
        return prev is not None and (prev == mips.JR_RA or mips.op(prev) == mips.OP_J or uncond(prev))

    def prologue(self, t: int) -> bool:
        w = self.w(t)
        return t % 8 == 0 and w is not None and (mips.Insn(t, w).stack_adjust or 0) < 0

    def looks_like_start(self, t: int) -> bool:
        """A function start: a valid first instruction and either 8-aligned
        (gcc) with a prologue (`addiu sp,sp,-N`), or right after the end of a
        function (then any 4-alignment: hand-written asm)."""
        if t % 4 or not self.in_ovl(t) or t in self.code:
            return False
        w = self.w(t)
        if w is None or w == 0 or not valid(w):
            return False
        if t % 8 == 0 and (mips.Insn(t, w).stack_adjust or 0) < 0:
            return True
        return self.after_end(t)

    def fill_gaps(self) -> None:
        """Non-zero words inside the code span that follow a function end and
        decode as a whole function (dead code, or reached through a pointer
        the analysis does not see) are code too."""
        if not self.code:
            return
        hi = max(self.code) + 4
        a = BASE
        while a < hi:
            if a in self.code or a in self.jtbl_words or self.w(a) == 0:
                a += 4
                continue
            if self.looks_like_start(a):
                reached, err, _c = self.walk(a)
                if not err:
                    self.add_function(a, "gap")
                    self.settle_calls()
                    hi = max(hi, max(self.code) + 4)
            a += 4

    def extend_tail(self) -> None:
        """.text is contiguous: after the last known function, keep taking the
        next function (after zero padding) while it decodes as a whole function
        that ends in jr ra / j and stays within 64 KiB; the first failure is the
        start of the data."""
        while self.code:
            a = max(self.code) + 4
            while a < self.end and self.w(a) == 0:
                a += 4
            if a >= self.end or not self.looks_like_start(a):
                return
            reached, err, _c = self.walk(a)
            if err or max(reached) - a > 0x10000 or min(reached) < a or not any(
                    self.w(x) == mips.JR_RA or mips.op(self.w(x)) == mips.OP_J for x in reached):
                return
            self.add_function(a, "tail")
            self.settle_calls()
            self.fill_gaps()
            self.jump_tables()
            self.settle_calls()

    def func_ranges(self) -> list[tuple[int, int, int]]:
        out = []
        for s, ins in sorted(self.funcs.items()):
            if ins:
                out.append((s, min(ins), max(ins) + 4))
        return out

    def linear(self, lo: int, hi: int, insns: set[int]):
        """Linear tracker over [lo, hi) (only code): yields (addr, word, state before)."""
        labels = set()
        for a in range(lo, hi, 4):
            if a in insns:
                t = mips.Insn(a, self.w(a)).branch_target
                if t is not None:
                    labels.add(t)
        labels |= {x for x in self._jt_targets if lo <= x < hi}
        st: dict[int, tuple] = {}
        clobber_at = None
        for a in range(lo, hi, 4):
            if a not in insns:
                st = {}
                continue
            w = self.w(a)
            if a in labels:
                st = {}
            yield a, w, st  # (after a call: the argument registers are still visible here)
            if a == clobber_at:
                st = {r: v for r, v in st.items() if r not in CALLER_SAVED}
            o = mips.op(w)
            rs, rt, rd = mips.rs(w), mips.rt(w), mips.rd(w)
            if o == mips.OP_JAL or (o == 0 and mips.funct(w) == 0x09) or is_bal(w):
                clobber_at = a + 8
            s = st.get(rs)
            if o == mips.OP_LUI:
                st[rt] = ("hi", (w & 0xFFFF) << 16)
                continue
            mem = o in mips.OP_LOADS or o in mips.OP_STORES or o in mips.OP_VU_MEM or o in (mips.OP_LQ, mips.OP_SQ)
            if s and o == 0x09 and s[0] in ("hi", "addr"):
                st[rt] = ("addr", (s[1] + mips.imm(w)) & 0xFFFFFFFF)
                continue
            if s and mem and s[0] in ("hi", "hix", "addr", "addrx") and o == 0x23:
                st[rt] = ("ld", (s[1] + mips.imm(w)) & 0xFFFFFFFF, s[0] in ("hix", "addrx"))
                continue
            if o == 0 and mips.funct(w) in (0x21, 0x2D, 0x25) and 0 in (rs, rt) and rd:
                x = st.get(rs or rt)
                if x and x[0] in ("addr", "hi"):
                    st[rd] = x
                else:
                    st.pop(rd, None)
                continue
            if o == 0 and mips.funct(w) in (0x21, 0x2D) and rd:
                for x in (st.get(rs), st.get(rt)):
                    if x and x[0] in ("hi", "addr"):
                        st[rd] = ("hix" if x[0] == "hi" else "addrx", x[1])
                        break
                else:
                    st.pop(rd, None)
                continue
            r, _keep = gpr_written(w)
            if r:
                st.pop(r, None)

    def jump_tables(self) -> bool:
        """jr through a word loaded from an indexed overlay table: read entries
        (bound: the nearest sltiu before it) while they point into the overlay."""
        found = False
        for fs, lo, hi in self.func_ranges():
            ins = self.funcs[fs]
            prev: list[tuple[int, int]] = []
            for a, w, st in self.linear(lo, hi, ins):
                prev.append((a, w))
                i = mips.Insn(a, w)
                if not i.is_jr or i.is_jr_ra or a in self.jr_sites:
                    continue
                s = st.get(mips.rs(w))
                if not (s and s[0] == "ld" and s[2] and self.in_ovl(s[1])):
                    continue
                base = s[1]
                bound = next((pw & 0xFFFF for pa, pw in reversed(prev[-24:]) if mips.op(pw) == 0x0B), 512)
                entries = []
                for k in range(bound):
                    t = self.w(base + 4 * k)
                    if t is None or not self.in_ovl(t) or t % 4 or (base + 4 * k) in self.code:
                        break
                    tw = self.w(t)
                    if tw is None or not valid(tw):
                        break
                    entries.append(t)
                if not entries:
                    continue
                self.jr_sites.add(a)
                self._jt[base] = entries
                for k, t in enumerate(entries):
                    self.jtbl_words[base + 4 * k] = fs
                self._jt_targets |= set(entries)
                err = self.extend_function(fs, entries)
                if err:
                    self.notes.append(f"jump table 0x{base:08x} of 0x{fs:08x}: {err}")
                found = True
        return found

    def internal_pointers(self) -> dict[int, str]:
        """Overlay addresses code builds with lui/addiu, and aligned words of
        non-code bytes whose value is in the overlay: candidate code pointers."""
        out: dict[int, str] = {}
        for fs, lo, hi in self.func_ranges():
            for a, w, st in self.linear(lo, hi, self.funcs[fs]):
                s = st.get(mips.rs(w))
                if s and mips.op(w) == 0x09 and s[0] == "hi":
                    v = (s[1] + mips.imm(w)) & 0xFFFFFFFF
                    if self.in_ovl(v):
                        out.setdefault(v, "hilo")
        for k, v in enumerate(self.words):
            a = BASE + 4 * k
            if a not in self.code and a not in self.jtbl_words and self.in_ovl(v):
                out.setdefault(v, "word")
        return out

    # ---- flow pairing
    def flow_pairs(self):
        """Per function: reaching lui definitions at every low-half user.
        Returns ({lo addr: (full, {lui addrs}, op)}, warnings)."""
        pairs: dict[int, tuple[int, frozenset, int]] = {}
        warn: list[str] = []
        lone_luis: set[int] = set()
        for fs, ins in self.funcs.items():
            if not ins:
                continue
            order = sorted(ins)
            idx = {a: k for k, a in enumerate(order)}
            n = len(order)
            succ: list[list[tuple[int, bool]]] = [[] for _ in range(n)]

            def is_ct(w: int) -> bool:
                i = mips.Insn(0, w)
                return i.is_branch or mips.op(w) in (mips.OP_J, mips.OP_JAL) or i.is_jr or i.is_jalr
            # a delay slot's successors come from its branch (no fall-through of its own)
            slots = {a + 4 for a in order if is_ct(self.w(a))}
            for k, a in enumerate(order):
                w = self.w(a)
                i = mips.Insn(a, w)
                o = mips.op(w)
                ct = is_ct(w)
                if not ct:
                    if a + 4 in idx and a not in slots:
                        succ[k].append((idx[a + 4], False))
                    continue
                d = idx.get(a + 4)
                if d is None:
                    continue
                succ[k].append((d, False))
                lk = likely(w)
                if lk and a + 8 in idx:
                    succ[k].append((idx[a + 8], False))  # not taken: delay slot skipped
                outs: list[tuple[int, bool]] = []
                if i.is_branch:
                    if is_bal(w):
                        if a + 8 in idx:
                            outs.append((idx[a + 8], True))
                    else:
                        t = i.branch_target
                        if t in idx:
                            outs.append((idx[t], False))
                        if not uncond(w) and not lk and a + 8 in idx:
                            outs.append((idx[a + 8], False))
                elif o == mips.OP_J:
                    t = i.jump_target
                    if t in idx:
                        outs.append((idx[t], False))
                elif o == mips.OP_JAL or i.is_jalr:
                    if a + 8 in idx:
                        outs.append((idx[a + 8], True))
                elif i.is_jr and not i.is_jr_ra:
                    outs += [(idx[t], False) for t in self._jt_targets if t in idx]
                succ[d] += outs
            state: list[dict | None] = [None] * n
            for root in [idx[fs]] + list(range(n)):  # the entry first; then code only it cannot reach
                if state[root] is not None:
                    continue
                state[root] = {}
                work = [root]
                while work:
                    k = work.pop()
                    st = dict(state[k])
                    w = self.words[(order[k] - BASE) >> 2]
                    if mips.op(w) == mips.OP_LUI:
                        st[mips.rt(w)] = frozenset([k])
                    elif is_move(w) and mips.rd(w):
                        src = st.get(mips.rs(w) or mips.rt(w))
                        if src:
                            st[mips.rd(w)] = src  # move rd, rs keeps the %hi (lui copied)
                        else:
                            st.pop(mips.rd(w), None)
                    else:
                        r, keep = gpr_written(w)
                        if r and not keep:
                            st.pop(r, None)
                    for s2, clob in succ[k]:
                        out = {r: v for r, v in st.items() if r not in CALLER_SAVED} if clob else st
                        cur = state[s2]
                        if cur is None:
                            state[s2] = dict(out)
                            work.append(s2)
                            continue
                        # a register absent from a state holds something else than a lui value
                        # (UNK): the merge keeps that, so a low half reached by a lui on one path
                        # and by any other value on another is not taken for a pair
                        ch = False
                        for r in set(cur) | set(out):
                            old = cur.get(r, UNK)
                            nv = old | out.get(r, UNK)
                            if nv != old:
                                cur[r] = nv
                                ch = True
                        if ch:
                            work.append(s2)
            used_luis: set[int] = set()
            for k, a in enumerate(order):
                st = state[k]
                w = self.w(a)
                o = mips.op(w)
                if o == mips.OP_LUI:
                    lone_luis.add(a)
                if st is None or o not in LO_OPS:
                    continue
                base = mips.rs(w)
                if base not in st:
                    continue
                if -1 in st[base]:
                    fulls = {(((self.words[(order[l] - BASE) >> 2] & 0xFFFF) << 16) + mips.imm(w)) & 0xFFFFFFFF
                             for l in st[base] if l >= 0}
                    if any(IMAGE_LO <= f <= IMAGE_HI for f in fulls):
                        warn.append(f"0x{a:08x}: reached by a lui (0x{min(fulls):08x}) on one path and by "
                                    f"another value on another: not fixed")
                    continue
                luis = frozenset(order[l] for l in st[base])
                fulls = {(((self.w(l) & 0xFFFF) << 16) + (mips.imm(w) if o != 0x0D else w & 0xFFFF)) & 0xFFFFFFFF
                         for l in luis}
                used_luis |= luis
                if len(fulls) > 1:
                    if any(IMAGE_LO <= f <= IMAGE_HI for f in fulls):
                        warn.append(f"0x{a:08x}: reached by luis with different values "
                                    + ", ".join(f"0x{f:08x}" for f in sorted(fulls)))
                    continue
                full = fulls.pop()
                prev = pairs.get(a)
                if prev and prev[0] != full:
                    warn.append(f"0x{a:08x}: two functions pair it differently")
                pairs[a] = (full, luis | (prev[1] if prev else frozenset()), o)
            lone_luis -= used_luis
        return pairs, warn, lone_luis


# ------------------------------------------------------------------ classification

TIER_OF = {"calltab": "1", "ftab": "1", "func": "1", "dma-chain": "1",
           "func-s16": "2", "dref": "2", "bref": "2", "oref": "2", "ptab": "2", "str": "2", "stride": "2",
           "dma": "3",
           "dptr-run": "3", "bptr-run": "3", "dptr": "3", "bptr": "3", "mirror": "3"}
REASONS = {
    "calltab": "main function start in an overlay table/word the overlay code loads and calls through",
    "ftab": "main function start in a run of >=3 function-start words",
    "func": "lone main function start",
    "func-s16": "main function start, s16-like neighbours (kept: starts are rare by chance)",
    "dref": "main data address the main ELF's code builds with %hi/%lo (or a D_ name src uses)",
    "bref": "main bss address the main ELF's code builds",
    "oref": "main data/bss address the overlay's own code builds with %hi/%lo",
    "ptab": "word in an overlay table/variable the overlay code loads and dereferences",
    "str": "start of a NUL-terminated string in the main data",
    "stride": "same offset as accepted pointers in a repeating record (stride 8-64, both sides)",
    "dma": "ADDR word of a tag-shaped qword (REF/REFS/REFE/NEXT/CALL, valid bits) no kicked chain reaches",
    "dma-chain": "ADDR word of a DMA tag the overlay code kicks",
    "dptr-run": "aligned main data target next to other pointer words",
    "bptr-run": "aligned main bss target next to other pointer words",
    "dptr": "aligned main data target, isolated, no rule against it (ambiguous remainder)",
    "bptr": "aligned main bss target, isolated, no rule against it (ambiguous remainder)",
    "mirror": "0x20000000/0x30000000 mirror of a 16-aligned address code builds",
    # rejects
    "into-func": "inside a main function (not a start): a number",
    "unaligned": "data/bss target not 4-aligned and not a string start",
    "s16": "s16 pairs / repeated value around it",
    "vucode": "VU microcode around it",
    "ascii": "ASCII text",
    "bytes": "packed bytes around it",
    "mipscode": "MIPS instructions around it (not reached as code)",
    "colour": "colour values around it",
    "float": "plausible floats around it, no pointer run",
    "mirror-x": "mirror of an address no code builds",
    "payload": "inside what a DMA tag transfers",
    "resfile": "inside a relocatable resource file the overlay code fixes up (func_001763f0)",
    "script": "inside a byte stream handed to the script VM / message parser",
}


def classify_words(ov: Overlay, main: Main, pairs: dict, code_refs: set[int], tracker) -> dict[int, tuple]:
    """{word addr: (value, mirror, kind, reason)} for every non-code aligned word
    whose value (or its 0x20/0x30 mirror base) is in the image."""
    cands: dict[int, tuple[int, int, str]] = {}
    for k, v in enumerate(ov.words):
        x = BASE + 4 * k
        if x in ov.code or x in ov.jtbl_words or x + 4 > ov.end:
            continue
        kd = main.kind(v)
        if kd:
            cands[x] = (v, 0, kd)
            continue
        hb = v & 0xF0000000
        if hb in MIRRORS and main.kind(v - hb) in ("data", "bss") and (v - hb) % 16 == 0:
            cands[x] = (v - hb, hb, "mirror")
    refs = main.cf.refs
    call_words, call_tables, ptr_words, ptr_tables, dma_heads, res_bases, scripts = tracker

    def w(a):
        if a in ov.code:
            return None
        return ov.w(a)

    def extend(bases):
        out = set()
        for b in bases:
            x = b
            while ov.in_ovl(x) and x not in ov.code:
                v = w(x)
                if v is None or not (v == 0 or main.kind(v)):
                    break
                out.add(x)
                x += 4
        return out
    typed_call = extend(call_tables) | set(call_words)
    typed_ptr = extend(ptr_tables) | set(ptr_words)
    ovl_refs = sorted(r for r in code_refs if ov.in_ovl(r))

    def region(bases):
        rng = []
        for b in sorted(bases):
            if ov.in_ovl(b):
                j = bisect.bisect_right(ovl_refs, b)
                rng.append((b, ovl_refs[j] if j < len(ovl_refs) else ov.end))
        return rng
    res_rng, scr_rng = region(res_bases), region(scripts)

    def in_rng(rng, x):
        return any(a <= x < b for a, b in rng)

    # DMA tags kicked from overlay code / tag-shaped qwords
    def tag_ok(t):
        tag, adr = w(t), w(t + 4)
        if tag is None or adr is None or t % 16:
            return False
        idn = (tag >> 28) & 7
        return not (tag >> 16) & 0x3FF and not (tag >> 26) & 3 and not tag & 0x80000000 and \
            idn in (0, 1, 2, 3, 4, 5) and adr % 16 == 0
    walked = set()
    for h in dma_heads:
        t = h
        for _ in range(4096):
            if not ov.in_ovl(t) or not tag_ok(t) or t in walked:
                break
            walked.add(t)
            tag = w(t)
            idn, qwc, adr = (tag >> 28) & 7, tag & 0xFFFF, w(t + 4)
            if idn == 7 or idn == 0:
                break
            if idn in (3, 4):
                t += 16
            elif idn == 1:
                t += 16 + 16 * qwc
            elif idn == 2:
                t = adr
            else:
                break
    payload = set()
    for t in walked:
        tag, adr = w(t), w(t + 4)
        idn, qwc = (tag >> 28) & 7, tag & 0xFFFF
        base = adr if idn in (0, 3, 4) else t + 16
        payload.update(range(base, base + 16 * qwc, 4))

    decided: dict[int, str] = {}
    starts = main.startset
    xs = sorted(x for x, (v, m, k) in cands.items() if m == 0 and v in starts)
    run_of: dict[int, int] = {}
    i = 0
    while i < len(xs):
        j = i
        while j + 1 < len(xs) and xs[j + 1] - xs[j] <= 8:
            j += 1
        for x in xs[i:j + 1]:
            run_of[x] = j - i + 1
        i = j + 1

    def neighbours(x, r=2):
        out = []
        for d in range(-r, r + 1):
            if d:
                v = w(x + 4 * d)
                if v is not None:
                    out.append(v)
        return out

    for x, (v, m, k) in cands.items():
        if m:
            continue
        if x in payload and x - 4 not in walked:
            decided[x] = "payload"
            continue
        if in_rng(res_rng, x):
            decided[x] = "resfile"
            continue
        if k == "text":
            if v in starts:
                nb = neighbours(x)
                if x not in typed_call and len(nb) == 4 and sum(1 for u in nb if FDR.noisy(u)) >= 3:
                    decided[x] = "bytes"  # a start by chance inside packed bytes
                elif x in typed_call:
                    decided[x] = "calltab"
                elif run_of.get(x, 1) >= 3:
                    decided[x] = "ftab"
                elif in_rng(scr_rng, x):
                    decided[x] = "script"
                elif sum(1 for u in nb if FDR.s16_small(u) and not main.kind(u) and u) >= 3:
                    decided[x] = "func-s16"
                else:
                    decided[x] = "func"
            else:
                decided[x] = "into-func" if v % 4 == 0 else "unaligned"
            continue
        nb_np = [u for u in neighbours(x) if not main.kind(u)]
        if FDR.ascii_word(v) and sum(1 for u in nb_np if FDR.ascii_word(u)) >= 2 and x not in typed_ptr:
            decided[x] = "ascii"  # text that happens to spell an address
            continue
        if v % 4:
            decided[x] = "str" if k == "data" and FDR.string_start(main.blob, v) else "unaligned"
            continue
        if x - 4 in walked:
            decided[x] = "dma-chain"
            continue
        if x % 16 == 4 and tag_ok(x - 4) and (w(x - 8) is None or True) and ((w(x - 4) >> 28) & 7) in (0, 2, 3, 4, 5):
            decided[x] = "dma"
            continue
        if v in refs and not (FDR.s16_small(v) or FDR.is_rgb0(v)):
            decided[x] = "dref" if k == "data" else "bref"
            continue
        if v in code_refs and not (FDR.s16_small(v) or FDR.is_rgb0(v)):
            decided[x] = "oref"
            continue
        if x in typed_ptr or x in typed_call:
            decided[x] = "ptab"
            continue
        if k == "data" and FDR.string_start(main.blob, v):
            decided[x] = "str"
            continue
        decided[x] = "?"

    def accepted(y):
        r = decided.get(y)
        return r is not None and r in TIER_OF

    repeats = collections.Counter(cands[x][0] for x, r in decided.items() if r == "?")
    for x, r in list(decided.items()):
        if r != "?":
            continue
        v, _m, k = cands[x]
        if any(accepted(x - s) and accepted(x + s) and cands[x - s][2] == k == cands[x + s][2]
               for s in range(8, 68, 4)):
            decided[x] = "stride"
            continue
        nb, nb4 = neighbours(x), neighbours(x, 4)
        nb_np = [u for u in nb if not main.kind(u)]
        accepted_near = any(accepted(x + d) for d in (-8, -4, 4, 8))
        ptr_run = [cands[x + d][0] for d in (-8, -4, 4, 8) if x + d in cands and cands[x + d][1] == 0]
        distinct_run = any(u != v for u in ptr_run)
        s16v = FDR.s16_small(v)
        if in_rng(scr_rng, x):
            decided[x] = "script"
        elif any(u in FDR.VU_NOPS for u in nb4):
            decided[x] = "vucode"
        elif FDR.ascii_word(v) and sum(1 for u in nb_np if FDR.ascii_word(u)) >= 2:
            decided[x] = "ascii"
        elif len(nb) == 4 and sum(1 for u in nb if FDR.noisy(u)) >= 3:
            decided[x] = "bytes"
        elif (s16v or repeats[v] >= 8) and (
                (s16v and repeats[v] >= 8) or any(FDR.is_colour(u) for u in nb)
                or sum(1 for d in (-8, -4, 4, 8) if not accepted(x + d) and (w(x + d) or 0) & 0xFFFF0000
                       and FDR.s16_small(w(x + d) or 0)) >= 2):
            decided[x] = "s16"
        elif sum(1 for u in nb if FDR.mips_like(u) and not FDR.s16_small(u)) >= 3:
            decided[x] = "mipscode"
        elif FDR.is_rgb0(v) and sum(1 for u in nb if FDR.is_rgb0(u) or FDR.is_colour(u)) >= 2:
            decided[x] = "colour"
        elif not accepted_near and not distinct_run and any(FDR.is_colour(u) or FDR.is_rgb0(u) for u in nb):
            decided[x] = "colour"
        elif not accepted_near and not distinct_run and len(nb) >= 4 and all(FDR.fbits_plausible(u) for u in nb) \
                and sum(1 for u in nb if u) >= 3:
            decided[x] = "float"
        elif distinct_run or accepted_near:
            decided[x] = "dptr-run" if k == "data" else "bptr-run"
        else:
            decided[x] = "dptr" if k == "data" else "bptr"
    for x, (v, m, k) in cands.items():
        if m:
            decided[x] = "mirror" if (v in refs or v in code_refs) else "mirror-x"
    return {x: (*cands[x], decided[x]) for x in decided}


def overlay_tracker(ov: Overlay):
    """Facts from the overlay's code (linear tracker, like find_data_relocs.scan_code):
    words loaded and called / dereferenced, and typed call arguments (DMA heads,
    resource files, byte streams) for overlay addresses."""
    call_words, call_tables, ptr_words, ptr_tables = set(), set(), set(), set()
    dma_heads, res_bases, scripts = set(), set(), set()
    watched = {t: v[0] for t, v in FDR.WATCHED_CALLS.items()}
    areg = {t: v[1] for t, v in FDR.WATCHED_CALLS.items()}
    stored: dict[int, set[int]] = collections.defaultdict(set)  # overlay variable -> overlay addresses stored
    via_var: list[tuple[str, int]] = []  # (kind, variable) whose loaded value is passed to a watched call
    for fs, lo, hi in ov.func_ranges():
        pending = None
        for a, w, st in ov.linear(lo, hi, ov.funcs[fs]):
            if pending and a == pending[1]:
                kind_, r = pending[0]
                s = st.get(r)
                tgt = {"dma": dma_heads, "res": res_bases, "script": scripts}.get(kind_)
                if s and s[0] == "addr" and ov.in_ovl(s[1]) and tgt is not None:
                    tgt.add(s[1])
                elif s and s[0] == "ld" and not s[2] and ov.in_ovl(s[1]) and tgt is not None:
                    via_var.append((kind_, s[1]))
                pending = None
            if mips.op(w) == 0x2B:  # sw: an overlay address stored into an overlay variable
                v_, b_ = st.get(mips.rt(w)), st.get(mips.rs(w))
                if v_ and v_[0] == "addr" and ov.in_ovl(v_[1]) and b_ and b_[0] in ("hi", "addr"):
                    stored[(b_[1] + mips.imm(w)) & 0xFFFFFFFF].add(v_[1])
            o = mips.op(w)
            if o in (mips.OP_J, mips.OP_JAL):
                t = mips.Insn(a, w).jump_target
                if t in watched:
                    pending = ((watched[t], areg[t]), a + 8)
            if o == 0 and mips.funct(w) in (0x08, 0x09) and w != mips.JR_RA:
                s = st.get(mips.rs(w))
                if s and s[0] == "ld":
                    (call_tables if s[2] else call_words).add(s[1])
            mem = o in mips.OP_LOADS or o in mips.OP_STORES or o in mips.OP_VU_MEM or o in (mips.OP_LQ, mips.OP_SQ)
            s = st.get(mips.rs(w))
            if s and s[0] == "ld" and mem:
                (ptr_tables if s[2] else ptr_words).add(s[1])
    for kind_, var in via_var:
        {"dma": dma_heads, "res": res_bases, "script": scripts}[kind_].update(stored.get(var, ()))
    return call_words, call_tables, ptr_words, ptr_tables, dma_heads, res_bases, scripts


# ------------------------------------------------------------------ per overlay

def analyze(ov: Overlay, main: Main, max_tier: int) -> dict:
    ov.discover()
    pairs, warn, lone = ov.flow_pairs()
    # linear cross-check (like asm_export: report disagreements)
    lin: dict[int, int] = {}
    for fs, lo, hi in ov.func_ranges():
        for a, w, st in ov.linear(lo, hi, ov.funcs[fs]):
            s = st.get(mips.rs(w))
            if s and s[0] == "hi" and mips.op(w) in LO_OPS:
                lin[a] = (s[1] + (mips.imm(w) if mips.op(w) != 0x0D else w & 0xFFFF)) & 0xFFFFFFFF
    disagree = [a for a, full in lin.items() if IMAGE_LO <= full <= IMAGE_HI and
                (a not in pairs or pairs[a][0] != full)]
    fix: list[dict] = []
    ambiguous: list[str] = []
    mid: list[str] = []
    code_refs = set()
    counts = collections.Counter()
    # jal / j
    for a in sorted(ov.code):
        w = ov.w(a)
        o = mips.op(w)
        if o in (mips.OP_J, mips.OP_JAL):
            t = mips.Insn(a, w).jump_target
            if main.kind(t) == "text":
                sym, add, note = main.symbolic(t)
                fix.append({"off": a - BASE, "kind": J26, "old": t})
                counts["jal" if o == mips.OP_JAL else "j"] += 1
                if note:
                    mid.append(f"0x{a:08x} {'jal' if o == mips.OP_JAL else 'j'} {main.name(t)} ({note})")
            elif main.kind(t):
                ambiguous.append(f"0x{a:08x} jump into main data 0x{t:08x}")
    # hi/lo
    hi_target: dict[int, int] = {}
    lo_rows = []
    for a, (full, luis, o) in sorted(pairs.items()):
        code_refs.add(full)
        if not IMAGE_LO <= full <= IMAGE_HI:
            continue
        if o == 0x0D:
            ambiguous.append(f"0x{a:08x} lui/ori 0x{full:08x} ({main.name(full)}): a constant? not fixed")
            continue
        if len(luis) > 1 and len({ov.w(l) & 0xFFFF for l in luis}) > 1:
            ambiguous.append(f"0x{a:08x} low half of luis with different values")
            continue
        for l in sorted(luis):
            hi_target.setdefault(l, full)
            lo_rows.append({"off": a - BASE, "kind": LO16, "old": full, "hi": l - BASE})
        counts["hilo"] += 1
    for l, full in sorted(hi_target.items()):
        fix.append({"off": l - BASE, "kind": HI16, "old": full})
    fix += lo_rows
    for l in sorted(lone):
        v = (ov.w(l) & 0xFFFF) << 16
        if IMAGE_LO <= v <= IMAGE_HI + 0x8000:
            ambiguous.append(f"0x{l:08x} lui 0x{v >> 16:04x} with no low half in the image range (not fixed)")
    ambiguous += [f"{x}" for x in warn]
    ambiguous += [f"0x{a:08x}: linear and flow trackers disagree" for a in disagree]
    # words
    tracker = overlay_tracker(ov)
    words = classify_words(ov, main, pairs, code_refs | {p[0] for p in pairs.values()}, tracker)
    wcount = collections.Counter()
    for x, (v, m, k, r) in sorted(words.items()):
        tier = TIER_OF.get(r, "x")
        wcount[(tier, r)] += 1
        if tier != "x" and int(tier) <= max_tier:
            fix.append({"off": x - BASE, "kind": WORD, "old": (v + m) & 0xFFFFFFFF, "base": v, "hb": m})
            counts["word"] += 1
            if k == "text" and v not in main.startset:
                mid.append(f"0x{x:08x} word {main.name(v)} (inside)")
    # code coverage
    code_lo, code_hi = (min(ov.code), max(ov.code) + 4) if ov.code else (BASE, BASE)
    gaps = 0
    for a in range(code_lo, code_hi, 4):
        if a not in ov.code and a not in ov.jtbl_words and ov.w(a):
            gaps += 1
    stray = sum(1 for a in ov.code if a >= code_hi)
    return {"fix": fix, "ambiguous": ambiguous, "mid": mid, "counts": counts, "wcount": wcount,
            "words": words, "pairs": pairs, "code_span": (code_lo, code_hi), "gap_words": gaps,
            "n_code": len(ov.code), "n_funcs": len(ov.funcs), "seed_kinds": collections.Counter(ov.seed_kind.values()),
            "jtbls": len(ov._jt), "unresolved_jr": unresolved_jr(ov), "notes": ov.notes,
            "stray": stray}


def unresolved_jr(ov: Overlay) -> list[int]:
    out = []
    for a in ov.code:
        w = ov.w(a)
        i = mips.Insn(a, w)
        if i.is_jr and not i.is_jr_ra and a not in ov.jr_sites:
            out.append(a)
    return sorted(out)


# ------------------------------------------------------------------ output

def emit(results: list[tuple[Overlay, dict]], main: Main) -> tuple[str, set[int], dict]:
    lines = ["/* Auto-generated by tools/shift/overlay_relocs.py from the user's overlays.",
             " * Build input of the shiftable build (out/ only, never commit). Offsets, kinds,",
             " * symbols and original main-ELF addresses only: no overlay bytes. */",
             '\t.section .ovl_fixups,"a",@progbits',
             "\t.align 4",
             "\t.globl kh1_ovl_fixups",
             "kh1_ovl_fixups:",
             f"\t.word 0x{MAGIC:08x}, {VERSION}, {len(results)}"]
    body = []
    labels: set[int] = set()
    js = {"overlays": []}
    for n, (ov, r) in enumerate(results):
        order = {J26: 0, WORD: 1, HI16: 2, LO16: 3}
        fx = sorted(r["fix"], key=lambda f: (order[f["kind"]], f["off"]))
        targets: list[int] = []
        tix: dict[int, int] = {}
        for f in fx:
            t = f["old"]
            if t not in tix:
                tix[t] = len(targets)
                targets.append(t)
            f["tidx"] = tix[t]
        if len(targets) > MAX_TIDX or ov.n > MAX_WOFF:
            raise SystemExit(f"error: {ov.name}: {len(targets)} targets / {ov.n} words exceed the table format")
        lines.append(f"\t.word 0x{ov.hash:08x}, {ov.size}, {len(fx)}, .Lent{n} - kh1_ovl_fixups, "
                     f"{len(targets)}, .Ltgt{n} - kh1_ovl_fixups  /* {ov.name} */")
        body.append(f".Lent{n}:  /* {ov.name} */")
        for f in fx:
            word = (f["kind"] << 30) | (f["tidx"] << 18) | (f["off"] >> 2)
            body.append(f"\t.word 0x{word:08x}")
            if f["kind"] == LO16:
                body.append(f"\t.word 0x{f['hi'] >> 2:08x}")
        body.append(f".Ltgt{n}:")
        for t in targets:
            hb = 0
            base = t
            if not main.kind(t):
                hb = t & 0xF0000000
                base = t - hb
            sym, add, _note = main.symbolic(base)
            add += hb
            if sym.startswith("__dr_"):
                labels.add(int(sym[5:], 16))
            body.append(f"\t.word {sym}{'+' if add >= 0 else '-'}0x{abs(add):x}, 0x{t:08x}")
        js["overlays"].append({"name": ov.name, "hash": ov.hash, "size": ov.size,
                               "fix": [{k: v for k, v in f.items() if k in ("off", "kind", "old", "hi", "tidx")}
                                       for f in fx], "targets": targets})
    lines += body
    lines.append("\t.globl kh1_ovl_fixups_end")
    lines.append("kh1_ovl_fixups_end:")
    return "\n".join(lines) + "\n", labels, js


def main_() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--overlays", type=Path, default=K.OUT / "overlays")
    ap.add_argument("--out-dir", type=Path, default=K.OUT / "shift")
    ap.add_argument("--tier", type=int, default=2,
                    help="emit data words with tier <= N (default 2: code evidence; tier 3 is reported only)")
    ap.add_argument("--report", action="store_true", help="print the full report (else a summary)")
    ap.add_argument("--debug", action="store_true", help="write ovl_debug.tsv (word values: out/ only)")
    a = ap.parse_args()
    out = a.out_dir.resolve()
    if K.OUT.resolve() not in (out, *out.parents):
        sys.exit("error: --out-dir must be under out/ (its files are derived from the user's overlays)")
    out.mkdir(parents=True, exist_ok=True)
    files = []
    if a.overlays.is_dir():
        files = sorted(p for p in a.overlays.iterdir() if p.suffix == ".x" and p.is_file())
    unknown = [p.name for p in files if p.name not in OVERLAYS]
    main = Main() if files else None
    results = []
    report = []
    for p in files:
        ov = Overlay(p, main)
        r = analyze(ov, main, a.tier)
        results.append((ov, r))
    if files:
        hashes = collections.Counter(ov.hash for ov, _r in results)
        dup = [n for n, c in hashes.items() if c > 1]
        if dup:
            sys.exit(f"error: overlay name hashes collide: {dup}")
        s, labels, js = emit(results, main)
    else:
        s, labels, js = emit([], None)
    (out / "ovl_fixups.s").write_text(s)
    (out / "ovl_labels.txt").write_text("".join(f"{x:08x}\n" for x in sorted(labels)))
    (out / "ovl_fixups.json").write_text(json.dumps(js))
    # report
    tot = collections.Counter()
    hdr = (f"{'overlay':14} {'bytes':>7} {'code':>7} {'funcs':>5} {'jtbl':>4} {'jal':>5} {'j':>4} {'hi/lo':>5} "
           f"{'words':>5} {'rej':>5} {'amb':>4} {'mid':>4} {'fixups':>6}")
    report.append(hdr)
    for ov, r in results:
        c = r["counts"]
        rej = sum(v for (t, _k), v in r["wcount"].items() if t == "x")
        amb3 = sum(v for (t, _k), v in r["wcount"].items() if t == "3")
        nfix = len(r["fix"])
        tot.update(c)
        tot["rej"] += rej
        tot["amb"] += len(r["ambiguous"]) + amb3
        tot["mid"] += len(r["mid"])
        tot["fix"] += nfix
        report.append(f"{ov.name:14} {ov.size:7d} {4 * r['n_code']:7d} {r['n_funcs']:5d} {r['jtbls']:4d} "
                      f"{c['jal']:5d} {c['j']:4d} {c['hilo']:5d} {c['word']:5d} {rej:5d} "
                      f"{len(r['ambiguous']) + amb3:4d} {len(r['mid']):4d} {nfix:6d}")
    report.append(f"{'total':14} {'':7} {'':7} {'':5} {'':4} {tot['jal']:5d} {tot['j']:4d} {tot['hilo']:5d} "
                  f"{tot['word']:5d} {tot['rej']:5d} {tot['amb']:4d} {tot['mid']:4d} {tot['fix']:6d}")
    detail = []
    for ov, r in results:
        detail.append(f"\n== {ov.name} (hash 0x{ov.hash:08x}, {ov.size} bytes)")
        lo, hi = r["code_span"]
        detail.append(f"  code: {r['n_code']} instructions in {r['n_funcs']} functions "
                      f"(seeds: {', '.join(f'{k} {v}' for k, v in sorted(r['seed_kinds'].items()))}), "
                      f"span 0x{lo:08x}-0x{hi:08x}, {r['gap_words']} non-zero non-code words inside the span, "
                      f"{r['jtbls']} jump tables, data 0x{hi:08x}-0x{ov.end:08x}")
        if r["unresolved_jr"]:
            detail.append(f"  jr through a register with no table found: {len(r['unresolved_jr'])}: "
                          + ", ".join(f"0x{x:08x}" for x in r["unresolved_jr"][:12]))
        for nte in r["notes"]:
            detail.append(f"  note: {nte}")
        detail.append("  data words: " + ", ".join(
            f"{t}:{k} {v}" for (t, k), v in sorted(r["wcount"].items(), key=lambda kv: (kv[0][0], -kv[1]))))
        if r["mid"]:
            detail.append(f"  mid-function targets ({len(r['mid'])}):")
            detail += [f"    {m}" for m in r["mid"]]
        amb = list(r["ambiguous"])
        amb += [f"0x{x:08x} word {main.name(v)} [{rr}]" for x, (v, m, k, rr) in sorted(r["words"].items())
                if TIER_OF.get(rr) == "3"]
        if amb:
            detail.append(f"  ambiguous ({len(amb)}):")
            detail += [f"    {x}" for x in amb]
    if unknown:
        detail.append(f"\nnote: files not in the known overlay list (still processed): {', '.join(unknown)}")
    text = "\n".join(report + detail) + "\n"
    (out / "ovl_report.txt").write_text(text)
    if a.debug:
        with (out / "ovl_debug.tsv").open("w") as fh:
            fh.write("overlay\taddr\tvalue\tmirror\tkind\treason\n")
            for ov, r in results:
                for x, (v, m, k, rr) in sorted(r["words"].items()):
                    fh.write(f"{ov.name}\t{x:08x}\t{v:08x}\t{m:x}\t{k}\t{rr}\n")
    if not files:
        print(f"ovl-relocs: no overlays in {a.overlays}: empty fixup table")
    else:
        print(f"ovl-relocs: {len(files)} overlays, {tot['fix']} fixups (jal {tot['jal']}, j {tot['j']}, "
              f"hi/lo pairs {tot['hilo']}, words {tot['word']}), {tot['mid']} mid-function targets, "
              f"{tot['amb']} ambiguous; {len(labels)} function labels; report: "
              f"{(out / 'ovl_report.txt').relative_to(K.ROOT.resolve()) if K.ROOT.resolve() in out.parents else out}")
        print(text if a.report else "\n".join(report))
    return 0


if __name__ == "__main__":
    sys.exit(main_())
