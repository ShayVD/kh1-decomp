#!/usr/bin/env python3
"""Data names some user declares larger than their extent, as one piece (phase 4, step 4).

  python3 -I tools/shift/merge_pieces.py [--name D_X ...] [--apply]

define_pieces.py skips a name when a C user declares it larger than its extent:
that user reaches the next names through it (a struct whose fields are named on
their own, or an array indexed past the next name). When everything the larger
object covers is already a piece (or unclaimed bytes), this makes one piece of
the whole object instead, `PIECE_BEGIN D_X, size` with each inner name as a
`PIECE_LABEL D_X, D_inner, off` (include/data/piece.inc): a global label inside
the section, so the inner names move with the object when it floats.

The size is the largest declaration, grown until no piece straddles its end
(the pieces it absorbs keep their own .word relocations, at their offset; the
bytes that were no piece get theirs from data_relocs.tsv, as define_pieces.py
--pointers writes them). A name is refused when the object would cover a
variable C defines or a compiled rodata block. Absorbed pieces leave their
module; their header declarations stay (a label is declared like a variable).

--group D_X:SIZE merges the pieces from D_X through D_X + SIZE into one piece whatever the
declarations say (a record the runtime showed is one object: session 20's object/table records,
the staging arena). --split does the same for every chain split_check.py reports (adjacent
pieces cut at a non-16-aligned boundary with a .word pointing at one of them), from the chain's
first piece to the end of its last, so the pair floats as one object instead of staying in place.
With either, only those groups are merged. The plan reads out/gen/data.tsv (placed
variables) from the last `make`: run `make` after each --apply before planning the next.

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
import define_pieces as DP  # noqa: E402

LINE_RE = re.compile(r"^\s*(PIECE|PIECE_BEGIN|PIECE_BYTES|PIECE_LABEL|PIECE_END)\s+(.*?)\s*(/\*.*\*/)?\s*$")
BIG_RE = re.compile(r"declared larger than the extent \((0x[0-9a-f]+) > (0x[0-9a-f]+)\)")


class Piece:
    def __init__(self, name: str, size: int, align: int, note: str):
        self.name, self.size, self.align, self.note = name, size, align, note
        self.addr = int(name[2:], 16)
        self.words: list[tuple[int, str]] = []   # (offset, expr)
        self.labels: list[tuple[int, str]] = []  # (offset, name)


def read_module(path: Path) -> tuple[list[str], list[Piece]]:
    head, pieces, cur, pos = [], [], None, 0
    for ln in path.read_text().splitlines():
        m = LINE_RE.match(ln)
        if not m and not ln.strip().startswith(".word"):
            if not pieces and cur is None:
                head.append(ln)
            continue
        if not m:  # .word inside PIECE_BEGIN/END
            cur.words.append((pos, ln.strip()[len(".word"):].strip()))
            pos += 4
            continue
        kind, args, note = m.group(1), [x.strip() for x in m.group(2).split(",")], m.group(3) or ""
        if kind in ("PIECE", "PIECE_BEGIN"):
            p = Piece(args[0], int(args[1], 0), int(args[2]), note)
            pieces.append(p)
            cur, pos = (p, 0) if kind == "PIECE_BEGIN" else (None, 0)
        elif kind == "PIECE_BYTES":
            pos = int(args[1], 0) + int(args[2], 0)
        elif kind == "PIECE_LABEL":
            cur.labels.append((int(args[2], 0), args[1]))
        elif kind == "PIECE_END":
            cur = None
    while head and not head[-1].strip():
        head.pop()
    return head, pieces


def piece_text(p: Piece) -> list[str]:
    note = f"  {p.note}" if p.note else ""
    if not p.words and not p.labels:
        return [f"\tPIECE {p.name}, 0x{p.size:x}, {p.align}{note}"]
    out = [f"\tPIECE_BEGIN {p.name}, 0x{p.size:x}, {p.align}{note}"]
    ev = sorted([(o, 0, n) for o, n in p.labels] + [(o, 1, e) for o, e in p.words])
    pos = 0
    for off, kind, what in ev:
        if off > pos:
            out.append(f"\tPIECE_BYTES {p.name}, 0x{pos:x}, 0x{off - pos:x}")
            pos = off
        if kind == 0:
            out.append(f"\tPIECE_LABEL {p.name}, {what}, 0x{off:x}")
        else:
            out.append(f"\t.word {what}")
            pos = off + 4
    if p.size > pos:
        out.append(f"\tPIECE_BYTES {p.name}, 0x{pos:x}, 0x{p.size - pos:x}")
    out.append(f"\tPIECE_END {p.name}, 0x{p.size:x}")
    return out


def split_chains(mods) -> dict[str, int]:
    """split_check.py's pairs as whole objects: each maximal run of adjacent pieces whose inner
    boundaries are not 16-aligned, when a .word points at one of them -> (first piece, run size)."""
    pointed = {e.split("+")[0].strip("() ") for _h, ps in mods.values() for p in ps for _o, e in p.words}
    out: dict[str, int] = {}
    for _h, ps in mods.values():
        ps = sorted(ps, key=lambda q: q.addr)
        i = 0
        while i < len(ps):
            j = i
            while j + 1 < len(ps) and ps[j].addr + ps[j].size == ps[j + 1].addr and ps[j + 1].addr % 16:
                j += 1
            run = ps[i:j + 1]
            if j > i and any(q.name in pointed or any(n in pointed for _o, n in q.labels) for q in run):
                out[ps[i].name] = ps[j].addr + ps[j].size - ps[i].addr
            i = j + 1
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--owners", default=str(ROOT / "out/shift/data_owners.tsv"))
    ap.add_argument("--name", action="append", default=[])
    ap.add_argument("--group", action="append", default=[], metavar="D_X:SIZE")
    ap.add_argument("--split", action="store_true")
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()
    owners = Path(a.owners)
    verdicts = {"single", "single+p", "shared"}
    big: dict[str, int] = {}
    for ptr in (False, True):
        _plans, skip = DP.plan(owners, verdicts, a.name, set(), ptr)
        for n, why in skip:
            m = BIG_RE.search(why)
            if m:
                big[n] = int(m.group(1), 16)
    mods: dict[str, tuple[list[str], list[Piece]]] = {}
    for src in sorted((ROOT / "src/data").glob("data_*.s")):
        mods[src.stem] = read_module(src)
    pieces = {p.name: (mod, p) for mod, (_h, ps) in mods.items() for p in ps}
    if a.group or a.split:
        big = {}
        for g in a.group:
            n, sz = g.split(":")
            big[n] = int(sz, 0)
        if a.split:
            big.update(split_chains(mods))
    blocks = DP.placed_blocks()  # (start, end, what): variables and compiled rodata
    names = {}  # every D_ name data_owners.py knows, by address
    for ln in owners.read_text().splitlines()[1:]:
        f = ln.split("\t")
        names[int(f[0], 16)] = f[1]
    relocs = DP.reloc_rows()
    words = sorted(relocs)
    import kh1tool as K
    layout = {f.name: f.addr for f in K.load_layout()}
    registry = K.load_registry()

    absorbed: set[str] = set()
    merged: list[tuple[Piece, list[str]]] = []
    for name in sorted(big, key=lambda n: int(n[2:], 16)):
        if name in absorbed:
            continue
        x = int(name[2:], 16)
        size, why = big[name], None
        while True:
            grown = size
            for s, e, what in blocks:
                if x < s < x + size or s <= x < e:
                    if what not in pieces:
                        why = f"covers {what} (0x{s:08x}), which is no piece"
                        break
                    grown = max(grown, e - x)
            for ad, n in names.items():
                if x < ad < x + size and n in big:
                    grown = max(grown, ad - x + big[n])
            if why or grown == size:
                break
            size = grown
        if why:
            print(f"-\t{name}\tskip\t{why}")
            continue
        inner = [what for s, e, what in blocks if x <= s < x + size]
        p = Piece(name, size, DP.piece_align(x, size), "/* untyped: merged (a user declares it larger "
                  f"than the next name): {', '.join(inner) if inner else 'no inner pieces'} */")
        covered = []
        for n in inner:
            _mod, q = pieces[n]
            d = q.addr - x
            if n != name:  # the group's first piece is the merged piece itself
                p.labels.append((d, n))
            p.labels += [(d + o, ln) for o, ln in q.labels]
            p.words += [(d + o, e) for o, e in q.words]
            covered.append((q.addr, q.addr + q.size))
        label_names = {n for _o, n in p.labels}
        for ad, n in sorted(names.items()):
            if x < ad < x + size and n not in label_names:
                p.labels.append((ad - x, n))
        # bytes that were no piece: their data_relocs rows become .word (tier x stays bytes)
        vars_ = sorted([(s, e, w) for s, e, w in blocks if w not in inner] + [(x, x + size, name)])
        for w in words[bisect.bisect_left(words, x):bisect.bisect_left(words, x + size)]:
            if any(s <= w < e for s, e in covered) or relocs[w][3] == "x":
                continue
            if w + 4 > x + size:
                print(f"-\t{name}\tskip\ta data_relocs word straddles the end")
                break
            p.words.append((w - x, DP.word_expr(relocs[w], vars_, layout, registry)))
        else:
            p.labels = sorted(set(p.labels))
            p.words.sort()
            absorbed |= set(inner) | {n for _o, n in p.labels}
            merged.append((p, inner))
            print(f"{DP.module(x)}\t{name}\t0x{size:x} (declared 0x{big[name]:x})\t{len(p.labels)} labels\t"
                  f"{len(p.words)} words\t{' '.join(n for _o, n in p.labels[:6])}")
    print(f"# {len(merged)} merged pieces, {sum(len(i) for _p, i in merged)} pieces absorbed", file=sys.stderr)
    if not a.apply:
        return 0
    drop = {n for _p, inner in merged for n in inner}
    add: dict[str, list[Piece]] = {}
    for p, _inner in merged:
        add.setdefault(DP.module(p.addr), []).append(p)
    for mod in sorted(set(add) | {pieces[n][0] for n in drop}):
        head, ps = mods[mod]
        ps = [q for q in ps if q.name not in drop] + add.get(mod, [])
        ps.sort(key=lambda q: q.addr)
        text = head + [""] + [ln for q in ps for ln in piece_text(q)] + [""]
        (ROOT / "src/data" / f"{mod}.s").write_text("\n".join(text))
    return 0


if __name__ == "__main__":
    sys.exit(main())
