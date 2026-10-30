#!/usr/bin/env python3
"""tools/ovl/ordcheck.py (session 141, wwm1 rounds 25-26): DRAFT...

Audits statement reorders in a draft's git history. For each pair of consecutive git versions of each file
(git log --follow), it lines up the identical statement lines of the two versions and finds every pair whose
relative order flipped. A flip is flagged when
  control  one line is control flow or a label: break, return, goto, continue, case, default, `L:`, else, an
           `if (...) {` / for / while / switch line, or a one-line if that returns, breaks, continues or jumps
           (a one-line `if (c) x = y;` or `while (c) x += y;` is judged as data);
  incdec   one line writes a name with ++ or -- inside a larger statement and the other line uses that name;
  data     one line assigns a plain variable (also each name of a chain `a = b = c;`, or `&x` passed to a call)
           and the other line uses it;
  call     one line calls a function and the other line calls one too or stores to memory or a D_ global.
Two lines in opposite arms of one if/else (in either version) never both run, so their flip is not flagged
(this covers the arm swaps tools/ovl/ifswap.py makes). By default a flip is printed only if the current version still has the pair in
the other order from the first version that had both lines (a later repair clears it); ALL=1 prints every flagged step. Steps that add or drop more
than MAXEDIT (default 6) statement lines are taken as hand rewrites, not reorders, and are skipped. Output: one line per flip with
the file, the commit that made it and the two lines. Not every hit is a bug (a rewrite that also changed other
lines can be fine), so read each one; a byte-identical match is always fine."""
import subprocess, re, sys, os, difflib
W = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CTRL = re.compile(r'^\s*(break|return|goto|continue|case|default|if|else|for|while|do|switch)\b|^\s*[A-Za-z_]\w*\s*:(?!:)')
ID = re.compile(r'[A-Za-z_]\w*')
IFO = re.compile(r'^(\s*)(?:\}\s*else\s+)?if\s*\((.*)\)\s*\{\s*$')


def git(*a):
    return subprocess.run(['git'] + list(a), cwd=W, capture_output=True, text=True).stdout


def incw(s):
    return {m.group(1) or m.group(4) for m in re.finditer(r'([A-Za-z_]\w*)\s*(\+\+|--)|(\+\+|--)\s*([A-Za-z_]\w*)', s)}


def plainw(s):
    # plain variables assigned by the line, including every name in a chain `a = b = c;` and `&x` passed out
    s = re.sub(r'^(?:if|while)\s*\(.*?\)\s*', '', s)
    w = set(re.findall(r'(?:^|(?<==))\s*([A-Za-z_]\w*)\s*(?:[+\-*/%&|^]|<<|>>)?=(?!=)', s))
    w |= set(re.findall(r'&\s*([A-Za-z_]\w*)\b(?!\s*[\[.])', s))
    return w


CALL = re.compile(r'\b(?!(?:if|while|for|switch|return|sizeof)\b)[A-Za-z_]\w*\s*\(')
MEMW = re.compile(r'^(?:(?:if|while)\s*\(.*?\)\s*)?(\*|[A-Za-z_]\w*\s*(?:->|\.|\[))|^(?:(?:if|while)\s*\(.*?\)\s*)?D_\w+\s*(?:[+\-*/%&|^]|<<|>>)?=(?!=)')


def callish(l):
    # a call that is not a cast: name( ... where the name is not a type keyword used as a cast
    # (names in capitals are taken as macros)
    return any(not re.match(r'^(s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|int|char|void|unsigned|float|double|[A-Z0-9_]+)$', m.group(0).rstrip('( ')) for m in CALL.finditer(l))


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
    # a call may read or write any memory: flag it against another call or a store to memory or a global
    if (callish(x) and (callish(y) or MEMW.match(y))) or (callish(y) and MEMW.match(x)):
        return 'call'
    return None


def align(A, B):
    # map index in A -> index in B for identical statement lines. Copies of one text are paired in order (the
    # k-th `p += 2;` with the k-th): two identical lines swapping places changes nothing, so this pairing never
    # hides a real move, and it never pairs a line with a copy in another case arm. If a text's count changed,
    # only the copies difflib lines up are paired.
    occ, ca = {}, {}
    for j, (k, _) in enumerate(B):
        occ.setdefault(k[0], []).append(j)
    for k, _ in A:
        ca[k[0]] = ca.get(k[0], 0) + 1
    m, seen = {}, {}
    for i, (k, _) in enumerate(A):
        n = seen.get(k[0], 0)
        seen[k[0]] = n + 1
        if ca[k[0]] == len(occ.get(k[0], [])):
            m[i] = occ[k[0]][n]
    # texts whose count changed (a line was edited, added or dropped): pair only what difflib lines up
    ta, tb = [k[0] for k, _ in A], [k[0] for k, _ in B]
    for a0, b0, n in difflib.SequenceMatcher(None, ta, tb, autojunk=False).get_matching_blocks():
        for t in range(n):
            if a0 + t not in m and ca[ta[a0 + t]] != len(occ[ta[a0 + t]]):
                m[a0 + t] = b0 + t
    return m


def check(a, b):
    A, la = stmts(a)
    B, lb = stmts(b)
    m = align(A, B)
    edits = (len(A) - len(m)) + (len(B) - len(m))
    if edits > MAXEDIT:
        return []
    armsb, armsa = arm_ranges(lb), arm_ranges(la)
    idx = sorted(m)
    bad = []
    for p in range(len(idx)):
        for q in range(p + 1, len(idx)):
            i, j = idx[p], idx[q]
            if m[i] < m[j]:
                continue
            x, y = A[i][0][0], A[j][0][0]
            if exclusive(armsa, A[i][1], A[j][1]) or exclusive(armsb, B[m[i]][1], B[m[j]][1]):
                continue
            w = None if x == y else why(x, y)
            if w:
                bad.append((w, x, y))
    return bad


def versions(p):
    # each commit's version of the file, under the path that commit used (git log --follow --name-only), so a
    # commit that also touches a same-named file elsewhere (a session132 original) does not get mixed in
    out = git('log', '--follow', '--name-only', '--format=@@%h %s', '--', p)
    revs = []
    for blk in out.split('@@')[1:]:
        ls = [l for l in blk.split('\n') if l.strip()]
        if len(ls) >= 2:
            revs.append((ls[0], ls[-1]))
    revs.reverse()
    for r, n in revs:
        t = subprocess.run(['git', 'show', '%s:%s' % (r.split()[0], n)], cwd=W, capture_output=True, text=True)
        if t.returncode == 0:
            yield r, t.stdout


ALL = os.environ.get('ALL')
MAXEDIT = int(os.environ.get('MAXEDIT', '6'))
for p in sys.argv[1:]:
    prev = None
    flips = {}  # unordered pair of line texts -> [number of flagged flips, class, last commit]
    for r, txt in versions(p):
        if prev is not None:
            for w, x, y in check(prev, txt):
                k = tuple(sorted((x, y)))
                e = flips.setdefault(k, [0, w, r])
                e[0] += 1
                e[2] = r
                if ALL:
                    print('%s  %s  [%s]  %r <-> %r' % (os.path.relpath(p, W), r[:70], w, x[:70], y[:70]))
        prev = txt
    if not ALL:
        # a pair flipped an odd number of times is still out of its original order (an even count was repaired)
        for (x, y), (n, w, r) in flips.items():
            if n % 2:
                print('%s  %s  [%s]  %r <-> %r' % (os.path.relpath(p, W), r[:70], w, x[:70], y[:70]))
