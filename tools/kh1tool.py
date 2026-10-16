#!/usr/bin/env python3
"""kh1-decomp build helper.

Same model as the GovanifY/kh2 decomp: every decompiled function is compiled
with -ffunction-sections, linked at its original address (everything else
resolves to original addresses through PROVIDE()), and its bytes are patched
into a copy of the original ELF. A function is matched when the patched bytes
equal the original bytes (and objdiff agrees, see `objdiff`).

Subcommands are driven by the Makefile; run `kh1tool.py -h` for the list.
"""
from __future__ import annotations

import argparse
import datetime as dt
import hashlib
import json
import os
import re
import shlex
import shutil
import struct
import subprocess
import sys
import tomllib
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elf32 import PF_X, PT_LOAD, SHT_SYMTAB, STT_FUNC, Elf  # noqa: E402
from mangle_gcc2 import resolve as resolve_symbol  # noqa: E402

ROOT = Path(os.environ.get("KH1_ROOT", Path(__file__).resolve().parents[1]))
CONFIG_PATH = Path(os.environ.get("KH1_CONFIG", ROOT / "kh1.toml"))
OUT = ROOT / "out"
GEN = OUT / "gen"
LAYOUT = ROOT / "layout.tsv"
REGISTRY = ROOT / "functions.tsv"
TOOLCHAIN_DIR = ROOT / "tools" / "toolchain"
LINKED = OUT / "linked.elf"
PATCHED = OUT / "kh1.elf"
PLACEMENTS = GEN / "placements.tsv"
OBJDIFF_DIR = OUT / "objdiff"
OBJDIFF_JSON = ROOT / "objdiff.json"
BINUTILS = os.environ.get("KH1_BINUTILS_PREFIX", "mips-linux-gnu-")

SOURCE_SUFFIXES = {".c": "c", ".cpp": "cxx", ".cc": "cxx", ".s": "asm", ".S": "asm"}
ADDR_REF_RE = re.compile(r"\b(?:func|D)_([0-9A-Fa-f]{8})\b")
PLACEHOLDER_RE = re.compile(r"^func_([0-9A-Fa-f]{8})(?:__.*)?$")

JR_RA = 0x03E00008


# --------------------------------------------------------------------------- config

def load_config() -> dict:
    with CONFIG_PATH.open("rb") as f:
        return tomllib.load(f)


def cfg_get(cfg: dict, dotted: str):
    cur = cfg
    for part in dotted.split("."):
        cur = cur[part]
    return cur


def orig_path(cfg: dict) -> Path:
    env = os.environ.get("KH1_ORIG")
    return Path(env) if env else ROOT / cfg["target"]["elf"]


def require_orig(cfg: dict) -> Elf:
    path = orig_path(cfg)
    if not path.exists():
        sys.exit(f"error: missing {path.name}. Copy it from your own disc to the repo root "
                 f"(it is gitignored and must never be committed).")
    return Elf.load(path)


def parse_int(text: str | int) -> int:
    return text if isinstance(text, int) else int(str(text), 0)


@dataclass(frozen=True)
class Flags:
    compiler: str
    cflags: str
    cxxflags: str
    asflags: str


def flags_for(cfg: dict, rel: str) -> Flags:
    tc = cfg["toolchain"]
    base = Flags(tc["compiler"], tc["cflags"], tc.get("cxxflags", tc["cflags"]), tc["asflags"])
    best = None
    for ov in tc.get("override", []):
        if rel.startswith(ov["path"]) and (best is None or len(ov["path"]) > len(best["path"])):
            best = ov
    if best is None:
        return base
    return Flags(best.get("compiler", base.compiler), best.get("cflags", base.cflags),
                 best.get("cxxflags", best.get("cflags", base.cxxflags)), best.get("asflags", base.asflags))


# --------------------------------------------------------------------------- tables

@dataclass(frozen=True)
class Func:
    addr: int
    end: int
    name: str

    @property
    def size(self) -> int:
        return self.end - self.addr


