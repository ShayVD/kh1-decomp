#!/usr/bin/env python3
"""Shared data names as per-symbol pieces of the user's ELF (phase 4, step 4).

  python3 -I tools/shift/define_pieces.py [--owners out/shift/data_owners.tsv]
                                          [--verdict shared] [--name D_X ...]
                                          [--exclude D_X ...] [--apply]

Game data (numeric tables, strings) never enters the repo. A `data` row of
data_owners.tsv becomes a *piece*: one line `PIECE D_X, size, align` in
`src/data/data_XXXX.s` (XXXX = address bits 31..16). The macro
(include/data/piece.inc) puts it in its own section `.data.D_X` as an
`.incbin` of out/data/pieces/D_X.bin, which tools/shift/cut_pieces.py cuts
from the user's ELF at build time. kh1tool link-script places each piece at
its address like a variable C defines (`make` stays byte-identical: the bytes
are the original ones), and the shift build can float each on its own.

A name qualifies when
  - its extent (data_owners.py, clamped at the next variable already defined
    in out/gen/data.tsv, at the next compiled rodata block of
    out/gen/rodata.tsv, and at the end of the data) does not start inside
    such a block,
  - no data_relocs.tsv row (accepted or rejected) lies inside it: the piece
    holds no pointer, so its bytes mean the same wherever it goes (pointers
    *into* it are fine: shift_ld retargets them at the piece symbol),
  - no C user declares it larger than the extent (that user reaches the next
    name through it).

When every C user outside src/sdk/ declares it the same way, the declaration
goes to include/data/data_XXXX.h and those users include the header at their
end (only if the file still compiles with it), as define_shared.py does for
bss. Users that disagree keep their own extern and the header lists nothing
for that name (a comment in the .s says so).

Without --apply only the plan is printed. Nothing here reads game bytes."""
from __future__ import annotations

import argparse
import bisect
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/shift"))
from define_vars import lowbit, probe_sizes  # noqa: E402
from define_shared import BASIC, base_type, compiles_with, user_decl  # noqa: E402
from elf32 import Elf  # noqa: E402

BLOB_START, BLOB_END = 0x00272C70, 0x00494050
PIECE_RE = re.compile(r"^\s*PIECE\s+(D_[0-9A-F]{8})\s*,\s*(0x[0-9a-fA-F]+|\d+)\s*,\s*(\d+)")


def module(addr: int) -> str:
    return f"data_{addr >> 16:04X}"


def piece_align(addr: int, size: int) -> int:
    """Section alignment: MIPS gas pads a section to its alignment, so it must also
    divide the size (the shift build aligns a floated piece by its address anyway)."""
    return min(lowbit(addr), lowbit(size), 16)


def placed_blocks() -> list[tuple[int, int, str]]:
    """(start, end, what) of everything already placed in the data range:
    C-defined variables (out/gen/data.tsv) and compiled rodata (rodata.tsv)."""
    out = []
    for ln in (ROOT / "out/gen/data.tsv").read_text().splitlines()[1:]:
        a, n, _o, sz, reg = ln.split("\t")
        if reg == "data":
            out.append((int(a, 16), int(a, 16) + int(sz, 16), n))
    elves: dict[str, Elf] = {}
    for ln in (ROOT / "out/gen/rodata.tsv").read_text().splitlines()[1:]:
        a, sec, obj = ln.split("\t")
        e = elves.setdefault(obj, Elf.load(ROOT / obj))
        s = e.section(sec)
        out.append((int(a, 16), int(a, 16) + (s.size if s else 0), f"{obj}:{sec}"))
    return sorted(out)


def reloc_words() -> list[int]:
    out = []
    for line in (ROOT / "data_relocs.tsv").read_text().splitlines():
        if not line or line.startswith(("#", "offset")):
            continue
        out.append(BLOB_START + int(line.split("\t")[0], 16))
    return sorted(out)


