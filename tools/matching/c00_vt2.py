# vt2.py NAME TEMPLATE DIR [-j N]: like vt.py but scores by sequence-diff count (robust to size changes). TRYPY env selects try script.
# template: <<<a@@b>>> alternatives, and <<<PERM\nl1\nl2\n>>>\n permutation blocks
import sys, re, subprocess, itertools, os, difflib
from concurrent.futures import ThreadPoolExecutor
TRY = ['python3', os.environ.get('TRYPY', 'tools/autodecomp.py')]
name, tf, d = sys.argv[1:4]
j = int(sys.argv[5]) if len(sys.argv) > 5 else 6
t = open(tf).read()
parts = re.split(r'<<<(.*?)>>>', t, flags=re.S)
fixed = parts[0::2]; alts = []
for p in parts[1::2]:
    if p.startswith('PERM\n'):
        lines = [l for l in p[5:].split('\n') if l.strip()]
        alts.append(['\n'.join(x) + '\n' for x in itertools.permutations(lines)])
    else:
        alts.append(p.split('@@'))
combos = list(itertools.product(*[range(len(a)) for a in alts]))
print(len(combos), 'combos', flush=True)
def mk(c): return fixed[0] + ''.join(alts[i][c[i]] + fixed[i+1] for i in range(len(c)))
def score(out):
    lines = out.splitlines()
    if not lines or 'MATCH' in lines[0] and 'mismatch' not in lines[0]: return 0
    o, u = [], []
    for l in lines[1:]:
        m = re.match(r'^([0-9a-f]{8}) (..) (.{40}) ?(.*)$', l)
        if not m: continue
        a, b = m.group(3).strip(), m.group(4).strip()
        nm = lambda x: re.sub(r'0x1[0-9a-f]{5}$', 'L', x)
        if a: o.append(nm(a))
        if b: u.append(nm(b))
    if not o: return 10**6
    sm = difflib.SequenceMatcher(None, o, u, autojunk=False)
    return sum(max(i2-i1, j2-j1) for tg, i1, i2, j1, j2 in sm.get_opcodes() if tg != 'equal')
def run(ix):
    k, c = ix
    src = mk(c)
    tmp = f'/home/claude/kh1-decomp/src/hand/{d}/.c00_vt2_{name}_{k}.c'
    open(tmp, 'w').write(src)
    r = subprocess.run([*TRY, 'try', name, '--file', tmp, '--out-dir', f'src/hand/{d}', '--diff'], cwd='/home/claude/kh1-decomp', capture_output=True, text=True).stdout
    os.remove(tmp)
    s = score(r)
    if s == 0: open(tf + '.match', 'w').write(src)
    return (s, c)
with ThreadPoolExecutor(j) as ex:
    res = list(ex.map(run, enumerate(combos)))
res.sort()
for r in res[:10]: print(r)
open(tf + '.best', 'w').write(mk(res[0][1]))
