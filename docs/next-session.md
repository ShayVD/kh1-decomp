# Next session prompt

Paste this to start the next session.

---

Continue kh1-decomp, the matching decomp of Kingdom Hearts Final Mix (PS2), retail `SLPS_251.98`, SHA-256 1993a4da…. Read README.md and everything in docs/ first; they are the only notes carried between sessions. My own `SLPS_251.98` is in my Downloads folder (never commit it); in a cloud container a copy is in the project files' uploads folder (check its SHA-256 against kh1.toml).

## The Mac

**The Mac is back from Monday 2026-10-26** (the user said on 2026-10-23 it was away until then; sessions 49 to 76
ran without it; sessions 77 to 102 ran on Sunday 2026-10-25, still without it). **Ask for the Mac and PCSX2 at the start** (the connect card in the Claude desktop app) **and make
item 1 the first thing**: nine float builds are waiting for a boot. Items 2 and 3 also need the Mac: the user's ISO
is in Downloads for the host run, and the overlay files are in Downloads/kh1-test/ovl. If the user says the Mac is
still away, skip items 1 to 3, add every float change to docs/float-untested.md as untested, and do the static
items.

## Where we stopped (end of session 102, 2026-10-25)

- **Session 102** (static + host, vita-port-plan 5.1ap, renderer-spec 5.4 "Session 102"): **the lens flare's
  depth read on the host, nameentry's row.** The user had not answered session 101's card yet, so "widen"
  stays (check the session 101 thread again: "keep them 4:3" still means deleting the `#ifndef KH1_PS2`
  block in winpart.nostrict.c's `func_00206130`). **nameentry's `func_002078f0(.., 0, 188, y, 200, 512,
  1)` is not a full-width rule**: `func_002078f0` passes its arguments on as `func_00201440(o, type 2, mode
  0, px 188, py y, pw 200, x 512, cols, id 1)`, a 200 px list-row frame at window x 188 (the 512 is the
  text's x), so nothing to widen. **The null store of a Z box the draws wrote now reads 0** (the farthest:
  the flare counts pixels under the light's Z, so it sees itself all visible) instead of a stale upload's
  bytes; a Z buffer the model holds (an upload or copy since, page granularity) still reads its bytes.
  New `kh1_gsmem_drawn` (gsmem.c). gsimage_test 21 checks. No src/ change: kh1.elf byte-identical, no
  float-untested row; selftest PASS, the host links (571).


- **Session 101** (static + host, vita-port-plan 5.1ao, renderer-spec 5.4 "Session 101"): **5.1an's contract
  in the null platform, the full-width rules, the lens flare's box.** The four `PlatGs*Image` calls were
  stubs on the host; **host/null/gsimage.c** now fills libgraph's packets and does the transfers against
  gsmem.c's model (a load is an upload while `KH1_HOST_TRACE >= 2`; a store hands main memory the PS2's
  packed shape whatever the view). **tests/host/gsimage_test.c** (selftest) asserts 5.1an's shapes under the
  960:544 view and 4:3 (0x90000 bytes and 0x600 a row for the target, 0x24000 for `0x3600`, the Z24 box,
  menubg's 64 bytes, the halves loaded back). **The menus' full-width rules** now run to the view's edges off
  the PS2 (winpart.nostrict.c `func_00206130`, `#ifndef KH1_PS2`), on the recommended option of a decision
  card the user had not answered yet: **check the session 101 thread; if the user chose "keep them 4:3",
  delete that block.** **The lens flare's box**: `bC0 = key->e << 3`, `bC1 = key->f << 2` (the same record,
  one caller), at most 4096 pixels by the scratch (0x3000 bytes). **All 677 out/build objects
  bit-identical**, kh1.elf byte-identical, no float-untested row; selftest PASS, the host links (571).


- **Session 100** (static, vita-port-plan 5.1an, renderer-spec 5.4 "Session 100"): **the full-screen draws
  that are not `func_00106b18` sends, the captures' `PlatGs` contract.** fscheck.py also walks the static
  chains of `sceDmaSend`, `func_00237018` and frame.c's `func_001e05a8`, and scans src/ for rectangles
  built in C with both 4:3 edges (outside `#ifdef KH1_PS2`; array sizes from include/ too; decimal
  28672 / 36864 count). Found **menubg.nostrict.c's four full-screen backdrop gradients** (now
  `PLAT_VIEW_GX0 / GX1`) and **the stored frame's three path-2 sends** `D_003DAE30` / `D_003DAF60` /
  `D_003DB050` (now fullscreen.c rows `X | U`; the zoom's C corners stay in canvas units, and fscheck now
  requires that for a send with an X row). The menus' full-width rules (`func_00206130(.., 0, y, 512, ..)`)
  stay with their windows (a reason). `gs_packets.callers(reg=)` drops stale argument addresses and finds
  delay-slot ones. 58 sends, 24 full-screen, 22 rows, 3 exempt, 0 problems; two more selftest negative
  cases. **All 677 out/build objects bit-identical**, kh1.elf byte-identical, no float-untested row.
  **The captures' contract** (vita-port-plan 5.1an): every `PlatGsExecStoreImage` (the target 512 x 384,
  the half capture 256 x 192, the lens flare's Z box in PSMZ24, menubg's two display pixels) and what a
  port returns: main memory always the PS2's shape (CPU effects read it: ripple, edge filter, grey tint,
  row scroll), the view squeezed into it and stretched back on the load; a disc picture loaded into the Z
  area placed 4:3.

