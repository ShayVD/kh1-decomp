#!/usr/bin/env python3
"""Find the pointers inside the data blob and write data_relocs.tsv
(docs/shiftable-plan.md, step 5; section "Session 13: data relocations").

  python3 -I tools/shift/find_data_relocs.py [--out data_relocs.tsv] [--debug out/shift/data_relocs.debug.tsv]

Needs `make` (layout, placements, compiled rodata) and the user's ELF. It
scans every aligned word of the file-backed data 0x272C70-0x494050, minus the
compiled .rodata blocks (out/gen/rodata.tsv: they carry their own
relocations), and classifies the words whose value points into the image
0x00100000-0x00675018 (optionally through a 0x20000000/0x30000000 mirror).

data_relocs.tsv (committed; addresses and names only, never game bytes):

  offset  type  symbol  addend  tier  reason

  offset   word offset in the blob (from D_BLOB = 0x272C70)
  type     R_MIPS_32, or R_MIPS_32+0x20000000 / +0x30000000 for a mirrored pointer
  symbol   the function containing the target (layout name), D_BLOB (file-backed data)
           or D_BSS (.bss; negative addends for 0x494050-0x494080)
  tier     1 certain, 2 strong evidence, 3 ambiguous but accepted by a rule,
           x a candidate a rule rejected (symbol/addend are `-`: no value is recorded)
  reason   short code, see REASONS

The shift link (tools/shift/shift_ld.py --data-relocs, --reloc-tier N) emits
`.word sym+addend` for every row with tier <= N.

Code analysis (fast, own tracker over the original code, every function):
%hi/%lo addresses code builds (`coderef`), words code loads and then calls
through (`jalr`/`jr`: call tables) or dereferences (pointer tables/variables),
and the data addresses passed to a few typed calls (WATCHED_CALLS): DMA chain
heads (sceDmaSend, D<n>_TADR stores), relocatable resource files (fixup
func_001763f0), byte streams (script VM, message parser) and the code the
libkernel patches copy into kernel RAM. Jump tables of the hand-written asm and
unmatched functions come from kh1tool's analyze_asm + asm_export's extra pattern
(as the symbolic export finds them).

Typed evidence beyond the rules: DMA chains walked from their kicks and tag
tables code references (payloads rejected); `extern` declarations in src/
(pointer arrays settle tier-3 words; a contradiction with a rule is reported);
tools/shift/data_reloc_overrides.tsv, reviewed decisions with their reason
(docs/shiftable-plan.md, "Session 13: reloc review"). Unaligned-target noise
and the words of resource files are counted, not listed."""
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
from elf32 import Elf  # noqa: E402

DATA_LO, DATA_HI = 0x00272C70, 0x00494050
BSS_LO, IMAGE_END = 0x00494080, 0x00675018
TEXT_LO = 0x00100000
MIRRORS = (0x20000000, 0x30000000)

REASONS = {
    # tier 1
    "ftab": "function start in a run of >=3 function-start words (callback/class/vtable tables)",
    "calltab": "function start in a table code loads and calls through (jalr/jr)",
    "func": "lone function start",
    "jtbl": "jump-table entry of an asm/unmatched function (analyze_asm)",
    "dma-chain": "ADDR word of a DMA tag on a chain code kicks (sceDmaSend / D_TADR store), walked tag by tag",
    # tier 2
    "func-s16": "function start, but the neighbourhood looks like s16 data (kept: starts are rare by chance)",
    "dref": "target is an address code builds with %hi/%lo (or a D_ name src references), not s16/colour-like",
    "ptab": "word in a table/variable code loads and dereferences or calls through",
    "dma": "ADDR word of a valid REF/REFS/REFE/NEXT/CALL tag (payload VIF/GIF, in range) in a tag table code references (templates code copies into packets)",
    "str": "points at the start of a NUL-terminated string",
    "stride": "same offset as accepted pointers in a repeating record (stride 8-64, both sides)",
    "bref": "bss target code builds with %hi/%lo",
    "typed": "tier-3 word inside a pointer variable/array a src extern declares (T *D_x, T *D_x[n], (*D_x[n])())",
    "override": "accepted by a reviewed entry of tools/shift/data_reloc_overrides.tsv (typed evidence, reason there)",
    # tier 3
    "dptr-run": "aligned data target next to other pointer words with different values or accepted pointers",
    "bptr-run": "aligned bss target next to other pointer words with different values or accepted pointers",
    "dptr": "aligned data target, isolated, no rule against it (the real ambiguous remainder)",
    "bptr": "aligned bss target, isolated, no rule against it (the real ambiguous remainder)",
    "near": "aligned target within 64 KiB of the word itself (self-relative records, lists), not s16-like",
    "mirror": "0x20000000/0x30000000 mirror of a 16-aligned data/bss address code builds with %hi/%lo",
    "into-table": "inside an asm/unmatched function, next to other words into it, distinct, not s16-like",
    # rejected (tier x)
    "typed-x": "tier-3 word inside an s16/u16/f32 array (explicit size) a src extern declares",
    "override-x": "rejected by a reviewed entry of tools/shift/data_reloc_overrides.tsv (typed evidence, reason there)",
    "s16": "s16-pair test: both halves small (|s16|<0x1000) or the value repeats >=8 times, with s16 pairs or colours around it",
    "payload": "inside what a DMA tag (dma/dma-chain) transfers: VIF codes, GIF packets, VU microcode and data",
    "resfile": "inside a relocatable resource file code fixes up with its own base (func_001763f0): offsets and numbers",
    "script": "ambiguous word in a byte stream code hands to the script VM / message parser (from that base to the next address code builds)",
    "spawn-tmpl": "u16 field (+0xc..+0x20) of an object spawn template {callback, 0, n, s16/u16 x, y, w, h...} (func_001f31a8's WA)",
    "gifregs": "REGS field of a GIFtag (NLOOP/FLG/NREG valid in the 8 bytes before, no register past NREG)",
    "bytes": "packed bytes around it: >= 3 of the 4 neighbours have no zero byte and are not addresses, floats or ASCII (bytecode)",
    "kcode": "EE code the libkernel patches copy into kernel RAM (0x80074000...) and run there: self-contained, no image address",
    "vucode": "VU microcode around it (VU nop words within 4 words)",
    "ascii": "the word and its neighbours are ASCII text",
    "colour": "colour test: the value is 0x00BBGGRR with two equal channels among such words, or RGBA (alpha 0x80/0xFF/0x40/0x7F) words next to it and no pointer run",
    "float": "float test: the words around it are plausible floats, no pointer run",
    "into-func": "inside a function, not a known jump table: a number (crt0's 0x1001xx values and the like)",
    "unaligned": "data/bss target not 4-aligned and not a string start",
    "mirror-x": "mirror of an address code never builds (in practice ctype/ASCII tables, 0x20202020)",
    "mipscode": "MIPS instructions around it (code carried as data, e.g. 0x46A000-0x46C000)",
    "smallint": "neighbours are small integers/ids and no stride evidence (counter, size, flags)",
}
TIER_OF = {"override": "2", "typed": "2", "ftab": "1", "calltab": "1", "func": "1", "jtbl": "1", "dma-chain": "1",
           "func-s16": "2", "near": "3", "dref": "2", "ptab": "2", "dma": "2", "str": "2", "stride": "2", "bref": "2",
           "dptr-run": "3", "bptr-run": "3", "dptr": "3", "bptr": "3", "mirror": "3", "into-table": "3"}

