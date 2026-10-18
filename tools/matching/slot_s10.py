# slot.py SRC FUNCADDR [SYM...]: compile once; assemble baseline, +all D_ defs, +each def; LCS per variant
import os, sys, re, subprocess, tempfile, difflib
from pathlib import Path
R = Path('/home/claude/kh1-decomp'); sys.path.insert(0, str(R/'tools'))
import kh1tool as K, autodecomp as A
from elf32 import Elf
src = Path(sys.argv[1]).resolve(); only = sys.argv[2]; force = sys.argv[3:]
A._init(); cfg = A._cfg
fl = K.flags_for(cfg, str(src.relative_to(R)))
cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
orig = K.require_orig(cfg); reg = K.load_registry()
td = Path(tempfile.mkdtemp(dir=os.environ.get('WDIR','/tmp'))); asm = td/'c.s'
r = subprocess.run([str(cc), "-S", "-x", "c", *fl.cflags.split(), *fl.ccflags.split(), *os.environ.get("CCX","").split(), "-ffunction-sections", f"-I{R/'include'}", f"-I{src.parent}", "-o", str(asm), str(src)], capture_output=True, text=True)
if r.returncode: print(r.stderr[-2000:]); sys.exit(1)
text = K.split_rodata(asm.read_text()); text = K.no_fill(text) if fl.no_fill else text
def run(text, tag):
    s = td/(tag+'.s'); obj = td/(tag+'.o'); out = td/(tag+'.elf'); s.write_text(text)
    r = subprocess.run([str(K.TOOLCHAIN_DIR / (fl.as_compiler or fl.compiler) / "bin" / "ee-gcc"), "-c", "-x", "assembler", *fl.cflags.split(), *os.environ.get("ASX","").split(), "-o", str(obj), str(s)], capture_output=True, text=True)
    if r.returncode: return None, r.stderr[-500:]
    K.fix_object(obj); elf = Elf.load(obj)
    funcs = [x.name[6:] for x in elf.sections if x.name.startswith('.text.')]
    defs = []
    for u in [x.name for x in elf.symbols() if x.shndx == 0 and x.name]:
        a = A.resolve(u, reg)
        if a is None: return None, 'unresolved '+u
        defs += ["--defsym", f"{u}=0x{a:08x}"]
    secs = ''.join(f"  .f_{fn} 0x{A.resolve(fn, reg):08x} : {{ *(.text.{fn}) }}\n" for fn in funcs)
    (td/'c.ld').write_text("SECTIONS {\n" + secs + "  .ctx 0x0f000000 : { *(.ctx .ctx.*) }\n  .other 0x40000000 : { *(.text .data .bss .rodata*) }\n  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) } }\n")
    r = subprocess.run([f"{K.BINUTILS}ld", "-EL", "--no-warn-mismatch", "-e", "0", "-o", str(out), "-T", str(td/'c.ld'), *defs, str(obj)], capture_output=True, text=True)
    if r.returncode: return None, r.stderr[-500:]
    L = Elf.load(out)
    for fn in funcs:
        a = A.resolve(fn, reg)
        if only not in fn: continue
        f = A._layout[a]
        ours = L.section_bytes(L.section(f".f_{fn}")); theirs = orig.read(f.addr, f.size)
        wo = [ours[i:i+4] for i in range(0, len(ours), 4)]; wt = [theirs[i:i+4] for i in range(0, len(theirs), 4)]
        sm = difflib.SequenceMatcher(None, wo, wt, autojunk=False)
        m = sum(b.size for b in sm.get_matching_blocks())
        pos = sum(1 for i in range(min(len(wo), len(wt))) if wo[i] != wt[i])
        return (max(len(wo), len(wt)) - m, pos, len(ours), f.size), None
    return None, 'nofunc'
# symbols defined in the asm
defined = set(re.findall(r'^([A-Za-z_.$][\w.$]*):', text, re.M))
# function body text
m = re.search(r'\.section\s+\.text\.\w*' + only + r'.*?\.end\s', text, re.S)
body = m.group(0) if m else text
syms = sorted(set(re.findall(r'\b(D_[0-9A-Fa-f]{6,8}|jtbl_\w+)\b', body)) - defined)
syms = [s for s in syms if not s.startswith('jtbl')] + force
mac = [l.strip() for l in body.split('\n') if re.match(r'\s+(la|dla|lw|sw|lh|lhu|lb|lbu|sh|sb|ld|sd|lwc1|swc1|lq|sq|l\.s|s\.s)\s+\$\w+,\s*[A-Za-z_]', l)]
print('macros', len(mac), mac[:8])
fsy = sorted(set(re.findall(r'\b(func_[0-9a-f]{8})\b', ' '.join(mac))) - defined)
syms += fsy
def add(text, ss):
    pre = ''.join(f'\t.section .ctx,"aw",@progbits\n\t.weak\t{s}\n\t.align 3\n{s}:\n\t.space 8\n' for s in ss)
    return pre + text
base, e = run(text, 'base'); print('base', base, e or '', td)
if os.environ.get('BASEONLY'): sys.exit()
if not syms: print('no syms'); sys.exit()
allr, e = run(add(text, syms), 'all'); print('all', len(syms), allr, e or '')
for s in syms:
    r1, e = run(add(text, [s]), 'one'); 
    if r1 != base: print(' ', s, r1, e or '')
