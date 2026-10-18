# mchk.py [-e "extra flags"] SRC...: checkfile for many files with one init; also writes $WDIR/last.s (WDIR env, default /tmp)
import os, sys, subprocess, tempfile
from pathlib import Path
ROOT = Path('/home/claude/kh1-decomp'); sys.path.insert(0, str(ROOT/'tools'))
import kh1tool as K, autodecomp as A
from elf32 import Elf
A._init(); cfg = A._cfg; orig = K.require_orig(cfg); reg = K.load_registry()
args = sys.argv[1:]; extra = []
if args and args[0] == '-e': extra = args[1].split(); args = args[2:]
def check(src):
    src = Path(src).resolve(); fl = K.flags_for(cfg, str(src.relative_to(ROOT)))
    cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
    td = Path(tempfile.mkdtemp()); asm, obj, out = td/'c.s', td/'c.o', td/'c.elf'
    r = subprocess.run([str(cc), "-S", "-x", "c", *fl.cflags.split(), *fl.ccflags.split(), *extra, "-ffunction-sections", f"-I{ROOT/'include'}", f"-I{src.parent}", "-o", str(asm), str(src)], capture_output=True, text=True)
    if r.returncode: print(src.name, r.stderr[-1500:]); return
    text = K.split_rodata(asm.read_text()); text = K.no_fill(text) if fl.no_fill else text
    asm.write_text(text); Path(os.environ.get('WDIR', '/tmp')+'/last.s').write_text(text)
    r = subprocess.run([str(K.TOOLCHAIN_DIR / (fl.as_compiler or fl.compiler) / "bin" / "ee-gcc"), "-c", "-x", "assembler", *fl.cflags.split(), "-o", str(obj), str(asm)], capture_output=True, text=True)
    if r.returncode: print(r.stderr); return
    K.fix_object(obj); elf = Elf.load(obj)
    funcs = [s.name[6:] for s in elf.sections if s.name.startswith('.text.')]
    defs = []
    for u in [s.name for s in elf.symbols() if s.shndx == 0 and s.name]:
        a = A.resolve(u, reg)
        if a is None: print('unresolved', u); return
        defs += ["--defsym", f"{u}=0x{a:08x}"]
    secs = ''.join(f"  .f_{fn} 0x{A.resolve(fn, reg):08x} : {{ *(.text.{fn}) }}\n" for fn in funcs)
    (td/'c.ld').write_text("SECTIONS {\n" + secs + "  .ctx 0x0f000000 : { *(.ctx .ctx.*) }\n  .other 0x40000000 : { *(.text .data .bss .rodata*) }\n  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) } }\n")
    r = subprocess.run([f"{K.BINUTILS}ld", "-EL", "--no-warn-mismatch", "-e", "0", "-o", str(out), "-T", str(td/'c.ld'), *defs, str(obj)], capture_output=True, text=True)
    if r.returncode: print(r.stderr); return
    L = Elf.load(out)
    for fn in funcs:
        a = A.resolve(fn, reg); f = A._layout[a]
        ours = L.section_bytes(L.section(f".f_{fn}")); theirs = orig.read(f.addr, f.size)
        op = ours + bytes(max(0, f.size - len(ours)))
        if op == theirs and len(ours) <= f.size: print(src.name, f"{a:08x} MATCH"); continue
        d = [i for i in range(0, min(len(ours), f.size), 4) if ours[i:i+4] != theirs[i:i+4]]
        print(src.name, f"{a:08x} FAIL {len(ours)} vs {f.size}, {len(d)}w", ' '.join(f"{a+i:x}:{ours[i:i+4][::-1].hex()}/{theirs[i:i+4][::-1].hex()}" for i in d[:6]))
for s in args: check(s)
