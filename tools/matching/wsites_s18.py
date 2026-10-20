# session 18 (s18w): loop insn-count lever sweeps. Needs sc6_s12.py/lro6_s12.py with ROOT pointing at this checkout (set SC6 to a patched copy) and MODE semantics: the copy used in s18 computed flags from $MODE (e.g. src/hand/nostrict) instead of the file path.
# wsites.py MODE ADDR RO BASE FUNC [NS=1,2,3] : wrap RHS of each simple assignment in FUNC with W() n times; score
import sys, os, re, subprocess
from concurrent.futures import ThreadPoolExecutor
R=os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
S=os.environ.get('SCRATCH', '/tmp/s18_' + 'wsites')
SC6=os.environ.get('SC6', os.path.join(R, 'tools/matching/sc6_s12.py'))
mode, addr, ro, base, fn = sys.argv[1:6]
ns = [int(x) for x in (sys.argv[6] if len(sys.argv) > 6 else '1,2,3').split(',')]
src = open(base).read()
W = '#define W(x) ({ __typeof__(x) _w = (x); _w; })\n'
i = src.index('\n', src.index('#include "common.h"')) + 1
src = src[:i] + W + src[i:]
fs = re.search(r'\n[^\n;]*\b' + fn + r'\s*\([^;{]*\)\s*\{', src).end()
# find matching end
d = 1; j = fs
while d: 
    d += {'{':1,'}':-1}.get(src[j], 0); j += 1
body = (fs, j)
sites = []
for m in re.finditer(r'(?<![=!<>+\-*/%&|^])=(?!=)\s*([^;=]+?);', src[fs:j]):
    rhs = m.group(1)
    if rhs.count('(') != rhs.count(')') or '{' in rhs or '"' in rhs: continue
    # skip declarations initialisers in for headers? keep simple
    sites.append((fs + m.start(1), fs + m.end(1)))
def run(job):
    k, n = job
    a, b = sites[k]
    e = src[a:b]
    for _ in range(n): e = 'W(%s)' % e
    t = src[:a] + e + src[b:]
    dd = os.path.join(S, 'ws', '%d_%d' % (k, n)); os.makedirs(dd, exist_ok=True)
    p = os.path.join(dd, 'x.c'); open(p, 'w').write(t)
    env = dict(os.environ, WDIR=dd, MODE=mode)
    r = subprocess.run(['python3', '-I', SC6, p, addr] + ([ro] if ro != '-' else []), capture_output=True, text=True, env=env, cwd=R)
    mm = re.search(r'orig-unmatched (\d+), ours-unmatched (\d+)\) size (\d+)', r.stdout)
    return k, n, src[a:b][:50], (mm.groups() if mm else ('ERR',))
jobs = [(k, n) for k in range(len(sites)) for n in ns]
print(len(sites), 'sites', flush=True)
with ThreadPoolExecutor(4) as ex:
    for k, n, e, r in ex.map(run, jobs): print(k, n, r, e.replace('\n', ' '), flush=True)
