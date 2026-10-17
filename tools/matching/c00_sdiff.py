# sdiff.py TRYPY NAME FILE [DIR]: sequence diff ignoring branch targets
import sys, subprocess, re, difflib
trypy, name, f = sys.argv[1:4]; d = sys.argv[4] if len(sys.argv) > 4 else 'src/hand'
r = subprocess.run(['python3', trypy, 'try', name, '--file', f, '--out-dir', d, '--diff'], cwd='/home/claude/kh1-decomp', capture_output=True, text=True).stdout
lines = r.splitlines()
print(lines[0])
o, u = [], []
for l in lines[1:]:
    m = re.match(r'^([0-9a-f]{8}) (..) (.{40}) ?(.*)$', l)
    if not m: continue
    a, b = m.group(3).strip(), m.group(4).strip()
    norm = lambda x: re.sub(r'0x1[0-9a-f]{5}$', 'L', x)
    if a: o.append((m.group(1), norm(a)))
    if b: u.append(norm(b))
sm = difflib.SequenceMatcher(None, [x[1] for x in o], u, autojunk=False)
n = 0
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal': continue
    n += max(i2 - i1, j2 - j1)
    print(f'--- {tag} @{o[i1][0] if i1 < len(o) else "end"}')
    for x in o[i1:i2]: print('  O', x[1])
    for x in u[j1:j2]: print('  U', x)
print('ndiff', n)
