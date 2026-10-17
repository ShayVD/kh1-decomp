# subst.py TEMPLATE NAME VAR=val,val... : generate all combos, test each, print scores
import sys, itertools, subprocess, re, os
from concurrent.futures import ThreadPoolExecutor
t = open(sys.argv[1]).read(); name = sys.argv[2]
d = os.environ.get('D', '')
vs = [a.split('=') for a in sys.argv[3:]]
keys = [k for k, _ in vs]; vals = [v.split(',') for _, v in vs]
combos = list(itertools.product(*vals))
def run(ix):
    k, c = ix
    src = t
    for kk, vv in zip(keys, c): src = src.replace('<<<%s>>>' % kk, vv)
    tmp = f'/home/claude/kh1-decomp/src/hand/{d}/.c16_sub_{name}_{k}.c'
    open(tmp, 'w').write(src)
    r = subprocess.run(['python3', 'tools/autodecomp.py', 'try', name, '--file', tmp, '--out-dir', f'src/hand/{d}'], cwd='/home/claude/kh1-decomp', capture_output=True, text=True).stdout
    os.remove(tmp)
    if 'MATCH' in r and 'mismatch' not in r: return (0, c, src)
    m = re.search(r'(\d+) words differ', r)
    return (int(m.group(1)) if m else 10**6, c, src)
with ThreadPoolExecutor(8) as ex: res = sorted(ex.map(run, enumerate(combos)), key=lambda x: x[0])
for r in res[:10]: print(r[0], r[1])
open(sys.argv[1] + '.best', 'w').write(res[0][2])
