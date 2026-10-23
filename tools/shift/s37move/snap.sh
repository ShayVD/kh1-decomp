#!/bin/bash
# snap.sh DIR: save the m12 float build's fingerprints into DIR (used by fcheck.sh)
D=$1; mkdir -p $D
E=out/shift/m12-float/kh1-shift.elf
cp out/shift/m12-float/float_covered.txt out/shift/m12-float/float_reach.txt $D/
mips-linux-gnu-readelf -lW $E | grep LOAD > $D/phdr.txt
python3 - $E > $D/loadhash.txt <<'PY'
import sys
d=open(sys.argv[1],'rb').read()
import struct
phoff=struct.unpack_from('<I',d,28)[0];n=struct.unpack_from('<H',d,44)[0]
import hashlib
for i in range(n):
    t,off,va,pa,fs,ms,fl,al=struct.unpack_from('<8I',d,phoff+32*i)
    if t==1: print(hex(va),hex(fs),hex(ms),hashlib.sha256(d[off:off+fs]).hexdigest())
PY
mips-linux-gnu-nm $E | sort > $D/syms.txt
