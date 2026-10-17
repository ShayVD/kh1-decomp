# usage: rr.py RODATA_ADDR(or -) try NAME --file F --out-dir D [--diff]
# places rodata at RODATA_ADDR and every other func_ defined in F at its real address
import sys, pathlib, re
sys.path.insert(0, '/home/claude/kh1-decomp/tools')
ro = sys.argv.pop(1)
_wt = pathlib.Path.write_text
def wt(self, s, *a, **k):
    if self.name == 'c.ld':
        src = (self.parent / 'c.c').read_text()
        m0 = re.search(r'\.text\.(\w+)\)', s).group(1)
        extra = ''
        for n in sorted(set(re.findall(r'^\s*[A-Za-z].*\b(func_([0-9a-f]{8}))\([^;]*$', src, re.M))):
            if n[0] != m0:
                extra += f'  .x{n[1]} 0x{n[1]} : {{ *(.text.{n[0]}) }}\n'
        if ro != '-':
            extra += f'  .r 0x{ro} : {{ *(.rodata*) }}\n'
        s = s.replace('  .other', extra + '  .other')
    return _wt(self, s, *a, **k)
pathlib.Path.write_text = wt
p = pathlib.Path('/home/claude/kh1-decomp/tools/autodecomp.py')
src = p.read_text().replace('return False, "uses rodata (needs hand placement)"', 'pass')
src = src.replace('if any(s.name.startswith(".rodata") and s.size for s in elf.sections):', 'if False:')
sys.argv = [str(p)] + sys.argv[1:]
exec(compile(src, str(p), 'exec'), {'__name__': '__main__', '__file__': str(p)})
