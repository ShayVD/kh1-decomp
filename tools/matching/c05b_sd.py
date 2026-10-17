# sd.py NAME FILE DIR [-n] [-v]: sequence diff ignoring branch targets; -n normalizes saved regs
import sys, subprocess, re, difflib
name, f, d = sys.argv[1:4]
norm_regs = '-n' in sys.argv; verbose = '-v' in sys.argv
r = subprocess.run(['python3', 'tools/autodecomp.py', 'try', name, '--file', f, '--out-dir', d, '--diff'], cwd='/home/claude/kh1-decomp', capture_output=True, text=True).stdout
lines = r.splitlines()
print(lines[0] if lines else 'nothing')
o, u = [], []
def norm(x):
    x = re.sub(r'0x1[0-9a-f]{5}$', 'L', x)
    if norm_regs:
        x = re.sub(r'\bs[0-8]\b', 'S', x)
        x = re.sub(r'\$f2[0-6]\b', 'F', x)
        x = re.sub(r'\b2(72|76|80|84)\(sp\)', 'SP(sp)', x)
    return x
for l in lines[1:]:
    m = re.match(r'^([0-9a-f]{8}) (..) (.{40}) ?(.*)$', l)
    if not m: continue
    a, b = m.group(3).strip(), m.group(4).strip()
    if a: o.append((m.group(1), norm(a)))
    if b: u.append(norm(b))
sm = difflib.SequenceMatcher(None, [x[1] for x in o], u, autojunk=False)
n = 0
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal': continue
    n += max(i2 - i1, j2 - j1)
    if verbose:
        print(f'--- {tag} @{o[i1][0] if i1 < len(o) else "end"}')
        for x in o[i1:i2]: print('  O', x[1])
        for x in u[j1:j2]: print('  U', x)
print('ndiff', n)