- **Session 99** (static + host, vita-port-plan 5.1am, renderer-spec 5.4 "Session 99"): **every
  full-screen send checked, the model's copies on one canvas.** **tools/host/fscheck.py** (needs the ELF;
  in the self-test when it is present, two negative cases) walks all 37 `func_00106b18` sends and checks the
  21 full-screen ones against host/port/fullscreen.c and the C's writes of their XYZ words. It found 8 sends
  with no row (now rows: `D_002B65E0` cross-fade, `D_002A4DD0` / `D_002A4B60` menu blur, `D_002A5A90` /
  `D_002A5620` / `D_002A5AC0` depth blur, `D_002A6A40` / `D_002A6AA0` shaped wipe) and 3 passes partly
  4:3 in C: the menu blur's first copy and the depth blur's alpha fill and capture (corners in data, now
  written with the view's edges under `#ifndef KH1_PS2`), brightfade.c's colour over the target (literals,
  now `PLAT_VIEW_GX0 / GX1`). **All 677 out/build objects bit-identical**, kh1.elf byte-identical, the float
  ELF the same (no float-untested row). `KH1_FS_UOWN`: a copy of a capture of its own. **The host model
  reads a stretched copy back by the margin** (gsregs.c `uorg`), so its display holds canvas d at pixel d and
  the spin copy no longer counts the margin twice; the present's display shot is no longer shifted.
  present_test 46 -> 47. Port rule: the half-size capture keeps the PS2's 256 x 192 x 3 bytes in main
  memory (`func_0010a3e8`'s 0x24000 block, `func_00102a48`'s scan).

- **Session 98** (static + host, vita-port-plan 5.1al, renderer-spec 5.4 "Session 98"): **the other copies
  walked, the stored frame's row.** No change under src/ (kh1.elf byte-identical, no float-untested row).
  The copy into the Z area `D_002A5FD0`, the spin copy `D_002A4ED0` and the spin strip `D_002A4FC0` read from
  the ELF (v ranges, CLAMP, SCISSOR in 5.4's table); present_test walks the two sprite copies at 4:3 and
  under the wide stretch: each lands where fullscreen.c's row says for a view-wide renderer (in the 512-wide
  model the Z-area copy shifts by the margin like the frame copy, the spin copy by it twice). The Z-area copy
  never writes the Z area's last column / row (x -1.5 .. 510.5). **Correction:** the frame copy's PRIM
  `0x116` has no ABE (session 97 said it did). **Finding:** the fake-disc `KH1_HOST_WIDE` run's `--extents`
  showed capture.c's `D_002B66B0` (the stored frame drawn back as it fades) still at 0 .. 512: a missing
  full-screen row, added to host/port/fullscreen.c (X and u); the frame copy's 80 strips at -82.8 .. 594.8.
  present_test 30 -> 46 checks.

- **Session 97** (static + host, vita-port-plan 5.1ak, renderer-spec 5.4 "Session 97"): **the frame copy
  walked, the wide view's shots.** No change under src/ (kh1.elf byte-identical, no float-untested row).
  The frame copy's packet read from the ELF (`D_002A65D0`: 6 x A+D, REGLIST PRIM / RGBAQ, 16 strips of UV
  XYZ2 UV XYZ2, **v 0 .. 384 over the display's 448 lines**, a ZBUF ZMSK bracket); tests/host/present_test.c
  builds that shape and walks it (`kh1_dma_walk`) under a made-up target: the display shot shows the target
  at the canvas map's pixels. **Finding:** under `KH1_HOST_WIDE` the stretched copy reads u from the view's
  left edge, so the model's 512-wide display holds canvas x d + 82.8 at pixel d (session 96's display shot
  was shifted). `kh1_present_wide` (set by main.c): the display shot is read back by the margin (canvas
  82.8 .. 512 shown), the target shot unchanged with black sides; both shot lines say so. Renderer-spec 5.4:
  the sides are the renderer's own wide 3D target, never the copy. present_test 22 -> 30 checks.

- **Session 96** (host only, vita-port-plan 5.1aj, renderer-spec 5.4 "Session 96"): **the frame copy in the
  present, the counts' high-water marks.** No change under src/ (kh1.elf byte-identical, no float-untested
  row). host/null/gsmem.c's `kh1_gsmem_flat_sprite` also draws a **textured SPRITE the exact model refused**
  (the frame copy `D_002A6890`: the 3D target `0x1A00` as a 512 x 512 bilinear texture), point-sampled, under
  the present's switch only, no page marked, no trace counter moved (`tex_sprites` / `tex_pixels`; the shot
  line prints both): fake disc `--draws / --targets / --uploads / --sends` identical with `KH1_HOST_SHOT`, 17
  textured sprites a frame, still black. **`KH1_HOST_COUNTS=1`** (host/null/counts.c): countcheck's DATA rows'
  high-water marks (renderer B's `D_0055C698.x4 / .x8 / .xc` 78 / 480 / 72, collisions `D_002C12C4` 2048 (a
  lower bound: reset per query), messages `D_00389C80` 273, grid `D_0029B2FC` ~1020, trigger boxes
  `D_00389C90.nbox` 10, the windows' `D_00389C90.cnt[0..7]` 256), sampled at each vblank, DMA send and list
  end, printed at the end with "OVER" past a size. tests/host/counts_test.c, gsmem_test +5.

- **Session 95** (static + host, vita-port-plan 5.1ai, renderer-spec 5.4 "Session 95"): **one margin in
  sixteenths, the flat sprites in the present, prim.c's send.** `kh1_view_side16` (host/port/view.c, rounded
  once: 1325 = 82.8125 px at 960 x 544) replaces `kh1_view_x0 / x1`; include/platform/view.h's
  `PLAT_VIEW_GX0 / GX1`, **`PLAT_VIEW_W16`** (8192 on the PS2; `PLAT_VIEW_W` is gone: sceneeff.c's spin
  `W16 / 2`, sway `u1 = W16 - u0`), `PLAT_VIEW_X0 / X1` (floats on the host), `PLAT_VIEW_SIDE` and the
  markers' bounds are exact in it, and `kh1_null_hud_wide(s32)` takes it, so the C passes and the stretched
  packets meet on the same sixteenth (canvas_test: view.c = `kh1_canvas_fit` at six screens, 57 checks).
  **all 677 out/build objects bit-identical**, kh1.elf byte-identical, the m12 float ELF the same bytes (no
  float-untested row). host/null/gsmem.c **`kh1_gsmem_flat_sprite`**: untextured SPRITEs (clears, display
  clear, fade, letterbox) filled into the model, only when the present is on (`kh1_gsmem_flat(1)`), with no
  page marked and no trace counter moved (fake disc: `--draws / --targets / --uploads / --sends` identical
  with `KH1_HOST_SHOT`; 16 a frame, still black: clear colour 0); the shot line prints the count.
  **prim.c's `D_00648070` send is 3D lines** (kind 1 nodes projected through the caller's matrix), not a HUD
  part, and func_00238440 has **no main-ELF caller** (nor prim.nostrict(_nofill).c's func_002384e0 /
  func_00238768 / func_002386c0): an overlay's. hudcheck.py fails on a staging send outside src/hud that
  `OTHER_STAGES` does not name (a third self-test negative case).