def load_layout() -> list[Func]:
    if not LAYOUT.exists():
        sys.exit("error: layout.tsv missing; run `make layout` with the original ELF present")
    out = []
    for line in LAYOUT.read_text().splitlines():
        if not line.strip() or line.startswith(("#", "addr")):
            continue
        addr, end, _size, name = line.split("\t")[:4]
        out.append(Func(int(addr, 16), int(end, 16), name))
    return out


def load_registry() -> dict[str, int]:
    """functions.tsv: symbol<TAB>address. Symbols may be C++ signatures."""
    out: dict[str, int] = {}
    if not REGISTRY.exists():
        return out
    for lineno, line in enumerate(REGISTRY.read_text().splitlines(), 1):
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        parts = s.split("\t")
        if len(parts) < 2:
            sys.exit(f"functions.tsv:{lineno}: expected symbol<TAB>address")
        sym = resolve_symbol(parts[0].strip())
        addr = int(parts[1], 16)
        if sym in out and out[sym] != addr:
            sys.exit(f"functions.tsv:{lineno}: {sym} defined twice with different addresses")
        out[sym] = addr
    return out


def iter_sources() -> list[Path]:
    src = ROOT / "src"
    return sorted(p for p in src.rglob("*") if p.suffix in SOURCE_SUFFIXES and p.is_file())


def obj_for(src: Path) -> Path:
    return OUT / "build" / src.relative_to(ROOT).with_suffix(src.suffix + ".o")


# --------------------------------------------------------------------------- check / layout

def cmd_check(args, cfg) -> int:
    path = orig_path(cfg)
    if not path.exists():
        print(f"missing: {path}")
        return 1
    digest = hashlib.sha256(path.read_bytes()).hexdigest()
    want = cfg["target"].get("sha256", "")
    print(f"{path.name}: sha256 {digest}")
    if not want:
        print("warning: kh1.toml has no pinned sha256 yet")
        return 0
    if digest != want:
        print(f"error: expected {want}; this is not the pinned target")
        return 1
    print("ok: matches pinned target")
    return 0


def code_range(cfg: dict, elf: Elf) -> tuple[int, int]:
    t = cfg["target"]
    if t.get("text_start") and t.get("text_end"):
        return parse_int(t["text_start"]), parse_int(t["text_end"])
    sec = elf.section(".text")
    if sec and sec.size:
        return sec.addr, sec.addr + sec.size
    for seg in elf.segments:
        if seg.type == PT_LOAD and seg.flags & PF_X:
            return seg.vaddr, seg.vaddr + seg.filesz
    sys.exit("error: cannot determine the code range; set target.text_start/text_end")


