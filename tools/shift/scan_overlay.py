#!/usr/bin/env python3
"""Which addresses of the main ELF does an EE overlay use? (shiftable plan
step 9, risk 1). Run it on overlay files (.x) you extracted from your own
disc (tools/shift/extract_kingdom.py): dkmovie.x, dktitle.x, gb.x, wm.x,
xl_limit.x, xs_dh_break.x, xs_{dumbo,bambi,genie,tink,mushu,simba}.x.

  python3 -I tools/shift/scan_overlay.py FILE.x [--base 0xF20000] [--all]
      [--layout layout.tsv] [--functions functions.tsv]

Standalone (Python >= 3.10, stdlib only): copy this file anywhere and pass
--layout / --functions (default: the repo root above tools/shift/).

The file is raw code+data loaded at --base (0x00F20000, where func_00111020
loads dkmovie.x), or an ELF (detected by its header: every PT_LOAD at its
own address). Every aligned word is checked for
  * jal / j whose target is in the main ELF's code 0x00100000-0x00272C70;
  * a lui and the low half that completes it (addiu / load / store through
    the same register, followed forward until the register is rewritten,
    the code returns, or 64 instructions) giving an address in the image
    0x00100000-0x00675018;
  * any other word whose value is in 0x00100000-0x00675018 (a data
    pointer, or an instruction that merely looks like one: judge by the
    neighbours; aligned code addresses at function starts are the strong
    ones).
Each hit is named from layout.tsv / functions.tsv (function + offset) or as
D_XXXXXXXX. If any are found, the overlay was linked against the main ELF's
absolute addresses: moving those functions/data breaks it unless they are
pinned or the overlay is relocated too.

Reads only the file given; prints names and addresses, never the file's
bytes. Nothing is written.
"""
from __future__ import annotations

import argparse
import bisect
import struct
import sys
from collections import Counter
from pathlib import Path

# Standalone: Python >= 3.10 stdlib only, no repo imports, so the file can be
# copied next to layout.tsv / functions.tsv and run on another machine.
REPO = Path(__file__).resolve().parents[2]
JR_RA = 0x03E00008
OP_SPECIAL, OP_J, OP_JAL, OP_LUI, OP_MMI = 0x00, 0x02, 0x03, 0x0F, 0x1C
OP_LQ, OP_SQ = 0x1E, 0x1F
OP_LOADS = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x1A, 0x1B, 0x37, 0x31, 0x35}
OP_STORES = {0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x3F, 0x39, 0x3D}
OP_VU_MEM = {0x36, 0x3E}  # lqc2 sqc2
GPR_RT_WRITERS = {0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x18, 0x19,
                  0x1A, 0x1B, 0x1E, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x37}


def op(w: int) -> int: return w >> 26
def rs(w: int) -> int: return (w >> 21) & 31
def rt(w: int) -> int: return (w >> 16) & 31
def rd(w: int) -> int: return (w >> 11) & 31
def funct(w: int) -> int: return w & 63


def imm(w: int) -> int:
    v = w & 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


TEXT_LO, TEXT_HI = 0x00100000, 0x00272C70
IMAGE_LO, IMAGE_HI = 0x00100000, 0x00675018
DATA_HI, BSS_LO = 0x00494068, 0x00494080
WINDOW = 64
LO_OPS = {0x09} | OP_LOADS | OP_STORES | OP_VU_MEM | {OP_LQ, OP_SQ}


def load_segments(path: Path, base: int) -> tuple[str, list[tuple[int, bytes]]]:
    data = path.read_bytes()
    if data[:4] == b"\x7fELF":
        if data[4] != 1 or data[5] != 1:
            sys.exit(f"{path}: not a 32-bit little-endian ELF")
        phoff, = struct.unpack_from("<I", data, 0x1C)
        phentsize, phnum = struct.unpack_from("<HH", data, 0x2A)
        segs = []
        for i in range(phnum):
            ptype, offset, vaddr, _pa, filesz = struct.unpack_from("<5I", data, phoff + i * phentsize)
            if ptype == 1 and filesz:  # PT_LOAD
                segs.append((vaddr, data[offset: offset + filesz]))
        return "ELF", segs
    return f"raw at 0x{base:08x}", [(base, data)]


class Func:
    def __init__(self, addr: int, end: int, name: str) -> None:
        self.addr, self.end, self.name = addr, end, name


def load_layout(path: Path) -> list[Func]:
    """layout.tsv: addr<TAB>end<TAB>size<TAB>name (hex addresses)."""
    if not path.exists():
        sys.exit(f"error: {path} missing (pass --layout PATH to the repo's layout.tsv)")
    out = []
    for line in path.read_text().splitlines():
        if not line.strip() or line.startswith(("#", "addr")):
            continue
        addr, end, _size, name = line.split("\t")[:4]
        out.append(Func(int(addr, 16), int(end, 16), name))
    return sorted(out, key=lambda f: f.addr)


def load_registry(path: Path) -> dict[int, str]:
    """functions.tsv: symbol<TAB>address (symbols may be C++ signatures, shown as written)."""
    out: dict[int, str] = {}
    if not path.exists():
        return out
    for line in path.read_text().splitlines():
        parts = line.strip().split("\t")
        if len(parts) < 2 or parts[0].startswith("#"):
            continue
        try:
            out[int(parts[1], 16)] = parts[0].strip()
        except ValueError:
            continue
    return out