- **Session 94** (static + host, vita-port-plan 5.1ah, renderer-spec 5.4 "Session 94"): **the lens grid under
  the wide view, a host present, the staging-send check.** One change under src/: sceneeff.c's lens grid u
  start is `(64 + PLAT_VIEW_SIDE) / 512` (`include/platform/view.h`, `0.0f` on the PS2: **all 677 out/build
  objects bit-identical**, kh1.elf byte-identical, the m12 float ELF the same bytes, no float-untested row),
  because the copy into the Z area it samples starts at the view's left edge; `D_002A6110`'s `CLAMP_1`
  REGION MAXU 510 grows by the view's added width (676) through fullscreen.c's new `KH1_FS_CLAMP` row
  (`kh1_canvas_stretch_clamp`). **`KH1_HOST_SHOT=W:H[:target][:DIR]`** (host/null/present.c): after each
  frame copy `D_002A6890` the GS model's display (or the 3D target) as a PAM through `kh1_canvas_unmap`,
  pillarboxed; turns the chain walk on (hook `kh1_dma_after_send`); the model has no 3D or untextured passes,
  so the fake disc's frames are black (tests/host/present_test.c, 12 checks). **hudcheck.py** also checks
  each of src/hud's **22 staging sends** follows its own part's environment send (in its function or a
  caller's, before the call): 0 problems; a self-test negative case. canvas_test 32 checks, gsregs_test +4.

- **Session 93** (static + host, vita-port-plan 5.1ag, renderer-spec 5.4 "Session 93"): **the full-screen
  packets' stretch, the HUD table check, the canvas map.** No change under src/ (kh1.elf byte-identical, the
  float ELF the same, no float-untested row). **include/platform/fullscreen.h + host/port/fullscreen.c** (port
  data beside hudanchor.c, keyed by the send): the clear `D_002A6500`, frame copy `D_002A6890`, fade
  `D_002A6070`, letterbox `D_002A61E0`, the copy into the Z area `D_002A5FD0`, the spin's copy `D_002A4ED0`
  and strip `D_002A4FC0` (u only), the menu capture `D_002B6760` (X from its own buffer's edge) and **the
  display clear `D_002BC980`** (dispenv.c `func_0010ff60`, new to the list). Under `KH1_HOST_WIDE` the chain
  walk stretches X (canvas 0 .. 512 to the view, -1325 .. 9517 sixteenths) and u (texels from the view's left
  edge) (`kh1_dma_fullscreen`, `kh1_gs_xstretch`), and **the scissor rule** reads a full 4:3 (or the display's
  0 .. 447) `SCISSOR` as the whole view and the 16 32-pixel columns as the view's columns (`kh1_gs_view`; a
  draw line's `, view scissor X0 X1`, `gsstate.py --extents` "(scissor: the view ...)"). Fake disc, wide: the
  clear, display clear and frame copy draw -82.8 .. 594.8. **include/platform/canvas.h + host/port/canvas.c**:
  `kh1_canvas_fit` / `kh1_canvas_map` (5.3 step 1's `(X / 16 - 1792) s + ox`), the stretch and the scissor
  rule as pure functions; tests/host/canvas_test.c (25 checks), gsregs_test +17. **tools/host/hudcheck.py**
  (no build, in the self-test and so in CI): every environment src/hud builds or sends is in
  `kh1_hud_anchors[]` or the new `kh1_hud_markers[]` (17: 11 anchored, 6 markers; gspkt.c's `D_006480D0` is the
  one other), with a negative case.

- **Session 92** (static + host, vita-port-plan 5.1af, renderer-spec 5.4 "Session 92"): **the HUD's anchors
  in the GIF path, the full-screen passes in C.** **include/platform/hudanchor.h + host/port/hudanchor.c**
  (new, port data): each gameplay HUD part's drawing environment and side (`D_00651C00` gauges right; the
  command menu `D_00648790` / `D_00648630`, pop-ups, target gauge, sign, counter, timer and the one-shot (a
  guess) left; notice and banner centre); markers over 3D send their own environments and are not in it.
  Under `KH1_HOST_WIDE` the chain walk (`kh1_dma_hud_anchors`, dmawalk.c) shifts every XYZ X
  (`kh1_gs_xshift`, gsregs.c) of a listed environment's send and of the staging sends (`D_00351E10`) after it
  by the margin (82.8 px = 1325 sixteenths at 960 x 544), so `gsstate.py --extents` shows the moved
  rectangles; gsregs_test +5 checks; the fake disc draws no HUD. A renderer must read the HUD
  environment's full-canvas `SCISSOR_1` as the whole view. **include/platform/view.h** gains `PLAT_VIEW_W`,
  `PLAT_VIEW_GX0 / GX1` (512, `0x7000`, `0x9000` on the PS2): the menu blur, spin, sway, depth blur, the
  post-copy flash and opdma's full-width band use them; the static full-screen packets are listed for the
  renderer's stretch (renderer-spec 5.4). **tests/selftest.sh runs viewcheck.py** (0 ulp with IEEE rounding)
  when the ELF is in the repo root. **All 677 out/build objects bit-identical**, the float ELF the same (no
  float-untested row); abicheck / relcheck / walkcheck / countcheck / layoutcheck 0, indcheck as before.

- **Session 91** (static + host, vita-port-plan 5.1ae, renderer-spec 5.3.1 and 5.4): **the drawn
  rectangles, the camera matrices in C, the wide switch.** **`gsstate.py RUN.txt --extents`**: the drawn
  rectangle per send in target pixels (host/null/gsregs.c keeps each draw state's vertex extent less
  `XYOFFSET`; draw lines end in `, xy X0 Y0 X1 Y1`); a send from the HUD's staging buffer `D_00351E10` is keyed
  by the environment sent before it (`D_00651C00 ch2 > D_00351E10 ch2`), with 5.3's anchor; on the fake disc
  only the clear, frame copy and flash (full screen). **host/port/view.c** = `func_00110618` in C for every
  port (the session 12 draft's maths; session 6's w6_02 has m5 wrong), linked on the host instead of the
  draft (census.py `HOST_TWINS`). **`tools/host/viewcheck.py`** (new) runs the original's 268 instructions
  from the ELF in an interpreter: **bit-identical** to view.c with IEEE rounding on 13 argument sets (2 ulp
  with the EE's round-toward-zero). **`KH1_HOST_WIDE=W:H`** (`1` = 960:544): only the two frustums' x scale
  change (x 0.7556), the markers' bounds 1709.2 .. 2386.8, objwin's -82 .. 594 through
  **include/platform/view.h** `PLAT_VIEW_X0 / X1` (0 / 512 literals on the PS2). **No other frustum in the
  main ELF** (journal, party menu, objwin, shadow, lens grid: view -> screen only; `D_002BC140 / 144` are the
  effects' / sound listener's camera pointers, the Gummi overlay sets them). **Bit 35's plan**: records'
  `flags & 0x20000` in roomobj.c's lists after `func_00132c70`, the object-script halfword `0xA30B` (table 0
  entry 163). **every out/build object bit-identical**, the shift ELF the same (no float-untested row).

- **Session 90** (static, vita-port-plan 5.1ad, renderer-spec 5.3.1 and 5.4): **the culls under a wider
  view, the HUD's anchor table, movies.** renderer-spec 5.4: **no CPU cull reads `D_002BC020`** (it is
  renderer A's 1636 x 303 px guard box, not a frustum; 2.2 and 5.3 corrected). `func_00110618` builds six
  matrices; the culls use the two **exact 4:3 frustums** `D_002BBE60` / `D_002BBEE0` (as `D_002BBFA0` /
  `D_002BBFE0`, 320 x 229 at scrz): the grid (`func_00107548` -> `func_00107ab8`, 8 box corners, no cone),
  props `func_00114a38`, actors `func_00135bb0`, shadows `func_00127c20`, ppp effects `func_001812d0`
  (off-screen ones also stop updating) and the party warp `func_00169f28` (picks an off-screen point) all
  go through `func_0024edf0`. **Hor+ = one constant** (the x 320 times 1.3235 in `func_00110618`); the
  projection stays. **Bit 35 of `x370` ("drawn") feeds gameplay** (flag-`0x20000` actors' motion, action
  25, script command `func_0012a030`, the lock-on line of sight). Lock-on has no screen test.
  `func_00121000` is not a cull (P18 flag). Markers `func_00249580` (`D_00469F90` / `D_00469FA0` =
  1792..2304 x 1856..2240) and objwin `func_0010b390` (0..512 x 0..384) need port-side bounds.
  **renderer-spec 5.3.1**: the HUD's sprite files (`UiFile`, rectangles in target pixels) plus each
  drawer's origin give every part's rectangle without a boot: Sora's gauge (360,257)-(503,375) right /
  bottom (`D_00454600`), the party gauges top right, the command menu (16,260) left / bottom, notice and
  banner (160,344) centre / bottom, pop-ups from (16,16), the counter (25,238), the timer; **the target's
  gauge is fixed at (16, 24 / 65 / 80), not a marker** (5.3 corrected). vita-port-plan 5.1ad **movies**:
  `func_00111020(n)` loads dkmovie.x to `0x00F20000` and calls `entry(0, n)`; commands 1-9 (start, status
  2 ready / 4 ended, width, close, stopped, the band's flags, frozen step, frame count / current);
  started by gamestate.c states 11-13 / 16-18 (asked for by dktitle.x, inferred) and script opcode 24
  entries 584 / 585 / 489 / 490; names `D_0046A058` (opn, end, end2, demo, end3, ffx2 .dat); no libmpeg
  in the main ELF (the decoder is in dkmovie.x); a `PlatMovie*` layer drafted (sceAvPlayer on re-encoded
  files or a software MPEG-2 decoder; licence open). Only docs/ changed: **every out/build object
  bit-identical**, the float ELF the same (no float-untested row).

- **Session 89** (static, vita-port-plan 5.1ac, renderer-spec 5.3): **the 2D layers' space, vibration,
  the CIRCLE / CROSS swap.** renderer-spec 5.3: every 2D drawer (windows, text, field text, HUD, notices,
  menus, markers projected from 3D) draws in 1/16 pixels of the 512 x 384 target at `(0x7000, 0x7400)`;
  outside it only the post-copy flash, the system-message band, fade.c's ending and the 640-wide movie
  buffer. **The target's pixels are square** (448 lines were NTSC's), so the plan is **4:3 at about
  725 x 544 (scale 1.4167) between bars first**, one affine map on every GIF-path draw, and later a hor+
  option (clip matrix `D_002BC020` / viewport `D_002BBF60`, full-screen passes widened, a port-side HUD
  anchor table, markers not anchored; **renderer A's grid visibility `func_00107548` must be checked
  first**). winmenu.c's y getter / setter use 0x7000 (no main-ELF caller). vita-port-plan 5.1ac:
  **vibration**: type-20 patterns, `{time, level}` ramps per motor, small motor on at >= 128, large 0-255,
  libvib's 3-profile packing; **the ELF's 7 patterns decoded** (hit reactions use 0 / 1 / 5 / 6; 2-4
  unused in the main ELF), event and object-script patterns from the disc; vm_lib.c `func_001d39b0` was
  commented as a sound, it starts a vibration (comment fixed); the PS TV wrapper's `SceCtrlActuator`
  mapping and a zero when the game stops sending. **The swap**: swapping 0x2000 / 0x4000 in
  `PlatPadRead` moves every confirm / cancel (81 raw cancels in 28 menu files, the window confirm
  `func_001fe5a0`, the action table, selector, framectl); padrec's replay / script stay right above it.
  **What does not follow**: the ELF's window font has no face-button icon (only L1 / R1, cells 8 / 9;
  font sheet decoded), so the message font's button glyphs and the disc's HUD / menu textures need
  port-side swaps, read from the real disc. Only docs/ and two src comments changed: **every out/build
  object bit-identical**, the float ELF the same (no float-untested row).


