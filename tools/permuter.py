#!/usr/bin/env python3
"""Set up decomp-permuter (simonlindholm/decomp-permuter) runs (ee-gcc 2.96
by default; `--out-dir src/sdk/libkernl` uses that directory's kh1.toml
compiler, flags and no_fill).

  tools/permuter.py import func_00123456 [--file draft.c]   # out/permuter/func_00123456/
  tools/permuter.py run func_00123456 [-j4] [--stop-on-zero ...]  # runs permuter.py on it
  tools/permuter.py batch queue.txt --seconds 120 [--write] [--out-dir DIR]  # each in turn; keeps verified matches

The starting C is `--file`, else autodecomp's closest failing draft
(out/autodecomp/fail/XXXXXXXX.c). The directory gets what the permuter wants:
base.c (preprocessed, only this function's body kept), target.o (the
original function, assembled from `kh1tool.py asm` so calls and %hi/%lo
pairs are relocations against the same func_/D_ names our code uses),
compile.sh (ee-gcc -O2 -G0 + fix-obj) and settings.toml (gcc weights,
R5900 objdump). The permuter lives in tools/toolchain/decomp-permuter
(`make toolchain` does not fetch it; this script clones it on first use).

The permuter's score is not ours: it ignores stack offsets by default and
weights regalloc differences lightly. A score-0 candidate must still pass
`autodecomp.py try func_X --file <candidate>` and `make`.
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K  # noqa: E402

ROOT = K.ROOT
PERMUTER = K.TOOLCHAIN_DIR / "decomp-permuter"
PERMUTER_URL = "https://github.com/simonlindholm/decomp-permuter.git"
PERMUTER_REV = "main"
OUTDIR = K.OUT / "permuter"

PRELUDE = """.set noat
.set noreorder
.macro glabel label
    .global \\label
    .type \\label, @function
    \\label:
.endm
.section .text
"""


def ensure_permuter() -> Path:
    if not (PERMUTER / "permuter.py").exists():
        subprocess.run(["git", "clone", "-q", "--depth", "1", PERMUTER_URL, str(PERMUTER)], check=True)
    return PERMUTER


def strip_draft(code: str) -> str:
    """Drop autodecomp's result comment on the first line."""
    return re.sub(r"\A/\*[^\n]*\*/\n", "", code)


def cmd_import(args, cfg) -> int:
    f = K.find_func(args.function)
    names = {a: s for s, a in K.load_registry().items()}
    sym = names.get(f.addr, f"func_{f.addr:08x}")
    src = Path(args.file) if args.file else K.OUT / "autodecomp" / "fail" / f"{f.addr:08x}.c"
    if not src.exists():
        print(f"no draft at {src}; pass --file", file=sys.stderr)
        return 1
    d = OUTDIR / sym
    d.mkdir(parents=True, exist_ok=True)
    out_dir = getattr(args, "out_dir", None) or "src/auto"
    fl = K.flags_for(cfg, f"{out_dir}/x.c")
    tc = K.TOOLCHAIN_DIR / fl.compiler / "bin"
    # base.c: preprocessed, since the permuter parses it with pycparser
    raw = d / "raw.c"
    raw.write_text('#include "m2c.h"\n\n' + strip_draft(src.read_text()))
    r = subprocess.run([str(tc / "ee-gcc"), "-E", "-P", "-x", "c", f"-I{ROOT / 'include'}", f"-I{ROOT / out_dir}",
                        "-D__attribute__(x)=", str(raw)], capture_output=True, text=True)
    if r.returncode:
        print(r.stderr, file=sys.stderr)
        return 1
    (d / "base.c").write_text(r.stdout)
    raw.unlink()
    # target.o
    body = K.function_asm(cfg, f, names).rstrip("\n").split("\n")
    while body and re.search(r"\*/ nop$", body[-1]):  # alignment padding
        body.pop()
    (d / "target.s").write_text(PRELUDE + "\n".join(body) + "\n")
    # ee-as 2.10 does not take $-named registers; modern binutils does
    r = subprocess.run([f"{K.BINUTILS}as", "-EL", "-march=r5900", "-mabi=eabi", "-o", str(d / "target.o"),
                        str(d / "target.s")], capture_output=True, text=True)
    if r.returncode:
        print(r.stderr, file=sys.stderr)
        return 1
    if fl.no_fill:  # as the build does it: compile to assembly, unfill, assemble
        nf = (f'"{sys.executable}" -c "import sys; sys.path.insert(0, \'{ROOT / "tools"}\'); import kh1tool as K; '
              f'p = sys.argv[1]; t = open(p).read(); open(p, \'w\').write(K.no_fill(K.split_rodata(t)))" "$3.s"')
        build = (f'"{tc / "ee-gcc"}" -S -x c {fl.cflags} "$1" -o "$3.s" && {nf} && '
                 f'"{tc / "ee-gcc"}" -c -x assembler {fl.cflags} "$3.s" -o "$3" && rm -f "$3.s" && ')
    else:
        build = f'"{tc / "ee-gcc"}" -c -x c {fl.cflags} "$1" -o "$3" && '
    (d / "compile.sh").write_text(
        "#!/bin/bash\n# invoked as: compile.sh input.c -o output.o\n" + build +
        f'"{sys.executable}" "{ROOT / "tools" / "kh1tool.py"}" fix-obj "$3" >/dev/null\n')
    os.chmod(d / "compile.sh", 0o755)
    (d / "settings.toml").write_text(
        f'func_name = "{sym}"\ncompiler_type = "gcc"\n'
        f'objdump_command = "{K.BINUTILS}objdump -drz -m mips:5900 -EL -M reg-names=numeric"\n')
    print(d.relative_to(ROOT))
    return 0


