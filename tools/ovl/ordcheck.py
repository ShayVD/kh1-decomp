#!/usr/bin/env python3
"""tools/ovl/ordcheck.py (session 141, wwm1 rounds 25-26): DRAFT...

Audits statement reorders in a draft's git history. For each pair of consecutive git versions of each file
(git log --follow), it lines up the identical statement lines of the two versions and finds every pair whose
relative order flipped. A flip is flagged when
  control  one line is control flow or a label: break, return, goto, continue, case, default, `L:`, else, an
           `if (...) {` / for / while / switch line, or a one-line if that returns, breaks, continues or jumps
           (a one-line `if (c) x = y;` or `while (c) x += y;` is judged as data);
  incdec   one line writes a name with ++ or -- inside a larger statement and the other line uses that name;
  data     one line assigns a plain variable (or ++/--) and the other line uses it.
Two lines in opposite arms of one if/else (in either version) never both run, so their flip is not flagged
(this covers the arm swaps tools/ovl/ifswap.py makes). By default a flip is printed only if the current version still has the pair in
the other order from the first version that had both lines (a later repair clears it); ALL=1 prints every flagged step. Steps that add or drop more
than MAXEDIT (default 6) statement lines are taken as hand rewrites, not reorders, and are skipped. Output: one line per flip with
the file, the commit that made it and the two lines. Not every hit is a bug (a rewrite that also changed other
lines can be fine), so read each one; a byte-identical match is always fine."""
import subprocess, re, sys, os
W = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CTRL = re.compile(r'^\s*(break|return|goto|continue|case|default|if|else|for|while|do|switch)\b|^\s*[A-Za-z_]\w*\s*:(?!:)')
ID = re.compile(r'[A-Za-z_]\w*')
IFO = re.compile(r'^(\s*)(?:\}\s*else\s+)?if\s*\((.*)\)\s*\{\s*$')


def git(*a):
    return subprocess.run(['git'] + list(a), cwd=W, capture_output=True, text=True).stdout


def incw(s):
    return {m.group(1) or m.group(4) for m in re.finditer(r'([A-Za-z_]\w*)\s*(\+\+|--)|(\+\+|--)\s*([A-Za-z_]\w*)', s)}


def plainw(s):
    m = re.match(r'^(?:(?:if|while)\s*\(.*\)\s*)?([A-Za-z_]\w*)\s*(?:[+\-*/%&|^]|<<|>>)?=(?!=)', s)
    return {m.group(1)} if m else set()


def stmts(text):
    # (key, line index) for statement-like lines inside braces; key = (stripped text, occurrence number)
    out, seen, depth = [], {}, 0
    lines = text.split('\n')
    for i, l in enumerate(lines):
        s = l.strip()
        if depth > 0 and s and not s.startswith(('/*', '*', '//')) and (s.endswith(';') or CTRL.match(l)):
            k = (s, seen.get(s, 0))
            seen[s] = k[1] + 1
            out.append((k, i))
        depth += l.count('{') - l.count('}')
    return out, lines


def arm_ranges(lines):
    # (then-arm range, else-arm range) of each `if (C) {...} else {...}` (else-if chains: the else arm runs to the
    # end of the chain)
    rs = []
    for i, l in enumerate(lines):
        m = IFO.match(l)
        if not m:
            continue
        ind = len(m.group(1))
        j = i + 1
        while j < len(lines) and not (len(lines[j]) - len(lines[j].lstrip()) == ind and lines[j].strip().startswith('}')):
            j += 1
        if j < len(lines) and re.match(r'^\s*\}\s*else\b', lines[j]):
            k = j
            while True:
                k += 1
                while k < len(lines) and not (len(lines[k]) - len(lines[k].lstrip()) == ind and lines[k].strip().startswith('}')):
                    k += 1
                if k >= len(lines) or not re.match(r'^\s*\}\s*else\b', lines[k]):
                    break
            rs.append(((i, j), (j, k)))
    return rs