CALLER_SAVED = {r for r in range(1, 32) if not (16 <= r <= 23 or r in (28, 29, 30))}


# --------------------------------------------------------------------------- code analysis

class CodeFacts:
    def __init__(self):
        self.refs: set[int] = set()          # %hi/%lo full addresses
        self.call_words: set[int] = set()    # address of a word code loads and calls through
        self.call_tables: set[int] = set()   # indexed: base of a table of called words
        self.ptr_words: set[int] = set()     # word code loads and dereferences
        self.ptr_tables: set[int] = set()    # indexed table of dereferenced words
        self.jtbl_entries: dict[int, int] = {}  # word address -> owning function start
        self.dma_heads: dict[int, set[int]] = collections.defaultdict(set)  # chain head -> kicking functions
        self.res_bases: dict[int, set[int]] = collections.defaultdict(set)  # relocatable resource -> fixing functions
        self.kcode: dict[int, int] = {}  # code copied into kernel RAM: source -> size
        self.scripts: dict[int, set[int]] = collections.defaultdict(set)  # byte streams -> reading functions


# Calls whose arguments type a data address (function -> (kind, address register, size register)):
# - "dma": sceDmaSend(ch, chain) = func_00266f38 (a1, chain mode CHCR 0x105) and the game's wrapper
#   func_00106b18(chain) (VIF1); direct D<n>_TADR stores (0x1000x030) are handled apart;
# - "res": relocatable resource files embedded in the data (model/motion sets): func_001763f0(base)
#   adds base to the offsets inside (`*p += base`), so the file holds offsets and numbers, never
#   absolute EE pointers;
# - "kcode": the libkernel patches copy code into kernel RAM with a temporary syscall
#   (func_0025f610 / func_0025fa30 / func_002608d0 (dest, src, size), e.g. 0x46AF18 -> 0x80074000);
#   that code runs there, never in place;
# - "script": byte streams: the script VM (func_0010ef70(vm, code, 0), func_001c4198(code, n)), the
#   message parser func_001c2d20(text, ...) and the message base func_001efb18(text, u16 offsets).
WATCHED_CALLS = {0x0010EF70: ("script", 5, None), 0x001C4198: ("script", 4, None),
                 0x001C2D20: ("script", 4, None), 0x001EFB18: ("script", 4, None),
                 0x00266F38: ("dma", 5, None), 0x00106B18: ("dma", 4, None), 0x001763F0: ("res", 4, None),
                 0x0025F610: ("kcode", 5, 6), 0x0025FA30: ("kcode", 5, 6), 0x002608D0: ("kcode", 5, 6)}
DMA_TADR = {0x10008030, 0x10009030, 0x1000A030, 0x1000B030, 0x1000B430, 0x1000C030, 0x1000C430,
            0x1000C830, 0x1000D030, 0x1000D430}


