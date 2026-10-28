# climb_s144.py SRC ADDR TAG STEPS [SEED] (session 144): random source mutations of one function, kept when the
# word count (lro6_s12.check: words not matched in order, +2 if the size is wrong) is no worse; 2% random accepts.
# SRC must sit under a directory whose kh1.toml mode gives the right flags (e.g. src/hand/nostrict/; delete it
# afterwards). The working copy is zz_TAG.c next to SRC; the best so far goes to $WDIR/best_TAG.c (WDIR defaults
# to /tmp/climb). Moves: a statement up / down by 1-12 lines inside its own block, only past statements with no
# textual dependence (can_move: no calls, no shared variable or field name); declaration swaps; operand swaps of
# a single top-level commutative operator. Score 0 is a candidate only: check it with make.
import sys, os, random, re, time, shutil
from pathlib import Path
src, addr, tag, steps = sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4])
seed = int(sys.argv[5]) if len(sys.argv) > 5 else int(time.time())
random.seed(seed)
S = Path(os.environ.get('WDIR', '/tmp/climb')); os.environ['WDIR'] = str(S / ('w_' + tag)); os.makedirs(os.environ['WDIR'], exist_ok=True)
os.environ.setdefault('RO', '0')
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lro6_s12 as L
work = Path(src).parent / f'zz_{tag}.c'
lines = Path(src).read_text().split('\n')
# body region: lines after the first line that opens the target function
fn = 'func_' + addr
def score(ls):
    work.write_text('\n'.join(ls))
    import io, contextlib
    with contextlib.redirect_stdout(io.StringIO()):
        r = L.check(str(work), fn)
    if not r or fn not in r: return None
    d, pos, n, sz = r[fn]
    return d * 4 + (0 if n == sz else 2) , d
start = next(i for i, l in enumerate(lines) if re.search(r'\b' + fn + r'\s*\(', l) and not l.startswith(' ') and not l.rstrip().endswith(';'))
while not lines[start].rstrip().endswith('{'): start += 1
end = next(i for i in range(start + 1, len(lines)) if lines[i].startswith('}'))
def stmt(l):
    s = l.strip()
    return s.endswith(';') and not s.startswith(('return', 'break', 'continue', 'goto', 'case', 'default')) and '{' not in s and '}' not in s and not s.startswith('//')
def indent(l): return len(l) - len(l.lstrip())

KW = {'if','while','for','sizeof','return','switch'}
def lhs_of(l):
    s = l.strip().rstrip(';')
    m = re.match(r'^(.*?[^=!<>+\-*/|&^])\s*([+\-*/|&^]|<<|>>)?=(?!=)', s)
    if m: return m.group(1).strip()
    m = re.match(r'^(\+\+|--)?\s*([\w.>\-\[\]]+?)\s*(\+\+|--)?$', s)
    if m and (m.group(1) or m.group(3)): return m.group(2)
    return None
def has_call(l):
    return any(n not in KW for n in re.findall(r'\b([A-Za-z_]\w*)\s*\(', l)) or l.count(';') > 1
def conflict(a, b):
    if has_call(a) or has_call(b): return True
    la, lb = lhs_of(a), lhs_of(b)
    if la is None or lb is None: return True
    for x, y in ((la, b), (lb, a)):
        if re.fullmatch(r'\w+', x):
            if re.search(r'\b' + x + r'\b', y): return True
        else:
            f = re.findall(r'[\w]+', x)[-1]  # last field / name of the store
            if re.search(r'\b' + f + r'\b', y): return True
            if '*' in x and '->' not in x and '.' not in x and '[' not in x: return True
    return False
def can_move(c, i, j):
    lo, hi = (j, i) if j < i else (i, j)
    rng = range(lo, hi + 1)
    for k in rng:
        if k == i: continue
        if not stmt(c[k]) or indent(c[k]) != indent(c[i]): return False
        if conflict(c[i], c[k]): return False
    return True
best = score(lines); cur = list(lines); curs = best
print('seed', seed, 'base', best, flush=True)
bestl = list(lines)
for it in range(steps):
    c = list(cur)
    cand = [i for i in range(start + 1, end) if stmt(c[i])]
    op = random.random()
    if op < 0.85:
        i = random.choice(cand)
        k = random.choice([-3, -2, -1, 1, 2, 3]) if op < 0.5 else random.randint(-12, 12)
        j = i + k
        if k == 0 or j <= start or j >= end or not can_move(c, i, j): continue
        l = c.pop(i); c.insert(j, l)
    elif op < 0.93:
        dre = re.compile(r'^\s*(const |volatile |register )*(s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|int|struct \w+|[A-Z]\w*)\s+\**\w+(\[\w*\])?\s*(,\s*\**\w+)*;\s*$')
        ds = [i for i in range(start + 1, end) if dre.match(c[i])]
        if len(ds) < 2: continue
        i = random.choice(ds); js = [j for j in ds if j != i and indent(c[j]) == indent(c[i]) and abs(j - i) < 40]
        if not js: continue
        j = random.choice(js); c[i], c[j] = c[j], c[i]
    else:
        # swap operands of a top-level commutative op in one assignment: "x = A | B;" -> "x = B | A;"
        i = random.choice(cand); s = c[i]
        m = re.match(r'^(\s*[^=]+?=\s*)(.+);\s*$', s)
        if not m: continue
        e = m.group(2); depth = 0; cuts = []
        for p, ch in enumerate(e):
            if ch in '([': depth += 1
            elif ch in ')]': depth -= 1
            elif depth == 0 and ch in '+|*&^' and e[p-1:p] != ch and e[p+1:p+2] not in (ch, '='): cuts.append(p)
        if len(cuts) != 1: continue
        p = cuts[0]; c[i] = m.group(1) + e[p+1:].strip() + ' ' + e[p] + ' ' + e[:p].strip() + ';'
    r = score(c)
    if r is None: continue
    if r[0] <= curs[0] or random.random() < 0.02:
        cur, curs = c, r
        if r[0] < best[0]:
            best = r; bestl = list(c)
            (S / f'best_{tag}.c').write_text('\n'.join(bestl))
            print(it, 'BEST', best, flush=True)
            if best[1] == 0: break
    if curs[0] > best[0] + 24: cur, curs = list(bestl), best
    if it % 200 == 0: print(it, 'cur', curs, 'best', best, flush=True)
work.unlink(missing_ok=True)
