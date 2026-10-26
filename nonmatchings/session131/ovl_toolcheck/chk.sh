#!/bin/bash
# chk.sh file.c [extra cflags]: link each ovl_ function at its address, compare with dktitle.x bytes
# (out/overlays/dktitle.x and out/ovl/dktitle.layout.tsv from tools/ovl/inventory.py; the user's file, never committed)
set -e
R=$(git rev-parse --show-toplevel)
f=$(realpath $1); shift
cd "$(mktemp -d)"
$R/tools/toolchain/ee-gcc2.96/bin/ee-gcc -c -O2 -G0 -ffunction-sections "$@" $f -o c.o
python3 $R/tools/kh1tool.py fix-obj c.o >/dev/null
funcs=$(mips-linux-gnu-nm c.o | awk '$2=="T"{print $3}' | grep ^ovl_)
{ echo "SECTIONS {"; for fn in $funcs; do echo "  .$fn 0x${fn#ovl_} : { *(.text.$fn) }"; done; echo "  /DISCARD/ : { *(.reginfo) *(.mdebug*) *(.comment) *(.pdr) }"; echo "}"; } > l.ld
mips-linux-gnu-ld -EL -o c.elf -T l.ld c.o --defsym D_00F2C6F0=0xf2c6f0 --defsym D_00F2C6F4=0xf2c6f4 --defsym D_00F2C8A0=0xf2c8a0 --defsym D_002C5AD8=0x2c5ad8 --defsym D_009A0000=0x9a0000 --defsym ovl_00f206c8=0xf206c8 --noinhibit-exec 2>/dev/null
for fn in $funcs; do a=$((0x${fn#ovl_})); n=$(awk -v A="00${fn#ovl_00}" '$1==A{print $3}' $R/out/ovl/dktitle.layout.tsv)
  mips-linux-gnu-objcopy -O binary -j .$fn c.elf o.bin
  m=$(stat -c%s o.bin); head -c $n /dev/zero > z.bin; cp z.bin p.bin; dd if=o.bin of=p.bin conv=notrunc status=none; ours=$(head -c $n p.bin | sha1sum | cut -c1-8); orig=$(tail -c +$((a-0xf20000+1)) $R/out/overlays/dktitle.x | head -c $n | sha1sum | cut -c1-8)
  [ "$ours" = "$orig" ] && echo "MATCH $fn ($n)" || echo "diff  $fn ($n, ours $(stat -c%s o.bin))"; done
