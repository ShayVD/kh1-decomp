# batch module: score many variants of one function in one compile.
# score(prefix, fname, bodies, mode, extra=[]) -> list of words-differ (0 = match), size mismatch adds 4/word
import sys, os, subprocess, tempfile, re
sys.path.insert(0, '/home/claude/kh1-decomp/tools')
import kh1tool as K, autodecomp as A
from elf32 import Elf
from pathlib import Path
ROOT = Path('/home/claude/kh1-decomp')
A._init(); cfg = A._cfg; reg = K.load_registry(); orig = K.require_orig(cfg)
def score(prefix, fname, bodies, mode, extra=(), tag='b', ro=None):
    ro = ro or os.environ.get('RO')
    a = A.resolve(fname, reg); lay = A._layout[a]; theirs = orig.read(lay.addr, lay.size)
    src = prefix + '\n'
    for k, b in enumerate(bodies):
        src += re.sub(r'\b%s\b' % fname, f'{fname}__v{k}', b) + '\n'
    t = ROOT/'src'/mode/f'.batch_{tag}_{os.getpid()}.c'
    t.write_text(src)
    fl = K.flags_for(cfg, str(t.relative_to(ROOT)))
    cc = K.TOOLCHAIN_DIR/fl.compiler/'bin'/'ee-gcc'
    td = Path(tempfile.mkdtemp())
    asm, obj, out = td/'c.s', td/'c.o', td/'c.elf'
    r = subprocess.run([str(cc), '-S', '-x', 'c', *fl.cflags.split(), *fl.ccflags.split(), *extra, '-ffunction-sections', f'-I{ROOT/"include"}', f'-I{t.parent}', '-o', str(asm), str(t)], capture_output=True, text=True)
    t.unlink()
    if r.returncode: print(r.stderr[:2000]); return [10**6]*len(bodies)
    text = K.split_rodata(asm.read_text())
    asm.write_text(K.no_fill(text) if fl.no_fill else text)
    r = subprocess.run([str(K.TOOLCHAIN_DIR/(fl.as_compiler or fl.compiler)/'bin'/'ee-gcc'), '-c', '-x', 'assembler', *fl.cflags.split(), '-o', str(obj), str(asm)], capture_output=True, text=True)
    if r.returncode: print(r.stderr[:2000]); return [10**6]*len(bodies)
    K.fix_object(obj)
    elf = Elf.load(obj)
    funcs = [s.name[6:] for s in elf.sections if s.name.startswith('.text.')]
    undef = [s.name for s in elf.symbols() if s.shndx == 0 and s.name]
    defs = []
    for u in undef:
        x = A.resolve(u, reg)
        if x is None: print('unresolved', u); return [10**6]*len(bodies)
        defs += ['--defsym', f'{u}=0x{x:08x}']
    secs = ''
    for fn in funcs:
        m = re.match(r'(.*)__v\d+$', fn)
        x = A.resolve(m.group(1) if m else fn, reg)
        if x is None: x = 0x30000000
        secs += f'  .f_{fn} 0x{x:08x} : {{ *(.text.{fn}) }}\n'
        if ro and m: secs += f'  .r_{fn} 0x{ro} : {{ *(.rodata.{fn} .rodata.{fn}.*) }}\n'
    (td/'c.ld').write_text('SECTIONS {\n' + secs + '  .ctx 0x0f000000 : { *(.ctx .ctx.*) }\n  .other 0x40000000 : { *(.text .data .bss .rodata*) }\n  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) } }\n')
    r = subprocess.run([f'{K.BINUTILS}ld', '-EL', '--no-warn-mismatch', '--no-check-sections', '-e', '0', '-o', str(out), '-T', str(td/'c.ld'), *defs, str(obj)], capture_output=True, text=True)
    if r.returncode: print(r.stderr[:2000]); return [10**6]*len(bodies)
    L = Elf.load(out); res = []
    for k in range(len(bodies)):
        ours = L.section_bytes(L.section(f'.f_{fname}__v{k}'))
        d = sum(1 for i in range(0, min(len(ours), lay.size), 4) if ours[i:i+4] != theirs[i:i+4])
        res.append(d + abs(len(ours) - lay.size) // 4 * 4 if not (d == 0 and len(ours) == lay.size) else 0)
    subprocess.run(['rm', '-rf', str(td)])
    return res
