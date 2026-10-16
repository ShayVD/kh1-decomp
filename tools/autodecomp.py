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
import difflib
import os
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K  # noqa: E402
import permute  # noqa: E402
import sigs as SIGS  # noqa: E402
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
_protos: dict[str, str] = {}
_cc = ""
OPTS = {"budget": 60, "context": True, "max_score": 16}


def _init():
    global _cfg, _names, _layout, _protos, _cc
    if _cfg is None:
        _cfg = K.load_config()
        _names = {a: s for s, a in K.load_registry().items()}
        _layout = {f.addr: f for f in K.load_layout()}
        sig = SIGS.load()
        for a, sg in sig.items():
            n = _names.get(a, f"func_{a:08x}")
            _protos[n] = SIGS.prototype(n, sg)
        _cc = str(K.TOOLCHAIN_DIR / K.flags_for(_cfg, "src/auto/x.c").compiler / "bin" / "ee-gcc")


def disasm(blob: bytes, addr: int) -> list[str]:
    """objdump one blob as R5900 code; returns 'mnemonic operands' per word."""
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as fh:
        fh.write(blob)
        path = fh.name
    try:
        r = subprocess.run([f"{K.BINUTILS}objdump", "-D", "-b", "binary", "-m", "mips:5900", "-EL",
                            f"--adjust-vma=0x{addr:x}", path], capture_output=True, text=True)
    finally:
        os.unlink(path)
    out = []
    for line in r.stdout.splitlines():
        m = re.match(r"^\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(.*)$", line)
        if m:
            out.append(re.sub(r"\s+", " ", m.group(1)).strip())
    return out


def print_diff(f: K.Func, ours: bytes) -> None:
    theirs = _orig.read(f.addr, f.size)
    a, b = disasm(theirs, f.addr), disasm(ours, f.addr)
    for i in range(max(len(a), len(b))):
        x = a[i] if i < len(a) else ""
        y = b[i] if i < len(b) else ""
        mark = "  " if x == y else "!="
        print(f"{f.addr + 4 * i:08x} {mark} {x:<40} {y}")


_m2c_main = None


def run_m2c(argv: list[str]) -> tuple[int, str]:
    """Run m2c in this process (much faster than a subprocess per call: the
    prototype context is parsed once per worker)."""
    global _m2c_main
    import contextlib
    import io
    if _m2c_main is None:
        sys.path.insert(0, str(M2C.parent))
        import m2c.main as mm
        orig = mm.build_typemap
        cache = {}

        def build_typemap(contexts, arch, use_cache=True):
            key = tuple(str(c) for c in contexts)
            if key not in cache:
                cache[key] = orig(contexts, arch, use_cache=use_cache)
            return cache[key]
        mm.build_typemap = build_typemap
        # m2c treats the bottom of the frame as outgoing stack arguments (o32
        # style) when its address is taken with `move rX, $sp`, and turns
        # stores there into extra call arguments. EE gcc passes 8 int + 8
        # float arguments in registers; KH1 has no stack-passed arguments,
        # so the bottom of the frame is always locals.
        import m2c.translate as mt
        orig_stack = mt.get_stack_info

        def get_stack_info(*a, **k):
            info = orig_stack(*a, **k)
            info.subroutine_arg_top = 0
            return info
        mt.get_stack_info = get_stack_info
        _m2c_main = mm
    out, err = io.StringIO(), io.StringIO()
    try:
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            rc = _m2c_main.run(_m2c_main.parse_flags(argv))
    except (Exception, SystemExit):
        return 1, ""
    return rc, out.getvalue()


def m2c_candidates(f: K.Func) -> list[str]:
    asm = ".set noat\n.set noreorder\n\n" + K.function_asm(_cfg, f, _names, eabi=True)
    with tempfile.NamedTemporaryFile("w", suffix=".s", delete=False) as fh:
        fh.write(asm)
        path = fh.name
    out = []
    ctx = [["--context", str(SIGS.SIGS_H)]] if OPTS["context"] and SIGS.SIGS_H.exists() else []
    try:
        for c in [[], *ctx]:
            for v in VARIANTS:
                rc, text = run_m2c(["-t", "mipsee-gcc-c", *c, *v, path])
                if rc == 0 and text not in out:
                    out.append(text)
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


