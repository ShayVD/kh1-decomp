# Progress: SLPS_251.98

Regenerate with `make progress-update` at the end of each session and commit the result.
A function counts as matched only when its rebuilt bytes are identical to the original
and objdiff reports 100% for it.

_Last updated 2026-10-25._

## Overall

| Group | Matched / functions | % functions | % code bytes | Decompiled, not matching |
|---|---|---|---|---|
| total | 6979 / 6988 | 99.87% | 98.84% | 0 |

<!-- phases -->
## By project phase (estimate, kept by hand; refresh it at the end of each session)

Session 88 (2026-10-25). Only phase 1 and the main ELF's share of phase 2 are measured; the rest is a judgement
from the docs named.

| Phase | Done | Basis |
|---|---|---|
| 1. Toolchain, repo skeleton, first matches | 100% | ee-gcc 2.96 pinned and checked (docs/toolchain.md), make + objdiff, kh1.elf byte-identical |
| 2. EE decomp (gameplay, menus, scripting, collision, audio control) | 90% | main ELF 6,979 / 6,988 functions (99.87%); 9 hard functions left; the overlays (dktitle.x, dkmovie.x, wm.x, gb.x, the summons, xl_limit.x) not started (vita-port-plan 5.2) |
| 3. VU1 microcode and GS usage as a renderer spec | 83% | all 22 VU programs inventoried, renderers A and B and the GS state, memory map, draw order (renderer B's depth key settled), both texture animation kinds, the map grid's three chains, frame pacing, the system-message display, the script's screen spin and the other full-screen effects (menu blur, depth blur, sway, lens grid, fades, letterbox) written up (renderer-spec 2-5, 4.14-4.17); not yet checked against a real-disc host run, open questions in renderer-spec 6 |
| 4. Shiftable cleanup (no dependence on the original layout) | 70% | code moves (m1 / m12 build), 2,041 data names float; the nine float builds since session 30 are unbooted, data not yet fully owned by src/ (docs/shiftable-plan.md, float-untested.md) |
| 5. Vita bring-up | 14% | step 1 of 8 (host build) mostly done: all game C links and boots to the first overlay call on a null platform with a GS register and memory model and a scriptable pad (5.1aa); the input layer read and the Vita's button mapping written (5.1ab); the draw list's replay point found (the frame-end wait, 5.1x); the sound driver's commands written up as the audio layer's interface (docs/sound-spec.md) and kept by a null sound server on the host (5.1z); no vitasdk build, extraction tool, renderer, sound or overlays yet (vita-port-plan 5) |
<!-- /phases -->

## By address segment (`[[segment]]` in kh1.toml)

| Group | Matched / functions | % functions | % code bytes | Decompiled, not matching |
|---|---|---|---|---|
| segment:game | 6258 / 6266 | 99.87% | 98.78% | 0 |
| segment:sdk | 721 / 722 | 99.86% | 99.39% | 0 |

## By source directory (decompiled functions only)

| Group | Matched / functions | % functions | % code bytes | Decompiled, not matching |
|---|---|---|---|---|
| dir:src/ai | 145 / 145 | 100.00% | 100.00% | 0 |
| dir:src/asm | 33 / 33 | 100.00% | 100.00% | 0 |
| dir:src/camera | 172 / 172 | 100.00% | 100.00% | 0 |
| dir:src/coll | 148 / 148 | 100.00% | 100.00% | 0 |
| dir:src/event | 129 / 129 | 100.00% | 100.00% | 0 |
| dir:src/game | 612 / 612 | 100.00% | 100.00% | 0 |
| dir:src/gfx | 219 / 219 | 100.00% | 100.00% | 0 |
| dir:src/gummi | 128 / 128 | 100.00% | 100.00% | 0 |
| dir:src/hand | 33 / 33 | 100.00% | 100.00% | 0 |
| dir:src/hud | 320 / 320 | 100.00% | 100.00% | 0 |
| dir:src/io | 30 / 30 | 100.00% | 100.00% | 0 |
| dir:src/list | 61 / 61 | 100.00% | 100.00% | 0 |
| dir:src/memcard | 55 / 55 | 100.00% | 100.00% | 0 |
| dir:src/menu | 540 / 540 | 100.00% | 100.00% | 0 |
| dir:src/model | 85 / 85 | 100.00% | 100.00% | 0 |
| dir:src/msgwin | 44 / 44 | 100.00% | 100.00% | 0 |
| dir:src/obj | 803 / 803 | 100.00% | 100.00% | 0 |
| dir:src/pad | 23 / 23 | 100.00% | 100.00% | 0 |
| dir:src/ppp | 706 / 706 | 100.00% | 100.00% | 0 |
| dir:src/save | 69 / 69 | 100.00% | 100.00% | 0 |
| dir:src/screen | 109 / 109 | 100.00% | 100.00% | 0 |
| dir:src/sdk | 721 / 721 | 100.00% | 100.00% | 0 |
| dir:src/shop | 92 / 92 | 100.00% | 100.00% | 0 |
| dir:src/sound | 155 / 155 | 100.00% | 100.00% | 0 |
| dir:src/text | 440 / 440 | 100.00% | 100.00% | 0 |
| dir:src/util | 172 / 172 | 100.00% | 100.00% | 0 |
| dir:src/vm | 935 / 935 | 100.00% | 100.00% | 0 |

## History

See `docs/progress-history.tsv` (one row per session).
