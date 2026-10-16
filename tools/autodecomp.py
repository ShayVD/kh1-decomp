#!/usr/bin/env python3
"""Batch-match small functions straight from m2c output.

For each candidate function: generate first-draft C with m2c (a few option
variants), compile it alone with the project compiler, link it at the
function's original address with every func_/D_ placeholder resolved to its
address, and compare the bytes with the original. Exact matches are kept;
everything else is listed for hand work. `make` (verify) is still the
authority: run it after writing the results into src/.

Usage:
  tools/autodecomp.py try func_00123456 ...       # print result per function
  tools/autodecomp.py batch --category setter,getter --max-insns 12 --write
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K  # noqa: E402
from elf32 import Elf  # noqa: E402

ROOT = K.ROOT
M2C = K.TOOLCHAIN_DIR / "m2c" / "m2c.py"
AUTO_DIR = ROOT / "src" / "auto"
CACHE = K.OUT / "autodecomp"
VARIANTS = [
    ["--valid-syntax"],
    ["--valid-syntax", "--void"],
    ["--valid-syntax", "--no-casts"],
    ["--valid-syntax", "--void", "--no-casts"],
]
ALLOWED_MACROS = {"M2C_FIELD", "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32", "M2C_UNK64", "M2C_BITWISE"}
SYM_RE = re.compile(r"^(func_([0-9a-fA-F]{8})|D_([0-9a-fA-F]{8}))$")

_cfg = None
_names = None
_layout = None


def _init():
    global _cfg, _names, _layout
    if _cfg is None:
        _cfg = K.load_config()
        _names = {a: s for s, a in K.load_registry().items()}
        _layout = {f.addr: f for f in K.load_layout()}


def m2c_candidates(f: K.Func) -> list[str]:
    asm = ".set noat\n.set noreorder\n\n" + K.function_asm(_cfg, f, _names)
    with tempfile.NamedTemporaryFile("w", suffix=".s", delete=False) as fh:
        fh.write(asm)
        path = fh.name
    out = []
    try:
        for v in VARIANTS:
            r = subprocess.run([sys.executable, str(M2C), "-t", "mipsee-gcc-c", *v, path],
                               capture_output=True, text=True)
            if r.returncode == 0 and r.stdout not in out:
                out.append(r.stdout)
    finally:
        os.unlink(path)
    return out


def usable(code: str) -> bool:
    if "M2C_ERROR" in code or "Decompilation failure" in code or "?" in code.replace("? :", ""):
        return False
    return set(re.findall(r"\bM2C_\w+", code)) <= ALLOWED_MACROS


def resolve(sym: str, registry: dict[str, int]) -> int | None:
    if sym in registry:
        return registry[sym]
    m = SYM_RE.match(sym)
    if m:
        return int(m.group(2) or m.group(3), 16)
    return None


def build_and_compare(f: K.Func, sym: str, code: str, workdir: Path) -> tuple[bool, str]:
    """Compile `code`, link .text.<sym> at f.addr, compare with the original."""
    fl = K.flags_for(_cfg, "src/auto/x.c")
    cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
    src, asm, obj, out = (workdir / n for n in ("c.c", "c.s", "c.o", "c.elf"))
    src.write_text('#include "m2c.h"\n\n' + code)
    r = subprocess.run([str(cc), "-S", "-x", "c", *fl.cflags.split(), "-ffunction-sections",
                        f"-I{ROOT / 'include'}", "-o", str(asm), str(src)], capture_output=True, text=True)
    if r.returncode:
        return False, "compile error: " + (r.stderr.strip().splitlines() or [""])[-1]
    asm.write_text(K.split_rodata(asm.read_text()))
    r = subprocess.run([str(cc), "-c", "-x", "assembler", *fl.cflags.split(), "-o", str(obj), str(asm)],
                       capture_output=True, text=True)
    if r.returncode:
        return False, "assemble error"
    K.fix_object(obj)
    elf = Elf.load(obj)
    if any(s.name.startswith(".rodata") and s.size for s in elf.sections):
        return False, "uses rodata (needs hand placement)"
    registry = K.load_registry()
    undef = [s.name for s in elf.symbols() if s.shndx == 0 and s.name]
    defsyms = []
    for u in undef:
        a = resolve(u, registry)
        if a is None:
            return False, f"unresolvable symbol {u}"
        defsyms += ["--defsym", f"{u}=0x{a:08x}"]
    ld_script = workdir / "c.ld"
    ld_script.write_text(f"SECTIONS {{ .f 0x{f.addr:08x} : {{ *(.text.{sym}) }}\n"
                         "  .other 0x40000000 : { *(.text .text.* .data .bss .rodata*) }\n"
                         "  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) } }\n")
    r = subprocess.run([f"{K.BINUTILS}ld", "-EL", "--no-warn-mismatch", "-e", "0", "-o", str(out),
                        "-T", str(ld_script), *defsyms, str(obj)],
                       capture_output=True, text=True)
    if r.returncode:
        return False, "link error: " + r.stderr.strip().splitlines()[-1]
    linked = Elf.load(out)
    sec = linked.section(".f")
    if sec is None:
        return False, "no code"
    ours = linked.section_bytes(sec)
    theirs = _orig.read(f.addr, f.size)
    ours_p = ours + bytes(max(0, f.size - len(ours)))
    if len(ours) > f.size or ours_p != theirs:
        diff = sum(1 for i in range(0, min(len(ours), f.size), 4) if ours[i:i + 4] != theirs[i:i + 4])
        return False, f"mismatch ({len(ours)} vs {f.size} bytes, {diff} words differ)"
    return True, "match"


_orig = None


def try_function(addr: int) -> tuple[int, bool, str, str]:
    global _orig
    _init()
    if _orig is None:
        _orig = K.require_orig(_cfg)
    f = _layout[addr]
    sym = _names.get(addr, f"func_{addr:08x}")
    cands = [c for c in m2c_candidates(f) if usable(c)]
    if not cands:
        return addr, False, "m2c output not usable", ""
    last = ""
    with tempfile.TemporaryDirectory() as td:
        for code in cands:
            ok, why = build_and_compare(f, sym, code, Path(td))
            if ok:
                return addr, True, why, code
            last = why
    return addr, False, last, cands[0]


# --------------------------------------------------------------------------- output

DECL_RE = re.compile(r"^(?P<decl>[^\n;{}]+?\b(?P<name>\w+)\s*(\([^;{}]*\))?(\[[^\]]*\])?)\s*;\s*(/\*.*\*/)?\s*$")


def split_unit(code: str) -> tuple[list[tuple[str, str]], str]:
    """m2c output -> ([(name, extern declaration line)], function body)."""
    decls, body = [], []
    lines = code.strip("\n").splitlines()
    i = 0
    while i < len(lines) and not re.match(r"^\S.*\)\s*\{\s*$", lines[i]):
        line = lines[i].strip()
        m = DECL_RE.match(line)
        if m:
            d = re.sub(r"\s*/\*.*\*/\s*$", "", line)
            decls.append((m.group("name"), d))
        i += 1
    body = lines[i:]
    return decls, "\n".join(body).rstrip() + "\n"


def write_results(matches: dict[int, str]) -> list[Path]:
    """Group matched functions into src/auto/text_XXXX0000.c (one file per
    64 KiB of address space; the original translation units are unknown).
    Functions whose extern declarations conflict with a file's go into a
    numbered sibling file."""
    files: dict[str, dict] = {}
    for addr in sorted(matches):
        decls, body = split_unit(matches[addr])
        base = f"text_{addr >> 16:04x}0000"
        n = 0
        while True:
            key = base if n == 0 else f"{base}_{n}"
            if (AUTO_DIR / f"{key}.c").exists():  # earlier runs' files stay untouched
                n += 1
                continue
            unit = files.setdefault(key, {"decls": {}, "funcs": [], "defined": set()})
            fname = _names.get(addr, f"func_{addr:08x}")
            conflict = any(name in unit["decls"] and unit["decls"][name] != d for name, d in decls)
            conflict |= fname in unit["decls"]
            conflict |= any(name in unit["defined"] for name, _ in decls)
            if not conflict:
                break
            n += 1
        for name, d in decls:
            unit["decls"][name] = d
        unit["funcs"].append(body)
        unit["defined"].add(fname)
    AUTO_DIR.mkdir(parents=True, exist_ok=True)
    written = []
    for key, unit in sorted(files.items()):
        path = AUTO_DIR / f"{key}.c"
        text = ["/* Matched automatically from m2c output (tools/autodecomp.py); not yet",
                " * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */",
                '#include "m2c.h"', ""]
        text += sorted(unit["decls"].values())
        text.append("")
        text.append("\n".join(unit["funcs"]))
        path.write_text("\n".join(text))
        written.append(path)
    return written


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("try")
    p.add_argument("functions", nargs="+")
    p.add_argument("--show", action="store_true")
    p = sub.add_parser("batch")
    p.add_argument("--segment", default="game")
    p.add_argument("--category")
    p.add_argument("--max-insns", type=int, default=16)
    p.add_argument("--min-insns", type=int, default=0)
    p.add_argument("--limit", type=int)
    p.add_argument("--jobs", type=int, default=os.cpu_count())
    p.add_argument("--write", action="store_true", help="write matches into src/auto/")
    p.add_argument("--report", default=str(K.OUT / "autodecomp.tsv"))
    p.add_argument("--from-report", help="only retry the functions this report marks as matching")
    args = ap.parse_args()
    _init()
    if args.cmd == "try":
        for fn in args.functions:
            addr, ok, why, code = try_function(K.find_func(fn).addr)
            print(f"{addr:08x}  {'MATCH' if ok else 'FAIL '}  {why}")
            if args.show:
                print(code)
        return 0

    done = K.decompiled_addrs()
    rows = [l.split("\t") for l in K.RANK_TSV.read_text().splitlines()[1:]]
    hdr = ["segment", *K.RANK_COLUMNS]
    sel = []
    for r in rows:
        d = dict(zip(hdr, r))
        if args.segment != "all" and d["segment"] != args.segment:
            continue
        if args.category and d["category"] not in args.category.split(","):
            continue
        if not args.min_insns <= int(d["insns"]) <= args.max_insns or d["category"] == "hard":
            continue
        a = int(d["addr"], 16)
        if a in done:
            continue
        sel.append(a)
    if args.from_report:
        prev = {int(l.split("\t")[0], 16) for l in Path(args.from_report).read_text().splitlines()[1:]
                if l.split("\t")[1] == "match"}
        sel = [a for a in sel if a in prev]
    sel = sel[: args.limit] if args.limit else sel
    print(f"trying {len(sel)} functions with {args.jobs} jobs", flush=True)
    matches, report = {}, []
    with ProcessPoolExecutor(args.jobs) as ex:
        for addr, ok, why, code in ex.map(try_function, sel, chunksize=4):
            report.append(f"{addr:08x}\t{'match' if ok else 'fail'}\t{why}")
            if ok:
                matches[addr] = code
                CACHE.mkdir(parents=True, exist_ok=True)
                (CACHE / f"{addr:08x}.c").write_text(code)
    Path(args.report).write_text("addr\tresult\tdetail\n" + "\n".join(report) + "\n")
    print(f"matched {len(matches)}/{len(sel)} (report: {args.report})")
    if args.write and matches:
        for p in write_results(matches):
            print(f"wrote {p.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
