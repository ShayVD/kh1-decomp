# prio.py FILE : global-alloc order with refs/live/priority/hard reg (uses cc.py dumps)
import sys, subprocess, re, os, glob, math
f = sys.argv[1]; dd = os.path.join(os.environ.get('WDIR', '/tmp/claude-0/s8/w9'), 'd')
for x in glob.glob(dd + '/.*'): os.remove(x)
subprocess.run(['python3', os.path.join(os.path.dirname(os.path.abspath(__file__)), 'cc_s8.py'), f, 'p', '-dl', '-dg'], cwd='/home/claude/kh1-decomp', capture_output=True)
lreg = open(glob.glob(dd + '/.*lreg')[0]).read(); greg = open(glob.glob(dd + '/.*greg')[0]).read()
fn = sys.argv[2] if len(sys.argv) > 2 else None
if fn:
    i = lreg.index(';; Function ' + fn); lreg = lreg[i:]; lreg = lreg[:lreg.find(';; Function ', 10) if ';; Function ' in lreg[10:] else None]
    i = greg.index(';; Function ' + fn); greg = greg[i:]
info = {}
for m in re.finditer(r'^Register (\d+) used (\d+) times across (\d+) insns(.*)$', lreg, re.M):
    info[int(m.group(1))] = (int(m.group(2)), int(m.group(3)), m.group(4))
order = [int(x) for x in re.search(r'regs to allocate: ([\d ]+)', greg).group(1).split()]
disp = {int(a): int(b) for a, b in re.findall(r'(\d+) in (\d+)', greg.split('Register dispositions:')[1].split('Hard regs')[0])}
names = {16+i: f's{i}' for i in range(8)}; names[30] = 's8'
for i in range(32): names.setdefault(i, f'r{i}')
for i in range(32, 64): names[i] = f'f{i-32}'
for r in order:
    n, l, rest = info.get(r, (0, 1, ''))
    pr = (int(math.log2(n)) if n else 0) * n / l
    print(f'{r:4d} refs {n:3d} live {l:4d} prio {pr:.4f} -> {names.get(disp.get(r), "MEM")}  {"user" if "user var" in rest else ""} calls:{re.search(r"crosses (\d+)", rest).group(1) if "crosses" in rest else 0}')
