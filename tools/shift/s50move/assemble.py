#!/usr/bin/env python3
"""Module assembler (phase 4, session 50; docs/modules.md "Session 50").

  python3 -I tools/shift/s50move/assemble.py OUT.c func_X ...

Writes a module from the functions' current files (out/gen/placements.tsv,
so run `make` first), in the order given, each preceded by what it saw
above it in its old file and uses (declarations, typedefs, macros, static
inline helpers, CONTEXT_ONLY copies), emitted once:

- a typedef / struct whose name is already taken by a different body is
  renamed for this function (NAME_<addr>), with its users;
- an extern whose name is already declared with another type becomes a
  view for this function only: `#define D_X (*(T (*)) &D_X)` ... `#undef`;
- a macro is #undef'd after the function unless the next function needs
  the same text;
- a prototype that disagrees with an earlier one (or the definition) is
  left out and listed as CONFLICT (check its return / float arguments);
- includes go where the old file had them (trailing ones at the end).

Old files' trailing includes are kept at the end.  The result is a draft:
check it with tools/checkfile.py, prune what it does not need
(tools/shift/s50move/prune.py), then `mod.py remove`, `make` and fcheck.sh.
"""
import sys, re, os
from pathlib import Path
HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent / 's36move'))
import ctop
ROOT = str(Path(__file__).resolve().parents[3]); os.chdir(ROOT)


def placements():
    src = {}
    for l in open('out/gen/placements.tsv'):
        p = l.rstrip('\n').split('\t')
        if len(p) > 3 and p[0] != 'addr':
            src[p[1]] = (p[0], p[3])
    return src


def strip(t): return re.sub(r'/\*.*?\*/|//[^\n]*', '', t, flags=re.S)
def norm(t): return re.sub(r'\s+', ' ', strip(t)).strip()
def idents(t): return set(re.findall(r'\b[A-Za-z_]\w*\b', strip(t)))
def sub(t, a, b): return re.sub(r'\b' + re.escape(a) + r'\b', b, t)


KW = set('extern static const volatile unsigned signed int char short long float double void '
         'struct union enum typedef register inline __inline__ __attribute__ aligned mode TI DI SI '
         's8 u8 s16 u16 s32 u32 s64 u64 f32 f64 u128 s128 sizeof'.split())


def no_attr(s):
    """drop __attribute__((...)) with balanced parentheses."""
    while True:
        i = s.find('__attribute__')
        if i < 0: return s
        j = s.index('(', i); d = 0
        for k in range(j, len(s)):
            d += {'(': 1, ')': -1}.get(s[k], 0)
            if d == 0: break
        s = s[:i] + s[k + 1:]


def classify(t, k, name):
    """-> (kind, names): kind in typedef, tag, var, proto, define, undef, include, inline, ctx, func, other."""
    s = strip(t).strip()
    if k == 'pp':
        m = re.match(r'#\s*define\s+(\w+)', s)
        if m: return 'define', [m.group(1)]
        m = re.match(r'#\s*undef\s+(\w+)', s)
        if m: return 'undef', [m.group(1)]
        if s.startswith('#include'): return 'include', []
        return 'other', []
    if k == 'func':
        if 'CONTEXT_ONLY' in s.split('{')[0]: return 'ctx', [name]
        if re.match(r'static\s+(inline|__inline__)', s): return 'inline', [name]
        return 'func', [name]
    if k != 'decl': return 'other', []
    s2 = no_attr(s)
    if s2.startswith('typedef'):
        body = re.sub(r'\{.*\}', '', s2, flags=re.S)
        m = re.search(r'\(\s*\*\s*(\w+)\s*\)', body)
        if m: return 'typedef', [m.group(1)]
        n = re.findall(r'(\w+)\s*(?:\[[^\]]*\]\s*)*[;,]', body)
        return 'typedef', n
    m = re.match(r'(struct|union|enum)\s+(\w+)\s*(\{.*\})?\s*;$', s2, flags=re.S)
    if m: return 'tag', [m.group(2)]
    if '(' in re.sub(r'\{.*\}', '', s2, flags=re.S) and not re.search(r'\(\s*\*', s2):
        m = re.search(r'(\w+)\s*\(', s2)
        return 'proto', [m.group(1)]
    names = []
    body = re.sub(r'=.*$', '', s2.rstrip(';'), flags=re.S)
    for part in split_top(body):
        m = re.search(r'\(\s*\*+\s*(\w+)\s*\)', part)
        if m: names.append(m.group(1)); continue
        m = re.search(r'(\w+)\s*(\[[^\]]*\]\s*)*$', part.strip())
        if m and m.group(1) not in KW: names.append(m.group(1))
    return 'var', names