LAST_BYTES: bytes = b""


def build_and_compare(f: K.Func, sym: str, code: str, workdir: Path) -> tuple[bool, str]:
    """Compile `code`, link .text.<sym> at f.addr, compare with the original.
    The linked bytes are left in LAST_BYTES (for --diff)."""
    global LAST_BYTES
    LAST_BYTES = b""
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
    LAST_BYTES = ours
    theirs = _orig.read(f.addr, f.size)
    ours_p = ours + bytes(max(0, f.size - len(ours)))
    if len(ours) > f.size or ours_p != theirs:
        diff = sum(1 for i in range(0, min(len(ours), f.size), 4) if ours[i:i + 4] != theirs[i:i + 4])
        return False, f"mismatch ({len(ours)} vs {f.size} bytes, {diff} words differ, score {score(ours, theirs)})"
    return True, "match"


def score(ours: bytes, theirs: bytes) -> int:
    """0 for identical code; otherwise how many words are not matched in
    order (insertions and deletions count once each)."""
    a = [ours[i:i + 4] for i in range(0, len(ours), 4)]
    b = [theirs[i:i + 4] for i in range(0, len(theirs), 4)]
    m = sum(x.size for x in difflib.SequenceMatcher(None, a, b, autojunk=False).get_matching_blocks())
    return len(a) + len(b) - 2 * m


def why_score(why: str) -> float:
    m = re.search(r"score (\d+)", why)
    return int(m.group(1)) if m else float("inf")


_orig = None


def locals_size(f: K.Func) -> int:
    """Bytes of locals at the bottom of the frame: below the lowest
    callee-saved register slot (or the whole frame if nothing is saved)."""
    import struct as st
    words = st.unpack(f"<{f.size // 4}I", _orig.read(f.addr, f.size))
    if not words or words[0] >> 16 != 0x27BD or not (words[0] & 0x8000):
        return 0
    frame = 0x10000 - (words[0] & 0xFFFF)
    saves = []
    for w in words[1:16]:
        op, base, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        # sd/sq/sw of $16-$23, $30, $31; swc1 of $f20-$f30
        if base == 29 and ((op in (0x3F, 0x1F, 0x2B) and (16 <= rt <= 23 or rt in (30, 31)))
                           or (op == 0x39 and rt >= 20)):
            saves.append(w & 0xFFFF)
    return min(saves) if saves else frame


