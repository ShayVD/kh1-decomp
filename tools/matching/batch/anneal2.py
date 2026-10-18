# anneal2.py FILE MODE FNAME ITERS BATCH SEED [extra flags]
# FILE: prefix, line '/*UNIT*/', then unit (inline helpers + function). Groups of lines between /*P*/ and /*Q*/ are permuted (within group).
import sys, random, re
sys.path.insert(0, '/tmp/claude-0/s7/w13/tools')
import batch
f, mode, fname = sys.argv[1:4]
iters, B, seed = int(sys.argv[4]), int(sys.argv[5]), int(sys.argv[6])
extra = sys.argv[7].split() if len(sys.argv) > 7 and sys.argv[7] else []
random.seed(seed)
s = open(f).read()
i = s.index('/*UNIT*/\n'); prefix = s[:i]; unit = s[i+9:]
parts = re.split(r'(/\*P\*/\n|/\*Q\*/)', unit)
# parts: text, P, group, Q, text, ...
segs = []; k = 0
while k < len(parts):
    if parts[k] == '/*P*/\n':
        segs.append([l for l in parts[k+1].split('\n') if l.strip()]); k += 3
    else:
        segs.append(parts[k]); k += 1
inl = re.findall(r'static inline [^(]*?\b(\w+)\s*\(', unit)
def render(sg, v=None):
    t = ''.join(x if isinstance(x, str) else '/*P*/\n' + '\n'.join(x) + '\n/*Q*/' for x in sg)
    if v is not None:
        for n in inl: t = re.sub(r'\b%s\b' % n, f'{n}__w{v}', t)
    return t
def mut(sg):
    sg = [x[:] if isinstance(x, list) else x for x in sg]
    gs = [g for g in sg if isinstance(g, list) and len(g) > 1]
    for _ in range(random.choice([1,1,1,2,2,3])):
        p = random.choice(gs)
        a, b = random.randrange(len(p)), random.randrange(len(p))
        if random.random() < 0.5: p[a], p[b] = p[b], p[a]
        else: x = p.pop(a); p.insert(b, x)
    return sg
def sc(cands):
    return batch.score(prefix, fname, [render(c, v) for v, c in enumerate(cands)], mode, extra)
cur = segs; cs = sc([cur])[0]; best = cs
print('start', cs, flush=True)
for it in range(iters):
    cands = [mut(cur) for _ in range(B)]
    r = sc(cands)
    m = min(r); k = random.choice([j for j in range(B) if r[j] == m])
    if m <= cs: cur, cs = cands[k], m
    if cs < best:
        best = cs; open(f + '.best', 'w').write(prefix + '/*UNIT*/\n' + render(cur)); print(it, 'best', best, flush=True)
    if cs == 0: print('MATCH'); break
open(f + '.cur', 'w').write(prefix + '/*UNIT*/\n' + render(cur))
print('final', cs, 'best', best)