def split_top(s):
    out, cur, d = [], '', 0
    for ch in s:
        if ch in '([{': d += 1
        if ch in ')]}': d -= 1
        if ch == ',' and d == 0: out.append(cur); cur = ''
        else: cur += ch
    out.append(cur)
    return out


def var_decls(t):
    """split `extern T a, *b[4];` into one declaration per name: [(name, decl)]."""
    kind, names = classify(t, 'decl', None)
    s = strip(t).strip().rstrip(';')
    if len(names) <= 1:
        return [(n, s + ';') for n in names]
    parts = split_top(s)
    m = re.search(r'\b' + re.escape(names[0]) + r'\b', parts[0])
    k = m.start()
    while k > 0 and parts[0][k - 1] in '*( \t': k -= 1
    base = parts[0][:k].rstrip() + ' '
    out = [(names[0], (base + parts[0][k:].strip()).strip() + ';')]
    for n, p in zip(names[1:], parts[1:]):
        out.append((n, (base + p.strip()).strip() + ';'))
    return out


def view(name, decl):
    """`extern T *D_X[4];` -> `#define D_X (*(T *(*)[4]) &D_X)`."""
    s = re.sub(r'^\s*extern\s+', '', strip(decl)).strip().rstrip(';')
    s = re.sub(r'\b(volatile)\b\s*', r'\1 ', s)
    ty = sub(s, name, '(*)')
    return '#define %s (*(%s) &%s)' % (name, ty, name)


