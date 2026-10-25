#!/usr/bin/env bash
# End-to-end test of the build tools on a synthetic ELF (no game data needed):
# builds a fake "original" with the configured compiler, decompiles two of its
# functions in src/, and checks that the pipeline reports MATCH for correct
# code and NONMATCHING for wrong code.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
HERE="$ROOT/tests/selftest"
COMPILER="$(python3 "$ROOT/tools/kh1tool.py" config toolchain.compiler)"
CC="$ROOT/tools/toolchain/$COMPILER/bin/ee-gcc"
[[ -x "$CC" ]] || { echo "selftest: $COMPILER not installed; run make toolchain" >&2; exit 1; }

W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
mkdir -p "$W/tools" "$W/src" "$W/docs"
cp "$ROOT"/Makefile "$ROOT"/kh1.ld "$W/"
cp "$ROOT"/tools/*.py "$W/tools/"
ln -s "$ROOT/tools/toolchain" "$W/tools/toolchain"
mkdir -p "$W/include"

"$CC" -c -O2 -G0 -o "$W/fake.o" "$HERE/fake_game.c"
python3 "$ROOT/tools/kh1tool.py" fix-obj "$W/fake.o"
mips-linux-gnu-ld -EL --no-warn-mismatch -T "$HERE/fake.ld" -o "$W/FAKE_000.00" "$W/fake.o"

addr() { mips-linux-gnu-nm "$W/FAKE_000.00" | awk -v s="$1" '$3==s {print $1}'; }
cat > "$W/kh1.toml" <<TOML
[target]
elf = "FAKE_000.00"
sha256 = "$(sha256sum "$W/FAKE_000.00" | cut -d' ' -f1)"
[toolchain]
compiler = "$COMPILER"
cflags = "-O2 -G0"
asflags = "-G0 -march=r5900 -EL"
[[segment]]
name = "fake"
start = "0x00100000"
end = "0x00200000"
TOML
printf 'AddCounter\t%s\nD_g_counter\t%s\n' "$(addr AddCounter)" "$(addr g_counter)" > "$W/functions.tsv"
# The fake game's GetHp must be at 0x00100000 for src/obj.c's placeholder name.
[[ "$(addr GetHp)" == "00100000" ]] || { echo "selftest: unexpected layout" >&2; exit 1; }

cd "$W"
make --no-print-directory check
make --no-print-directory layout
[[ $(grep -c '^0010' layout.tsv) -eq 7 ]] || { echo "selftest: expected 7 functions"; cat layout.tsv; exit 1; }

make --no-print-directory rank ARGS="--segment all" | tee rank.log
grep -q 'getter' rank.log

# Heal + Clear are correct: expect a byte-identical build. Heal also covers a
# jal to an undecompiled placeholder and a jal to a registry symbol.
cp "$HERE/src/obj.c" src/
sed -i "s/^\(\(00100000\|[0-9a-f]*\)\t[0-9a-f]*\t[0-9]*\t\)func_$(addr Heal)$/\1Heal/" layout.tsv
printf 'Heal\t%s\nClear\t%s\n' "$(addr Heal)" "$(addr Clear)" >> functions.tsv
make --no-print-directory verify | tee verify1.log
grep -q '^OK:' verify1.log

# Kind (jump table) + Name (string literals): rodata must be placed at the
# original addresses, inferred from the code's %hi/%lo pairs.
cp "$HERE/src/rodata.c" src/
printf 'Kind\t%s\nName\t%s\n' "$(addr Kind)" "$(addr Name)" >> functions.tsv
make --no-print-directory verify | tee verify1b.log
grep -q '^OK:' verify1b.log
[[ $(tail -n +2 out/gen/rodata.tsv | wc -l) -eq 2 ]] || { echo "selftest: expected 2 rodata blocks"; cat out/gen/rodata.tsv; exit 1; }
# A wrong string must be caught as a rodata mismatch.
sed 's/"beta"/"betA"/' "$HERE/src/rodata.c" > src/rodata.c
if make --no-print-directory verify > verify1c.log 2>&1; then
  echo "selftest: wrong rodata was not detected" >&2; cat verify1c.log; exit 1
fi
grep -q 'RODATA MISMATCH' verify1c.log
cp "$HERE/src/rodata.c" src/

# A wrong AddCounter must be caught.
cp "$HERE/src/counter.c" src/
if make --no-print-directory verify > verify2.log 2>&1; then
  echo "selftest: wrong code was not detected" >&2; cat verify2.log; exit 1
fi
grep -q "NONMATCHING 0x$(addr AddCounter) AddCounter" verify2.log

make --no-print-directory report | tee report.log
grep -q '100.00%  src/obj.c  Heal' report.log
grep -q 'src/counter.c  AddCounter' report.log
! grep -q '100.00%  src/counter.c  AddCounter' report.log
make --no-print-directory progress | tee progress.log
grep -q 'Functions matched: 4/7' progress.log
# The host's DMA chain walk (host/null/dmawalk.c) on made-up chains, when gcc -m32 works.
if gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/dmawalk_test" \
     "$ROOT/tests/host/dmawalk_test.c" "$ROOT/host/null/dmawalk.c" "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c" 2> "$W/dmawalk_cc.log"; then
  "$W/dmawalk_test" > "$W/dmawalk.log" || { grep -v '^kh1-host:   ' "$W/dmawalk.log"; exit 1; }
  tail -n 1 "$W/dmawalk.log"
  # the GS register file it feeds (host/null/gsregs.c, session 79)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/gsregs_test" \
      "$ROOT/tests/host/gsregs_test.c" "$ROOT/host/null/dmawalk.c" "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c"
  "$W/gsregs_test" > "$W/gsregs.log" || { grep -v '^kh1-host:' "$W/gsregs.log"; exit 1; }
  tail -n 1 "$W/gsregs.log"
  # the GS memory it feeds (host/null/gsmem.c, session 80)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/gsmem_test" \
      "$ROOT/tests/host/gsmem_test.c" "$ROOT/host/null/dmawalk.c" "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c"
  "$W/gsmem_test" > "$W/gsmem.log" || { grep -v '^kh1-host:' "$W/gsmem.log"; exit 1; }
  tail -n 1 "$W/gsmem.log"
  # the null sound server (host/null/sound.c, session 86)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/sound_test" \
      "$ROOT/tests/host/sound_test.c" "$ROOT/host/null/sound.c"
  "$W/sound_test" > "$W/sound.log" || { cat "$W/sound.log"; exit 1; }
  tail -n 1 "$W/sound.log"
else
  echo "selftest: no gcc -m32, dmawalk_test skipped"
fi
echo "selftest: PASS"
