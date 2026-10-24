#!/usr/bin/env python3
"""Check a whole source file: compile it once with its directory's flags
(kh1.toml), link every func_/named function at its own original address
(so calls between them resolve, and a callee defined earlier in the file
has its effect), and compare each against the original ELF.

  tools/checkfile.py src/hand/FILE.c
  KH1_EXTRA_CCFLAGS="-fno-sched-interblock" tools/checkfile.py ...   (extra C -> asm flags)

Prints MATCH or FAIL per function. A function that uses rodata (jump
tables, strings, float constants) differs only in the words that address
it, since rodata is not placed here; `make` places it."""
import os, sys, re, subprocess, tempfile
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import kh1tool as K
import autodecomp as A
from elf32 import Elf
ROOT = Path(__file__).resolve().parent.parent
VERBOSE = '-v' in sys.argv[2:]  # list each differing word
src = Path(sys.argv[1]).resolve()
A._init()
cfg = A._cfg
rel = str(src.relative_to(ROOT))
fl = K.flags_for(cfg, rel)
cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
orig = K.require_orig(cfg)
reg = K.load_registry()
td = Path(tempfile.mkdtemp())
asm, obj, out = td/'c.s', td/'c.o', td/'c.elf'
r = subprocess.run([str(cc), "-S", "-x", "c", *fl.cflags.split(), *fl.ccflags.split(), *os.environ.get("KH1_EXTRA_CCFLAGS", "").split(), "-ffunction-sections", f"-I{ROOT/'include'}", f"-I{src.parent}", "-o", str(asm), str(src)], capture_output=True, text=True)
if r.returncode: print(r.stderr); sys.exit(1)
text = K.split_rodata(asm.read_text())
asm.write_text(K.no_fill(text) if fl.no_fill else text)
r = subprocess.run([str(K.TOOLCHAIN_DIR / (fl.as_compiler or fl.compiler) / "bin" / "ee-gcc"), "-c", "-x", "assembler", *fl.cflags.split(), "-o", str(obj), str(asm)], capture_output=True, text=True)
if r.returncode: print(r.stderr); sys.exit(1)
K.fix_object(obj)
elf = Elf.load(obj)
funcs = [s.name[6:] for s in elf.sections if s.name.startswith('.text.')]
undef = [s.name for s in elf.symbols() if s.shndx == 0 and s.name]
defs = []
for u in undef:
    a = A.resolve(u, reg)
    if a is None: print('unresolved', u); sys.exit(1)
    defs += ["--defsym", f"{u}=0x{a:08x}"]
secs = ''
for fn in funcs:
    a = A.resolve(fn, reg)
    if a is None: continue  # a local helper with no original address: lands in .other
    secs += f"  .f_{fn} 0x{a:08x} : {{ *(.text.{fn}) }}\n"
(td/'c.ld').write_text("SECTIONS {\n" + secs + "  .ctx 0x0f000000 : { *(.ctx .ctx.*) }\n  .other 0x40000000 : { *(.text .data .bss .rodata*) }\n  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) } }\n")
r = subprocess.run([f"{K.BINUTILS}ld", "-EL", "--no-warn-mismatch", "-e", "0", "-o", str(out), "-T", str(td/'c.ld'), *defs, str(obj)], capture_output=True, text=True)
if r.returncode: print(r.stderr); sys.exit(1)
L = Elf.load(out)
for fn in funcs:
    a = A.resolve(fn, reg)
    if a is None: continue
    f = A._layout[a]
    ours = L.section_bytes(L.section(f".f_{fn}"))
    theirs = orig.read(f.addr, f.size)
    op = ours + bytes(max(0, f.size - len(ours)))
    if op == theirs and len(ours) <= f.size: print(f"{a:08x} MATCH")
    else:
        d = sum(1 for i in range(0, min(len(ours), f.size), 4) if ours[i:i+4] != theirs[i:i+4])
        print(f"{a:08x} FAIL {len(ours)} vs {f.size}, {d} words differ")
        if VERBOSE:
            for i in range(0, min(len(ours), f.size), 4):
                if ours[i:i+4] != theirs[i:i+4]:
                    print(f"  {a+i:08x} ours {ours[i:i+4][::-1].hex()} orig {theirs[i:i+4][::-1].hex()}")
