#!/usr/bin/env python3
"""Write functions out as assembly sources (for code that was assembly, or
inline-asm blocks, in the original: VU0 macro code, MMI string routines).

  tools/asm_export.py OUT.s func_00267328 0x002675b8 ... [--header TEXT] [--symbolic]
  tools/asm_export.py --regen FILE.s [FILE.s ...] [--symbolic]

Each instruction becomes `.word 0x........` with its disassembly as a
comment: modern binutils does not take the VU0 macro mnemonics. One
`.section .text.<name>` per function (the build places functions by section,
docs/workflow.md). Names come from functions.tsv.

Plain mode bakes absolute addresses into the words (right only at the
original addresses). --symbolic (docs/shiftable-plan.md, step 1) makes the
output position-independent for the shiftable build:

  * jal/j to code (other functions, or inside this one): the 26-bit field is
    zeroed and `.reloc .-4, R_MIPS_26, func+off` added (func = the function
    containing the target, as the build defines it);
  * %hi/%lo pairs found by kh1tool's tracker (analyze_asm) whose address is in
    the image 0x00100000-0x00675018 (end of .bss included, crt0's heap start):
    16-bit field zeroed, R_MIPS_HI16 / R_MIPS_LO16 against D_XXXXXXXX (data,
    exact address, addend 0) or func+off (code). A lui shared by low halves
    with different targets uses the first target's symbol for all of them;
  * branches are PC-relative and stay as they are.

The .s files are assembled by binutils `as` ($(AS), 2.42 here), which takes
`.reloc`; ee-as 2.10 (the ee-gcc drivers) does not ("Unknown pseudo-op"),
which is fine because the build never assembles .s files with it.

--regen rewrites existing exports in place: same header comment, same
functions and section names, in the same order. A global label is added at
every address inside an exported function that src/ references as
func_XXXXXXXX (mid-function entry points such as func_001001d8).

Jump tables (a %lo load feeding a jr) found in exported functions are listed
on stderr: their entries live in the data blob and need data relocations.
"""
import argparse
import bisect
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K  # noqa: E402
import mips  # noqa: E402

IMAGE_LO, IMAGE_HI = 0x00100000, 0x00675018   # code .. end of .bss (inclusive)
FUNC_LINE_RE = re.compile(r"^([\w.$]+):\s+/\* 0x([0-9A-Fa-f]{8}) \*/")


class Namer:
    """Canonical names for code addresses: the symbol the build defines at a
    function start (out/gen/placements.tsv when present, then functions.tsv,
    else func_XXXXXXXX), plus an offset for addresses inside a function."""

    def __init__(self) -> None:
        self.layout = K.load_layout()
        self.starts = [f.addr for f in self.layout]
        self.text_lo, self.text_hi = self.layout[0].addr, self.layout[-1].end
        self.names: dict[int, str] = {a: s for s, a in K.load_registry().items()}
        for a, s, _o, _r in K.load_placements():
            self.names[a] = s

    def func_name(self, addr: int) -> str:
        return self.names.get(addr, f"func_{addr:08x}")

    def code(self, addr: int) -> tuple[str, int]:
        i = bisect.bisect_right(self.starts, addr) - 1
        f = self.layout[i]
        return self.func_name(f.addr), addr - f.addr

    def target(self, addr: int) -> tuple[str, int]:
        if self.text_lo <= addr < self.text_hi:
            return self.code(addr)
        return f"D_{addr:08X}", 0


def expr(sym: str, off: int) -> str:
    return sym if off == 0 else f"{sym}{'+' if off > 0 else '-'}{abs(off):#x}"


def src_label_refs() -> set[int]:
    out = set()
    for p in K.iter_sources():
        if p.suffix in (".s", ".S"):  # exports name their own %hi/%lo targets
            continue
        for m in K.ADDR_REF_RE.finditer(p.read_text(errors="ignore")):
            if m.group(0).startswith("func_"):
                out.add(int(m.group(1), 16))
    return out


