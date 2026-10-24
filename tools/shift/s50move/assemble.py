#!/usr/bin/env python3
"""Module assembler (phase 4, session 50; docs/modules.md "Session 50").

  python3 -I tools/shift/s50move/assemble.py OUT.c func_X ...
  python3 -I tools/shift/s50move/assemble.py --onto MODULE.c func_X ...
      (append to an existing module: what it declares counts as emitted)

Writes a module from the functions' current files (out/gen/placements.tsv,
so run `make` first), in the order given, each preceded by what it saw
above it in its old file and uses (declarations, typedefs, macros, static
inline helpers, CONTEXT_ONLY copies), emitted once:

- a typedef / struct whose name is already taken by a different body is
  renamed for this function (NAME_<addr>), with its users;
- an extern whose name is already declared with another type becomes a
  view for this function only, then `#undef`: a scalar by value
  `#define D_X ((T) D_X)`, an array by address `#define D_X ((T *) D_X)`,
  and one whose address is taken by memory `#define D_X (*(T *) &D_X)`
  (a memory view of a scalar reorders loads in a strict-aliasing file);
- a macro is #undef'd after the function unless the next function needs
  the same text;
- a prototype that disagrees with an earlier one (or the definition) is
  left out and listed as CONFLICT (check its return / float arguments);
- a prototype that disagrees in its return kind, argument count or a float
  argument is viewed for the function: `#define F ((RET (*)(ARGS)) F)`;
- includes go where the old file had them (trailing ones are dropped).

The result is a draft:
check it with tools/checkfile.py, prune what it does not need
(tools/shift/s50move/prune.py), then `mod.py remove`, `make` and fcheck.sh.
"""
import sys, re, os
from pathlib import Path
HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent / 's36move'))
import ctop
ROOT = str(Path(__file__).resolve().parents[3]); os.chdir(ROOT)


def citems(src):
    """ctop.items, with macro invocation lines (MACRO(a, b) with no ';', as in
    a macro-generated definition) split off the declaration ctop runs them
    into, as items of their own (kind 'macro')."""
    out = []
    for t, k, n in ctop.items(src):
        if k == 'decl':
            lines = t.split('\n'); i = 0; pre = []
            while i < len(lines) and (lines[i].strip() == '' or re.match(r'\s*\w+\(.*\)\s*$', lines[i])):
                pre.append(lines[i]); i += 1
            if any(l.strip() for l in pre) and i < len(lines):
                out.append(('\n'.join(pre) + '\n', 'macro', None))
                out.append(('\n'.join(lines[i:]), k, n)); continue
        out.append((t, k, n))
    return out


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
        if i < 0: i = s.find('ALIGNED(')  # include/common.h's __attribute__((aligned(n)))
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
        m = re.match(r'typedef\s+(struct|union|enum)\s+(\w+)\s*\{', s2)
        if m and m.group(2) not in n: n = n + [m.group(2) + '#tag']  # the tag it declares too
        return 'typedef', n
    m = re.match(r'(struct|union|enum)\s+(\w+)\s*(\{.*\})?\s*;$', s2, flags=re.S)
    if m: return 'tag', [m.group(2) + '#tag']  # the tag namespace
    m = re.match(r'([^(]*?)\b(\w+)\s*(\[[^\]]*\]\s*)*__asm__\s*\(', s2, flags=re.S) \
        or re.match(r'([^(]*?)\b(\w+)\s*(\(.*\))\s*__asm__\s*\(', s2, flags=re.S)
    if m:  # `extern T D_X __asm__("D_X");` (or a prototype) under `#define D_X D_X_<addr>`: a renamed alias
        return 'asmvar', [m.group(2) + '#asm']
    m = re.match(r'[^(]*?\b(\w+)\s*\(', re.sub(r'\{.*\}', '', s2, flags=re.S))
    if m and m.group(1) not in KW:  # the first '(' follows a name: a prototype
        if '{' not in s2:  # `void f(), g();` declares both (session 52)
            return 'proto', [n for n, d in proto_decls(s2)]
        return 'proto', [m.group(1)]
    names = []
    body = re.sub(r'=.*$', '', s2.rstrip(';'), flags=re.S)
    for part in split_top(body):
        m = re.search(r'\(\s*\*+\s*(\w+)\s*(\[[^\]]*\]\s*)*\)', part)  # (*f)(...), (*f[n])(...)
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


