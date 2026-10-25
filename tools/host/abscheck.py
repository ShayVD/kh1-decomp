#!/usr/bin/env python3
"""List the PS2 addresses written as numbers in the host objects (phase 5, docs/vita-port-plan.md 5.1m).

  python3 -I tools/host/abscheck.py [--all] [--tsv out/host/abscheck.tsv]

Run after `make host-census`.  On the host and the Vita a variable is where
the linker puts it, so C that reads memory through a number instead of a name
(`((s32 *)0x35BD40)[i]`, a hardware register) reads an address that is not
the game's.  The PS2 objects cannot show it (every address there is a
number); the host objects can: there a name is a relocation, and a number is
not.  Reads `objdump -dr` of every game object under out/host (src/, the
drafts in nonmatchings/, data/), not the null platform or the port.

Rows (exit 1 when there are any):
  mem   a memory operand whose displacement, with no relocation on the
        instruction, is a PS2 address: main memory 0x00100000-0x01ffffff,
        the hardware registers 0x10000000-0x1200ffff, the scratchpad
        0x70000000-0x70003fff (or a mirror: | 0x20000000 / 0x30000000).
  imm   an immediate (mov / push / lea / cmp) with no relocation that is
        exactly the start of a function or variable of the linked PS2 ELF
        (out/shift/kh1-shift.linked.elf): an address passed as a number.
Other immediates in those ranges are DMA tags, GS registers, masks and
colours, and are not rows.  REVIEWED holds the compiler patterns read by hand
(index arithmetic folded into a displacement, a tag word built with lea, a
heap carved at fixed offsets); --all prints them too.  Only names and
instruction text are printed, no game bytes."""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HOST = ROOT / "out" / "host"
GAME_DIRS = ("src", "nonmatchings", "data")
PS2_ELF = ROOT / "out" / "shift" / "kh1-shift.linked.elf"

# (function, displacement) -> why: read by hand, not an address
REVIEWED = {
    ("func_0010a780", 0x70000001): "the end tag cnt * 13 + 0x70000001 built with lea",
    ("func_001bfe50", 0x16BC00): "the task heap's offsets from its base (func_001bfec8's 0x171388 bytes)",
    ("func_001bfe50", 0x170700): "the task heap's offsets from its base",
    ("func_001bfe50", 0x171388): "the task heap's end",
}
NOT_ADDRESSES = {"_ftext"}  # 0x100000 is also a GS value (the windows' 0x100000 words)

INSN = re.compile(r"^\s+([0-9a-f]+):\s+(\S.*)$")
RELOC = re.compile(r"^\s+[0-9a-f]+:\s+R_386_")
FUNC = re.compile(r"^[0-9a-f]+ <(.+)>:$")
DISP = re.compile(r"(?<![\w$])(-?0x[0-9a-f]+)\(([^)]*)\)")
ABS = re.compile(r"(?<![\w$(])(0x[0-9a-f]+)(?![\w(])")
IMM = re.compile(r"\$(0x[0-9a-f]+)")


def ps2_address(v):
    v &= 0xFFFFFFFF
    if 0x10000000 <= v < 0x12010000 or 0x70000000 <= v < 0x70004000:
        return True
    return v >> 28 in (0, 2, 3) and 0x00100000 <= (v & 0x0FFFFFFF) < 0x02000000


def ps2_symbols():
    if not PS2_ELF.exists():
        return {}
    out = subprocess.run(["mips-linux-gnu-nm", str(PS2_ELF)], capture_output=True, text=True).stdout
    syms = {}
    for ln in out.splitlines():
        p = ln.split()
        if len(p) == 3 and p[1] in "TtDdBbRrSs" and p[2] not in NOT_ADDRESSES:
            v = int(p[0], 16)
            if 0x00100000 <= v < 0x02000000:
                syms.setdefault(v, p[2])
    return syms


def objects():
    for d in GAME_DIRS:
        yield from sorted((HOST / d).rglob("*.o"))
    if (HOST / "defs_host.c.o").exists():
        yield HOST / "defs_host.c.o"


def scan(obj, syms):
    lines = subprocess.run(["objdump", "-dr", "--no-show-raw-insn", str(obj)],
                           capture_output=True, text=True).stdout.split("\n")
    fn = None
    for i, ln in enumerate(lines):
        m = FUNC.match(ln)
        if m:
            fn = m.group(1)
            continue
        m = INSN.match(ln)
        if not m or RELOC.match(ln) or (i + 1 < len(lines) and RELOC.match(lines[i + 1])):
            continue
        text = m.group(2)
        op, _, args = text.partition(" ")
        if not args or op.startswith(("j", "call")):
            continue
        for d in DISP.finditer(args):
            v = int(d.group(1), 16)
            if abs(v) >= 0x100000 and ps2_address(v):
                yield fn, "mem", v, text.strip()
        for d in ABS.finditer(args):
            v = int(d.group(1), 16)
            if ps2_address(v):
                yield fn, "mem", v, text.strip()
        if op.startswith(("mov", "push", "lea", "cmp")):
            for d in IMM.finditer(args):
                v = int(d.group(1), 16)
                if v in syms:
                    yield fn, "imm " + syms[v], v, text.strip()


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--all", action="store_true", help="also print the REVIEWED patterns")
    ap.add_argument("--tsv", help="write the rows here")
    a = ap.parse_args()
    if not (HOST / "src").is_dir():
        sys.exit("abscheck: no out/host/src; run `make host-census` first")
    syms = ps2_symbols()
    if not syms:
        print("# abscheck: no out/shift/kh1-shift.linked.elf (run `make shift`): imm rows skipped", file=sys.stderr)
    rows, reviewed, nobj = [], [], 0
    for obj in objects():
        nobj += 1
        rel = str(obj.relative_to(HOST))
        for fn, kind, v, text in scan(obj, syms):
            row = (rel, fn, kind, "0x%x" % (v & 0xFFFFFFFF), text)
            if (fn, v & 0xFFFFFFFF) in REVIEWED:
                reviewed.append(row + (REVIEWED[(fn, v & 0xFFFFFFFF)],))
            else:
                rows.append(row)
    rows = sorted(set(rows))
    for r in rows:
        print("\t".join(r))
    if a.all:
        for r in sorted(set(reviewed)):
            print("REVIEWED\t" + "\t".join(r))
    if a.tsv:
        Path(a.tsv).write_text("".join("\t".join(r) + "\n" for r in rows))
    print("# %d host objects; %d rows (PS2 addresses as numbers); %d reviewed patterns left out"
          % (nobj, len(rows), len(set(reviewed))))
    return 1 if rows else 0


if __name__ == "__main__":
    sys.exit(main())
