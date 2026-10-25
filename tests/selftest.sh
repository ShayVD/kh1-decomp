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
# session 112: a long literal shifted by 32 or more (32-bit on the host) fails tools/host/longcheck.py
# (and, when gcc -m32 works, a 32-bit variable shifted so: gcc's shift-count warning)
LONGCC=(); echo 'int x;' > "$W/m32.c"; gcc -m32 -fsyntax-only "$W/m32.c" 2> /dev/null && LONGCC=(--cc gcc)
python3 -I "$ROOT/tools/host/longcheck.py" "${LONGCC[@]}" > "$W/long.log" || { cat "$W/long.log"; exit 1; }
tail -n 1 "$W/long.log"
mkdir -p "$W/longneg/obj" && sed 's/1ULL << 61;/1UL << 61;/' "$ROOT/src/obj/objdraw.nostrict.c" > "$W/longneg/obj/objdraw.nostrict.c"
if python3 -I "$ROOT/tools/host/longcheck.py" --src "$W/longneg" > "$W/long_neg.log" ||
   ! grep -q 'objdraw.nostrict.c:98: 1UL << 61' "$W/long_neg.log"; then
  echo "selftest: longcheck missed 1UL << 61" >&2; cat "$W/long_neg.log" >&2; exit 1
fi
# session 113: sizeof(long) (8 on the EE, 4 on the host) fails too
mkdir -p "$W/longneg2" && echo 'int f(void) { return sizeof(long); }' > "$W/longneg2/f.c"
if python3 -I "$ROOT/tools/host/longcheck.py" --src "$W/longneg2" > "$W/long_neg2.log" ||
   ! grep -q 'f.c:1: sizeof(long)' "$W/long_neg2.log"; then
  echo "selftest: longcheck missed sizeof(long)" >&2; cat "$W/long_neg2.log" >&2; exit 1
fi
# session 113: the CLUTs the windows' and text's packets read, from the C (tools/host/clutcheck.py); a window
# part whose palette 4 is read after its TEX2's CLD 2 load is taken away fails
python3 -I "$ROOT/tools/host/clutcheck.py" > "$W/clut.log" || { cat "$W/clut.log"; exit 1; }
tail -n 1 "$W/clut.log"
mkdir -p "$W/clutneg/src" && cp -r "$ROOT/src/text" "$W/clutneg/src/"
sed -i 's/p\[6\] = 0x4007bf8001300000;/p[6] = 0x0007bf8001300000;/' "$W/clutneg/src/text/winpart.nostrict.c"
if python3 -I "$ROOT/tools/host/clutcheck.py" --src "$W/clutneg/src" > "$W/clut_neg.log" ||
   ! grep -q 'func_00202300 .*reads the CLUT 0x3DFC (CSA 4)' "$W/clut_neg.log"; then
  echo "selftest: clutcheck missed a window part's CLUT load taken away" >&2; cat "$W/clut_neg.log" >&2; exit 1
fi
# session 114: the HUD's TEX0 pair whose first word no longer loads (CLD 0), and a timer TEX0 stored into a word
# DESCRIPTORS does not list, and a field-text glyph TEX0 whose CLD 1 is taken away, fail
mkdir -p "$W/clutneg2/src" && cp -r "$ROOT/src/hud" "$ROOT/src/text" "$W/clutneg2/src/"
sed -i 's/case 0: \*p = (u64)tbp << 37 | 0x2000000665423600;/case 0: *p = (u64)tbp << 37 | 0x0000000665423600;/' "$W/clutneg2/src/text/fldtext.c"
sed -i 's/t->f61 = 1;/t->f61 = 0;/' "$W/clutneg2/src/hud/ui.c"
sed -i 's/D_00669338 = 0x0607400621413600;/D_00669340 = 0x0607400621413600;/' "$W/clutneg2/src/hud/timer.nostrict.c"
if python3 -I "$ROOT/tools/host/clutcheck.py" --src "$W/clutneg2/src" > "$W/clut_neg2.log" ||
   ! grep -q 'func_0024aa48 .*no longer matches' "$W/clut_neg2.log" ||
   ! grep -q 'stored into D_00669340 with no register' "$W/clut_neg2.log" ||
   ! grep -q 'D_00669338: in DESCRIPTORS, but no TEX value' "$W/clut_neg2.log" ||
   ! grep -q 'func_0010c5c8 .*stored into p with no register' "$W/clut_neg2.log"; then
  echo "selftest: clutcheck missed a broken HUD TEX0 pair, an unlisted stored TEX0 or a glyph TEX0 that no longer loads" >&2; cat "$W/clut_neg2.log" >&2; exit 1
