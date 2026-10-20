#!/usr/bin/env python3
"""Generate the link script of the shiftable build (docs/shiftable-plan.md, step 6).

  python3 -I tools/shift/shift_ld.py missing
      print the layout functions no source places (input for an asm export)
  python3 -I tools/shift/shift_ld.py gen [--asm-obj O ...] [--aliases F ...]
      write out/shift/kh1-shift.ld, out/shift/blob.s, out/shift/objects.lst,
      out/shift/expected.tsv

Unlike kh1.ld (every function pinned at its original address, everything
else PROVIDEd at its original address), this script links:

- .text: every placed `.text.<fn>` section in original address order, with
  no fixed addresses. Gaps are reproduced with `. = ALIGN(n)` (the smallest
  power of two that gives the original start), so moving the whole text by a
  multiple of 64 keeps them; only a gap no alignment explains becomes
  `. += n` (reported).
- .data: the file-backed data after code as one blob (out/shift/blob.s,
  `.incbin` chunks of out/shift/data/main.bin), with holes where compiled
  `.rodata.*` sections (out/gen/rodata.tsv) are placed at the same blob
  offset. D_BLOB is its start.
- Variables defined in C (out/gen/data.tsv, phase 4): one in the data range
  fills a hole at its blob offset, like compiled rodata; one in the bss range
  is placed at its offset from D_BSS inside .bss. Both move with data/bss.
- .bss: NOBITS, D_BSS at its start, sized like the original (up to _end).
- Every name the objects reference but do not define gets an explicit,
  position-independent definition: code addresses become a label
  `name = . + off;` next to the function that contains them (aliases,
  mid-function entry points, statics referenced by placeholder), data
  `D_X = D_BLOB + off`, bss `D_X = D_BSS + off`. Only addresses outside the
  image (fixed buffers, kernel RAM, hardware registers) stay absolute.
  There is no PROVIDE: a name with no definition is a link error.
- .ctx (CONTEXT_ONLY copies) and unplaced rodata are discarded (a reference
  to them from placed code is a link error); stray .text/.data/.bss input
  goes to .shift_orphan, which shift_elf.py requires to be empty.

Paths of extra inputs are parameters, so the exports and alias table of the
symbolic-asm work (s13s1) drop in without changing this script."""
from __future__ import annotations

import argparse
import bisect
import json
import re
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import kh1tool as K  # noqa: E402
from elf32 import Elf  # noqa: E402

SHIFT = K.OUT / "shift"
DATA_RE = re.compile(r"^D_([0-9A-Fa-f]{8})$")
ALIAS_RE = re.compile(r"^\s*([A-Za-z_.$][\w.$]*)\s*=\s*[^;]+;")
MAX_ALIGN = 4096


@dataclass
class Placed:
    addr: int          # original address
    name: str          # symbol (function) or section (rodata)
    obj: str           # object path relative to the repo root
    section: str
    size: int
    align: int
    region: str = ""   # variables defined in C: "data" or "bss"


def rel(p: Path | str) -> str:
    p = Path(p)
    try:
        return p.resolve().relative_to(K.ROOT.resolve()).as_posix()
    except ValueError:
        return p.as_posix()


def addralign(elf: Elf, index: int) -> int:
    return struct.unpack_from("<I", elf.data, elf._shdr_off(index) + 32)[0] or 1


def name_address(name: str, registry: dict[str, int]) -> int | None:
    if name in registry:
        return registry[name]
    m = K.PLACEHOLDER_RE.match(name) or DATA_RE.match(name)
    return int(m.group(1), 16) if m else None


def objects_mk_objs() -> list[str]:
    mk = K.GEN / "objects.mk"
    if not mk.exists():
        sys.exit("error: out/gen/objects.mk missing; run `make` first")
    for line in mk.read_text().splitlines():
        if line.startswith("OBJS :="):
            return [SUBST.get(o, o) for o in line.split(":=", 1)[1].split()]
    return []


def load_image() -> dict:
    p = SHIFT / "data" / "image.json"
    if not p.exists():
        sys.exit("error: out/shift/data/image.json missing; run tools/shift/extract_data.py")
    return json.loads(p.read_text())


class Elves:
    def __init__(self):
        self.cache: dict[str, Elf] = {}

    def __call__(self, obj: str) -> Elf:
        if obj not in self.cache:
            self.cache[obj] = Elf.load(K.ROOT / obj)
        return self.cache[obj]


SUBST: dict[str, str] = {}  # object -> variant object (KH1_SHIFTABLE builds, tools/shift/variants.py)


def collect_functions(asm_objs: list[str], registry, elves,
                      drafts: dict[str, str] | None = None) -> tuple[list[Placed], list[str]]:
    """drafts: function name -> draft object (SHIFT_DRAFTS); its `.text.<name>` takes the
    place of the asm export's section of that name."""
    funcs, errors = [], []
    drafts = drafts or {}
    for addr, sym, obj, _src in K.load_placements():
        obj = SUBST.get(obj, obj)
        e = elves(obj)
        sec = e.section(f".text.{sym}")
        funcs.append(Placed(addr, sym, obj, sec.name, sec.size, addralign(e, sec.index)))
    for obj in asm_objs + list(drafts.values()):
        e = elves(obj)
        for sec in e.sections:
            if not sec.name.startswith(".text.") or not sec.size:
                continue
            sym = sec.name[len(".text."):]
            if (sym in drafts) != (obj in drafts.values()):
                continue  # an asm export the draft replaces
            addr = name_address(sym, registry)
            if addr is None:
                errors.append(f"{obj}: {sec.name}: no address for {sym}")
                continue
            funcs.append(Placed(addr, sym, obj, sec.name, sec.size, addralign(e, sec.index)))
    funcs.sort(key=lambda f: f.addr)
    layout = {f.addr: f for f in K.load_layout()}
    seen: dict[int, Placed] = {}
    for f in funcs:
        if f.addr in seen:
            errors.append(f"0x{f.addr:08x} placed twice: {seen[f.addr].obj} and {f.obj}")
        seen[f.addr] = f
        if f.addr not in layout:
            errors.append(f"{f.obj}: {f.name} at 0x{f.addr:08x} is not a function start in layout.tsv")
    for a, lf in sorted(layout.items()):
        if a not in seen:
            errors.append(f"layout function {lf.name} (0x{a:08x}) has no code in the shift build")
    return funcs, errors