def plan(owners: Path, verdicts: set[str], names: list[str], exclude: set[str]):
    blocks = placed_blocks()
    bstarts = [b[0] for b in blocks]
    words = reloc_words()
    done = {b[2] for b in blocks}
    rows, skip = [], []
    for ln in owners.read_text().splitlines()[1:]:
        f = ln.split("\t")
        if f[2] != "data" or f[6] not in verdicts or f[1] in done or f[1] in exclude:
            continue
        if names and f[1] not in names:
            continue
        addr, ext = int(f[0], 16), int(f[3], 16)
        i = bisect.bisect_right(bstarts, addr) - 1
        if i >= 0 and addr < blocks[i][1]:
            skip.append((f[1], f"starts inside {blocks[i][2]}"))
            continue
        end = min(addr + ext, BLOB_END)
        if i + 1 < len(blocks) and blocks[i + 1][0] < end:
            end = blocks[i + 1][0]
        ext = end - addr
        if ext <= 0:
            skip.append((f[1], "empty extent"))
            continue
        j = bisect.bisect_left(words, addr - 3)
        if j < len(words) and words[j] < end:
            skip.append((f[1], f"data_relocs row at 0x{words[j]:08x} inside the extent"))
            continue
        rows.append((addr, f[1], ext, [x for x in f[7].split(";") if x]))
    # declarations of the C users outside src/sdk/
    decls_of: dict[str, dict[tuple, list]] = {}
    unknown: dict[str, list] = {}
    need: dict[str, dict[str, str]] = {}
    for addr, name, ext, files in rows:
        ds: dict[tuple, list] = {}
        for fn in files:
            if not fn.endswith(".c") or fn.startswith("src/sdk/"):
                continue
            d, _why = user_decl(ROOT / fn, name)
            if d:
                ds.setdefault(d, []).append(fn)
            else:
                unknown.setdefault(name, []).append(fn)
        decls_of[name] = ds
        for (_t, decl), fns in ds.items():
            need.setdefault(fns[0], {})[name + "__" + str(len(need.get(fns[0], {})))] = \
                f"{name}[0]" if "[]" in decl else name
    sizes: dict[tuple[str, str], int] = {}
    for fn, exprs in need.items():
        # one expression per (file, name): the first declaration this file writes
        flat = {}
        for k, e in exprs.items():
            n = k.split("__")[0]
            flat.setdefault(n, e)
        try:
            got = probe_sizes(ROOT / fn, flat)
        except RuntimeError:
            got = {}
        for n, sz in got.items():
            sizes[(fn, n)] = sz
    out = []
    for addr, name, ext, files in rows:
        ds = decls_of[name]
        big = 0
        for (_t, decl), fns in ds.items():
            if "[]" not in decl:
                big = max(big, sizes.get((fns[0], name), 0))
        if big > ext:
            skip.append((name, f"declared larger than the extent ({big:#x} > {ext:#x})"))
            continue
        header = None
        why = ""
        if len(ds) == 1 and name not in unknown:
            (tspec, decl), _fns = next(iter(ds.items()))
            if base_type(tspec) not in BASIC:
                why = f"type {tspec} is not a common.h basic type"
            elif not re.fullmatch(r"\**\w+(\[[^\]]*\])*", decl):
                why = f"declarator {decl} not handled"
            elif "[]" in decl:
                el = sizes.get((_fns[0], name), 0)
                header = (tspec, decl) if el and ext % el == 0 else None
                why = "" if header else "element size does not divide the extent"
            else:
                header = (tspec, decl)
        elif not ds:
            why = "no C user outside src/sdk/ with one file-scope extern"
        else:
            why = "users disagree: " + " | ".join(f"{t} {d}" for t, d in sorted(ds)) + \
                  (f"; unparsed in {len(unknown.get(name, []))} file(s)" if name in unknown else "")
        cfiles = sorted({fn for fns in ds.values() for fn in fns})
        out.append((addr, name, ext, files, header, why, cfiles))
    return out, skip


def piece_lines(addr: int, name: str, ext: int, header, why: str) -> list[str]:
    note = "" if header else f"  /* untyped: {why} */"
    return [f"\tPIECE {name}, 0x{ext:x}, {piece_align(addr, ext)}{note}"]


