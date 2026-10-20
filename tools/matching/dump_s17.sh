#!/bin/bash
# dump_s17.sh FILE OUTDIR [extra flags]: compile FILE with ee-gcc 2.96 -O2 -G0 (+extra) and all RTL dumps (-da) into OUTDIR
R=$(cd "$(dirname "$0")/../.." && pwd)
F=$(readlink -f "$1"); O=$2; shift 2
mkdir -p "$O" && cp "$F" "$O/x.c" && cd "$O" && rm -f x.c.* && "$R/tools/toolchain/ee-gcc2.96/bin/ee-gcc" -S -x c -O2 -G0 "$@" -ffunction-sections -I"$R/include" -I"$(dirname "$F")" -da -o x.s x.c
