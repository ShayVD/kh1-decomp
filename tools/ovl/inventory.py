#!/usr/bin/env python3
"""Inventory of an EE overlay (phase 5, docs/vita-port-plan.md section 3:
the overlays must be decompiled for the port; dktitle.x first).

Run it on an overlay you extracted from your own disc
(tools/shift/extract_kingdom.py): it loads at 0x00F20000 like every KH1
overlay, the entry is the first byte.

  python3 -I tools/ovl/inventory.py FILE.x [--base 0xF20000]
      [--tsv out/ovl/NAME.layout.tsv] [--strings]

It finds the overlay's own functions (the entry, every jal target inside the
file, and what follows an unconditional jump and its delay slot when no
branch reaches past it), the end of the code (after the last function's return:
the rest is data), and for each function its size, calls inside the overlay,
calls into the main ELF (named from layout.tsv / functions.tsv, game or SDK
segment) and %hi/%lo references to main-ELF data and to its own data.
--tsv writes the functions as a layout.tsv (addr, end, size, name) for a
future overlay build. --strings lists the offsets and lengths of the ASCII
strings in the data part (never their text).

Reads only the file given and prints addresses and names, never its bytes.

  python3 -I tools/ovl/inventory.py --selftest
checks the function finder on a slice of the main ELF (SLPS_251.98 in the
repo root) against layout.tsv.
"""
from __future__ import annotations

import argparse
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / "tools" / "shift"))
import scan_overlay as so  # noqa: E402

SDK_LO = 0x0024F2E0
NOP = 0
# beq bne blez bgtz, their likely forms, regimm (bltz / bgez ...)
BRANCH_OPS = {0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17, 0x01}


