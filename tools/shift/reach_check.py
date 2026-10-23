#!/usr/bin/env python3
"""Find code that reaches a floated variable through another object's address (phase 4).

  python3 -I tools/shift/reach_check.py [--ld out/shift/m12-float/kh1-shift.ld] [--out FILE]
                                        [--elf SLPS_251.98] [--overlays out/overlays] [--all]
                                        [--no-RULE ...]  (one rule off each, for bisecting: --help)

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
import random
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import mips  # noqa: E402
from elf32 import Elf  # noqa: E402

BLOB_START, BSS_START, IMAGE_END = 0x00272C70, 0x00494080, 0x00675018
TEXT_START = 0x00100000
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
# Session 27 (str-arg): callee -> {argument: kind} for an argument the callee only reads, as a string that
# ends at its first NUL (the libc ones read aligned quadwords, so at most 15 bytes more of the same qword).
# fmt: a printf format (func_00259698 skips the byte after a lone '%', so every '%' must start a whole
# conversion); str: any bytes; kh: func_001ea268's text, whose control bytes 5-7 and 9-31 take parameter
# bytes (so none may occur before the NUL).
STRING_ARGS = {
    0x00259CC0: {0: "fmt"},  # scePrintf(fmt, ...)
    0x00259C88: {0: "fmt"},  # func_00259c88(fmt, ...): the same printer, without the callback swap
    0x00250248: {0: "fmt"},  # printf(fmt, ...)
    0x00250EB0: {1: "fmt"},  # sprintf(dst, fmt, ...)
    0x00250340: {0: "str"},  # puts(s)
    0x00250F40: {1: "str"},  # strcat(dst, src)
    0x002511B0: {1: "str"},  # strcpy(dst, src)
    0x0025106C: {0: "str", 1: "str"},  # strcmp(a, b)
    0x00251400: {0: "str", 1: "str"},  # strncmp(a, b, n)
    0x002512C4: {0: "str"},  # strlen(s)
    0x001EA268: {1: "kh"},  # func_001ea268(dst, src): the game's strcat for encoded text
}
_FMT = re.compile(rb"%[-+ #0]*[0-9]*(\.[0-9]+)?[hlLqjzt]*[diouxXcspfeEgGn%]")


def string_end(data: bytes, ub: int, kind: str) -> int | None:
    """Offset just past the NUL that ends a string read from any offset in [0, ub] of a data object whose
    bytes (to the next name) are data: None unless the object is a non-empty string literal, i.e. the
    NUL is followed only by zero padding of at most 15 bytes (a buffer filled at run time has a long
    zero tail, or no text)."""
    z = data.find(b"\0", ub)
    if z <= 0 or not data[0] or len(data) - z > 16 or any(data[z:]):
        return None
    txt = data[:z]
    if kind == "fmt":
        if ub or any(c < 0x20 and c not in (9, 10, 13) or c == 0x7F for c in txt):
            return None
        if _FMT.sub(b"", txt).count(b"%"):
            return None  # a '%' that does not start a whole conversion
    elif kind == "kh" and any(5 <= c <= 7 or 9 <= c <= 31 for c in txt):
        return None
    return z + 1


# Session 27 (dma-count): func_00237018(buf, n, wait) writes a DMA "end" tag with qwc n - 1 at buf and sends
# buf on GIF channel 2 in chain mode (func_00266f38: CHCR 0x105), so the DMA reads exactly 16 * n bytes.
DMA_COUNT_CALLS = {
    0x00237018: [(4, lambda st: 16 * st[5] if isinstance(st.get(5), int) and 0 < st[5] < 0x10000 else None)],
    # func_00106cd0(addr, qwc) appends a ref tag (word 0 = 0x30000000 + qwc, word 1 = addr) to the chain in
    # D_00494A90: the DMA reads 16 * qwc bytes at addr
    0x00106CD0: [(4, lambda st: 16 * st[5] if isinstance(st.get(5), int) and 0 < st[5] < 0x10000 else None)],
}
# Session 27 (list-arg): callee -> (list argument, element width, terminator, {argument: bytes per element}):
# the callee reads the list until the terminator ("m1": a word -1, "neg": a negative halfword) and
# advances each dependent argument by its stride per element before it. A list literal in .data (ending
# with the terminator and at most 12 bytes of zero padding) gives the count.
LIST_CALLS = {
    0x0024AFC0: (0, 4, "m1", {1: 4}),  # func_0024afc0(list, out[] words, hdr)
    0x0024AF40: (0, 4, "m1", {1: 0xC0}),  # func_0024af40(list, out[] 0xC0-byte records, hdr)
    0x0024C8B8: (1, 2, "neg", {}),  # func_0024c8b8(o, list of halfwords, ...)
}


def list_count(data: bytes, width: int, term: str) -> int | None:
    """Elements before the terminator of a list literal that fills data (the object to the next name)."""
    for k in range(0, len(data) - width + 1, width):
        v = int.from_bytes(data[k:k + width], "little", signed=True)
        if (term == "m1" and v == -1) or (term == "neg" and v < 0):
            rest = data[k + width:]
            return k // width if len(rest) <= 12 and not any(rest) else None
    return None


# Session 27 (dma-chain): callee -> argument that is the start of a DMA source chain the callee (or the
# callback it registers) sends in chain mode (func_00266f38 writes it to TADR with CHCR 0x105):
# func_00106b18(chain) and func_00106bd8(chain, ...) send it on channel D_002A6B84 (through func_00106b98's
# callback for the latter), func_00266f38(channel, chain) directly.
CHAIN_CALLS = {0x00106B18: 0, 0x00106BD8: 0, 0x00266F38: 1}


def parse_chain(read, base: int, end: int):
    """Follow a DMA source chain in the image from base: (end of the tags and inline data, [(ref address,
    bytes)]) when every tag is refe/cnt/ref/end and every tag and its inline data lie in [base, end);
    None for next/call/ret/refs tags, a chain past end, or more than 256 tags."""
    p, refs = base, []
    for _n in range(256):
        if p + 16 > end:
            return None
        w0, w1 = read(p), read(p + 4)
        if w0 is None or w1 is None:
            return None
        qwc, tid = w0 & 0xFFFF, (w0 >> 28) & 7
        if tid in (0, 3):  # refe / ref: qwc quadwords at ADDR
            if w1 >> 31 or not qwc:
                return None  # scratchpad, or an empty transfer
            refs.append((w1 & 0x7FFFFFFF, 16 * qwc))
            p += 16
            if tid == 0:
                return p, refs
        elif tid in (1, 7):  # cnt / end: qwc quadwords after the tag
            p += 16 + 16 * qwc
            if p > end:
                return None
            if tid == 7:
                return p, refs
        else:
            return None
    return None


ARG = "arg"  # ("arg", k, off): argument k on entry + off
IDX = "idx"  # register = known base + offset: ("idx", base, upper bound of the offset or None)
UB = "ub"  # a small value with an upper bound: ("ub", U)
LT = "lt"  # a comparison result: ("lt", r, N) = register r < N
HI = "hi"  # register = a lui alone: ("hi", value); its %lo users are relocated fields
SET = "set"  # register = one of a few exact addresses: ("set", frozenset) from a join (session 21)
HIX = "hix"  # register = a lui + an index: ("hix", value, upper bound or None); %lo users index from value+lo
JT = "jt"  # register = a word of a jump table: ("jt", table address, largest byte offset)
PTR = "ptr"  # register = the word loaded from a pointer global G, + an offset: ("ptr", G, off or None if indexed)
SET_MAX = 8  # a join of more addresses becomes base + bounded offset (IDX)
AX = "ax"  # session 30 (arg-bound): register = argument k on entry * m + a, a scaled index: ("ax", k, m, a);
# an IDX/HIX made from one carries it as a 4th element ("ax", k, m, a) with a an upper bound


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
    if isinstance(v, tuple) and v[0] == SET:  # used as a base for an index: lowest + span
        lo, hi = min(v[1]), max(v[1])
        return (lo, hi - lo) if hi - lo < 0x10000 else None
    return None


def _ax(v):
    """Session 30 (arg-bound): v as a scaled argument ("ax", k, m, a) (an argument + off is ("ax", k, 1, off))."""
    if isinstance(v, tuple) and v[0] == ARG and len(v) == 3:  # (not one that a join made: see analyse's join)
        return (AX, v[1], 1, v[2])
    if isinstance(v, tuple) and v[0] == AX:
        return v
    return None


SHADOW_MAX = 3  # arg-keep/join-keep: distinct values a register gets from shadow visits at a point before widening


def _addressy(v):
    """Session 31 (arg-keep, join-keep): a value whose uses make events (an address, a %hi, an indexed base, a pointer
    global's word, a jump table word), so dropping it at a join drops accesses."""
    if isinstance(v, int):
        return v > 0x10000
    return isinstance(v, tuple) and v[0] in (SET, IDX, HIX, PTR, HI, JT)


def _widen(v, got=()):
    """Session 31 (arg-keep, join-keep): an address value with its offset made unknown: from the lowest base of v and
    the values got (of the same kind, within 64 KiB of v's) + any index."""
    if isinstance(v, tuple) and v[0] in (PTR, HI, JT):
        return (PTR, v[1], None) if v[0] == PTR else v
    kind = HIX if isinstance(v, tuple) and v[0] == HIX else IDX

    def base(x_):
        if kind == HIX:
            return x_[1] if isinstance(x_, tuple) and x_[0] == HIX else None
        if isinstance(x_, tuple) and x_[0] == SET:
            return min(x_[1])
        a_ = _idx(x_)
        return None if a_ is None else a_[0]
    b0 = base(v)
    return (kind, min([b0] + [b_ for x_ in got if (b_ := base(x_)) is not None and abs(b_ - b0) < 0x10000]), None)


def _covers(j, x):
    """Session 31 (arg-keep, join-keep): a join result j makes at least the events address value x makes."""
    if j == x:
        return True
    if not isinstance(j, tuple) or isinstance(x, tuple) and x[0] in (HI, JT):
        return False
    if j[0] == SET:
        return _addrs(x) is not None and _addrs(x) <= j[1]
    if j[0] == IDX:
        a = _idx(x)
        return a is not None and j[1] <= a[0] and (j[2] is None or a[1] is not None and a[0] + a[1] <= j[1] + j[2])
    if j[0] == HIX:
        return isinstance(x, tuple) and x[0] == HIX and x[1] == j[1] and (
            j[2] is None or x[2] is not None and x[2] <= j[2])
    if j[0] == PTR:
        return isinstance(x, tuple) and x[0] == PTR and x[1] == j[1] and (j[2] is None or x[2] == j[2])
    return False


def _addrs(v):
    """The exact addresses a value can be: an address or a SET; else None."""
    if isinstance(v, int) and v > 0x10000:
        return {v}
    if isinstance(v, tuple) and v[0] == SET:
        return set(v[1])
    return None


def _gaddr(b, w: int):
    """The image address a load/store `op rt, imm(base)` names when base holds an address or a %hi."""
    if isinstance(b, int) and b > 0x10000:
        g = (b + mips.imm(w)) & 0xFFFFFFFF
    elif isinstance(b, tuple) and b[0] == HI:
        g = (b[1] + mips.imm(w)) & 0xFFFFFFFF
    else:
        return None
    return g if BLOB_START <= g < IMAGE_END else None


def gpr_writes(w: int) -> set[int]:
    """General registers an instruction may write (for the countdown-loop pattern)."""
    o = mips.op(w)
    if o == mips.OP_SPECIAL and mips.funct(w) == 0x09:  # jalr
        return set(CALLER_SAVED) | {mips.rd(w)}
    if o in (mips.OP_SPECIAL, mips.OP_MMI):
        return {mips.rd(w)}
    if o == 0x03:  # jal
        return set(CALLER_SAVED)
    if o == mips.OP_REGIMM:
        return {31} if mips.rt(w) in (0x10, 0x11, 0x12, 0x13) else set()
    if 0x08 <= o <= 0x0F or o in (0x18, 0x19, 0x1A, 0x1B, 0x1E) or (o in mips.OP_LOADS and o not in (0x31, 0x35)):
        return {mips.rt(w)}
    if o in (0x10, 0x11, 0x12) and mips.rs(w) < 4:  # mfc / dmfc / cfc / qmfc2
        return {mips.rt(w)}
    return set()


def countdown_loops(insns: list[mips.Insn], counters: bool = False) -> dict[int, tuple]:
    """Single-back-edge loops whose trip count a decrementing counter caps (session 21):

        li v1,N; loop: ...; addiu v1,v1,-k; sq $0,0(v0); bgtz v1,loop; addiu v0,v0,16

    (func_00232ad0's clears). The back edge B is `bgtz c` / `bne c,$0` / `bgez c` (or the likely
    forms), the body [header, B's delay slot] has no inner back edge and no switch, c is written
    once there, by `addiu c,c,-k` that every path through the body executes, and each walked
    pointer p is written once, by `addiu p,p,s` (s > 0). Exits are free. Also an up-counter
    `addiu i,i,k; slti t,i,L; bne t,$0` from an exact start i0: it is taken as a countdown of
    L - i0. Returns {header index: (back-branch index, c, k, kind, {p: s}, L or None)}; kind says how
    many times the back edge can be taken for a counter that enters at most N (see back_edges).
    With counters=True (session 27) an up-counter loop is listed even when it walks no pointer: its
    counter itself is capped at the header (analyse's counter-cap)."""
    n = len(insns)
    a0 = insns[0].addr if n else 0
    out = {}
    jumps = []  # (from index, target index) of every branch and jump
    switch = False  # analyse() sends a switch's `jr` to every label
    for j, x in enumerate(insns):
        t_ = x.branch_target if x.is_branch else (x.jump_target if x.is_j else None)
        if t_ is not None:
            jumps.append((j, (t_ - a0) // 4))
        if x.is_jr and not x.is_jr_ra:
            switch = True
    for b, ins in enumerate(insns):
        w = ins.word
        o = mips.op(w)
        c = None
        if o in (0x07, 0x17) and mips.rt(w) == 0:
            c, kind = mips.rs(w), "gtz"
        elif o in (0x05, 0x15) and (mips.rs(w) == 0) != (mips.rt(w) == 0):
            c, kind = mips.rs(w) or mips.rt(w), "nez"
        elif o == mips.OP_REGIMM and mips.rt(w) in (0x01, 0x03):
            c, kind = mips.rs(w), "gez"
        if not c or b + 1 >= n:
            continue
        h = (ins.branch_target - a0) // 4
        if not (0 <= h <= b):
            continue
        # the header must be the only way in: no branch from outside into the body
        ok = not any(h < t_ <= b + 1 and (switch or not h <= j <= b + 1) for j, t_ in jumps)
        skipped = set()  # body indices some path from the header to B does not execute
        writes: dict[int, list[int]] = {}
        for j in range(h, b + 2):
            x = insns[j]
            for r in gpr_writes(x.word):
                writes.setdefault(r, []).append(j)
            if j >= b:
                continue
            tgt = x.branch_target if x.is_branch else (x.jump_target if x.is_j else None)
            if x.is_jr and not x.is_jr_ra:
                ok = False  # a switch
            if tgt is None:
                continue
            ti = (tgt - a0) // 4
            if h <= ti <= j:
                ok = False  # an inner loop or a second back edge
            elif j < ti <= b + 1:
                likely = mips.op(x.word) in (0x14, 0x15, 0x16, 0x17) or (
                    mips.op(x.word) == mips.OP_REGIMM and mips.rt(x.word) in (0x02, 0x03, 0x12, 0x13))
                skipped.update(range(j + (1 if likely else 2), ti))
        if not ok:
            continue
        wc = writes.get(c, [])
        if kind == "nez" and wc and wc[-1] < b:  # the test register: only its last write before B counts
            wc = [wc[-1]]                       # (a call earlier in the body clobbers v0)
            if mips.op(insns[wc[0]].word) not in (0x0A, 0x0B):
                wc = writes.get(c, [])
        if len(wc) != 1 or wc[0] in skipped:
            continue
        x = insns[wc[0]].word
        lim, tst = None, None
        if kind == "nez" and mips.op(x) in (0x0A, 0x0B) and mips.rt(x) == c and mips.rs(x) not in (0, c) \
                and wc[0] < b and (mips.op(x) == 0x0A or mips.imm(x) >= 0):
            # an up-counter: t = slti i, L; ... bne t, $0 (i = i + k once per iteration, from an exact start)
            tst, c, lim = c, mips.rs(x), mips.imm(x)
            wi = writes.get(c, [])
            if len(wi) != 1 or wi[0] in skipped:
                continue
            y = insns[wi[0]].word
            if not (mips.op(y) in (0x09, 0x19) and mips.rs(y) == c and mips.rt(y) == c and mips.imm(y) > 0):
                continue
            k = mips.imm(y)
            kind = "gtz" if wi[0] < wc[0] else "gtz-slot"  # the test sees i after (or before) the step
        else:
            if not (mips.op(x) in (0x09, 0x19) and mips.rs(x) == c and mips.rt(x) == c and mips.imm(x) < 0):
                continue
            k = -mips.imm(x)
            if kind == "nez" and k != 1:
                continue
            kind += "-slot" if wc[0] == b + 1 else ""
        ps = {}
        for r, js in writes.items():
            if r in (0, c, tst) or len(js) != 1:
                continue
            y = insns[js[0]].word
            if mips.op(y) in (0x09, 0x19) and mips.rs(y) == r and mips.rt(y) == r and 0 < mips.imm(y):
                ps[r] = mips.imm(y)
        if ps or (counters and lim is not None):
            out.setdefault(h, (b, c, k, kind, ps, lim))
    return out


def nested_carries(insns: list[mips.Insn], loops: dict[int, tuple]) -> tuple[dict, dict]:
    """Session 29 (nest-carry): a counter an inner loop steps and the outer loop carries over, as in
    func_00103a70's 4x4 copy:

        t5 = 0; t7 = 0; outer: t4 = 3; inner: ...; t5 += 1; ...; t4--; bgez t4, inner; ...
        t7 += 1; slti v0, t7, 4; bnez v0, outer

    t5 is never reset, so neither loop alone bounds it, but the inner body runs at most
    (outer trips) * (inner trips) times in all. The inner loop is one of countdown_loops'; the outer
    loop is the same pattern (a down-counter or an up-counter from an exact start, written once per
    iteration outside the inner loops, header the only way in) except that it may contain inner
    loops whose back edges are its only backward branches. A carried counter c is written exactly
    once in the outer body, by `addiu c, c, k` (k > 0) inside the inner body (a path that skips the
    step only lowers c). A register stepped once per outer iteration outside the inner loops
    (`t6 += 4`) is capped at the outer header like countdown_loops' walked pointers. Returns
    ({outer header: (back-branch index, counter, k, kind, {r: step}, lim)}, {inner header: {c: (outer
    header, k)}})."""
    n = len(insns)
    a0 = insns[0].addr if n else 0
    jumps = []
    for j, x in enumerate(insns):
        t_ = x.branch_target if x.is_branch else (x.jump_target if x.is_j else None)
        if t_ is not None:
            jumps.append((j, (t_ - a0) // 4))
        if x.is_jr and not x.is_jr_ra:
            return {}, {}  # a switch: analyse() sends its `jr` to every label
    outer: dict[int, tuple] = {}
    carry: dict[int, dict] = {}
    for b, ins in enumerate(insns):
        w = ins.word
        o = mips.op(w)
        c = None
        if o in (0x07, 0x17) and mips.rt(w) == 0:
            c, kind = mips.rs(w), "gtz"
        elif o in (0x05, 0x15) and (mips.rs(w) == 0) != (mips.rt(w) == 0):
            c, kind = mips.rs(w) or mips.rt(w), "nez"
        elif o == mips.OP_REGIMM and mips.rt(w) in (0x01, 0x03):
            c, kind = mips.rs(w), "gez"
        if not c or b + 1 >= n:
            continue
        h = (ins.branch_target - a0) // 4
        inner = [(hi, lp[0]) for hi, lp in loops.items() if h < hi and lp[0] < b]
        if not (0 <= h <= b) or not inner or h in loops:
            continue
        if any(h < t_ <= b + 1 and not h <= j <= b + 1 for j, t_ in jumps):
            continue  # a way into the body other than the header
        in_inner = lambda j: any(hi <= j <= bi + 1 for hi, bi in inner)
        ok = True
        skipped = set()
        writes: dict[int, list[int]] = {}
        for j in range(h, b + 2):
            x = insns[j]
            for r in gpr_writes(x.word):
                writes.setdefault(r, []).append(j)
            if j >= b:
                continue
            tgt = x.branch_target if x.is_branch else (x.jump_target if x.is_j else None)
            if tgt is None:
                continue
            ti = (tgt - a0) // 4
            if ti <= j:
                if (ti, j) not in inner:
                    ok = False  # a backward branch that is not an inner loop's back edge
            elif ti <= b + 1:
                likely = mips.op(x.word) in (0x14, 0x15, 0x16, 0x17) or (
                    mips.op(x.word) == mips.OP_REGIMM and mips.rt(x.word) in (0x02, 0x03, 0x12, 0x13))
                skipped.update(range(j + (1 if likely else 2), ti))
        if not ok:
            continue
        wc = writes.get(c, [])
        if kind == "nez" and wc and wc[-1] < b:
            wc = [wc[-1]]
            if mips.op(insns[wc[0]].word) not in (0x0A, 0x0B):
                wc = writes.get(c, [])
        if len(wc) != 1 or wc[0] in skipped or in_inner(wc[0]):
            continue
        x = insns[wc[0]].word
        lim, tst = None, None
        if kind == "nez" and mips.op(x) in (0x0A, 0x0B) and mips.rt(x) == c and mips.rs(x) not in (0, c) \
                and wc[0] < b and (mips.op(x) == 0x0A or mips.imm(x) >= 0):
            tst, c, lim = c, mips.rs(x), mips.imm(x)
            wi = writes.get(c, [])
            if len(wi) != 1 or wi[0] in skipped or in_inner(wi[0]):
                continue
            y = insns[wi[0]].word
            if not (mips.op(y) in (0x09, 0x19) and mips.rs(y) == c and mips.rt(y) == c and mips.imm(y) > 0):
                continue
            k = mips.imm(y)
            kind = "gtz" if wi[0] < wc[0] else "gtz-slot"
        else:
            if not (mips.op(x) in (0x09, 0x19) and mips.rs(x) == c and mips.rt(x) == c and mips.imm(x) < 0):
                continue
            k = -mips.imm(x)
            if kind == "nez" and k != 1:
                continue
            kind += "-slot" if wc[0] == b + 1 else ""
        ps = {}  # registers the outer body steps once, outside the inner loops (t6 += 4 in func_00103a70)
        for r, js in writes.items():
            if r in (0, c, tst) or len(js) != 1 or in_inner(js[0]):
                continue
            y = insns[js[0]].word
            if mips.op(y) in (0x09, 0x19) and mips.rs(y) == r and mips.rt(y) == r and mips.imm(y) > 0:
                ps[r] = mips.imm(y)
        outer.setdefault(h, (b, c, k, kind, ps, lim))
        for hi, bi in inner:
            ic = loops[hi][1]
            for r, js in writes.items():
                if r in (0, c, tst, ic) or len(js) != 1 or not hi <= js[0] <= bi + 1:
                    continue
                y = insns[js[0]].word
                if mips.op(y) in (0x09, 0x19) and mips.rs(y) == r and mips.rt(y) == r and mips.imm(y) > 0:
                    carry.setdefault(hi, {}).setdefault(r, (h, mips.imm(y)))
    return outer, carry


def _likely(w: int) -> bool:
    """A branch-likely: its delay slot runs only when the branch is taken (bc1fl/bc1tl too)."""
    o = mips.op(w)
    return o in (0x14, 0x15, 0x16, 0x17) or (o == mips.OP_REGIMM and mips.rt(w) in (0x02, 0x03, 0x12, 0x13)) \
        or (o in (mips.OP_COP1, mips.OP_COP2) and mips.rs(w) == 0x08 and mips.rt(w) & 2 != 0)


def path_loops(insns: list[mips.Insn], counters: bool = True) -> dict[int, tuple]:
    """Session 30 (path-step): countdown_loops' loops, proved over the paths of the body instead of by
    single writes. countdown_loops wants the counter written once, by a step every path executes; gcc
    also puts the step in a likely branch's delay slot on the path that loops and returns on the other
    (func_0011e248: `bnel v0,s1,next; addiu v1,v1,1` ... `jr ra`), or in both arms of an if
    (func_001269d8: `blezl a0,test; addiu t0,t0,1` and `addiu t0,t0,1` on the fall-through), and it
    walks a pointer through a copy (func_00111510: `move a1,a0; ...; addiu a0,a1,4`).

    The body [header, back branch's delay slot] must have no backward branch but the back edge, no
    switch `jr`, no linking branch, and no way in but the header (as countdown_loops). Every path from
    the header that reaches the back edge is followed (the body is acyclic; paths that branch or jump
    out, or return, leave the loop and do not matter), tracking each register as {its header value or
    another register's + a constant} (or unknown), and a `slti/sltiu t, i, L` result as (that
    instruction, i's value there). On the edge that loops:
      - a down-counter c (`bgtz/bgez/bne c,$0`; bne only with k = 1) is c - k on every path, and the
        branch tests c - k on every path (kind) or c on every path (kind-slot: the step is in the slot);
      - an up-counter i (`bne t,$0` with t = slti i, L on every path, from one instruction) is i + k on
        every path, and that slti saw i + k (gtz) or i (gtz-slot) on every path;
      - a walked register p is p + d on every path with 0 <= d, max d = s > 0 (a path that steps less
        only lowers it).
    Returns {header index: (back-branch index, c, k, kind, {p: s}, L or None)} like countdown_loops."""
    n = len(insns)
    a0 = insns[0].addr if n else 0
    jumps = []
    for j, x in enumerate(insns):
        t_ = x.branch_target if x.is_branch else (x.jump_target if x.is_j else None)
        if t_ is not None:
            jumps.append((j, (t_ - a0) // 4))
        if x.is_jr and not x.is_jr_ra:
            return {}  # a switch: analyse() sends its `jr` to every label
    out = {}
    TOP = None

    def get(stt, r):
        return frozenset({("r", r, 0)}) if r not in stt else stt[r]

    def put(stt, r, v):
        if r:
            stt[r] = v

    def ex(stt, j):
        """Execute insns[j] on a path state (a copy is returned)."""
        stt = dict(stt)
        w = insns[j].word
        o, s, t = mips.op(w), mips.rs(w), mips.rt(w)
        if o in (0x09, 0x19):  # addiu / daddiu
            v = get(stt, s)
            put(stt, t, TOP if v is TOP or any(e[0] != "r" for e in v)
                else frozenset(("r", e[1], e[2] + mips.imm(w)) for e in v))
        elif o in (0x0A, 0x0B):  # slti / sltiu
            v = get(stt, s)
            put(stt, t, TOP if v is TOP or s == 0 or any(e[0] != "r" for e in v)
                else frozenset(("lt", j, e[1], e[2]) for e in v))
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x21, 0x2D, 0x25) and (s == 0 or t == 0):  # move
            put(stt, mips.rd(w), get(stt, t if s == 0 else s))
        elif o == mips.OP_SPECIAL and mips.funct(w) == 0x0C:  # syscall: v0/v1 and the like
            for r in CALLER_SAVED:
                put(stt, r, TOP)
        else:
            for r in gpr_writes(w):
                put(stt, r, TOP)
        return stt

    def join(x, y):
        if x is None:
            return y
        z = {}
        for r in set(x) | set(y):
            u, v = get(x, r), get(y, r)
            z[r] = TOP if u is TOP or v is TOP or len(u | v) > 4 else u | v
        return z

    for b, ins in enumerate(insns):
        w = ins.word
        o = mips.op(w)
        if not ins.is_branch or b + 1 >= n:
            continue
        h = (ins.branch_target - a0) // 4
        if not (0 <= h < b):
            continue
        c = None
        if o in (0x07, 0x17) and mips.rt(w) == 0:
            c, kind = mips.rs(w), "gtz"
        elif o in (0x05, 0x15) and (mips.rs(w) == 0) != (mips.rt(w) == 0):
            c, kind = mips.rs(w) or mips.rt(w), "nez"
        elif o == mips.OP_REGIMM and mips.rt(w) in (0x01, 0x03):
            c, kind = mips.rs(w), "gez"
        if not c:
            continue
        if any(h < t_ <= b + 1 and not h <= j <= b + 1 for j, t_ in jumps):
            continue  # a way into the body other than the header
        ok = True
        ins_st: dict[int, dict] = {h: {}}  # instruction index -> joined state of the paths reaching it
        for j in range(h, b):
            x = insns[j]
            stt = ins_st.get(j)
            if stt is None:
                continue  # no path from the header reaches j (or only as a delay slot, done below)
            xw = x.word
            ctl = x.is_branch or x.is_j or x.is_jr or x.is_jal or x.is_jalr
            if not ctl:
                ins_st[j + 1] = join(ins_st.get(j + 1), ex(stt, j))
                continue
            if j + 1 >= b or (x.is_jr and not x.is_jr_ra) \
                    or (mips.op(xw) == mips.OP_REGIMM and mips.rt(xw) in (0x10, 0x11, 0x12, 0x13)):
                ok = False  # a slot that is the back branch, a switch, or a linking branch
                break
            if x.is_jal or x.is_jalr:  # a call: its slot, then the callee clobbers (gpr_writes), then j + 2
                ins_st[j + 2] = join(ins_st.get(j + 2), ex(ex(stt, j + 1), j))
                continue
            s0 = ex(stt, j)
            slot = ex(s0, j + 1)
            if x.is_jr_ra:
                continue  # returns: the path leaves the loop
            tgt = x.branch_target if x.is_branch else x.jump_target
            ti = (tgt - a0) // 4
            if a0 <= tgt and ti <= j:
                ok = False  # a second back edge or an inner loop
                break
            if h < ti <= b + 1:  # (a target outside the body leaves the loop)
                ins_st[ti] = join(ins_st.get(ti), slot)
            if x.is_j:
                continue
            always = (mips.op(xw) == 0x04 and mips.rs(xw) == mips.rt(xw)) or (
                mips.op(xw) == mips.OP_REGIMM and mips.rt(xw) in (0x01, 0x11) and mips.rs(xw) == 0)
            if not always:
                ins_st[j + 2] = join(ins_st.get(j + 2), s0 if _likely(xw) else slot)
        if not ok:
            continue
        at_b = ins_st.get(b)
        if at_b is None:
            continue
        taken = ex(at_b, b + 1)  # the delay slot runs on the edge that loops (likely or not)
        tv = get(at_b, c)
        lim, tst = None, None
        if tv is TOP or len(tv) != 1:
            continue
        (tk,) = tv
        if kind == "nez" and tk[0] == "lt":
            _lt, jl, i_, d_ = tk
            y = insns[jl].word
            if not (mips.op(y) == 0x0A or mips.imm(y) >= 0) or i_ == c:
                continue
            iv = get(taken, i_)
            if iv is TOP or len(iv) != 1:
                continue
            (_r, src, k), = iv
            if _r != "r" or src != i_ or k <= 0 or d_ not in (0, k):
                continue
            tst, c, lim = c, i_, mips.imm(y)
            kind = "gtz" if d_ == k else "gtz-slot"
        else:
            cv = get(taken, c)
            if cv is TOP or len(cv) != 1:
                continue
            (_r0, s0_, dB), (_r1, s1_, dS) = tk, next(iter(cv))
            if _r0 != "r" or _r1 != "r" or s0_ != c or s1_ != c or dS >= 0:
                continue
            k = -dS
            if kind == "nez" and k != 1:
                continue
            if dB == dS:
                pass
            elif dB == 0:
                kind += "-slot"
            else:
                continue
        ps = {}
        for r in range(1, 32):
            if r in (c, tst):
                continue
            v = get(taken, r)
            if v is TOP or any(e[0] != "r" or e[1] != r or e[2] < 0 for e in v):
                continue
            s_ = max(e[2] for e in v)
            if s_ > 0:
                ps[r] = s_
        if ps or (counters and lim is not None):
            out.setdefault(h, (b, c, k, kind, ps, lim))
    return out


def arg_bounds(funcs, calls_to: dict, direct_only, caller_of) -> dict[int, tuple]:
    """Session 30 (arg-bound): for each function f in funcs, the largest value each argument register can hold
    on entry (None: unknown), over its call sites calls_to[f] = {call pc: (value per argument register)}: an exact
    int (a negative one is unknown), ("arg", k, off) = the caller's own argument k + off (caller_of(pc) is the
    caller; it must be in funcs), or None. Only a function with direct_only(f) (every way in is one of these calls)
    is bounded. A least fixpoint from "no call yet"; a recursion whose bound keeps growing gives up."""
    n = len(ARG_REGS)
    BOT, TOP = "bot", "top"
    ubs = {f_: [BOT] * n if direct_only(f_) else [TOP] * n for f_ in funcs}

    def site(v_, pc_):
        if isinstance(v_, int):
            return v_ if v_ >= 0 else TOP
        if isinstance(v_, tuple):
            u_ = ubs.get(caller_of(pc_), [TOP] * n)[v_[1]]
            return u_ if u_ in (BOT, TOP) else (u_ + v_[2] if u_ + v_[2] >= 0 else TOP)
        return TOP

    for _round in range(64):
        changed = False
        for f_ in sorted(funcs):
            if not direct_only(f_):
                continue
            for k_ in range(n):
                vals = [site(vs[k_], pc_) for pc_, vs in calls_to[f_].items()]
                new = TOP if TOP in vals else max((x_ for x_ in vals if x_ != BOT), default=BOT)
                old = ubs[f_][k_]
                if old == TOP or new == old or new == BOT or (old != BOT and new != TOP and new < old):
                    continue
                ubs[f_][k_] = new if old == BOT or new == TOP else max(old, new)
                changed = True
        if not changed:
            break
    else:
        return {f_: (None,) * n for f_ in funcs}  # no fixpoint
    return {f_: tuple(None if u_ in (BOT, TOP) else u_ for u_ in v_) for f_, v_ in ubs.items()}


def back_edges(kind: str, n: int, k: int) -> int:
    """How many times a countdown loop's back edge can be taken when its counter enters at most n.
    The test sees the decremented counter (kind without -slot) or the counter before the
    decrement in B's delay slot (-slot)."""
    if kind == "gtz":
        return max(0, (n - 1) // k)  # back while n - j*k > 0, j = 1, 2, ...
    if kind == "gtz-slot":
        return max(0, (n + k - 1) // k)  # back while n - (j-1)*k > 0
    if kind == "gez":
        return max(0, n // k)
    if kind == "gez-slot":
        return max(0, n // k + 1)
    if kind == "nez":
        return max(0, n - 1)
    return max(0, n)  # nez-slot


def analyse(insns: list[mips.Insn], starts: set[int] | None = None, args: bool = False,
            countdown: bool = True, joins: bool = True, arg_join: bool = True, hi_index: bool = True,
            read_word=None, cases: bool = True, ptr_globals: bool = True, counter_cap: bool = True,
            slot_refine: bool = True, end_ptr: bool = True, nest_carry: bool = True,
            path_step: bool = True, wr_span: bool = True, arg_bound: bool = True, arg_keep: bool = True,
            join_keep: bool = True, stored_idx: bool = True, visit_rng=None):
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
    to unbounded.

    Session 21: a pointer walk whose loop a decrementing counter caps (countdown_loops) gets
    the counter's trip count as its bound (`countdown`), and a join of a few exact addresses
    (`o->p = cond ? A : B`) stays a SET of them (`joins`): accesses, stores and call arguments
    through it are made at each address, not from the lowest one with an unknown index. Code
    after a `jr` that nothing branches to (a switch's cases) is analysed from a fresh state.

    Session 31 (`arg_keep`): the arg-join keeps the argument when one path holds it and another an
    address, and dropped the address. Events come from every state a point is visited with, so the
    address's accesses were seen only when its path happened to be visited first. Now such a join also
    visits the point once more with the joined state but the address in that register (a shadow visit:
    its events are reported, its successors are merged as usual), whichever side arrived first.
    `join_keep` does the same for any other join that does not cover an address (an address joined with
    an unknown value, two bases that end up unrelated). A register that keeps getting new values from
    shadows at one point (a walk) is widened to base + unknown after SHADOW_MAX of them, so it ends.
    `stored_idx`: a store of base + index (&D[i]) stores the base (before, only an exact address did).
    visit_rng (tests, --visit-seed): a random.Random that picks the next point to visit instead of the
    last one pushed; the output should not depend on it (docs/shiftable-plan.md "Session 31" lists what
    still does)."""
    n = len(insns)
    if not n:
        return
    a0 = insns[0].addr
    index = lambda addr: (addr - a0) // 4
    entry = {0: 0}
    if args:
        entry.update({r: (ARG, k, 0) for k, r in enumerate(ARG_REGS)})
    states: dict[int, dict] = {0: entry}
    work: list = [0]  # points to visit; a tuple (i, state) is a shadow visit (session 31, arg-keep/join-keep)
    seen_out = set()
    shadow_seen: set = set()  # (i, frozen state) of every shadow visit pushed
    shadow_lost: dict[tuple, set] = {}  # (i, k) -> the values shadows gave k at i
    grow: dict[tuple, int] = {}
    wide: set[int] = set()  # arguments this function walks or indexes (reach not bounded by its offsets)
    loops = countdown_loops(insns, counters=counter_cap) if countdown else {}
    if countdown and path_step:  # session 30: the loops whose steps only the paths of the body prove
        for h_, lp_ in path_loops(insns, counters=counter_cap).items():
            old_ = loops.get(h_)
            if old_ is not None and old_[:4] == lp_[:4] and old_[5] == lp_[5]:  # the same loop: walks of both
                lp_ = lp_[:4] + ({r_: max(old_[4].get(r_, 0), lp_[4].get(r_, 0))
                                  for r_ in set(old_[4]) | set(lp_[4])},) + lp_[5:]
            if old_ is None or old_[:4] == lp_[:4] and old_[5] == lp_[5]:
                loops[h_] = lp_
    outer, carry = nested_carries(insns, loops) if countdown and nest_carry else ({}, {})
    loop_entry: dict[int, dict] = {}  # loop header -> joined state of the edges that enter the loop
    loop_heads = set()  # targets of a backward branch or jump
    for j_, x_ in enumerate(insns):
        t_ = x_.branch_target if x_.is_branch else (x_.jump_target if x_.is_j else None)
        if t_ is not None and a0 <= t_ <= x_.addr:
            loop_heads.add((t_ - a0) // 4)

    def join(i, k, v, u):
        if u == v:
            return v
        if arg_bound and isinstance(v, tuple) and isinstance(u, tuple) and v[0] == u[0] == ARG and v[1:3] == u[1:3]:
            return v[:3] + ("j",)  # (one side came through a join below)
        av = [t_ for t_ in (v, u) if isinstance(t_, tuple) and t_[0] == ARG]
        if arg_join and len(av) == 1:
            # an argument on one path and something else on the other (a reused register, p = p->next):
            # not a walk of the argument. Accesses through the join count as the argument's reach.
            # Session 30 (arg-bound): marked ("j"), so it is not taken for the argument's value as an index.
            return av[0][:3] + ("j",) if arg_bound else av[0]
        for t_ in av:
            wide.add(t_[1])  # two offsets of one argument (a walk), or two arguments
        if joins and i not in loop_heads:  # at a loop head a join is a walk (base + offset), not a choice
            sa, sb = _addrs(v), _addrs(u)
            if sa is not None and sb is not None and len(sa | sb) <= SET_MAX:
                return (SET, frozenset(sa | sb))
        a, b = _idx(v), _idx(u)
        if a is not None and b is not None and abs(a[0] - b[0]) < 0x10000:
            base = min(a[0], b[0])
            if a[1] is None or b[1] is None:
                return (IDX, base, None)
            hi = max(a[0] + a[1], b[0] + b[1]) - base
            # a pointer walking a table (p = D; ... p += 0x2c in a loop): base + bounded offset
            return (IDX, base, hi)
        if isinstance(v, tuple) and isinstance(u, tuple) and v[0] == u[0] == PTR and v[1] == u[1]:
            return (PTR, v[1], v[2] if v[2] == u[2] else None)  # a walk through the pointer G holds
        x, y = _ub(v), _ub(u)
        if x is not None and y is not None:
            return (UB, max(x, y))
        return None

    def loop_value(i, k):
        """A countdown loop's walked pointer k at its header i: entry + stride * back edges."""
        b, c, step_, kind, ps, lim = loops[i]
        e = loop_entry.get(i, {})
        a, nmax = _idx(e.get(k)), _ub(e.get(c))
        if lim is not None:  # an up-counter: from an exact start to the limit
            i0 = e.get(c)
            nmax = lim - i0 if isinstance(i0, int) and -0x10000 < i0 < 0x10000 else None
        if nmax is None:
            return None
        if nest_carry and a is None and (u := _ub(e.get(k))) is not None:
            # session 29: a stepped offset, not a pointer (func_00103a70's t3 = t6 * 4, +4 per inner run)
            return (UB, u + ps[k] * back_edges(kind, nmax, step_))
        if a is None or a[1] is None:
            return None
        return (IDX, a[0], a[1] + ps[k] * back_edges(kind, nmax, step_))

    def counter_value(i):
        """Session 27 (counter-cap): an up-counter `i = i0; do { ...; i += k; } while (i < L)` at its
        header i is at most max(i0, L - 1), or max(i0, L - 1 + k) when the test sees i before the step:
        the back edge is taken only when the test passed. Without it the counter's bound widened away
        (0, 1, 2, then unbounded) before the test could cap it, and so did every index made from it."""
        b, c, step_, kind, ps, lim = loops[i]
        i0 = loop_entry.get(i, {}).get(c)
        if lim is None or not (isinstance(i0, int) and -0x10000 < i0 < 0x10000):
            return None
        return (UB, max(i0, lim - 1 + (step_ if kind == "gtz-slot" else 0)))

    def trips(lp, e):
        """How many times a loop's body can run in one entry, from its entry state e (None: unknown)."""
        _b, c, step_, kind, _ps, lim = lp  # countdown_loops' or nested_carries' outer tuple
        if lim is not None:
            i0 = e.get(c)
            nmax = lim - i0 if isinstance(i0, int) and -0x10000 < i0 < 0x10000 else None
        else:
            nmax = _ub(e.get(c))
        return None if nmax is None else back_edges(kind, nmax, step_) + 1

    def carry_value(i, k):
        """Session 29 (nest-carry): carried counter k at inner header i: start + step * (all runs - 1)."""
        ho, step_ = carry[i][k]
        eo, ei = loop_entry.get(ho), loop_entry.get(i)
        if eo is None or ei is None:
            return None
        c0, to, ti = _ub(eo.get(k)), trips(outer[ho], eo), trips(loops[i], ei)
        if c0 is None or to is None or ti is None or to * ti > 0x10000:
            return None
        return (UB, c0 + step_ * (to * ti - 1))

    def outer_value(i, k):
        """Session 29 (nest-carry): a register the outer loop steps once per iteration, at its header."""
        e = loop_entry.get(i)
        to = trips(outer[i], e) if e is not None else None
        if to is None:
            return None
        a = _idx(e.get(k))
        if a is not None and a[1] is not None:
            return (IDX, a[0], a[1] + outer[i][4][k] * (to - 1))
        u = _ub(e.get(k))
        return None if u is None else (UB, u + outer[i][4][k] * (to - 1))

    def merge(i, st, src=None):
        if not (0 <= i < n):
            return
        lp = loops.get(i)
        op_ = outer.get(i)
        if op_ is not None and src != op_[0]:  # an edge into an outer loop (nest-carry)
            e = loop_entry.get(i)
            loop_entry[i] = dict(st) if e is None else {k: j for k, v in e.items()
                                                          if (j := join(i, k, v, st.get(k))) is not None}
        if lp is not None and src != lp[0]:  # an edge into the loop, not its back edge
            e = loop_entry.get(i)
            loop_entry[i] = dict(st) if e is None else {k: j for k, v in e.items()
                                                          if (j := join(i, k, v, st.get(k))) is not None}
        old = states.get(i)
        if old is None:
            states[i] = dict(st)
            work.append(i)
            return
        new = {}
        lost: list = []  # session 31 (arg-keep, join-keep): (k, value) of an address the join dropped
        for k in (set(old) | set(st)) if arg_join else list(old):
            v = old.get(k)
            if k in carry.get(i, ()) and (cap := carry_value(i, k)) is not None:
                new[k] = cap  # a counter the outer loop carries over (session 29)
                continue
            if lp is not None and k in lp[4] and (cap := loop_value(i, k)) is not None:
                new[k] = cap  # the counter bounds the walk: no widening
                continue
            if counter_cap and lp is not None and k == lp[1] and (cap := counter_value(i)) is not None:
                new[k] = cap  # the up-counter itself (session 27)
                continue
            if op_ is not None and k in op_[4] and (cap := outer_value(i, k)) is not None:
                new[k] = cap  # stepped once per outer iteration (session 29)
                continue
            j = join(i, k, v, st.get(k))
            if (arg_keep and arg_join) if isinstance(j, tuple) and j[0] == ARG else join_keep:
                lost += [(k, x_) for x_ in (v, st.get(k)) if _addressy(x_) and not _covers(j, x_)]
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
        for k, x_ in lost:  # session 31 (arg-keep, join-keep): visit i again with the address the join dropped
            got = shadow_lost.setdefault((i, k), set())
            if x_ not in got and len(got) >= SHADOW_MAX:
                x_ = _widen(x_, got)  # a value that keeps changing here (a walk): base + unknown offset
            got.add(x_)
            sh = dict(new)
            sh[k] = x_
            key = (i, frozenset(sh.items()))
            if key not in shadow_seen:
                shadow_seen.add(key)
                work.append((i, sh))

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
        if -0x10000 < lim < 0x10000 and (cur is None or _ub(cur) is not None or isinstance(cur, tuple) and cur[0] in (PTR, AX)
                                          or cases and isinstance(cur, tuple) and cur[0] == ARG):
            # (an argument below a small limit is a number, not a pointer: switch(a0 + 1) and such)
            u = _ub(cur)
            if u is None or u > lim - 1:
                st[r] = (UB, lim - 1)

    def end_compare(pc, x, y, how):
        """Session 28 (end-ptr): a compare or subtract of a value against an exact image address A.
        `p < &N` / `&N - p` (A the minuend) uses A as the end of whatever p walks: when A starts a name N, the object
        before N must stay next to it (the actor table D_002C64A0 is walked with `p >= D_002E26A0` as
        its end). An equality test only counts when the other side is a pointer known to come from
        another address (an identity test `o == &N` is common and harmless)."""
        out = []
        for a_, b_ in ((x, y),) if how == "sub" else ((x, y), (y, x)):  # `p - &N` is an index into N
            if not (isinstance(a_, int) and BLOB_START <= a_ < IMAGE_END + 0x10000) or isinstance(b_, int):
                continue
            if how == "eq":
                ib = _idx(b_)
                if ib is None or ib[0] == a_:
                    continue
            out.append((pc, a_, None, 0, "end-" + how))
        return out

    def step(ins, st):
        w = ins.word
        o, s, t, d = mips.op(w), mips.rs(w), mips.rt(w), mips.rd(w)
        ev = []
        before = dict(st)
        if o == mips.OP_LUI:
            st[t] = (HI, (w & 0xFFFF) << 16)
            if arg_bound and TEXT_START <= st[t][1] < BLOB_START:
                ev.append(("codeaddr", st[t][1]))
        elif o in (0x09, 0x19):  # addiu / daddiu
            b = st.get(s)
            if isinstance(b, tuple) and b[0] == HI:  # %hi + %lo: a relocated address (shift_cmp maps it)
                st[t] = (b[1] + mips.imm(w)) & 0xFFFFFFFF
                if arg_bound and TEXT_START <= st[t] < BLOB_START:
                    ev.append(("codeaddr", st[t]))  # a code address built: a function called through a pointer
                if st[t] >> 28 in (2, 3) and BLOB_START <= st[t] & 0x0FFFFFFF < IMAGE_END + 0x10000:
                    ev.append((ins.addr, st[t] & 0x0FFFFFFF, None, 0, "uncached"))
            elif isinstance(b, int):
                v = (b + mips.imm(w)) & 0xFFFFFFFF
                if (w & 0xFFFF) != 0 or s != t:
                    ev.append((ins.addr, b, mips.imm(w), 0, "addr"))
                st[t] = v if b > 0x10000 or not (b + mips.imm(w)) < 0 else b + mips.imm(w)
                if arg_bound and TEXT_START <= v < BLOB_START:
                    ev.append(("codeaddr", v))
            elif isinstance(b, tuple) and b[0] == ARG:
                st[t] = (ARG, b[1], b[2] + mips.imm(w)) + b[3:]
            elif isinstance(b, tuple) and b[0] == PTR:
                st[t] = (PTR, b[1], None if b[2] is None else b[2] + mips.imm(w))
            elif isinstance(b, tuple) and b[0] == IDX:
                st[t] = (IDX, b[1], None if b[2] is None else b[2] + mips.imm(w))
                if len(b) > 3 and b[2] is None:  # (session 30) the scaled argument index, + imm
                    st[t] = st[t] + ((AX, b[3][1], b[3][2], b[3][3] + mips.imm(w)),)
            elif isinstance(b, tuple) and b[0] == UB:
                st[t] = (UB, b[1] + mips.imm(w))
            elif isinstance(b, tuple) and b[0] == HIX:  # &D[i] built as lui + addu + addiu %lo
                st[t] = (IDX, (b[1] + mips.imm(w)) & 0xFFFFFFFF, b[2]) + b[3:]
            elif isinstance(b, tuple) and b[0] == AX:
                st[t] = (AX, b[1], b[2], b[3] + mips.imm(w))
            elif isinstance(b, tuple) and b[0] == SET:
                if (w & 0xFFFF) != 0 or s != t:
                    ev += [(ins.addr, x, mips.imm(w), 0, "addr") for x in sorted(b[1])]
                st[t] = (SET, frozenset((x + mips.imm(w)) & 0xFFFFFFFF for x in b[1]))
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
            if o in (0x2B, 0x3F) and t != 0 and _addrs(st.get(t)):  # sw/sd of an address (or of each one a join holds)
                ev += [(ins.addr, x, None, 0, "stored") for x in sorted(_addrs(st[t]))]
                g_ = _gaddr(b, w)
                if g_ is not None:  # ... into a pointer global G (session 25: followed through G's loads)
                    ev += [("storedto", x, g_) for x in sorted(_addrs(st[t]))]
            elif stored_idx and o in (0x2B, 0x3F) and t != 0 and isinstance(st.get(t), tuple) and st[t][0] == IDX:
                # session 31 (stored-idx): &D[i] stored is D stored (before, only an exact address counted, so a
                # store seen only with the joined state of a loop, base + index, was not reported)
                ev.append((ins.addr, st[t][1], None, 0, "stored"))
            if o in mips.OP_STORES or o in (0x1F, 0x3E):  # the bytes a store may write (session 27)
                if _addrs(b):
                    ev += [("wr", (x + mips.imm(w)) & 0xFFFFFFFF, WIDTH[o]) for x in sorted(_addrs(b))]
                elif isinstance(b, tuple) and b[0] in (IDX, HIX):
                    lo_ = (b[1] + (mips.imm(w) if b[0] == IDX else 0)) & 0xFFFFFFFF
                    # session 30 (wr-span): from lo_ (which has the displacement of an IDX base) the store
                    # reaches offset + width; the displacement was added twice (too short when it is negative)
                    span = b[2] + WIDTH[o] + (mips.imm(w) if b[0] == HIX or not wr_span else 0) \
                        if b[2] is not None else None
                    ev.append(("wr", lo_, span))
            if isinstance(b, tuple) and b[0] == PTR:
                ev.append(("ptrmem", b[1], None if b[2] is None else b[2] + mips.imm(w), WIDTH[o]))
            if isinstance(b, int):
                ev.append((ins.addr, b, mips.imm(w), WIDTH[o], "mem"))
            elif isinstance(b, tuple) and b[0] == SET:
                ev += [(ins.addr, x, mips.imm(w), WIDTH[o], "mem") for x in sorted(b[1])]
            elif isinstance(b, tuple) and b[0] == HIX and len(b) > 3:  # D[a*m] (session 30): bounded by the callers
                ev.append(("argidx", ins.addr, (b[1] + mips.imm(w)) & 0xFFFFFFFF, b[3][1], b[3][2], b[3][3],
                           WIDTH[o]))
            elif isinstance(b, tuple) and b[0] == IDX and len(b) > 3:
                ev.append(("argidx", ins.addr, b[1], b[3][1], b[3][2], b[3][3] + mips.imm(w), WIDTH[o]))
            elif isinstance(b, tuple) and b[0] == HIX:  # D[i] as lui + addu + lw %lo(D)
                ev.append((ins.addr, (b[1] + mips.imm(w)) & 0xFFFFFFFF, b[2], WIDTH[o], "idx"))
            elif isinstance(b, tuple) and b[0] == IDX:
                ev.append((ins.addr, b[1], None if b[2] is None else b[2] + mips.imm(w), WIDTH[o], "idx"))
            elif isinstance(b, tuple) and b[0] == ARG:
                ev.append(("argmem", b[1], b[2] + mips.imm(w), WIDTH[o]))
            if (ins.is_load or o == 0x1E) and o not in (0x31, 0x35, 0x36):  # gpr destination (lq too)
                if o == 0x24:  # lbu
                    st[t] = (UB, 0xFF)
                elif o == 0x25:  # lhu
                    st[t] = (UB, 0xFFFF)
                elif o == 0x23 and read_word and isinstance(b, tuple) and b[0] == HIX and b[2] is not None \
                        and 0 <= b[2] <= 0x400:
                    st[t] = (JT, (b[1] + mips.imm(w)) & 0xFFFFFFFF, b[2])  # a switch's jump table
                elif o == 0x23 and ptr_globals and _gaddr(b, w) is not None:
                    st[t] = (PTR, _gaddr(b, w), 0)  # the pointer a global holds
                else:
                    st.pop(t, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x21, 0x2D, 0x20, 0x2C, 0x25):  # addu daddu add dadd or
            x, y = st.get(s), st.get(t)
            if mips.funct(w) in (0x25, 0x21, 0x2D) and d != 0:  # base | 0x20000000: the uncached alias
                xv = x[1] if isinstance(x, tuple) and x[0] == HI else x
                yv = y[1] if isinstance(y, tuple) and y[0] == HI else y
                for b, m in ((xv, yv), (yv, xv)):
                    if isinstance(b, int) and isinstance(m, int) and m in (0x20000000, 0x30000000) \
                            and BLOB_START <= b < IMAGE_END + 0x10000:
                        ev.append((ins.addr, b, None, 0, "uncached"))
            hx = [(p_, q_) for p_, q_ in ((x, y), (y, x)) if isinstance(p_, tuple) and p_[0] == HI
                  and not (isinstance(q_, int) or isinstance(q_, tuple) and q_[0] == HI)]
            if hi_index and mips.funct(w) in (0x21, 0x2D) and s != 0 and t != 0 and d != 0 and len(hx) == 1:
                # lui + addu index: the %lo load or addiu that follows indexes from %hi + %lo
                u = _ub(hx[0][1])
                st[d] = (HIX, hx[0][0][1], u if u is not None and u >= 0 else None)
                if arg_bound and st[d][2] is None and (ax_ := _ax(hx[0][1])) is not None:
                    st[d] = st[d] + (ax_,)  # (session 30) lui + addu of a scaled argument
                x = y = "done"
            x = None if isinstance(x, tuple) and x[0] in (HI, LT) else x
            y = None if isinstance(y, tuple) and y[0] in (HI, LT) else y
            if s != 0 and t != 0:
                for p_, q_ in ((x, y), (y, x)):
                    if isinstance(p_, tuple) and p_[0] == ARG and not isinstance(q_, int):
                        wide.add(p_[1])
            if x == "done":
                pass
            elif t == 0 or s == 0:  # a move
                v = x if t == 0 else y
                if v is None:
                    st.pop(d, None)
                else:
                    st[d] = v
            elif isinstance(x, int) and isinstance(y, int):
                st[d] = (x + y) & 0xFFFFFFFF if mips.funct(w) != 0x25 else x | y
            elif mips.funct(w) != 0x25 and any(isinstance(p_, tuple) and p_[0] == SET and isinstance(q_, int)
                                                and -0x10000 < q_ < 0x10000 for p_, q_ in ((x, y), (y, x))):
                sv, c_ = (x, y) if isinstance(x, tuple) and x[0] == SET else (y, x)
                st[d] = (SET, frozenset((e_ + c_) & 0xFFFFFFFF for e_ in sv[1]))
            elif mips.funct(w) != 0x25 and any(isinstance(p_, tuple) and p_[0] == PTR and _idx(q_) is None
                                                for p_, q_ in ((x, y), (y, x))):
                pv, other = (x, y) if isinstance(x, tuple) and x[0] == PTR else (y, x)
                off = pv[2] + other if pv[2] is not None and isinstance(other, int) and -0x10000 < other < 0x10000 \
                    else None
                st[d] = (PTR, pv[1], off)
            elif _idx(x) is not None or _idx(y) is not None:
                a, other = (_idx(x), y) if _idx(x) is not None else (_idx(y), x)
                u = _ub(other)
                if mips.funct(w) == 0x25 or a[1] is None or u is None:
                    st[d] = (IDX, a[0], None)
                    if arg_bound and mips.funct(w) != 0x25 and a[1] is not None and (ax_ := _ax(other)) is not None:
                        st[d] = st[d] + ((AX, ax_[1], ax_[2], ax_[3] + a[1]),)  # (session 30) &D + a*m
                else:
                    st[d] = (IDX, a[0], a[1] + u)
            elif _ub(x) is not None and _ub(y) is not None and mips.funct(w) != 0x25:
                st[d] = (UB, _ub(x) + _ub(y))
            else:
                st.pop(d, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x23, 0x2F):  # subu dsubu
            x = st.get(s)
            if end_ptr and d != 0:
                ev += end_compare(ins.addr, x, st.get(t), "sub")
            if isinstance(x, tuple) and x[0] == ARG:
                wide.add(x[1])
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
            elif arg_bound and mips.funct(w) == 0x00 and sh < 16 and d != 0 and (ax_ := _ax(st.get(t))) is not None:
                st[d] = (AX, ax_[1], ax_[2] << sh, ax_[3] << sh)  # (session 30) an argument scaled
            else:
                st.pop(d, None)
        elif o == mips.OP_SPECIAL and mips.funct(w) in (0x2A, 0x2B):  # slt sltu: t = s < t
            lim = st.get(t)
            if end_ptr and d != 0:
                ev += end_compare(ins.addr, st.get(s), lim, "lt")
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
        if arg_bound:  # (session 30) each argument register at a direct call: an exact value, the caller's own
            # argument + an offset ("arg", k, off; not one a join made), or None
            ev.append(("callargs", target, ins.addr, tuple(
                st.get(r) if isinstance(st.get(r), int) and -0x10000 < st.get(r) < 0x10000
                else st.get(r) if isinstance(st.get(r), tuple) and st.get(r)[0] == ARG and len(st.get(r)) == 3
                and -0x10000 < st.get(r)[2] < 0x10000 else None for r in ARG_REGS)))
        # a known block function: its pointer arguments with their byte counts
        for ptr, size in BLOCK_CALLS.get(target, ()):
            b, n_ = st.get(ptr), size(st)
            if isinstance(b, int) and isinstance(n_, int) and 0 < n_ <= 0x100000:
                ev.append((ins.addr, b, 0, n_, f"call:{target:08x}:"))
        blk = {}  # argument -> byte count a block function is given for it (session 21)
        for ptr, size in BLOCK_CALLS.get(target, ()):
            n_ = size(st)
            if ptr in ARG_REGS and isinstance(n_, int) and 0 < n_ <= 0x100000:
                blk[ARG_REGS.index(ptr)] = n_
        if True:
            for j, r in enumerate(ARG_REGS):
                v = st.get(r)
                if isinstance(v, tuple) and v[0] == SET:  # each address of a join is passed
                    ev += [("pass", target, j, x, ins.addr) for x in sorted(v[1])]
                    ev += [("passidx", target, j, x, 0, ins.addr, blk.get(j)) for x in sorted(v[1])]
                    continue
                a_ = _idx(v)
                if a_ is not None:  # &D_X[i] passed to a call: an indexed access the callee makes (session 20)
                    ev.append(("passidx", target, j, a_[0], a_[1], ins.addr, blk.get(j)))
                if (isinstance(v, int) and v > 0x10000) or (isinstance(v, tuple) and v[0] == ARG):
                    ev.append(("pass", target, j, v, ins.addr))
        return ev

    def jump_table(v):
        """The case addresses of a jump table register (all inside this function), or None."""
        if not (isinstance(v, tuple) and v[0] == JT):
            return None
        out = []
        for off in range(0, v[2] + 4, 4):
            x = read_word(v[1] + off)
            if x is None or not (a0 <= x < a0 + 4 * n) or x & 3:
                return None
            out.append(x)
        return out

    after_jr = sorted(insns[k + 2].addr for k in range(n - 2) if insns[k].is_jr) if cases else []
    while work:
        i = work.pop(visit_rng.randrange(len(work)) if visit_rng else -1)
        if isinstance(i, tuple):  # a shadow visit (session 31, arg-keep)
            i, st = i[0], dict(i[1])
        else:
            st = dict(states[i])
        ins = insns[i]
        ev = []
        if ins.is_branch or ins.is_j or ins.is_jr or ins.is_jal or ins.is_jalr:
            likely = mips.op(ins.word) in (0x14, 0x15, 0x16, 0x17) or (
                mips.op(ins.word) == mips.OP_REGIMM and mips.rt(ins.word) in (0x02, 0x03, 0x12, 0x13))
            call = ins.is_jal or ins.is_jalr
            w = ins.word
            cond = None
            if end_ptr and mips.op(w) in (0x04, 0x05, 0x14, 0x15) and mips.rt(w) and mips.rs(w):
                ev += end_compare(ins.addr, st.get(mips.rs(w)), st.get(mips.rt(w)), "eq")
            if mips.op(w) in (0x04, 0x05, 0x14, 0x15) and (mips.rt(w) == 0) != (mips.rs(w) == 0):
                cond = (mips.rs(w) or mips.rt(w), mips.op(w) in (0x05, 0x15))  # (t, branch-if-nonzero)
            # session 27 (slot-refine): a branch's test refines the state before its delay slot, so a
            # slot that scales the counter (`bne v1,$0,loop; sll v0,s2,2`) sees the capped counter
            edge_first = slot_refine and ins.is_branch and cond is not None and i + 1 < n
            if i + 1 < n and not edge_first:  # (with edge_first each edge steps the slot itself)
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
            elif ins.is_branch and edge_first:
                st_t = dict(st)
                refine(st_t, cond, True)
                ev += step(insns[i + 1], st_t)
                merge(index(ins.branch_target), st_t, src=i)
                st_f = dict(st)
                refine(st_f, cond, False)
                if not likely:
                    ev += step(insns[i + 1], st_f)
                merge(i + 2, st_f)
            elif ins.is_branch:
                st_t = dict(st_d)
                if cond and cond[0] in st and st.get(cond[0]) == st_d.get(cond[0]):
                    refine(st_t, cond, True)
                merge(index(ins.branch_target), st_t, src=i)
                always = (mips.op(w) == 0x04 and mips.rs(w) == mips.rt(w)) or (
                    mips.op(w) == mips.OP_REGIMM and mips.rt(w) in (0x01, 0x11) and mips.rs(w) == 0)
                if not always:  # `b` is beq $0,$0 (or bgez $0): no fall-through
                    st_f = dict(st if likely else st_d)
                    if cond and cond[0] in st and st.get(cond[0]) == st_f.get(cond[0]):
                        refine(st_f, cond, False)
                    merge(i + 2, st_f)
            elif ins.is_j:
                merge(index(ins.jump_target), st_d)
            elif ins.is_jr and not ins.is_jr_ra and (jt := jump_table(st.get(mips.rs(w)))):
                for j in jt:  # a switch whose table we read: each case
                    merge(index(j), st_d)
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
        if not work and args:
            for k in sorted(wide):
                if ("argwide", k) not in seen_out:
                    seen_out.add(("argwide", k))
                    yield ("argwide", k)
        if not work and starts:
            # unreached code: start fresh at the next listed label
            for j in sorted(set(starts) | set(after_jr)):  # also the code after a `jr` (a switch's cases)
                k = index(j)
                if 0 <= k < n and k not in states:
                    states[k] = {0: 0}
                    work.append(k)
                    break


ALL_ARGS = frozenset(ARG_REGS)
# EE kernel syscalls (v1 = number, arguments in a0..) whose argument count is known (ps2sdk kernel.h);
# any other syscall reads every argument register.
SYSCALL_ARGS = {0x64: 1, -0x68: 1,  # FlushCache(op), iFlushCache(op)
                0x14: 1, 0x15: 1, 0x16: 1, 0x17: 1, -0x1A: 1, -0x1B: 1, -0x1C: 1, -0x1D: 1,  # [i]Enable/Disable Intc/Dmac
                0x2F: 0, 0x32: 0, 0x33: 1, -0x34: 1,  # GetThreadId, SleepThread, [i]WakeupThread
                0x40: 1, 0x41: 1, 0x42: 1, -0x43: 1, 0x44: 1, 0x45: 1, -0x46: 1, 0x47: 2, -0x48: 2}  # semaphores


def gpr_reads(w: int) -> set[int] | None:
    """General registers an instruction may read (an over-approximation); None for one that may read
    any argument register (syscall, an opcode not listed here). A call's own reads are handled by
    arg_live()."""
    o = mips.op(w)
    s, t = mips.rs(w), mips.rt(w)
    if o == mips.OP_SPECIAL:
        if mips.funct(w) in (0x0C, 0x0D):  # syscall / break
            return None
        if mips.funct(w) in (0x0A, 0x0B):  # movz / movn keep rd when the test fails
            return {s, t, mips.rd(w)}
        return {s, t}
    if o == mips.OP_MMI:
        return {s, t}
    if o == mips.OP_REGIMM:
        return {s}
    if o in (0x02, 0x03, 0x0F):  # j jal lui
        return set()
    if 0x08 <= o <= 0x0E or o in (0x18, 0x19):  # addi .. xori, daddi daddiu
        return {s}
    if o in mips.OP_BRANCH:
        return {s, t}
    if o in (0x1A, 0x1B, 0x22, 0x26):  # ldl ldr lwl lwr merge into rt
        return {s, t}
    if o in mips.OP_LOADS or o in (0x1E, 0x2F, 0x33, 0x36):  # loads, lq, cache, pref, lqc2
        return {s}
    if o in mips.OP_STORES or o in (0x1F, 0x3E):  # stores, sq, sqc2
        return {s, t}
    if o in (mips.OP_COP0, mips.OP_COP1, mips.OP_COP2):
        return {t}  # mtc/ctc/dmtc/qmtc2 read rt; the rest read no gpr (rt is extra, harmless)
    return None


def arg_live(funcs: list[tuple[int, list[mips.Insn]]], read_word=None) -> dict[int, frozenset]:
    """Session 27 (dead-arg): the argument registers each function may read before writing them, on
    any path, including what the functions it calls or tail-calls read (a least fixpoint over the
    call graph). A value left in a0-t3 at a call is an argument only if the callee reads it.

    Conservative where the code leaves the function: an unknown callee, a jalr, a syscall, a switch's
    `jr`, a branch out of the function or a fall-through past its end read every argument register.
    After a jal the caller-saved registers are dead (the EE ABI: a callee may clobber them)."""
    live: dict[int, frozenset] = {f_: frozenset() for f_, _x in funcs}
    cs = frozenset(CALLER_SAVED)

    def one(insns):
        n = len(insns)
        a0 = insns[0].addr
        lin = [frozenset()] * (n + 2)

        def callee_live(t):
            return live.get(t, ALL_ARGS)

        def through(j, after):
            """Live before instruction j (a delay slot or a plain one) given live after it."""
            r = gpr_reads(insns[j].word) if j < n else None
            if r is None and j < n and insns[j].is_syscall and j > 0:
                p_ = insns[j - 1].word  # li v1, N; syscall
                if mips.op(p_) == 0x09 and mips.rs(p_) == 0 and mips.rt(p_) == 3 and mips.imm(p_) in SYSCALL_ARGS:
                    r = {3} | set(ARG_REGS[:SYSCALL_ARGS[mips.imm(p_)]])
            if r is None:
                return after | ALL_ARGS
            return frozenset(r) | (after - gpr_writes(insns[j].word))

        def at(k):
            if 0 <= k < n:
                return lin[k]
            return ALL_ARGS  # off the end of the function, or a branch outside it

        changed = True
        while changed:
            changed = False
            for i in range(n - 1, -1, -1):
                x = insns[i]
                w = x.word
                if x.is_jal:
                    after = (at(i + 2) - cs) | callee_live(x.jump_target)
                    v = through(i + 1, after)
                elif x.is_jalr:
                    after = (at(i + 2) - cs) | ALL_ARGS
                    v = frozenset({mips.rs(w)}) | through(i + 1, after)
                elif x.is_j:
                    t_ = x.jump_target
                    k = (t_ - a0) // 4
                    after = at(k) if a0 <= t_ < a0 + 4 * n else callee_live(t_)
                    v = through(i + 1, after)
                elif x.is_jr_ra:
                    v = through(i + 1, frozenset())
                elif x.is_jr:
                    v = frozenset({mips.rs(w)}) | ALL_ARGS
                elif x.is_branch:
                    k = (x.branch_target - a0) // 4
                    likely = mips.op(w) in (0x14, 0x15, 0x16, 0x17) or (
                        mips.op(w) == mips.OP_REGIMM and mips.rt(w) in (0x02, 0x03, 0x12, 0x13))
                    r = gpr_reads(w)
                    r = ALL_ARGS if r is None else frozenset(r)
                    if mips.op(w) == mips.OP_REGIMM and mips.rt(w) in (0x10, 0x11, 0x12, 0x13):
                        r = ALL_ARGS  # bltzal & co: a call
                    if likely:
                        v = r | through(i + 1, at(k)) | at(i + 2)
                    else:
                        v = r | through(i + 1, at(k) | at(i + 2))
                else:
                    v = through(i, at(i + 1))
                if v != lin[i]:
                    lin[i] = v | lin[i]
                    changed = True
        return lin[0] & ALL_ARGS

    for _round in range(64):
        changed = False
        for f_, insns in funcs:
            if not insns:
                continue
            v = one(insns)
            if v != live[f_]:
                live[f_] = v | live[f_]
                changed = True
        if not changed:
            break
    else:
        return {}  # no fixpoint: callers treat every register as live
    return live


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
    ap.add_argument("--no-idx-base", action="store_true",
                    help="do not keep a floated indexed base whose next name stays in place (session 20 rule)")
    ap.add_argument("--no-stored", action="store_true",
                    help="do not treat a stored address as an unbounded indexed base (session 20 rule)")
    ap.add_argument("--no-uncached", action="store_true",
                    help="do not keep names whose uncached alias is built (session 20 rule)")
    ap.add_argument("--no-countdown", action="store_true",
                    help="do not bound pointer walks by a decrementing loop counter (session 21 rule)")
    ap.add_argument("--no-join", action="store_true",
                    help="a join of exact addresses is the lowest one + an index, not each address (session 21)")
    ap.add_argument("--no-arg-join", action="store_true",
                    help="an argument joined with any other value is walked (wide; session 20 behaviour)")
    ap.add_argument("--no-hi-index", action="store_true",
                    help="ignore D[i] built as lui + addu + %%lo (and switch tables read from the ELF; session 21)")
    ap.add_argument("--no-switch", action="store_true",
                    help="do not read switch jump tables, nor analyse the code after a `jr` nothing branches to")
    ap.add_argument("--no-block-bound", action="store_true",
                    help="&B[i] passed to memcpy/memset/pool init is unbounded even with a known count (session 20)")
    ap.add_argument("--no-ptr-global", action="store_true",
                    help="do not follow an address stored into a pointer global through the global's loads "
                         "(session 25)")
    ap.add_argument("--no-piece-next", action="store_true",
                    help="an unbounded index keeps only the next name, even when that name is inside the base's "
                         "own piece (session 25: then the next name after the piece)")
    ap.add_argument("--no-counter-cap", action="store_true",
                    help="do not cap an up-counter (i = i0; ... i += k; while (i < L)) at its loop header (session 27)")
    ap.add_argument("--no-slot-refine", action="store_true",
                    help="refine a branch's edges after its delay slot, not before (session 27)")
    ap.add_argument("--no-str-arg", action="store_true",
                    help="a string literal passed to printf/strcpy/strcmp/... is not bounded by its NUL (session 27)")
    ap.add_argument("--no-list-arg", action="store_true",
                    help="a -1/negative-terminated list literal does not bound func_0024afc0 & co (session 27)")
    ap.add_argument("--no-dma-count", action="store_true",
                    help="func_00237018(buf, n) is not a block access of 16 * n bytes (session 27)")
    ap.add_argument("--no-dma-chain", action="store_true",
                    help="a static DMA chain sent by func_00106b18 & co is not bounded by its parsed tags (session 27)")
    ap.add_argument("--no-dead-arg", action="store_true",
                    help="an address left in an argument register at a call is passed even when the callee never "
                         "reads that register (session 27)")
    ap.add_argument("--no-end-ptr", action="store_true",
                    help="a compare or subtract against a name's address does not tie the object before it to "
                         "the name (session 28)")
    ap.add_argument("--no-nest-carry", action="store_true",
                    help="do not bound a counter an inner loop steps and its outer loop carries over (session 29)")
    ap.add_argument("--no-path-step", action="store_true",
                    help="prove a loop's counter step and walked pointers only by single writes, not over the paths "
                         "of its body (session 30)")
    ap.add_argument("--no-wr-span", action="store_true",
                    help="count an indexed store's displacement twice in the bytes it may write (before session 30)")
    ap.add_argument("--no-arg-bound", action="store_true",
                    help="an index made from a function's argument is unbounded even when every caller passes a "
                         "constant (session 30)")
    ap.add_argument("--no-arg-keep", action="store_true",
                    help="an argument joined with an address drops the address (the address's accesses are seen only "
                         "when its path is visited first; before session 31)")
    ap.add_argument("--no-join-keep", action="store_true",
                    help="a join of an address with an unknown value (or one it does not cover) drops the address "
                         "(before session 31)")
    ap.add_argument("--no-stored-idx", action="store_true",
                    help="storing base + an index (&D[i]) does not count as storing D (before session 31)")
    ap.add_argument("--data-tsv", type=Path, default=ROOT / "out/gen/data.tsv",
                    help="variable sizes and the default pieces (a copy with pieces split tests a layout)")
    ap.add_argument("--explain", type=Path, help="write one line per indexed argument (&B[i] passed to a call) "
                    "with its callee, bound and reason")
    ap.add_argument("--visit-seed", type=int, help="visit each function's points in a random order from this seed "
                    "(a check of order dependence: diff the output against the default order's; session 31)")
    ap.add_argument("--debug", type=lambda x: int(x, 16), help="print the call sites passing this address")
    a = ap.parse_args()

    if not a.no_dma_count:
        BLOCK_CALLS.update(DMA_COUNT_CALLS)
    sizes = {}
    for ln in a.data_tsv.read_text().splitlines()[1:]:
        f = ln.split("\t")
        sizes[f[1]] = int(f[3], 16) if f[3].startswith("0x") else int(f[3], 16)
    if a.ld:
        pcs = pieces_from_ld(a.ld, sizes)
    else:
        pcs = []
        for ln in a.data_tsv.read_text().splitlines()[1:]:
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

    def read_word(addr: int):
        b_ = elf.read(addr, 4)
        return None if b_ is None else struct.unpack("<I", b_)[0]

    live_in = {} if a.no_dead_arg else arg_live([(r_[1][0].addr, r_[1]) for r_ in regions
                                                 if r_[1] and not r_[0].endswith(".x")])
    dead_arg = 0

    hits: dict[tuple, set] = {}
    idx: dict[int, set] = {}
    idx_all: dict[int, set] = {}
    idx_end: dict[int, int | None] = {}  # indexed base -> end of the furthest bounded access (None: unbounded)
    own: dict[int, dict[int, list[int]]] = {}  # function -> arg -> [lo, hi) reached from it
    passes: dict[int, list] = {}  # function -> [(callee, j, ("arg", k, off))]
    sites: list = []  # (caller name, callee, j, address)
    passidx: list = []  # (caller name, callee, j, base, bound of the offset or None)
    wide_args: dict[int, set] = {}  # function -> arguments it walks or indexes
    stored: set[int] = set()  # addresses some function stores to memory
    uncached: dict[int, set] = {}  # address -> functions that build its 0x20000000/0x30000000 alias
    why: dict[int, set] = {}  # indexed base -> the kinds of access that make it one (shown in the log)
    ptr_stores: dict[int, set] = {}  # pointer global G -> the addresses code stores into it
    ptr_users: dict[int, set] = {}  # pointer global G -> functions that access through the pointer G holds
    ptr_reach: dict[int, int | None] = {}  # G -> end of the furthest access through it (None: indexed)
    explain: list[str] = []
    writes: list = []  # (address, bytes or None for an unbounded index) of every store from a known base
    end_uses: dict[int, dict] = {}  # address compared or subtracted as an end -> kind -> functions (end-ptr)
    codeaddr: set[int] = set()  # code addresses some code builds (arg-bound: functions called through pointers)
    calls_to: dict[int, dict] = {}  # callee -> call pc -> exact argument values at the call (None: unknown)
    argidx: list = []  # (function name, start, pc, address, k, m, a, width): D[arg k * m + a] (arg-bound)

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
        for e in analyse(insns, set(x for x in labels if x), args=is_func,
                         countdown=not a.no_countdown, joins=not a.no_join, arg_join=not a.no_arg_join,
                         hi_index=not a.no_hi_index, cases=not a.no_switch,
                         read_word=read_word if is_func and not a.no_switch else None,
                         ptr_globals=not a.no_ptr_global, counter_cap=not a.no_counter_cap,
                         slot_refine=not a.no_slot_refine, end_ptr=not a.no_end_ptr,
                         nest_carry=not a.no_nest_carry, path_step=not a.no_path_step,
                         wr_span=not a.no_wr_span, arg_keep=not a.no_arg_keep, join_keep=not a.no_join_keep,
                         stored_idx=not a.no_stored_idx,
                         visit_rng=None if a.visit_seed is None else random.Random(a.visit_seed * 1000003 + fstart),
                         arg_bound=not a.no_arg_bound and is_func):
            if e[0] == "argmem":
                _k, k, off, width = e
                r = own.setdefault(fstart, {}).setdefault(k, [off, off + width])
                r[0], r[1] = min(r[0], off), max(r[1], off + width)
                continue
            if e[0] == "storedto":
                ptr_stores.setdefault(e[2], set()).add(e[1])
                continue
            if e[0] == "codeaddr":  # session 30 (arg-bound)
                codeaddr.add(e[1])
                continue
            if e[0] == "callargs":
                cs_ = calls_to.setdefault(e[1], {})
                v_ = e[3] if is_func else None
                if e[2] in cs_:  # the call seen again with another state: what both allow
                    o_ = cs_[e[2]]
                    v_ = None if o_ is None or v_ is None else tuple(x_ if x_ == y_ else None for x_, y_ in zip(o_, v_))
                cs_[e[2]] = v_
                continue
            if e[0] == "argidx":
                argidx.append((name, fstart) + e[1:])
                continue
            if e[0] == "wr":
                writes.append((e[1], e[2]))
                continue
            if e[0] == "ptrmem":
                _k, g, off, width = e
                ptr_users.setdefault(g, set()).add(name)
                end = None if off is None else off + width
                if g not in ptr_reach or (ptr_reach[g] is not None and (end is None or end > ptr_reach[g])):
                    ptr_reach[g] = end
                continue
            if e[0] == "argwide":
                wide_args.setdefault(fstart, set()).add(e[1])
                continue
            if e[0] == "passidx":
                _p, callee, j, base, ub, _pc, nblk = e
                if BLOB_START <= base < IMAGE_END + 0x10000:
                    passidx.append((name, callee, j, base, ub, nblk, _pc))
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
            if kind == "uncached":
                uncached.setdefault(base, set()).add(name)
                continue
            if kind.startswith("end-"):
                end_uses.setdefault(base, {}).setdefault(kind, set()).add(name)
                continue
            if kind == "stored":
                # an address stored to memory is used through a pointer no check follows, often with
                # a length stored next to it (func_001e* keeps &D_003E4658 and 0x310 in D_003E8E28/2C,
                # and D_003E4658 is declared 8 bytes): its extent is unknown, like an unbounded index
                if not a.no_stored:
                    stored.add(base)
                    idx_all.setdefault(base, set()).add(name)
                    idx_end[base] = None
                    why.setdefault(base, set()).add("stored")
                continue
            if kind == "idx":
                idx_all.setdefault(base, set()).add(name)
                end = None if disp is None else base + disp + width
                why.setdefault(base, set()).add("idx" if end is None else "idx-ub")
                if base not in idx_end or (idx_end[base] is not None and (end is None or end > idx_end[base])):
                    idx_end[base] = end
                if piece(base)[0] is not None:
                    idx.setdefault(base, set()).add(name)
                continue
            check(name, base, disp, width, kind)
    # Session 30 (arg-bound): an access D[a_k * m + a] whose index is argument k of its function F, scaled. When
    # every way into F is a direct call (jal F or a tail call j F) that the analysis saw, with argument k an exact
    # value >= 0 at each, the index is at most m * (largest of them) + a. F is not proved when its address is
    # taken: a word equal to F anywhere in the ELF or an overlay, code that builds F (lui/addiu), a jal/j word for F
    # the analysis did not see as a call (or from an overlay), a branch into F from outside it, or code before F
    # that may fall into it. Otherwise (or with --no-arg-bound) the access stays unbounded, as before.
    if argidx:
        fn_end = {s_: e_ for s_, e_, _n in funcs}
        need = {f_ for _n, f_, *_r in argidx}
        img_words: set[int] = set()
        jal_pcs: dict[int, set] = {}
        blobs = [(elf.data, lambda off: next((sg.vaddr + off - sg.offset for sg in elf.segments
                                               if sg.offset <= off < sg.offset + sg.filesz and sg.type == 1), None))]
        for p_ in sorted(a.overlays.glob("*.x")) if a.overlays.is_dir() else []:
            blobs.append((p_.read_bytes(), lambda off: None))  # an overlay: any call or word is unknown
        for data_, vaddr_of in blobs:
            for (wd,) in struct.iter_unpack("<I", data_[: len(data_) & ~3]):
                img_words.add(wd)
            for off in range(0, len(data_) - 3, 4):
                wd = int.from_bytes(data_[off:off + 4], "little")
                if wd >> 26 in (2, 3) and (((wd & 0x3FFFFFF) << 2) in fn_end):
                    jal_pcs.setdefault((wd & 0x3FFFFFF) << 2, set()).add(vaddr_of(off))
        branched, targets = set(), set()
        for _rn, insns_ in regions:
            for x_ in insns_ or ():
                t_ = x_.branch_target if x_.is_branch else (x_.jump_target if x_.is_j else None)
                targets.add(t_)
                if x_.is_branch and x_.branch_target in fn_end and not (
                        x_.branch_target <= x_.addr < fn_end.get(x_.branch_target, 0)):
                    branched.add(x_.branch_target)

        def falls_into(f_):
            """Whether the code just before f_ may run on into it (no unconditional jump ends it)."""
            p_ = f_ - 4
            for _k in range(16):
                wd = read_word(p_)
                if wd is None:
                    return True
                if wd != 0:
                    break
                p_ -= 4
            else:
                return False  # only padding

            def uncond(x):
                return x is not None and (x == mips.JR_RA or (x >> 26 == 0 and x & 0x3F == 0x08) or x >> 26 == 2
                                          or (x >> 26 == 4 and (x >> 21) & 31 == (x >> 16) & 31))
            return not (uncond(read_word(p_)) or uncond(read_word(p_ - 4)) and p_ not in targets)

        arg_stats: dict[str, int] = {}
        fstarts = sorted(fn_end)

        def caller_of(pc_):
            i_ = bisect.bisect_right(fstarts, pc_) - 1
            return fstarts[i_] if i_ >= 0 and pc_ < fn_end[fstarts[i_]] else None

        direct: dict[int, bool] = {}

        def direct_only(f_):
            """Every way into f_ is a direct call the analysis saw (its argument values may still be unknown)."""
            if f_ not in direct:
                cs = calls_to.get(f_, {})
                direct[f_] = bool(cs) and f_ not in img_words and f_ not in codeaddr and f_ not in branched \
                    and not falls_into(f_) and all(pc_ in cs for pc_ in jal_pcs.get(f_, ())) \
                    and all(v_ is not None for v_ in cs.values())
                if not direct[f_] and f_ in need:
                    why_f = ("no direct call" if not cs else "address taken" if f_ in img_words or f_ in codeaddr
                             else "branched or fallen into" if f_ in branched or falls_into(f_)
                             else "a call not analysed" if not all(pc_ in cs for pc_ in jal_pcs.get(f_, ()))
                             else "a call from an overlay")
                    arg_stats[why_f] = arg_stats.get(why_f, 0) + 1
            return direct[f_]

        closure, todo = set(), sorted(need)  # the functions whose bounds are needed, and their callers'
        while todo:
            f_ = todo.pop()
            if f_ in closure:
                continue
            closure.add(f_)
            if direct_only(f_):
                for pc_, vs in calls_to.get(f_, {}).items():
                    if any(isinstance(v_, tuple) for v_ in vs) and (g_ := caller_of(pc_)) is not None:
                        todo.append(g_)
        ubs = arg_bounds(closure, calls_to, direct_only, caller_of)
        arg_ub: dict[int, tuple | None] = {f_: ubs[f_] for f_ in need}
        for name, f_, _pc, b_, k_, m_, a_, wdt in argidx:
            u_ = (arg_ub.get(f_) or (None,) * len(ARG_REGS))[k_]
            end = None if u_ is None or m_ < 0 else b_ + m_ * u_ + a_ + wdt
            if a.explain:
                explain.append(f"{b_:08x}\t{'idx-arg' if end is not None else 'idx'}\t{name}\t-\targ{k_}*{m_}+{a_}\t"
                               f"ub={u_}\tend={'+' + str(end - b_) if end is not None else None}\tpc={_pc:08x}")
            idx_all.setdefault(b_, set()).add(name)
            why.setdefault(b_, set()).add("idx" if end is None else "idx-arg")
            if b_ not in idx_end or (idx_end[b_] is not None and (end is None or end > idx_end[b_])):
                idx_end[b_] = end
            if piece(b_)[0] is not None:
                idx.setdefault(b_, set()).add(name)
    # Session 25: an address stored into a pointer global G is reached through every load of G. func_00106ed0
    # sets D_00494BAC = D_00472190 (chain 1's table, 16-byte ref tags) and func_00107548 indexes the pointer
    # with a 32-byte stride by a count loaded from room data, so the table runs into chain 2. Each address
    # stored into G is an indexed base reaching as far as the accesses through G (unbounded when indexed).
    for g, addrs in sorted(ptr_stores.items()):
        if g not in ptr_reach:
            continue
        for b_ in sorted(addrs):
            if not (BLOB_START <= b_ < IMAGE_END + 0x10000):
                continue
            end = None if ptr_reach[g] is None else b_ + ptr_reach[g]
            idx_all.setdefault(b_, set()).update(ptr_users[g])
            why.setdefault(b_, set()).add(f"via-ptr:{g:08x}" if end is None else f"via-ptr-ub:{g:08x}")
            if b_ not in idx_end or (idx_end[b_] is not None and (end is None or end > idx_end[b_])):
                idx_end[b_] = end
            if piece(b_)[0] is not None:
                idx.setdefault(b_, set()).update(ptr_users[g])
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
    for _round in range(12):  # an argument passed on to a callee that walks it is walked too
        changed = False
        for f, ps in passes.items():
            for callee, j, k, _off in ps:
                if j in wide_args.get(callee, ()) and k not in wide_args.get(f, ()):
                    wide_args.setdefault(f, set()).add(k)
                    changed = True
        if not changed:
            break
    anchors = sorted(anchor_addrs(a.anchors_elf) | {p_[0] for p_ in pcs})
    wr_small = sorted((x, n) for x, n in writes if n is not None and n <= 64)
    wr_big = [(x, n) for x, n in writes if n is not None and n > 64]
    wr_unb = sorted(x for x, n in writes if n is None)

    def obj_written(lo, hi):
        """Whether a store the analysis sees may write a byte of [lo, hi): an exact or bounded one that
        overlaps it, or an unbounded index from a base inside it (session 27)."""
        i_ = bisect.bisect_left(wr_small, (lo - 64, 0))
        while i_ < len(wr_small) and wr_small[i_][0] < hi:
            if wr_small[i_][0] + wr_small[i_][1] > lo:
                return True
            i_ += 1
        if any(x < hi and x + n > lo for x, n in wr_big):
            return True
        i_ = bisect.bisect_left(wr_unb, lo)
        return i_ < len(wr_unb) and wr_unb[i_] < hi

    def str_bound(callee, j, base, ub):
        """Offset past the NUL of a string literal at base (+ up to ub) that a STRING_ARGS callee reads
        as argument j, when that NUL is inside the literal's own object; else None (session 27)."""
        sk = STRING_ARGS.get(callee, {}).get(j)
        if a.no_str_arg or not sk or ub is None or not (BLOB_START <= base and base + ub < BSS_START):
            return None
        k_ = bisect.bisect_right(anchors, base)
        obj_end = min(anchors[k_] if k_ < len(anchors) else BSS_START, BSS_START)
        if obj_end - base > 0x10000 or obj_written(base, obj_end):
            return None
        return string_end(elf.read(base, obj_end - base), ub, sk)

    for name, callee, j, v in sites:
        c = reach.get(callee, {}).get(j)
        if callee in BLOCK_CALLS:  # their own byte count is checked at the call
            continue
        if str_bound(callee, j, v, 0) is not None:
            continue  # the callee's quadword reads past the NUL are discarded (session 27)
        if c and c[1] - c[0] <= 0x40000:
            check(name, v, c[0], c[1] - c[0], f"arg{j}:{fname.get(callee, hex(callee))}:")
    # &B[i] passed as argument j: the callee reaches [lo, hi) from it, so the access ends at
    # B + bound(i) + hi; unbounded when either is unknown (block functions count their bytes).
    str_arg = 0
    call_args: dict[tuple, dict] = {}  # (caller, pc) -> {argument: [(base, bound)]}
    for name, callee, j, base, ub, nblk, pc in passidx:
        call_args.setdefault((name, pc), {}).setdefault(j, []).append((base, ub))

    def list_end(name, pc, callee, j, base, ub):
        """End of argument j's reach at a LIST_CALLS call whose list argument is one list literal (session 27)."""
        spec = LIST_CALLS.get(callee)
        if a.no_list_arg or not spec or ub is None or (j != spec[0] and j not in spec[3]):
            return None
        la = call_args.get((name, pc), {}).get(spec[0], [])
        if len(la) != 1 or la[0][1] != 0 or not (BLOB_START <= la[0][0] < BSS_START):
            return None
        lb = la[0][0]
        k_ = bisect.bisect_right(anchors, lb)
        obj_end = min(anchors[k_] if k_ < len(anchors) else BSS_START, BSS_START)
        if obj_end - lb > 0x10000 or obj_written(lb, obj_end):
            return None
        cnt = list_count(elf.read(lb, obj_end - lb), spec[1], spec[2])
        if cnt is None:
            return None
        return base + ub + (spec[1] * (cnt + 1) if j == spec[0] else spec[3][j] * cnt)

    # DMA chains (session 27): a chain object passed only to CHAIN_CALLS, never stored, indexed or written
    # by any store the analysis sees, whose tags parse to the end inside the object: the DMA reads the
    # tags and inline data, and each ref/refe target for 16 * qwc bytes (an access from that address).
    uses: dict[int, set] = {}
    for name, callee, j, base, ub, nblk, pc in passidx:
        if callee in live_in and ARG_REGS[j] not in live_in[callee] and callee not in BLOCK_CALLS:
            continue  # not an argument (dead-arg)
        uses.setdefault(base, set()).add((callee, j, ub))
    stored_to = {x for xs in ptr_stores.values() for x in xs}

    def chain_of(base):
        if a.no_dma_chain or not (BLOB_START <= base < BSS_START) or base in stored or base in stored_to \
                or why.get(base, set()) & {"idx", "idx-ub"} or base in uncached:
            return None
        if any(CHAIN_CALLS.get(c_) != j_ or u_ != 0 for c_, j_, u_ in uses.get(base, ())):
            return None
        k_ = bisect.bisect_right(anchors, base)
        obj_end = min(anchors[k_] if k_ < len(anchors) else BSS_START, BSS_START)
        if obj_end - base > 0x10000 or obj_written(base, obj_end):
            return None  # (a store into the chain's object could change a tag)
        return parse_chain(read_word, base, obj_end)

    dma_chain = 0
    list_arg = 0
    for name, callee, j, base, ub, nblk, pc in passidx:
        ch_ = chain_of(base) if CHAIN_CALLS.get(callee) == j and ub == 0 else None
        if ch_ is not None:
            dma_chain += 1
            cend, refs = ch_
            for b_, end in [(base, cend)] + [(x, x + n) for x, n in refs]:
                why.setdefault(b_, set()).add("dma-chain" if b_ == base else "dma-ref")
                if a.explain:
                    explain.append(f"{b_:08x}\t{'dma-chain' if b_ == base else 'dma-ref'}\t{name}\t"
                                   f"{fname.get(callee, hex(callee))}\targ{j}\tub={ub}\tend=+{end - b_}\tblk=None")
                idx_all.setdefault(b_, set()).add(name)
                if b_ not in idx_end or (idx_end[b_] is not None and end > idx_end[b_]):
                    idx_end[b_] = end
                if piece(b_)[0] is not None:
                    idx.setdefault(b_, set()).add(name)
            continue
        le_ = list_end(name, pc, callee, j, base, ub)
        if le_ is not None:  # a list literal's count bounds the list and the arguments walked with it
            list_arg += 1
            why.setdefault(base, set()).add("arg-list")
            if a.explain:
                explain.append(f"{base:08x}\targ-list\t{name}\t{fname.get(callee, hex(callee))}\targ{j}\tub={ub}\t"
                               f"end=+{le_ - base}\tblk={nblk}")
            idx_all.setdefault(base, set()).add(name)
            if base not in idx_end or (idx_end[base] is not None and le_ > idx_end[base]):
                idx_end[base] = le_
            if piece(base)[0] is not None:
                idx.setdefault(base, set()).add(name)
            continue
        z_ = str_bound(callee, j, base, ub)
        if z_ is not None:  # a string literal read to its NUL, inside its own object (session 27)
            str_arg += 1
            why.setdefault(base, set()).add("arg-str")
            if a.explain:
                explain.append(f"{base:08x}\targ-str\t{name}\t{fname.get(callee, hex(callee))}\targ{j}\tub={ub}\t"
                               f"end=+{z_}\tblk={nblk}")
            idx_all.setdefault(base, set()).add(name)
            if base not in idx_end or (idx_end[base] is not None and base + z_ > idx_end[base]):
                idx_end[base] = base + z_
            if piece(base)[0] is not None:
                idx.setdefault(base, set()).add(name)
            continue
        if callee in live_in and ARG_REGS[j] not in live_in[callee] and callee not in BLOCK_CALLS:
            dead_arg += 1  # the callee never reads the register: the address is not an argument (session 27)
            continue
        c = reach.get(callee, {}).get(j)
        if ub is not None and c and c[1] - c[0] <= 0x40000 and c[0] >= 0 \
                and j not in wide_args.get(callee, ()) and callee not in BLOCK_CALLS:
            end = base + ub + c[1]
        elif ub is not None and nblk and not a.no_block_bound:  # memcpy/memset/pool init with a known count
            end = base + ub + nblk
        else:
            end = None
        r_ = ("arg-ub" if end is not None else "arg:block" if callee in BLOCK_CALLS else
              "arg:wide" if j in wide_args.get(callee, ()) else "arg:noreach" if not c else "arg:idx")
        why.setdefault(base, set()).add(r_)
        if a.explain:
            explain.append(f"{base:08x}\t{r_}\t{name}\t{fname.get(callee, hex(callee))}\targ{j}\tub={ub}\t"
                           f"reach={c}\tblk={nblk}")
        idx_all.setdefault(base, set()).add(name)
        if base not in idx_end or (idx_end[base] is not None and (end is None or end > idx_end[base])):
            idx_end[base] = end
        if piece(base)[0] is not None:
            idx.setdefault(base, set()).add(name)
    # An array indexed from B may run past the next name: D_00550400[i] for i < 64 (0x48-byte
    # entries) covers D_005512A0, which is entries 52..63 under its own name (session 18,
    # found from the stale writes in a RAM dump). A floated variable that is the next name
    # after an indexed base in another piece stays with it.
    bounded = []
    # stored: the address is stored; idx / arg: an unbounded index (an access, or &B[i] passed to a
    # call); -ub: a bounded one that ends past the next name
    _why = lambda b_: "[" + ",".join(sorted(why.get(b_, ()))) + "]"
    for base, fs in sorted(idx_all.items()):
        i = bisect.bisect_right(anchors, base)
        if i >= len(anchors):
            continue
        nxt = anchors[i]
        pb_ = piece(base)[0]
        if not a.no_piece_next and pb_ is not None and idx_end.get(base, 0) is None and piece(nxt)[0] == pb_:
            # unbounded, and the next name is inside the base's own piece (a merged piece, a bss run):
            # the access can run past the piece, into the first name after it (session 25)
            while i < len(anchors) and piece(anchors[i])[0] == pb_:
                i += 1
            if i >= len(anchors):
                continue
            nxt = anchors[i]
            why.setdefault(base, set()).add("piece-next")
        pn, nn = piece(nxt)
        if a.no_bounds is False and idx_end.get(base) is not None and idx_end[base] <= nxt:
            bounded.append((base, nxt, idx_end[base]))
            continue  # every indexed access from base is bounded and ends before the next name
        if pn is not None and pn != piece(base)[0] and nxt - base <= 0x10000:
            hits.setdefault((base, piece(base)[1], nxt, nn, "idx-next" + _why(base), 0), set()).update(fs)
        elif not a.no_idx_base and pn is None and piece(base)[0] is not None and nxt - base <= 0x10000:
            # the base floats and the next name stays: the array runs on into a name of the blob
            # (D_00472190 is declared 0x40, func_001073f0 copies 0x4000 bytes through it; session 20)
            hits.setdefault((base, piece(base)[1], nxt, nn, "idx-base" + _why(base), 0), set()).update(fs)
    # A name whose uncached alias (| 0x20000000 or 0x30000000) is built is a DMA/GIF buffer whose real
    # size no declaration gives: func_00162428 stores D_00573AC0 | 0x20000000 and func_0015f8c8 writes a
    # 0x500-byte packet through it (session 19). The base stays in place, and so does the next name.
    if not a.no_uncached:
        for base, fs in sorted(uncached.items()):
            i = bisect.bisect_right(anchors, base)
            nxt = anchors[i] if i < len(anchors) else base
            pb, nb = piece(base)
            pn, nn = piece(nxt)
            if pb is not None or pn is not None:
                hits.setdefault((base, nb, nxt, nn, "uncached", 0), set()).update(fs)
    # Session 28 (end-ptr): an address used as a walk's end (`p < &N`, `&N - p`, `p != &N` for a pointer
    # walked from elsewhere) that starts a name N ties the object ending there to N: D_002C64A0 (96 actors of
    # 1200 bytes) is walked with `if (p >= D_002E26A0) p = D_002C64A0` (func_00123810), so floating the table
    # lost Donald and Goofy (session 27, KH1_F27_R1). The object before N is the last name below it.
    end_ptr = 0
    for addr, kinds in sorted(end_uses.items()):
        i = bisect.bisect_left(anchors, addr)
        if i == 0 or i >= len(anchors) or anchors[i] != addr:
            continue  # not a name's start: inside an object, which moves whole
        prev = anchors[i - 1]
        pp, np_ = piece(prev)
        pn, nn = piece(addr)
        fs = set().union(*kinds.values())
        why.setdefault(prev, set()).add("end-ptr")
        if pp != pn or piece(addr - 1)[0] != pn:
            end_ptr += 1
            hits.setdefault((prev, np_, addr, nn, "end-ptr[" + ",".join(sorted(kinds)) + "]", 0), set()).update(fs)
    for (base, nb, tgt, nt, kind, width), fs in sorted(hits.items()):
        print(f"{base:08x} ({nb or 'in place'}) -> {tgt:08x} ({nt or 'in place'})\t{kind}{width or ''}\t"
              + " ".join(sorted(fs)[:6]) + (f" +{len(fs) - 6}" if len(fs) > 6 else ""))
    if a.out:
        names = sorted({n for (_b, nb, _t, nt, _k, _w) in hits for n in (nb, nt) if n})
        a.out.write_text("".join(n + "\n" for n in names))
    if a.explain:
        a.explain.write_text("".join(x + "\n" for x in explain))
    if a.all:
        for base, fs in sorted(idx.items()):
            print(f"{base:08x} ({piece(base)[1]}) indexed\t" + " ".join(sorted(fs)[:6]))
    if a.debug:
        for name, callee, j, v in sites:
            if v == a.debug:
                print(f"debug: {name} passes {v:08x} as arg{j} to {fname.get(callee, hex(callee))}: "
                      f"reach {reach.get(callee, {}).get(j)}")
    print(f"# {len(stored)} addresses are stored to memory", file=sys.stderr)
    if argidx:
        print(f"# {len(arg_ub)} functions index by an argument, {sum(1 for f_ in arg_ub if direct[f_])} called "
              f"directly only (arg-bound); not: " + ", ".join(f"{v_} {k_}" for k_, v_ in sorted(arg_stats.items())),
              file=sys.stderr)
    print(f"# {dma_chain} DMA chain arguments are bounded by their parsed tags (dma-chain)", file=sys.stderr)
    print(f"# {list_arg} list arguments are bounded by a list literal's count (list-arg)", file=sys.stderr)
    print(f"# {str_arg} string arguments end at their NUL inside their object (str-arg)", file=sys.stderr)
    print(f"# {dead_arg} indexed arguments are dropped: the callee never reads the register (dead-arg)",
          file=sys.stderr)
    print(f"# {len(uncached)} addresses have their uncached alias built", file=sys.stderr)
    print(f"# {len(end_uses)} addresses are compared or subtracted as an end, {end_ptr} tie two pieces (end-ptr)",
          file=sys.stderr)
    print(f"# {len(bounded)} indexed bases have bounded accesses that end before the next name",
          file=sys.stderr)
    print(f"# {len(reach)} functions reach from their arguments, {len(sites)} call sites pass an address",
          file=sys.stderr)
    print(f"# {len(pcs)} floated variables, {len(hits)} cross-piece accesses, {len(idx)} indexed floated bases",
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