def function_relocs(an: K.FuncAnalysis, f: K.Func, namer: Namer, warn: list[str]) -> dict[int, tuple[int, str, str]]:
    """addr -> (field mask to clear, reloc type, symbol expression)."""
    rel: dict[int, tuple[int, str, str]] = {}
    for a, w, _mn, _ops in an.insns:
        o = mips.op(w)
        if o in (mips.OP_J, mips.OP_JAL):
            t = mips.Insn(a, w).jump_target
            if namer.text_lo <= t < namer.text_hi:
                rel[a] = (0x03FFFFFF, "R_MIPS_26", expr(*namer.code(t)))
            else:
                warn.append(f"{f.name}: 0x{a:08x} jump to 0x{t:08x} outside the code, left absolute")
    lo_luis, full_of = flow_pairs(an, f, [])
    if more_jtbls(an, f, full_of):  # tables the linear tracker missed: redo the flow with their edges
        lo_luis, full_of = flow_pairs(an, f, warn)
    else:
        lo_luis, full_of = flow_pairs(an, f, warn)
    # connected groups of luis and the low halves they reach; each group is
    # relocated against one symbol (the first target's)
    parent: dict[int, int] = {}

    def find(x: int) -> int:
        while parent.setdefault(x, x) != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x
    for u, ls in lo_luis.items():
        for l in ls:
            parent[find(l)] = find(u)
    groups: dict[int, list[int]] = {}
    for x in parent:
        groups.setdefault(find(x), []).append(x)
    hi_set = {l for ls in lo_luis.values() for l in ls}
    for members in groups.values():
        luis = sorted(m for m in members if m in hi_set)
        us = sorted(m for m in members if m in lo_luis)
        targets = {u: full_of[u] for u in us}
        if not all(IMAGE_LO <= t <= IMAGE_HI for t in targets.values()):
            if any(IMAGE_LO <= t <= IMAGE_HI for t in targets.values()):
                warn.append(f"{f.name}: luis {', '.join(f'0x{l:08x}' for l in luis)} feed targets in and "
                            f"outside the image, left absolute")
            continue
        sym, off0 = namer.target(targets[us[0]])
        base = targets[us[0]] - off0
        if len(set(targets.values())) > 1:
            warn.append(f"{f.name}: luis {', '.join(f'0x{l:08x}' for l in luis)} shared by "
                        f"{len(set(targets.values()))} targets "
                        f"({', '.join(f'0x{t:08x}' for t in sorted(set(targets.values())))}); all relative to {sym}")
        for l in luis:
            first = min(u for u in us if l in lo_luis[u])
            rel[l] = (0xFFFF, "R_MIPS_HI16", expr(sym, targets[first] - base))
        for u in us:
            rel[u] = (0xFFFF, "R_MIPS_LO16", expr(sym, targets[u] - base))
        # the linear tracker (kh1tool analyze_asm) must agree where it found a pair
        for u in us:
            if u in an.lo_hi and (an.lo_hi[u] not in lo_luis[u] or an.lo_of[u] != targets[u]):
                warn.append(f"{f.name}: 0x{u:08x}: flow and linear %hi/%lo trackers disagree")
    check_pairing(rel, f, warn)
    for a, w, _mn, _ops in an.insns:
        if mips.op(w) == mips.OP_LUI and a not in rel and IMAGE_LO >> 16 <= (w & 0xFFFF) <= IMAGE_HI >> 16:
            warn.append(f"{f.name}: lui 0x{a:08x} (0x{w & 0xFFFF:x}) left absolute: no tracked low half "
                        f"(a constant, a dead value, or address arithmetic the tracker misses)")
    return rel



def more_jtbls(an: K.FuncAnalysis, f: K.Func, full_of: dict[int, int]) -> bool:
    """Jump tables kh1tool's pattern (a %lo load right before the jr) misses,
    e.g. `addiu v1,a0,%lo(tbl); addu v0,v0,v1; lw a0,0(v0); jr a0`: the last
    %lo address in the data before a jr through a register other than ra,
    entries read from the original while they point into the function
    (at most the bound of a preceding sltiu). Added to an.jtbls."""
    orig = _orig_elf()
    found = False
    for k, (a, w, _m, _o) in enumerate(an.insns):
        i = mips.Insn(a, w)
        if not i.is_jr or i.is_jr_ra:
            continue
        prev = [x for x in an.insns[max(0, k - 8): k]]
        base = next((full_of[pa] for pa, _pw, _pm, _po in reversed(prev)
                     if pa in full_of and 0x00272C70 <= full_of[pa] < 0x00494068), None)
        if base is None or base in an.jtbls:
            continue
        bound = next((pw & 0xFFFF for pa, pw, _pm, _po in reversed(an.insns[max(0, k - 16): k])
                      if mips.op(pw) == 0x0B), 256)
        entries = []
        for n in range(bound):
            t = int.from_bytes(orig.read(base + 4 * n, 4) or b"\0\0\0\0", "little")
            if not f.addr <= t < f.end:
                break
            entries.append(t)
        if entries:
            an.jtbls[base] = entries
            an.labels.update(entries)
            found = True
    return found