def main(out, funcs):
    src = placements()
    files = {}
    for f in funcs:
        files.setdefault(src[f][1], ctop.items(open(src[f][1]).read()))
    inmod = set(funcs)
    plan = []  # (func, [(kind, names, text)], body)
    for f in funcs:
        addr, path = src[f]
        its = files[path]
        scope = {}  # name -> (order, kind, text)
        order = 0
        incs = []
        body = None
        for t, k, n in its:
            kind, names = classify(t, k, n)
            order += 1
            if kind == 'func' and n == f:
                body = t.strip('\n') + '\n'; break
            if kind == 'undef':
                for x in names: scope.pop(x, None)
                continue
            if kind == 'include':
                incs.append((order, t.strip())); continue
            if kind == 'var':
                for nm, d in var_decls(t):
                    scope[nm] = (order, 'var', d)
                continue
            if kind == 'func':
                continue  # a real definition above: not copied (see the docstring)
            for x in names:
                scope[x] = (order, kind, t.strip('\n'))
        assert body, (f, path)
        need, used = {}, idents(body)
        changed = True
        while changed:
            changed = False
            for x in list(used):
                if x in scope and x not in need and x != f:
                    if scope[x][1] == 'ctx' and x in inmod: continue
                    need[x] = scope[x]; used |= idents(scope[x][2]); changed = True
        notes = [t.strip('\n') for t, k, n in its if k == 'comment' and re.search(r'\b' + f + r'\b', t)
                 and not re.search(r'\b(is|are) in\b', t)]
        body = ''.join(x + '\n' for x in notes) + body
        tail_incs = []
        after = False
        for t, k, n in its:
            if k == 'func' and n == f: after = True; continue
            if after and k == 'pp' and strip(t).strip().startswith('#include'):
                tail_incs.append(t.strip())
        plan.append((f, addr, path, sorted(need.items(), key=lambda kv: kv[1][0]), incs, body, tail_incs))

    emitted = {}  # name -> (kind, norm text)
    macros = {}   # active macro name -> norm text
    lines = ['/* TODO: what this module is (docs/modules.md). */']
    seen_inc = set(); trailing = []
    conflicts = []
    for idx, (f, addr, path, need, incs, body, tail_incs) in enumerate(plan):
        sec = ['', '/* %s (from %s). */' % (f, path.replace('src/', ''))]
        for o, t in incs:
            if t not in seen_inc and (not need or o <= max(v[0] for _, v in need) or True):
                seen_inc.add(t); sec.append(t)
        items = [(nm, v[1], v[2]) for nm, v in need]
        # renames for typedef / tag conflicts, to a fixed point
        ren = {}
        while True:
            def cur(t):
                for a, b in ren.items(): t = sub(t, a, b)
                return t
            new = False
            for nm, kind, t in items:
                if kind in ('typedef', 'tag') and nm not in ren and nm in emitted \
                        and emitted[nm][1] != norm(cur(t)):
                    ren[nm] = '%s_%s' % (nm, addr[-5:]); new = True
            if not new: break
        def cur(t):
            for a, b in ren.items(): t = sub(t, a, b)
            return t
        views = []
        mine = []
        for nm, kind, t in items:
            t2 = cur(t); n2 = ren.get(nm, nm)
            if kind in ('typedef', 'tag', 'inline', 'ctx'):
                if n2 in emitted and emitted[n2][1] == norm(t2): continue
                if n2 in macros: sec.append('#undef ' + n2); macros.pop(n2)
                emitted[n2] = (kind, norm(t2)); sec.append(t2); continue
            if kind == 'var':
                if nm in macros: sec.append('#undef ' + nm); macros.pop(nm)
                if nm not in emitted:
                    emitted[nm] = ('var', norm(t2)); sec.append(t2)
                elif emitted[nm][1] != norm(t2):
                    views.append(view(nm, t2))
                continue
            if kind == 'proto':
                if nm in emitted:
                    if emitted[nm][1] != norm(t2):
                        conflicts.append('%s: %s  vs  %s' % (f, norm(t2), emitted[nm][1]))
                    continue
                emitted[nm] = ('proto', norm(t2)); sec.append(t2); continue
            if kind == 'define':
                if macros.get(nm) == norm(t2): continue
                if nm in macros: sec.append('#undef ' + nm)
                macros[nm] = norm(t2); mine.append(nm); sec.append(t2); continue
        for v in views:
            sec.append(v)
        b = cur(body)
        # a definition after a prototype: the definition wins in `emitted`
        mm = re.match(r'([^{]*?)\b' + re.escape(f) + r'\s*\(([^)]*)\)', strip(b), flags=re.S)
        if f in emitted and emitted[f][0] == 'proto':
            pass
        emitted[f] = ('def', norm(b.split('{')[0]))
        sec.append(b.rstrip('\n'))
        for v in views:
            sec.append('#undef ' + re.match(r'#define (\w+)', v).group(1))
        nxt = {}
        if idx + 1 < len(plan):
            for nm, v in plan[idx + 1][3]:
                if v[1] == 'define': nxt[nm] = norm(v[2])
        for nm in mine:
            if nxt.get(nm) != macros.get(nm):
                sec.append('#undef ' + nm); macros.pop(nm, None)
        lines += sec
        for t in tail_incs:
            if t not in seen_inc and t not in trailing: trailing.append(t)
    lines.append('')
    lines += trailing
    open(out, 'w').write(re.sub(r'\n{3,}', '\n\n', '\n'.join(lines) + '\n'))
    for c in conflicts: print('CONFLICT', c)


if __name__ == '__main__':
    if len(sys.argv) < 3: sys.exit(__doc__)
    main(sys.argv[1], sys.argv[2:])
