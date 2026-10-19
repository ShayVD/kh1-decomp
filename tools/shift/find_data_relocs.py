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
through (`jalr`/`jr`: call tables) or dereferences (pointer tables/variables).
Jump tables of the hand-written asm and unmatched functions come from
kh1tool's analyze_asm + asm_export's extra pattern (as the symbolic export
finds them)."""
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
    # tier 2
    "func-s16": "function start, but the neighbourhood looks like s16 data (kept: starts are rare by chance)",
    "dref": "target is an address code builds with %hi/%lo (or a D_ name src references), not s16/colour-like",
    "ptab": "word in a table/variable code loads and dereferences or calls through",
    "dma": "address word of a DMA tag (REF/REFS/REFE/NEXT/CALL id in the word before, qword aligned)",
    "str": "points at the start of a NUL-terminated string",
    "stride": "same offset as accepted pointers in a repeating record (stride 8-64, both sides)",
    "bref": "bss target code builds with %hi/%lo",
    # tier 3
    "dptr-run": "aligned data target next to other pointer words with different values or accepted pointers",
    "bptr-run": "aligned bss target next to other pointer words with different values or accepted pointers",
    "dptr": "aligned data target, isolated, no rule against it (the real ambiguous remainder)",
    "bptr": "aligned bss target, isolated, no rule against it (the real ambiguous remainder)",
    "near": "aligned target within 64 KiB of the word itself (self-relative records, lists), not s16-like",
    "mirror": "0x20000000/0x30000000 mirror of a 16-aligned data/bss address code builds with %hi/%lo",
    "into-table": "inside an asm/unmatched function, next to other words into it, distinct, not s16-like",
    # rejected (tier x)
    "s16": "s16-pair test: both halves small (|s16|<0x1000) or the value repeats >=8 times, with s16 pairs or colours around it",
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
TIER_OF = {"ftab": "1", "calltab": "1", "func": "1", "jtbl": "1",
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
        for k, w in enumerate(words):
            a = f.addr + 4 * k
            if a in labels:
                st.clear()
            if a == clobber_at:
                for r in [r for r in st if r in CALLER_SAVED]:
                    del st[r]
            o = mips.op(w)
            rs, rt, rd = mips.rs(w), mips.rt(w), mips.rd(w)
            if o in (0x03,) or (o == 0 and mips.funct(w) == 0x09):
                clobber_at = a + 8
            if o == 0 and mips.funct(w) in (0x08, 0x09) and w != mips.JR_RA:  # jr/jalr
                s = st.get(rs)
                if s and s[0] == "ld":
                    (cf.call_tables if s[2] else cf.call_words).add(s[1])
            if o == mips.OP_LUI:
                st[rt] = ("hi", (w & 0xFFFF) << 16)
                continue
            s = st.get(rs)
            new = None
            mem = o in mips.OP_LOADS or o in mips.OP_STORES or o in mips.OP_VU_MEM or o in (mips.OP_LQ, mips.OP_SQ)
            if s and s[0] == "ld" and mem:
                (cf.ptr_tables if s[2] else cf.ptr_words).add(s[1])
            elif s and o in (0x09, 0x0D) and s[0] in ("hi", "addr"):
                full = (s[1] + (mips.imm(w) if o == 0x09 else w & 0xFFFF)) & 0xFFFFFFFF
                if s[0] == "hi":
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


# --------------------------------------------------------------------------- main scan

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", type=Path, default=K.ROOT / "data_relocs.tsv")
    ap.add_argument("--debug", type=Path, default=None,
                    help="also write a per-word table with values (under out/ only: holds game bytes)")
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
        if k == "text":
            if x in cf.jtbl_entries:
                decided[x] = "jtbl"
            elif v in startset:
                nb = neighbours(x)
                if x in typed_call:
                    decided[x] = "calltab"
                elif run_of.get(x, 1) >= 3:
                    decided[x] = "ftab"
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
        if k == "data" and x % 16 == 4:
            tag = bl.w(x - 4)
            if tag is not None and (tag >> 28) & 7 in (0, 2, 3, 4, 5) and (tag >> 16) & 0x3FF == 0 \
                    and (tag & 0x8C000000) == 0 and v % 16 == 0 and (tag >> 28) != 0:
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

    def accepted(y: int) -> bool:
        r = decided.get(y)
        return r is not None and r != "?" and r in TIER_OF

    # rules for the ambiguous words
    repeats = collections.Counter(cands[x][0] for x, r in decided.items() if r == "?")
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
        if any(w in VU_NOPS for w in nb4):
            decided[x] = "vucode"
        elif ascii_word(v) and sum(1 for w in nb_np if ascii_word(w)) >= 2:
            decided[x] = "ascii"
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

    # rows
    rows = []
    counts = collections.Counter()
    for x in sorted(decided):
        r = decided[x]
        v, m, k = cands[x]
        tier = TIER_OF.get(r, "x")
        counts[(tier, r)] += 1
        if tier == "x":
            if r != "unaligned":  # noise (unaligned targets): counted, not listed (keeps the file small)
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
             "# offset: from D_BLOB = 0x00272c70; unaligned-target noise is counted by the tool, not listed.",
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
    print(f"  -> {a.out.name}: {len(rows)} rows")
    return 0


if __name__ == "__main__":
    sys.exit(main())
