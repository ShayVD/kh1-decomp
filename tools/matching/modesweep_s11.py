# modesweep_s11.py (session 11): re-measure drafts under every combination of
# strict/nostrict x fill/nofill x {none, -fno-gcse, -fno-sched-interblock}, scored
# by words not in the LCS against the original. Game drafts only (SDK drafts keep
# their mode). usage: WDIR=... python3 modesweep_s11.py drafts.txt [addr...]
# drafts.txt: "addr path" lines (path relative to the repo root; NONE skipped).
import os, sys, re, subprocess, tempfile, difflib, shutil, itertools, json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]; sys.path.insert(0, str(ROOT/'tools'))
import kh1tool as K, autodecomp as A
from elf32 import Elf
A._init(); cfg = A._cfg; orig = K.require_orig(cfg); reg = K.load_registry()
W = Path(os.environ.get('WDIR', '/tmp/claude-0/s11/modes')); W.mkdir(parents=True, exist_ok=True)
TD = Path(tempfile.mkdtemp(prefix='kh1ms_', dir=str(W)))
import atexit; atexit.register(shutil.rmtree, TD, True)
CC = K.TOOLCHAIN_DIR / 'ee-gcc2.96' / 'bin' / 'ee-gcc'

def ro_of(head):
    m = re.search(r'(?:rodata|rr(?:\.py)?|RO=|jtbl_)\s*(?:jtbl_)?(?:at\s+)?(?:0x)?([0-9A-Fa-f]{8})', head)
    if m and 0x480000 <= int(m.group(1), 16) < 0x4c0000: return m.group(1).lower()
    return None

def check(src, inc, addr, flags, nofill, ro=None):
    asm, obj, out = TD/'c.s', TD/'c.o', TD/'c.elf'
    r = subprocess.run([str(CC), '-S', '-x', 'c', '-O2', '-G0', *flags, '-ffunction-sections',
                        f'-I{ROOT/"include"}', f'-I{ROOT/"src"}', f'-I{inc}', '-o', str(asm), str(src)],
                       capture_output=True, text=True, timeout=600)
    if r.returncode: return 'cc: ' + r.stderr[-200:]
    text = K.split_rodata(asm.read_text()); text = K.no_fill(text) if nofill else text
    asm.write_text(text)
    r = subprocess.run([str(CC), '-c', '-x', 'assembler', '-O2', '-G0', '-o', str(obj), str(asm)], capture_output=True, text=True)
    if r.returncode: return 'as: ' + r.stderr[-200:]
    K.fix_object(obj); elf = Elf.load(obj)
    funcs = [s.name[6:] for s in elf.sections if s.name.startswith('.text.')]
    defs = []
    for u in [s.name for s in elf.symbols() if s.shndx == 0 and s.name]:
        a = A.resolve(u, reg)
        if a is None: return 'unresolved ' + u
        defs += ['--defsym', f'{u}=0x{a:08x}']
    secs = ''.join(f'  .f_{fn} 0x{A.resolve(fn, reg):08x} : {{ *(.text.{fn}) }}\n' for fn in funcs if A.resolve(fn, reg) is not None)
    rod = f'  .r 0x{ro} : {{ *(.rodata*) }}\n' if ro else ''
    other = '*(.text .data .bss)' if ro else '*(.text .data .bss .rodata*)'
    (TD/'c.ld').write_text('SECTIONS {\n' + secs + rod + '  .ctx 0x0f000000 : { *(.ctx .ctx.*) }\n  .other 0x40000000 : { ' + other + ' }\n  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.pdr) *(.comment) } }\n')
    r = subprocess.run([f'{K.BINUTILS}ld', '-EL', '--no-warn-mismatch', '-e', '0', '-o', str(out), '-T', str(TD/'c.ld'), *defs, str(obj)], capture_output=True, text=True)
    if r.returncode: return 'ld: ' + r.stderr[-200:]
    L = Elf.load(out)
    for fn in funcs:
        if A.resolve(fn, reg) != addr: continue
        f = A._layout[addr]
        ours = L.section_bytes(L.section(f'.f_{fn}')); theirs = orig.read(f.addr, f.size)
        wo = [ours[i:i+4] for i in range(0, len(ours), 4)]; wt = [theirs[i:i+4] for i in range(0, len(theirs), 4)]
        m = sum(b.size for b in difflib.SequenceMatcher(None, wo, wt, autojunk=False).get_matching_blocks())
        return (max(len(wo), len(wt)) - m, len(ours) - f.size)
    return 'nofunc'

MODES = []
for strict, fill, extra in itertools.product((True, False), (True, False), ('', '-fno-gcse', '-fno-sched-interblock')):
    fl = ([] if strict else ['-fno-strict-aliasing']) + ([extra] if extra else [])
    MODES.append((('strict' if strict else 'nostrict') + ('' if fill else '_nofill') + (extra.replace('-fno-', '_no') if extra else ''), fl, not fill))

def main():
    lines = [l.split() for l in Path(sys.argv[1]).read_text().splitlines() if l.strip()]
    onlys = sys.argv[2:]
    for addr, draft in lines:
        if draft == 'NONE' or (onlys and addr not in onlys): continue
        p = ROOT/draft
        if 'sdk' in p.read_text(errors='replace').split('\n', 1)[0]: print(addr, 'sdk: skipped', flush=True); continue
        ro = ro_of(p.read_text(errors='replace')[:600])
        res = {}
        for name, fl, nf in MODES:
            try: res[name] = check(p, p.parent, int(addr, 16), fl, nf, ro)
            except Exception as e: res[name] = 'exc ' + str(e)[:100]
        ok = {k: v for k, v in res.items() if isinstance(v, tuple)}
        best = sorted(ok.items(), key=lambda kv: (kv[1][0], abs(kv[1][1])))[:4]
        print(addr, draft.split('/')[-1], 'ro' if ro else '', 'best:', ' '.join(f'{k}={v[0]}{"" if v[1]==0 else f"({v[1]:+d}b)"}' for k, v in best),
              '| errs', len(res) - len(ok), flush=True)
        with open(W/'modes.jsonl', 'a') as fh: fh.write(json.dumps({'addr': addr, 'draft': draft, 'res': {k: list(v) if isinstance(v, tuple) else v for k, v in res.items()}}) + '\n')
main()
