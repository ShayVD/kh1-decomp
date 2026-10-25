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
# The HUD's anchor table against the C (tools/host/hudcheck.py, session 93): every environment src/hud
# sends is an anchor or a marker, and a table missing one fails.
python3 -I "$ROOT/tools/host/hudcheck.py" > "$W/hud.log" || { cat "$W/hud.log"; exit 1; }
tail -n 1 "$W/hud.log"
sed '/D_00669070, -1/d' "$ROOT/host/port/hudanchor.c" > "$W/hudanchor_missing.c"
if python3 -I "$ROOT/tools/host/hudcheck.py" --table "$W/hudanchor_missing.c" > "$W/hud_missing.log"; then
  echo "selftest: hudcheck missed a HUD environment left out of the table" >&2; exit 1
fi
# session 94: a staging send under no environment fails (the minigame timer's send taken out)
mkdir -p "$W/hudneg/src" && cp -r "$ROOT/src/hud" "$W/hudneg/src/"
sed -i '/func_00237018(&D_00669070, 0x16, 1);/d' "$W/hudneg/src/hud/timer.c"
if python3 -I "$ROOT/tools/host/hudcheck.py" --src "$W/hudneg/src" > "$W/hud_neg.log" ||
   ! grep -q 'D_006691D4 .*follows no environment send' "$W/hud_neg.log"; then
  echo "selftest: hudcheck missed a staging send under no environment" >&2; cat "$W/hud_neg.log" >&2; exit 1
fi
# session 95: a staging send outside src/hud that OTHER_STAGES does not name fails (prim.c's buffer renamed)
mkdir -p "$W/hudneg2/src/gfx" && cp -r "$ROOT/src/hud" "$W/hudneg2/src/"
sed 's/D_00648070/D_00648080/g' "$ROOT/src/gfx/prim.c" > "$W/hudneg2/src/gfx/prim.c"
if python3 -I "$ROOT/tools/host/hudcheck.py" --src "$W/hudneg2/src" > "$W/hud_neg2.log" ||
   ! grep -q 'D_00648080 .*outside src/hud and OTHER_STAGES does not name it' "$W/hud_neg2.log"; then
  echo "selftest: hudcheck missed a staging send outside src/hud" >&2; cat "$W/hud_neg2.log" >&2; exit 1
fi
# The host's DMA chain walk (host/null/dmawalk.c) on made-up chains, when gcc -m32 works.
if gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/dmawalk_test" \
     "$ROOT/tests/host/dmawalk_test.c" "$ROOT/host/null/dmawalk.c" "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c" "$ROOT/host/port/canvas.c" 2> "$W/dmawalk_cc.log"; then
  "$W/dmawalk_test" > "$W/dmawalk.log" || { grep -v '^kh1-host:   ' "$W/dmawalk.log"; exit 1; }
  tail -n 1 "$W/dmawalk.log"
  # the GS register file it feeds (host/null/gsregs.c, session 79)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/gsregs_test" \
      "$ROOT/tests/host/gsregs_test.c" "$ROOT/host/null/dmawalk.c" "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c" "$ROOT/host/port/canvas.c"
  "$W/gsregs_test" > "$W/gsregs.log" || { grep -v '^kh1-host:' "$W/gsregs.log"; exit 1; }
  tail -n 1 "$W/gsregs.log"
  # the GS memory it feeds (host/null/gsmem.c, session 80)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/gsmem_test" \
      "$ROOT/tests/host/gsmem_test.c" "$ROOT/host/null/dmawalk.c" "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c" "$ROOT/host/port/canvas.c"
  "$W/gsmem_test" > "$W/gsmem.log" || { grep -v '^kh1-host:' "$W/gsmem.log"; exit 1; }
  tail -n 1 "$W/gsmem.log"
  # the 2D canvas map and the full-screen rules (host/port/canvas.c, session 93)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/canvas_test" \
      "$ROOT/tests/host/canvas_test.c" "$ROOT/host/port/canvas.c" "$ROOT/host/port/view.c"
  "$W/canvas_test" > "$W/canvas.log" || { cat "$W/canvas.log"; exit 1; }
  tail -n 1 "$W/canvas.log"
  # the host "present" (host/null/present.c, KH1_HOST_SHOT, session 94)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/present_test" \
      "$ROOT/tests/host/present_test.c" "$ROOT/host/null/present.c" "$ROOT/host/null/dmawalk.c" \
      "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c" "$ROOT/host/port/canvas.c"
  "$W/present_test" "$W" > "$W/present.log" || { grep -v '^kh1-host:' "$W/present.log"; exit 1; }
  tail -n 1 "$W/present.log"
  # the null sound server (host/null/sound.c, session 86)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/sound_test" \
      "$ROOT/tests/host/sound_test.c" "$ROOT/host/null/sound.c"
  "$W/sound_test" > "$W/sound.log" || { cat "$W/sound.log"; exit 1; }
  tail -n 1 "$W/sound.log"
  # the null pad and its script (host/null/pad.c, session 87)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/pad_test" \
      "$ROOT/tests/host/pad_test.c" "$ROOT/host/null/pad.c"
  "$W/pad_test" "$W" > "$W/pad.log" 2>&1 || { cat "$W/pad.log"; exit 1; }
  tail -n 1 "$W/pad.log"
  # the camera matrices' C twin (host/port/view.c) against the original's func_00110618
  # (tools/host/viewcheck.py, session 91), only with the user's own ELF in the repo root
  ELF="$ROOT/$(cd "$ROOT" && python3 tools/kh1tool.py config target.elf)"
  if [[ -f "$ELF" ]]; then
    python3 -I "$ROOT/tools/host/viewcheck.py" --elf "$ELF" --round nearest > "$W/view.log" || { cat "$W/view.log"; exit 1; }
    grep -q 'worst 0 ulp$' "$W/view.log" || { echo "selftest: view.c is not bit-identical to func_00110618" >&2; cat "$W/view.log"; exit 1; }
    tail -n 1 "$W/view.log"
  else
    echo "selftest: no $(basename "$ELF"), viewcheck skipped"
  fi
else
  echo "selftest: no gcc -m32, dmawalk_test skipped"
fi
echo "selftest: PASS"