def collect_rodata(elves, funcs: list[Placed], asm_objs: list[str]) -> list[Placed]:
    """Compiled rodata placed by the normal build (out/gen/rodata.tsv), plus
    .rodata.* of the extra asm objects (symbolic jump tables), located the
    same way kh1tool link-script does it: from the %hi/%lo pairs that
    reference them, compared with the original code."""
    rows = [(ad, n, SUBST.get(o, o)) for ad, n, o in K.load_rodata_placements()]
    if asm_objs:
        orig = K.require_orig(K.load_config())
        for obj in asm_objs:
            placed = {f.name: f.addr for f in funcs if f.obj == obj}
            found, problems = K.infer_rodata(K.ROOT / obj, placed, orig)
            for msg in problems:
                print(f"warning: {msg}", file=sys.stderr)
            rows += [(addr, name, obj) for name, addr in found.items()]
    out = []
    for addr, name, obj in rows:
        e = elves(obj)
        sec = e.section(name)
        out.append(Placed(addr, name, obj, name, sec.size, addralign(e, sec.index)))
    return sorted(out, key=lambda r: r.addr)


def float_align(addr: int) -> int:
    """A floated variable keeps the alignment its original address had, up to a cache
    line (64): DMA and SIF buffers rely on it, whatever the C declaration says."""
    return min(addr & -addr, 64)


def collect_variables(elves) -> list[Placed]:
    """Variables C defines (out/gen/data.tsv): .data.<name> sections at their original
    address, with the region ('data' or 'bss') kept in Placed.section's suffix."""
    out = []
    for addr, name, obj, size, region in K.load_data_placements():
        obj = SUBST.get(obj, obj)
        e = elves(obj)
        sec = e.section(f".data.{name}")
        if sec is None or sec.size != size:
            sys.exit(f"error: {obj}: .data.{name} missing or resized since `make`; run `make` first")
        out.append(Placed(addr, name, obj, sec.name, size, addralign(e, sec.index), region))
    return sorted(out, key=lambda v: v.addr)


