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
    users: dict[int, list[int]] = {}
    for u, lui in an.lo_hi.items():
        users.setdefault(lui, []).append(u)
    for lui, us in sorted(users.items()):
        us.sort()
        targets = [an.lo_of[u] for u in us]
        if not all(IMAGE_LO <= t <= IMAGE_HI for t in targets):
            if any(IMAGE_LO <= t <= IMAGE_HI for t in targets):
                warn.append(f"{f.name}: lui 0x{lui:08x} feeds targets in and outside the image, left absolute")
            continue
        sym, off0 = namer.target(targets[0])
        base = targets[0] - off0
        if len(set(targets)) > 1:
            warn.append(f"{f.name}: lui 0x{lui:08x} shared by {len(set(targets))} targets "
                        f"({', '.join(f'0x{t:08x}' for t in sorted(set(targets)))}); all relative to {sym}")
        rel[lui] = (0xFFFF, "R_MIPS_HI16", expr(sym, an.hi_of[lui] - base))
        for u, t in zip(us, targets):
            rel[u] = (0xFFFF, "R_MIPS_LO16", expr(sym, t - base))
    check_pairing(rel, f, warn)
    for a, w, _mn, _ops in an.insns:
        if mips.op(w) == mips.OP_LUI and a not in rel and IMAGE_LO >> 16 <= (w & 0xFFFF) <= IMAGE_HI >> 16:
            warn.append(f"{f.name}: lui 0x{a:08x} (0x{w & 0xFFFF:x}) left absolute: no tracked low half "
                        f"(a constant, a dead value, or address arithmetic the tracker misses)")
    return rel


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
