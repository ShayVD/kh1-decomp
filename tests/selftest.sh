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
[[ $(grep -c '^0010' layout.tsv) -eq 5 ]] || { echo "selftest: expected 5 functions"; cat layout.tsv; exit 1; }

# Heal + Clear are correct: expect a byte-identical build. Heal also covers a
# jal to an undecompiled placeholder and a jal to a registry symbol.
cp "$HERE/src/obj.c" src/
sed -i "s/^\(\(00100000\|[0-9a-f]*\)\t[0-9a-f]*\t[0-9]*\t\)func_$(addr Heal)$/\1Heal/" layout.tsv
printf 'Heal\t%s\nClear\t%s\n' "$(addr Heal)" "$(addr Clear)" >> functions.tsv
make --no-print-directory verify | tee verify1.log
grep -q '^OK:' verify1.log

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
grep -q 'Functions matched: 2/5' progress.log
echo "selftest: PASS"