fi
# session 115: every CLUT the C uploads into GS memory, and when (tools/host/clutupload.py); a CLUT upload in a
# function REVIEWED does not list, and a listed one whose upload is gone, fail
python3 -I "$ROOT/tools/host/clutupload.py" > "$W/clutup.log" || { cat "$W/clutup.log"; exit 1; }
tail -n 1 "$W/clutup.log"
mkdir -p "$W/clutupneg/src" && cp -r "$ROOT/src/hud" "$W/clutupneg/src/"
sed -i 's/^void func_002393d8(void) {/void func_002393d0(void) {/' "$W/clutupneg/src/hud/hud.c"
sed -i 's/PlatGsSetDefLoadImage(&li, 0x3FD8, 1, 0, 0, 0, 16, 16);/PlatGsSetDefLoadImage(\&li, 0x3FD8, 1, 0, 0, 0, 64, 16);/' "$W/clutupneg/src/hud/hud.c"
if python3 -I "$ROOT/tools/host/clutupload.py" --src "$W/clutupneg/src" > "$W/clutup_neg.log" ||
   ! grep -q 'func_002393d0 (hud/hud.c): uploads a CLUT but is not in REVIEWED' "$W/clutup_neg.log" ||
   ! grep -q 'func_00239368: in REVIEWED but no CLUT upload found' "$W/clutup_neg.log"; then
  echo "selftest: clutupload missed an unlisted CLUT upload or a listed one taken away" >&2; cat "$W/clutup_neg.log" >&2; exit 1
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
  # the image loads and stores (host/null/gsimage.c, session 101): 5.1an's shapes under a wide view
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/gsimage_test" \
      "$ROOT/tests/host/gsimage_test.c" "$ROOT/host/null/gsimage.c" "$ROOT/host/null/dmawalk.c" \
      "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c" "$ROOT/host/port/canvas.c"
  "$W/gsimage_test" > "$W/gsimage.log" || { cat "$W/gsimage.log"; exit 1; }
  tail -n 1 "$W/gsimage.log"
  # the lens flare's visibility count on that store (kelnscls.nostrict.c func_00192958, session 103)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -fno-strict-aliasing -DKH1_HOST -I"$ROOT/include" -I"$ROOT/src" \
      -o "$W/flare_test" "$ROOT/tests/host/flare_test.c" "$ROOT/src/ppp/kelnscls.nostrict.c" \
      "$ROOT/host/port/libvu0.c" "$ROOT/host/null/gsimage.c" "$ROOT/host/null/dmawalk.c" \
      "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c" "$ROOT/host/port/canvas.c" -lm
  "$W/flare_test" > "$W/flare.log" || { cat "$W/flare.log"; exit 1; }
  tail -n 1 "$W/flare.log"
  # the other store readers: menubg's backdrop colours, the half capture and the menu blur's empty
  # test, vm_lib's capture (session 104); --gc-sections keeps only what the four functions reach
  gcc -m32 -malign-double -std=gnu89 -O1 -w -fno-strict-aliasing -ffunction-sections -fdata-sections -DKH1_HOST \
      -I"$ROOT/include" -I"$ROOT/src" -Wl,--gc-sections -o "$W/storeread_test" "$ROOT/tests/host/storeread_test.c" \
      "$ROOT/src/menu/menubg.c" "$ROOT/src/screen/capture.c" "$ROOT/src/gfx/sceneeff.c" "$ROOT/src/screen/screen.c" \
      "$ROOT/host/null/gsimage.c" "$ROOT/host/null/dmawalk.c" "$ROOT/host/null/gsregs.c" "$ROOT/host/null/gsmem.c" \
      "$ROOT/host/port/canvas.c" -lm
  "$W/storeread_test" > "$W/storeread.log" || { cat "$W/storeread.log"; exit 1; }
  tail -n 1 "$W/storeread.log"
  # KH1_HOST_COUNTS's high-water marks (host/null/counts.c, session 96)
  gcc -m32 -malign-double -std=gnu89 -O1 -w -DKH1_HOST -I"$ROOT/include" -o "$W/counts_test" \
      "$ROOT/tests/host/counts_test.c" "$ROOT/host/null/counts.c"
  "$W/counts_test" > "$W/counts.log" || { cat "$W/counts.log"; exit 1; }
  tail -n 1 "$W/counts.log"
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
# The full-screen packets' table against the ELF and the C (tools/host/fscheck.py, session 99), only with
# the user's own ELF in the repo root: every full-screen send is a fullscreen.c row, built from the view in C,
# or exempt; a table missing the stored frame's row fails, and so does the flash's 4:3 literal put back.
# Session 100: also the sceDmaSend / func_00237018 chains, and C rectangles holding both 4:3 edges.
ELF="$ROOT/$(cd "$ROOT" && python3 tools/kh1tool.py config target.elf)"
if [[ -f "$ELF" ]]; then
  python3 -I "$ROOT/tools/host/fscheck.py" --elf "$ELF" > "$W/fs.log" || { cat "$W/fs.log"; exit 1; }
  tail -n 1 "$W/fs.log"
  sed '/D_002B66B0, KH1_FS_X/d' "$ROOT/host/port/fullscreen.c" > "$W/fullscreen_missing.c"
  if python3 -I "$ROOT/tools/host/fscheck.py" --elf "$ELF" --table "$W/fullscreen_missing.c" > "$W/fs_missing.log" ||
     ! grep -q 'D_002B66B0 .*no KH1_FS_X row' "$W/fs_missing.log"; then
    echo "selftest: fscheck missed a full-screen send left out of the table" >&2; cat "$W/fs_missing.log" >&2; exit 1
  fi
  mkdir -p "$W/fsneg/screen" && cp -r "$ROOT/src/." "$W/fsneg/"
  sed -i 's/D_002A6970\[11\] = 0x18C000000 | PLAT_VIEW_GX1;/D_002A6970[11] = 0x18C009000;/' "$W/fsneg/screen/brightfade.c"
  if python3 -I "$ROOT/tools/host/fscheck.py" --elf "$ELF" --src "$W/fsneg" > "$W/fs_neg.log" ||
     ! grep -q 'writes D_002A6970\[11\] = 0x18C009000: a 4:3 edge' "$W/fs_neg.log"; then
    echo "selftest: fscheck missed a full-screen pass written with a 4:3 edge" >&2; cat "$W/fs_neg.log" >&2; exit 1
  fi
  # session 100: the stored frame's path-2 send (frame.c func_001e05a8) left out of the table
  sed '/D_003DAF60, KH1_FS_X/d' "$ROOT/host/port/fullscreen.c" > "$W/fullscreen_missing2.c"
  if python3 -I "$ROOT/tools/host/fscheck.py" --elf "$ELF" --table "$W/fullscreen_missing2.c" > "$W/fs_missing2.log" ||
     ! grep -q 'D_003DAF60 .*no KH1_FS_X row' "$W/fs_missing2.log"; then
    echo "selftest: fscheck missed the stored frame's func_001e05a8 send" >&2; cat "$W/fs_missing2.log" >&2; exit 1
  fi
  # session 100: a full-screen rectangle built in C with both 4:3 edges (the menu background's gradient put back)
  mkdir -p "$W/fsneg2" && cp -r "$ROOT/src/." "$W/fsneg2/"
  sed -i 's/PLAT_VIEW_GX0;/0x7000;/; s/PLAT_VIEW_GX1;/0x9000;/' "$W/fsneg2/menu/menubg.nostrict.c"
  if python3 -I "$ROOT/tools/host/fscheck.py" --elf "$ELF" --src "$W/fsneg2" > "$W/fs_neg2.log" ||
     ! grep -q 'func_0020a9b0 writes both 4:3 edges' "$W/fs_neg2.log"; then
    echo "selftest: fscheck missed a full-screen rectangle built in C with the 4:3 edges" >&2; cat "$W/fs_neg2.log" >&2; exit 1
  fi
  # session 107: a send drawn past its frame's width under the wide view (the depth blur's capture made the
  # view's full width into its 512-wide buffer)
  mkdir -p "$W/fsneg3" && cp -r "$ROOT/src/." "$W/fsneg3/"
  sed -i 's|XYZ(0x7000 + PLAT_VIEW_W16 / 2, 0x8000|XYZ(0x7000 + PLAT_VIEW_W16, 0x8000|' "$W/fsneg3/gfx/sceneeff.nostrict.c"
  if python3 -I "$ROOT/tools/host/fscheck.py" --elf "$ELF" --src "$W/fsneg3" > "$W/fs_neg3.log" ||
     ! grep -q 'D_002A5A90 .*drawn past its frame.s width .*x 0.0 .. 677.6, FBW x 64 = 512' "$W/fs_neg3.log"; then
    echo "selftest: fscheck missed a send drawn past its frame's width" >&2; cat "$W/fs_neg3.log" >&2; exit 1
  fi
  # session 108: the blocks each FRAME send draws, against the PS2's and the memory map: with the menu capture's
  # and the depth blur's entries taken out of BLOCK_EXPECTED, the capture's wrap into 0x3900 and the blur's
  # capture over the off-screen buffer 0x3A00 both fail
  if python3 -I -c 'import sys; sys.path.insert(0, sys.argv[1]); import fscheck as f