class Names:
    def __init__(self, layout: Path = REPO / "layout.tsv", functions: Path = REPO / "functions.tsv") -> None:
        self.layout = load_layout(layout)
        self.starts = [f.addr for f in self.layout]
        self.reg = load_registry(functions)

    def func(self, addr: int) -> tuple[str, bool]:
        i = bisect.bisect_right(self.starts, addr) - 1
        if i < 0 or addr >= self.layout[i].end:
            return f"0x{addr:08x} (between functions)", False
        f = self.layout[i]
        name = self.reg.get(f.addr, f.name)
        return (name, True) if addr == f.addr else (f"{name}+0x{addr - f.addr:x}", False)

    def target(self, addr: int) -> tuple[str, str]:
        if TEXT_LO <= addr < TEXT_HI:
            n, start = self.func(addr)
            return n, "code (function start)" if start else "code (inside a function)"
        kind = "data" if addr < DATA_HI else ("bss" if addr >= BSS_LO else "data/bss gap")
        if addr == IMAGE_HI:
            kind = "end of bss"
        return f"D_{addr:08X}", kind


def gpr_written(w: int) -> int | None:
    o = op(w)
    if o in (0x11, 0x12):
        return rt(w) if rs(w) in (0, 1, 2) else None
    if o in GPR_RT_WRITERS:
        return rt(w)
    if o == OP_MMI:
        return rd(w)
    if o == OP_JAL:
        return 31
    if o == OP_SPECIAL and not (funct(w) in (0x21, 0x2D) and rd(w) == rs(w)):
        return rd(w)
    return None


def scan(segs: list[tuple[int, bytes]], names: Names) -> list[tuple[int, str, int, str, str]]:
    """[(vaddr, kind, target, name, target kind)]"""
    hits = []
    for base, blob in segs:
        n = len(blob) // 4
        words = struct.unpack(f"<{n}I", blob[: n * 4])
        used = set()
        for k, w in enumerate(words):
            a = base + 4 * k
            o = op(w)
            if o in (OP_J, OP_JAL):
                t = ((a + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                if TEXT_LO <= t < TEXT_HI:
                    hits.append((a, "jal" if o == OP_JAL else "j", t, *names.target(t)))
                    used.add(k)
            elif o == OP_LUI and IMAGE_LO >> 16 <= (w & 0xFFFF) <= (IMAGE_HI + 0x8000) >> 16:
                r, upper = rt(w), (w & 0xFFFF) << 16
                for j in range(k + 1, min(n, k + 1 + WINDOW)):
                    w2 = words[j]
                    o2 = op(w2)
                    if o2 in LO_OPS and rs(w2) == r:
                        full = (upper + imm(w2)) & 0xFFFFFFFF
                        if IMAGE_LO <= full <= IMAGE_HI:
                            hits.append((base + 4 * j, "%hi/%lo", full, *names.target(full)))
                            used.update((k, j))
                    if w2 == JR_RA or gpr_written(w2) == r:
                        break
        for k, w in enumerate(words):
            if k not in used and IMAGE_LO <= w <= IMAGE_HI:
                hits.append((base + 4 * k, "word", w, *names.target(w)))
    return hits


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file")
    ap.add_argument("--base", default="0x00F20000", help="load address of a raw file (default 0x00F20000)")
    ap.add_argument("--all", action="store_true", help="list every hit (default: code hits all, words summarized)")
    ap.add_argument("--layout", default=str(REPO / "layout.tsv"), help="the repo's layout.tsv (default: next to tools/)")
    ap.add_argument("--functions", default=str(REPO / "functions.tsv"), help="the repo's functions.tsv (optional)")
    a = ap.parse_args()
    path = Path(a.file)
    fmt, segs = load_segments(path, int(a.base, 0))
    names = Names(Path(a.layout), Path(a.functions))
    hits = scan(segs, names)
    print(f"{path.name}: {fmt}, {sum(len(b) for _a, b in segs)} bytes")
    by_kind = Counter(h[1] for h in hits)
    strong = [h for h in hits if h[1] != "word"]
    words = [h for h in hits if h[1] == "word"]
    for h in sorted(strong):
        print(f"  0x{h[0]:08x}  {h[1]:8} 0x{h[2]:08x}  {h[3]}  [{h[4]}]")
    shown = words if a.all else [h for h in words if h[4] == "code (function start)"]
    if shown:
        print(f"  data words{'' if a.all else ' pointing at function starts (--all for every word)'}:")
        for h in sorted(shown):
            print(f"  0x{h[0]:08x}  word     0x{h[2]:08x}  {h[3]}  [{h[4]}]")
    print("summary:")
    for kind in ("jal", "j", "%hi/%lo", "word"):
        sub = [h for h in hits if h[1] == kind]
        if not sub:
            continue
        tk = Counter(h[4] for h in sub)
        print(f"  {kind:8} {by_kind[kind]:6} hits, {len({h[2] for h in sub}):5} distinct targets  "
              + ", ".join(f"{k}: {v}" for k, v in sorted(tk.items())))
    if not hits:
        print("  no reference into 0x00100000-0x00675018 found")
    funcs = sorted({h[3] for h in strong if h[4] == "code (function start)"})
    if funcs:
        print(f"  main-ELF functions called or addressed by code: {len(funcs)}: {', '.join(funcs[:40])}"
              + (" ..." if len(funcs) > 40 else ""))
    return 0


if __name__ == "__main__":
    sys.exit(main())
