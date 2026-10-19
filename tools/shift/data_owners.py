#!/usr/bin/env python3
"""Who uses each data/bss address (phase 4 planning, docs/shiftable-plan.md "Phase 4").

  python3 -I tools/shift/data_owners.py [--link out/shift] [--out out/shift/data_owners.tsv]
                                       [--file SRC] [--summary]

Reads the M0 link (`make shift`; `ld -q` keeps the relocations) and lists, for
every D_ name the code references, the addresses code builds from it (HI16/LO16
pairs, R_MIPS_32 words), the source files those references come from, and the
data-blob pointers (data_relocs.tsv rows, emitted as `.word D_BLOB+x` /
`D_BSS+x`) that point into it. An object's extent is from its own address to
the next "anchor" (any D_ name's address or any data pointer's target): an
upper bound on its size, since nothing else is known to start before it.

Rows (one per D_ name, by address): addr, region (data/bss), extent, max
offset code reaches from it (built address - addr, +4), files (`;`), number of
blob pointers into it, other names that land inside it, and a verdict:

  single   every reference into the extent comes from one source file and no
           blob pointer points into it: can become a real definition in that
           file, and later move freely
  single+p one file, but blob pointers point into it: a definition at the
           original blob/bss offset is fine; moving it needs those pointers
           relocated against the new symbol
  shared   more than one file: belongs in a shared module (or a header + one
           definition)

--file SRC prints only the names SRC references, with that verdict.
Nothing here reads or prints game bytes; only addresses, names and counts."""
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
sys.path.insert(0, str(TOOLS / "shift"))
import kh1tool as K  # noqa: E402
import mips  # noqa: E402
from elf32 import R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16, Elf  # noqa: E402
from shift_cmp import read_map, sext, source_of  # noqa: E402

BLOB_START, BSS_START, IMAGE_END = 0x00272C70, 0x00494080, 0x00675018
DATA_RE = re.compile(r"^D_([0-9A-Fa-f]{8})$")


def code_refs(link: Path):
    """(target address, D_ name, source file) for every reference in .text and
    compiled rodata to a D_ name inside the image."""
    elf = Elf.load(link / "kh1-shift.linked.elf")
    syms = elf.symbols()
    smap = read_map(link / "kh1-shift.map")
    pieces = sorted((a, a + s, source_of(k[0])) for k, (a, s, _o) in smap.items() if s)
    starts = [p[0] for p in pieces]

    def src_at(addr: int) -> str:
        i = bisect.bisect_right(starts, addr) - 1
        return pieces[i][2] if i >= 0 and addr < pieces[i][1] else "?"

    out = []
    for sec in elf.sections:
        if sec.name not in (".text", ".data"):
            continue
        body = elf.section_bytes(sec)
        rel = elf.relocations(sec)
        his = [(off, si) for off, typ, si in rel if typ == R_MIPS_HI16]

        def word(addr: int) -> int:
            return struct.unpack_from("<I", body, addr - sec.addr)[0]
        for off, typ, si in rel:
            name = syms[si].name if si < len(syms) else ""
            if not DATA_RE.match(name):
                continue
            if typ == R_MIPS_32:
                target = word(off)
            elif typ == R_MIPS_LO16:
                w = word(off)
                reg = mips.rs(w)
                src = src_at(off)
                cands = [h for h in reversed(his) if h[0] < off and src_at(h[0]) == src] + \
                        [h for h in his if h[0] > off and src_at(h[0]) == src]
                hi = None
                for test in (lambda h: h[1] == si and mips.rt(word(h[0])) == reg, lambda h: h[1] == si):
                    hi = next((h[0] for h in cands if test(h)), None)
                    if hi is not None:
                        break
                if hi is None:
                    continue
                target = (((word(hi) & 0xFFFF) << 16) + sext(w & 0xFFFF)) & 0xFFFFFFFF
            else:
                continue
            if BLOB_START <= target <= IMAGE_END:
                out.append((target, name, src_at(off)))
    return out


def blob_ptrs(path: Path) -> list[tuple[int, int]]:
    """(word address, target address) of accepted data_relocs.tsv rows into data/bss."""
    out = []
    for line in path.read_text().splitlines():
        if not line or line.startswith(("#", "offset")):
            continue
        off, _typ, sym, addend, tier, _r = line.split("\t")
        if tier == "x" or sym not in ("D_BLOB", "D_BSS"):
            continue
        base = BLOB_START if sym == "D_BLOB" else BSS_START
        out.append((BLOB_START + int(off, 16), base + int(addend, 16)))
    return out


