# tog_s17.py (s17m1): greedy/random toggle climb over choice sites in a C template.
# usage: python3 -I tools/matching/tog_s17.py FUNC MODE_DIR TEMPLATE [iters] [seed]
# TEMPLATE holds sites written as \x01alt0\x03alt1\x03alt2\x02 (control chars; make templates with python) (alternatives may span lines; no nesting).
# Starts from alt0 everywhere, does a full single-site sweep, then random 1-2 site moves (accept <=).
# Writes the best instance to TEMPLATE.best.c and prints progress (true DP LCS, orig words unmatched).
import sys, os, re, random, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
os.chdir(ROOT)
import autodecomp as A, kh1tool as K

def tlcs(a, b):
    prev = [0] * (len(b) + 1)
    for x in a:
        cur = [0] * (len(b) + 1)
        for j, y in enumerate(b):
            cur[j + 1] = prev[j] + 1 if x == y else (prev[j + 1] if prev[j + 1] > cur[j] else cur[j])
        prev = cur
    return prev[-1]

fn, mode, tpl = sys.argv[1:4]
iters = int(sys.argv[4]) if len(sys.argv) > 4 else 300
random.seed(int(sys.argv[5]) if len(sys.argv) > 5 else 1)
A.AUTO_DIR = (ROOT / mode).resolve()
A._init()
A._orig = K.require_orig(A._cfg)
f = K.find_func(fn)
sym = A._names.get(f.addr, f"func_{f.addr:08x}")
theirs = A._orig.read(f.addr, f.size)
tw = [theirs[i:i + 4] for i in range(0, len(theirs), 4)]
A.EXTRA_INCLUDES[:] = [Path(tpl).resolve().parent]
text = open(tpl).read()
parts = re.split(r'\x01(.*?)\x02', text, flags=re.S)
fixed = parts[0::2]
sites = [p.split('\x03') for p in parts[1::2]]
print('sites', len(sites), [len(s) for s in sites], flush=True)
cache = {}

def inst(c):
    out = [fixed[0]]
    for k, ch in enumerate(c):
        out.append(sites[k][ch]); out.append(fixed[k + 1])
    return ''.join(out)

CHECK = os.environ.get('CHECK')
def score(c):
    c = tuple(c)
    if c in cache: return cache[c]
    if CHECK and not eval(CHECK, {'t': inst(c)}):
        cache[c] = 99999; return 99999
    with tempfile.TemporaryDirectory() as td:
        ok, why = A.build_and_compare(f, sym, inst(c), Path(td))
    if ok: s = 0
    elif not A.LAST_BYTES: s = 99999
    else:
        ow = [A.LAST_BYTES[i:i + 4] for i in range(0, len(A.LAST_BYTES), 4)]
        m = tlcs(ow, tw); s = (len(tw) - m) + (len(ow) - m)
    cache[c] = s
    return s

cur = [0] * len(sites)
best = score(cur)
print('start', best, flush=True)
def save(c, s):
    open(tpl + '.best.c', 'w').write(inst(c))
save(cur, best)
improved = True
while improved and best:
    improved = False
    for k in range(len(sites)):
        for ch in range(len(sites[k])):
            if ch == cur[k]: continue
            c = list(cur); c[k] = ch
            s = score(c)
            if s < best:
                best, cur, improved = s, c, True
                print('sweep', best, cur, flush=True); save(cur, best)
for it in range(iters):
    if not best: break
    c = list(cur)
    for _ in range(random.choice((1, 2, 2, 3))):
        k = random.randrange(len(sites))
        c[k] = random.randrange(len(sites[k]))
    s = score(c)
    if s <= best:
        if s < best:
            print('it', it, s, c, flush=True); save(c, s)
        best, cur = s, c
print('best', best, cur, flush=True)