def scan_code(image: bytes, load: int, layout: list[K.Func]) -> CodeFacts:
    """One linear pass per function. Register state: ('hi', upper) after lui,
    ('addr', A) after lui+addiu, ('hix'/'addrx', ...) after adding an index,
    ('ld', A, indexed) for a word loaded from address A."""
    cf = CodeFacts()
    for f in layout:
        n = (f.end - f.addr) // 4
        words = struct.unpack_from(f"<{n}I", image, f.addr - load)
        labels = set()
        for k, w in enumerate(words):
            t = mips.Insn(f.addr + 4 * k, w).branch_target
            if t is not None:
                labels.add(t)
        st: dict[int, tuple] = {}
        clobber_at = None
        call = None  # (WATCHED_CALLS entry, address after the delay slot)

        def watched(c):
            kind_, areg, sreg = c
            s = st.get(areg)
            if not (s and s[0] == "addr"):
                return
            if kind_ == "dma":
                cf.dma_heads[s[1]].add(f.addr)
            elif kind_ == "res":
                cf.res_bases[s[1]].add(f.addr)
            elif kind_ == "script":
                cf.scripts[s[1]].add(f.addr)
            elif (n_ := st.get(sreg)) and n_[0] == "const":
                cf.kcode[s[1]] = n_[1]

        for k, w in enumerate(words):
            a = f.addr + 4 * k
            if call and a == call[1]:
                watched(call[0])
                call = None
            if a in labels:
                st.clear()
            if a == clobber_at:
                for r in [r for r in st if r in CALLER_SAVED]:
                    del st[r]
            o = mips.op(w)
            rs, rt, rd = mips.rs(w), mips.rt(w), mips.rd(w)
            if o in (0x03,) or (o == 0 and mips.funct(w) == 0x09):
                clobber_at = a + 8
            if o in (0x02, 0x03):  # jal, or j as a tail call
                tgt = (a + 4) & 0xF0000000 | (w & 0x3FFFFFF) << 2
                if tgt in WATCHED_CALLS:
                    call = (WATCHED_CALLS[tgt], a + 8)
            if o == 0x2B and (s_ := st.get(rs)):  # sw to a DMA channel's TADR
                if s_[0] in ("hi", "addr", "io") and (s_[1] + mips.imm(w)) & 0xFFFFFFFF in DMA_TADR:
                    v_ = st.get(rt)
                    if v_ and v_[0] == "addr":
                        cf.dma_heads[v_[1]].add(f.addr)
            if o == 0 and mips.funct(w) in (0x08, 0x09) and w != mips.JR_RA:  # jr/jalr
                s = st.get(rs)
                if s and s[0] == "ld":
                    (cf.call_tables if s[2] else cf.call_words).add(s[1])
            if o == mips.OP_LUI:
                st[rt] = ("hi", (w & 0xFFFF) << 16)
                continue
            if o in (0x09, 0x0D) and rs == 0:  # li: a small constant (sizes of watched calls)
                st[rt] = ("const", mips.imm(w) if o == 0x09 else w & 0xFFFF)
                continue
            s = st.get(rs)
            new = None
            mem = o in mips.OP_LOADS or o in mips.OP_STORES or o in mips.OP_VU_MEM or o in (mips.OP_LQ, mips.OP_SQ)
            if s and s[0] == "ld" and mem:
                (cf.ptr_tables if s[2] else cf.ptr_words).add(s[1])
            elif s and o in (0x09, 0x0D) and s[0] in ("hi", "addr"):
                full = (s[1] + (mips.imm(w) if o == 0x09 else w & 0xFFFF)) & 0xFFFFFFFF
                if s[0] == "hi":
                    if full in DMA_TADR:
                        st[rt] = ("io", full)  # DMA register (lui/ori): only for the TADR test
                        continue
                    if o == 0x0D or not K.RAM_START <= full < K.RAM_END:
                        full = None  # gcc never builds an address with ori: a constant
                    else:
                        cf.refs.add(full)
                if full is not None:
                    new = ("addr", full)
            elif s and mem and s[0] in ("hi", "hix", "addr", "addrx"):
                full = (s[1] + mips.imm(w)) & 0xFFFFFFFF
                if s[0] in ("hi", "hix"):
                    cf.refs.add(full)
                if o == 0x23:  # lw: remember what was loaded
                    st[rt] = ("ld", full, s[0] in ("hix", "addrx"))
                    continue
            if o == 0 and mips.funct(w) in (0x21, 0x2D, 0x25) and 0 in (rs, rt):
                x = st.get(rs or rt)  # move rd, rs (addu/daddu/or with $zero): a copy
                if x and x[0] == "addr":
                    st[rd] = x
                else:
                    st.pop(rd, None)
                continue
            if o == 0 and mips.funct(w) == 0x24:  # and rd, rs, rt: an address masked (& 0x0FFFFFFF for TADR)
                a1, a2 = st.get(rs), st.get(rt)
                x = a1 if a1 and a1[0] == "addr" and not a2 else a2 if a2 and a2[0] == "addr" and not a1 else None
                if x:
                    st[rd] = x
                else:
                    st.pop(rd, None)
                continue
            if o == 0 and mips.funct(w) in (0x21, 0x2D):  # addu/daddu: base + index
                a1, a2 = st.get(rs), st.get(rt)
                for x in (a1, a2):
                    if x and x[0] in ("hi", "addr"):
                        new = ("hix" if x[0] == "hi" else "addrx", x[1])
                        st[rd] = new
                        break
                else:
                    st.pop(rd, None)
                continue
            if new is not None and o in (0x09, 0x0D):
                st[rt] = new
                continue
            # anything else written is forgotten
            if o in (0x11, 0x12):
                if rs in (0, 1, 2):
                    st.pop(rt, None)
            elif o in K.GPR_RT_WRITERS:
                st.pop(rt, None)
            elif o in (mips.OP_MMI, 0):
                st.pop(rd, None)
            elif o == 0x03:
                st.pop(31, None)
        if call:  # a tail call (j) whose delay slot ends the function
            watched(call[0])
    return cf


def asm_jump_tables(funcs: list[K.Func], cf: CodeFacts) -> int:
    """Jump tables of hand-written asm / unmatched functions, found exactly
    like the symbolic export does (kh1tool analyze_asm + asm_export.more_jtbls)."""
    import asm_export as AE
    cfg = K.load_config()
    n = 0
    for f in funcs:
        an = K.analyze_asm(cfg, f)
        AE.more_jtbls(an, f, AE.flow_pairs(an, f, [])[1])
        for base, entries in an.jtbls.items():
            for i in range(len(entries)):
                cf.jtbl_entries[base + 4 * i] = f.addr
                n += 1
    return n


# --------------------------------------------------------------------------- data tests

def fbits_plausible(w: int) -> bool:
    """A float a game table would hold: 0, or exponent 2^-20..2^20."""
    if w in (0, 0x80000000):
        return True
    e = (w >> 23) & 0xFF
    return 107 <= e <= 147


def s16_small(w: int) -> bool:
    lo, hi = w & 0xFFFF, w >> 16
    lo = lo - 0x10000 if lo & 0x8000 else lo
    hi = hi - 0x10000 if hi & 0x8000 else hi
    return abs(lo) < 0x1000 and abs(hi) < 0x1000


VU_NOPS = (0x8000033C, 0x000002FF)  # VU lower / upper nop: microcode around


def ascii_word(w: int) -> bool:
    bs = w.to_bytes(4, "little")
    return all(32 <= c < 127 or c == 0 for c in bs) and sum(1 for c in bs if c) >= 2


