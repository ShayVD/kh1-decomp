# lchk_s10.py (session 10, w13): like mchk_s10.py but scores by LCS words, in process (~0.04 s per variant); set WDIR.
import os, sys, subprocess, tempfile
from pathlib import Path
ROOT = Path('/home/claude/kh1-decomp'); sys.path.insert(0, str(ROOT/'tools'))
import kh1tool as K, autodecomp as A
from elf32 import Elf
A._init(); cfg = A._cfg; orig = K.require_orig(cfg); reg = K.load_registry()
import atexit, shutil
_TD = Path(tempfile.mkdtemp(prefix='kh1chk_')); atexit.register(shutil.rmtree, _TD, True)  # one scratch dir per process, reused
extra = []
import difflib
def check(src, only=None):
    src = Path(src).resolve(); fl = K.flags_for(cfg, str(src.relative_to(ROOT)))
    cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
    td = _TD; asm, obj, out = td/'c.s', td/'c.o', td/'c.elf'
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
    L = Elf.load(out); res = {}
    for fn in funcs:
        a = A.resolve(fn, reg); f = A._layout[a]
        if only and only not in fn: continue
        ours = L.section_bytes(L.section(f".f_{fn}")); theirs = orig.read(f.addr, f.size)
        wo = [ours[i:i+4] for i in range(0, len(ours), 4)]; wt = [theirs[i:i+4] for i in range(0, len(theirs), 4)]
        sm = difflib.SequenceMatcher(None, wo, wt, autojunk=False)
        m = sum(b.size for b in sm.get_matching_blocks())
        pos = sum(1 for i in range(min(len(wo), len(wt))) if wo[i] != wt[i])
        res[fn] = (max(len(wo), len(wt)) - m, pos, len(ours), f.size)
    return res
