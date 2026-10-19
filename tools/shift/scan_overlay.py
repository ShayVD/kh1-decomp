#!/usr/bin/env python3
"""Which addresses of the main ELF does an EE overlay use? (shiftable plan
step 9, risk 1). Run it on overlay files (.x) you extracted from your own
disc: dkmovie.x, dktitle.x, gb.x, wm.x, xl_limit.x, xs_dh_break.x.

  python3 -I tools/shift/scan_overlay.py FILE.x [--base 0xF20000] [--all]

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

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import kh1tool as K  # noqa: E402
import mips  # noqa: E402

TEXT_LO, TEXT_HI = 0x00100000, 0x00272C70
IMAGE_LO, IMAGE_HI = 0x00100000, 0x00675018
DATA_HI, BSS_LO = 0x00494068, 0x00494080
WINDOW = 64
LO_OPS = {0x09} | mips.OP_LOADS | mips.OP_STORES | mips.OP_VU_MEM | {mips.OP_LQ, mips.OP_SQ}


def load_segments(path: Path, base: int) -> tuple[str, list[tuple[int, bytes]]]:
    data = path.read_bytes()
    if data[:4] == b"\x7fELF":
        from elf32 import PT_LOAD, Elf
        elf = Elf(data, path)
        segs = [(s.vaddr, data[s.offset: s.offset + s.filesz]) for s in elf.segments
                if s.type == PT_LOAD and s.filesz]
        return "ELF", segs
    return f"raw at 0x{base:08x}", [(base, data)]


class Names:
    def __init__(self) -> None:
        self.layout = K.load_layout()
        self.starts = [f.addr for f in self.layout]
        self.reg = {a: s for s, a in K.load_registry().items()}

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
    o = mips.op(w)
    if o in (0x11, 0x12):
        return mips.rt(w) if mips.rs(w) in (0, 1, 2) else None
    if o in K.GPR_RT_WRITERS:
        return mips.rt(w)
    if o == mips.OP_MMI:
        return mips.rd(w)
    if o == mips.OP_JAL:
        return 31
    if o == mips.OP_SPECIAL and not (mips.funct(w) in (0x21, 0x2D) and mips.rd(w) == mips.rs(w)):
        return mips.rd(w)
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
            o = mips.op(w)
            if o in (mips.OP_J, mips.OP_JAL):
                t = ((a + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                if TEXT_LO <= t < TEXT_HI:
                    hits.append((a, "jal" if o == mips.OP_JAL else "j", t, *names.target(t)))
                    used.add(k)
            elif o == mips.OP_LUI and IMAGE_LO >> 16 <= (w & 0xFFFF) <= (IMAGE_HI + 0x8000) >> 16:
                r, upper = mips.rt(w), (w & 0xFFFF) << 16
                for j in range(k + 1, min(n, k + 1 + WINDOW)):
                    w2 = words[j]
                    o2 = mips.op(w2)
                    if o2 in LO_OPS and mips.rs(w2) == r:
                        full = (upper + mips.imm(w2)) & 0xFFFFFFFF
                        if IMAGE_LO <= full <= IMAGE_HI:
                            hits.append((base + 4 * j, "%hi/%lo", full, *names.target(full)))
                            used.update((k, j))
                    if w2 == K.JR_RA or gpr_written(w2) == r:
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
    a = ap.parse_args()
    path = Path(a.file)
    fmt, segs = load_segments(path, int(a.base, 0))
    names = Names()
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
