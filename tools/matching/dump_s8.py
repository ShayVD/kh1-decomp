# dump.py SRC [extra flags...]: compile SRC with its dir's flags plus extras, dumps in WDIR/d/
import os, sys, subprocess, shutil
from pathlib import Path
ROOT = Path('/home/claude/kh1-decomp'); sys.path.insert(0, str(ROOT/'tools'))
import kh1tool as K, autodecomp as A
A._init(); src = Path(sys.argv[1]).resolve()
fl = K.flags_for(A._cfg, str(src.relative_to(ROOT)))
cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
d = Path(os.environ.get('WDIR', '/tmp/claude-0/s8/w7')) / 'd'; shutil.rmtree(d, ignore_errors=True); d.mkdir()
shutil.copy(src, d/'x.c')
r = subprocess.run([str(cc), "-S", "-x", "c", *fl.cflags.split(), *fl.ccflags.split(), *sys.argv[2:], "-ffunction-sections", f"-I{ROOT/'include'}", f"-I{src.parent}", "-o", "x.s", "x.c"], cwd=d, capture_output=True, text=True)
print(r.stderr[-2000:]); print(' '.join(fl.cflags.split()+fl.ccflags.split()))
