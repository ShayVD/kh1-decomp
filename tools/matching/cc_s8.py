# cc.py SRC OUTBASE [extra flags...]: compile SRC with its dir's flags into WDIR/d/OUTBASE.s (dumps next to it)
import os, sys, subprocess
from pathlib import Path
R = Path('/home/claude/kh1-decomp'); sys.path.insert(0, str(R/'tools'))
import kh1tool as K, autodecomp as A
A._init()
src = Path(sys.argv[1]).resolve(); out = Path(os.environ.get('WDIR', '/tmp/claude-0/s8/w9')) / 'd' / (sys.argv[2] + '.s')
fl = K.flags_for(A._cfg, str(src.relative_to(R)))
cc = K.TOOLCHAIN_DIR / fl.compiler / "bin" / "ee-gcc"
r = subprocess.run([str(cc), "-S", "-x", "c", *fl.cflags.split(), *fl.ccflags.split(), *sys.argv[3:], "-ffunction-sections", f"-I{R/'include'}", f"-I{src.parent}", "-o", str(out), str(src)], cwd=out.parent, capture_output=True, text=True)
print(r.stderr[-2000:])
