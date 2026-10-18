# ld.py SRC FUNC [ctx]: LCS word diff listing (ours vs orig), RO env for rodata
import os, sys, subprocess, difflib, re, tempfile, shutil
sys.path.insert(0, '/home/claude/kh1-decomp/tools/matching')
src, fn = sys.argv[1], sys.argv[2]; ctx = int(sys.argv[3]) if len(sys.argv) > 3 else 2
_d = tempfile.mkdtemp(prefix='s11w2ld_')
try:
    if os.environ.get('RO'):
        import lchkro_s10 as L; L.tempfile.mkdtemp = lambda *a, **k: _d; td = _d
    else:
        import lchk_s10 as L; td = str(L._TD)
    if os.environ.get('EX'): L.extra = os.environ['EX'].split()
    r = L.check(src, fn); print(r)
    import autodecomp as A
    a = A.resolve(fn, L.reg); f = A._layout[a]
    def dis(path, start, size, sec=None):
        args = ['mips-linux-gnu-objdump', '-d', '-m', 'mips:5900', '-EL', '-M', 'gpr-names=32,reg-names=numeric' if False else 'gpr-names=32']
        args += ['--start-address=0x%x' % start, '--stop-address=0x%x' % (start + size), path]
        o = subprocess.run(args, capture_output=True, text=True).stdout
        out = []
        for l in o.split('\n'):
            m = re.match(r'\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)', l)
            if m: out.append((m.group(1), m.group(2), re.sub(r'\s+', ' ', m.group(3).split('<')[0]).strip()))
        return out
    ours = dis(td + '/c.elf', a, r[fn][2]); th = dis('/home/claude/kh1-decomp/SLPS_251.98', a, f.size)
    sm = difflib.SequenceMatcher(None, [x[1] for x in ours], [x[1] for x in th], autojunk=False)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal': continue
        print('---', tag)
        for k in range(max(i1 - ctx, 0), i1): print('   %s %s' % (ours[k][0], ours[k][2]))
        for k in range(i1, i2): print(' < %s %s' % (ours[k][0], ours[k][2]))
        for k in range(j1, j2): print(' > %s %s' % (th[k][0], th[k][2]))
finally:
    shutil.rmtree(_d, True)
