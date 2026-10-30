#!/usr/bin/env python3
"""tools/ovl/storeperm.py (session 141, wwm1 round 25): OVL DRAFT

Store-order sweep. Finds each run of up to 7 consecutive simple stores (one-line `lvalue = expr;` or `lvalue op= expr;`
at one indentation, no call, no ++/--, no declaration, no control statement or label: a one-line `if (c) x = y;`,
`case 1: x = y;` or `L: x = y;` never moves) where no statement reads or rewrites what another one in the
run writes, and tries every order of that run with hand.py try. The runs are swept one at a time, top to bottom; a
run's best order is kept only if hand.py's score goes down, and later runs start from it. dkmovie func_00f270c8
matched this way (round 24): only the order of its last six stores was wrong.

Prints the score per run and the final result. A match is written to $OVLTOOL_DIR/sp_match_FUNC[.mode].c (default
out/ovl/tools); OUT=path writes the best version found. MAXN=n (default 7) limits the run length (n! orders per run, 7! = 5040 at about
0.2 s each), and TLIM=seconds stops the sweep after that long (the runs left are listed). FROM=line skips the runs that start
above that line (to resume a cut-off sweep from its OUT file). DRY=1 only
lists the runs.
A store through one pointer can alias a store through another; the sweep does not check that, so read a kept order
before trusting the draft's behaviour (a byte-identical match settles it)."""
import subprocess, sys, re, os, itertools, time
W = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
D = os.environ.get('OVLTOOL_DIR', os.path.join(W, 'out', 'ovl', 'tools'))
os.makedirs(D, exist_ok=True)
MAXN = int(os.environ.get('MAXN', '7'))
TLIM = float(os.environ.get('TLIM', '0'))
T0 = time.time()
o, d = sys.argv[1:3]
base = os.path.basename(d)
f = base.split('.')[0]
mode = '.' + base.split('.')[1] if base.count('.') > 1 else ''
L = open(d).read().split('\n')
ST = re.compile(r'^(\s+)([^=;{}"]+?)\s*(=|\+=|-=|\*=|/=|\|=|&=|\^=|<<=|>>=)\s*([^;{}"]+);\s*$')
CALL = re.compile(r'\b(?!sizeof\b|if\b|while\b|for\b|switch\b|return\b)[A-Za-z_]\w*\s*\(')
CTRL = re.compile(r'^\s*(if|else|for|while|do|switch|return|case|default|goto|break|continue)\b|^\s*[A-Za-z_]\w*\s*:(?!:)')
DECL = re.compile(r'^(const\s+|static\s+|volatile\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*[\s\*]+[A-Za-z_]\w*(\[[^\]]*\])?$')


def store(line):
    m = ST.match(line)
    if not m or '++' in line or '--' in line or '==' in m.group(2) or CTRL.match(line):
        return None
    lv, rhs = m.group(2).strip(), m.group(4)
    if CALL.search(lv) or CALL.search(rhs) or DECL.match(lv) or '?' in lv:
        return None
    return m.group(1), re.sub(r'\s+', '', lv), m.group(3), re.sub(r'\s+', '', rhs)


def reads(s):
    # text a statement reads: its right side, its lvalue's index/base expressions, and the lvalue itself for op=
    ind, lv, op, rhs = s
    if op != '=':
        return rhs + ' ' + lv
    m = re.match(r'^(.*?)(->\w+|\.\w+|\[(.*)\])$', lv)
    if not m:
        return rhs + ' ' + lv.lstrip('*(')
    return rhs + ' ' + m.group(1) + ' ' + (m.group(3) or '')


def uses(text, lv):
    if re.match(r'^[A-Za-z_]\w*$', lv):
        return re.search(r'\b%s\b' % re.escape(lv), text) is not None
    return re.search(re.escape(lv) + r'(?!\w)', text) is not None


def dep(a, b):
    if a[1] == b[1]:
        return True
    return uses(reads(b), a[1]) or uses(reads(a), b[1])


def runs(T):
    out = []
    i = 0
    while i < len(T):
        s = store(T[i])
        if not s:
            i += 1
            continue
        cur = [i]
        j = i + 1
        while j < len(T) and len(cur) < MAXN:
            t = store(T[j])
            if not t or t[0] != s[0] or any(dep(store(T[k]), t) for k in cur):
                break
            cur.append(j)
            j += 1
        if len(cur) > 1:
            out.append(cur)
        i = j
    return out


def score(T):
    p = os.path.join(D, 'sp_%s_%s%s.c' % (o, f, mode))
    open(p, 'w').write('\n'.join(T))
    r = subprocess.run(['python3', 'tools/ovl/hand.py', 'try', o, f, p], cwd=W, capture_output=True, text=True).stdout.split('\n')[0]
    if 'MATCH' in r and 'FAIL' not in r:
        open(os.path.join(D, 'sp_match_%s%s.c' % (f, mode)), 'w').write('\n'.join(T))
        return 0, r
    m = re.search(r'score (\d+)', r)
    return (int(m.group(1)) if m else 99999), r


best, r0 = score(L)
start = best
print('%s %s start %d (%s)' % (o, f, best, r0[10:80]), flush=True)
R = [c for c in runs(L) if c[0] + 1 >= int(os.environ.get('FROM', '0'))]
print('runs:', ' '.join('%d+%d' % (c[0] + 1, len(c)) for c in R), flush=True)
if os.environ.get('DRY'):
    sys.exit(0)
for c in R:
    if best == 0:
        break
    if TLIM and time.time() - T0 > TLIM:
        print('  time limit: runs at lines %s not tried' % ' '.join(str(x[0] + 1) for x in R[R.index(c):]), flush=True)
        break
    lines = [L[k] for k in c]
    rb, ro = best, None
    for perm in itertools.permutations(range(len(c))):
        if perm == tuple(range(len(c))):
            continue
        T = list(L)
        for k, q in zip(c, perm):
            T[k] = lines[q]
        s, _ = score(T)
        if s < rb:
            rb, ro = s, T
            if s == 0:
                break
    if ro is not None:
        L = ro
        print('  run at line %d (%d stores): %d -> %d' % (c[0] + 1, len(c), best, rb), flush=True)
        best = rb
print('%s %s %s %d -> %d' % (o, f, 'MATCH' if best == 0 else 'done', start, best), flush=True)
if os.environ.get('OUT'):
    open(os.environ['OUT'], 'w').write('\n'.join(L))
