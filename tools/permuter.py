#!/usr/bin/env python3
"""Set up decomp-permuter (simonlindholm/decomp-permuter) runs for ee-gcc 2.96.

  tools/permuter.py import func_00123456 [--file draft.c]   # out/permuter/func_00123456/
  tools/permuter.py run func_00123456 [-j4] [--stop-on-zero ...]  # runs permuter.py on it

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
    fl = K.flags_for(cfg, "src/auto/x.c")
    tc = K.TOOLCHAIN_DIR / fl.compiler / "bin"
    # base.c: preprocessed, since the permuter parses it with pycparser
    raw = d / "raw.c"
    raw.write_text('#include "m2c.h"\n\n' + strip_draft(src.read_text()))
    r = subprocess.run([str(tc / "ee-gcc"), "-E", "-P", "-x", "c", f"-I{ROOT / 'include'}",
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
    (d / "compile.sh").write_text(
        "#!/bin/bash\n# invoked as: compile.sh input.c -o output.o\n"
        f'"{tc / "ee-gcc"}" -c -x c {fl.cflags} "$1" -o "$3" && '
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


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("import")
    p.add_argument("function")
    p.add_argument("--file")
    p = sub.add_parser("run")
    p.add_argument("function")
    p.add_argument("rest", nargs=argparse.REMAINDER)
    args = ap.parse_args()
    cfg = K.load_config()
    return {"import": cmd_import, "run": cmd_run}[args.cmd](args, cfg)


if __name__ == "__main__":
    sys.exit(main())