def proto_decls(t):
    """split `extern void f(), g(int);` into one prototype per name: [(name, decl)]."""
    s = re.sub(r'^\s*extern\s+', '', no_attr(strip(t)).strip().rstrip(';'))
    parts = split_top(s)
    m = re.match(r'(.*?)\b(\w+)\s*\(', parts[0], flags=re.S)
    if not m: return []
    out = [(m.group(2), parts[0].strip() + ';')]
    for p in parts[1:]:
        m2 = re.match(r'\s*\**\s*(\w+)\s*\(', p)
        if m2: out.append((m2.group(1), m.group(1) + p.strip() + ';'))
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


INTS = set('s8 u8 s16 u16 s32 u32 s64 u64 int char short long unsigned signed M2C_UNK'.split())


def shape(name, decl):
    """(type text without the name, 'array' | 'scalar' | 'other')."""
    s = re.sub(r'^\s*extern\s+', '', strip(decl)).strip().rstrip(';')
    s = re.sub(r'\b(volatile)\b\s*', r'\1 ', s)
    if re.search(r'\b' + re.escape(name) + r'\s*\[', s): return s, 'array'
    if re.search(r'\*\s*(const\s+|volatile\s+)*' + re.escape(name) + r'\b', s): return s, 'scalar'
    words = set(re.findall(r'\w+', s)) - {name, 'volatile', 'const'}
    return s, ('scalar' if words and words <= INTS else 'other')


def view(name, decl, base, addr=False, sfx=None):
    """A view of D_X as this function declared it, given the first declaration
    `base`.  Scalars (pointers, integers) are cast by value and arrays by
    address, so the access stays a direct one: an access through `*(T *)&D_X`
    loses gcc 2.96's MEM_SCALAR_P and can reorder loads (session 49's trap).
    Anything else is `(*(T (*)) &D_X)`."""
    s, k = shape(name, decl)
    s0, k0 = shape(name, base)
    if sfx and not addr:
        # an `__asm__` alias with this function's type: the access is the old
        # file's own (session 52: cast views changed the address folding of
        # arrays, and an assignment through a value-cast view of a pointer
        # changed func_00151808)
        return 'extern %s __asm__("%s");\n#define %s %s_%s' % (sub(s, name, name + '_' + sfx), name, name, name, sfx)
    def wide(t):  # a 64-bit integer (a pointer has a '*')
        return '*' not in t and bool(re.search(r'\b(u64|s64|long\s+long)\b', t))
    vol = lambda t: bool(re.search(r'\bvolatile\b', t)) and '*' not in t  # a volatile scalar (session 52:
    # a value cast drops the volatile and reorders the accesses: view it in memory)
    if k == 'scalar' and k0 == 'scalar' and not addr and wide(s) == wide(s0) and vol(s) == vol(s0):  # (&D_X needs an lvalue;
        # a value cast of a 32-bit base to u64 would load 32 bits)
        return '#define %s ((%s) %s)' % (name, sub(s, name, ''), name)
    if k == 'array' and sfx:
        # an array: an `__asm__` alias with this function's type (session 52: a
        # cast view `((T *) D_X)` changed the address folding of D_00573F10,
        # D_00575528, D_00575328 and D_002E26A0)
        return 'extern %s __asm__("%s");\n#define %s %s_%s' % (sub(s, name, name + '_' + sfx), name, name, name, sfx)
    if k == 'array':
        el = re.sub(r'\[[^\]]*\]', '', sub(s, name, '(*)'), count=1)
        el = re.sub(r'\(\*\)\s*$', '*', el.strip()) if el.strip().endswith('(*)') else el
        return '#define %s ((%s) %s%s)' % (name, el, '' if k0 == 'array' else '&', name)
    return '#define %s (*(%s) &%s)' % (name, sub(s, name, '(*)'), name)