def find_functions(base: int, words: tuple[int, ...]) -> tuple[list[int], int]:
    """(sorted function starts, end of code).

    A function starts at the entry, at every jal target inside the file, and
    after an unconditional transfer (jr ra, jr reg, j out of the current
    function, b) and its delay slot, over nop padding, when no branch seen
    since the current function's start lands at or after that point. On the
    main ELF (--selftest) this finds every layout.tsv start, with under 1%
    extra splits (a j tail inside a function)."""
    n = len(words)
    end_code = base
    starts = {base}
    cur = base
    max_target = 0
    for k in range(n):
        w = words[k]
        a = base + 4 * k
        o = so.op(w)
        if o in (so.OP_J, so.OP_JAL):
            t = ((a + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
            if o == so.OP_JAL and base <= t < base + 4 * n:
                starts.add(t)
        if o in BRANCH_OPS or (o in (0x11, 0x12) and so.rs(w) == 8):
            max_target = max(max_target, a + 4 + (so.imm(w) << 2))
        if w == so.JR_RA:
            end_code = a + 8
        uncond = (w == so.JR_RA or (o == so.OP_SPECIAL and so.funct(w) == 8)
                  or (o == so.OP_J and not cur <= (((a + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)) <= a)
                  or (o == 0x04 and so.rs(w) == 0 and so.rt(w) == 0))
        if uncond and max_target < a + 8:
            j = k + 2
            while j < n and words[j] == NOP:
                j += 1
            if j < n:
                starts.add(base + 4 * j)
                cur = base + 4 * j
                max_target = 0
    starts = sorted(s for s in starts if s < end_code)
    return starts, end_code


def inventory(base: int, blob: bytes, names: so.Names):
    n = len(blob) // 4
    words = struct.unpack(f"<{n}I", blob[: n * 4])
    starts, end_code = find_functions(base, words)
    top = base + 4 * n
    bounds = starts + [end_code]
    funcs = []
    for i, s in enumerate(starts):
        e = bounds[i + 1]
        funcs.append({"addr": s, "end": e, "own_calls": set(), "main_calls": Counter(),
                      "main_data": set(), "own_data": set()})

    def owner(a: int):
        lo, hi = 0, len(starts) - 1
        while lo <= hi:
            m = (lo + hi) // 2
            if starts[m] <= a:
                lo = m + 1
            else:
                hi = m - 1
        return funcs[hi] if hi >= 0 and a < funcs[hi]["end"] else None

    for k in range((end_code - base) // 4):
        w = words[k]
        a = base + 4 * k
        f = owner(a)
        if f is None:
            continue
        o = so.op(w)
        if o in (so.OP_J, so.OP_JAL):
            t = ((a + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
            if base <= t < top and o == so.OP_JAL:
                f["own_calls"].add(t)
            elif so.TEXT_LO <= t < so.TEXT_HI:
                f["main_calls"][t] += 1
        elif o == so.OP_LUI:
            r, upper = so.rt(w), (w & 0xFFFF) << 16
            for j in range(k + 1, min((end_code - base) // 4, k + 1 + so.WINDOW)):
                w2 = words[j]
                if so.op(w2) in so.LO_OPS and so.rs(w2) == r:
                    full = (upper + so.imm(w2)) & 0xFFFFFFFF
                    if so.IMAGE_LO <= full <= so.IMAGE_HI:
                        f["main_data"].add(full)
                    elif base <= full < top:
                        f["own_data"].add(full)
                if w2 == so.JR_RA or so.gpr_written(w2) == r:
                    break
    return funcs, end_code, top


def strings(blob: bytes, start: int, minlen: int = 4):
    out, k = [], start
    while k < len(blob):
        j = k
        while j < len(blob) and 0x20 <= blob[j] < 0x7F:
            j += 1
        if j - k >= minlen and j < len(blob) and blob[j] == 0:
            out.append((k, j - k))
        k = j + 1
    return out


def report(path_name: str, base: int, blob: bytes, names: so.Names, tsv: str | None, show_strings: bool) -> None:
    funcs, end_code, top = inventory(base, blob, names)
    print(f"{path_name}: {len(blob)} bytes at 0x{base:08x}; code 0x{base:08x}-0x{end_code:08x} "
          f"({end_code - base} bytes), data 0x{end_code:08x}-0x{top:08x} ({top - end_code} bytes)")
    print(f"functions: {len(funcs)}")
    main_calls = Counter()
    main_data = set()
    for f in funcs:
        main_calls.update(f["main_calls"])
        main_data |= f["main_data"]
    for f in funcs:
        mc = ", ".join(names.func(t)[0] for t in sorted(f["main_calls"]))
        print(f"  0x{f['addr']:08x} {f['end'] - f['addr']:6d}  own calls {len(f['own_calls']):3d}  "
              f"main calls {sum(f['main_calls'].values()):3d}  main data {len(f['main_data']):3d}  "
              f"own data {len(f['own_data']):3d}" + (f"  -> {mc}" if mc else ""))
    game = {t: c for t, c in main_calls.items() if t < SDK_LO}
    sdk = {t: c for t, c in main_calls.items() if t >= SDK_LO}
    print(f"main-ELF functions called: {len(main_calls)} ({len(game)} game, {len(sdk)} SDK), "
          f"{sum(main_calls.values())} call sites")
    for label, d in (("game", game), ("SDK", sdk)):
        if d:
            print(f"  {label}: " + ", ".join(f"{names.func(t)[0]} x{c}" for t, c in
                                            sorted(d.items(), key=lambda kv: (-kv[1], kv[0]))))
    print(f"main-ELF data named by %hi/%lo: {len(main_data)}: "
          + ", ".join(f"D_{a:08X}" for a in sorted(main_data)))
    st = strings(blob, end_code - base)
    print(f"strings in the data part: {len(st)}")
    if show_strings:
        for off, ln in st:
            print(f"  0x{base + off:08x} {ln}")
    if tsv:
        p = Path(tsv)
        p.parent.mkdir(parents=True, exist_ok=True)
        with p.open("w") as fh:
            for f in funcs:
                fh.write(f"{f['addr']:08x}\t{f['end']:08x}\t{f['end'] - f['addr']}\tovl_{f['addr']:08x}\n")
        print(f"wrote {p}")


def selftest() -> int:
    elf = REPO / "SLPS_251.98"
    if not elf.exists():
        print("selftest: SLPS_251.98 not in the repo root")
        return 1
    _fmt, segs = so.load_segments(elf, 0)
    names = so.Names()
    bad = 0
    # game-code slices of overlay size, each starting at a function
    for lo, hi in ((0x00109000, 0x00121000), (0x00180000, 0x001A0000), (0x001C0000, 0x00200000)):
        lo = min(f.addr for f in names.layout if f.addr >= lo)
        hi = min(f.addr for f in names.layout if f.addr >= hi)
        seg_base, blob = next((b, d) for b, d in segs if b <= lo < b + len(d))
        piece = blob[lo - seg_base: hi - seg_base]
        words = struct.unpack(f"<{len(piece) // 4}I", piece)
        found, end = find_functions(lo, words)
        fs = set(found)
        ts = {f.addr for f in names.layout if lo <= f.addr < end}
        print(f"selftest 0x{lo:08x}-0x{hi:08x}: layout.tsv {len(ts)} functions, found {len(fs)}, "
              f"missed {len(ts - fs)}, extra {len(fs - ts)}")
        bad += len(ts - fs) > 0 or len(fs - ts) > len(ts) // 50
    print("selftest:", "FAIL" if bad else "OK")
    return 1 if bad else 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file", nargs="?")
    ap.add_argument("--base", default="0x00F20000")
    ap.add_argument("--tsv")
    ap.add_argument("--strings", action="store_true")
    ap.add_argument("--selftest", action="store_true")
    a = ap.parse_args()
    if a.selftest:
        return selftest()
    if not a.file:
        ap.error("FILE.x is needed (or --selftest)")
    path = Path(a.file)
    _fmt, segs = so.load_segments(path, int(a.base, 0))
    names = so.Names()
    for base, blob in segs:
        report(path.name, base, blob, names, a.tsv, a.strings)
    return 0


if __name__ == "__main__":
    sys.exit(main())