- **6,979 / 6,988 functions matched** (docs/progress.md). No matching work in sessions 27-94.
- **Nine default float builds are unbooted**: sessions 30 (2,100 float), 31 (2,047), 32 (2,043), 33 (2,032), 34
  (2,049, unchanged in 35 to 58), 59 (2,053, unchanged in 60 to 68), 69 (2,043), 70 (2,041; sessions 71 to 85
  left the float ELF's bytes the same; so did 87 to 94) and **86 (2,041, the current default: D_0063F640 inside the floated
  sound status block)**. Session 69 made 21 objects one definition (vita-port-plan 5.1i): 10 objects that floated in place as
  parts of a run now float whole into the float area (the shop / list windows D_0062F6E0 / D_0062F790 / D_00630460,
  the ppp matrices D_00615E70 / D_00616000, D_0052EB50, D_00551700, D_00575900, the timer sets D_006692F0 /
  D_00669320) and 20 neighbours are pinned. Session 70 made 6 more one definition (5.1j: the command menus
  D_00650120[7], the object slots D_00550400[64], the DMA packet area D_00573AC0, the hit records D_0054C440 with
  areabox's groups, the list callback D_006305C0, the ability counts D_00642C70): only 2 newly pinned (D_00642C70,
  D_00650DD0), nothing newly floats. The undo of each is reverting that session's commit (float-untested.md rows 69,
  70, 86). docs/float-untested.md lists every change since the last booted build (KH1_F29_N) and the switch that undoes
  each. Session 59 released 4 names (`--no-fmt-read`, low risk); session 34 released 19 (bisect order
  `--no-hix-join`, `--no-widen-heads`, `--no-likely-slot`).
- **Register passthrough** (portability.md rule 10; vita-port-plan.md §5.1c-§5.1e): argcheck lists **0 short
  calls and 3 value uses**: func_001ffaf0 (winmenu.c), func_002040a0 and func_00206710 (winpart.c) have no
  caller in the main ELF; check them against dktitle.x's calls into the main ELF. BENIGN keys may name the
  caller (a third field).