def exclusive(rs, a, b):
    # true when lines a and b sit in opposite arms of one if/else: they never both run, so their order is moot
    return any((t[0] < a < t[1] and e[0] < b < e[1]) or (t[0] < b < t[1] and e[0] < a < e[1]) for t, e in rs)


def conds(lines):
    return {m.group(2).strip() for l in lines for m in [IFO.match(l)] if m}


ONEL = re.compile(r'^\s*(if|while)\s*\(.*\)\s*[^{};]+;\s*$')


def ctrl(l):
    # a one-line `if (c) x = y;` / `while (c) x += y;` is judged by its data (it reads c and y, writes x); one with
    # return, break, continue or goto in it, or any other control line or label, is control
    if ONEL.match(l) and not re.search(r'\b(return|break|continue|goto)\b', l):
        return False
    return bool(CTRL.match(l))


def why(x, y):
    if ctrl(x) or ctrl(y):
        return 'control'
    ix, iy = set(ID.findall(x)), set(ID.findall(y))
    if (incw(x) & iy) or (incw(y) & ix):
        return 'incdec'
    if (plainw(x) & iy) or (plainw(y) & ix):
        return 'data'
    return None


def check(a, b):
    A, la = stmts(a)
    B, lb = stmts(b)
    pa = {k: i for i, (k, _) in enumerate(A)}
    pb = {k: i for i, (k, _) in enumerate(B)}
    lineb = {k: n for k, n in B}
    armsb, armsa = arm_ranges(lb), arm_ranges(la)
    linea = {k: n for k, n in A}
    ca, cb = {}, {}
    for k, _ in A:
        ca[k[0]] = ca.get(k[0], 0) + 1
    for k, _ in B:
        cb[k[0]] = cb.get(k[0], 0) + 1
    # a line whose count changed between the versions cannot be paired up reliably; leave it out
    common = [k for k, _ in A if k in pb and ca[k[0]] == cb[k[0]]]
    edits = (len(A) - len(common)) + (len(B) - len(common))
    if edits > MAXEDIT:
        return []
    bad = []
    for i in range(len(common)):
        for j in range(i + 1, len(common)):
            x, y = common[i], common[j]
            if (pa[x] < pa[y]) == (pb[x] < pb[y]):
                continue
            if exclusive(armsb, lineb[x], lineb[y]) or exclusive(armsa, linea[x], linea[y]):
                continue
            w = why(x[0], y[0])
            if w:
                bad.append((w, x, y, pb[x] < pb[y]))
    return bad


def versions(p):
    revs = [r for r in git('log', '--format=%h %s', '--follow', '--', p).strip().split('\n') if r]
    revs.reverse()
    stem = os.path.basename(p).split('.')[0]
    for r in revs:
        h = r.split()[0]
        for n in git('show', '--name-only', '--format=', h).split():
            if os.path.basename(n).split('.')[0] == stem:
                t = subprocess.run(['git', 'show', '%s:%s' % (h, n)], cwd=W, capture_output=True, text=True)
                if t.returncode == 0:
                    yield r, t.stdout
                    break


ALL = os.environ.get('ALL')
MAXEDIT = int(os.environ.get('MAXEDIT', '6'))
for p in sys.argv[1:]:
    cur = open(p).read() if os.path.exists(p) else ''
    C, _ = stmts(cur)
    pc = {k: i for i, (k, _) in enumerate(C)}
    prev = None
    hist = []
    for r, txt in versions(p):
        V, _ = stmts(txt)
        hist.append({k: i for i, (k, _) in enumerate(V)})
        if prev is not None:
            for w, x, y, xfirst in check(prev, txt):
                # unsafe now only if the current order differs from the first version that had both lines
                base = next(h[x] < h[y] for h in hist if x in h and y in h)
                still = x in pc and y in pc and (pc[x] < pc[y]) != base
                if ALL or still:
                    print('%s  %s  [%s]%s  %r <-> %r' % (os.path.relpath(p, W), r[:70], w, '' if still else ' (since undone)', x[0][:70], y[0][:70]))
        prev = txt