_ORIG = None


def _orig_elf():
    global _ORIG
    if _ORIG is None:
        _ORIG = K.require_orig(K.load_config())
    return _ORIG


BRANCH_LIKELY = {0x14, 0x15, 0x16, 0x17}
CALLER_SAVED = [r for r in range(1, 32) if not (16 <= r <= 23 or r in (28, 29, 30))]


def gpr_written(w: int) -> tuple[int | None, bool]:
    """(GPR an instruction writes, keeps_hi): keeps_hi for addu/daddu rX,rX,rY,
    which keeps rX's %hi (jump-table indexing), as in kh1tool's tracker."""
    o = mips.op(w)
    if o in (0x11, 0x12):
        return (mips.rt(w), False) if mips.rs(w) in (0, 1, 2) else (None, False)
    if o in K.GPR_RT_WRITERS:
        return mips.rt(w), False
    if o == mips.OP_MMI:
        return mips.rd(w), False
    if o == mips.OP_JAL:
        return 31, False
    if o == mips.OP_REGIMM and mips.rt(w) in (0x10, 0x11, 0x12, 0x13):
        return 31, False
    if o == mips.OP_SPECIAL:
        if mips.funct(w) in (0x21, 0x2D) and mips.rd(w) == mips.rs(w):
            return mips.rd(w), True
        return mips.rd(w), False
    return None, False


def flow_pairs(an: K.FuncAnalysis, f: K.Func, warn: list[str]) -> tuple[dict[int, set[int]], dict[int, int]]:
    """%hi/%lo pairing by reaching definitions over the function's control
    flow (delay slots, likely branches, jump tables, caller-saved registers
    clobbered by calls). The linear tracker forgets a lui at every label, so
    it misses a %hi hoisted out of a loop or kept across a branch.
    Returns (low-half user addr -> lui addrs reaching it, user -> full address)."""
    ins = [(a, w) for a, w, _m, _o in an.insns]
    n = len(ins)
    idx = {a: k for k, (a, _w) in enumerate(ins)}
    jt_targets = sorted({t for es in an.jtbls.values() for t in es})
    # edges: k -> [(succ, clobber)]
    succ: list[list[tuple[int, bool]]] = [[] for _ in range(n)]
    slot = False  # ins[k] is a delay slot: its successors come from the branch
    for k, (a, w) in enumerate(ins):
        i = mips.Insn(a, w)
        o = mips.op(w)
        is_ct = i.is_branch or o in (mips.OP_J, mips.OP_JAL) or i.is_jr or i.is_jalr
        in_slot, slot = slot, is_ct
        if not is_ct:
            if o == 0x10 and (w & 0x3F) == 0x18 and mips.rs(w) == 0x10:  # eret
                continue
            # a delay slot falls through only on a not-taken ordinary branch (added below);
            # after a likely branch it runs only on the taken path
            if k + 1 < n and not in_slot:
                succ[k].append((k + 1, False))
            continue
        d = k + 1  # delay slot
        likely = o in BRANCH_LIKELY or (o == mips.OP_REGIMM and mips.rt(w) in (0x02, 0x03, 0x12, 0x13)) or \
            (o in (0x11, 0x12) and mips.rs(w) == 0x08 and mips.rt(w) & 2)
        if d < n:
            succ[k].append((d, False))
        if likely and k + 2 < n:
            succ[k].append((k + 2, False))  # not taken: the delay slot is skipped
        if d >= n:
            continue
        outs: list[tuple[int, bool]] = []
        uncond = (o == 0x04 and mips.rs(w) == 0 and mips.rt(w) == 0) or \
            (o == mips.OP_REGIMM and mips.rt(w) == 0x01 and mips.rs(w) == 0)
        if i.branch_target is not None:
            t = i.branch_target
            if t in idx:
                outs.append((idx[t], False))
            if (o == mips.OP_REGIMM and mips.rt(w) in (0x10, 0x11, 0x12, 0x13)):  # bal: a call
                outs = [(k + 2, True)] if k + 2 < n else []
            elif not uncond and not likely and k + 2 < n:
                outs.append((k + 2, False))
        elif o == mips.OP_J:
            t = i.jump_target
            if t in idx:
                outs.append((idx[t], False))
        elif o == mips.OP_JAL or i.is_jalr:
            if k + 2 < n:
                outs.append((k + 2, True))
        elif i.is_jr and not i.is_jr_ra:
            outs += [(idx[t], False) for t in jt_targets if t in idx]
        succ[d] += outs
    # forward data flow: state = reg -> frozenset of lui indices
    # (code nothing reaches, e.g. after an eret, is an entry point of its own)
    state_in: list[dict[int, frozenset] | None] = [None] * n
    work: list[int] = []
    for root in range(n):
        if state_in[root] is not None:
            continue
        state_in[root] = {}
        work.append(root)
        _flow(work, state_in, succ, ins)
    lo_luis: dict[int, set[int]] = {}
    full_of: dict[int, int] = {}
    for k, (a, w) in enumerate(ins):
        st = state_in[k]
        if st is None:
            continue
        o = mips.op(w)
        base = mips.rs(w)
        if base not in st or not (o in (0x09, 0x0D) or o in mips.OP_LOADS or o in mips.OP_STORES
                                  or o in mips.OP_VU_MEM or o in (mips.OP_LQ, mips.OP_SQ)):
            continue
        fulls = {(ins[l][1] & 0xFFFF) << 16 for l in st[base]}
        fulls = {(u + (mips.imm(w) if o != 0x0D else w & 0xFFFF)) & 0xFFFFFFFF for u in fulls}
        full = min(fulls)
        if o == 0x0D or (o == 0x09 and not K.RAM_START <= full < K.RAM_END):
            continue
        if len(fulls) > 1:
            warn.append(f"{f.name}: 0x{a:08x} is reached by luis with different values; left absolute")
            continue
        lo_luis[a] = {ins[l][0] for l in st[base]}
        full_of[a] = full
    return lo_luis, full_of