def sig(s):
    """'RET NAME(ARGS)...' -> (ret, [arg kinds]) with kinds f (float), d (double),
    n (a char or short: the caller truncates it), x."""
    s = no_attr(strip(s)).strip().rstrip(';').split('{')[0]
    m = re.match(r'(.*?)\b(\w+)\s*\((.*)\)\s*$', s, flags=re.S)
    if not m: return None
    ret = re.sub(r'\b(extern|static|inline|__inline__)\b', '', m.group(1)).split()
    ret = 'void' if ret == ['void'] else ('f' if ret and ret[-1] in ('f32', 'float') else ('d' if ret and ret[-1] in ('f64', 'double') else 'x'))
    args = [a.strip() for a in split_top(m.group(3))] if m.group(3).strip() not in ('', 'void') else []
    kinds = []
    for a in args:
        w = re.findall(r'\w+', a)
        if '*' in a or '[' in a or '(' in a: kinds.append('x')
        elif w and w[0] in ('f32', 'float'): kinds.append('f')
        elif w and w[0] in ('f64', 'double'): kinds.append('d')
        elif a == '...': kinds.append('...')
        elif w and w[0] in ('s8', 'u8', 's16', 'u16', 'char', 'short'): kinds.append('n')  # narrowed by the callee
        else: kinds.append('x')
    return ret, kinds


def risky(a, b):
    """two prototypes of one function that can compile differently: the return
    kind, the argument count or a float / double argument differs."""
    sa, sb = sig(a), sig(b)
    if not sa or not sb: return False
    if (sa[0] == 'void') != (sb[0] == 'void') and 'void' not in (sa[0], sb[0]): return True
    return sa[0] != sb[0] and 'void' not in (sa[0], sb[0]) or sa[1] != sb[1]


def unnamed(proto):
    """a prototype's text without parameter names, extern and spacing."""
    s = no_attr(strip(proto)).strip().rstrip(';')
    s = re.sub(r'^\s*(extern|static)\s+', '', s)
    m = re.match(r'(.*?\b\w+)\s*\((.*)\)\s*$', s, flags=re.S)
    if not m: return norm(s)
    args = []
    for a in split_top(m.group(2)):
        a = a.strip()
        if a in ('', 'void', '...'): args.append(a); continue
        a = re.sub(r'\(\s*\*+\s*\w+\s*\)', '(*)', a)  # function pointer names
        a = re.sub(r'\b\w+\s*((\[[^\]]*\]\s*)*)$', lambda x: x.group(1), a) \
            if len(re.findall(r'\w+', re.sub(r'\[[^\]]*\]', '', a))) > 1 and '(*)' not in a else a
        args.append(re.sub(r'\s+', ' ', a).replace(' *', '*').strip())
    return re.sub(r'\s+', ' ', m.group(1)).replace(' *', '*') + '(' + ','.join(args) + ')'


def defret(proto):
    """the return type text of a prototype."""
    s = no_attr(strip(proto)).strip()
    s = re.sub(r'^\s*(extern|static)\s+', '', s)
    m = re.match(r'(.*?)\b\w+\s*\(', s, flags=re.S)
    return m.group(1).strip() if m else 'int'


def called(name, body):
    """the body calls `name` (a function only taken by address, `&f`, needs no
    view: a cast view is not an lvalue; session 52)"""
    return re.search(r'\b' + re.escape(name) + r'\s*\(', strip(body)) is not None


def fview(name, proto):
    """call `name` through this prototype: #define NAME ((RET (*)(ARGS)) NAME)."""
    s = no_attr(strip(proto)).strip().rstrip(';')
    s = re.sub(r'^\s*extern\s+', '', s)
    parts, depth, cur = [], 0, ''
    for ch in s:  # `void f(), g();` declares several: keep the one of `name` (session 52)
        depth += (ch == '(') - (ch == ')')
        if ch == ',' and depth == 0: parts.append(cur); cur = ''
        else: cur += ch
    parts.append(cur)
    if len(parts) > 1:
        m = re.match(r'(.*?)\b\w+\s*\(', parts[0], flags=re.S)
        mine = [x for x in parts if re.search(r'\b' + re.escape(name) + r'\b', x)]
        s = (m.group(1) if m else 'int ') + (mine[0].strip() if mine else parts[0].strip())
        if mine and mine[0] is parts[0]: s = parts[0]
    return '#define %s ((%s) %s)' % (name, sub(s, name, '(*)'), name)