del f.BLOCK_EXPECTED[("D_002B6760", "wide")], f.BLOCK_EXPECTED[("D_002A5620", 0x3A00)]
sys.argv = [sys.argv[0], "--elf", sys.argv[2]]; f.main()' "$ROOT/tools/host" "$ELF" > "$W/fs_neg4.log" ||
     ! grep -q 'D_002B6760 .*draws blocks 0x3900 .. 0x3924, .*past the PS2.s (0x3600 .. 0x38FF)' "$W/fs_neg4.log" ||
     ! grep -q 'D_002A5620 .*draws blocks 0x3A00 .*in off-screen buffer 0x3A00' "$W/fs_neg4.log"; then
    echo "selftest: fscheck missed a send drawing blocks past the PS2's or over a live buffer" >&2
    cat "$W/fs_neg4.log" >&2; exit 1
  fi
  # session 109: the render-to-texture sends from the C. With the window font's entries taken out, the eye
  # overlay (its tags finished by texspot's stores) and, when gcc -m32 builds tools/host/rtsends.c, the
  # 196 and 256 shadow windows fail; with texspot's tag stores gone the eye overlay is reported unwalked
  if python3 -I -c 'import sys; sys.path.insert(0, sys.argv[1]); import fscheck as f
del f.BLOCK_EXPECTED[("D_004F7820", 0x3D7C)], f.BLOCK_EXPECTED[("D_0035C4A0", 0x3D7C)]
sys.argv = [sys.argv[0], "--elf", sys.argv[2]]; f.main()' "$ROOT/tools/host" "$ELF" > "$W/fs_neg5.log" ||
     ! grep -q 'D_0035C4A0+D_0035C550 .*draws blocks 0x3D7C .. 0x3DFF in window font' "$W/fs_neg5.log" ||
     { grep -q 'run-time builds' "$W/fs_neg5.log" &&
       ! { grep -q 'D_004F7820\[1\] .*in window font' "$W/fs_neg5.log" &&
           grep -q 'D_004F7820\[2\] .*in window font' "$W/fs_neg5.log" &&
           ! grep -q 'D_004F7820\[0\]' "$W/fs_neg5.log"; }; }; then
    echo "selftest: fscheck missed a render-to-texture send over the window font" >&2; cat "$W/fs_neg5.log" >&2; exit 1
  fi
  mkdir -p "$W/fsneg6" && cp -r "$ROOT/src/." "$W/fsneg6/"
  sed -i '/D_0035C550\.x3 = 112;/d' "$W/fsneg6/gfx/texspot.nostrict.c"
  if python3 -I "$ROOT/tools/host/fscheck.py" --elf "$ELF" --src "$W/fsneg6" > "$W/fs_neg6.log" ||
     ! grep -q "D_0035C550's tag stores .* not found" "$W/fs_neg6.log"; then
    echo "selftest: fscheck missed the eye overlay's tag stores gone" >&2; cat "$W/fs_neg6.log" >&2; exit 1
  fi
  # session 110: the Z buffers the sends write and the textures they read. With the depth blur's wide Z entry
  # and (session 111) renderer B's step-2 upload before the callbacks taken out, the blur's capture writing Z
  # past the PS2's blocks and the eye overlay reading an image nothing in its picture uploaded both fail; with
  # the crossfade's ZBUF put back to 0 (session 112: `1UL << 32` was 0 under -m32), its Z in the display too
  # (when gcc -m32 builds rtsends.c)
  if python3 -I -c 'import sys; sys.path.insert(0, sys.argv[1]); import fscheck as f
