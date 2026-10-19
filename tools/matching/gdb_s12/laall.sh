#!/bin/bash
H=$(cd "$(dirname "$0")" && pwd)  # usage: pass an absolute path to the C file
# laall.sh FILE BLOCK [extra cc1 flags]
D=${GDBS12_DIR:-/tmp/gdb_s12}; mkdir -p $D; cd $D; cp $1 la_in.c; sed "s/BLK/$2/" "$H"/laall.gdb > la_cur.gdb
CC1=/home/claude/kh1-decomp/tools/toolchain/ee-gcc2.96/lib/gcc-lib/ee/2.96-ee-001003-1/cc1
gdb -q -batch -x la_cur.gdb --args $CC1 -lang-c -I/home/claude/kh1-decomp/include -D__GNUC__=2 -D__GNUC_MINOR__=96 -Dmips -DMIPSEL -DR5900 -D_mips -D__mips__ -D__mips=3 -D__mips64 -D__mips_eabi -D__mips_single_float la_in.c -G0 -quiet -dumpbase la_in.c -O2 -ffunction-sections $3 -o /dev/null 2>&1 | grep "^q\|^\\$"