- **Calls through pointers** (`python3 -I tools/host/indcheck.py [--all] [--tsv out/host/indcheck.tsv]`,
  vita-port-plan.md §5.1e-§5.1h): **0 `?`, 0 DATA, 0 OPEN, 0 `?def`** (session 68). 242 rows: 117 OK, 42 READ,
  70 OVERLAY, 13 CLANG (gcc nested functions in ppp/keshptail(x), kethdraw; a draft's `$10`). Session 68:
  ASM_TAKES holds the parameters of assembly / SDK targets read by hand (FlushCache, iFlushCache, the libvu0
  RotMatrix trio, SyncDCache), and a piece called as one pointer reaches its first `.word` only. Session 67: PSys.mods are &D_00370200[id] (the words
  pppRelocProgram relocates), so pppsys.c's system steps call PppClass fn10 (never set) / fn14 / fn18 (all
  take nothing); the Range52 is func_0010f558's choice list (msgwin / list / shop, FIELD_SAME). The 70
  OVERLAY rows (vm_lib's 41 hooks, mcstep's request hook 13, partyctl's cb44 4, textwin's x0 2, the setters
  func_001c06c0 / func_001468f8 / func_0012cab8, D_00304B6C, D_002E27D4, D_00616220, func_0011f228, vmath's
  handler stack, gumisave's two overlay entry calls) are for the dktitle.x / overlay check.
- **Argument classes** (portability.md rule 11): `python3 -I tools/host/abicheck.py` (text) and indcheck
  (trees) both 0. Run both after any new declaration. indcheck: **0 CLANG** (session 69: the three nested-function
  files are CLANG-READ, read from their gcc host objects, which have no `call *`).
- **DMA addresses** (portability.md rule 13): `python3 -I tools/host/dmacheck.py` at **0 rows** (run it after
  touching packet code; `--list` for the sends).
- **PS2 addresses as numbers** (portability.md rule 14): `python3 -I tools/host/abscheck.py` at **0 rows**, code
  and data (after `make host-census` and a `make shift`; run it after matching or editing code that names an
  address, or after a data change; `--all` lists the decided data words).
- **Layout dependencies** (portability.md rule 12, vita-port-plan.md §5.1i-§5.1k): two checks, both at **0 rows**;
  run both after any data change (a new row is a host crash waiting: opdma in 64, the notice in 68 were found by
  crashing). `python3 -I tools/host/layoutcheck.py` (after `make shift` and `make host-census`) reads the linked
  PS2 ELF: code that reaches past its variable's host definition (10 false positives in its REVIEWED table).
  **`python3 -I tools/host/relcheck.py`** (session 70, after `make host-census`) reads the host objects'
  relocations, where the C name is kept (session 71: also the PS2 objects and the unlinked drafts; `--no-ps2`,
  `--no-drafts`): it finds C that names one variable and lands exactly on the next
  (`&D_00650120[6]` = D_00650C00, invisible to layoutcheck); its REVIEWED table holds 39 compiler patterns (loop
  ends to a field, folded `a[i - 1]`); `--all` adds the references exactly at an end (read in 70: loop ends).
  census.py keeps names with no C definition at their PS2 distances (out/host/defs_host.c blocks) and aliases
  names inside a C definition into it (out/host/aliases.ld); shift_ld.py lets such a field name follow its floated
  object. layoutcheck `--all`'s 733 unbounded index rows were sorted in session 70 (5.1j): an idx-next row is any
  index the analysis cannot bound, so reading does not shrink the list; relcheck found the real splits instead.
  An `s32 [5]` at a 4- but not 8-aligned address fails the link (ee-gcc pads it): merge with the name before.
  **`python3 -I tools/host/walkcheck.py`** (session 86, no build needed): pointer walks that run on from one loop
  into the next, which neither check sees, and since session 87 index walks and builder results (0 WALK, 42 REVIEWED); census.py's HOST_TAIL pads a piece on the host only.
  **`python3 -I tools/host/countcheck.py`** (session 88, no build needed): counts kept in a global, stepped in one
  function and used as an index in another (0 COUNT, 37 REVIEWED; the DATA rows wait for high-water marks: `KH1_HOST_COUNTS=1` prints them, session 96).
- **Null platform**: PlatMcSync answers done with "no card" (-10) and PlatMcGetInfo writes its outputs;
  **host/null/pad.c** (session 87): one pad connected, nothing pressed (`KH1_HOST_PAD=none`: no pad,
  `KH1_HOST_PAD=FILE`: a script; vita-port-plan 5.1aa). PlatSifCallRpc hands the sound
  RPCs to **host/null/sound.c** (session 86): RPC 0x30 answers 1; RPC 0 keeps the status block's address; a
  frame after a queue (RPC 30) the bank transfers it held (commands 3, 4, 0xB, 0x28) come off the +0x1F00
  count (D_0063F540: boot waits for it non-zero, the sound tasks / summons / soft reset for 0); SE and
  stream `used` entries are set on a play and cleared on a stop, after a fade or by time (sound-spec 5);
  the disc-error word and the message buffer read 0. `KH1_HOST_SND=trace` prints the commands,
  `tools/host/sndlog.py RUN.txt` sums them up.
  **DMAC interrupts** (session 68): the null platform keeps PlatAddDmacHandler's handlers, a status bit per
  channel (set by PlatDmaSend / PlatDmaPutVif1Chcr with STR, cleared by PlatDmaPutStat) and the enable mask, and
  runs an enabled channel's handlers outside any handler: mdlgs.c's GS task list ends (D_00559DB4) and
  func_0015ef60's frame-end wait returns.
  **Threads** (session 67, host/null/threads.c): the game's threads run as ucontext coroutines (a thread runs
  from the main thread's PlatWaitSema until it waits; semaphores count; PlatIReferSemaStatus reports the
  waiters). This runs src/util/thread.c's loader worker: every func_001204a0 file load reads on it (before,
  a load's result stayed -1 for ever).
