# oneoff.py NAME FILE DIR : remove each prototype one at a time, score with sdiff ndiff
import sys, re, subprocess, os
from concurrent.futures import ThreadPoolExecutor
name, f, d = sys.argv[1:4]
s = open(f).read()
protos = [l for l in s.split('\n') if re.match(r'^[A-Za-z].*\bfunc_[0-9a-f]{8}\(.*\);$', l)]
def run(k):
    pr = protos[k] if k >= 0 else None
    src = s if pr is None else s.replace(pr + '\n', '', 1)
    tmp = f'/home/claude/kh1-decomp/{d}/.c14_one_{name}_{k+1}.c'
    open(tmp, 'w').write(src)
    r = subprocess.run(['python3', '/tmp/claude-0/s/c00/sdiff.py', 'tools/autodecomp.py', name, tmp, d], cwd='/home/claude/kh1-decomp', capture_output=True, text=True).stdout
    os.remove(tmp)
    m = re.search(r'ndiff (\d+)', r)
    return (int(m.group(1)) if m else (0 if 'MATCH' in r.split('\n')[0] and 'mismatch' not in r else 10**6), pr)
with ThreadPoolExecutor(8) as ex:
    res = list(ex.map(run, range(-1, len(protos))))
for r in sorted(res, key=lambda x: x[0])[:10]: print(r)
