#!/usr/bin/env python3
"""Data names as per-symbol pieces of the user's ELF (phase 4, step 4).

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
PIECE_RE = re.compile(r"^\s*PIECE(_BEGIN)?\s+(D_[0-9A-F]{8})\s*,\s*(0x[0-9a-fA-F]+|\d+)\s*,\s*(\d+)")
PLACEHOLDER = re.compile(r"^func_[0-9A-Fa-f]{8}$")


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


def reloc_rows() -> dict[int, tuple]:
    """data_relocs.tsv: {word address: (type, symbol, addend, tier)}."""
    out = {}
    for line in (ROOT / "data_relocs.tsv").read_text().splitlines():
        if not line or line.startswith(("#", "offset")):
            continue
        off, typ, sym, add, tier, _r = line.split("\t")
        out[BLOB_START + int(off, 16)] = (typ, sym, add, tier)
    return out


def word_expr(row, vars_: list[tuple[int, int, str]], layout: dict[str, int], registry: dict[str, int]) -> str:
    """The `.word` operand for an accepted data_relocs row: a code target by its function
    name (or func_XXXXXXXX), a data/bss target by the variable it lies in (name+offset)
    or by its D_ name. Both links resolve these names (PROVIDE / shift_ld)."""
    typ, sym, add, _tier = row
    hi = int(typ.split("+", 1)[1], 16) if "+" in typ else 0
    add = int(add, 16)
    if sym in ("D_BLOB", "D_BSS"):
        t = (BLOB_START if sym == "D_BLOB" else 0x00494080) + add
        i = bisect.bisect_right([v[0] for v in vars_], t) - 1
        if i >= 0 and t < vars_[i][1]:
            base, off = vars_[i][2], t - vars_[i][0]
        else:
            base, off = f"D_{t:08X}", 0
    else:
        base = sym if (sym in registry or PLACEHOLDER.match(sym)) else f"func_{layout[sym]:08x}"
        off = add
    off += hi
    return base + (f"+0x{off:x}" if off > 0 else (f"-0x{-off:x}" if off < 0 else ""))


def plan(owners: Path, verdicts: set[str], names: list[str], exclude: set[str], pointers: bool = False):
    blocks = placed_blocks()
    bstarts = [b[0] for b in blocks]
    relocs = reloc_rows()
    words = sorted(relocs)
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
        inside = words[j:bisect.bisect_left(words, end)]
        if inside and not pointers:
            skip.append((f[1], f"data_relocs row at 0x{inside[0]:08x} inside the extent"))
            continue
        if inside and (inside[0] < addr or inside[-1] + 4 > end):
            skip.append((f[1], "a data_relocs word straddles the extent"))
            continue
        if pointers and not inside:
            continue  # the default mode's
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
    if pointers:
        # the pointers become `.word` relocations; targets inside a variable (defined, or a
        # piece of this run) are named by it, so they follow it when it floats
        import kh1tool as K
        layout = {f.name: f.addr for f in K.load_layout()}
        registry = K.load_registry()
        vars_ = sorted([(a, a + int(sz, 16), n) for a, n, sz in
                        ((int(ln.split("\t")[0], 16), ln.split("\t")[1], ln.split("\t")[3])
                         for ln in (ROOT / "out/gen/data.tsv").read_text().splitlines()[1:])]
                       + [(p[0], p[0] + p[2], p[1]) for p in out])
        out = [p + ([(w - p[0], word_expr(relocs[w], vars_, layout, registry))
                     for w in words[bisect.bisect_left(words, p[0]):bisect.bisect_left(words, p[0] + p[2])]
                     if relocs[w][3] != "x"],) for p in out]
    else:
        out = [p + ([],) for p in out]
    return out, skip


def piece_lines(addr: int, name: str, ext: int, header, why: str, words) -> list[str]:
    note = "" if header else f"  /* untyped: {why} */"
    if not words:
        return [f"\tPIECE {name}, 0x{ext:x}, {piece_align(addr, ext)}{note}"]
    out = [f"\tPIECE_BEGIN {name}, 0x{ext:x}, {piece_align(addr, ext)}{note}"]
    pos = 0
    for off, expr in words:
        if off > pos:
            out.append(f"\tPIECE_BYTES {name}, 0x{pos:x}, 0x{off - pos:x}")
        out.append(f"\t.word {expr}")
        pos = off + 4
    if ext > pos:
        out.append(f"\tPIECE_BYTES {name}, 0x{pos:x}, 0x{ext - pos:x}")
    out.append(f"\tPIECE_END {name}, 0x{ext:x}")
    return out


def apply(plans) -> None:
    mods: dict[str, list] = {}
    for p in plans:
        mods.setdefault(module(p[0]), []).append(p)
    for mod, ps in sorted(mods.items()):
        src = ROOT / "src/data" / f"{mod}.s"
        hdr = ROOT / "include/data" / f"{mod}.h"
        old_lines = src.read_text().splitlines() if src.exists() else []
        have: dict[str, list[str]] = {}
        cur = None
        for ln in old_lines:
            m = PIECE_RE.match(ln)
            if m:
                have[m.group(2)] = [ln]
                cur = m.group(2) if m.group(1) else None
            elif cur:
                have[cur].append(ln)
                if ln.strip().startswith("PIECE_END"):
                    cur = None
        for addr, name, ext, _f, header, why, _c, words in ps:
            have[name] = piece_lines(addr, name, ext, header, why, words)
        body = [ln for n in sorted(have, key=lambda n: int(n[2:], 16)) for ln in have[n]]
        src.write_text("\n".join([
            f"/* Data names {mod[5:]}xxxx as pieces of the user's ELF (phase 4, step 4;",
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
            f"/* Data names {mod[5:]}xxxx: pieces of the user's ELF defined in",
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
    ap.add_argument("--pointers", action="store_true",
                    help="only names whose extent holds accepted data_relocs rows: they become .word relocations")
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    plans, skip = plan(Path(a.owners), set(a.verdict or ["shared"]), a.name, set(a.exclude), a.pointers)
    if a.limit:
        plans = sorted(plans)[:a.limit]
    for addr, name, ext, files, header, why, _c, words in sorted(plans):
        t = f"{header[0]} {header[1]}" if header else f"(untyped: {why})"
        w = f"\t{len(words)} pointers: " + " ".join(e for _o, e in words[:4]) if words else ""
        print(f"{module(addr)}\t{name}\t0x{ext:x}\t{len(files)} users\t{t}{w}")
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