def analyse(link: Path, relocs: Path):
    refs = code_refs(link)
    ptrs = blob_ptrs(relocs)
    names: dict[str, int] = {}
    for _t, n, _s in refs:
        names[n] = int(DATA_RE.match(n).group(1), 16)
    anchors = sorted(set(names.values()) | {t for _w, t in ptrs} | {BSS_START, IMAGE_END})
    by_target = sorted(refs)
    targets = [r[0] for r in by_target]
    ptr_targets = sorted(t for _w, t in ptrs)
    rows = []
    for n, a in sorted(names.items(), key=lambda kv: kv[1]):
        i = bisect.bisect_right(anchors, a)
        end = anchors[i] if i < len(anchors) else IMAGE_END
        if a < BSS_START <= end:
            end = BSS_START
        inside = by_target[bisect.bisect_left(targets, a):bisect.bisect_left(targets, end)]
        files = sorted({s for _t, _n, s in inside})
        own = [t for t, nn, _s in by_target if nn == n]
        reach = max(own) - a + 4 if own else 0
        others = sorted({nn for _t, nn, _s in inside if nn != n})
        np = bisect.bisect_left(ptr_targets, end) - bisect.bisect_left(ptr_targets, a)
        verdict = "shared" if len(files) > 1 else ("single+p" if np else "single")
        rows.append(dict(name=n, addr=a, region="bss" if a >= BSS_START else "data", extent=end - a,
                         reach=reach, files=files, ptrs=np, others=others, verdict=verdict))
    return rows


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--link", type=Path, default=K.OUT / "shift")
    ap.add_argument("--data-relocs", type=Path, default=K.ROOT / "data_relocs.tsv")
    ap.add_argument("--out", type=Path, default=K.OUT / "shift" / "data_owners.tsv")
    ap.add_argument("--file", help="only the names this source file references")
    ap.add_argument("--summary", action="store_true", help="counts per verdict and region, best files")
    a = ap.parse_args()
    if not (a.link / "kh1-shift.linked.elf").exists():
        sys.exit("error: no M0 link; run `make shift` first")
    rows = analyse(a.link, a.data_relocs)
    a.out.write_text("addr\tname\tregion\textent\treach\tptrs_in\tverdict\tfiles\tothers_inside\n" + "".join(
        f"{r['addr']:08x}\t{r['name']}\t{r['region']}\t0x{r['extent']:x}\t0x{r['reach']:x}\t{r['ptrs']}\t"
        f"{r['verdict']}\t{';'.join(r['files'])}\t{';'.join(r['others'])}\n" for r in rows))
    if a.file:
        for r in rows:
            if a.file in r["files"]:
                print(f"{r['addr']:08x} {r['name']:12} {r['region']:4} extent 0x{r['extent']:<6x} reach 0x{r['reach']:<5x} "
                      f"ptrs {r['ptrs']:<3} {r['verdict']:8} {' '.join(f for f in r['files'] if f != a.file)}")
    if a.summary or not a.file:
        c = collections.Counter((r["region"], r["verdict"]) for r in rows)
        for (reg, v), n in sorted(c.items()):
            print(f"{reg:4} {v:8} {n:5}")
        per_file = collections.defaultdict(lambda: [0, 0, 0])
        for r in rows:
            for f in r["files"]:
                per_file[f][0] += 1
                if r["verdict"] != "shared":
                    per_file[f][1] += 1
                    per_file[f][2] += r["extent"] if r["region"] == "bss" else 0
        best = sorted(per_file.items(), key=lambda kv: (-(kv[1][1] == kv[1][0]), -kv[1][1]))
        print("files whose every referenced name is single-owner (names, single-owner, bss bytes):")
        for f, (n, s, b) in [kv for kv in best if kv[1][0] == kv[1][1]][:25]:
            print(f"  {f}: {n} names, 0x{b:x} bss bytes")
        print(f"wrote {a.out.relative_to(K.ROOT) if a.out.is_relative_to(K.ROOT) else a.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
