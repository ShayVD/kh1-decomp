#!/bin/bash
# ga.sh FILE.c : global-alloc trace (last GA_BEGIN group = last function); then reg_renumber from greg dump
R=/home/claude/kh1-decomp; T=$R/tools/toolchain/ee-gcc2.96
cd $R
timeout 300 gdb -batch -x /tmp/claude-0/s13/s13w3/gdb/cj.py --args $T/lib/gcc-lib/ee/2.96-ee-001003-1/cc1 -lang-c -Iinclude -D__GNUC__=2 -D__GNUC_MINOR__=96 -D__GNUC_PATCHLEVEL__=0 -Dmips -DMIPSEL -DR5900 -D_mips -D_MIPSEL -D_R5900 -D__ee__ -D__mips__ -D__MIPSEL__ -D__R5900__ -D__mips -D__MIPSEL -D__R5900 -D__OPTIMIZE__ -D__LANGUAGE_C -D_LANGUAGE_C -DLANGUAGE_C "-D__SIZE_TYPE__=unsigned int" "-D__PTRDIFF_TYPE__=int" -D__LONG_MAX__=9223372036854775807L -U__mips -D__mips=3 -D__mips64 -D__mips_eabi -D__mips_single_float $1 -G0 -quiet -O2 -ffunction-sections $EXTRA -o /dev/null 2>&1 | grep "^CJ" | awk '/CJ_BEGIN/{buf=""} {buf=buf $0 "\n"} END{printf "%s", buf}'