def cmd_run(args, cfg) -> int:
    ensure_permuter()
    f = K.find_func(args.function)
    names = {a: s for s, a in K.load_registry().items()}
    d = OUTDIR / names.get(f.addr, f"func_{f.addr:08x}")
    if not (d / "base.c").exists():
        print(f"run `tools/permuter.py import {args.function}` first", file=sys.stderr)
        return 1
    return subprocess.run([sys.executable, str(PERMUTER / "permuter.py"), str(d), *args.rest]).returncode


def accept(sym: str, addr: int, out_dir: Path) -> str | None:
    """A permuter output as autodecomp code (the declarations it saw + its
    function), if it is byte-identical."""
    import tempfile
    import autodecomp as A
    A._init()
    if A._orig is None:
        A._orig = K.require_orig(A._cfg)
    src = (out_dir / "source.c").read_text()
    m = re.search(rf"^\S[^\n;]*\b{sym}\([^)]*\)\s*\{{", src, re.M)
    if not m:
        return None
    pre = src[: m.start()]  # declarations after the headers' typedefs
    tail = pre[pre.rfind("typedef"):].split("\n", 1)[1] if "typedef" in pre else pre
    func = re.sub(r"\)\s*\n\{", ") {", src[m.start():], count=1)
    code = "\n".join(l for l in tail.splitlines() if l.strip()) + "\n\n" + func.strip() + "\n"
    with tempfile.TemporaryDirectory() as td:
        ok, _why = A.build_and_compare(A._layout[addr], sym, code, Path(td))
    return code if ok else None


def cmd_batch(args, cfg) -> int:
    """Import + run each function for --seconds, keep byte-identical score-0
    outputs (written to src/auto/ as each is found, with --write)."""
    import signal
    import autodecomp as A
    ensure_permuter()
    names = {a: s for s, a in K.load_registry().items()}
    matches = {}
    for fn in Path(args.queue).read_text().split():
        f = K.find_func(fn if fn.startswith("func_") else "func_" + fn)
        sym = names.get(f.addr, f"func_{f.addr:08x}")
        ns = argparse.Namespace(function=sym, file=None, out_dir=args.out_dir)
        if cmd_import(ns, cfg):
            print(f"{sym} import failed", flush=True)
            continue
        d = OUTDIR / sym
        p = subprocess.Popen([sys.executable, str(PERMUTER / "permuter.py"), str(d), f"-j{args.jobs}",
                              "--stop-on-zero"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                             start_new_session=True)
        try:
            p.wait(args.seconds)
        except subprocess.TimeoutExpired:
            os.killpg(p.pid, signal.SIGTERM)
            p.wait()
        outs = sorted(d.glob("output-*"), key=lambda o: int(o.name.split("-")[1]))
        best = outs[0].name.split("-")[1] if outs else "-"
        code = next((c for o in outs if o.name.startswith("output-0-") for c in [accept(sym, f.addr, o)] if c), None)
        print(f"{sym} best {best} {'MATCH' if code else ''}", flush=True)
        if code:
            matches[f.addr] = code
            if args.write:  # as found, so a long batch that is stopped keeps its matches
                for path in A.write_results({f.addr: code}):
                    print(f"wrote {path.relative_to(ROOT)}", flush=True)
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("import")
    p.add_argument("function")
    p.add_argument("--file")
    p.add_argument("--out-dir", help="compile with this source directory's kh1.toml flags (default src/auto)")
    p = sub.add_parser("run")
    p.add_argument("function")
    p.add_argument("rest", nargs=argparse.REMAINDER)
    p = sub.add_parser("batch")
    p.add_argument("queue", help="file with one function (func_X or address) per line")
    p.add_argument("--seconds", type=int, default=120)
    p.add_argument("--jobs", type=int, default=4)
    p.add_argument("--write", action="store_true")
    p.add_argument("--out-dir", help="flags and destination directory for matches (default src/auto)")
    args = ap.parse_args()
    if getattr(args, "out_dir", None):
        import autodecomp as A
        A.AUTO_DIR = (ROOT / args.out_dir).resolve()
    cfg = K.load_config()
    return {"import": cmd_import, "run": cmd_run, "batch": cmd_batch}[args.cmd](args, cfg)


if __name__ == "__main__":
    sys.exit(main())
