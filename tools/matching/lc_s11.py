# lc.py [-e flags] SRC [ONLY]: LCS words; uses lchkro if RO env set
import os, sys
sys.path.insert(0, '/home/claude/kh1-decomp/tools/matching')
args = sys.argv[1:]; ex = []
if args and args[0] == '-e': ex = args[1].split(); args = args[2:]
if os.environ.get('RO'):
    import tempfile, shutil
    _d = tempfile.mkdtemp(prefix='s11w2ro_'); import atexit; atexit.register(shutil.rmtree, _d, True)
    import lchkro_s10 as L
    L.tempfile.mkdtemp = lambda *a, **k: _d
else: import lchk_s10 as L
L.extra = ex
r = L.check(args[0], args[1] if len(args) > 1 else None)
if r:
    for k, v in r.items(): print(k, v)
