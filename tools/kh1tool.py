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
DATA_PLACEMENTS = GEN / "data.tsv"
OBJDIFF_DIR = OUT / "objdiff"
OBJDIFF_JSON = ROOT / "objdiff.json"
BINUTILS = os.environ.get("KH1_BINUTILS_PREFIX", "mips-linux-gnu-")

SOURCE_SUFFIXES = {".c": "c", ".cpp": "cxx", ".cc": "cxx", ".s": "asm", ".S": "asm"}
ADDR_REF_RE = re.compile(r"\b(?:func|D)_([0-9A-Fa-f]{8})\b")
PLACEHOLDER_RE = re.compile(r"^func_([0-9A-Fa-f]{8})(?:__.*)?$")
DATA_NAME_RE = re.compile(r"^D_([0-9A-Fa-f]{8})$")

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
    no_fill: bool = False  # gas never fills delay slots in .set reorder code (split-rodata --no-fill)
    ccflags: str = ""      # extra flags for the C -> assembly step only (not the assembler)
    as_compiler: str = ""  # toolchain whose driver assembles compiled C (default: compiler)


# A module file picks a flag mode with its name: src/vm/vm_ops.nostrict.c uses the
# override whose `mode` is "nostrict" (kh1.toml; docs/modules.md "Flags"). Dot-files
# (scratch copies) never carry a mode; `gen` rejects an unknown one under src/.
MODE_FILE_RE = re.compile(r"(?:^|/)[^/.][^/]*\.([A-Za-z0-9_]+)\.(?:c|cpp|cc)$")


def flag_modes(cfg: dict) -> dict[str, dict]:
    return {ov["mode"]: ov for ov in cfg["toolchain"].get("override", []) if "mode" in ov}


