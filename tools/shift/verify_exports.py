#!/usr/bin/env python3
"""Check symbolic asm exports outside the normal build (shift/unmatched/*.s):
assemble each file, link every .text.<name> section at its original address
with every undefined symbol at its original address (D_XXXXXXXX / func_XXXXXXXX
by name, other names from functions.tsv, func+off as written), and compare
with the original ELF. Also checks that the relocations are really there
(a word export with no relocations would pass this test too).

  python3 -I tools/shift/verify_exports.py shift/unmatched/*.s [--delta 0x12340]

--delta D links the code and every symbol inside the image (0x00100000-
0x00675018) D bytes higher and checks each word against the original moved
by D: relocated fields must hold target+D (%hi with the carry of the moved
address), every other word must be unchanged. That proves the relocations
that exist are right, including %hi/%lo pairing (pick D not a multiple of
0x10000); it cannot find an address the export left absolute.

Needs the user's ELF (kh1.toml target) and binutils; writes only under
out/shift_verify/."""
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import kh1tool as K  # noqa: E402
from elf32 import Elf  # noqa: E402

AS = K.BINUTILS + "as"
LD = K.BINUTILS + "ld"
OUTDIR = K.OUT / "shift_verify"
NAME_RE = re.compile(r"^(?:func|D)_([0-9A-Fa-f]{8})$")


def undefined_symbols(obj: Path) -> set[str]:
    out = subprocess.run([K.BINUTILS + "readelf", "-sW", str(obj)], check=True, capture_output=True, text=True).stdout
    names = set()
    for line in out.splitlines():
        p = line.split()
        if len(p) >= 8 and p[6] == "UND" and p[4] in ("GLOBAL", "WEAK"):
            names.add(p[7])
    return names


def reloc_count(obj: Path) -> int:
    out = subprocess.run([K.BINUTILS + "readelf", "-rW", str(obj)], check=True, capture_output=True, text=True).stdout
    sec, n = "", 0
    for line in out.splitlines():
        m = re.match(r"Relocation section '\.rel(\S+)'", line)
        if m:
            sec = m.group(1)
        elif sec.startswith(".text") and "R_MIPS_" in line:
            n += 1
    return n


RELOC_RE = re.compile(r"^\t\.word\t0x([0-9A-F]{8})  /\* ([0-9A-F]{8}) .*\n\t\.reloc\t\.-4, (R_MIPS_\w+), "
                      r"([\w.$]+)(?:([+-])0x([0-9a-f]+))?$", re.M)
IMAGE_LO, IMAGE_HI = 0x00100000, 0x00675018


def expected_moved(text: str, reg: dict, delta: int) -> dict[int, tuple[str, int]]:
    """addr -> (reloc type, original target address) from the export's text."""
    out = {}
    for m in RELOC_RE.finditer(text):
        sym = m.group(4)
        nm = NAME_RE.match(sym)
        base = int(nm.group(1), 16) if nm else reg[sym]
        off = int(m.group(6), 16) * (-1 if m.group(5) == "-" else 1) if m.group(6) else 0
        out[int(m.group(2), 16)] = (m.group(3), base + off)
    return out


def moved(v: int, delta: int) -> int:
    return v + delta if IMAGE_LO <= v <= IMAGE_HI else v


def main() -> int:
    args = sys.argv[1:]
    delta = 0
    if "--delta" in args:
        k = args.index("--delta")
        delta = int(args[k + 1], 0)
        del args[k: k + 2]
    files = [Path(a) for a in args]
    if not files:
        sys.exit(__doc__)
    cfg = K.load_config()
    orig = K.require_orig(cfg)
    reg = K.load_registry()
    layout = {f.addr: f for f in K.load_layout()}
    OUTDIR.mkdir(parents=True, exist_ok=True)
    bad = 0
    for src in files:
        obj = OUTDIR / (src.stem + ".o")
        subprocess.run([AS, *cfg["toolchain"]["asflags"].split(), "-o", str(obj), str(src)], check=True)
        exp = expected_moved(src.read_text(), reg, delta)
        secs = re.findall(r"\.section\s+\.text\.([\w.$]+),", src.read_text())
        defs, ok = [], True
        for s in sorted(undefined_symbols(obj)):
            m = NAME_RE.match(s)
            addr = int(m.group(1), 16) if m else reg.get(s)
            if addr is None:
                print(f"{src}: undefined symbol {s} has no known address")
                ok = False
                continue
            defs.append(f"{s} = 0x{moved(addr, delta):08x};")
        lines = ["SECTIONS {"]
        for name in secs:
            addr = reg.get(name) or int(NAME_RE.match(name).group(1), 16)
            lines.append(f"  .f_{addr:08x} 0x{addr + delta:08x} : {{ KEEP(*(.text.{name})) }}")
        lines += ["  /DISCARD/ : { *(*) }", "}"] + defs
        ld = OUTDIR / (src.stem + ".ld")
        ld.write_text("\n".join(lines) + "\n")
        elf_path = OUTDIR / (src.stem + ".elf")
        subprocess.run([LD, "-EL", "-e", "0", "--no-check-sections", "-T", str(ld), "-o", str(elf_path), str(obj)],
                       check=True)
        linked = Elf.load(elf_path)
        for name in secs:
            addr = reg.get(name) or int(NAME_RE.match(name).group(1), 16)
            sec = linked.section(f".f_{addr:08x}")
            code = linked.data[sec.offset: sec.offset + sec.size]
            want = orig.read(addr, layout[addr].size)
            if delta:
                want = bytearray(want)
                for a, (typ, t) in exp.items():
                    if not addr <= a < addr + len(want):
                        continue
                    o = a - addr
                    w = int.from_bytes(want[o:o + 4], "little")
                    nt = moved(t, delta)
                    if typ == "R_MIPS_26":
                        w = (w & 0xFC000000) | ((nt >> 2) & 0x03FFFFFF)
                    elif typ == "R_MIPS_HI16":
                        w = (w & 0xFFFF0000) | (((nt + 0x8000) >> 16) & 0xFFFF)
                    elif typ == "R_MIPS_LO16":
                        w = (w & 0xFFFF0000) | (nt & 0xFFFF)
                    want[o:o + 4] = w.to_bytes(4, "little")
                want = bytes(want)
            if code != want:
                ok = False
                diffs = [i for i in range(0, min(len(code), len(want)), 4) if code[i:i + 4] != want[i:i + 4]]
                print(f"{src}: {name} differs ({len(code)} vs {len(want)} bytes; first word diff at "
                      f"+0x{diffs[0] if diffs else 0:x})")
        n = reloc_count(obj)
        print(f"{src}: {'OK' if ok else 'FAIL'} ({len(secs)} functions, {n} text relocations)")
        bad += not ok
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
