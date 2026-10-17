# perm.py FILE MODE FN a_marker b_marker [fixed_prefix_count] : permute lines in [a,b) (full-line markers, a included), score by words differ
import sys, itertools, subprocess, re, os, threading, glob
from concurrent.futures import ThreadPoolExecutor
f, mode, fn, am, bm = sys.argv[1:6]; fixed = int(sys.argv[6]) if len(sys.argv) > 6 else 0
s = open(f).read(); a = s.index(am); b = s.index(bm)
lines = [l for l in s[a:b].split('\n') if l.strip()]
head, rest = lines[:fixed], lines[fixed:]
d = 'src/hand' if mode == 'hand' else 'src/hand/' + mode
def run(ix):
    k, p = ix
    src = s[:a] + '\n'.join(head + list(p)) + '\n' + s[b:]
    tmp = f'/home/claude/kh1-decomp/{d}/.w6f9_pm{threading.get_ident()}.c'
    open(tmp, 'w').write(src)
    r = subprocess.run(['python3', 'tools/autodecomp.py', 'try', fn, '--file', tmp, '--out-dir', d], cwd='/home/claude/kh1-decomp', capture_output=True, text=True).stdout
    l = r.splitlines()[0] if r else ''
    if 'MATCH' in l and 'mismatch' not in l: sc = 0
    else:
        m = re.search(r'(\d+) vs (\d+) bytes, (\d+) words', l)
        sc = int(m.group(3)) + 4 * abs(int(m.group(1)) - int(m.group(2))) if m else 10**6
    return sc, k, src
perms = list(enumerate(itertools.permutations(rest)))
import threading
lock = threading.Lock()
best = [10**9]
def job(ix):
    sc, k, src = run(ix)
    with lock:
        if sc < best[0]:
            best[0] = sc; open(f + '.pbest', 'w').write(src); print(k, sc, flush=True)
    return sc
ths = []
# two at a time, sequential files per slot
with ThreadPoolExecutor(2) as ex:
    res = list(ex.map(job, perms))
for x in glob.glob(f'/home/claude/kh1-decomp/{d}/.w6f9_pm*.c'): os.remove(x)
print('best', best[0], 'of', len(perms))
