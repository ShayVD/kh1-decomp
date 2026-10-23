"""Declarations of module functions in other files that differ from the module
header (session 33).

  python3 -I tools/shift/s33types/s33_protodiff.py [--all] [--defs]

Functions defined in src/vm, src/camera and src/msgwin; prototypes in
include/vm, include/camera and include/msgwin.  For every other src/ .c file,
prints each one-line declaration (file scope or block scope) whose normalized
type (parameter names dropped, arrays as pointers, `()` as <noproto>) differs
from the header's.  --all also prints the ones that agree; --defs also prints
declarations of module functions the headers do not declare.  Text only:
compile to check (s29_asmdiff, s31_warndiff, make)."""
import os, re, sys, glob

MODS = ['vm', 'camera', 'msgwin']
KW = {'int', 'char', 'short', 'long', 'unsigned', 'signed', 'float', 'double',
      'void', 'const', 'volatile'}
FN = r'(func_[0-9a-f]{8})'
DECL = re.compile(r'^(\s*)((?:extern\s+|static\s+)?[A-Za-z_][\w\s\*]*?)\b' + FN +
                  r'\s*\(([^;{}]*)\)\s*(?:__attribute__\s*\(\(.*\)\))?\s*;')

def strip_comments(t):
    t = re.sub(r'/\*.*?\*/', lambda m: '\n' * m.group(0).count('\n'), t, flags=re.S)
    return re.sub(r'//[^\n]*', '', t)

def norm_param(p):
    p = p.strip()
    if p == '...':
        return p
    if '(' in p:      # function pointer: drop the name inside (*name)
        return re.sub(r'\(\s*\*\s*\w+\s*\)', '(*)', re.sub(r'\s+', '', p))
    arr = p.count('[')
    p = re.sub(r'\[[^\]]*\]', '', p)
    toks = re.findall(r'[A-Za-z_]\w*|\*', p)
    if len(toks) >= 2 and toks[-1] != '*' and toks[-1] not in KW and \
            toks[-2] not in ('struct', 'union', 'enum'):
        toks = toks[:-1]
    s = ' '.join(toks).replace(' *', '*') + '*' * arr
    return s

def norm(ret, params):
    ret = re.sub(r'\b(extern|static)\b', '', ret)
    ret = ' '.join(re.findall(r'[A-Za-z_]\w*|\*', ret)).replace(' *', '*')
    params = params.strip()
    if params == '':
        ps = '<noproto>'
    elif params == 'void':
        ps = 'void'
    else:
        depth, cur, out = 0, '', []
        for ch in params:
            if ch == ',' and depth == 0:
                out.append(cur); cur = ''
                continue
            depth += ch == '('
            depth -= ch == ')'
            cur += ch
        out.append(cur)
        ps = ', '.join(norm_param(x) for x in out)
    return '%s(%s)' % (ret, ps)

def decls(path):
    t = strip_comments(open(path, errors='replace').read())
    lines = t.split('\n')
    res = []
    # join multi-line declarations: simple approach, scan statement-wise
    for i, l in enumerate(lines):
        m = DECL.match(l)
        if not m:
            continue
        ind, ret, name, params = m.groups()
        if re.search(r'\breturn\b|=', ret) or ret.strip() == '':
            continue
        res.append((i + 1, 'local' if ind else 'file', name, norm(ret, params), l.strip()))
    return res

def main():
    show_all = '--all' in sys.argv
    hdr = {}
    for d in MODS:
        for h in glob.glob('include/%s/*.h' % d):
            for ln, sc, name, sig, raw in decls(h):
                hdr[name] = (h, sig)
    defined = {}
    for d in MODS:
        for f in glob.glob('src/%s/*.c' % d):
            t = strip_comments(open(f, errors='replace').read())
            for m in re.finditer(r'^[A-Za-z_][^;\n]*\b' + FN + r'\s*\([^;]*?\)\s*\{', t, re.M):
                defined[m.group(1)] = f
    found = []
    for f in sorted(glob.glob('src/**/*.c', recursive=True)):
        if any(f.startswith('src/%s/' % d) for d in MODS):
            continue
        for ln, sc, name, sig, raw in decls(f):
            if name not in defined:
                continue
            if name in hdr:
                h, hs = hdr[name]
                if sig != hs or show_all:
                    found.append((f, ln, sc, name, sig, hs, h))
            elif '--defs' in sys.argv:
                found.append((f, ln, sc, name, sig, '<no header>', defined[name]))
    files = {}
    for f, ln, sc, name, sig, hs, h in found:
        files.setdefault(f, []).append((ln, sc, name, sig, hs, h))
    for f in sorted(files):
        print(f)
        for ln, sc, name, sig, hs, h in files[f]:
            print('  %5d %-5s %s  %s   [hdr %s %s]' % (ln, sc, name, sig, hs, os.path.basename(h)))
    print('# %d declarations in %d files' % (len(found), len(files)), file=sys.stderr)

main()