del f.ZBLOCK_EXPECTED[("D_002A5620", "wide")]
f.STEP2_AFTER.clear()
sys.argv = [sys.argv[0], "--elf", sys.argv[2]]; f.main()' "$ROOT/tools/host" "$ELF" > "$W/fs_neg7.log" ||
     ! grep -q 'D_002A5620 .*its ZBUF draws blocks 0x0E80 .*past the PS2.s (0x0E00 .. 0x0E7F' "$W/fs_neg7.log" ||
     ! grep -q 'D_0035C4A0+D_0035C550 .*reads blocks 0x3600 .. 0x360F in texture slot' "$W/fs_neg7.log" ||
     ! grep -q 'D_0035C4A0+D_0035C550 .*its CLUT load reads blocks 0x3700 .. 0x3703 in texture slot' "$W/fs_neg7.log"; then
    echo "selftest: fscheck missed a Z write past the PS2's blocks or an unloaded texture or CLUT" >&2
    cat "$W/fs_neg7.log" >&2; exit 1
  fi
  sed 's/func_0011fb38(0x4e, 1ULL << 32, p);/func_0011fb38(0x4e, 0, p);/' "$ROOT/src/obj/objdraw.nostrict.c" > "$W/objdraw_z0.c"
  if python3 -I -c 'import sys; sys.path.insert(0, sys.argv[1]); import fscheck as f