def apply(plans) -> None:
    mods: dict[str, list] = {}
    for p in plans:
        mods.setdefault(module(p[0]), []).append(p)
    for mod, ps in sorted(mods.items()):
        src = ROOT / "src/data" / f"{mod}.s"
        hdr = ROOT / "include/data" / f"{mod}.h"
        old_lines = src.read_text().splitlines() if src.exists() else []
        have = {m.group(1): ln for ln in old_lines if (m := PIECE_RE.match(ln))}
        for addr, name, ext, _f, header, why, _c in ps:
            have[name] = piece_lines(addr, name, ext, header, why)[0]
        body = [have[n] for n in sorted(have, key=lambda n: int(n[2:], 16))]
        src.write_text("\n".join([
            f"/* Shared data names {mod[5:]}xxxx as pieces of the user's ELF (phase 4, step 4;",
            " * tools/shift/define_pieces.py). Each PIECE is its own section .data.<name>, an",
            " * .incbin of out/data/pieces/<name>.bin that tools/shift/cut_pieces.py cuts from",
            " * the ELF at build time: no game bytes are in the repo. Declarations: the header",
            f" * include/data/{mod}.h (names whose C users agree on the type). */",
            '\t.include "include/data/piece.inc"',
            "",
            *body, ""]))
        old_decls = []
        if hdr.exists():
            old_decls = [ln for ln in hdr.read_text().splitlines() if ln.startswith("extern ")]
        new = [f"extern {p[4][0]} {p[4][1]};" for p in ps if p[4]]
        decls = sorted(set(old_decls + new), key=lambda ln: re.search(r"D_([0-9A-F]{8})", ln).group(1))
        guard = f"KH1_DATA_{mod.upper()}_H"
        m2c = any(re.search(r"\bM2C_UNK", ln) for ln in decls)
        hdr.write_text("\n".join([
            f"/* Shared data names {mod[5:]}xxxx: pieces of the user's ELF defined in",
            f" * src/data/{mod}.s (phase 4, tools/shift/define_pieces.py). Only names whose",
            " * C users agree on the type are declared here; users include this at their end. */",
            f"#ifndef {guard}", f"#define {guard}", "", '#include "common.h"',
            *(['#include "m2c.h"'] if m2c else []), "", *decls, "", f"#endif /* {guard} */", ""]))
    # users: include the header where the file still compiles with it
    users: dict[str, set] = {}
    for p in plans:
        if p[4]:
            for f in p[6]:
                users.setdefault(f, set()).add(module(p[0]))
    for f, ms in sorted(users.items()):
        path = ROOT / f
        for mod in sorted(ms):
            inc = f"data/{mod}.h"
            text = path.read_text()
            if f'#include "{inc}"' in text:
                continue
            if compiles_with(path, inc):
                path.write_text(text + ("" if text.endswith("\n") else "\n") + f'#include "{inc}"\n')
                print(f"include\t{f}\t{inc}", file=sys.stderr)
            else:
                print(f"keep\t{f}\t{inc}", file=sys.stderr)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--owners", default=str(ROOT / "out/shift/data_owners.tsv"))
    ap.add_argument("--verdict", action="append", default=[], help="data_owners verdicts (default: shared)")
    ap.add_argument("--name", action="append", default=[])
    ap.add_argument("--exclude", action="append", default=[])
    ap.add_argument("--limit", type=int, default=0, help="at most N pieces (lowest addresses first)")
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    plans, skip = plan(Path(a.owners), set(a.verdict or ["shared"]), a.name, set(a.exclude))
    if a.limit:
        plans = sorted(plans)[:a.limit]
    for addr, name, ext, files, header, why, _c in sorted(plans):
        t = f"{header[0]} {header[1]}" if header else f"(untyped: {why})"
        print(f"{module(addr)}\t{name}\t0x{ext:x}\t{len(files)} users\t{t}")
    for n, why in skip:
        print(f"-\t{n}\tskip\t{why}")
    typed = sum(1 for p in plans if p[4])
    print(f"# {len(plans)} pieces ({typed} typed, {len(plans) - typed} untyped), {len(skip)} skipped",
          file=sys.stderr)
    if a.apply and plans:
        apply(plans)
    return 0


if __name__ == "__main__":
    sys.exit(main())
