#!/bin/bash
# The float check of a module move (phase 4, session 37; docs/modules.md "Session 37").
#   tools/shift/s37move/fcheck.sh base    before the move (after a plain `make shift` and
#                                         tools/shift/data_owners.py in a fresh tree)
#   tools/shift/s37move/fcheck.sh NAME    after each chunk: builds the m12 float ELF with no
#                                         overlays and compares float_covered.txt, float_reach.txt,
#                                         the loaded bytes and the symbols with base.
S=${S:-out/s37check}
cd "$(dirname "$0")/../../.."
mkdir -p $S/emptyovl
make shift SHIFT_MODE=m12 SHIFT_FLOAT=1 SHIFT_OVERLAYS=$S/emptyovl -j4 > $S/float_$1.log 2>&1 || { echo BUILD FAIL; tail $S/float_$1.log; exit 1; }
grep 'M12-FLOAT OK' $S/float_$1.log | head -1 | cut -c1-60
tools/shift/s37move/snap.sh $S/$1
[ "$1" = base ] && exit 0
for f in float_covered.txt float_reach.txt loadhash.txt phdr.txt; do cmp -s $S/base/$f $S/$1/$f && echo "same $f" || echo "DIFF $f"; done
diff <(awk '{print $1,$3}' $S/base/syms.txt) <(awk '{print $1,$3}' $S/$1/syms.txt) | head -5