def main(out, funcs, onto=False):
    src = placements()
    files = {}
    for f in funcs:
        files.setdefault(src[f][1], citems(open(src[f][1]).read()))
    inmod = set(funcs)
    defhead = {}  # the module's own definitions: header text
    for f in funcs:
        for t, k, n in files[src[f][1]]:
            if k == 'func' and n == f: defhead[f] = strip(t).split('{')[0].strip() + ';'
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
                for x in names: scope.pop(x + '#def', None)
                continue
            if kind == 'include':
                incs.append((order, t.strip())); continue
            if kind == 'var':
                for nm, d in var_decls(t):
                    if nm in src and not nm.startswith('D_'):  # m2c's `extern M2C_UNK func_X;` (an address)
                        scope[nm] = (order, 'proto', '%s %s();' % (defret(defhead[nm]) if nm in defhead else 'void', nm))
                        continue
                    if not re.match(r'\s*(extern|static)\b', d) and '=' not in d:
                        d = 'extern ' + re.sub(r'\s+;', ';', no_attr(d).strip())  # a definition stays in its file: declare it
                    scope[nm] = (order, 'var', d)
                continue
            if kind == 'func':
                continue  # a real definition above: not copied (see the docstring)
            if kind == 'proto' and len(names) > 1:
                for nm, d in proto_decls(t): scope[nm] = (order, 'proto', d)
                continue
            for x in names:  # a macro has its own key: `#define D_X (*(T *)&D_X)` needs D_X's extern too
                scope[x + '#def' if kind == 'define' else x] = (order, kind, t.strip('\n'))
        if body is None:  # a macro-generated definition: MACRO(f, ...)
            order = 0; scope = {}
            for t, k, n in its:
                order += 1
                m = re.search(r'^[ \t]*(\w+)\(\s*' + f + r'\b.*\)[ \t]*$', t, flags=re.M)
                if m and k != 'func':
                    body = m.group(0).strip() + '\n'; break
                kind, names = classify(t, k, n)
                if kind == 'undef':
                    for x in names: scope.pop(x + '#def', None)
                elif kind == 'var':
                    for nm, d in var_decls(t): scope[nm] = (order, 'var', d)
                elif kind not in ('include', 'func', 'other'):
                    for x in names: scope[x + '#def' if kind == 'define' else x] = (order, kind, t.strip('\n'))
        assert body, (f, path)
        need, used = {}, idents(body)
        changed = True
        while changed:
            changed = False
            for x0 in list(used):
                for x in (x0, x0 + '#tag', x0 + '#asm', x0 + '#def'):
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

    # the base declaration of an extern the functions declare differently: an
    # array one if there is one (an access through an array view folds its
    # offset into the address differently), else the first
    arrays = {}
    for pl in plan:
        for nm, v in pl[3]:
            if v[1] == 'var' and shape(nm, v[2])[1] == 'array' and nm not in arrays: arrays[nm] = v[2]
    emitted = {}  # name -> (kind, norm text)
    emac = {}     # name -> the macro naming it when its declaration was emitted
    macros = {}   # active macro name -> norm text
    lines = ['/* TODO: what this module is (docs/modules.md). */']
    seen_inc = set()
    # every old file's includes go at the top (a header's typedef after a
    # local one of the same name would not compile); what they declare counts
    # as emitted, so a clashing local typedef is renamed and a clashing extern
    # viewed
    hdr_incs = []
    for pl in plan:
        for o, t in pl[4]:
            if t not in hdr_incs: hdr_incs.append(t)
    def seed(path, done):
        if path in done or not os.path.exists(path): return
        done.add(path)
        for t, k, n in citems(open(path).read()):
            kind, names = classify(t, k, n)
            if kind == 'include':
                m = re.search(r'#include\s+"([^"]+)"', t)
                if m: seed('include/' + m.group(1), done)
            elif kind == 'var':
                for nm, d in var_decls(t): emitted.setdefault(nm, ('var', norm(d), d))
            elif kind in ('typedef', 'tag', 'proto'):
                for x in names: emitted.setdefault(x, (kind, norm(t)))
            elif kind == 'define':
                for x in names: macros.setdefault(x, norm(t))
    done = set()
    if not onto:
        for t in hdr_incs:
            m = re.search(r'#include\s+"([^"]+)"', t)
            if m: seed('include/' + m.group(1), done)
        lines += hdr_incs
        seen_inc |= set(hdr_incs)
    if onto:  # append to an existing module: what it declares counts as emitted
        old = open(out).read()
        lines = [old.rstrip('\n')]
        for t, k, n in citems(old):
            kind, names = classify(t, k, n)
            if kind == 'include': seen_inc.add(t.strip())
            elif kind == 'undef':
                for x in names: macros.pop(x, None)
            elif kind == 'define':
                for x in names: macros[x] = norm(t)
            elif kind == 'var':
                for nm, d in var_decls(t): emitted.setdefault(nm, ('var', norm(d), d))
            elif kind in ('typedef', 'tag', 'inline', 'ctx', 'proto'):
                for x in names: emitted.setdefault(x, (kind, norm(t)))
            elif kind == 'func':
                emitted[n] = ('def', norm(t.split('{')[0]))
        for t in list(seen_inc):
            m = re.search(r'#include\s+"([^"]+)"', t)
            if m: seed('include/' + m.group(1), done)
        new = [x for x in hdr_incs if x not in seen_inc]
        for t in new:
            m = re.search(r'#include\s+"([^"]+)"', t)
            if m: seed('include/' + m.group(1), done)
        if new:  # after the module's first include
            ol = lines[0].split('\n')
            k = next((i for i, l in enumerate(ol) if l.startswith('#include')), 0)
            lines[0] = '\n'.join(ol[:k + 1] + new + ol[k + 1:])
        seen_inc |= set(new)
    trailing = []
    conflicts = []
    for idx, (f, addr, path, need, incs, body, tail_incs) in enumerate(plan):
        sec = ['', '/* %s (from %s). */' % (f, path.replace('src/', ''))]
        items = [(nm, v[1], v[2]) for nm, v in need]
        # renames for typedef / tag conflicts, to a fixed point
        ren = {}
        while True:
            def cur(t):
                for a, b in ren.items(): t = sub(t, a, b)
                return t
            new = False
            for nm, kind, t in items:
                if kind in ('typedef', 'tag', 'inline') and nm.split('#')[0] not in ren and nm in emitted \
                        and emitted[nm][1] != norm(cur(t)):
                    r = nm.split('#')[0]; ren[r] = '%s_%s' % (r, addr[-5:]); new = True
            if not new: break
        def cur(t):
            for a, b in ren.items(): t = sub(t, a, b)
            return t
        views = []
        mine = []
        owndefs = {nm.split('#')[0] for nm, kind, t in items if kind == 'define'}
        done_txt = set()
        for nm, kind, t in items:
            r = nm.split('#')[0]
            t2 = cur(t); n2 = ren.get(r, r) + nm[len(r):]
            r0 = n2.split('#')[0]
            if kind == 'asmvar':  # emitted as it is, once per text and rename macro
                key = '%s@%s@%s' % (n2, norm(t2), macros.get(r0))
                if emitted.get(key): continue
                emitted[key] = (kind, norm(t2)); sec.append(t2); continue
            if kind in ('typedef', 'tag', 'inline', 'ctx') and norm(t2) in done_txt:
                continue  # (a typedef needed by two of its names)
            if kind in ('typedef', 'tag', 'inline', 'ctx'):
                done_txt.add(norm(t2))
                # under this function's own `#define NAME NAME_<addr>` the
                # declaration names another identifier: emit it again
                if n2 in emitted and emitted[n2][1] == norm(t2) and emac.get(n2) == macros.get(r0): continue
                if r0 in macros and r0 not in mine: sec.append('#undef ' + r0); macros.pop(r0)
                emitted[n2] = (kind, norm(t2)); emac[n2] = macros.get(r0); sec.append(t2)
                if kind == 'typedef':  # its other names (a struct tag) are taken too
                    for x in classify(t2, 'decl', None)[1]:
                        if x not in emitted: emitted[x] = (kind, norm(t2)); emac[x] = macros.get(x.split('#')[0])
                continue
            if kind == 'var':
                if nm in macros and nm not in owndefs: sec.append('#undef ' + nm); macros.pop(nm)
                if nm not in emitted:
                    b = arrays.get(nm, t2)
                    known = all(x in emitted or x in KW or x == nm or x in INTS for x in idents(b))
                    if b != t2 and not known: b = t2
                    emitted[nm] = ('var', norm(b), b); sec.append(b)
                if emitted[nm][1] != norm(t2) and nm not in owndefs:  # (the function's own macro views it)
                    views.append(view(nm, t2, emitted[nm][2], re.search(r'&\s*' + nm + r'\b', strip(body)) is not None, f.split('_')[-1]))
                continue
            if kind == 'proto' and nm in inmod and emitted.get(nm, ('',))[0] in ('', 'proto', 'kr') \
                    and unnamed(t2) != unnamed(defhead[nm]):
                # a prototype of a function defined later in the module that
                # disagrees with its definition: declare it old-style (the
                # definition's return type when the declarations know it) and
                # view this function's prototype
                if nm not in emitted:
                    rt = defret(defhead[nm])
                    if not all(x in emitted or x in KW or x in INTS for x in idents(rt)): rt = defret(t2)
                    sec.append('%s %s();' % (rt, nm)); emitted[nm] = ('kr', '')
                if sig(t2) and sig(t2)[1]: views.append(fview(nm, t2)) if called(nm, body) else None
                continue
            if kind == 'proto':
                if nm in emitted:
                    if emitted[nm][1] != norm(t2):
                        if risky(emitted[nm][1], norm(t2)):
                            views.append(fview(nm, t2)) if called(nm, body) else None
                            conflicts.append('%s: %s  vs  %s (viewed)' % (f, norm(t2), emitted[nm][1]))
                        elif emitted[nm][0] != 'kr' and unnamed(emitted[nm][1]) != unnamed(t2) and sig(t2):
                            # other pointer types: the function's own types
                            # (a member of the result, a struct argument)
                            views.append(fview(nm, t2)) if called(nm, body) else None
                            conflicts.append('%s: %s  vs  %s (viewed)' % (f, norm(t2), emitted[nm][1]))
                        else:
                            conflicts.append('%s: %s  vs  %s' % (f, norm(t2), emitted[nm][1]))
                    continue
                emitted[nm] = ('proto', norm(t2)); sec.append(t2); continue
            if kind == 'define':
                nm = n2.split('#')[0]
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
            sec.append('#undef ' + re.search(r'^#define (\w+)', v, flags=re.M).group(1))
        nxt = {}  # the next later definition of each macro (kept if it is the same)
        for pl in plan[idx + 1:]:
            for nm, v in pl[3]:
                if v[1] == 'define' and nm.split('#')[0] not in nxt: nxt[nm.split('#')[0]] = norm(v[2])
        for nm in mine:
            if nxt.get(nm) != macros.get(nm):
                sec.append('#undef ' + nm); macros.pop(nm, None)
        lines += sec
        # an old file's trailing includes only checked its own declarations
        # against the shared headers; the module's may differ, so drop them
    lines.append('')
    lines += trailing
    open(out, 'w').write(re.sub(r'\n{3,}', '\n\n', '\n'.join(lines) + '\n'))
    for c in conflicts: print('CONFLICT', c)


if __name__ == '__main__':
    if len(sys.argv) < 3: sys.exit(__doc__)
    if sys.argv[1] == '--onto': main(sys.argv[2], sys.argv[3:], onto=True)
    else: main(sys.argv[1], sys.argv[2:])
