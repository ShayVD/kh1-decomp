# lcs.py SRC [FUNCADDR]: like checkfile but LCS word diff; masks jump-table/rodata hi/lo? (no). Prints per func: size, lcs-off
import os, sys, re, subprocess, tempfile, difflib
from pathlib import Path
R = Path('/home/claude/kh1-decomp'); sys.path.insert(0, str(R/'tools'))
import kh1tool as K, autodecomp as A
from elf32 import Elf
src = Path(sys.argv[1]).resolve(); only = sys.argv[2] if len(sys.argv) > 2 else None
A._init(); cfg = A._cfg
fl = K.flags_for(cfg, str(src.relative_to(R)))
cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
orig = K.require_orig(cfg); reg = K.load_registry()
td = Path(tempfile.mkdtemp()); asm, obj, out = td/'c.s', td/'c.o', td/'c.elf'
r = subprocess.run([str(cc), "-S", "-x", "c", *fl.cflags.split(), *fl.ccflags.split(), *os.environ.get("KH1_EXTRA_CCFLAGS", "").split(), "-ffunction-sections", f"-I{R/'include'}", f"-I{src.parent}", "-o", str(asm), str(src)], capture_output=True, text=True)
if r.returncode: print(r.stderr); sys.exit(1)
text = K.split_rodata(asm.read_text())
if os.environ.get('PP'):
    import importlib.util as iu; sp=iu.spec_from_file_location('pp',os.environ['PP']); m=iu.module_from_spec(sp); sp.loader.exec_module(m); text=m.pp(text)
asm.write_text(K.no_fill(text) if fl.no_fill else text)
r = subprocess.run([str(K.TOOLCHAIN_DIR / (fl.as_compiler or fl.compiler) / "bin" / "ee-gcc"), "-c", "-x", "assembler", *fl.cflags.split(), "-o", str(obj), str(asm)], capture_output=True, text=True)
if r.returncode: print(r.stderr); sys.exit(1)
K.fix_object(obj); elf = Elf.load(obj)
funcs = [s.name[6:] for s in elf.sections if s.name.startswith('.text.')]
defs = []
for u in [s.name for s in elf.symbols() if s.shndx == 0 and s.name]:
    a = A.resolve(u, reg)
    if a is None: print('unresolved', u); sys.exit(1)
    defs += ["--defsym", f"{u}=0x{a:08x}"]
secs = ''.join(f"  .f_{fn} 0x{A.resolve(fn, reg):08x} : {{ *(.text.{fn}) }}\n" for fn in funcs)
(td/'c.ld').write_text("SECTIONS {\n" + secs + "  .ctx 0x0f000000 : { *(.ctx .ctx.*) }\n  .other 0x40000000 : { *(.text .data .bss .rodata*) }\n  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) } }\n")
r = subprocess.run([f"{K.BINUTILS}ld", "-EL", "--no-warn-mismatch", "-e", "0", "-o", str(out), "-T", str(td/'c.ld'), *defs, str(obj)], capture_output=True, text=True)
if r.returncode: print(r.stderr); sys.exit(1)
L = Elf.load(out)
if os.environ.get('W9_DUMP'):
    open(os.path.join(os.environ.get('WDIR', '/tmp/claude-0/s8/w9'), 'ours.txt'),'w').write(subprocess.run([f"{K.BINUTILS}objdump", '-d', '-M', 'no-aliases' if False else 'gpr-names=32', str(out)], capture_output=True, text=True).stdout)
for fn in funcs:
    a = A.resolve(fn, reg)
    if only and only not in fn: continue
    f = A._layout[a]
    ours = L.section_bytes(L.section(f".f_{fn}")); theirs = orig.read(f.addr, f.size)
    wo = [ours[i:i+4] for i in range(0, len(ours), 4)]; wt = [theirs[i:i+4] for i in range(0, len(theirs), 4)]
    sm = difflib.SequenceMatcher(None, wo, wt, autojunk=False)
    m = sum(b.size for b in sm.get_matching_blocks())
    pos = sum(1 for i in range(min(len(wo), len(wt))) if wo[i] != wt[i])
    print(f"{a:08x} {len(ours)} vs {f.size} lcsoff {max(len(wo), len(wt)) - m} posoff {pos}")
    if '-v' in os.environ.get('LV', ''):
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag != 'equal': print(f"  {tag} ours@{a+4*i1:08x}+{i2-i1} orig@{a+4*j1:08x}+{j2-j1}")
