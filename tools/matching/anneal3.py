# anneal3.py FILE MODE FNAME ITERS BATCH SEED [extra flags]
# like anneal2 but dependency-aware: lines in a /*P*/../*Q*/ group keep def->use order
# (a line defining x stays before lines using x and vice versa); /*FIX*/ lines keep their mutual order.
import sys, random, re
sys.path.insert(0, '/tmp/claude-0/s7/w35/tools')
import batch
f, mode, fname = sys.argv[1:4]
iters, B, seed = int(sys.argv[4]), int(sys.argv[5]), int(sys.argv[6])
extra = sys.argv[7].split() if len(sys.argv) > 7 and sys.argv[7] else []
random.seed(seed)
s = open(f).read()
i = s.index('/*UNIT*/\n'); prefix = s[:i]; unit = s[i+9:]
parts = re.split(r'(/\*P\*/\n|/\*Q\*/)', unit)
ident = re.compile(r'[A-Za-z_]\w*')
def info(l):
    m = re.match(r'\s*([A-Za-z_]\w*)\s*(\+|-|\*|/|\||&)?=[^=]', l)
    dv = m.group(1) if m else None
    m2 = re.match(r'\s*([A-Za-z_]\w*)\s*(\+\+|--)', l)
    if m2: dv = m2.group(1)
    return dv, set(ident.findall(l))
segs = []; groups = []; k = 0
while k < len(parts):
    if parts[k] == '/*P*/\n':
        L = [l for l in parts[k+1].split('\n') if l.strip()]
        n = len(L); inf = [info(l) for l in L]; must = set()
        for a in range(n):
            for b in range(a+1, n):
                da, ua = inf[a]; db, ub = inf[b]
                if '/*FIX*/' in L[a] and '/*FIX*/' in L[b]: must.add((a, b))
                if (da and da in ub) or (db and db in ua): must.add((a, b))
        groups.append((L, must)); segs.append(len(groups)-1); k += 3
    else:
        segs.append(parts[k]); k += 1
inl = re.findall(r'static inline [^(]*?\b(\w+)\s*\(', unit)
def render(perm, v=None):
    t = ''
    for x in segs:
        if isinstance(x, str): t += x
        else: t += '/*P*/\n' + '\n'.join(groups[x][0][j] for j in perm[x]) + '\n/*Q*/'
    if v is not None:
        for n in inl: t = re.sub(r'\b%s\b' % n, f'{n}__w{v}', t)
    return t
def valid(g, p):
    pos = {x: q for q, x in enumerate(p)}
    return all(pos[a] < pos[b] for a, b in groups[g][1])
def mut(perm):
    perm = [p[:] for p in perm]
    gs = [g for g in range(len(groups)) if len(groups[g][0]) > 1]
    for _ in range(random.choice([1, 1, 1, 2, 2, 3])):
        for tries in range(50):
            g = random.choice(gs); p = perm[g][:]
            a, b = random.randrange(len(p)), random.randrange(len(p))
            if random.random() < 0.5: p[a], p[b] = p[b], p[a]
            else: x = p.pop(a); p.insert(b, x)
            if valid(g, p): perm[g] = p; break
    return perm
def sc(cands):
    return batch.score(prefix, fname, [render(c, v) for v, c in enumerate(cands)], mode, extra)
cur = [list(range(len(g[0]))) for g in groups]; cs = sc([cur])[0]; best = cs
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
