# var_s17.py (s17m1): make variants of a base C file by text substitution and score them.
# usage: python3 -I tools/matching/var_s17.py FUNC MODE_DIR BASE VARFILE
# VARFILE: python file defining V = {name: [(old, new), ...]}; each variant applies its pairs to BASE.
import sys, subprocess, os
from pathlib import Path
fn, mode, base, vf = sys.argv[1:5]
ns = {}
exec(open(vf).read(), ns)
src = open(base).read()
files = []
for name, subs in ns['V'].items():
    s = src
    ok = True
    for o, n in subs:
        if o not in s:
            print(name, 'MISSING', repr(o[:40])); ok = False; break
        s = s.replace(o, n, 1)
    if not ok: continue
    p = os.path.join(mode, '.s17v_%s.c' % name)
    open(p, 'w').write(s)
    files.append(p)
r = subprocess.run(['python3', '-I', str(Path(__file__).with_name('sc_s17.py')), fn, mode] + files, capture_output=True, text=True)
print(r.stdout + r.stderr)
for p in files: os.unlink(p)