def find_functions(elf: Elf, start: int, end: int) -> list[Func]:
    """Heuristic boundary finder: jal targets, the entry point, code pointers
    stored in data, and stack-frame prologues right after a `jr $ra`."""
    code = elf.read(start, end - start)
    words = struct.unpack(f"<{len(code) // 4}I", code[: len(code) // 4 * 4])

    def word_at(addr: int) -> int | None:
        i = (addr - start) // 4
        return words[i] if 0 <= i < len(words) else None

    def follows_function_end(addr: int) -> bool:
        a = addr - 4
        skipped = 0
        while skipped < 8 and word_at(a) == 0 and word_at(a - 4) != JR_RA:
            a -= 4
            skipped += 1
        return word_at(a - 4) == JR_RA

    def is_prologue(w: int | None) -> bool:
        return w is not None and (w & 0xFFFF8000) in (0x27BD8000, 0x67BD8000)  # (d)addiu sp,sp,-N

    starts = set()
    if start <= elf.entry < end:
        starts.add(elf.entry)
    for i, w in enumerate(words):
        op = w >> 26
        if op == 3:  # jal
            tgt = ((start + i * 4 + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
            if start <= tgt < end:
                starts.add(tgt)
        if w == JR_RA:
            a = start + i * 4 + 8
            while word_at(a) == 0:
                a += 4
            if is_prologue(word_at(a)):
                starts.add(a)

    # Code pointers in non-code loaded data (vtables, callback tables). Jump
    # tables also point into code, so only accept addresses that follow a
    # function end.
    for seg in elf.segments:
        if seg.type != PT_LOAD:
            continue
        blob = elf.data[seg.offset: seg.offset + seg.filesz]
        for j in range(0, len(blob) - 3, 4):
            va = seg.vaddr + j
            if start <= va < end:
                continue
            (p,) = struct.unpack_from("<I", blob, j)
            if start <= p < end and p % 4 == 0 and follows_function_end(p):
                starts.add(p)

    ordered = sorted(starts)
    funcs = []
    for k, a in enumerate(ordered):
        e = ordered[k + 1] if k + 1 < len(ordered) else end
        while e - 4 > a and word_at(e - 4) == 0 and word_at(e - 8) != JR_RA:
            e -= 4  # drop alignment padding, keep the delay slot after jr ra
        funcs.append(Func(a, e, f"func_{a:08x}"))
    return funcs


def import_ghidra_csv(path: Path) -> list[Func]:
    """Ghidra 'Functions' window export (Name, Location, Function Size) or
    plain addr<TAB>size<TAB>name lines."""
    import csv
    rows = []
    text = path.read_text()
    dialect = "excel-tab" if "\t" in text.splitlines()[0] else "excel"
    reader = csv.reader(text.splitlines(), dialect=dialect)
    header = next(reader)
    cols = {h.strip().lower(): i for i, h in enumerate(header)}
    if "location" in cols:
        for r in reader:
            addr = int(r[cols["location"]].split(":")[-1], 16)
            size = int(r[cols["function size"]])
            rows.append(Func(addr, addr + size, f"func_{addr:08x}"))
    else:
        for r in [header, *reader]:
            if r and not r[0].startswith("#"):
                addr, size = int(r[0], 16), int(r[1], 0)
                rows.append(Func(addr, addr + size, f"func_{addr:08x}"))
    return sorted(rows, key=lambda f: f.addr)


def cmd_layout(args, cfg) -> int:
    elf = require_orig(cfg)
    if args.ghidra:
        funcs = import_ghidra_csv(Path(args.ghidra))
        how = f"imported from {Path(args.ghidra).name}"
    else:
        start, end = code_range(cfg, elf)
        funcs = find_functions(elf, start, end)
        how = f"heuristic scan of 0x{start:08x}-0x{end:08x}"
    lines = ["# AUTO-GENERATED by `tools/kh1tool.py layout` (" + how + ").",
             "# Hand edits are allowed (split/merge mis-detected functions); keep it sorted.",
             "addr\tend\tsize\tname"]
    lines += [f"{f.addr:08x}\t{f.end:08x}\t{f.size}\t{f.name}" for f in funcs]
    LAYOUT.write_text("\n".join(lines) + "\n")
    print(f"layout.tsv: {len(funcs)} functions ({how})")
    return 0


# --------------------------------------------------------------------------- build generation

def cmd_gen(args, cfg) -> int:
    """Write out/gen/objects.mk (per-source compile rules) and symbols.ld."""
    GEN.mkdir(parents=True, exist_ok=True)
    rules, objs = [], []
    for src in iter_sources():
        rel = src.relative_to(ROOT).as_posix()
        obj = obj_for(src).relative_to(ROOT).as_posix()
        kind = SOURCE_SUFFIXES[src.suffix]
        fl = flags_for(cfg, rel)
        tc = f"$(TOOLCHAIN)/{fl.compiler}/bin"
        if kind == "asm":
            cmd = f"$(AS) {fl.asflags} -o $@ {rel}"
        else:
            lang, flags = ("c++", fl.cxxflags) if kind == "cxx" else ("c", fl.cflags)
            cmd = (f"{tc}/ee-gcc -c -x {lang} {flags} -ffunction-sections $(INCLUDES) "
                   f"-o $@ {rel} && $(KH1) fix-obj $@")
        rules.append(f"{obj}: {rel} $(HEADERS) kh1.toml\n\t@mkdir -p $(dir $@)\n"
                     f"\t@echo CC {rel}\n\t@{cmd}\n")
        objs.append(obj)
    (GEN / "objects.mk").write_text(
        "# Auto-generated by tools/kh1tool.py gen\n"
        + f"OBJS := {' '.join(objs)}\n\n" + "\n".join(rules))

    provides: dict[str, int] = dict(load_registry())
    for src in iter_sources():
        for m in ADDR_REF_RE.finditer(src.read_text(errors="ignore")):
            provides.setdefault(m.group(0), int(m.group(1), 16))
    gp = cfg["target"].get("gp")
    lines = ["/* Auto-generated by tools/kh1tool.py gen */"]
    if gp:
        lines.append(f"_gp = {gp};")
    lines += [f"PROVIDE({name} = 0x{addr:08x});" for name, addr in sorted(provides.items(), key=lambda kv: kv[1])]
    (GEN / "symbols.ld").write_text("\n".join(lines) + "\n")
    print(f"gen: {len(objs)} sources, {len(provides)} provided symbols")
    return 0


def fix_object(path: Path) -> bool:
    """ee-as 2.10 (shipped with ee-gcc 2.9x) can emit local symbols after
    global ones and sets .symtab's sh_info wrongly; modern ld rejects both.
    Reorder the table locals-first (stable), remap relocation symbol indexes,
    and set sh_info to the first global, as the ELF spec requires."""
    SHT_RELA, SHT_REL = 4, 9
    data = bytearray(path.read_bytes())
    elf = Elf(bytes(data), path)
    changed = False
    for sec in elf.sections:
        if sec.type != SHT_SYMTAB:
            continue
        n = sec.size // 16
        entries = [bytes(data[sec.offset + i * 16: sec.offset + (i + 1) * 16]) for i in range(n)]
        is_local = [e[12] >> 4 == 0 for e in entries]
        order = [i for i in range(n) if is_local[i]] + [i for i in range(n) if not is_local[i]]
        first_global = sum(is_local)
        hdr = elf._shdr_off(sec.index)
        if order != list(range(n)):
            remap = {old: new for new, old in enumerate(order)}
            for new, old in enumerate(order):
                data[sec.offset + new * 16: sec.offset + (new + 1) * 16] = entries[old]
            for rs in elf.sections:
                if rs.type not in (SHT_REL, SHT_RELA):
                    continue
                link = struct.unpack_from("<I", data, elf._shdr_off(rs.index) + 24)[0]
                if link != sec.index:
                    continue
                step = 8 if rs.type == SHT_REL else 12
                for off in range(rs.offset, rs.offset + rs.size, step):
                    (info,) = struct.unpack_from("<I", data, off + 4)
                    struct.pack_into("<I", data, off + 4, (remap[info >> 8] << 8) | (info & 0xFF))
            changed = True
        if struct.unpack_from("<I", data, hdr + 28)[0] != first_global:
            struct.pack_into("<I", data, hdr + 28, first_global)
            changed = True
    if changed:
        path.write_bytes(bytes(data))
    return changed


def cmd_fix_obj(args, cfg) -> int:
    for p in args.objects:
        fix_object(Path(p))
    return 0


def object_functions(obj: Path) -> list[tuple[str, str]]:
    """(symbol, section) for each function defined in an object."""
    elf = Elf.load(obj)
    out = []
    for s in elf.symbols():
        if s.type == STT_FUNC and s.shndx and s.shndx < len(elf.sections):
            out.append((s.name, elf.sections[s.shndx].name))
    return out


def symbol_address(sym: str, registry: dict[str, int]) -> int | None:
    if sym in registry:
        return registry[sym]
    m = PLACEHOLDER_RE.match(sym)
    return int(m.group(1), 16) if m else None


def cmd_link_script(args, cfg) -> int:
    """After compiling: pin each function's section at its original address."""
    registry = load_registry()
    layout = {f.addr: f for f in load_layout()}
    placements, errors = [], []
    for src in iter_sources():
        obj = obj_for(src)
        for sym, sec in object_functions(obj):
            addr = symbol_address(sym, registry)
            rel = src.relative_to(ROOT).as_posix()
            if addr is None:
                errors.append(f"{rel}: {sym} has no address (add it to functions.tsv or name it func_XXXXXXXX)")
            elif addr not in layout:
                errors.append(f"{rel}: {sym} at 0x{addr:08x} is not a function start in layout.tsv")
            elif sec != f".text.{sym}":
                errors.append(f"{rel}: {sym} is in section {sec}, expected .text.{sym} (-ffunction-sections)")
            else:
                placements.append((addr, sym, obj.relative_to(ROOT).as_posix(), rel))
    seen: dict[int, str] = {}
    for addr, sym, _obj, rel in placements:
        if addr in seen:
            errors.append(f"0x{addr:08x} defined twice: {seen[addr]} and {rel}")
        seen[addr] = rel
    if errors:
        print("\n".join(f"error: {e}" for e in errors), file=sys.stderr)
        return 1
    placements.sort()
    secs = [f"  .f_{a:08x} 0x{a:08x} : {{ KEEP({obj}(.text.{sym})) }}" for a, sym, obj, _ in placements]
    (GEN / "functions.ld").write_text("/* Auto-generated by tools/kh1tool.py link-script */\n"
                                      + "\n".join(secs) + "\n")
    PLACEMENTS.write_text("addr\tsymbol\tobject\tsource\n" + "".join(
        f"{a:08x}\t{s}\t{o}\t{r}\n" for a, s, o, r in placements))
    print(f"link-script: {len(placements)} functions placed")
    return 0


def load_placements() -> list[tuple[int, str, str, str]]:
    if not PLACEMENTS.exists():
        return []
    out = []
    for line in PLACEMENTS.read_text().splitlines()[1:]:
        a, s, o, r = line.split("\t")
        out.append((int(a, 16), s, o, r))
    return out


# --------------------------------------------------------------------------- patch / verify

def cmd_patch(args, cfg) -> int:
    orig = require_orig(cfg)
    layout = {f.addr: f for f in load_layout()}
    data = bytearray(orig.data)
    placements = load_placements()
    linked = Elf.load(LINKED) if placements else None
    bad = 0
    for addr, sym, _obj, src in placements:
        sec = linked.section(f".f_{addr:08x}")
        f = layout[addr]
        if sec is None or sec.addr != addr:
            print(f"error: {sym}: section .f_{addr:08x} missing from linked ELF", file=sys.stderr)
            return 1
        code = linked.data[sec.offset: sec.offset + sec.size]
        if len(code) > f.size:
            print(f"warning: {sym} ({src}) is {len(code)} bytes, original is {f.size}; truncated")
            bad += 1
            code = code[: f.size]
        code = code + bytes(f.size - len(code))
        off = orig.vaddr_to_offset(addr)
        data[off: off + f.size] = code
    PATCHED.parent.mkdir(parents=True, exist_ok=True)
    PATCHED.write_bytes(bytes(data))
    print(f"patch: {len(placements)} functions written to {PATCHED.relative_to(ROOT)}")
    return 0


def function_status(cfg) -> dict[int, str]:
    """addr -> matched | nonmatching | asm"""
    orig = require_orig(cfg)
    built = Elf.load(PATCHED) if PATCHED.exists() else None
    placed = {a for a, *_ in load_placements()}
    status = {}
    for f in load_layout():
        if f.addr not in placed or built is None:
            status[f.addr] = "asm"
        else:
            status[f.addr] = "matched" if orig.read(f.addr, f.size) == built.read(f.addr, f.size) else "nonmatching"
    return status


def cmd_verify(args, cfg) -> int:
    orig = orig_path(cfg).read_bytes()
    built = PATCHED.read_bytes()
    st = function_status(cfg)
    names = {a: s for a, s, *_ in load_placements()}
    nonm = [a for a, s in st.items() if s == "nonmatching"]
    for a in nonm:
        print(f"NONMATCHING 0x{a:08x} {names.get(a, '')}")
    if orig == built:
        print(f"OK: {PATCHED.name} is byte-identical to the original "
              f"({sum(1 for s in st.values() if s == 'matched')} decompiled functions)")
        return 0
    print(f"FAIL: {len(nonm)} decompiled function(s) differ from the original")
    return 1


# --------------------------------------------------------------------------- progress

def segment_of(cfg, addr: int) -> str:
    for seg in cfg.get("segment", []):
        if parse_int(seg["start"]) <= addr < parse_int(seg["end"]):
            return seg["name"]
    return "other"


def gather_progress(cfg) -> dict:
    layout = load_layout()
    st = function_status(cfg)
    by_src = {a: r for a, _s, _o, r in load_placements()}
    report = load_objdiff_report()
    groups: dict[str, dict] = defaultdict(lambda: {"funcs": 0, "matched": 0, "nonmatching": 0,
                                                    "bytes": 0, "matched_bytes": 0})
    disagreements = []
    for f in layout:
        s = st[f.addr]
        if s == "matched" and report is not None:
            pct = report.get(f"func_{f.addr:08x}", report.get(by_src.get(f.addr, ""), None))
            if isinstance(pct, float) and pct < 100.0:
                disagreements.append(f.addr)
        keys = ["total", f"segment:{segment_of(cfg, f.addr)}"]
        if f.addr in by_src:
            parts = Path(by_src[f.addr]).parts
            keys.append(f"dir:src/{parts[1]}" if len(parts) > 2 else "dir:src")
        for key in keys:
            g = groups[key]
            g["funcs"] += 1
            g["bytes"] += f.size
            if s == "matched":
                g["matched"] += 1
                g["matched_bytes"] += f.size
            elif s == "nonmatching":
                g["nonmatching"] += 1
    return {"groups": dict(groups), "objdiff_disagreements": disagreements}


def pct(a: int, b: int) -> str:
    return f"{100.0 * a / b:.2f}%" if b else "0.00%"


def cmd_progress(args, cfg) -> int:
    prog = gather_progress(cfg)
    g = prog["groups"]
    tot = g.get("total", {"funcs": 0, "matched": 0, "nonmatching": 0, "bytes": 0, "matched_bytes": 0})
    print(f"Functions matched: {tot['matched']}/{tot['funcs']} ({pct(tot['matched'], tot['funcs'])})")
    print(f"Code bytes matched: {tot['matched_bytes']}/{tot['bytes']} ({pct(tot['matched_bytes'], tot['bytes'])})")
    print(f"Decompiled but not matching: {tot['nonmatching']}")
    for key in sorted(k for k in g if k != "total"):
        v = g[key]
        print(f"  {key:<24} {v['matched']:>6}/{v['funcs']:<6} {pct(v['matched_bytes'], v['bytes']):>8} of bytes")
    if prog["objdiff_disagreements"]:
        print("warning: objdiff reports <100% for byte-identical functions: "
              + ", ".join(f"0x{a:08x}" for a in prog["objdiff_disagreements"]))
    OUT.mkdir(exist_ok=True)
    (OUT / "progress.json").write_text(json.dumps(prog, indent=2))
    (OUT / "badge.json").write_text(json.dumps({
        "schemaVersion": 1, "label": cfg["target"]["elf"],
        "message": pct(tot["matched_bytes"], tot["bytes"]), "color": "blue"}))
    if args.write:
        write_progress_md(cfg, prog)
    return 0


def write_progress_md(cfg, prog) -> None:
    g = prog["groups"]
    tot = g["total"]
    hist = ROOT / "docs" / "progress-history.tsv"
    today = dt.date.today().isoformat()
    rows = hist.read_text().splitlines() if hist.exists() else ["date\tmatched\tfunctions\tmatched_bytes\tbytes\tnonmatching"]
    rows = [r for r in rows if not r.startswith(today)]
    rows.append(f"{today}\t{tot['matched']}\t{tot['funcs']}\t{tot['matched_bytes']}\t{tot['bytes']}\t{tot['nonmatching']}")
    hist.write_text("\n".join(rows) + "\n")

    def table(keys):
        out = ["| Group | Matched / functions | % functions | % code bytes | Decompiled, not matching |",
               "|---|---|---|---|---|"]
        for k in keys:
            v = g[k]
            out.append(f"| {k} | {v['matched']} / {v['funcs']} | {pct(v['matched'], v['funcs'])} | "
                       f"{pct(v['matched_bytes'], v['bytes'])} | {v['nonmatching']} |")
        return "\n".join(out)

    md = [f"# Progress: {cfg['target']['elf']}", "",
          "Regenerate with `make progress-update` at the end of each session and commit the result.",
          "A function counts as matched only when its rebuilt bytes are identical to the original",
          "and objdiff reports 100% for it.", "",
          f"_Last updated {today}._", "", "## Overall", "", table(["total"]), "",
          "## By address segment (`[[segment]]` in kh1.toml)", "",
          table(sorted(k for k in g if k.startswith("segment:"))), "",
          "## By source directory (decompiled functions only)", "",
          table(sorted(k for k in g if k.startswith("dir:"))) if any(k.startswith("dir:") for k in g)
          else "_No decompiled functions yet._", "",
          "## History", "", "See `docs/progress-history.tsv` (one row per session).", ""]
    (ROOT / "docs" / "progress.md").write_text("\n".join(md))
    print("wrote docs/progress.md and docs/progress-history.tsv")


# --------------------------------------------------------------------------- objdiff

def words_asm(name: str, blob: bytes) -> str:
    lines = [f".globl {name}", f".type {name}, @function", f"{name}:"]
    for i in range(0, len(blob), 4):
        lines.append(f"  .word 0x{struct.unpack_from('<I', blob, i)[0]:08x}")
    lines.append(f".size {name}, . - {name}")
    return "\n".join(lines)


def cmd_objdiff(args, cfg) -> int:
    """One objdiff unit per source file. Target = original bytes, base = our
    patched bytes, both post-link so relocations resolve identically."""
    orig = require_orig(cfg)
    built = Elf.load(PATCHED)
    layout = {f.addr: f for f in load_layout()}
    by_src: dict[str, list[tuple[int, str]]] = defaultdict(list)
    for a, sym, _o, rel in load_placements():
        by_src[rel].append((a, sym))
    units = []
    for d in ("target", "base", "asm"):
        (OBJDIFF_DIR / d).mkdir(parents=True, exist_ok=True)
    for rel, funcs in sorted(by_src.items()):
        unit = rel.replace("/", "__")
        objs = {}
        for side, img in (("target", orig), ("base", built)):
            body = "\n".join(words_asm(sym, img.read(a, layout[a].size)) for a, sym in sorted(funcs))
            asm = OBJDIFF_DIR / "asm" / f"{unit}.{side}.s"
            asm.write_text(".set noreorder\n.set noat\n.text\n" + body + "\n")
            obj = OBJDIFF_DIR / side / f"{unit}.o"
            subprocess.run([f"{BINUTILS}as", "-march=r5900", "-EL", "-G0", "-o", str(obj), str(asm)], check=True)
            objs[side] = obj.relative_to(ROOT).as_posix()
        fl = flags_for(cfg, rel)
        units.append({
            "name": rel,
            "target_path": objs["target"],
            "base_path": objs["base"],
            "metadata": {"source_path": rel, "complete": all(
                orig.read(a, layout[a].size) == built.read(a, layout[a].size) for a, _ in funcs)},
            "scratch": {"platform": "ps2", "compiler": fl.compiler,
                        "c_flags": (fl.cxxflags if rel.endswith((".cpp", ".cc")) else fl.cflags),
                        "ctx_path": None, "build_ctx": False},
        })
    config = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "min_version": "2.0.0",
        "custom_make": "make",
        "build_target": False,
        "build_base": True,
        "watch_patterns": ["src/**/*.c", "src/**/*.cpp", "src/**/*.s", "include/**/*.h", "functions.tsv"],
        "units": units,
    }
    OBJDIFF_JSON.write_text(json.dumps(config, indent=2) + "\n")
    print(f"objdiff: {len(units)} units written to objdiff.json")
    return 0


def objdiff_cli() -> str | None:
    local = TOOLCHAIN_DIR / "objdiff-cli"
    return str(local) if local.exists() else shutil.which("objdiff-cli")


def cmd_objdiff_report(args, cfg) -> int:
    cli = objdiff_cli()
    if cli is None:
        sys.exit("error: objdiff-cli not found; run tools/setup_toolchain.sh")
    out = OBJDIFF_DIR / "report.json"
    subprocess.run([cli, "report", "generate", "-p", str(ROOT), "-o", str(out), "-f", "json"], check=True)
    rep = json.loads(out.read_text())
    for unit in rep.get("units", []):
        for fn in unit.get("functions", []):
            print(f"{fn.get('fuzzy_match_percent', 0.0):7.2f}%  {unit['name']}  {fn['name']}")
    return 0


def load_objdiff_report() -> dict[str, float] | None:
    path = OBJDIFF_DIR / "report.json"
    if not path.exists():
        return None
    out = {}
    for unit in json.loads(path.read_text()).get("units", []):
        for fn in unit.get("functions", []):
            out[fn["name"]] = float(fn.get("fuzzy_match_percent", 0.0))
    return out


# --------------------------------------------------------------------------- main

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("check", help="hash the original ELF and compare with kh1.toml")
    p = sub.add_parser("config", help="print a kh1.toml value (dotted key)")
    p.add_argument("key")
    p = sub.add_parser("layout", help="(re)generate layout.tsv from the original ELF")
    p.add_argument("--ghidra", help="import a Ghidra function list (CSV/TSV) instead of scanning")
    sub.add_parser("gen", help="write out/gen/objects.mk and symbols.ld")
    p = sub.add_parser("fix-obj", help="repair ee-as 2.10 symbol tables for modern ld")
    p.add_argument("objects", nargs="+")
    sub.add_parser("link-script", help="write out/gen/functions.ld from compiled objects")
    sub.add_parser("patch", help="patch linked functions into a copy of the original")
    sub.add_parser("verify", help="compare out/kh1.elf with the original")
    p = sub.add_parser("progress", help="print progress; --write updates docs/progress.md")
    p.add_argument("--write", action="store_true")
    sub.add_parser("objdiff", help="write objdiff.json and unit objects")
    sub.add_parser("objdiff-report", help="run objdiff-cli report and print per-function match")
    args = ap.parse_args()
    cfg = load_config()
    if args.cmd == "config":
        print(cfg_get(cfg, args.key))
        return 0
    return {
        "check": cmd_check, "fix-obj": cmd_fix_obj, "layout": cmd_layout, "gen": cmd_gen, "link-script": cmd_link_script,
        "patch": cmd_patch, "verify": cmd_verify, "progress": cmd_progress,
        "objdiff": cmd_objdiff, "objdiff-report": cmd_objdiff_report,
    }[args.cmd](args, cfg)


if __name__ == "__main__":
    sys.exit(main())
