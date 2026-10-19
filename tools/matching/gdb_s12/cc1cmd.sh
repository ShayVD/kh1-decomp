#!/bin/bash
# prints cc1 command for hand mode on file $1
cd /tmp/claude-0/s12/s12w4/dumps
python3 -I - "$1" <<'PY'
import sys, subprocess
sys.path.insert(0, '/home/claude/kh1-decomp/tools'); import kh1tool as K
cfg = K.load_config(); fl = K.flags_for(cfg, 'src/hand/x.c')
cc = K.TOOLCHAIN_DIR / fl.compiler / 'bin' / 'ee-gcc'
r = subprocess.run([str(cc), '-v', '-S', '-x', 'c', *fl.cflags.split(), *fl.ccflags.split(), '-ffunction-sections', '-I/home/claude/kh1-decomp/include', '-o', '/dev/null', sys.argv[1]], capture_output=True, text=True)
for l in r.stderr.splitlines():
    if 'cc1' in l and not l.startswith('Reading') : print(l)
PY