- **Host build (phase 5)**: `make host-census` links out/host/kh1-host (all 512 game files + the 8 drafts).
  `KH1_HOST_ISO=PATH out/host/kh1-host` reads the user's own disc image by sector (host/port/cd_image.c;
  `KH1_HOST_TRACE=1` prints the searches and reads, `=4` (session 77) each send's GS state values for `tools/host/gsstate.py`, `=5` (session 79) also each send's draw states from host/null/gsregs.c (`gsstate.py --draws`), uploads (`--uploads`, session 80) and render targets (`--targets`, session 81; Z formats decode since session 82; `tools/host/drawkeys.py` lists the draw list's keys, `tools/host/sendorder.py` the sending tasks; session 83: the list nodes, `gsstate.py --nodes`; session 84: `KH1_HOST_DMAC=defer` leaves the draw list to the replay), `=2` also walks each DMA chain and reads its data as GIF packets / VIF codes / PATH2, with each send's GS registers (sessions 74-76, host/null/dmawalk.c; `tools/host/dmawalk.py` is the offline twin for the static chains), `KH1_HOST_FRAMES=N` caps the run, default 600; session 94: `KH1_HOST_SHOT=W:H[:target][:DIR]` writes the GS model's display after each frame copy as a PAM). On
  tests/host/fake_disc.py's image (now with a one-sector "dktitle.x" in KINGDOM.IDX) the boot reads SYSTEM.CNF,
  KINGDOM.IDX and dktitle.x (frame 2, on the loader thread) and calls D_00F20000(0, 0), which faults:
  main.c prints "fault at PS2 0x00f20000 in the memory map" and the caller. **`KH1_HOST_OVL=stub`** (session
  68, a test switch in host/null/main.c) answers the entry with 0 instead (the main loop then stays in the
  title's state 1); **`KH1_HOST_OVL=stub:2`** also asks for state 2 with func_00109558 (a guess at the title's
  "new game"), and the boot then loads dh.wdt, amusic/sedh.dat, dh00_01.bin, dh00_01.img, dh01.ard (Dive to the
  Heart) and, on the fake disc where those files are missing, ends in func_00132790 (roomobj.nostrict.c) on
  data that is not there (reached from func_001136a8 through the sound and file queue; under gdb, `handle SIGSEGV
  nostop pass` skips the stub's own fault). The stub does not work under valgrind (valgrind runs the overlay's bytes). **Valgrind: 0 errors** up to the
  fault (session 73 again; `apt-get install valgrind libc6-dbg:i386`; under valgrind the fault is a SIGILL). **Not yet run on the
  real ISO** (it is on the Mac): it should stop at the same call. opdma.c's three GS tag lists are one
  definition (D_0061EEA0[0x140]); session 68 made the notice's four sprite sets one (src/hud/notice.nostrict.c
  `D_00656230_sets[4][9]`): func_00243a90's fill ran over D_006561D0 on the host. Sessions 69 and 70 found the rest statically
  (layoutcheck, relcheck: 27 more objects one definition); the stub:2 run still ends in func_00132790 on the fake disc.
- **dktitle.x**: tools/ovl/inventory.py is ready (functions, main-ELF calls and data, code / data split;
  `--selftest` on the main ELF finds every layout.tsv start). Not run: the file is on the Mac. §5.2 has the plan
  to decompile it (toolchain check on 5-8 leaves first).
- **Original source names** (docs/elf-notes.md): ttlib/ui_gauge.c, ttlib/ui.c, src/decode.c, src/sa_task.c, with
  their ranges; none below 0x001c08e8 so far.