def is_rgb0(w: int) -> bool:
    """0x00BBGGRR with three equal-ish channels (grey/colour constants)."""
    r, g, b = w & 0xFF, (w >> 8) & 0xFF, (w >> 16) & 0xFF
    return w >> 24 == 0 and r and g and b and (r == g or g == b or r == b)


MIPS_OPS = {0x03, 0x04, 0x05, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B,
            0x37, 0x3F, 0x1E, 0x1F}
MIPS_SPECIAL = {0x08, 0x09, 0x21, 0x23, 0x24, 0x25, 0x2A, 0x2B, 0x2D, 0x2F}


def mips_like(w: int) -> bool:
    """A common EE instruction (embedded code: IOP/EE code carried as data)."""
    o = w >> 26
    if o == 0:
        f = w & 0x3F
        if f in MIPS_SPECIAL and (w >> 6) & 0x1F == 0:
            return True
        return f == 0 and w != 0 and (w >> 21) & 0x1F == 0  # sll
    return o in MIPS_OPS and w & 0xFFFF0000 not in (0, 0xFFFF0000)


def is_colour(w: int) -> bool:
    return (w >> 24) in (0x80, 0xFF, 0x40, 0x7F) and (w & 0xFFFFFF) != 0


def noisy(w: int) -> bool:
    """A word of packed bytes (bytecode, compressed data): no zero byte, not 0xFFFFFFFF, not an
    image address, not a plausible float, not ASCII."""
    return all(w.to_bytes(4, "little")) and w != 0xFFFFFFFF and not TEXT_LO <= w <= IMAGE_END \
        and not fbits_plausible(w) and not ascii_word(w)


def gif_regs(lo: int, hi: int, v: int, nxt: int) -> bool:
    """v is the REGS field (bits 64-95) of the GIFtag (lo, hi): NLOOP > 0, bits 16-45 zero,
    FLG PACKED/REGLIST, and no register nibble past NREG."""
    if lo & 0xFFFF0000 or not lo & 0x7FFF or hi & 0x3FFF or (hi >> 26) & 3 > 1 or not hi >> 28:
        return False
    nreg = hi >> 28  # NREG 0 (16 registers) is legal but too weak as evidence
    return (nreg >= 8 or v >> (4 * nreg) == 0) and (nreg > 8 or nxt == 0)


class Blob:
    def __init__(self, image: bytes, load: int):
        self.image, self.load = image, load

    def w(self, a: int) -> int | None:
        o = a - self.load
        if a < DATA_LO or a + 4 > DATA_HI or o < 0:
            return None
        return struct.unpack_from("<I", self.image, o)[0]

    def b(self, a: int) -> int:
        return self.image[a - self.load]


def string_start(bl: Blob, v: int) -> bool:
    if not DATA_LO < v < DATA_HI - 2:
        return False
    if bl.b(v - 1) != 0:
        return False
    n = 0
    a = v
    while a < DATA_HI and n < 256:
        c = bl.b(a)
        if c == 0:
            break
        if not (32 <= c < 127 or c in (9, 10, 13) or c >= 0x80):
            return False
        n += 1
        a += 1
    return n >= 2 and a < DATA_HI and bl.b(a) == 0


# --------------------------------------------------------------------------- DMA packets

VIF_CMDS = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x10, 0x11, 0x13, 0x14, 0x15, 0x17, 0x20, 0x30, 0x31,
            0x4A, 0x50, 0x51}
DMA_TAG_NAMES = "REFE CNT NEXT REF REFS CALL RET END".split()


def vif_code(c: int) -> bool:
    cmd = (c >> 24) & 0x7F
    return cmd in VIF_CMDS or 0x60 <= cmd <= 0x7F  # UNPACK


def tag_bits_ok(t: int) -> bool:
    """A DMAtag's low word: qwc, bits 16-25 zero, PCE 0, IRQ 0 (none in this image sets them)."""
    return (t >> 16) & 0x3FF == 0 and (t >> 26) & 3 == 0 and t >> 31 == 0


def tag_shape(bl: Blob, t: int) -> bool:
    """The qword at t is a REF/REFS/REFE/NEXT/CALL tag whose ADDR (t+4) is a 16-aligned data/bss address:
    tag bits valid; the upper 64 bits (VIF codes when TTE is set) zero or VIF codes; for REF*,
    ADDR + 16*qwc inside the image and the payload's first qword two VIF codes or a GIFtag;
    for NEXT/CALL, a valid tag at ADDR."""
    tag, v = bl.w(t), bl.w(t + 4)
    if tag is None or v is None or t % 16 or not tag_bits_ok(tag) or v % 16 or not DATA_LO <= v <= IMAGE_END:
        return False
    idn, qwc = (tag >> 28) & 7, tag & 0xFFFF
    if idn not in (0, 2, 3, 4, 5) or tag == 0 and v == 0:
        return False
    if not all(bl.w(t + k) == 0 or vif_code(bl.w(t + k) or 0) for k in (8, 12)):
        return False
    if idn in (0, 3, 4):
        if v + 16 * qwc > IMAGE_END:
            return False
        if qwc and v < DATA_HI:
            if v + 16 * qwc > DATA_HI:
                return False
            a, b = bl.w(v), bl.w(v + 4)
            gif = a & 0x7FFF and (b >> 26) & 3 != 3  # GIFtag: NLOOP > 0, FLG != 3
            if not (vif_code(a) and vif_code(b)) and not gif:
                return False
        return idn != 0 or qwc > 0  # REFE with qwc 0: (0, pointer) records are not packets
    nt = bl.w(v) if v < DATA_HI else 0
    return nt is not None and tag_bits_ok(nt)


