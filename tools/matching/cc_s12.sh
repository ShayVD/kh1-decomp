#!/bin/bash
# cc.sh src outdir : compile with dumps using the file's mode flags
cd /home/claude/kh1-decomp
FL=$(python3 -I -c "
import sys; sys.path.insert(0,'tools'); import kh1tool as K, autodecomp as A
A._init(); fl=K.flags_for(A._cfg, sys.argv[1]); print(fl.compiler, fl.cflags, fl.ccflags)" "${1#/home/claude/kh1-decomp/}")
set -- "$@"
COMP=${FL%% *}; REST=${FL#* }
cp "$1" "$2/x.c"
cd "$2" && /home/claude/kh1-decomp/tools/toolchain/$COMP/bin/ee-gcc -S -x c $REST -ffunction-sections -I/home/claude/kh1-decomp/include -I$(dirname $1) -da $EXTRA -o x.s x.c