f.RT_SOURCES = tuple(sys.argv[3] if s.endswith("objdraw.nostrict.c") else s for s in f.RT_SOURCES)
sys.argv = [sys.argv[0], "--elf", sys.argv[2]]; f.main()' "$ROOT/tools/host" "$ELF" "$W/objdraw_z0.c" > "$W/fs_neg9.log" ||
     { grep -q 'run-time builds' "$W/fs_neg9.log" &&
       ! grep -q 'func_00135ed0\[64x64\] .*its ZBUF at 0x0000 is in display' "$W/fs_neg9.log"; }; then
    echo "selftest: fscheck missed the crossfade's Z in the display" >&2; cat "$W/fs_neg9.log" >&2; exit 1
  fi
  # session 112: the CLUT loads. Renderer B's step-2 TEX0 with CLD 0 (no load) leaves the eye overlay's first
  # sprite reading a CLUT nothing in its picture loads
  mkdir -p "$W/fsneg10" && cp -r "$ROOT/src/." "$W/fsneg10/"
  sed -i 's/| 0x2006E00401313600ULL;/| 0x0006E00401313600ULL;/' "$W/fsneg10/model/mdlgs.nostrict.c"
  if python3 -I "$ROOT/tools/host/fscheck.py" --elf "$ELF" --src "$W/fsneg10" > "$W/fs_neg10.log" ||
     ! grep -q 'D_0035C4A0+D_0035C550 .*reads the CLUT 0x3700 (CSA 0) that no TEX0 / TEX2 in its picture loads' "$W/fs_neg10.log"; then
    echo "selftest: fscheck missed a CLUT read nothing loaded" >&2; cat "$W/fs_neg10.log" >&2; exit 1
  fi
  # session 111: the stretched copies' sources. The menu blur's row without KH1_FS_UOWN (its capture's own
  # buffer read as a texture), the depth blur capture's with it (the 3D target read as a capture's buffer) and
  # the frame copy's without KH1_FS_U (its 32-texel strips of the target, under session 99's 255-texel test)
  sed 's/{ D_002A4B60, KH1_FS_U | KH1_FS_UOWN,/{ D_002A4B60, KH1_FS_U,/; s/{ D_002A5A90, KH1_FS_U,/{ D_002A5A90, KH1_FS_U | KH1_FS_UOWN,/
       s/{ D_002A6890, KH1_FS_X | KH1_FS_U,/{ D_002A6890, KH1_FS_X,/' "$ROOT/host/port/fullscreen.c" > "$W/fullscreen_src.c"
  if python3 -I "$ROOT/tools/host/fscheck.py" --elf "$ELF" --table "$W/fullscreen_src.c" > "$W/fs_neg8.log" ||
     ! grep -q 'D_002A4B60 .*reads TEX0 0x3600 TBW 4 .*a capture.s own buffer: KH1_FS_UOWN' "$W/fs_neg8.log" ||
     ! grep -q 'D_002A5A90 .*reads TEX0 0x1A00 .*under KH1_FS_UOWN: no capture.s own buffer (the 3D target)' "$W/fs_neg8.log" ||
     ! grep -q 'D_002A6890 .*copies the 3D target (u over 32 texels) and its row has no KH1_FS_U' "$W/fs_neg8.log"; then
    echo "selftest: fscheck missed a stretched copy reading the wrong buffer" >&2; cat "$W/fs_neg8.log" >&2; exit 1
  fi
else
  echo "selftest: no $(basename "$ELF"), fscheck skipped"
fi
echo "selftest: PASS"
