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

Session 127 (2026-10-25). Only phase 1 and the main ELF's share of phase 2 are measured; the rest is a judgement
from the docs named.

| Phase | Done | Basis |
|---|---|---|
| 1. Toolchain, repo skeleton, first matches | 100% | ee-gcc 2.96 pinned and checked (docs/toolchain.md), make + objdiff, kh1.elf byte-identical |
| 2. EE decomp (gameplay, menus, scripting, collision, audio control) | 90% | main ELF 6,979 / 6,988 functions (99.87%); 9 hard functions left; the overlays (dktitle.x, dkmovie.x, wm.x, gb.x, the summons, xl_limit.x) not started (vita-port-plan 5.2) |
| 3. VU1 microcode and GS usage as a renderer spec | 90% | all 22 VU programs inventoried, renderers A and B and the GS state, memory map, draw order (renderer B's depth key settled), both texture animation kinds, the map grid's three chains, frame pacing, the system-message display, the script's screen spin and the other full-screen effects (menu blur, depth blur, sway, lens grid, fades, letterbox) written up (renderer-spec 2-5, 4.14-4.17), the 2D layers' one coordinate space and the 960 x 544 scaling plan (5.3), the HUD's anchor table (5.3.1), every CPU cull's frustum under a wider view (5.4; no other frustum in the main ELF), a per-send drawn-rectangle list for the real-disc check (`gsstate.py --extents`), the full-screen passes' 4:3 constants listed (C and static packets, 5.4) with the static packets' stretch and the scissor rule written down, the lens grid's sampling under the wide view settled (5.4 "Session 94"), one rounded margin for every wide-view form (5.4 "Session 95"), the frame copy's packet read and what the wide view's sides are (5.4 "Session 97"), the other copies' shapes read and walked and one missed full-screen send found (5.4 "Session 98"), every full-screen send checked by a tool against the table and the C (8 more rows, 3 passes fixed, 5.4 "Session 99"), and the other GIF paths too (the menu backdrop and the stored frame's three sends, 5.4 "Session 100"), the menus' full-width rules widened with the backdrop (5.4 "Session 101", nameentry's row checked: not a rule, "Session 102"), every 2D sprite's CLUT shown loaded in its own picture (4.9 "Session 113") and the 2D palette table (4.9 "Session 114"), with who writes every CLUT block and how often, 2D and 3D (4.13 "Session 115"), and no render target over a boot or load CLUT but the window font's known three (4.13 "Session 116"), and the texture functions and wrap / filter modes the game sets (4.13 "Session 120": MODULATE, DECAL once, no HIGHLIGHT; no mipmaps), and the blend equations and alpha / destination alpha tests the game sets (4.13 "Session 121": five ALPHA forms, every TEST value one GPU draw), and its depth states, fog and primitive forms (4.13 "Session 122": Z24 GEQUAL / GREATER / ALWAYS, Z16S for shadows; TRISTRIP, TRIFAN, TRIANGLE, SPRITE, LINE, no LINESTRIP), and the whole draw state's GPU pipelines counted (4.13 "Session 123": 27 from the static packets, about 42 with the C's states) with the render targets the game draws into and the PS2's shared blocks between them, and the draw calls the static packets take (4.13 "Session 124": 148 over 38 sends, the column copies' scissors the most; 43 once the repeated columns merge, 4.13 "Session 125"), and each frame's render passes in order with their load / store needs for a tiled GPU (4.13 "Session 126": the 3D target and the display cleared by strips, stored because the frame copy samples one and the other is scanned out, depth discarded), and the transfers between the draws and the 27 static fragment shaders as source (4.13 "Session 127": 26 generate, the shadow casters' 1-bit FBMSK needs a frame read); not yet checked against a real-disc host run, open questions in renderer-spec 6 |
| 4. Shiftable cleanup (no dependence on the original layout) | 70% | code moves (m1 / m12 build), 2,041 data names float; the nine float builds since session 30 are unbooted, data not yet fully owned by src/ (docs/shiftable-plan.md, float-untested.md) |
| 5. Vita bring-up | 23% | step 1 of 8 (host build) mostly done: all game C links and boots to the first overlay call on a null platform with a GS register and memory model and a scriptable pad (5.1aa); the input layer read and the Vita's button mapping written (5.1ab), vibration and the CIRCLE / CROSS swap planned (5.1ac), the movie player's main-ELF interface and a `PlatMovie*` layer drafted (5.1ad), the camera matrices in C (bit-identical maths to the original's code) with a hor+ wide switch (5.1ae), the HUD's anchor table as port data applied in the host's GIF path and the full-screen passes in C widened through `platform/view.h` (5.1af), the static full-screen packets stretched in the host's GIF path, a check that every HUD environment is anchored or a marker, and the 2D canvas map as tested port maths (5.1ag), the lens grid widened, a host "present" writing the GS model's frames as images and every HUD staging send checked against its part's environment (5.1ah), the view's margin in one sixteenths convention and the present showing the flat passes (5.1ai), the present's frame copy and a high-water hook for the real-disc run's list counts (5.1aj), the copy walked in a test and the wide view's shots lined up (5.1ak), the Z-area and spin copies walked under the wide stretch and the stored frame's row added (5.1al), every full-screen send checked by fscheck.py and the host model's copies on one canvas (5.1am), the other GIF paths' full-screen draws widened or given rows and the captures' `PlatGs` contract written (5.1an), the null platform's image loads and stores in the PS2's shapes with a test, and the lens flare's depth box sized (5.1ao), its depth read answered "all visible" where the host model holds no depth (5.1ap) and tested on the game's own count (5.1aq), the other store readers (menu backdrop, half capture and blur, vm_lib's capture) tested on the game's own C (5.1ar), the menu capture's copy sent through the host's GIF path with and without the present's fill (5.1as), the present's fill kept inside its buffer and the depth blur's capture tested (5.1at), sends drawn past their frame's width found by fscheck.py (5.1au), the GS blocks each send draws checked against the PS2's and the memory map (5.1av), the render-to-texture sends (shadows, crossfade, eye overlay) built from the game's C and checked the same way (5.1aw); their Z writes and texture reads checked too (5.1ax); the stretched copies' source buffers and the step-3 callbacks' first sprites checked (5.1ay); the CLUT loads checked and eight shifts by 32 or more that broke under the host's 32-bit `long` fixed, with a check (longcheck.py; the crossfade's "depth write" was one of them, 5.1az); the windows', text's, menus' and HUD's CLUT reads checked from the C, so a port keys 2D palettes by CBP / CSA (clutcheck.py, 5.1ba), with the 2D palette table and the HUD's TEX0 pairs checked by the tool (5.1bb), and the palette-cache invalidation list as a tool check (clutupload.py: palettes keyed by the bytes uploaded, only the room CLUTs change between frames, 5.1bc), and that palette cache as port code tested on those cases through the GS model (host/port/palcache.c, 5.1bd), wired into the host's present with per-frame upload counts, and a texture cache's key chosen by test (page stamp, then the bytes, 5.1be), then that texture cache as port code in the present, render targets never kept (5.1bf), and the GPU format each PSM uploads as with TEXA applied in the shader, tested against the GS model (host/port/texfmt.c, 5.1bg), and the shader's texture function (TFX / TCC) and sampler state (CLAMP's four wrap modes, TEX1's filter) as port code tested the same way (host/port/texfunc.c, sampler.c, 5.1bh), and the blend state (targets' alpha on the 0x80 scale, Cs pre-scaled in the shader: the game's forms exact or within 2) with the alpha test and DATE as discards, masks and a stencil (host/port/blend.c, atest.c, 5.1bi), and the depth state (the GS's Z scaled into a float depth, exact), fog (the shader's exact integer step) and the primitive assembly (the GIF's vertex queue as GPU lists, flat colour copied, sprites as two triangles, half-pixel centres) tested against the GS model and gsregs.c's queue (host/port/depth.c, fog.c, primasm.c, 5.1bj), and the whole draw state as GPU pipelines, fragment shader variants and uniforms with a pipeline count over the host run and the static packets, and the render targets, viewport and scissor as port code tested against the GS model's target list (host/port/drawstate.c, target.c, tools/host/drawpipes.py, 5.1bk), and the GPU vertex layout with its vertex shader variants tested against the GS model's sprite at 4:3 and 960 x 544, and the batches and draw calls a frame takes counted over the host run and the static packets (host/port/vertex.c, batch.c, 5.1bl), the column copies merged into one draw each and the per-frame vertex and uniform rings sized as port code (host/port/ring.c, 5.1bm), and the draw list recorded as GPU commands (passes, batches with vertex ranges and uniform slots in the rings, column groups held) with each pass's load / store needs, replayed through a software rasteriser against the GS model (host/port/cmdbuf.c, 5.1bn), the uploads, copies, CLUT loads and texture decodes in that list so it is complete, and every shader variant written as Cg from one table and run back by an interpreter against the models (host/port/shadergen.c, 5.1bo); the draw list's replay point found (the frame-end wait, 5.1x); the sound driver's commands written up as the audio layer's interface (docs/sound-spec.md) and kept by a null sound server on the host (5.1z); no vitasdk build, extraction tool, renderer, sound or overlays yet (vita-port-plan 5) |
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
