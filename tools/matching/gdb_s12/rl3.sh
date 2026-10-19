#!/bin/bash
cd /tmp/claude-0/s12/s12w4/dumps; cp $1 la_in.c
gdb -q -batch -x ../bin/rl3.gdb --args /home/claude/kh1-decomp/tools/toolchain/ee-gcc2.96/lib/gcc-lib/ee/2.96-ee-001003-1/cc1 -lang-c -I/home/claude/kh1-decomp/include -D__GNUC__=2 -D__GNUC_MINOR__=96 -Dmips -DMIPSEL -DR5900 -D_mips -D__mips__ -D__mips=3 -D__mips64 -D__mips_eabi -D__mips_single_float la_in.c -G0 -quiet -dumpbase la_in.c -O2 -ffunction-sections -o /dev/null 2>&1 | grep "^uid\|^at"
