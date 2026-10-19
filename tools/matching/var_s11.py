# var.py BASE FUNC MODE 'old1=>new1' ... : apply each replacement set (separated by ;;) and score
import sys, io, contextlib
sys.path.insert(0, '/home/claude/kh1-decomp/tools/matching')
import lchk_s10 as L
base, fn, mode = sys.argv[1], sys.argv[2], sys.argv[3]
F = '/home/claude/kh1-decomp/src/%s/.s11w21_var.c' % mode
s0 = open(base).read()
for spec in sys.argv[4:]:
    s = s0; ok = True
    for rep in spec.split(' | '):
        o, n = rep.split('=>')
        o = o.replace('\\n', '\n'); n = n.replace('\\n', '\n')
        cnt = 1
        if o.startswith('@'):
            k, o = o[1:].split('@', 1); k = int(k)
            idx = -1
            for _ in range(k): idx = s.index(o, idx + 1)
            s = s[:idx] + n + s[idx + len(o):]; continue
        if o not in s: print('MISSING', o); ok = False; break
        s = s.replace(o, n, 1)
    if not ok: continue
    open(F, 'w').write(s)
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf): r = L.check(F, fn)
    print(r[fn] if r else buf.getvalue()[-300:], spec[:150], flush=True)