def _flow(work, state_in, succ, ins) -> None:
    while work:
        k = work.pop()
        st = dict(state_in[k])
        a, w = ins[k]
        if mips.op(w) == mips.OP_LUI:
            st[mips.rt(w)] = frozenset([k])
        else:
            r, keep = gpr_written(w)
            if r and not keep:
                st.pop(r, None)
        for s2, clob in succ[k]:
            out = st
            if clob:
                out = {r: v for r, v in st.items() if r not in CALLER_SAVED}
            cur = state_in[s2]
            if cur is None:
                state_in[s2] = dict(out)
                work.append(s2)
            else:
                changed = False
                for r, v in out.items():
                    if not v <= cur.get(r, frozenset()):
                        cur[r] = cur.get(r, frozenset()) | v
                        changed = True
                if changed:
                    work.append(s2)


def _addend(e: str) -> tuple[str, int]:
    m = re.match(r"^(.*?)([+-]0x[0-9a-f]+)?$", e)
    return m.group(1), int(m.group(2), 16) if m.group(2) else 0


def check_pairing(rel: dict, f: K.Func, warn: list[str]) -> None:
    """GNU ld (REL) pairs each R_MIPS_HI16 with the next R_MIPS_LO16 against
    the same symbol and takes the addend from both fields. Make sure that
    pairing gives every HI16 its own addend."""
    items = sorted(rel.items())
    for k, (a, (_m, typ, e)) in enumerate(items):
        if typ != "R_MIPS_HI16":
            continue
        sym, add = _addend(e)
        lo = next((_addend(e2)[1] for _a2, (_m2, t2, e2) in items[k + 1:]
                   if t2 == "R_MIPS_LO16" and _addend(e2)[0] == sym), None)
        if lo is None:
            warn.append(f"{f.name}: HI16 at 0x{a:08x} ({e}) has no LO16 after it")
            continue
        hi_field = ((add + 0x8000) >> 16) & 0xFFFF
        lo_field = lo & 0xFFFF
        got = (hi_field << 16) + (lo_field - 0x10000 if lo_field & 0x8000 else lo_field)
        if got != add:  # %hi(S + got) == %hi(S + add) for every S only if got == add
            warn.append(f"{f.name}: HI16 at 0x{a:08x} ({e}) pairs with a LO16 of addend {lo:#x}")