def try_function(addr: int) -> tuple[int, bool, str, str]:
    """m2c drafts, fixed up, then a greedy search over single-edit
    permutations of the closest one (tools/permute.py)."""
    global _orig
    _init()
    if _orig is None:
        _orig = K.require_orig(_cfg)
    f = _layout[addr]
    sym = _names.get(addr, f"func_{addr:08x}")
    raw = [c for c in m2c_candidates(f) if usable(c)]
    if not raw:
        return addr, False, "m2c output not usable", ""
    cands = []
    loc = locals_size(f)
    for c in raw:
        p = permute.preprocess(c, _protos, _cc, loc)
        cands += [p, *permute.variants(p)]
    cands = list(dict.fromkeys(cands))
    seen = set(cands)
    scored = []
    with tempfile.TemporaryDirectory() as td:
        for code in cands:
            ok, why = build_and_compare(f, sym, code, Path(td))
            if ok:
                return addr, True, why, code
            scored.append((why_score(why), why, code))
        scored.sort(key=lambda t: t[0])
        best = scored[0]
        if best[0] > OPTS["max_score"]:
            return addr, False, best[1], best[2]
        # Search from the closest draft, then (with what is left of the
        # budget) from the closest one that differs in which globals are
        # volatile: some fixes need that and a reordering together.
        def volatiles(c):
            return tuple(re.findall(r"^extern volatile .*$", c, re.M))
        starts = [best] + [next((t for t in scored[1:] if volatiles(t[2]) != volatiles(best[2])
                                 and t[0] <= OPTS["max_score"]), None)]
        evals = 0
        overall = best
        for k, start_ in enumerate(s_ for s_ in starts if s_ is not None):
            best = start_
            limit = OPTS["budget"] if k else OPTS["budget"] * 2 // 3
            sideways = 3  # moves to an equally close draft when stuck (e.g. two swaps needed)
            while best[0] != float("inf") and evals < limit:
                improved = False
                level = None
                for desc, code in permute.mutations(best[2]):
                    if code in seen:
                        continue
                    seen.add(code)
                    evals += 1
                    ok, why = build_and_compare(f, sym, code, Path(td))
                    if ok:
                        return addr, True, f"match (permuted, {evals} tries)", code
                    sc = why_score(why)
                    if sc < best[0]:
                        best = (sc, why, code)
                        improved = True
                        break
                    if sc == best[0] and level is None:
                        level = (sc, why, code)
                    if evals >= limit:
                        break
                if not improved:
                    if level is None or sideways == 0:
                        break
                    sideways -= 1
                    best = level
            if best[0] < overall[0]:
                overall = best
        best = overall
    return addr, False, best[1], best[2]


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
    p.add_argument("--diff", action="store_true", help="original vs ours, per instruction")
    p.add_argument("--file", help="try this C file instead of m2c output")
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
    p.add_argument("--only-failed", help="only retry functions this report lists as failing")
    for q in (p, sub.choices["try"]):
        q.add_argument("--budget", type=int, default=60, help="permutations tried per function (0 = none)")
        q.add_argument("--max-score", type=int, default=16, help="only search drafts at most this far off")
        q.add_argument("--no-context", action="store_true", help="do not give m2c the guessed prototypes")
    args = ap.parse_args()
    OPTS["budget"] = args.budget
    OPTS["max_score"] = args.max_score
    OPTS["context"] = not args.no_context
    if not SIGS.SIGS_TSV.exists():
        SIGS.write(K.load_config())
    _init()
    if args.cmd == "try":
        global _orig
        _orig = K.require_orig(_cfg)
        for fn in args.functions:
            f = K.find_func(fn)
            if args.file:
                sym = _names.get(f.addr, f"func_{f.addr:08x}")
                code = Path(args.file).read_text()
                with tempfile.TemporaryDirectory() as td:
                    ok, why = build_and_compare(f, sym, code, Path(td))
                addr = f.addr
            else:
                addr, ok, why, code = try_function(f.addr)
                if args.diff and not ok and code:
                    with tempfile.TemporaryDirectory() as td:
                        build_and_compare(f, _names.get(addr, f"func_{addr:08x}"), code, Path(td))
            print(f"{addr:08x}  {'MATCH' if ok else 'FAIL '}  {why}")
            if args.show:
                print(code)
            if args.diff and LAST_BYTES:
                print_diff(f, LAST_BYTES)
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
    if args.only_failed:
        prev = {int(l.split("\t")[0], 16) for l in Path(args.only_failed).read_text().splitlines()[1:]
                if l.split("\t")[1] == "fail"}
        sel = [a for a in sel if a in prev]
    sel = sel[: args.limit] if args.limit else sel
    print(f"trying {len(sel)} functions with {args.jobs} jobs", flush=True)
    matches, report = {}, []
    with ProcessPoolExecutor(args.jobs) as ex:
        for n, (addr, ok, why, code) in enumerate(ex.map(try_function, sel, chunksize=4), 1):
            report.append(f"{addr:08x}\t{'match' if ok else 'fail'}\t{why}")
            if n % 100 == 0:
                print(f"  {n}/{len(sel)} done, {len(matches) + ok} matched", flush=True)
            if ok:
                matches[addr] = code
                CACHE.mkdir(parents=True, exist_ok=True)
                (CACHE / f"{addr:08x}.c").write_text(code)
            elif code:  # closest draft, for hand work (out/autodecomp/fail/)
                (CACHE / "fail").mkdir(parents=True, exist_ok=True)
                (CACHE / "fail" / f"{addr:08x}.c").write_text(f"/* {why} */\n" + code)
    Path(args.report).write_text("addr\tresult\tdetail\n" + "\n".join(report) + "\n")
    print(f"matched {len(matches)}/{len(sel)} (report: {args.report})")
    if args.write and matches:
        for p in write_results(matches):
            print(f"wrote {p.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