def walk_chains(bl: Blob, heads) -> tuple[set[int], list[str]]:
    """Follow every source chain (Dn_CHCR MOD=chain) from a kicked head inside the blob.
    Returns the tag addresses visited and one line per head."""
    tags, log = set(), []
    for h in sorted(heads):
        if not DATA_LO <= h < DATA_HI:
            continue
        a, stack, path, end = h, [], [], "left the blob (runtime buffer)"
        for _ in range(4096):
            if not DATA_LO <= a < DATA_HI or a % 16:
                break
            t = bl.w(a)
            if not tag_bits_ok(t):
                end = f"invalid tag at 0x{a:08x} (ADDR patched by code)"
                break
            idn, qwc = (t >> 28) & 7, t & 0xFFFF
            tags.add(a)
            path.append(DMA_TAG_NAMES[idn])
            if idn == 0:
                end = "REFE"
                break
            if idn == 1:
                a += 16 + 16 * qwc
            elif idn == 2:
                a = bl.w(a + 4)
            elif idn in (3, 4):
                a += 16
            elif idn == 5:
                stack.append(a + 16 + 16 * qwc)
                a = bl.w(a + 4)
            elif idn == 6 and stack:
                a = stack.pop()
            else:
                end = DMA_TAG_NAMES[idn]
                break
        c = collections.Counter(path)
        log.append(f"0x{h:08x}: {len(path)} tags ({', '.join(f'{k} {n}' for k, n in c.items())}), ends: {end}")
    return tags, log


# --------------------------------------------------------------------------- src declarations

DECL = re.compile(r"\bextern\s+(?:const\s+|volatile\s+|struct\s+|unsigned\s+|signed\s+)*([A-Za-z_]\w*)\s*(\**)\s*"
                  r"(?:const\s*)?(\(\s*\*\s*)?(D_[0-9A-Fa-f]{8})\b\s*((?:\[[^\]]*\]\s*)*)")
# u8/char arrays are left out: the code declares opaque blobs (DMA packets, files) as u8 D_x[]
NUM_SIZE = {"s16": 2, "u16": 2, "short": 2, "f32": 4, "float": 4}


def src_types(refs_sorted: list[int]) -> list[tuple[int, int, str, str]]:
    """Typed ranges from the `extern` declarations in src/ and include/: (lo, hi, 'ptr'|'num', name).
    'ptr': pointer variables and arrays of pointers (incl. function pointers); 'num': s16/u16/f32
    arrays with explicit dimensions. Extent: the declared dimensions, or for a pointer array `[]` up
    to the next address code builds. A symbol declared both ways somewhere is left out."""
    seen: dict[int, set[tuple[str, int | None]]] = collections.defaultdict(set)
    for path in list((K.ROOT / "src").rglob("*.c")) + list((K.ROOT / "include").rglob("*.h")):
        for m in DECL.finditer(path.read_text(errors="replace")):
            base, stars, fp, name, dims = m.groups()
            a = int(name[2:], 16)
            if not DATA_LO <= a < DATA_HI:
                continue
            if fp or stars:
                kind_, size = "ptr", 4
            elif base in NUM_SIZE:
                kind_, size = "num", NUM_SIZE[base]
            else:
                continue
            n = 1
            for d in re.findall(r"\[([^\]]*)\]", dims):
                d = d.strip()
                n = n * int(d, 0) if n is not None and re.fullmatch(r"0x[0-9a-fA-F]+|\d+", d) else None
            seen[a].add((kind_, None if n is None else n * size))
    out = []
    for a, ds in seen.items():
        kinds = {k for k, _ in ds}
        if len(kinds) != 1:
            continue
        kind_ = kinds.pop()
        sizes = [z for _, z in ds if z is not None]
        if kind_ == "num" and not sizes:
            continue
        if sizes:
            hi = a + max(sizes)
        else:
            j = bisect.bisect_right(refs_sorted, a)
            hi = refs_sorted[j] if j < len(refs_sorted) else DATA_HI
        out.append((a, min(hi, DATA_HI), kind_, f"D_{a:08X}"))
    return sorted(out)