def flags_for(cfg: dict, rel: str) -> Flags:
    tc = cfg["toolchain"]
    base = Flags(tc["compiler"], tc["cflags"], tc.get("cxxflags", tc["cflags"]), tc["asflags"])
    m = MODE_FILE_RE.search(rel)
    best = flag_modes(cfg).get(m.group(1)) if m else None
    for ov in [] if best else tc.get("override", []):
        if rel.startswith(ov["path"]) and (best is None or len(ov["path"]) > len(best["path"])):
            best = ov
    if best is None:
        return base
    return Flags(best.get("compiler", base.compiler), best.get("cflags", base.cflags),
                 best.get("cxxflags", best.get("cflags", base.cxxflags)), best.get("asflags", base.asflags),
                 bool(best.get("no_fill", False)), best.get("ccflags", ""), best.get("as_compiler", ""))


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
    # dot-files are scratch copies (try harnesses); KH1_SKIP: a regex of paths to leave out
    skip = re.compile(os.environ["KH1_SKIP"]) if os.environ.get("KH1_SKIP") else None
    return sorted(p for p in src.rglob("*") if p.suffix in SOURCE_SUFFIXES and p.is_file()
                  and not p.name.startswith(".") and not (skip and skip.search(str(p.relative_to(ROOT)))))


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
        if op == 2:  # j to a frame-allocating prologue: a function entered by a tail call
            tgt = ((start + i * 4 + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
            if start <= tgt < end and is_prologue(word_at(tgt)):
                starts.add(tgt)
        if w == JR_RA:
            a = start + i * 4 + 8
            while word_at(a) == 0:
                a += 4
            if is_prologue(word_at(a)):
                starts.add(a)

    # EE kernel syscall stubs (`li $v1,N; syscall; jr $ra; nop`) sit back to
    # back with no prologue and are mostly reached through tail calls.
    for i, w in enumerate(words[1:], 1):
        if w == 0x0000000C and words[i - 1] >> 16 == 0x2403:
            a = start + (i - 1) * 4
            if follows_function_end(a):
                starts.add(a)

    # Switch jump tables: `lui $at,%hi(T); addu $at,$at,$r; lw $r,%lo(T)($at);
    # ... jr $r`, bounded by an earlier `sltiu $x,$y,N`. Their entries point at
    # case labels inside a function (often right after a `jr $ra`), so they
    # must not be mistaken for function pointers below.
    case_labels: set[int] = set()
    for i, w in enumerate(words):
        if w >> 26 != 0 or w & 0x3F != 0x08 or (w >> 21) & 31 == 31:
            continue  # want jr $r, r != ra
        reg = (w >> 21) & 31
        lo = hi = None
        count = None
        for j in range(i - 1, max(i - 12, -1), -1):
            x = words[j]
            if lo is None and x >> 26 == 0x23 and (x >> 16) & 31 == reg:  # lw reg, lo(base)
                lo, base = x & 0xFFFF, (x >> 21) & 31
            elif lo is not None and hi is None and x >> 26 == 0x0F and (x >> 16) & 31 == base:
                hi = x & 0xFFFF
            elif x >> 26 == 0x0B and count is None:  # sltiu
                count = x & 0xFFFF
        if lo is None or hi is None:
            continue
        table = ((hi << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
        jr_addr = start + i * 4
        for k in range(count if count else 1024):
            blob = elf.read(table + k * 4, 4)
            if blob is None:
                break
            (t,) = struct.unpack("<I", blob)
            if not (start <= t < end) or abs(t - jr_addr) > 0x10000:
                break
            case_labels.add(t)

    # Code pointers in non-code loaded data (vtables, callback tables). Jump
    # tables also point into code, so only accept addresses that follow a
    # function end and are not known case labels.
    for seg in elf.segments:
        if seg.type != PT_LOAD:
            continue
        blob = elf.data[seg.offset: seg.offset + seg.filesz]
        for j in range(0, len(blob) - 3, 4):
            va = seg.vaddr + j
            if start <= va < end:
                continue
            (p,) = struct.unpack_from("<I", blob, j)
            if start <= p < end and p % 4 == 0 and p not in case_labels and follows_function_end(p):
                starts.add(p)

    # A `jr $ra` that no earlier branch in the function jumps past ends the
    # function: whatever follows is a new one reached only by pointer or tail
    # call (gcc places every block of a function before its last return or
    # branches to it). Not applied after a jump-table `jr`.
    ordered = sorted(starts)
    for k, a in enumerate(ordered):
        e = ordered[k + 1] if k + 1 < len(ordered) else end
        reach, pos = a, a
        while pos < e - 8:
            w = word_at(pos)
            o = w >> 26
            if o in (4, 5, 6, 7, 20, 21, 22, 23) or (o == 1 and (w >> 16) & 31 in (0, 1, 2, 3, 16, 17, 18, 19)) \
                    or (o in (17, 18) and (w >> 21) & 31 == 8):
                off = w & 0xFFFF
                reach = max(reach, pos + 4 + ((off - 0x10000 if off & 0x8000 else off) << 2))
            sibcall = False
            if o == 2:
                t = ((pos + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                if a <= t < e:
                    reach = max(reach, t)
                else:
                    sibcall = True  # tail call: ends the function like `jr $ra`
            elif o == 0 and w & 0x3F in (0x08, 0x09) and w != JR_RA and w & 0x3F == 0x08:
                break  # jump table: case blocks follow
            if (w == JR_RA or sibcall) and reach <= pos + 4:
                n = pos + 8
                while n < e and word_at(n) == 0:
                    n += 4
                if n < e:
                    starts.add(n)
                    reach = n
                pos = n
                continue
            pos += 4

    ordered = sorted(starts)
    funcs = []
    for k, a in enumerate(ordered):
        e = ordered[k + 1] if k + 1 < len(ordered) else end
        while e - 4 > a and word_at(e - 4) == 0 and word_at(e - 8) != JR_RA and word_at(e - 8) >> 26 != 2:
            e -= 4  # drop alignment padding, keep the delay slot after jr ra / a tail call
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

# ee-gcc 2.96 emits GOFAST names for double-precision libcalls (the EE FPU is
# single precision); the retail build linked libgcc fp-bit under the usual
# names. Same calling conventions, so each alias resolves to the original.
LIBCALL_ALIASES = {
    "dpadd": "__adddf3", "dpsub": "__subdf3", "dpmul": "__muldf3", "dpdiv": "__divdf3",
    "dpcmp": "__cmpdf2", "fptodp": "__extendsfdf2", "dptofp": "__truncdfsf2",
    "litodp": "__floatsidf", "dptoli": "__fixdfsi", "dptoul": "__fixunsdfsi",
}


def cmd_gen(args, cfg) -> int:
    """Write out/gen/objects.mk (per-source compile rules) and symbols.ld."""
    GEN.mkdir(parents=True, exist_ok=True)
    rules, objs = [], []
    skip_dsec = cfg["toolchain"].get("data_sections_skip", [])
    modes = flag_modes(cfg)
    for src in iter_sources():
        rel = src.relative_to(ROOT).as_posix()
        m = MODE_FILE_RE.search(rel)
        if m and m.group(1) not in modes:
            sys.exit(f"error: {rel}: unknown flag mode '{m.group(1)}' (kh1.toml modes: {', '.join(sorted(modes))})")
        obj = obj_for(src).relative_to(ROOT).as_posix()
        kind = SOURCE_SUFFIXES[src.suffix]
        fl = flags_for(cfg, rel)
        tc = f"$(TOOLCHAIN)/{fl.compiler}/bin"
        atc = f"$(TOOLCHAIN)/{fl.as_compiler or fl.compiler}/bin"
        if kind == "asm":
            cmd = f"$(AS) {fl.asflags} -o $@ {rel}"
        else:
            lang, flags = ("c++", fl.cxxflags) if kind == "cxx" else ("c", fl.cflags)
            # Compile to assembly, give each function its own .rodata.<fn>
            # section (split-rodata), then assemble with the same driver.
            # Game code: each global variable in its own section (.data.<name>), so a
            # table defined in C can be placed at its original address (data_placements).
            dsec = "" if rel.startswith(tuple(skip_dsec)) else " -fdata-sections -fno-common"
            cmd = (f"{tc}/ee-gcc -S -x {lang} {flags} {fl.ccflags} -ffunction-sections{dsec} $(INCLUDES) "
                   f"-o $(@:.o=.s) {rel} && $(KH1) split-rodata {'--no-fill ' if fl.no_fill else ''}$(@:.o=.s) && "
                   f"{atc}/ee-gcc -c -x assembler {flags} -o $@ $(@:.o=.s) && $(KH1) fix-obj $@")
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
    # GOFAST libcall names -> libgcc routines (LIBCALL_ALIASES, docs/toolchain.md).
    for alias, target in LIBCALL_ALIASES.items():
        if target in provides:
            provides.setdefault(alias, provides[target])
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
    if strip_context_only(data, path):
        changed = True
    if changed:
        path.write_bytes(bytes(data))
    return changed


def is_ctx_section(name: str) -> bool:
    """Sections of CONTEXT_ONLY functions (include/common.h): .ctx, and the
    .ctx.rodata.* that split_rodata gives their constants and jump tables."""
    return name == ".ctx" or name.startswith(".ctx.")


def strip_context_only(data: bytearray, path: Path) -> bool:
    """A CONTEXT_ONLY function is compiled only so gcc 2.96 knows its
    register use when it compiles the callers below it (the callee-earlier
    effect, docs/context-only-plan.md); its code is never placed. Every
    global or weak symbol defined in a .ctx section becomes an undefined
    global, so callers resolve to the original address (symbols.ld) or to the
    real matched definition in another file. weak keeps ee-as from turning
    calls into relocations against the .ctx section symbol; a static
    CONTEXT_ONLY function would, which is an error."""
    elf = Elf(bytes(data), path)
    ctx = {sec.index for sec in elf.sections if is_ctx_section(sec.name)}
    if not ctx:
        return False
    changed = False
    for sec in elf.sections:
        if sec.type != SHT_SYMTAB:
            continue
        for i in range(sec.size // 16):
            off = sec.offset + i * 16
            info, shndx = data[off + 12], struct.unpack_from("<H", data, off + 14)[0]
            if shndx in ctx and info >> 4 in (1, 2):  # GLOBAL, WEAK
                struct.pack_into("<IIBBH", data, off + 4, 0, 0, (1 << 4) | (info & 0xF), 0, 0)
                changed = True
    syms = elf.symbols()
    for sec in elf.sections:
        if is_ctx_section(sec.name) or not sec.name.startswith((".text", ".rodata", ".data")):
            continue
        for _off, _typ, si in elf.relocations(sec):
            if si < len(syms) and syms[si].type == 3 and syms[si].shndx in ctx:  # STT_SECTION
                raise SystemExit(f"error: {path}: {sec.name} refers to a static CONTEXT_ONLY "
                                 f"function or its data; make it non-static")
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


RDATA_RE = re.compile(r"^\s*(\.rdata|\.section\s+\.rodata)\b")
SECTION_RE = re.compile(r"^\s*(?:\.section\s+([\w.$]+)|(\.text|\.data|\.rdata|\.bss)\b)")
ENT_RE = re.compile(r"^\s*\.ent\s+([\w.$]+)")
END_RE = re.compile(r"^\s*\.end\s+([\w.$]+)")
RODATA_PLACEMENTS = GEN / "rodata.tsv"


def split_rodata(text: str) -> str:
    """gcc 2.96 puts every function's string literals, float/double constants
    and jump tables into one .rodata per object. Move each function's pieces
    into .rodata.<function> so they can be linked at their original address
    one function at a time. Constants are emitted just before the function
    that uses them (or inside it, for jump tables), so a .rdata block between
    functions belongs to the next .ent; blocks inside a function get
    .rodata.<function>.<n>; trailing blocks stay in .rodata."""
    lines = text.splitlines()
    ents = [(i, m.group(1)) for i, l in enumerate(lines) if (m := ENT_RE.match(l))]
    # CONTEXT_ONLY functions (section .ctx): their rodata is .ctx.rodata.*,
    # which is never placed (see fix_object).
    ctx_funcs, sec = set(), ".text"
    for line in lines:
        if m := SECTION_RE.match(line):
            sec = m.group(1) or m.group(2)
        elif m := ENT_RE.match(line):
            if is_ctx_section(sec):
                ctx_funcs.add(m.group(1))
    out, cur, k, inner = [], None, 0, 0
    for i, line in enumerate(lines):
        if m := ENT_RE.match(line):
            cur, inner = m.group(1), 0
        elif END_RE.match(line):
            cur = None
        elif RDATA_RE.match(line):
            while k < len(ents) and ents[k][0] < i:
                k += 1
            owner = cur or (ents[k][1] if k < len(ents) else None)
            prefix = ".ctx.rodata" if owner in ctx_funcs else ".rodata"
            if cur:
                # a block inside the function (a jump table) is its own
                # section: the assembler's literal pool (`li.d` constants,
                # in plain .rodata) can sit between it and the strings
                # before the function (_dtoa_r)
                inner += 1
                line = f'\t.section {prefix}.{owner}.{inner},"a",@progbits'
            elif owner:
                line = f'\t.section {prefix}.{owner},"a",@progbits'
        out.append(line)
    return "\n".join(out) + "\n"


REORDER_JUMPS = re.compile(r"\t(jal|jalr|j|jr|b|beq|bne|beqz|bnez|bgez|bgtz|blez|bltz|bc1t|bc1f)\t")


def no_fill(text: str) -> str:
    """Emulate the assembler the SDK's newlib was built with: it never fills a
    delay slot in `.set reorder` code (ee-as 2.9-990721 behaves the same);
    ee-as 2.96 moves the previous instruction into it. Each such jump is
    wrapped in `.set noreorder` with an explicit nop. Slots gcc fills itself
    (in its own noreorder blocks) are untouched. docs/toolchain.md."""
    out: list[str] = []
    reorder = True
    for line in text.split("\n"):
        st = line.strip()
        if st == ".set\tnoreorder" or st == ".set noreorder":
            reorder = False
        elif st == ".set\treorder" or st == ".set reorder":
            reorder = True
        if reorder and REORDER_JUMPS.match(line):
            out += ["\t.set\tnoreorder", line, "\tnop", "\t.set\treorder"]
            continue
        out.append(line)
    return "\n".join(out)


def cmd_split_rodata(args, cfg) -> int:
    for p in args.files:
        path = Path(p)
        text = split_rodata(path.read_text())
        if args.no_fill:
            text = no_fill(text)
        path.write_text(text)
    return 0


def sext16(v: int) -> int:
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def infer_rodata(obj: Path, placed: dict[str, int], orig: Elf) -> tuple[dict[str, int], list[str]]:
    """Original address of each .rodata.* section in `obj`, inferred from the
    %hi/%lo pairs that reference it: the original instruction pair at the same
    offset in the placed function holds the original address, our pair holds
    the offset inside our section. Returns ({section: addr}, problems)."""
    from elf32 import R_MIPS_HI16, R_MIPS_LO16
    elf = Elf.load(obj)
    syms = elf.symbols()
    rodata = {sec.index: sec for sec in elf.sections if sec.name.startswith(".rodata")}
    cands: dict[str, set[int]] = defaultdict(set)
    for sec in elf.sections:
        if not sec.name.startswith(".text."):
            continue
        fn = sec.name[len(".text."):]
        if fn not in placed:
            continue
        ours = elf.section_bytes(sec)
        theirs = orig.read(placed[fn], sec.size) or b""
        if len(theirs) < sec.size:
            continue
        last_hi: dict[int, int] = {}
        for off, typ, si in elf.relocations(sec):
            if typ == R_MIPS_HI16:
                last_hi[si] = off
                continue
            if typ != R_MIPS_LO16 or si not in last_hi or si >= len(syms):
                continue
            sym = syms[si]
            if sym.shndx not in rodata:
                continue
            hi = last_hi[si]
            ow_hi, ow_lo = (struct.unpack_from("<I", ours, o)[0] for o in (hi, off))
            tw_hi, tw_lo = (struct.unpack_from("<I", theirs, o)[0] for o in (hi, off))
            our_off = ((ow_hi & 0xFFFF) << 16) + sext16(ow_lo) + sym.value
            their_addr = (((tw_hi & 0xFFFF) << 16) + sext16(tw_lo)) & 0xFFFFFFFF
            cands[rodata[sym.shndx].name].add(their_addr - our_off)
    found, problems = {}, []
    for name, addrs in cands.items():
        if len(addrs) == 1:
            found[name] = addrs.pop()
        else:
            problems.append(f"{obj.name}: {name}: references disagree on its original address "
                            f"({', '.join(f'0x{a:08x}' for a in sorted(addrs))}); the code does not match yet")
    for sec in rodata.values():
        if sec.size and sec.name not in found and sec.name not in cands:
            problems.append(f"{obj.name}: {sec.name}: no placed function references it; left unplaced")
    return found, problems


def symbol_address(sym: str, registry: dict[str, int]) -> int | None:
    if sym in registry:
        return registry[sym]
    m = PLACEHOLDER_RE.match(sym)
    return int(m.group(1), 16) if m else None


def object_data(obj: Path) -> tuple[list[tuple[str, str, int]], list[str]]:
    """Global variables defined in C (-fdata-sections: section .data.<name>, phase 4):
    (symbol, section, size) for each, and the names of any other non-empty data
    sections (statics in plain .data/.bss, which cannot be placed)."""
    elf = Elf.load(obj)
    out, stray = [], []
    by_sec: dict[int, list] = defaultdict(list)
    for s in elf.symbols():
        if s.shndx and s.shndx < len(elf.sections) and s.bind in (1, 2) and s.name:
            by_sec[s.shndx].append(s)
    for sec in elf.sections:
        if not sec.size or sec.flags & 2 == 0:  # SHF_ALLOC
            continue
        if sec.name.startswith(".data."):
            name = sec.name[len(".data."):]
            if not any(x.name == name and x.value == 0 for x in by_sec.get(sec.index, [])):
                stray.append(sec.name)
                continue
            out.append((name, sec.name, sec.size))
        elif sec.name in (".data", ".bss", ".sdata", ".sbss") or sec.name.startswith((".bss.", ".sdata.", ".sbss.")):
            stray.append(sec.name)
    return out, stray


def data_region(cfg, orig: Elf, addr: int, size: int) -> str | None:
    """'data' (file-backed, after code), 'bss' (in the load segment but not in the
    file), or None if [addr, addr+size) is not inside one of them."""
    text_end = parse_int(cfg["target"]["text_end"])
    seg = next(s for s in orig.segments if s.type == PT_LOAD and s.vaddr <= text_end < s.vaddr + s.memsz)
    if not (text_end <= addr and addr + size <= seg.vaddr + seg.memsz):
        return None
    file_end = seg.vaddr + seg.filesz
    if addr + size <= file_end:
        return "data"
    return "bss" if addr >= file_end else None


def load_data_placements() -> list[tuple[int, str, str, int, str]]:
    """(addr, symbol, object, size, region) of the variables C defines (out/gen/data.tsv)."""
    if not DATA_PLACEMENTS.exists():
        return []
    out = []
    for line in DATA_PLACEMENTS.read_text().splitlines()[1:]:
        a, n, o, sz, reg = line.split("\t")
        out.append((int(a, 16), n, o, int(sz, 16), reg))
    return out


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
    # Variables defined in C (phase 4): each .data.<name> at the address of <name>.
    data_rows = []
    orig_d = None
    for src in iter_sources():
        obj = obj_for(src)
        rel = src.relative_to(ROOT).as_posix()
        # C sources, and the data pieces of src/data/*.s (phase 4 step 4: PIECE, one
        # .incbin section per name, tools/shift/define_pieces.py)
        if src.suffix not in (".c", ".cpp", ".cc") and not (src.suffix == ".s" and rel.startswith("src/data/")):
            continue
        found, stray = object_data(obj)
        for sec in stray:
            errors.append(f"{rel}: data section {sec} cannot be placed: define each variable as a "
                          f"non-static global with a D_XXXXXXXX or functions.tsv name")
        for name, sec, size in found:
            m = DATA_NAME_RE.match(name)
            addr = registry.get(name, int(m.group(1), 16) if m else None)
            if addr is None:
                errors.append(f"{rel}: variable {name} has no address (name it D_XXXXXXXX or add it to functions.tsv)")
                continue
            orig_d = orig_d or require_orig(cfg)
            region = data_region(cfg, orig_d, addr, size)
            if region is None:
                errors.append(f"{rel}: {name} (0x{addr:08x}, 0x{size:x} bytes) is not inside the data or bss of the image")
                continue
            data_rows.append((addr, name, obj.relative_to(ROOT).as_posix(), size, region, rel))
    data_rows.sort()
    for (a1, n1, _o1, s1, _r1, f1), (a2, n2, _o2, _s2, _r2, f2) in zip(data_rows, data_rows[1:]):
        if a1 + s1 > a2:
            errors.append(f"{n1} ({f1}, 0x{a1:08x}+0x{s1:x}) overlaps {n2} ({f2}, 0x{a2:08x})")
    if errors:
        print("\n".join(f"error: {e}" for e in errors), file=sys.stderr)
        return 1
    placements.sort()
    secs = [f"  .f_{a:08x} 0x{a:08x} : {{ KEEP({obj}(.text.{sym})) }}" for a, sym, obj, _ in placements]
    secs += [f"  .d_{a:08x} 0x{a:08x} : {{ KEEP({obj}(.data.{n})) }}" for a, n, obj, _s, _r, _f in data_rows]
    rodata_rows = []
    by_obj: dict[str, dict[str, int]] = defaultdict(dict)
    for a, sym, obj, _ in placements:
        by_obj[obj][sym] = a
    orig = require_orig(cfg) if by_obj else None
    for obj, placed in sorted(by_obj.items()):
        found, problems = infer_rodata(ROOT / obj, placed, orig)
        for msg in problems:
            print(f"warning: {msg}", file=sys.stderr)
        for name, addr in sorted(found.items(), key=lambda kv: kv[1]):
            secs.append(f"  .r_{addr:08x} 0x{addr:08x} : {{ KEEP({obj}({name})) }}")
            rodata_rows.append((addr, name, obj))
    (GEN / "functions.ld").write_text("/* Auto-generated by tools/kh1tool.py link-script */\n"
                                      + "\n".join(secs) + "\n")
    RODATA_PLACEMENTS.write_text("addr\tsection\tobject\n" + "".join(
        f"{a:08x}\t{n}\t{o}\n" for a, n, o in sorted(rodata_rows)))
    PLACEMENTS.write_text("addr\tsymbol\tobject\tsource\n" + "".join(
        f"{a:08x}\t{s}\t{o}\t{r}\n" for a, s, o, r in placements))
    DATA_PLACEMENTS.write_text("addr\tsymbol\tobject\tsize\tregion\n" + "".join(
        f"{a:08x}\t{n}\t{o}\t{sz:x}\t{reg}\n" for a, n, o, sz, reg, _f in data_rows))
    nb = sum(1 for r in data_rows if r[4] == "bss")
    print(f"link-script: {len(placements)} functions, {len(rodata_rows)} rodata blocks placed"
          + (f", {len(data_rows)} variables ({len(data_rows) - nb} data, {nb} bss)" if data_rows else ""))
    return 0


def load_rodata_placements() -> list[tuple[int, str, str]]:
    if not RODATA_PLACEMENTS.exists():
        return []
    out = []
    for line in RODATA_PLACEMENTS.read_text().splitlines()[1:]:
        a, n, o = line.split("\t")
        out.append((int(a, 16), n, o))
    return out


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
    rodata = load_rodata_placements()
    for addr, name, obj in rodata:
        sec = linked.section(f".r_{addr:08x}")
        off = orig.vaddr_to_offset(addr)
        if sec is None or off is None or orig.vaddr_to_offset(addr + sec.size - 1) is None:
            print(f"error: {name} ({obj}) at 0x{addr:08x} is missing or outside the image", file=sys.stderr)
            return 1
        data[off: off + sec.size] = linked.data[sec.offset: sec.offset + sec.size]
    variables = load_data_placements()
    for addr, name, obj, size, region in variables:
        sec = linked.section(f".d_{addr:08x}")
        if sec is None or sec.addr != addr or sec.size != size:
            if sec is None:
                print(f"error: {name} ({obj}): section .d_{addr:08x} missing from linked ELF", file=sys.stderr)
            else:
                print(f"error: {name} ({obj}): section .d_{addr:08x} is {sec.size:#x} bytes at 0x{sec.addr:08x}, "
                      f"expected {size:#x} at 0x{addr:08x} (an array the compiler aligns to 8 at an address "
                      "that is not, padded at the end?)", file=sys.stderr)
            return 1
        body = linked.data[sec.offset: sec.offset + sec.size] if sec.type != 8 else bytes(size)
        if region == "bss":
            if any(body):
                print(f"error: {name} ({obj}) is in .bss (0x{addr:08x}) but has a non-zero initialiser",
                      file=sys.stderr)
                return 1
            continue  # not in the file; zero at startup
        off = orig.vaddr_to_offset(addr)
        data[off: off + size] = body
    PATCHED.parent.mkdir(parents=True, exist_ok=True)
    PATCHED.write_bytes(bytes(data))
    print(f"patch: {len(placements)} functions, {len(rodata)} rodata blocks"
          + (f", {sum(1 for v in variables if v[4] == 'data')} data variables" if variables else "")
          + f" written to {PATCHED.relative_to(ROOT)}")
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
    if load_rodata_placements():
        o_elf, b_elf, linked = Elf(orig), Elf(built), Elf.load(LINKED)
        for addr, name, obj in load_rodata_placements():
            size = linked.section(f".r_{addr:08x}").size
            if o_elf.read(addr, size) != b_elf.read(addr, size):
                print(f"RODATA MISMATCH 0x{addr:08x} {name} ({obj})")
    if load_data_placements():
        o_elf, b_elf = Elf(orig), Elf(built)
        for addr, name, obj, size, region in load_data_placements():
            if region == "data" and o_elf.read(addr, size) != b_elf.read(addr, size):
                print(f"DATA MISMATCH 0x{addr:08x} {name} ({obj})")
    if orig == built:
        print(f"OK: {PATCHED.name} is byte-identical to the original "
              f"({sum(1 for s in st.values() if s == 'matched')} decompiled functions)")
        return 0
    print(f"FAIL: {len(nonm)} decompiled function(s) differ from the original"
          + ("" if nonm else " (the difference is in placed rodata or data, or outside decompiled code)"))
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
    # One row per session: `make progress-update SESSION=4` (several sessions
    # can fall on one day); a rerun replaces the row with the same date+session.
    session = os.environ.get("SESSION", "")
    header = "date\tsession\tmatched\tfunctions\tmatched_bytes\tbytes\tnonmatching"
    rows = hist.read_text().splitlines()[1:] if hist.exists() else []
    rows = [r for r in rows if r.split("\t")[:2] != [today, session]]
    rows.append(f"{today}\t{session}\t{tot['matched']}\t{tot['funcs']}\t{tot['matched_bytes']}\t{tot['bytes']}\t{tot['nonmatching']}")
    rows = [header] + rows
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


# --------------------------------------------------------------------------- rank

HARD_MMI_FUNCTS = {0x04, 0x08, 0x09, 0x28, 0x29, 0x30, 0x31, 0x34, 0x36, 0x37, 0x3C, 0x3E, 0x3F}
RANK_TSV = OUT / "rank.tsv"
RANK_COLUMNS = ["addr", "size", "insns", "score", "category", "shape", "twins", "calls", "branches",
                "loops", "jumptable", "fpu", "frame", "loads", "stores", "flags", "status", "name"]


def analyze_function(f: Func, blob: bytes) -> dict:
    """Size/complexity metrics for one function (see `rank`)."""
    import mips
    insns = mips.decode(f.addr, blob)
    while insns and insns[-1].word == 0 and len(insns) > 1 and insns[-2].word != mips.JR_RA:
        insns.pop()  # alignment padding
    m = {"insns": len(insns), "calls": 0, "branches": 0, "loops": 0, "jumptable": 0, "fpu": 0,
         "frame": 0, "loads": 0, "stores": 0, "tail": 0}
    flags = set()
    lui_regs: set[int] = set()
    shape = []
    for i in insns:
        w = i.word
        o = mips.op(w)
        masked = w
        if i.is_jal:
            m["calls"] += 1
            masked = w & 0xFC000000
        elif i.is_jalr:
            m["calls"] += 1
        elif i.is_j:
            tgt = i.jump_target
            if not (f.addr <= tgt < f.end):
                m["tail"] += 1
                masked = w & 0xFC000000
        elif i.is_jr and not i.is_jr_ra:
            m["jumptable"] += 1
        if i.is_branch:
            m["branches"] += 1
            if i.branch_target <= i.addr:
                m["loops"] += 1
        if i.is_load:
            m["loads"] += 1
        if i.is_store:
            m["stores"] += 1
        if i.is_fpu:
            m["fpu"] += 1
        if i.stack_adjust is not None and i.stack_adjust < 0:
            m["frame"] = max(m["frame"], -i.stack_adjust)
        if i.is_vu0:
            flags.add("vu0")
        if o in (mips.OP_LQ, mips.OP_SQ):
            flags.add("lq/sq")
        if o == mips.OP_MMI and mips.funct(w) in HARD_MMI_FUNCTS:
            flags.add("mmi")
        if i.is_cop0:
            flags.add("cop0")
        if i.is_syscall:
            flags.add("syscall")
        if i.is_sync:
            flags.add("sync")
        # Shape: mask call targets and %hi/%lo halves so functions that differ
        # only in which globals/callees they use hash together.
        if o == mips.OP_LUI:
            lui_regs.add(mips.rt(w))
            masked = w & 0xFFFF0000
        elif mips.rs(w) in lui_regs and o not in (mips.OP_SPECIAL, mips.OP_REGIMM) and not i.is_branch:
            masked = w & 0xFFFF0000
            if mips.rt(w) in lui_regs and o not in mips.OP_STORES:
                lui_regs.discard(mips.rt(w))
        shape.append(masked)
    leaf = m["calls"] == 0 and m["tail"] == 0
    hard = bool(flags & {"vu0", "lq/sq", "mmi", "cop0", "syscall"})
    n = m["insns"]
    if hard:
        cat = "hard"
    elif n <= 2 and not m["loads"] and not m["stores"]:
        cat = "stub"
    elif leaf and m["branches"] == 0 and m["stores"] == 0 and m["loads"] and n <= 6:
        cat = "getter"
    elif leaf and m["branches"] == 0 and m["stores"] and n <= 10:
        cat = "setter"
    elif m["calls"] == 0 and m["tail"] == 1 and m["branches"] == 0 and n <= 8:
        cat = "thunk"
    elif m["calls"] == 1 and m["branches"] == 0 and n <= 12:
        cat = "wrapper"
    elif leaf and m["loops"] and not m["jumptable"]:
        cat = "loop"
    elif leaf:
        cat = "leaf"
    else:
        cat = "other"
    score = n + 2 * m["branches"] + 4 * m["calls"] + 2 * m["tail"] + 10 * m["jumptable"] + 50 * hard
    m.update(leaf=leaf, category=cat, score=score, flags=",".join(sorted(flags)),
             shape=hashlib.sha1(struct.pack(f"<{len(shape)}I", *shape)).hexdigest()[:10])
    return m


def decompiled_addrs() -> dict[int, str]:
    """addr -> 'src' / 'wip' for functions already in src/ or nonmatchings/."""
    out: dict[int, str] = {}
    registry = load_registry()
    for base, tag in ((ROOT / "nonmatchings", "wip"), (ROOT / "src", "src")):
        for p in sorted(base.rglob("*")):
            if p.suffix not in SOURCE_SUFFIXES or not p.is_file():
                continue
            text = p.read_text(errors="ignore")
            for m in re.finditer(r"^[A-Za-z_][^;{}()]*?\b(func_([0-9A-Fa-f]{8})|\w+)\s*\([^;{]*\)\s*\{",
                                 text, re.M):
                addr = int(m.group(2), 16) if m.group(2) else registry.get(m.group(1))
                if addr is None:
                    continue
                if m.group(0).startswith("CONTEXT_ONLY"):
                    out.setdefault(addr, "wip")  # a copy for its callers, not a match
                else:
                    out[addr] = tag
    return out


def cmd_rank(args, cfg) -> int:
    """Rank functions by size/complexity so the easy ones get done first."""
    elf = require_orig(cfg)
    done = decompiled_addrs()
    rows = []
    for f in load_layout():
        seg = segment_of(cfg, f.addr)
        m = analyze_function(f, elf.read(f.addr, f.size))
        rows.append({"addr": f"{f.addr:08x}", "size": f.size, "segment": seg,
                     "status": done.get(f.addr, "asm"), "name": f.name, **m})
    twins: dict[str, int] = defaultdict(int)
    for r in rows:
        twins[r["shape"]] += 1
    for r in rows:
        r["twins"] = twins[r["shape"]]
    rows.sort(key=lambda r: (r["score"], r["addr"]))
    OUT.mkdir(exist_ok=True)
    with RANK_TSV.open("w") as fh:
        fh.write("\t".join(["segment", *RANK_COLUMNS]) + "\n")
        for r in rows:
            fh.write("\t".join(str(int(v) if isinstance(v, bool) else v)
                               for v in [r["segment"], *(r[c] for c in RANK_COLUMNS)]) + "\n")

    sel = [r for r in rows
           if (args.segment == "all" or r["segment"] == args.segment)
           and (args.all or r["status"] == "asm")
           and (not args.category or r["category"] in args.category.split(","))
           and (not args.leaf or r["leaf"])
           and (args.max_insns is None or r["insns"] <= args.max_insns)]
    if args.summary:
        cats: dict[str, list] = defaultdict(lambda: [0, 0, 0])
        for r in sel:
            c = cats[r["category"]]
            c[0] += 1
            c[1] += r["size"]
            c[2] += r["status"] != "asm"
        print(f"{'category':<10} {'funcs':>6} {'bytes':>9} {'done':>5}")
        for k, (n, b, d) in sorted(cats.items(), key=lambda kv: -kv[1][0]):
            print(f"{k:<10} {n:>6} {b:>9} {d:>5}")
        return 0
    print("addr      insns score category  twins calls br loops  flags          status")
    for r in sel[: args.limit]:
        print(f"{r['addr']}  {r['insns']:>5} {r['score']:>5} {r['category']:<9} {r['twins']:>5} "
              f"{r['calls']:>5} {r['branches']:>2} {r['loops']:>5}  {r['flags'] or '-':<14} {r['status']}")
    print(f"({len(sel)} functions selected; full table in {RANK_TSV.relative_to(ROOT)})")
    return 0


# --------------------------------------------------------------------------- asm / m2c

OBJDUMP_LINE_RE = re.compile(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)$")
REG_RE = re.compile(r"(?<![\w$.%])(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f[0-9]{1,2}|vf[0-9]{1,2}|vi[0-9]{1,2})(?![\w])")


RAM_START, RAM_END = 0x00100000, 0x02000000  # EE main RAM above the kernel


# objdump prints o32 names; registers 8-15 are a4-a7, t0-t3 under the EE's
# EABI, which is what m2c's mipsee target expects (arguments 5-8 in a4-a7).
EABI_NAMES = {"t0": "a4", "t1": "a5", "t2": "a6", "t3": "a7", "t4": "t0", "t5": "t1", "t6": "t2", "t7": "t3"}


# I-type ALU ops and integer loads (incl. ld/lq): the result goes to rt
GPR_RT_WRITERS = {0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x18, 0x19,
                  0x1A, 0x1B, 0x1E, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x37}


@dataclass
class FuncAnalysis:
    """What function_asm knows about one original function (also used by
    tools/asm_export.py --symbolic): the objdump lines, branch/jump labels,
    the %hi/%lo tracker's result and the jump tables it found."""
    insns: list            # (addr, word, mnemonic, operands)
    labels: set            # in-function branch / jump / jump-table targets
    hi_of: dict            # lui addr -> full address (of its first low half)
    lo_of: dict            # low-half user addr -> full address
    lo_hi: dict            # low-half user addr -> the lui addr it pairs with
    jtbls: dict            # table address -> entries (in-function addresses)


def analyze_asm(cfg, f: Func) -> FuncAnalysis:
    import mips
    orig_path_ = orig_path(cfg)
    out = subprocess.run([f"{BINUTILS}objdump", "-D", "-z", "-m", "mips:5900", "-EL",
                          f"--start-address=0x{f.addr:x}", f"--stop-address=0x{f.end:x}",
                          str(orig_path_)], check=True, capture_output=True, text=True).stdout
    insns = []
    for line in out.splitlines():
        m = OBJDUMP_LINE_RE.match(line)
        if m:
            insns.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3), m.group(4)))
    labels = set()
    for a, w, _mn, _ops in insns:
        t = mips.Insn(a, w).branch_target
        if t is not None:
            labels.add(t)
        if mips.op(w) == mips.OP_J and f.addr <= mips.Insn(a, w).jump_target < f.end:
            labels.add(mips.Insn(a, w).jump_target)
    # %hi/%lo: resolve each lui to the addresses its low halves produce.
    hi_of: dict[int, int] = {}   # lui addr -> full address
    lo_of: dict[int, int] = {}   # user addr -> full address
    lo_hi: dict[int, int] = {}   # user addr -> lui addr
    live: dict[int, tuple[int, int]] = {}  # reg -> (lui addr, upper)
    clobber_at = None
    for a, w, mn, _ops in insns:
        o = mips.op(w)
        if a in labels:
            live.clear()
        if a == clobber_at:  # the call (after its delay slot) clobbered caller-saved registers
            for r in [r for r in live if not (16 <= r <= 23 or r in (28, 29, 30))]:
                del live[r]
        if o == 0x03 or (o == mips.OP_SPECIAL and mips.funct(w) == 0x09):  # jal / jalr
            clobber_at = a + 8
        if o == mips.OP_LUI:
            live[mips.rt(w)] = (a, (w & 0xFFFF) << 16)
            continue
        base = mips.rs(w)
        if base in live and (o in (0x09, 0x0D) or o in mips.OP_LOADS or o in mips.OP_STORES
                             or o in mips.OP_VU_MEM or o in (mips.OP_LQ, mips.OP_SQ)):
            lui_a, upper = live[base]
            full = (upper + (mips.imm(w) if o != 0x0D else w & 0xFFFF)) & 0xFFFFFFFF
            # gcc builds addresses with lui/addiu, never lui/ori; and an addiu
            # pair outside EE RAM is a constant (float bits, masks), not data.
            if o == 0x0D or (o == 0x09 and not RAM_START <= full < RAM_END):
                pass
            else:
                hi_of.setdefault(lui_a, full)
                lo_of[a] = full
                lo_hi[a] = lui_a
        # forget a %hi held in a register this instruction overwrites
        if o in (0x11, 0x12):  # COP1/COP2: only mfc/dmfc/cfc write a GPR (rt)
            if mips.rs(w) in (0, 1, 2):
                live.pop(mips.rt(w), None)
        elif o in GPR_RT_WRITERS:
            live.pop(mips.rt(w), None)
        elif o == mips.OP_MMI:
            live.pop(mips.rd(w), None)
        if o == mips.OP_SPECIAL and not (mips.funct(w) in (0x21, 0x2D) and mips.rd(w) == base):
            live.pop(mips.rd(w), None)  # addu/daddu rX,rX,rY keeps rX's %hi (jump tables)

    # Jump tables: a %lo load feeding a `jr`. m2c needs the table contents.
    orig = Elf.load(orig_path_)
    jtbls: dict[int, list[int]] = {}
    count = None
    for k, (a, w, mn, _ops) in enumerate(insns):
        if mips.op(w) == 0x0B:
            count = w & 0xFFFF
        i = mips.Insn(a, w)
        if i.is_jr and not i.is_jr_ra:
            for pa, pw, _m, _o in insns[max(0, k - 3): k]:
                if pa in lo_of and mips.op(pw) == 0x23 and mips.rt(pw) == mips.rs(w):
                    base, entries = lo_of[pa], []
                    for n in range(count or 256):
                        blob = orig.read(base + 4 * n, 4)
                        t = struct.unpack("<I", blob)[0] if blob else 0
                        if not (f.addr <= t < f.end):
                            break
                        entries.append(t)
                    jtbls[base] = entries
                    labels.update(entries)
    return FuncAnalysis(insns, labels, hi_of, lo_of, lo_hi, jtbls)


def function_asm(cfg, f: Func, names: dict[int, str], eabi: bool = False) -> str:
    """GNU-as listing of one original function in the style m2c and decomp.me
    expect: `glabel`, $-prefixed registers, .L labels for branch targets,
    func_/D_ names (or functions.tsv names) for calls and %hi/%lo pairs.
    `eabi` names registers 8-15 a4-a7/t0-t3 (for m2c)."""
    import mips
    an = analyze_asm(cfg, f)
    insns, labels, hi_of, lo_of, jtbls = an.insns, an.labels, an.hi_of, an.lo_of, an.jtbls
    layout = load_layout()
    lo_text, hi_text = layout[0].addr, layout[-1].end

    def sym(addr: int) -> str:
        if addr in names:
            return names[addr]
        if addr in jtbls:
            return f"jtbl_{addr:08X}"
        return f"func_{addr:08x}" if lo_text <= addr < hi_text else f"D_{addr:08X}"

    lines = [f"glabel {names.get(f.addr, f.name)}"]
    for a, w, mn, ops in insns:
        if a in labels:
            lines.append(f".L{a:08X}:")
        i = mips.Insn(a, w)
        ops = REG_RE.sub(lambda m: "$" + (EABI_NAMES.get(m.group(1), m.group(1)) if eabi else m.group(1)), ops)
        if i.branch_target is not None:
            ops = re.sub(r"(0x)?[0-9a-f]+(\s*<[^>]*>)?$", f".L{i.branch_target:08X}", ops)
        elif i.jump_target is not None:
            t = i.jump_target
            ops = f".L{t:08X}" if (i.is_j and f.addr <= t < f.end) else sym(t)
        elif a in hi_of:
            ops = re.sub(r"0x[0-9a-f]+$", f"%hi({sym(hi_of[a])})", ops)
        elif a in lo_of:
            ops = re.sub(r"(-?0x[0-9a-f]+|-?\d+)(\(\$\w+\))?$",
                         lambda m: f"%lo({sym(lo_of[a])})" + (m.group(2) or ""), ops)
        lines.append(f"    /* {a:08X} {w:08X} */ {mn:<10} {ops}".rstrip())
    for base, entries in sorted(jtbls.items()):
        lines += ["", ".section .rodata", f"glabel jtbl_{base:08X}"]
        lines += [f"    .word .L{t:08X}" for t in entries]
        lines += [".section .text"]
    return "\n".join(lines) + "\n"


def find_func(arg: str) -> Func:
    registry = load_registry()
    addr = registry.get(arg)
    if addr is None:
        addr = int(arg.removeprefix("func_"), 16)
    for f in load_layout():
        if f.addr == addr:
            return f
    sys.exit(f"error: no function starts at 0x{addr:08x} in layout.tsv")


def cmd_asm(args, cfg) -> int:
    names = {a: s for s, a in load_registry().items()}
    for fn in args.functions:
        print(function_asm(cfg, find_func(fn), names))
    return 0


def cmd_m2c(args, cfg) -> int:
    """Decompile with m2c (tools/toolchain/m2c, fetched by make toolchain).
    m2c output is a starting point, never a match."""
    m2c = TOOLCHAIN_DIR / "m2c" / "m2c.py"
    if not m2c.exists():
        sys.exit("error: m2c not installed; run make toolchain")
    names = {a: s for s, a in load_registry().items()}
    asm_dir = OUT / "m2c"
    asm_dir.mkdir(parents=True, exist_ok=True)
    rc = 0
    for fn in args.functions:
        f = find_func(fn)
        path = asm_dir / f"{f.addr:08x}.s"
        path.write_text(".set noat\n.set noreorder\n\n" + function_asm(cfg, f, names, eabi=True))
        res = subprocess.run([sys.executable, str(m2c), "-t", "mipsee-gcc-c", *args.m2c_args, str(path)],
                             capture_output=True, text=True)
        sys.stdout.write(res.stdout)
        if res.returncode:
            sys.stderr.write(res.stderr)
            rc = 1
    return rc


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
    p = sub.add_parser("split-rodata", help="move each function's constants into .rodata.<fn> (asm in place)")
    p.add_argument("files", nargs="+")
    p.add_argument("--no-fill", action="store_true", help="never let gas fill delay slots in .set reorder code")
    sub.add_parser("link-script", help="write out/gen/functions.ld from compiled objects")
    sub.add_parser("patch", help="patch linked functions into a copy of the original")
    sub.add_parser("verify", help="compare out/kh1.elf with the original")
    p = sub.add_parser("progress", help="print progress; --write updates docs/progress.md")
    p.add_argument("--write", action="store_true")
    sub.add_parser("objdiff", help="write objdiff.json and unit objects")
    sub.add_parser("objdiff-report", help="run objdiff-cli report and print per-function match")
    p = sub.add_parser("asm", help="print a function's original asm in m2c/decomp.me syntax")
    p.add_argument("functions", nargs="+", help="func_XXXXXXXX, an address, or a functions.tsv name")
    p = sub.add_parser("m2c", help="first-draft C for a function with m2c (not a match)")
    p.add_argument("functions", nargs="+")
    p.add_argument("--m2c-args", nargs=argparse.REMAINDER, default=[])
    p = sub.add_parser("rank", help="rank functions by size/complexity (writes out/rank.tsv)")
    p.add_argument("--segment", default="game", help="segment name from kh1.toml, or 'all' (default: game)")
    p.add_argument("--category", help="comma-separated: stub,getter,setter,thunk,wrapper,loop,leaf,other,hard")
    p.add_argument("--leaf", action="store_true", help="only functions that make no calls")
    p.add_argument("--max-insns", type=int)
    p.add_argument("--limit", type=int, default=40)
    p.add_argument("--all", action="store_true", help="include functions already in src/ or nonmatchings/")
    p.add_argument("--summary", action="store_true", help="count functions per category")
    args = ap.parse_args()
    cfg = load_config()
    if args.cmd == "config":
        print(cfg_get(cfg, args.key))
        return 0
    return {
        "check": cmd_check, "fix-obj": cmd_fix_obj, "split-rodata": cmd_split_rodata, "layout": cmd_layout, "gen": cmd_gen, "link-script": cmd_link_script,
        "patch": cmd_patch, "verify": cmd_verify, "progress": cmd_progress,
        "objdiff": cmd_objdiff, "objdiff-report": cmd_objdiff_report, "rank": cmd_rank, "asm": cmd_asm, "m2c": cmd_m2c,
    }[args.cmd](args, cfg)


if __name__ == "__main__":
    sys.exit(main())
