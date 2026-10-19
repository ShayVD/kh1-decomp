#!/usr/bin/env python3
"""Alias table for the shiftable link (docs/shiftable-plan.md 1a, step 3).

Many names share an address with a function the shift link defines: the
GOFAST libcall names (dpadd = __adddf3, ...), func_XXXXXXXX placeholders of
functions that have a real name (func_00250054 = memset), functions.tsv
names of the same address, the name C code uses for an unmatched function
whose export is named otherwise (func_00265608 = sceGsDefDispEnv). The
normal build resolves them all with PROVIDE() at the original address; the
shift link must not (a PROVIDE silently pins a name to its *old* address),
so each one becomes `alias = canonical;` (or `alias = canonical + 0xOFF;`
for an address inside a function).

  python3 -I tools/shift/aliases.py [--out shift/aliases.ld]

Defined names come from out/linked.elf (the normal build's link of every
src/ object; run `make` first) and the exports in shift/unmatched/*.s.
Aliases are written for every functions.tsv / libcall name of a defined
address and for every name an object or export references without defining,
when its address is in the code (0x00100000-0x00272C70). Only names and
addresses, no game bytes. tools/shift/provide_check.py lists what is left.
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import kh1tool as K  # noqa: E402
from elf32 import Elf  # noqa: E402

TEXT_LO, TEXT_HI = 0x00100000, 0x00272C70
IMAGE_LO, IMAGE_HI = 0x00100000, 0x00675018
SHN_ABS = 0xFFF1
NAME_RE = re.compile(r"^(?:func|D)_([0-9A-Fa-f]{8})$")
EXPORT_DEF_RE = re.compile(r"^([\w.$]+):\s+/\* 0x([0-9A-Fa-f]{8}) \*/", re.M)
EXPORT_REF_RE = re.compile(r"^\t\.reloc\t\.-4, R_MIPS_\w+, ([\w.$]+)", re.M)
PROVIDE_RE = re.compile(r"^PROVIDE\((\S+) = 0x([0-9a-f]+)\);", re.M)
DEFAULT_EXPORTS = K.ROOT / "shift" / "unmatched"
DEFAULT_OUT = K.ROOT / "shift" / "aliases.ld"


def object_paths() -> list[Path]:
    mk = (K.GEN / "objects.mk").read_text()
    m = re.search(r"^OBJS := (.*)$", mk, re.M)
    return [K.ROOT / p for p in m.group(1).split()]


def collect(exports: Path = DEFAULT_EXPORTS):
    """(defined name -> addr, canonical name per function start,
    referenced-undefined name -> set of referencing files, provide map)."""
    if not K.LINKED.exists():
        sys.exit("error: out/linked.elf missing; run `make` first")
    defined: dict[str, int] = {}
    for s in Elf.load(K.LINKED).symbols():
        if s.name and s.bind in (1, 2) and s.shndx not in (0, SHN_ABS) and s.shndx < 0xFF00:
            defined[s.name] = s.value
    refs: dict[str, set[str]] = {}
    for obj in object_paths():
        elf = Elf.load(obj)
        for s in elf.symbols():
            if s.name and s.shndx == 0 and s.bind in (1, 2):
                refs.setdefault(s.name, set()).add(obj.relative_to(K.ROOT).as_posix())
    export_files = sorted(exports.glob("*.s")) if exports.exists() else []
    for p in export_files:
        text = p.read_text()
        for m in EXPORT_DEF_RE.finditer(text):
            defined[m.group(1)] = int(m.group(2), 16)
        for m in EXPORT_REF_RE.finditer(text):
            refs.setdefault(m.group(1), set()).add(p.relative_to(K.ROOT).as_posix())
    for name in list(refs):
        if name in defined:
            del refs[name]
    canon: dict[int, str] = {}
    for a, s, _o, _r in K.load_placements():
        canon[a] = s
    for p in export_files:
        for m in EXPORT_DEF_RE.finditer(p.read_text()):
            canon.setdefault(int(m.group(2), 16), m.group(1))
    provides = {m.group(1): int(m.group(2), 16) for m in PROVIDE_RE.finditer((K.GEN / "symbols.ld").read_text())}
    return defined, canon, refs, provides


def address_of(name: str, provides: dict[str, int], registry: dict[str, int]) -> int | None:
    if name in provides:
        return provides[name]
    m = NAME_RE.match(name)
    if m:
        return int(m.group(1), 16)
    if name in registry:
        return registry[name]
    t = K.LIBCALL_ALIASES.get(name)
    return registry.get(t) if t else None


def build_aliases(defined, canon, refs, provides) -> tuple[list[tuple[str, str, int]], list[str]]:
    """[(alias, canonical, offset)], notes."""
    registry = K.load_registry()
    layout = K.load_layout()
    starts = {f.addr: f for f in layout}
    import bisect
    addrs = [f.addr for f in layout]
    candidates: set[str] = set(refs)
    candidates |= {n for n, a in registry.items() if a in canon}
    candidates |= {n for n, t in K.LIBCALL_ALIASES.items() if registry.get(t) in canon}
    out, notes = [], []
    for name in sorted(candidates):
        if name in defined:
            continue
        a = address_of(name, provides, registry)
        if a is None or not TEXT_LO <= a < TEXT_HI:
            continue
        if a in canon:
            if canon[a] != name:
                out.append((name, canon[a], 0))
            continue
        f = layout[bisect.bisect_right(addrs, a) - 1]
        if f.addr in canon and a < f.end:
            out.append((name, canon[f.addr], a - f.addr))
            notes.append(f"{name} is inside {canon[f.addr]} (+0x{a - f.addr:x}); right only while that "
                         f"function's code is the original")
        elif a not in starts:
            notes.append(f"{name} (0x{a:08x}) is in no defined function")
    return out, notes


def render(aliases: list[tuple[str, str, int]]) -> str:
    lines = ["/* Generated by tools/shift/aliases.py: names that share an address with a function the",
             " * shiftable link defines (or point inside one). Names and addresses only. */"]
    for name, target, off in sorted(aliases, key=lambda x: (x[1], x[2], x[0])):
        lines.append(f"{name} = {target};" if off == 0 else f"{name} = {target} + 0x{off:x};")
    return "\n".join(lines) + "\n"


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", default=str(DEFAULT_OUT))
    ap.add_argument("--exports", default=str(DEFAULT_EXPORTS))
    a = ap.parse_args()
    defined, canon, refs, provides = collect(Path(a.exports))
    aliases, notes = build_aliases(defined, canon, refs, provides)
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    Path(a.out).write_text(render(aliases))
    for n in notes:
        print(f"note: {n}", file=sys.stderr)
    print(f"aliases: {len(aliases)} lines -> {a.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