- **Helpers:** `python3 -I tools/shift/s50move/group.py src/DIR/NAME LO HI` drafts modules per flag mode,
  `tools/shift/s37move/fcheck.sh base|NAME` (compare float_covered.txt as a sorted set; run `base` on a clean tree
  before any edit, and never run `make` while it builds; a syms line naming a func_ alias that went away is
  expected after a rename), `tools/shift/cover_check.py | grep NAME`, `tools/checkfile.py FILE -v`,
  `tools/shift/s31types/s31_warndiff.py FILES` (compares with HEAD: commit-free check). Data definitions: compare
  `cut -f2 out/gen/data.tsv | sort` with the session's base (saved before the first edit). reach_check alone (40 s,
  no build): `python3 -I tools/shift/reach_check.py --elf SLPS_251.98 --overlays EMPTYDIR --out F.txt` (after a
  `make shift`; the anchors come from out/shift/kh1-shift.linked.elf). Host: `make host-census` (or
  `python3 -I tools/host/census.py --exe`), then `out/host/kh1-host` (gdb works: objects have -g; `gdb -batch -ex
  "break kh1_host_vblank if frames >= N" -ex run -ex bt out/host/kh1-host` shows where frame N is); `--files
  CAUSE` / `--show FILE`; out/host/undefined.txt. `python3 -I tools/host/argcheck.py --tsv out/host/argcheck.tsv`
  lists the passthrough calls, `python3 -I tools/host/abicheck.py` the argument-class mismatches. `python3 -I tools/host/vu2c.py FILE LINE` turns one VU0 asm statement into PlatVu0
  calls. `python3 -I tools/host/walkcheck.py` lists pointer walks across loops, `tools/host/countcheck.py` counts across functions, `python3 -I tools/host/hudcheck.py [-v]` the HUD's environments against hudanchor.c's tables (session 93) and each staging send's environment (session 94), `python3 -I tools/host/viewcheck.py [--wide 960:544]` checks host/port/view.c's camera matrices against the ELF's func_00110618 (needs the ELF and gcc -m32), `python3 -I tools/host/sndlog.py
  RUN.txt` a run's sound commands (with `KH1_HOST_SND=trace`). A quick "did any object change" check: `find out/build -name '*.o' | sort | xargs sha1sum` before the
  first edit and after (sessions 62 to 66 did this), or build origin/main in a `git worktree`
  (symlink tools/toolchain, copy the ELF) and `cmp` every out/build .o.
  **`git fetch origin main` first**: the container's origin/main can be stale. A fresh container needs `apt-get
  install libc6:i386 libstdc++5:i386 binutils-mips-linux-gnu gcc-multilib gdb` (indcheck needs clang, present in the cloud image) (after `dpkg --add-architecture
  i386`), `make toolchain`, the ELF, a plain `make shift` and tools/shift/data_owners.py before `fcheck.sh base`.

## What is left (9 functions)

Best drafts are in nonmatchings/session23-match/ and older (table in its NOTES.md). Counts are LCS words.

1. **1-4 words**: 001fd858 (1, reorg liveness), 001f2630 (1, nofill), 001f1fc8 (2, nofill), 00265608 (4, closed).
2. **15-24 words**: 001c62a0 (15), 00200e28 (24).
3. **Large**: 00110618 (93, FP register permutation), 0010d470 (170, jump2 cross-jumping), 001636d0 (394, gcse build).

## Session 103 plan (at most 3 workers, docs/workflow.md "Resource limit")

1. **Boot test (only with the Mac, from Monday 2026-10-26)**: run a plain `make shift`, tools/shift/data_owners.py,
   stage out/overlays from Downloads/kh1-test/ovl, `make shift SHIFT_MODE=m12 SHIFT_FLOAT=1`, copy the ELF to
   Downloads/kh1-test/s103 and /mnt/project-files/kh1-runtime/s103, patch KH1_BIG.iso, and run the route in
   docs/float-untested.md (include a shop, the in-game menu: the top menu, the item, equipment, abilities (session 70
   merged its counts), customize, status, config and journal pages with each journal section, changing a config
   option, using an item, equipping a weapon, a save point (save to a card, overwrite a save, change the party:
   **session 87: after the save point's party choice, does a member appear who was not chosen?**
   savemenu.c `func_00228588`), loading a save from the title screen, a new game's name entry if one is reachable,
   buying and selling in an item shop and a Gummi shop, the Gummi garage (session 87 read its lists), the Moogle's
   synthesis, a list that pages (session 70 merged the list callback), the title screen left idle until its demo,
   a battle with the HUD (the HP / MP gauges, the command menu including its second kind-4 menu (session 70:
   D_00650120[6]), lock-on and the target's gauge, damage numbers, an "obtained" notice), the world map's gauge, a
   minigame with a timer or score if one is near, a level-up, a Trinity mark if one is near, a summon if one is
   available, enemy drops picked up, the pause, a game over and its continue, a room change and a world change, a
   movie, music and sound effects throughout (session 86 moved the sound status block's message buffer), a
   controller pulled out for a second (the system-message band, renderer-spec 4.15), a scene with the screen
   spin if one is near (renderer-spec 4.16: the picture turning into itself), **session 88's effects** (renderer-spec
   4.17: the blur when the menu opens and closes, an event's letterbox bars and fades to black and white, a room that
   sways (underwater is a guess) and whether anything drawn after it looks wrong (the Z buffer holds colour then),
   a depth blur or lens bulge if one is near), **the controls of 5.1ab's table** (SELECT's first person, L2 / R2
   camera and target cycling while locked on, L1 shortcuts, R3), **sessions 91 to 102: nothing new to see on the PS2 (the float ELF is the same)**, **session 90: an object window whose speaker is off screen (objwin's tail `f6`), a movie (opening or the title's demo: skip it with a button and with START), the party gauges' place (the data say top right)**, **session 89: a pad that vibrates when the player is hit** (PCSX2's force feedback, if the user's pad has it; renderer-spec 5.3 needs nothing from the boot), and anything using atan: camera, lock-on). If it breaks, bisect: session 86's commit first (revert its data_0063.s / bss_0063.c change), then
   session 70's (revert it), then session 69's (the one-definition merges), then session 59's `--no-fmt-read`, then
   session 34's switches. Move what boots into docs/shiftable-plan.md and clear docs/float-untested.md. Note what
   the boot shows about the "(a guess)" modules and rename the ones it settles. Without the Mac: skip.
2. **Host run on the real disc (with the Mac)**: ask once for the user's ISO (Downloads; the unpatched original,
   not KH1_BIG.iso) to be copied into the container's scratchpad (never into the repo or project files), and run:
   `KH1_HOST_ISO=... KH1_HOST_TRACE=1 out/host/kh1-host`, once under valgrind, `KH1_HOST_TRACE=2` (every DMA chain
   walked: a chain leaving host memory or ending inside a packet is a bug; record the windows' per-draw packets),
   `KH1_HOST_TRACE=5` with `gsstate.py RUN.txt --sends --draws --uploads --targets --nodes` (compare with
   renderer-spec 3.2 / 4.7-4.16 and 5.1; every node in drawkeys.py's map; the targets `0x1A00`, Z24 `0x0E00`, the
   display buffer, `0x3A00`), `KH1_HOST_TEXDUMP=DIR` (look at the decoded message font: readable glyphs settle
   gsmem.c's swizzle and 4.9's 2-bits-a-layer inference), then **`KH1_HOST_OVL=stub:2`** (Dive to the Heart's
   files are on the real disc: record how far the room parse func_00132790 gets), and the `KH1_HOST_TRACE=5` room
   run once more with `KH1_HOST_DMAC=defer` (same `--nodes` order expected; pending only at frame-end waits; the
   texture steps' dir-2 copies in `--uploads`; key 50000's P3 upload and chain 3, `D_0047E220` / `D_00482260`,
   with its tags in map section 1). Run each with `KH1_HOST_SND=trace` and `python3 -I tools/host/sndlog.py
   RUN.txt` (the boot's bank transfers, the title / Dive to the Heart music starts, SEs played and ended, no
   frame near 256 records; the transfer count back to 0). **Session 87: the pad is connected by default now**;
   compare one run with `KH1_HOST_PAD=none` (it should sit in the "no controller" band from frame 32), and once
   the room run gets further, try a `KH1_HOST_PAD` script (START at the title, CIRCLE, the menu with
   TRIANGLE?; session 88: start from tests/host/pads/title.txt and move its frames to what the run shows). Read the
   message files' code 11 digit counts (`dig[12]`, 5.1aa). **Session 89: find the message font's button glyph codes** (circle, cross, triangle, square, L1 / R1 ... in the decoded font and the message files) **and the disc's HUD / menu textures that show a button** (`KH1_HOST_TEXDUMP`), for 5.1ac's swap lists; record the HUD draws' rectangles for renderer-spec 5.3.1's anchor table (**`gsstate.py RUN.txt --extents`**, session 91: one row per HUD part keyed `ENV > D_00351E10`; check each row of 5.3.1, the kind-3 gauge, the one-shot and the minigame timer's x / y). **Session 91: run the room once with `KH1_HOST_WIDE=1`** (the culls let more through: compare the draw-list node counts with and without it); **session 92: with `KH1_HOST_WIDE=1` and `--extents` each HUD part in host/port/hudanchor.c's table should move by -82.8 / +82.8 px (centre ones and markers not); a part that moves wrong or a HUD environment missing from the table is a table fix**; **session 93: every full-screen send (the clear, display clear, frame copy, fade, letterbox, the copies) at -82.8 .. 594.8 with "(scissor: the view)", and a full-screen send that stays 0 .. 512 is a missing `host/port/fullscreen.c` row**, **session 94: one run with `KH1_HOST_SHOT=960:544:DIR` (DIR in the scratchpad, never committed; look at a few frames: the uploads and 2D sprites the model holds, pillarboxed; session 95: the clears, fades and letterbox now show their colours, and the shot line counts the flat sprites) and, if the lens grid is reached, its `CLAMP_1` MAXU 676 under `KH1_HOST_WIDE=1`**, and **list the actors with spawn flag `0x20000`** (renderer-spec 5.4 "Bit 35's readers": gdb after `func_00132c70`, each of roomobj.c's four lists' 0x78-byte records with `flags & 0x20000`) and scan the room's object scripts for the halfword `0xA30B` (`func_0012a030`). **Session 88 / 96: record the high-water marks of countcheck's
   DATA rows** with **`KH1_HOST_COUNTS=1`** on every real-disc run (session 96, host/null/counts.c: printed at the
   end; an "OVER" row is a real overrun, on the PS2 too: write it into countcheck's REVIEWED entry; the collision
   count is a lower bound). **Session 96: the display shot now goes through the frame copy** (the target's
   contents point-sampled): look at a `KH1_HOST_SHOT` frame of the title and of Dive to the Heart (**session 97**: under `KH1_HOST_WIDE` the display shot starts at canvas x 82.8 by design; compare one `:target` shot; **session 98**: with `--extents`, the stored frame back `D_002B66B0` (capture.c, a fade from a stored frame: the menu or a world change?) should now be at -83.5 .. 594.1; note which scenes send it, and whether the spin copy / strip or the copy into the Z area appear; **session 99**: every full-screen send fscheck.py lists should show at -82.8 .. 594.8 under `KH1_HOST_WIDE`, the half-size captures `D_002B6760` / `D_002A5A90` at the view's half: open the menu (the blur `D_002A4B60` / `D_002A4DD0`), a world change (the cross-fade `D_002B65E0`) and, if reached, an event's depth blur and the shaped wipe `D_002A6A40` / `D_002A6AA0`; the display shot now shows canvas 0 .. 512 unshifted; **session 100**: the menu's backdrop gradient at -82.8 .. 594.8 (menubg's four, built in C; not a send, so in `--draws`), and, in a scene with vm_lib's screen effects (a zoom, cross-fade or tint of the stored frame), `D_003DAE30` / `D_003DAF60` / `D_003DB050` at -82.8 .. 594.8; **session 101**: the image loads now reach the model, so `--uploads` lists them (timload, roombg, objwin, hud, fldtext, opimage, mdlpkt, capture's halves) and `KH1_HOST_TEXDUMP` should show more decoded textures; a store now returns the model's bytes (menubg's backdrop colours, the blur's empty test); in a menu with a full-width rule (top menu, journal, load screen) the rule's flat sprite at -82.8 .. 594.8 in `--draws`; if a lens flare is reached, record its key's e / f (the box `e x 8` by `f x 4`, at most 4096 pixels); **session 102**: a flare's Z24 store of a box the draws wrote now reads 0, so the flare shows at full strength on the host ("all visible"); a flare that is dim or hidden means the Z area held uploaded or copied bytes there: note the scene). Fix host-only causes the way
   sessions 63 to 70 did (platform answers, layout dependencies as one definition with layoutcheck, relcheck and
   walkcheck at 0, the PS2 ELF byte-identical).
3. **dktitle.x (with the Mac)**: copy Downloads/kh1-test/ovl/dktitle.x into the container (never commit it), run
   `python3 -I tools/ovl/inventory.py dktitle.x --tsv out/ovl/dktitle.layout.tsv`, record the counts (not the bytes)
   in §5.2, then the toolchain check of §5.2 step 2 on 5-8 small leaf functions. Check argcheck's 3 value uses and
   func_002066b0's BENIGN entry against dktitle.x's calls into the main ELF, and indcheck's OVERLAY rows
   (does dktitle.x call the setters func_001c06c0 / func_001468f8 / func_0012cab8 or write vm_lib's hooks? what do
   the targets take?). Does it call func_00109558, and with which states (session 68 guessed 2 = new game)? Does it
   call drawlist's flushes (func_00237f20 / func_002380c0 / func_00238258) or the push func_002376c8, gspkt.c's
   func_002372e0 / func_00237318, and which of the 16 sound entry points with no main-ELF caller (sound-spec 3)? Session 95: does any overlay call prim.c's senders `func_00238440` (3D lines through `D_00648070`), `func_002384e0`, `func_00238768` or `func_002386c0`, and under which environment?
   Does dkmovie.x (the same folder) store 2 to `D_002BBE04` (the movie copy from `0x118000`, renderer-spec 4.15),
   and does any overlay read the field parity `D_002BBDE8`? Session 87: does any overlay call func_001fb3e0 /
   func_001fbb50 (wintext's number draws with no main-ELF caller) and with which digit counts, or store 1 / 4 to
   `D_002BBE04` (the screen spin)? Session 88: who calls padrec.c's recorder / replay / button script / idle timer
   (`func_00233650` ... `func_002336e8`: the title's demo?), memstack.c's push / pop (`func_001bb480` /
   `func_001bb4b0`, depth 4), pause.c's `func_00114068` (the 2 px menu blur), and does anything read the pad's
   second repeat word (+0x14) or `D_002C5C2C`? Session 89: does any overlay start a vibration (`func_00176ba8`, `func_00147790` with patterns 2-4), set bit 16 of `D_002C5978` (vibration off), or call winmenu.c's y getter / setter `func_001fd268` / `func_001fd278` (0x7000, not 0x7400)? **Session 90: dkmovie.x** (the same folder): run inventory.py on it too and check vita-port-plan 5.1ad's "To confirm" list (commands 0-9 and their returns, its stores of 2 to `D_002BBE04` and to `D_002BBE18`, whether n indexes `D_0046A058`, how a title skip is seen, whether it calls `func_001111b0`, sceIpu / sound commands used); does any overlay build its own frustum (5.4 open; session 91: does the Gummi / world map code call `func_00110a48` or `func_001bb858`, and with which matrices)? Without the Mac: skip.
4. **Static, without the Mac**: (a) **the user's answer on the full-width rules** (session 101's card, still
   unanswered at session 102): "keep them 4:3" means deleting the `#ifndef KH1_PS2` block in
   winpart.nostrict.c's `func_00206130` and renderer-spec 5.4 "Session 101"'s paragraph (say so in a new
   vita-port-plan 5.1 entry); (b) **a host test of the flare's count**: link kelnscls.nostrict.c's
   `func_00192958` with the null platform in a selftest case (a made-up `FlareObj`, the Z buffer drawn by
   `kh1_gsmem_draw`) and check `f7C` stays at full strength, then with a Z box uploaded nearer than the light
   and check it dims by the covered share (vita-port-plan 5.1ap); (c) `KH1_HOST_DMAC=defer` as the default,
   argcheck's 3 value uses and the callers of prim.c's senders still wait for the Mac.
5. **Matching (optional, 1 worker)**: only with a new idea (001c62a0 or the nofill pair).
6. End with `make progress-update SESSION=103`, refresh the per-phase table in docs/progress.md (between its
   `<!-- phases -->` markers; the generator keeps it), commit, open a PR, and refresh this prompt (keep the
   Mac note accurate).
7. **Once the PR is merged, message the coordinator to start the next session** (session 104) with this
   prompt: the user wants each session to start the next one without being asked.