def gap_statement(prev_end: int, start: int, align: int) -> tuple[str | None, bool]:
    """Statement that takes the location counter from prev_end to start,
    given the input section's own alignment. (stmt, explicit_padding)."""
    if start < prev_end:
        raise ValueError(f"overlap: previous ends at 0x{prev_end:08x}, next starts at 0x{start:08x}")
    nat = -(-prev_end // align) * align
    if nat == start:
        return None, False
    a = 8
    while a <= MAX_ALIGN:
        if -(-prev_end // a) * a == start:
            return f". = ALIGN({a});", False
        a *= 2
    return f". += 0x{start - prev_end:x};", True


def read_aliases(paths: list[str]) -> tuple[list[str], set[str]]:
    lines, names = [], set()
    for p in paths:
        for line in Path(p).read_text().splitlines():
            m = ALIAS_RE.match(line)
            if m:
                names.add(m.group(1))
        lines.append(f"INCLUDE {rel(p)}")
    return lines, names


def cmd_missing(a) -> int:
    placed = {addr for addr, *_ in K.load_placements()}
    print(" ".join(f.name for f in K.load_layout() if f.addr not in placed))
    return 0


def load_data_relocs(path: Path, max_tier: int, layout_addr: dict[str, int]) -> tuple[dict[int, tuple], list[str]]:
    """data_relocs.tsv rows with tier <= max_tier: {original word address:
    (symbol, addend, high bits, text target address or None)}."""
    out, errors = {}, []
    if max_tier <= 0 or not path.exists():
        return out, errors
    for line in path.read_text().splitlines():
        if not line or line.startswith(("#", "offset")):
            continue
        off, typ, sym, addend, tier, _reason = line.split("\t")
        addr = f"{0x00272C70 + int(off, 16):08x}"  # offsets are from the original D_BLOB
        if tier == "x" or int(tier) > max_tier:
            continue
        hi = int(typ.split("+", 1)[1], 16) if "+" in typ else 0
        add = int(addend, 16)
        if sym in ("D_BLOB", "D_BSS"):
            out[int(addr, 16)] = (sym, add, hi, None)
        elif sym in layout_addr:
            out[int(addr, 16)] = (sym, add, hi, layout_addr[sym] + add)
        else:
            errors.append(f"{path.name}: {addr}: unknown target symbol {sym}")
    return out, errors


def pick_drafts(a, asm_objs: list[str], elves, registry):
    """SHIFT_DRAFTS: {name: draft object} for the drafts that can link, one row per
    draft for drafts.tsv, the asm objects still needed, and the asm sections to discard.
    A draft whose undefined names have no definition and no address stays out (status
    `no-link`); its asm export is linked instead."""
    if not a.draft_obj:
        return {}, [], asm_objs, []
    if a.mode == "m0":
        sys.exit("error: SHIFT_DRAFTS needs a moved mode (m1, m2 or m12): drafts are not at the original addresses")
    owner: dict[str, str] = {}  # text section name -> asm object
    known: set[str] = set()  # names some linked object defines
    for obj in objects_mk_objs() + asm_objs:
        for s in elves(obj).symbols():
            if s.name and s.shndx and s.bind in (1, 2):
                known.add(s.name)
    for obj in asm_objs:
        for sec in elves(obj).sections:
            if sec.name.startswith(".text.") and sec.size:
                owner[sec.name] = obj
    alias_names = read_aliases(a.aliases)[1]
    drafts, rows = {}, []
    for spec in a.draft_obj:
        name, obj = spec.split("=", 1)
        obj = rel(obj)
        sec = f".text.{name}"
        if sec not in owner:
            rows.append([name, "-", "no-link", obj, "-", "no asm export defines " + sec])
            continue
        unresolved = []
        for s in elves(obj).symbols():
            if s.shndx or not s.name or s.bind not in (1, 2):
                continue
            n = s.name
            target = K.LIBCALL_ALIASES.get(n, n)
            if n in known or n in alias_names or target in known or name_address(target, registry) is not None:
                continue
            unresolved.append(n)
        addr = name_address(name, registry)
        if unresolved:
            rows.append([name, f"{addr:08x}", "no-link", obj, owner[sec],
                         "undefined: " + ", ".join(sorted(unresolved))])
            continue
        drafts[name] = obj
        rows.append([name, f"{addr:08x}", "linked", obj, owner[sec], ""])
    keep, discard = [], []
    for obj in asm_objs:
        mine = [s for s, o in owner.items() if o == obj]
        gone = [s for s in mine if s[len(".text."):] in drafts]
        if mine and len(gone) == len(mine):
            continue  # every function of this export is drafted: leave the object out
        keep.append(obj)
        discard += [(obj, s) for s in gone]
    return drafts, rows, keep, discard


def cmd_gen(a) -> int:
    img = load_image()
    registry = K.load_registry()
    elves = Elves()
    for spec in a.subst_obj:
        old, new = spec.split("=", 1)
        SUBST[rel(old)] = rel(new)
    out_dir = Path(a.out_dir)
    asm_objs = [rel(o) for o in a.asm_obj]
    drafts, draft_rows, asm_objs, discard = pick_drafts(a, asm_objs, elves, registry)
    funcs, errors = collect_functions(asm_objs, registry, elves, drafts)
    rodata = collect_rodata(elves, funcs, asm_objs)
    variables = collect_variables(elves)
    data_vars = [v for v in variables if v.region == "data"]
    bss_vars = [v for v in variables if v.region == "bss"]
    floating = set()
    if a.float_vars:
        if a.mode == "m0":
            sys.exit("error: --float-vars needs a moved mode: floated variables are not at their original address")
        floating = {v.name for v in variables} - set(a.float_skip)
        if a.float_skip_file:  # inside another declared object (cover_check.py): moving it breaks the object
            covered = set(Path(a.float_skip_file).read_text().split())
            floating -= covered
            print(f"shift-ld: --float-vars: {len(covered)} variables inside another declared object stay in place")
        if a.float_only:  # bisecting: only these bss variables float (data variables still do)
            floating = {v.name for v in variables if v.name in floating
                        and (v.name in a.float_only or v.addr < img["bss_start"])}
    load, text_end = img["load"], img["text_end"]
    blob_start, blob_end = img["data_start"], img["data_end"]
    bss_start, image_end = img["bss_start"], img["image_end"]
    blob_obj = rel(a.blob_obj)

    for r in rodata + data_vars:
        if not (blob_start <= r.addr and r.addr + r.size <= blob_end):
            errors.append(f"{r.obj}: {r.section} at 0x{r.addr:08x} is outside the data blob")
    for v in bss_vars:
        if not (bss_start <= v.addr and v.addr + v.size <= image_end):
            errors.append(f"{v.obj}: {v.section} at 0x{v.addr:08x} is outside .bss (0x{bss_start:08x}-)")
    # A block that lies inside an earlier one is a merged copy (two files with
    # the same assert string: the original linker kept one). The first one
    # fills the hole; the copies get a non-allocated (INFO) section at the same blob offset,
    # so their references resolve there and their bytes are not loaded twice.
    primary, dups = [], []
    for r in sorted(rodata + data_vars, key=lambda x: x.addr):
        if primary and r.addr < primary[-1].addr + primary[-1].size:
            p = primary[-1]
            if r.addr + r.size <= p.addr + p.size:
                dups.append(r)
            elif r.region or p.region:
                errors.append(f"{r.section} ({r.obj}) overlaps {p.section} ({p.obj})")
            else:
                errors.append(f"rodata {r.section} ({r.obj}) overlaps {p.section} ({p.obj})")
            continue
        primary.append(r)

    # Every global definition in a placed section, and every undefined reference.
    placed_secs: dict[tuple[str, str], int] = {(f.obj, f.section): f.addr for f in funcs}
    placed_secs.update({(r.obj, r.section): r.addr for r in rodata + variables})
    defined: dict[str, tuple[int | None, str]] = {}
    undefined: dict[str, str] = {}
    all_objs = list(dict.fromkeys(objects_mk_objs() + asm_objs + list(drafts.values())))
    hook_objs = [rel(a.ovl_hook)] if a.ovl_hook else []  # its references (D_ names) need definitions too
    for obj in all_objs + hook_objs:
        e = elves(obj)
        for s in e.symbols():
            if s.bind not in (1, 2) or not s.name:
                continue
            if s.shndx == 0:
                undefined.setdefault(s.name, obj)
                continue
            sec = e.sections[s.shndx].name if s.shndx < len(e.sections) else None
            base = placed_secs.get((obj, sec))
            addr = base + s.value if base is not None else None
            if s.name in defined and defined[s.name][0] is not None and addr is not None and s.bind == 1:
                errors.append(f"{s.name} defined twice: {defined[s.name][1]} and {obj}")
            if s.name not in defined or addr is not None:
                defined[s.name] = (addr, obj)

    script_defined = {"D_BLOB", "D_BSS", "_ftext", "_etext", "_fdata", "_edata", "_gp", "_fbss", "_end"}
    # the overlay fixup hook and table (M1/M2) define their own names (kh1_ovl_loaded...)
    for o in (a.ovl_hook, a.ovl_fixups):
        if o:
            script_defined |= {x.name for x in elves(rel(o)).symbols() if x.bind in (1, 2) and x.shndx}
    alias_lines, alias_names = read_aliases(a.aliases)
    # Labels go next to the function containing them; data/bss/absolute at the end.
    starts = [f.addr for f in funcs]
    labels: dict[int, list[tuple[str, int]]] = {}
    tail: list[str] = []
    kinds = {"label": 0, "alias": 0, "data": 0, "bss": 0, "abs": 0}
    expected: list[tuple[int, str, str]] = []
    for name in sorted(undefined):
        if name in script_defined:
            continue
        if name in alias_names:  # defined by the alias file; still checked by the M0 verifier
            addr = name_address(K.LIBCALL_ALIASES.get(name, name), registry)
            if addr is not None and load <= addr < text_end:
                expected.append((addr, "label", name))
            continue
        if name in defined:
            if defined[name][0] is None:
                errors.append(f"{name} (used by {undefined[name]}) is defined only in an unplaced section of "
                              f"{defined[name][1]}")
            continue
        target = K.LIBCALL_ALIASES.get(name)
        addr = name_address(target, registry) if target else name_address(name, registry)
        if target and target in defined and defined[target][0] is not None:
            addr = defined[target][0]
        if addr is None:
            errors.append(f"{name} (used by {undefined[name]}) has no address and no definition")
            continue
        if load <= addr < text_end:
            i = bisect.bisect_right(starts, addr) - 1
            f = funcs[i] if i >= 0 else None
            if f is None or addr >= f.addr + max(f.size, 4):
                errors.append(f"{name} = 0x{addr:08x} (used by {undefined[name]}) is in code but in no placed function")
                continue
            labels.setdefault(f.addr, []).append((name, addr - f.addr))
            kinds["alias" if addr == f.addr else "label"] += 1
            expected.append((addr, "label", name))
        elif blob_start <= addr < blob_end:
            tail.append(f"{name} = D_BLOB + 0x{addr - blob_start:x};")
            kinds["data"] += 1
            expected.append((addr, "data", name))
        elif blob_end <= addr <= image_end:
            off = addr - bss_start
            tail.append(f"{name} = D_BSS {'+' if off >= 0 else '-'} 0x{abs(off):x};")
            kinds["bss"] += 1
            expected.append((addr, "bss", name))
        else:
            tail.append(f"{name} = 0x{addr:08x};  /* fixed address outside the image */")
            kinds["abs"] += 1
    bss_runs: list[list[Placed]] = []
    if a.float_vars:
        # Floated bss goes after the original .bss and pushes _end (crt0's heap start) up;
        # the game's fixed arenas start at 0x006A0000 (func_0014a090) and crt0's heap is
        # 0xA000 bytes from _end, so only a budget of bss floats. Variables with no other
        # name between them form a run that floats or stays as one block, at the same
        # offsets: code that walks one buffer into the next (the s6_24 menu objects) keeps
        # working. Smallest runs first; the large ones stay at their D_BSS offset
        # (shift_cmp checks _end + heap < the arena).
        others = sorted(ad for ad, k, n in expected if k == "bss")
        run: list[Placed] = []
        for v in bss_vars:
            if v.name not in floating:
                if run:
                    bss_runs.append(run)
                run = []
                continue
            if run and bisect.bisect_left(others, v.addr) != bisect.bisect_left(others, run[-1].addr + 1):
                bss_runs.append(run)
                run = []
            run.append(v)
        if run:
            bss_runs.append(run)
        span = lambda r: r[-1].addr + r[-1].size - r[0].addr
        budget, kept, keep_runs = a.float_bss_budget, [], []
        for r in sorted(bss_runs, key=lambda r: (span(r), r[0].addr)):
            if span(r) + 64 <= budget:
                budget -= span(r) + 64
            else:
                floating -= {v.name for v in r}
                kept += r
                keep_runs.append(id(r))
        bss_runs = [r for r in bss_runs if id(r) not in keep_runs]
        # Floated data goes after the blob and pushes .bss (and _end) up as much: a budget
        # of it floats, smallest first (cost: size rounded up to its alignment; they are
        # packed by alignment below, so the padding stays inside that bound).
        dbudget, dkept = a.float_data_budget, []
        for v in sorted((v for v in data_vars if v.name in floating), key=lambda v: (v.size, v.addr)):
            al = float_align(v.addr)
            cost = -(-v.size // al) * al
            if cost <= dbudget:
                dbudget -= cost
            else:
                dkept.append(v)
        floating -= {v.name for v in dkept}
        if dkept:
            print(f"shift-ld: --float-vars: {len(dkept)} data variables over the 0x{a.float_data_budget:x} budget "
                  f"stay in the blob (0x{sum(v.size for v in dkept):x} bytes); "
                  f"{sum(1 for v in data_vars if v.name in floating)} float")
        if kept:
            print(f"shift-ld: --float-vars: {len(kept)} bss variables over the 0x{a.float_bss_budget:x} budget "
                  f"stay at their D_BSS offset (largest {max(kept, key=lambda v: v.size).name}, "
                  f"0x{sum(v.size for v in kept):x} bytes); {len(bss_runs)} runs float")
    # A floated variable leaves its original place: nothing else may point inside it
    # (another D_ name defined as blob/bss base + offset, or a blob pointer).
    fl_ranges = sorted((v.addr, v.addr + v.size, v.name) for v in variables if v.name in floating)
    def in_floated(addr: int):
        i = bisect.bisect_right(fl_ranges, (addr, 1 << 40, "")) - 1
        return fl_ranges[i][2] if i >= 0 and addr < fl_ranges[i][1] else None
    for line in tail:
        m = re.match(r"(\S+) = D_(BLOB|BSS) ([+-]) 0x([0-9a-f]+);", line)
        if m:
            base = blob_start if m.group(2) == "BLOB" else bss_start
            ad = base + (int(m.group(4), 16) if m.group(3) == "+" else -int(m.group(4), 16))
            if in_floated(ad):
                errors.append(f"--float-vars: {m.group(1)} (0x{ad:08x}) points inside {in_floated(ad)}")
    # Data relocations (data_relocs.tsv): pointers in the blob become `.word sym+addend`.
    # Code targets get a label at their function (__dr_XXXXXXXX = function start).
    drel, drel_err = load_data_relocs(Path(a.data_relocs), a.reloc_tier,
                                      {f.name: f.addr for f in K.load_layout()})
    errors += drel_err
    # Phase 4 step 5: a blob word that points into a variable an object defines (C, or a
    # data piece of src/data/*.s) is a relocation against that variable, so it follows
    # the variable when it floats (same value when it does not).
    var_ranges = sorted((v.addr, v.addr + v.size, v.name) for v in variables)
    var_starts = [r[0] for r in var_ranges]
    n_retarget = 0
    for w_addr, (sym, add, hi, t) in list(drel.items()):
        if sym not in ("D_BLOB", "D_BSS"):
            continue
        ad = (blob_start if sym == "D_BLOB" else bss_start) + add
        i = bisect.bisect_right(var_starts, ad) - 1
        if i >= 0 and ad < var_ranges[i][1]:
            drel[w_addr] = (var_ranges[i][2], ad - var_ranges[i][0], hi, t)
            n_retarget += 1
    for w_addr, (sym, add, _hi, _t) in drel.items():
        if sym in ("D_BLOB", "D_BSS"):
            ad = (blob_start if sym == "D_BLOB" else bss_start) + add
            if in_floated(ad):
                errors.append(f"--float-vars: the blob word at 0x{w_addr:08x} points inside {in_floated(ad)}")
    hole_ranges = sorted((r.addr, r.addr + r.size) for r in primary)
    in_holes = 0
    for w_addr in list(drel):
        i = bisect.bisect_right(hole_ranges, (w_addr, 1 << 40)) - 1
        if i >= 0 and w_addr < hole_ranges[i][1]:
            del drel[w_addr]  # now a compiled/asm rodata block with its own relocations
            in_holes += 1
    dr_labels: dict[int, str] = {}
    for w_addr, (sym, add, hi, target) in drel.items():
        if target is None:
            continue
        i = bisect.bisect_right(starts, target) - 1
        f = funcs[i] if i >= 0 else None
        if f is None or target >= f.addr + max(f.size, 4) + 8:
            errors.append(f"data reloc at 0x{w_addr:08x}: target 0x{target:08x} is in no placed function")
            continue
        if f.addr not in dr_labels:
            dr_labels[f.addr] = f"__dr_{f.addr:08x}"
            labels.setdefault(f.addr, []).append((dr_labels[f.addr], 0))
        drel[w_addr] = (dr_labels[f.addr], target - f.addr, hi, target)

    # Overlay fixups (KH1_OVL_FIXUPS, M1/M2): the table names main-ELF functions as
    # __dr_XXXXXXXX labels (+ offset for mid-function targets): define them too.
    ovl_objs = [rel(o) for o in (a.ovl_hook, a.ovl_fixups) if o]
    if a.ovl_labels:
        fstarts = {f.addr for f in funcs}
        for line in Path(a.ovl_labels).read_text().split():
            fa = int(line, 16)
            if fa not in fstarts:
                errors.append(f"{a.ovl_labels}: 0x{fa:08x} is not a placed function start")
            elif fa not in dr_labels:
                dr_labels[fa] = f"__dr_{fa:08x}"
                labels.setdefault(fa, []).append((dr_labels[fa], 0))

    if errors:
        print("\n".join(f"error: {e}" for e in errors), file=sys.stderr)
        return 1

    # ---- .text
    padded = []
    text = [f"  .text 0x{load:08x} : {{", "    _ftext = .;"]
    pos = load
    order = list(funcs)
    split = None
    # A KH1_SHIFTABLE variant may be longer than its original slot (M1/M2 only: the
    # KH1_OVL_FIXUPS hook adds a call): the functions after it move by a multiple of 64
    # (`. = ALIGN(64) + start % 64`), so every later `. = ALIGN(n)` keeps its meaning.
    grown = [f for f, g in zip(funcs, funcs[1:]) if f.addr + f.size > g.addr]
    if grown and a.mode == "m0":
        print("error: m0: " + ", ".join(f"{f.name} ({f.obj})" for f in grown) + " longer than the original slot",
              file=sys.stderr)
        return 1
    # each grown function pushes what follows to the next 64-byte boundary (+ its offset mod 64)
    nxt_of = {f.addr: g for f, g in zip(funcs, funcs[1:])}
    growth = sum(-(-(f.addr + f.size) // 64) * 64 - (nxt_of[f.addr].addr // 64) * 64 for f in grown)
    data_limit = blob_start + (a.data_shift if a.mode in ("m2", "m12") else 0)
    if a.mode in ("m1", "m12"):
        # Rotate: the last functions (from a 64-aligned start) go to the front.
        # Each block keeps its offsets modulo 64, so every `. = ALIGN(n)` keeps its meaning.
        last_end = funcs[-1].addr + funcs[-1].size
        prev_end = {g.addr: f.addr + f.size for f, g in zip(funcs, funcs[1:])}

        def fits(sp: int) -> bool:  # the rotated text must still end before the fixed data
            return -(-(load + last_end - sp) // 64) * 64 + (prev_end[sp] - load) + growth <= data_limit
        cands = [f.addr for f in funcs[1:] if f.addr % 64 == 0 and last_end - f.addr >= a.m1_min and fits(f.addr)]
        if not cands:
            print("error: m1: no 64-aligned function start leaves enough to move", file=sys.stderr)
            return 1
        split = max(cands)
        order = [f for f in funcs if f.addr >= split] + [f for f in funcs if f.addr < split]
        pos = split
    for f in order:
        if split is not None and f.addr == funcs[0].addr:
            text.append(f"    . = ALIGN(64);  /* m1: end of the rotated block 0x{split:08x}- */")
            pos = load
        if pos > f.addr:  # the previous function grew (see `grown`)
            stmt, explicit = f". = ALIGN(64) + 0x{f.addr % 64:x};  /* the previous function grew */", False
        else:
            stmt, explicit = gap_statement(pos, f.addr, f.align)
        if not stmt and pos != f.addr and f.addr in labels:
            stmt = f". = ALIGN({f.align});"  # so `.` is the function start for its labels
        if stmt:
            text.append(f"    {stmt}")
        if explicit:
            padded.append(f"0x{pos:08x}-0x{f.addr:08x} before {f.name}")
        for name, off in sorted(labels.get(f.addr, []), key=lambda t: (t[1], t[0])):
            text.append(f"    {name} = . + 0x{off:x};" if off else f"    {name} = .;")
        text.append(f"    KEEP({f.obj}({f.section}))  /* 0x{f.addr:08x} */")
        expected.append((f.addr, "func", f.name))
        pos = f.addr + f.size
    stmt, explicit = gap_statement(pos, blob_start, 1)
    text.append("    _etext = .;")
    text.append("  } =0")
    data_addr = f"ALIGN({stmt[len('. = ALIGN('):-2]})" if stmt and not explicit else (
        "." if not stmt else None)
    if a.mode == "m1":
        data_addr = f"0x{blob_start:08x}"  # data fixed; ld fails if the rotated text overruns it
    elif a.mode == "m12" or (a.mode == "m2" and growth):
        if a.mode == "m2" and load + (text_end - load) + growth > data_limit:
            print(f"error: m2: the text grew by 0x{growth:x}, more than --data-shift 0x{a.data_shift:x}",
                  file=sys.stderr)
            return 1
        data_addr = f"0x{blob_start + a.data_shift:08x}"  # the delta stays data_shift; ld fails on an overrun
    elif a.mode == "m2" and data_addr is not None:
        data_addr = f"{data_addr} + 0x{a.data_shift:x}"
    if data_addr is None:
        print(f"error: gap 0x{pos:08x}-0x{blob_start:08x} between code and data has no alignment", file=sys.stderr)
        return 1

    # ---- .data: blob chunks and compiled rodata holes
    blob_s = ["/* Auto-generated by tools/shift/shift_ld.py: the original data, cut around",
              " * the compiled rodata blocks. Build input only; main.bin is never committed. */"]
    data = [f"  .data {data_addr} : {{", "    _fdata = .;", "    D_BLOB = .;"]
    cur = blob_start
    chunk = 0

    drel_addrs = sorted(drel)
    n_words = 0

    def emit_chunk(upto: int) -> None:
        nonlocal cur, chunk, n_words
        if upto > cur:
            sec = f".blob.{chunk:04d}"
            # `.align 0`: no automatic alignment of .word (the chunk may start unaligned)
            blob_s.append(f'\t.section {sec},"aw",@progbits\n\t.align 0')
            i = bisect.bisect_left(drel_addrs, cur)
            p = cur
            while i < len(drel_addrs) and drel_addrs[i] + 4 <= upto:
                w = drel_addrs[i]
                if w > p:
                    blob_s.append(f'\t.incbin "{rel(a.blob)}", 0x{p - blob_start:x}, 0x{w - p:x}')
                sym, add, hi, _t = drel[w]
                off = add + hi
                blob_s.append(f"\t.word {sym}{'+' if off >= 0 else '-'}0x{abs(off):x}")
                n_words += 1
                p = w + 4
                i += 1
            if upto > p:
                blob_s.append(f'\t.incbin "{rel(a.blob)}", 0x{p - blob_start:x}, 0x{upto - p:x}')
            data.append(f"    KEEP({blob_obj}({sec}))  /* 0x{cur:08x} */")
            chunk += 1
            cur = upto

    for r in primary:
        emit_chunk(r.addr)
        if r.addr % r.align:
            print(f"error: {r.section} at 0x{r.addr:08x} is not {r.align}-aligned", file=sys.stderr)
            return 1
        if r.name in floating:  # its old place stays a zero gap; the variable goes after the blob
            data.append(f"    . += 0x{r.size:x};  /* {r.name} floated */")
            cur = r.addr + r.size
            continue
        data.append(f"    KEEP({r.obj}({r.section}))  /* 0x{r.addr:08x} */")
        if r.region:
            expected.append((r.addr, "data", r.name))
        else:
            expected.append((r.addr, "rodata", f"{r.obj}:{r.section}"))
        cur = r.addr + r.size
    emit_chunk(blob_end)
    # largest alignment first: no padding between the floated variables beyond the budget's bound
    fl_data = sorted((v for v in data_vars if v.name in floating), key=lambda v: (-float_align(v.addr), v.addr))
    if fl_data:
        # --float-vars: the variables in their own place after the blob
        data += ["    __float_data_start = .;"]
        for v in fl_data:
            data += [f"    . = ALIGN({float_align(v.addr)});",
                     f"    KEEP({v.obj}({v.section}))  /* was 0x{v.addr:08x} */"]
    if drafts:
        # SHIFT_DRAFTS: the drafts' own rodata (jump tables, constants) after the blob;
        # the asm version's tables in the blob stay, unused by the draft.
        data += ["    . = ALIGN(16);", "    __draft_rodata_start = .;"]
        data += [f"    KEEP({o}(.rodata .rodata.*))" for o in drafts.values()]
        data += ["    __draft_rodata_end = .;"]
    if ovl_objs:
        # The overlay fixup hook and its table, after the blob. The end keeps the
        # original distance to .bss (crt0 clears from D_BSS - 0x30, $gp is set there):
        # `. = ALIGN(128) + blob_end % 128`, so the table is never cleared.
        data += ["    . = ALIGN(16);", "    __ovl_fixup_start = .;"]
        data += [f"    KEEP({o}(.text .text.* .rodata .rodata.* .data .data.* .sdata .sdata.* "
                 f".bss .bss.* .sbss .sbss.* .scommon COMMON .ovl_fixups))" for o in ovl_objs]
        data += ["    __ovl_fixup_end = .;"]
    if ovl_objs or drafts or fl_data:
        data += ["    . = ALIGN(128);", f"    . += 0x{blob_end % 128:x};"]
    data += ["    _edata = .;", "  } =0"]
    rodup = []
    for r in dups:
        rodup.append(f"  .rodup_{r.addr:08x} (D_BLOB + 0x{r.addr - blob_start:x}) (INFO) : "
                    f"{{ KEEP({r.obj}({r.section})) }}  /* copy of the block at 0x{r.addr:08x} */")
        expected.append((r.addr, "rodata", f"{r.obj}:{r.section}"))
    bss_gap = bss_start - blob_end
    bss_align = next((n for n in (8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096)
                      if -(-blob_end // n) * n == bss_start), None) if bss_gap else 1
    if bss_align is None:
        print("error: .bss start is not an alignment of the data end", file=sys.stderr)
        return 1

    # Variables C defines in the bss range: at their offset from D_BSS (zero-initialised,
    # so their input sections only reserve space in the NOLOAD output section).
    bss_lines, bss_tail = [], []
    for k, r in enumerate(bss_runs):  # after the original .bss, before _end (crt0 clears up to _end)
        al = max(float_align(v.addr) for v in r)
        bss_tail += [f"    . = ALIGN({al}) + 0x{r[0].addr % al:x};", f"    __float_run{k} = .;"]
        for v in r:
            bss_tail.append(f"    . = __float_run{k} + 0x{v.addr - r[0].addr:x};")
            bss_tail.append(f"    KEEP({v.obj}({v.section}))  /* was 0x{v.addr:08x} */")
    for v in bss_vars:
        if v.name in floating:
            continue
        bss_lines.append(f"    . = D_BSS + 0x{v.addr - bss_start:x};")
        bss_lines.append(f"    KEEP({v.obj}({v.section}))  /* 0x{v.addr:08x} */")
        expected.append((v.addr, "bss", v.name))
    if bss_tail:
        # crt0 clears .bss up to D_00675018 and starts the heap there: it must be the new _end
        tail = [("D_00675018 = _end;  /* heap start: after the floated bss variables */"
                 if t.startswith("D_00675018 = ") else t) for t in tail]
        bss_tail = [f"    . = D_BSS + 0x{image_end - bss_start:x};", "    . = ALIGN(16);",
                    "    __float_bss_start = .;"] + bss_tail
    out = [
        "/* Auto-generated by tools/shift/shift_ld.py: link script of the shiftable",
        " * build (docs/shiftable-plan.md). No PROVIDE: every name is defined here",
        " * or by an object, or the link fails. */",
        f"ENTRY({next(f.name for f in funcs if f.addr == img['entry'])})",
        "",
        "SECTIONS",
        "{",
        *text,
        "",
        *data,
        "  _gp = _edata;     /* crt0: $gp, and where it starts clearing */" if not a.bss_pad else
        "  _gp = D_BSS - 0x30;",
        "  _fbss = _gp;",
        f"  .bss ALIGN({bss_align}) (NOLOAD) : {{",
        *([f"    . += 0x{a.bss_pad:x};  /* --bss-pad experiment */"] if a.bss_pad else []),
        "    D_BSS = .;",
        *bss_lines,
        f"    . = D_BSS + 0x{image_end - bss_start:x};  /* .bss and the .reginfo slot up to the heap */",
        *bss_tail,
        "    _end = .;",
        "  }",
        "",
        "",
        "  /* Merged rodata copies: same blob offset as the block they duplicate, not loaded. */",
        *rodup,
        "",
        "  /* Must stay empty (shift_elf.py checks): code or data nobody placed. */",
        "  .shift_orphan 0x40000000 : {",
        "    *(.text .text.* .gnu.linkonce.t.*)",
        "    *(.data .data.* .sdata .sdata.* .lit4 .lit8 .gnu.linkonce.d.*)",
        "    *(.sbss .sbss.* .bss .bss.* .scommon COMMON)",
        "  }",
        "",
        "  /DISCARD/ : {",
        *[f"    {o}({sec})  /* replaced by a SHIFT_DRAFTS draft */" for o, sec in discard],
        "    *(.ctx .ctx.*)",
        "    *(.rodata .rodata.* .gnu.linkonce.r.*)",
        "    *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) *(.gnu.attributes)",
        "    *(.MIPS.abiflags) *(.note*) *(.gcc_compiled*)",
        "  }",
        "}",
        "",
        "/* Aliases from the symbolic-asm work (alias = canonical;). */",
        *alias_lines,
        "",
        "/* Data and bss names: blob/bss base + offset; fixed addresses outside the image. */",
        *tail,
        "",
    ]
    out_dir.mkdir(parents=True, exist_ok=True)
    write(out_dir / "kh1-shift.ld", "\n".join(out))
    write(out_dir / "blob.s", "\n".join(blob_s) + "\n")
    write(out_dir / "objects.lst", "\n".join(all_objs + [blob_obj] + ovl_objs) + "\n")
    draft_tsv = out_dir / "drafts.tsv"
    if draft_rows:
        write(draft_tsv, "name\taddr\tstatus\tdraft\treplaces\tnote\n" + "".join("\t".join(r) + "\n" for r in draft_rows))
    elif draft_tsv.exists():
        draft_tsv.unlink()
    write(out_dir / "expected.tsv", "addr\tkind\tname\n" + "".join(
        f"{ad:08x}\t{k}\t{n}\n" for ad, k, n in sorted(expected)))
    variant_objs = set(SUBST.values())
    nexts = {f.addr: g.addr for f, g in zip(funcs, funcs[1:])}
    write(out_dir / "variants.tsv", "addr\tend\tname\tobject\n" + "".join(
        f"{f.addr:08x}\t{nexts.get(f.addr, f.addr + f.size):08x}\t{f.name}\t{f.obj}\n"
        for f in funcs if f.obj in variant_objs))
    print(f"shift-ld: {len(funcs)} functions ({len(asm_objs)} extra asm objects), {len(rodata)} rodata holes, "
          f"{chunk} blob chunks, {len(dups)} merged rodata copies; defined {kinds['alias']} aliases + {kinds['label']} mid-function labels, "
          f"{kinds['data']} data + {kinds['bss']} bss names, {kinds['abs']} absolute (outside the image)"
          + (f"; {len(data_vars)} data + {len(bss_vars)} bss variables defined in C" if variables else "")
          + (f" ({len(floating)} floated)" if floating else ""))
    print(f"shift-ld: mode {a.mode}: {n_words} data relocations (tier <= {a.reloc_tier}) as .word sym+addend"
          + (f", {in_holes} rows inside rodata holes skipped" if in_holes else "")
          + (f", {n_retarget} retargeted at the variable they point into" if n_retarget else "")
          + (f"; text rotated at 0x{split:08x} (0x{funcs[-1].addr + funcs[-1].size - split:x} bytes to the front)"
             if split is not None else "")
          + (f"; data and bss shifted by 0x{a.data_shift:x}" if a.mode in ("m2", "m12") else "")
          + (f"; variant objects: {', '.join(sorted(variant_objs))}" if variant_objs else "")
          + (f"; overlay fixups: {', '.join(ovl_objs)}" if ovl_objs else "")
          + (f"; text grew by 0x{growth:x}" if growth else ""))
    if draft_rows:
        print(f"shift-ld: SHIFT_DRAFTS: {len(drafts)} drafts linked in place of their asm exports"
              + "".join(f"; {r[0]} {r[2]}: {r[5]}" for r in draft_rows if r[2] != "linked"))
    for p in padded:
        print(f"shift-ld: note: explicit padding {p} (no alignment explains it)")
    return 0


def write(path: Path, text: str) -> None:
    path = Path(path)
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("missing", help="print layout functions with no placed code")
    g = sub.add_parser("gen", help="write the link script, blob.s and object list")
    g.add_argument("--asm-obj", action="append", default=[],
                   help="extra object with .text.<fn> sections (asm export of unplaced functions)")
    g.add_argument("--aliases", action="append", default=[], help="file of `alias = canonical;` lines")
    g.add_argument("--blob", default=str(SHIFT / "data" / "main.bin"))
    g.add_argument("--out-dir", default=str(SHIFT), help="where the script, blob.s, objects.lst go")
    g.add_argument("--blob-obj", default=None, help="default: OUT_DIR/blob.o")
    g.add_argument("--mode", choices=("m0", "m1", "m2", "m12"), default="m0",
                   help="m0: original addresses; m1: rotate the text (data fixed); m2: data+bss moved; "
                        "m12: both (text rotated, data+bss moved by --data-shift)")
    g.add_argument("--draft-obj", action="append", default=[], metavar="NAME=OBJ",
                   help="SHIFT_DRAFTS: link OBJ's .text.NAME (a near-miss C draft, tools/shift/drafts.py) "
                        "in place of the asm export of NAME; not with m0")
    g.add_argument("--m1-min", type=lambda x: int(x, 0), default=0x10000,
                   help="m1: move at least this many bytes of code to the front")
    g.add_argument("--data-shift", type=lambda x: int(x, 0), default=0x1000, help="m2: data/bss delta")
    g.add_argument("--data-relocs", default=str(K.ROOT / "data_relocs.tsv"))
    g.add_argument("--reloc-tier", type=int, default=3,
                   help="emit data_relocs.tsv rows with tier <= N as relocations (0: none)")
    g.add_argument("--subst-obj", action="append", default=[], metavar="OBJ=VARIANT",
                   help="link VARIANT instead of OBJ (KH1_SHIFTABLE builds)")
    g.add_argument("--float-vars", action="store_true",
                   help="moved modes: link the variables C defines away from their original place "
                        "(data after the blob, bss after the original .bss); phase 4")
    g.add_argument("--float-skip-file", metavar="FILE",
                   help="--float-vars: names (one per line) that stay in place: tools/shift/cover_check.py --out")
    g.add_argument("--float-skip", action="append", default=[], metavar="NAME",
                   help="--float-vars: leave NAME at its original place (bisecting a runtime failure)")
    g.add_argument("--float-only", action="append", default=[], metavar="NAME",
                   help="--float-vars: only these bss variables float (bisecting a runtime failure)")
    g.add_argument("--float-bss-budget", type=lambda x: int(x, 0), default=0x10000,
                   help="--float-vars: at most this many bytes of bss float (smallest variables first)")
    g.add_argument("--float-data-budget", type=lambda x: int(x, 0), default=0x4000,
                   help="--float-vars: at most this many bytes of data variables float (smallest first)")
    g.add_argument("--bss-pad", type=lambda x: int(x, 0), default=0, help="experiment: pad before .bss")
    g.add_argument("--ovl-fixups", default=None, help="overlay fixup table object (ovl_fixups.s), M1/M2")
    g.add_argument("--ovl-hook", default=None, help="the KH1_OVL_FIXUPS hook object (shift/ovl_fixup.c)")
    g.add_argument("--ovl-labels", default=None, help="function starts the table names (__dr_ labels)")
    a = ap.parse_args()
    if a.cmd == "gen" and a.blob_obj is None:
        a.blob_obj = str(Path(a.out_dir) / "blob.o")
    return cmd_missing(a) if a.cmd == "missing" else cmd_gen(a)


if __name__ == "__main__":
    sys.exit(main())
