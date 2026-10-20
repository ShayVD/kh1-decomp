# session 18 (s18w): loop insn-count lever sweeps. Needs sc6_s12.py/lro6_s12.py with ROOT pointing at this checkout (set SC6 to a patched copy) and MODE semantics: the copy used in s18 computed flags from $MODE (e.g. src/hand/nostrict) instead of the file path.
# sweep.py MODE ADDR RO BASE OLD NEWFMT N1,N2,... [HELPER]
# NEWFMT contains {E}: the wrapped expression; wraps EXPR (from OLD's '{' marker?) -> simpler: OLD is replaced by NEWFMT.format(E=wrap(inner,n))
import sys, os, subprocess, re
from concurrent.futures import ThreadPoolExecutor
R=os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
S=os.environ.get('SCRATCH', '/tmp/s18_' + 'sweep')
SC6=os.environ.get('SC6', os.path.join(R, 'tools/matching/sc6_s12.py'))
mode, addr, ro, base, old, inner, fmt, ns = sys.argv[1:9]
helper = sys.argv[9] if len(sys.argv) > 9 else ''
src = open(base).read()
assert old in src, old
if helper:
    i = src.index('\nvoid func_'); src = src[:i] + '\n' + helper + '\n' + src[i:]
def mk(n):
    e = inner
    for _ in range(n): e = 'rdw(%s)' % e
    t = src.replace(old, fmt.replace('{E}', e), 1)
    d = os.path.join(S, 'sw', str(n)); os.makedirs(d, exist_ok=True)
    p = os.path.join(d, 'x.c'); open(p, 'w').write(t)
    env = dict(os.environ, WDIR=d, MODE=mode)
    args = ['python3', '-I', SC6, p, addr] + ([ro] if ro != '-' else [])
    r = subprocess.run(args, capture_output=True, text=True, env=env, cwd=R)
    m = re.search(r'orig-unmatched (\d+), ours-unmatched (\d+)\) size (\d+)', r.stdout)
    return n, (m.groups() if m else r.stdout[-200:] + r.stderr[-300:])
nl = []
for part in ns.split(','):
    if '-' in part:
        a, b, *st = part.split('-'); nl += list(range(int(a), int(b) + 1, int(st[0]) if st else 1))
    else: nl.append(int(part))
with ThreadPoolExecutor(4) as ex:
    for n, r in ex.map(mk, nl): print(n, r, flush=True)