def export(names: list[str], header: str, symbolic: bool = False, sections: list[str] | None = None,
           labels: set[int] | None = None, report: list[str] | None = None) -> str:
    cfg = K.load_config()
    reg = K.load_registry()
    by_addr = {a: s for s, a in reg.items()}
    namer = Namer() if symbolic else None
    labels = labels or set()
    warn = report if report is not None else []
    lines = [header if header.startswith("/*") else (f"/* {header} */" if header else
                                                      "/* exported by tools/asm_export.py */"),
             "\t.set\tnoreorder", "\t.set\tnoat"]
    for k, n in enumerate(names):
        f = K.find_func(n if not n.startswith("0x") else "func_" + n[2:].lower().zfill(8))
        sym = sections[k] if sections else by_addr.get(f.addr, f"func_{f.addr:08x}")
        body = [l for l in K.function_asm(cfg, f, by_addr).splitlines() if l.strip().startswith("/*")]
        rel = {}
        if symbolic:
            an = K.analyze_asm(cfg, f)
            rel = function_relocs(an, f, namer, warn)
            for base, entries in sorted(an.jtbls.items()):
                warn.append(f"{sym}: jump table at 0x{base:08x}, {len(entries)} entries into "
                            f"0x{f.addr:08x}-0x{f.end:08x} (data blob, needs data relocations)")
        lines += ["", f'\t.section\t.text.{sym},"ax",@progbits', f"\t.globl\t{sym}", f"\t.ent\t{sym}",
                  f"{sym}:  /* 0x{f.addr:08X} */"]
        for l in body:
            # `/* ADDR WORD */ text`
            addr, word = l.strip()[2:].split("*/")[0].split()[:2]
            text = l.split("*/", 1)[1].strip()
            a, w = int(addr, 16), int(word, 16)
            if a in labels and a != f.addr:
                lab = f"func_{a:08x}"
                lines += [f"\t.globl\t{lab}", f"{lab}:  /* mid-function entry point */"]
            r = rel.get(a)
            if r:
                lines.append(f"\t.word\t0x{w & ~r[0] & 0xFFFFFFFF:08X}  /* {addr} {' '.join(text.split())} */")
                lines.append(f"\t.reloc\t.-4, {r[1]}, {r[2]}")
            else:
                lines.append(f"\t.word\t0x{word}  /* {addr} {' '.join(text.split())} */")
        lines.append(f"\t.end\t{sym}")
    return "\n".join(lines) + "\n"


def parse_existing(path: Path) -> tuple[str, list[str], list[str]]:
    """(header comment, function addresses, section names) of an export."""
    text = path.read_text()
    head = text.split("\n\t.set\tnoreorder", 1)[0]
    addrs, secs = [], []
    for line in text.splitlines():
        m = FUNC_LINE_RE.match(line)
        if m:
            secs.append(m.group(1))
            addrs.append("0x" + m.group(2).lower())
    return head, addrs, secs


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("out", nargs="?")
    ap.add_argument("functions", nargs="*")
    ap.add_argument("--header", default="")
    ap.add_argument("--symbolic", action="store_true", help="relocatable output (.reloc), see above")
    ap.add_argument("--regen", nargs="+", metavar="FILE.s", help="rewrite existing exports in place")
    a = ap.parse_args()
    report: list[str] = []
    if a.regen:
        refs = src_label_refs()
        for p in map(Path, a.regen):
            head, addrs, secs = parse_existing(p)
            fs = [K.find_func("func_" + x[2:].zfill(8)) for x in addrs]
            labels = {r for r in refs for f in fs if f.addr < r < f.end}
            p.write_text(export(addrs, head, a.symbolic, secs, labels, report))
            print(f"{p}: {len(addrs)} functions"
                  + (f", labels {', '.join(f'func_{x:08x}' for x in sorted(labels))}" if labels else ""))
    else:
        if not a.out or not a.functions:
            ap.error("OUT.s and at least one function are required (or --regen)")
        Path(a.out).write_text(export(a.functions, a.header, a.symbolic, report=report))
    for r in report:
        print(f"note: {r}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