# --------------------------------------------------------------------------- main scan

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", type=Path, default=K.ROOT / "data_relocs.tsv")
    ap.add_argument("--debug", type=Path, default=None,
                    help="also write a per-word table with values (under out/ only: holds game bytes)")
    ap.add_argument("--verbose", action="store_true", help="print each walked DMA chain")
    ap.add_argument("--overrides", type=Path, default=Path(__file__).with_name("data_reloc_overrides.tsv"),
                    help="reviewed decisions: offset, end (or -), accept|reject, reason")
    a = ap.parse_args()
    if a.debug and K.OUT.resolve() not in a.debug.resolve().parents:
        sys.exit("error: --debug output holds game bytes and must be under out/")
    cfg = K.load_config()
    orig = K.require_orig(cfg)
    seg = next(s for s in orig.segments if s.type == 1)
    load = seg.vaddr
    image = orig.data[seg.offset: seg.offset + seg.filesz]
    layout = K.load_layout()
    starts = [f.addr for f in layout]
    startset = set(starts)
    text_hi = layout[-1].end

    # holes: compiled rodata (carry their own relocations)
    holes = []
    for addr, sec, obj in K.load_rodata_placements():
        e = Elf.load(K.ROOT / obj)
        holes.append((addr, addr + e.section(sec).size))
    holes.sort()
    hole_starts = [h[0] for h in holes]

    def in_hole(x: int) -> bool:
        i = bisect.bisect_right(hole_starts, x) - 1
        return i >= 0 and x < holes[i][1]

    cf = scan_code(image, load, layout)
    # D_ names src references (out/gen/symbols.ld PROVIDEs)
    symld = K.GEN / "symbols.ld"
    if symld.exists():
        for m in re.finditer(r"PROVIDE\(D_[0-9A-Fa-f]{8} = 0x([0-9a-f]{8})\)", symld.read_text()):
            cf.refs.add(int(m.group(1), 16))
    # asm / unmatched functions: placements from .s sources + layout functions nothing places
    placed = {ad: src for ad, _s, _o, src in K.load_placements()}
    asm_funcs = [f for f in layout if f.addr not in placed or placed[f.addr].endswith(".s")]
    asm_funcs = [f for f in asm_funcs if not placed.get(f.addr, "").endswith("syscall.s")]
    n_jt = asm_jump_tables(asm_funcs, cf)
    asm_addrs = {f.addr for f in asm_funcs}

    bl = Blob(image, load)


    def func_of(v: int) -> K.Func | None:
        i = bisect.bisect_right(starts, v) - 1
        return layout[i] if i >= 0 and v < max(layout[i].end, layout[i].addr + 4) else None

    def kind(v: int) -> str | None:
        if TEXT_LO <= v < text_hi:
            return "text"
        if DATA_LO <= v < DATA_HI:
            return "data"
        if DATA_HI <= v <= IMAGE_END:
            return "bss"
        return None

    # table typing: extend typed bases over contiguous candidate words
    typed_call, typed_ptr = set(), set()
    for bases, out in ((cf.call_tables, typed_call), (cf.ptr_tables, typed_ptr)):
        for b in bases:
            x = b
            while DATA_LO <= x < DATA_HI and not in_hole(x):
                v = bl.w(x)
                if v is None or not (v == 0 or kind(v)):
                    break
                out.add(x)
                x += 4
    typed_call |= {x for x in cf.call_words}
    typed_ptr |= {x for x in cf.ptr_words}

    # pass 1: candidates
    cands: dict[int, tuple[int, int, str]] = {}  # word addr -> (value, mirror, kind)
    for x in range(DATA_LO, DATA_HI, 4):
        if in_hole(x):
            continue
        v = bl.w(x)
        k = kind(v)
        if k:
            cands[x] = (v, 0, k)
            continue
        hi = v & 0xF0000000
        if hi in MIRRORS and kind(v - hi) in ("data", "bss") and (v - hi) % 16 == 0:
            cands[x] = (v - hi, hi, "mirror")

    # DMA: chains walked from the kicks, then tag-shaped qwords grouped into runs (gaps <= 0x80);
    # a run holding an address code builds is a template table code copies tags from.
    dma_walked, dma_log = walk_chains(bl, cf.dma_heads)
    dma_shape = sorted(x - 4 for x in cands if x % 16 == 4 and not in_hole(x - 4) and tag_shape(bl, x - 4))
    dma_run_ref: dict[int, bool] = {}
    refs_sorted = sorted(cf.refs)
    i = 0
    while i < len(dma_shape):
        j = i
        while j + 1 < len(dma_shape) and dma_shape[j + 1] - dma_shape[j] <= 0x80:
            j += 1
        lo, hi = dma_shape[i], dma_shape[j] + 16
        ref = bisect.bisect_left(refs_sorted, lo) < bisect.bisect_left(refs_sorted, hi)
        for t in dma_shape[i:j + 1]:
            dma_run_ref[t] = ref
        i = j + 1
    dma_shape = set(dma_shape)
    # relocatable resource files: from the base code passes to the fixup up to the next address code builds
    res_ranges = []
    for b in sorted(cf.res_bases):
        if DATA_LO <= b < DATA_HI:
            j = bisect.bisect_right(refs_sorted, b)
            res_ranges.append((b, min(refs_sorted[j] if j < len(refs_sorted) else DATA_HI, DATA_HI)))
    res_lo = [r[0] for r in res_ranges]
    script_ranges = []
    for b in sorted(cf.scripts):
        if DATA_LO <= b < DATA_HI:
            j = bisect.bisect_right(refs_sorted, b)
            script_ranges.append((b, min(refs_sorted[j] if j < len(refs_sorted) else DATA_HI, DATA_HI)))
    script_lo = [r[0] for r in script_ranges]

    def in_script(x: int) -> bool:
        i = bisect.bisect_right(script_lo, x) - 1
        return i >= 0 and x < script_ranges[i][1]

    def in_res(x: int) -> bool:
        i = bisect.bisect_right(res_lo, x) - 1
        return i >= 0 and x < res_ranges[i][1]

    def spawn_field(x: int, v: int) -> bool:
        """x is a u16-pair field (+0xc..+0x20) of an object spawn template (func_001f31a8's WA):
        {callback, 0, n < 0x100, s16 xc/xe, u16 x10/x12 (0 when set at run time), ...}."""
        if not s16_small(v):
            return False
        for d in range(0xC, 0x24, 4):
            b = x - d
            w10 = bl.w(b + 0x10) or 0
            if (bl.w(b) or 0) in startset and bl.w(b + 4) == 0 and 0 < (bl.w(b + 8) or 0) < 0x100 \
                    and (w10 == 0 or s16_small(w10) and w10 >> 16 and w10 & 0xFFFF):
                return True
        return False

    # payloads: what the tags transfer (VIF codes, GIF packets, VU microcode/data): never EE pointers
    dma_payload: set[int] = set()
    for t in dma_walked | {t for t in dma_shape if dma_run_ref[t]}:
        tag, adr = bl.w(t), bl.w(t + 4)
        idn, qwc = (tag >> 28) & 7, tag & 0xFFFF
        base = adr if idn in (0, 3, 4) else t + 16
        dma_payload.update(range(base, base + 16 * qwc, 4))

    def is_ptr_like(x: int) -> bool:
        return x in cands and cands[x][1] == 0

    decided: dict[int, str] = {}

    def neighbours(x: int, r: int = 2) -> list[int]:
        out = []
        for d in range(-r, r + 1):
            if d == 0:
                continue
            w = bl.w(x + 4 * d)
            if w is not None and not in_hole(x + 4 * d):
                out.append(w)
        return out

    # function-start runs
    run_of: dict[int, int] = {}
    xs = sorted(x for x, (v, m, k) in cands.items() if m == 0 and v in startset)
    i = 0
    while i < len(xs):
        j = i
        while j + 1 < len(xs) and xs[j + 1] - xs[j] <= 8:
            j += 1
        for x in xs[i:j + 1]:
            run_of[x] = j - i + 1
        i = j + 1

    for x, (v, m, k) in cands.items():
        if m:
            continue
        if x in dma_payload and x - 4 not in dma_walked and not (x - 4 in dma_shape and dma_run_ref[x - 4]):
            decided[x] = "payload"
            continue
        if in_res(x):
            decided[x] = "resfile"
            continue
        if any(b <= x < b + n for b, n in cf.kcode.items()):
            decided[x] = "kcode"
            continue
        if k == "text":
            if x in cf.jtbl_entries:
                decided[x] = "jtbl"
            elif v in startset:
                nb = neighbours(x)
                if x in typed_call:
                    decided[x] = "calltab"
                elif run_of.get(x, 1) >= 3:
                    decided[x] = "ftab"
                elif in_script(x):  # a lone start inside a byte stream: a script op by chance
                    decided[x] = "script"
                elif spawn_field(x, v):  # a u16 pair that equals a function start by chance
                    decided[x] = "spawn-tmpl"
                elif sum(1 for w in nb if s16_small(w) and not kind(w) and w) >= 3:
                    decided[x] = "func-s16"
                else:
                    decided[x] = "func"
            elif v % 4:
                continue  # unaligned into code: noise, not listed
            else:
                f = func_of(v)
                same = [y for y in (x - 4, x + 4) if y in cands and cands[y][1] == 0 and cands[y][2] == "text"
                        and func_of(cands[y][0]) is f and cands[y][0] not in startset]
                if f is not None and f.addr in asm_addrs and same and not s16_small(v) \
                        and len({cands[y][0] for y in same} | {v}) > 1:
                    decided[x] = "into-table"
                else:
                    decided[x] = "into-func"
            continue
        # data / bss target
        if x in cf.jtbl_entries:
            continue
        if v % 4:
            decided[x] = "str" if k == "data" and string_start(bl, v) else "unaligned"
            continue
        if x - 4 in dma_walked and (bl.w(x - 4) >> 28) & 7 in (0, 2, 3, 4, 5):
            decided[x] = "dma-chain"
            continue
        if x - 4 in dma_shape and dma_run_ref[x - 4]:  # unreferenced tag shapes prove nothing (sizes, s16)
            decided[x] = "dma"
            continue
        if v in cf.refs and not (s16_small(v) or is_rgb0(v)):
            decided[x] = "dref" if k == "data" else "bref"
            continue
        if x in typed_ptr or x in typed_call:
            decided[x] = "ptab"
            continue
        if k == "data" and string_start(bl, v):
            decided[x] = "str"
            continue
        decided[x] = "?"  # decided by the rules below

    def k_is_text(y: int) -> bool:
        return cands[y][2] == "text"

    def accepted(y: int) -> bool:
        r = decided.get(y)
        return r is not None and r != "?" and r in TIER_OF

    # rules for the ambiguous words
    # value repeats among the undecided words (and the region rejects, which held them before those rules)
    repeats = collections.Counter(cands[x][0] for x, r in decided.items() if r in ("?", "resfile", "payload"))
    for x, r in list(decided.items()):
        if r != "?":
            continue
        v, _m, k = cands[x]
        stride_hit = False
        for s in range(8, 68, 4):
            if accepted(x - s) and accepted(x + s) and cands[x - s][2] == k == cands[x + s][2]:
                stride_hit = True
                break
        if stride_hit:
            decided[x] = "stride"
            continue
        nb = neighbours(x)
        nb4 = neighbours(x, 4)
        nb_np = [w for w in nb if not kind(w)]  # neighbours that are not pointer-like
        accepted_near = any(accepted(x + d) for d in (-8, -4, 4, 8))
        ptr_run = [cands[x + d][0] for d in (-8, -4, 4, 8) if is_ptr_like(x + d)]
        distinct_run = any(u != v for u in ptr_run)
        s16v = s16_small(v)
        if in_script(x):
            decided[x] = "script"
        elif spawn_field(x, v):
            decided[x] = "spawn-tmpl"
        elif x % 16 == 8 and gif_regs(bl.w(x - 8) or 0, bl.w(x - 4) or 0, v, bl.w(x + 4) or 0):
            decided[x] = "gifregs"
        elif any(w in VU_NOPS for w in nb4):
            decided[x] = "vucode"
        elif ascii_word(v) and sum(1 for w in nb_np if ascii_word(w)) >= 2:
            decided[x] = "ascii"
        elif len(nb) == 4 and sum(1 for w in nb if noisy(w)) >= 3:
            decided[x] = "bytes"
        elif (s16v or repeats[v] >= 8) and (
                (s16v and repeats[v] >= 8) or any(is_colour(w) for w in nb)
                or sum(1 for d in (-8, -4, 4, 8) if not accepted(x + d) and (bl.w(x + d) or 0) & 0xFFFF0000
                       and s16_small(bl.w(x + d) or 0)) >= 2):
            decided[x] = "s16"
        elif sum(1 for w in nb if mips_like(w) and not s16_small(w)) >= 3:
            decided[x] = "mipscode"
        elif is_rgb0(v) and sum(1 for w in nb if is_rgb0(w) or is_colour(w)) >= 2:
            decided[x] = "colour"
        elif abs(v - x) < 0x10000:
            decided[x] = "near"
        elif not accepted_near and not distinct_run and any(is_colour(w) or is_rgb0(w) for w in nb):
            decided[x] = "colour"
        elif not accepted_near and not distinct_run and len(nb) >= 4 and all(fbits_plausible(w) for w in nb) \
                and sum(1 for w in nb if w) >= 3:
            decided[x] = "float"
        elif distinct_run or accepted_near:
            decided[x] = "dptr-run" if k == "data" else "bptr-run"
        else:
            decided[x] = "dptr" if k == "data" else "bptr"

    for x, (v, m, k) in cands.items():
        if not m:
            continue
        decided[x] = "mirror" if v in cf.refs else "mirror-x"

    # src declarations: settle the tier-3 words of typed ranges; report contradictions
    typed_ranges = src_types(refs_sorted)
    conflicts = []
    for lo, hi, kind_, name in typed_ranges:
        for x in range(lo + (-lo) % 4, hi, 4):
            r = decided.get(x)
            if r is None or cands[x][1]:
                continue
            tier = TIER_OF.get(r, "x")
            if tier == "3":
                decided[x] = "typed" if kind_ == "ptr" else "typed-x"
            elif (kind_ == "ptr") != (tier != "x") and r not in ("unaligned", "resfile", "payload", "kcode") \
                    and not (kind_ == "num" and k_is_text(x)):
                conflicts.append(f"0x{x:08x} {r} in {kind_} {name}")

    # reviewed overrides (typed evidence a rule cannot see): a reject applies to the accepted and
    # ambiguous words of its range, an accept to one candidate word
    n_ovr = collections.Counter()
    if a.overrides and a.overrides.exists():
        for ln, line in enumerate(a.overrides.read_text().splitlines(), 1):
            if not line.strip() or line.startswith("#") or line.startswith("offset\t"):
                continue
            f = line.split("\t")
            lo = DATA_LO + int(f[0], 16)
            hi = DATA_LO + int(f[1], 16) if f[1] != "-" else lo + 4
            if f[2] not in ("accept", "reject") or len(f) < 4 or not f[3].strip():
                sys.exit(f"error: {a.overrides.name}:{ln}: want offset, end, accept|reject, reason")
            hit = 0
            for x in range(lo, hi, 4):
                if x not in decided or cands[x][1]:
                    continue
                tier = TIER_OF.get(decided[x], "x")
                if f[2] == "reject" and tier != "x":
                    decided[x] = "override-x"
                    hit += 1
                elif f[2] == "accept" and (tier == "3" or tier == "x" and hi == lo + 4) and cands[x][0] % 4 == 0:
                    decided[x] = "override"
                    hit += 1
            if f[2] == "accept" and not hit:
                sys.exit(f"error: {a.overrides.name}:{ln}: accept matches no candidate word")
            n_ovr[f[2]] += hit

    # rows
    rows = []
    counts = collections.Counter()
    for x in sorted(decided):
        r = decided[x]
        v, m, k = cands[x]
        tier = TIER_OF.get(r, "x")
        counts[(tier, r)] += 1
        if tier == "x":
            if r not in ("unaligned", "resfile") and (k == "text" or m or v % 4 == 0):  # region/noise: counted, not listed
                rows.append((x, "-", "-", "-", tier, r))
            continue
        if k == "text":
            f = func_of(v)
            sym, add = f.name, v - f.addr
        elif k == "mirror" or k in ("data", "bss"):
            if DATA_LO <= v < DATA_HI:
                sym, add = "D_BLOB", v - DATA_LO
            elif v < text_hi:
                f = func_of(v)
                sym, add = (f.name, v - f.addr)
            else:
                sym, add = "D_BSS", v - BSS_LO
        typ = "R_MIPS_32" if not m else f"R_MIPS_32+0x{m:08x}"
        rows.append((x, typ, sym, add, tier, r))

    lines = ["# Generated by tools/shift/find_data_relocs.py (docs/shiftable-plan.md, step 5).",
             "# Pointers in the data blob 0x00272c70-0x00494050. Addresses and names only.",
             "# tier 1/2/3 = accepted (certain / strong / rule), x = rejected candidate (no value kept).",
             "# Reasons: " + "; ".join(f"{k}: {v}" for k, v in REASONS.items()),
             "# offset: from D_BLOB = 0x00272c70; unaligned-target noise and resfile words are counted by the tool, not listed.",
             "offset\ttype\tsymbol\taddend\ttier\treason"]
    for x, typ, sym, add, tier, r in rows:
        adds = "-" if add == "-" else (f"0x{add:x}" if add >= 0 else f"-0x{-add:x}")
        lines.append(f"{x - DATA_LO:06x}\t{typ}\t{sym}\t{adds}\t{tier}\t{r}")
    a.out.write_text("\n".join(lines) + "\n")

    if a.debug:
        a.debug.parent.mkdir(parents=True, exist_ok=True)
        with a.debug.open("w") as fh:
            fh.write("addr\tvalue\tmirror\tkind\treason\tneighbours\n")
            for x in sorted(decided):
                v, m, k = cands[x]
                nb = " ".join(f"{w:08x}" for w in neighbours(x))
                fh.write(f"{x:08x}\t{v:08x}\t{m:x}\t{k}\t{decided[x]}\t{nb}\n")

    print(f"find-data-relocs: {len(cands)} candidate words, {len(holes)} rodata holes skipped, "
          f"{n_jt} asm jump-table entries, {len(cf.refs)} code-built addresses")
    by_tier = collections.Counter()
    for (t, r), c in counts.items():
        by_tier[t] += c
    for t in ("1", "2", "3", "x"):
        detail = ", ".join(f"{r} {c}" for (tt, r), c in sorted(counts.items(), key=lambda kv: -kv[1]) if tt == t)
        print(f"  tier {t}: {by_tier[t]:5d}  ({detail})")
    print(f"  DMA: {len(cf.dma_heads)} kicked chain heads, {len(dma_log)} in the blob, {len(dma_walked)} tags walked; "
          f"{len(dma_shape)} tag-shaped qwords, {sum(1 for t in dma_shape if not dma_run_ref[t])} of them in unreferenced runs (not used)")
    print(f"  src declarations: {len(typed_ranges)} typed ranges, {len(conflicts)} contradictions (rule decisions kept)")
    if a.verbose:
        for c_ in conflicts:
            print("    " + c_)
    print(f"  overrides: {n_ovr['accept']} accepted, {n_ovr['reject']} rejected")
    print("  kernel code copied out: " + ", ".join(f"0x{b:08x}+0x{n:x}" for b, n in sorted(cf.kcode.items())))
    print(f"  byte streams: {len(script_ranges)} ranges, 0x{sum(b - a for a, b in script_ranges):x} bytes")
    print("  resource files: " + ", ".join(f"0x{a:08x}-0x{b:08x}" for a, b in res_ranges))
    if a.verbose:
        for line in dma_log:
            print("    " + line)
    print(f"  -> {a.out.name}: {len(rows)} rows")
    return 0


if __name__ == "__main__":
    sys.exit(main())
