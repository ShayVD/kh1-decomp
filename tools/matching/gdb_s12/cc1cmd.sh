#!/bin/bash
H=$(cd "$(dirname "$0")" && pwd)  # usage: pass an absolute path to the C file
# prints cc1 command for hand mode on file $1
D=${GDBS12_DIR:-/tmp/gdb_s12}; mkdir -p $D; cd $D
python3 -I - "$1" <<'PY'
import sys, subprocess
sys.path.insert(0, '/home/claude/kh1-decomp/tools'); import kh1tool as K
cfg = K.load_config(); fl = K.flags_for(cfg, 'src/hand/x.c')
cc = K.TOOLCHAIN_DIR / fl.compiler / 'bin' / 'ee-gcc'
r = subprocess.run([str(cc), '-v', '-S', '-x', 'c', *fl.cflags.split(), *fl.ccflags.split(), '-ffunction-sections', '-I/home/claude/kh1-decomp/include', '-o', '/dev/null', sys.argv[1]], capture_output=True, text=True)
for l in r.stderr.splitlines():
    if 'cc1' in l and not l.startswith('Reading') : print(l)
PY
