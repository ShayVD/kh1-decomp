# The native renderer (2026-10-30)

Port code, not game code: nothing here changes kh1.elf or src/. The goal is a steady 30 fps in Dive to the
Heart on a Vita (15.7 on main 9c32dca), by drawing from the game's own records with the GPU's vertex shader
instead of running the VU1 programs on the A9 and decoding their GIF output on the GS worker. renderer-spec.md
section 5 ("Mapping to a modern API") is the plan's outline; this file is how the port gets there in stages,
each behind `renderer=native` in config.txt with the GS path as the fallback and the default.

## Where the time goes today

One draw of renderer B or A, end to end (vita-build.md "The VU1 programs on the Vita, timed" and the later
speed sections):

1. **Game thread**: VIF1 unpacks the chain's records into VU1 memory, then the translated VU1 program (vu1.c /
   vu1_nat.h) transforms every vertex: a 4x4 matrix, 1 / w, STQ x Q, the cross product for the ADC bit, FTOI4,
   and writes a GIF packet. In the Dive this is ~750-1,000 ms of A9 time per 2 s (P0 the map's strips over half,
   P13 skinned characters late in the run, P11 / P18 ~160-260 ms, P4 ~100 ms).
2. **GS worker**: each XGKICK's packet is walked tag by tag (gsregs.c), every vertex through the register file,
   gsmem's draw bookkeeping, and pipes.c's primitive assembly.
3. **GPU thread**: every vertex converted again (vertex.h `kh1_vertex_of`), batched per triangle (batch.c),
   then recorded into GXM calls.

The native path removes 1's arithmetic, 2's per-vertex work and 3's per-vertex conversion for the programs it
knows: the game thread only copies the records it was going to read anyway, and the GPU does the transform.

## Stage 1: P18 (this branch)

P18 is renderer B's rigid, flat-coloured, back-face-culled program (renderer-spec 2.3): Sora and most of the
Dive's B models. Its record stream (renderer-spec 2.3, vu1_nat.h `nat_18`): op 0 loads a matrix into slot 0 / 1
/ 2 (vf05-08 / vf12-15 / vf19-22), op 1 is a GIF tag and n vertices of (normal with the slot in w, position,
STQ), anything else ends the run. A census of the Dive to frame 7000: vi12 always 0x0ff0 (F 255), vi13 0x8000
(the cull on), vi14 1, the tag NREG 3 FLG 0 REGS STQ / RGBA / XYZF2, p.w always 1, t.z always 1; ~4 matrices and
~12 records a run, ~4.4 vertices a record, a slot often reloaded mid-run.

**The flow** (natdraw.h has the payload):

- vu1.c `start_run`: with `kh1_vu1_draw` set and the program P18, `nd_18` (host/port/vu1_draw.h) parses the
  stream instead of running the program. It copies each matrix as loaded (VU column order) and each vertex's
  position, STQ and matrix index (a slot's matrix from before the run is taken from the VF registers), then
  hands one payload to `kh1_vu1_draw`. It writes the last loaded matrices back to the slots (the next run may
  draw with them) and leaves the program at its idle PC. Anything it does not expect (p.w not 1, more than 32
  matrices, a full buffer) returns 0 and the real program runs, so a wrong guess costs speed, not a picture.
  What it does not write: the program's output area, vf26-31, ACC, Q, vi01-07. Nothing in the Dive reads them
  between runs (the next run's set-up writes them), but a program that does would differ: that is the first
  thing to check when a scene draws wrong with native on and right with it off.
- dmawalk.c `path1_draw` queues the payload on the GS worker (`w_native`). gsregs.c `kh1_gs_native_run` does
  per record what the GIF tag would have (PRE writes PRIM, the draw is counted in gsmem with the scissor as
  its extent), so gsmem's targets, the CLUT and texture bookkeeping and the frame's draw counts stay as they
  were, and calls pipes.c's hook.
- pipes.c's recorder takes the run as it takes a strip's primitive state (`prim_state`), then queues one
  `r_native` op for the GPU thread: `kh1_nat_tris` lists the triangles, `kh1_nat_fold` folds the screen
  mapping into each matrix, `kh1_cmd_native` makes one draw command with the matrices in the uniform ring.
  One run is one draw: native commands are never batched with others (yet).
- gxmrec.c picks the native vertex program (KH1_VERT_NAT + the usual variant), gxm.c uploads `u_m` (4 rows a
  matrix, up to 32) and sets the cull mode for the draw.

**The vertex shader** (shadergen.c): `clip = F . (x, y, z, 1)` with F = N x M from `kh1_nat_fold`: N is
vertex.h's mapping of a GS XYZ to the target (XYOFFSET, the half pixel, the margin and scale, 2 / w - 1) and
depth.h's Z scale, as a matrix applied before the divide, so the GPU's divide by w gives the same place as
P18's divide then the GS path's mapping. z is clamped to 0 .. w (the GS clamps Z; a GPU would clip). The
GPU interpolates STQ perspective-correctly and the fragment shader's S / Q divide is unchanged, which is the
GS's per-pixel result for P18's STQ x Q.

**The cull**: P18 drops the triangle ending at vertex j when the cross product of its last two screen edges,
the operands swapped by the parity (h[3] + j) & 1, has a negative z. `kh1_nat_tris` lists the even ones with
their first two vertices swapped, so every triangle drawn is kept when cross(p1 - p0, p2 - p0) >= 0 in window
coordinates with y down, and the GPU's cull mode does the rest. `natcull=` picks it: 1 (CCW, the default), 2
(CW), 0 none. Which of GXM's modes matches is **not checked on hardware**: if Sora shows his inside (or
vanishes), try `natcull=2`; `natcull=0` draws both sides (the safe fallback).

**What differs from the GS path, by design**: positions are not truncated to 12.4 (within 1/16 GS pixel:
tests/host/natdraw_test.c), Z is not truncated (within one Z step), a triangle crossing w = 0 is clipped by the
GPU instead of being drawn by the GS from its wrapped coordinates (P18 has no clipping: such a triangle was
garbage on the PS2 too, and the Dive has none in view).

**Checked**: tests/host/natdraw_test.c (the fold against the GS path's vertex at two scales, Z24 / Z16 and an X
shift; the winding rule against P18's ADC at both parities; the triangle list), shadergen_test (the 7 native
variants read back and run: F x position, the clamp, the attributes passed on; the "mi" input at pad[0]), and
the host GPU stand-in (gxmcheck, tests/host/gxm_mock.c, now with clipping, perspective-correct attributes and
the cull) on the Dive side by side with the GS path (below). **Not checked**: SceShaccCg compiling `u_m[(int)
r1.x]` (if it refuses, the log says `native variants failed` and renderer=native turns itself off), the cull
mode on hardware, the frame rate.

**What stage 1 can gain**: P18 is ~160-260 ms of VU1 time per 2 s in the Dive (with P11), out of ~750-1,000,
plus its share of the GS worker's and the GPU thread's per-vertex work. It is the smallest of the three and was
picked first because its records are the simplest; it proves the path (parse, payload, fold, shader, cull) the
others reuse. Expect a few fps at most from it alone.

**The GPU is now the limit (s151b, 2026-10-30)**: the Vita log at 16.09 fps shows the SGX's work taking close
to the whole ~31 ms frame with every core waiting on it (the start-of-frame wait 7.4 ms), at the top GPU clock.
The native path as it stands moves work from the A9 to the GPU (a heavier vertex shader, one draw command and
one uniform upload a run where the GS path batched many runs' triangles together), so stage 1 alone is not
expected to raise the Dive's frame rate and could lower it. What the GPU spends its frame on (scenes and
render-target switches, overdraw from the full-screen passes, readbacks) has to be measured first; the
native path's own part is to keep its draws few (stage 5's batching, moved ahead of the other programs if
draw count shows up) and its vertex work small.

**On a Vita (native1, 2026-10-30)**: the native variants compiled (SceShaccCg took the indexed `u_m`), the log said
`renderer: native`, and ~3,700 P18 runs per 2 s were drawn by the GPU's transform in the Dive. P18's CPU time per 2 s
fell from ~216 ms (GS path, an earlier log) to ~59 ms (the parse, still counted as P18's runs). The Dive's steady
stretch (frames ~5,100-6,550) ran at 31.4 frames/s (~15.7 pictures/s, against 16.09 for s151b on the GS path): no
gain, as expected while the GPU is the limit (the start-of-frame wait ~540 ms per 2 s, the same as before). The GS
worker was busy ~2.27 s of 2.4 s there and waited 627 ms on the recording (the GPU thread). The picture looked right
(Shay, by eye: the default natcull=1 is GXM's matching cull mode).

**The GPU's frame cut (2026-10-31, host-measured only)**: vita-build.md "The GPU's work in the Dive". The ~31 ms
was mostly the SGX's tile loads and stores: 21 scenes a picture on the 3D target, one for each particle draw
(their texture uploads split the scene), ~70 MB of tile traffic. On the host's stand-in that is now 6 scenes and
~13 MB with the same pictures, and the present no longer copies or clears. With the GPU off the critical path the
Dive should become CPU-bound at ~18-20 pictures/s (the game thread's ~51 ms of work a picture in native1's log),
so the stages below, P0 first, are what is left between that and 30. The native path's own draw count matters
less now that scenes, not draws, were the cost.

## Stage 3 first: P0, the map's strips (2026-10-31, host only)

Moved ahead of P13: P0 is the game thread's biggest program in the Dive (~570-700 ms per 2.4 s on a Vita, native1's
log), and with the GPU's frame cut (vita-build.md "The GPU's work in the Dive") the game thread is expected to be
the limit. On with `renderer=native` (config.txt), `natp0=0` keeps P0 (and P4) on the VU1 programs with P18 still native;
host `KH1_HOST_NATIVE=1`, `KH1_HOST_NATP0=0`. P4 (below) goes with it.

**The flow** is P18's (above) with a payload of its own (natdraw.h, program 0):

- vu1_draw.h `nd_0`, at P0's batch entry (00c or its idle 04e): one batch is one record: the GIF tag (NLOOP n, PRE
  PRIM), then per vertex the position and its strip flag word, ST already divided by 4096, and RGBA already
  scaled by vf31 and truncated as P0's ITOF0 / MUL / FTOI0 do (a few operations a vertex, where P0 runs its whole
  transform, clip test, divide and cross product). One matrix: the screen matrix (vf01-04) times the clip one
  (vf13-16), so x / w, y / w and z / w are the VU's after its divide. F is the I register (P0's MULI.w). The run
  leaves qw48.y (the clipped fans' PRIM, from the tag's w) and the idle PC, as P0 would.
- pipes.c: consecutive P0 runs with the same matrix and header join one recorder op (a map object's batches;
  any other recorder op, a new PRIM or a state change ends it), so the Dive's frame has ~57 draws instead of 253
  (the GS path batches to 41).
- natdraw.c `kh1_nat_tris0` lists each batch's triangles twice over: those P0 back-face culls (flag bit 0x20),
  for a draw with the cull mode, in the one winding rule P18's use (P0's product is -cross(p1 - p0, p2 - p0) x the
  flag's sign), and the double-sided ones (0x02 only) for a draw with none. A flag word whose low half is 0 draws
  nothing (the strip's restart).

**Two shader changes**, both only for native draws:

- **Colour straight across the screen** (drawstate.h `lin`): the GS interpolates colour and fog linearly in
  screen space; a GPU with a real w interpolates every varying with perspective, which brightened P0's lit floor
  by up to ~13 levels. With a texture, the native vertex shader passes colour and fog times w and w in tc.w, and
  the fragment shader divides them back (a perspective-correct interpolation of a x w, over one of w, is the
  screen-linear a). P18's flat colour is unchanged by it.
- **No z clamp for P0** (the matrix index's bit 7, `pad[0] = 0x80`): P18's z is clamped to 0 .. w (the GS clamps
  Z). P0 clips at its near plane instead, and a clamp at a vertex behind the camera (w < 0) made z negative along
  the clipped edge, which then lost the floor in front of the camera (a black wedge in the picture). Unclamped,
  the GPU clips at 0 <= z <= w, the nearest P0's Z can be. The GPU's frustum clipping stands in for P0's clipper
  (Sutherland-Hodgman over its guard box, as fans): the triangles P0 drops or clips are drawn whole and clipped by
  the GPU.

**P4** (renderer A without the back-face test: the double-sided map meshes and the sky, ~120-160 ms per 2.4 s)
takes the same path (`nd_0(pc, 1)`: entered at 00c or its idle 045, every drawing flag word to the double-sided
list, the clipped fans' template left alone as P4 leaves it). `natp0=0` turns both off. KH1_HOST_NATCHECK covers it:
to Dive frame 7000, 22,876 P4 runs, no triangle drawn by P4 alone, colours / ST / F equal.

**Checked on the host**:

- `KH1_HOST_NATCHECK=1` (vu1_draw.h `nd_0_check`): P0 runs as the program and each batch's output is compared
  with the payload. Over the Dive to frame 5200 (180,000 runs): every vertex's colour, ST and F equal; of 7.8 M
  triangles, 1.97 M drawn by both, 5.15 M by neither, 625 by the program alone (each a sliver under 0.1 pixel
  whose sign the 12.4 positions round the other way), 0.67 M by the native lists alone (those P0 drops or clips
  at its guard box; the GPU clips them).
- natdraw_test `tris0` (the rule on 2,000 random triangles with each flag), shadergen_test (the native variants'
  w products), make test.
- Pictures (gxmcheck, the GPU stand-in, which now also clips at z <= w and a guard band): frames 5101 / 5103 of
  the Dive against the GS path's GPU picture: ~29 % of pixels differ, by ~6 levels on average, 306-355 pixels by
  more than 32 (texel picks where the positions are not truncated to 12.4, and the floor's near edge where P0's
  clipper interpolated colour in clip space). Frame counts the same: 5,652 triangles drawn against 5,294, the
  fragments 1,450,868 against 1,450,846.
- Host instructions, callgrind over frames 5000-5060 (one thread, trace 5): 3.69 G with the GS path, 2.09 G
  native. P0's translated program was 1.74 G of it; nd_0 and the hand-off ~0.14 G. The GS worker's kick decode
  (w_kick) 636 M to 310 M.

**Not checked**: anything on a Vita. SceShaccCg compiling the new forms (`col / tc.wwww`, `step`), whether the SGX
clips at z <= w as the stand-in does (if it clamps instead, geometry right at the camera would show where P0 clipped
it), the frame rate. If the map looks wrong with renderer=native, `natp0=0` is the first switch to try.

**First Vita runs (2026-10-31): the floor (P0) and the Keyblade (P11) did not show; fixed.** Their draws are the
lin ones (mi's bit 7 with a texture): the vertex shader hands over colour x w for the fragment shader to divide by
w, and that went through a COLOR0 varying, which the Vita's GPU clamps to 0 .. 1, so the divided colour came out
near black. The logs refused no shader and skipped no draw; P18 (w 1) and P10 (untextured) drew right, P0 and P11
did not, in the runs with each on. Now (shadergen.c) a native textured vertex shader writes its colour to TEXCOORD3
and every native textured draw is lin (cmdbuf.c `kh1_cmd_native`; P18's w is 1, so its divide changes nothing).
The stand-in (gxm_mock.c) now clamps a COLOR varying the same way: with that, the build before the fix draws the
Dive's 3D target at frame 4999 without the floor, and the fixed build draws it identical to the unclamped picture,
as are all 84 renderer=native pictures of the Dive (7,000 frames). shadergen_test checks that neither a native
textured vertex shader nor a lin fragment shader uses a COLOR varying for it.

The x86 stand-in had missed it, and so had an ARM build of it (`python3 -I tools/vita/build.py --linux-arm --gxm`,
out/armlinux/kh1-arm-gxm under qemu-arm: 48 of 84 pictures differ from x86's by float rounding, frame 4999's 3D
target in 4,121 pixels, 11 by more than 32 levels), as neither clamped.

### P11 too (2026-10-31, host only)

P11 (renderer B's unlit models with a near-plane cull and a guard band: the Keyblade and other held or field
objects in the Dive) has P18's record stream and output word for word, so `nd_18(pc, 11)` hands its runs over in
P18's payload with program number 11. The recorder (pipes.c r_native) draws it as P18 but with mi's bit 7 and
KH1_NAT_LIN, so z is not clamped and the GPU clips where P11 dropped every triangle with a vertex in front of its
near plane (w < 1) or off the guard band. The run's colour and F are constant, so the screen-linear colour of
KH1_NAT_LIN changes nothing there. `natp11=0` / `KH1_HOST_NATP11=0` keeps P11 on the VU (with the rest native).

Checked on the host (gxmcheck, renderer=native, dive_en.txt, a picture every 500 frames to 6999): 12 of the 14
pictures are identical to the P0 / P4 native build's; 6499 and 6999 differ in 201 and 276 pixels, along the
Keyblade's edges (the GPU's own rasterisation of the triangles the GS path drew). Not checked on a Vita. In the
qemu-arm timing of the Dive (vita-build.md "P12 as hand-written C") P11 was 4.2 s of ~75 s of VU1 run time.

### P10 too (2026-10-31, host only)

P10 (the shadow pass's untextured strips under the characters) goes over in the same payload as program 10
(vu1_draw.h `nd_10`): matrix records of 4 qwords, a position a qword (w the slot), no back-face test or ADC, so
every triangle is drawn with no cull, ST 0 (the PRIM has no TME). The colour is not in the run's VU memory (TOPS is
at 0 every other run, over qw0-1): it is the RGBAQ P10's set-up run (from 000, still run by the program) kicks from
qw1, so start_run keeps qw1 then (`nd_10_setup`). The first try read qw1 at the strip run and drew Sora's shadow in
the floor's colour. Runs of fewer than 3 positions are left to the program. `natp10=0` / `KH1_HOST_NATP10=0` keeps
P10 on the VU.

Checked on the host (as for P11): 11 of 14 Dive pictures identical to the P11 build's; 4999, 5499 and 6999 differ in
46, 72 and 98 pixels along the shadows' edges. In the qemu-arm timing P10 was 6.6 s of ~75 s of VU1 run time.
Not checked on a Vita.

Host instructions with everything above native (P0, P4, P10, P11, P18; callgrind over frames 5000-5060, one thread,
trace 5, as for P0): 1.75 G, against 2.09 G with P0 alone native and 3.69 G on the GS path.

### P13 too: the skinned models (2026-10-31, host only)

P13 (renderer B's skinned, flat-coloured, back-face-culled program, and the
biggest VU1 program on the Vita's game thread in the Dive: 542 ms per 2.4 s in the floor-fix log; in dive_en.txt's
pictures it draws Sora in the stretches around frames 3000-4000 and 6700-7500) goes over in P18's
payload as program 13 (vu1_draw.h `nd_13`, from 006). `natp13=0` / `KH1_HOST_NATP13=0` keeps it on the VU.

- **The stream** is P18's plus the skinning records (renderer-spec 2.3 "g & 1"): op 0 with w 1 sets the palette's base
  (vi06), w 2 or more loads nothing, op 2 starts the index stream (vi08 / vi09: the word to read next, which carries
  across groups and runs). A vertex is (-, -, -, k), k pre-weighted positions and STQ; each position's matrix is the
  next index (0 / 1 / 2 a slot, 0x100 + j the palette's entry j, which the program loads into slot 2, so a later
  index 2 means that entry). nd_13 walks it the way nat_13 does, on copies of the slots, and writes back what the
  run leaves: the slots, vi06 / vi08 / vi09, I (2046) and the idle PC.
- **One bone** (69 % of the Dive's P13 vertices): the position (xyz / weight) and its matrix go to the GPU, as P18's.
- **More than one bone** (31 %): summed on the CPU in plain float (c = sum M_i x p_i, the clip-space point the
  program divides), then handed over in a bone's space: v = M_a^-1 x c, position v.xyz / v.w with matrix a (since
  the first Vita log, a = one reference a run: below). The GPU's M_a x (v / v.w, 1) is c / v.w, the same screen
  place; v.w is the weights' sum (1) because every bone matrix of a model shares its projection, so the GPU's w and
  the perspective-correct STQ are the program's too.
- **One reference a run (2026-10-31, after the first Vita log)**: the summed vertices of a run are all handed over in
  one matrix's space, the first summed vertex's first bone (M_r), through Q_i = M_r^-1 x M_i made once per matrix a
  run (in double, kept as floats): a vertex is then k float matrix products and one reciprocal, with no double
  arithmetic (it was M_a^-1 x c in double, three double divides, per vertex). In the Dive a run has ~6 matrices,
  ~3.4 of them used by summed vertices, and ~0.5 new references (KH1_HOST_NATCHECK: the same counts and positions as
  before, worst 1.01 sixteenths).
- **The ADC**: P13's back-face rule is P18's (the parity from the record's w), so `kh1_nat_tris` lists it and the
  GPU's cull mode does the rest. Its guard band (a vertex off x / y 0..4092 or z / 4096 off 0..4092 drops the
  triangles that end at it) is the GPU's clipping instead: pipes.c draws program 13 as P11 (mi's bit 7, KH1_NAT_LIN, z
  not clamped).
- **Joined draws** (pipes.c `nat_hook`): a P13 run whose colour, F and cull match the open P13 op's joins it, its
  matrices appended (up to 32 in all) and its vertices' indices moved past the op's; a new PRIM, any state change or
  a full op still ends it. Without this each run was its own draw: the Dive's pictures went from 52 / 139 draws (GS
  path) to 264 / 350; joined, 94 / 180, with identical pictures.
- **Falls back to the program** for an influence count of 0 or over 8, more than 32 matrices, a matrix with no
  inverse, v.w not positive or a full buffer (none seen in the Dive).

Checked on the host:

- `KH1_HOST_NATCHECK=1` now covers P13 (`nd_13_check`): the program runs, and each vertex's screen position from the
  payload (its matrix x its position, divided) is compared with the program's XYZF2, and each triangle's ADC with the
  cull rule on the program's own 12.4 positions. To Dive frame 8000 (dive_en.txt, en.iso): 196,000 runs, 8,685,473
  vertices (2,760,075 summed on the CPU); every drawn vertex within 1.01 sixteenths of a pixel of the program's
  (the FTOI4 truncation), Z within one step; triangles drawn by both 2,541,733, by neither 2,207,319, by the program
  only 5,314 (slivers: cross products of 1-27 in 12.4 units, whose sign the rounding decides), by the native lists only
  6,743 (off the guard band: the GPU clips them). The ARM build under qemu-arm prints the same counts.
- Pictures (gxmcheck, renderer=native, a picture every 250 frames to 7499): the 22 without P13 are identical with
  natp13 on and off; the 8 with it (frames 3249-3999 and 6749-7499, Sora) differ in 721-8,489 pixels, 17-125 of them
  by more than 32 levels, scattered along edges (positions no longer truncated to 12.4). By eye the same.
- Host instructions (callgrind over frames 7000-7060, one thread, trace 5, renderer=native, Sora on P13): 2.35 G with
  natp13=0, 1.04 G with it on. P13's translated program was 0.49 G of that and its share of fin / fo ~0.4 G; nd_13
  costs 0.10 G. On the Vita P13 already runs as hand-written NEON (vu1_nat.h nat_13, ~40 % fewer instructions than
  the translation), so its saving there is smaller than the host's; the GS worker's kick decode for it goes too.

**On a Vita (2026-10-31, Shay's logs, renderer=native, latewait=0)**: Sora looked right. Where P13 draws (Dive frames
~4,900-5,450) the GS worker was busy ~1,650-1,900 ms per 2.4 s with nothing else changed (2,200 before) and the game
no longer waited for it; but P13's own time on the game thread was still ~470-740 ms per 2.4 s (the program's, NEON,
was ~740), ~60 us a run where the qemu-arm timing gives ~20 (P0 ~37 on the Vita, ~21 in qemu). So the parse costs far
more on the A9 than qemu suggests; the change above takes the double arithmetic out of the vertex loop, and the
`native renderer:` line now gives the time spent handing payloads to the GS worker (`handing them to the GS worker N
ms (P13's M ms)`), the rest of P13's time in `vu1 programs:` being the parse. Under qemu-arm (frames 0-7300, one
thread, KH1_HOST_CLOCK=1) P13 native was 6.2 s in all (2.5 s of it the hand-off, which on the host runs the GS worker's
side inline) against 19.8 s for the NEON program with its kicks.

**The hand-off line on a Vita (2026-10-31, PR #200's build, Dive frames ~3,700-7,700)**: P13 ~600-720 ms per 2.6 s
window, of it only ~40-60 ms handing payloads over: the parse is ~640 ms (~55 us a run of ~42 vertices, ~1.3 us a
vertex, ~580 A9 cycles), the one-reference-matrix change no faster there. Not the sound threads taking the game's
core: with `sndcore=2` (sound pinned to the third core) P13 was the same 600-680 ms, and the frame recording on that
core then made the GS worker wait 0.9-1.8 s a window (10-14 pictures a second): leave sndcore unset. Then (same date):
the summed vertices' products in NEON (`vmlaq_lane_f32`, not fused: the scalar sum's roundings in another order; NATCHECK
to frame 8000 gives the counts above unchanged on the host's scalar path and on qemu-arm's NEON one), a palette entry
loaded into slot 2 not copied again when it is the one there already, and the `native renderer:` line's `N P13 runs
handed back to the program (M ms)`: the runs nd_13 gave up on, and their time (the parse that gave up, then the
program's), so the parse's own share of `vu1 programs:` P13 is that line's P13 time less the hand-off and this.

**latewait (2026-10-31)**: two of those runs had `latewait=1` in config.txt (the mod menu's "Frame catch-up: Off",
saved there before the first of them; the menu writes only the values it shows, so it was set from the menu at some
point, not by a bug): the game thread then waits for a vblank every frame, ~700-800 ms per 2.4 s in the Dive, ~13
pictures a second where latewait=0 gives ~15-16. Keep it at 0.

Not checked on a Vita: the GPU's cost of one draw a P13 run (each with up to 32 matrices) where
the GS path batched them; the Vita log's `native renderer:` line now also counts P13's vertices and the summed ones.
If Sora looks wrong with renderer=native, `natp13=0` is the switch to try first.

## The stages after

2. **P13 (skinned, flat, cull)**: done (above, "P13 too"). Not as planned here (the palette in `u_m` and the bone
   indices and weights in the vertex): one-bone vertices go to the GPU as P18's, the rest are summed on the CPU and
   handed over in their first bone's space, so the vertex format and shaders are unchanged.
3. **P0 (map strips)**: renderer A's flags in the vertex w (strip restart, winding) become the triangle list, and
   its clipping becomes the GPU's. Over half of the Dive's VU1 time. The map's chains do not change between
   frames; once the CPU side parses a chain the triangle list can be cached by the chain's address and the
   matrices' change alone uploaded, which removes most of the game thread's work for it.
4. **P12**: P11, P10 and P4 are done (above); P12 the lit variant (3 lights and ambient in the shader with the same
   clamps).
5. **Batching and threads**: native runs of one pipeline and texture joined into one draw (the matrices
   indexed per vertex already allow it), and `nd_*`'s parse moved off the game thread to the GS worker (the
   payload would then be the VU memory image).

Each stage lands behind the same switch, with a host side-by-side against the GS path before it goes to a Vita.

## Running it

- Vita: `renderer=native` in ux0:data/kh1/config.txt (`natcull=0/1/2` for the cull). The log says
  `kh1-vita: renderer: native ...` at start and every 2 s `kh1-vita: native renderer: N runs drawn by the GPU's
  transform, D draws, T triangles`.
- Host: `KH1_HOST_NATIVE=1` (needs `KH1_HOST_TRACE=5`, the recorder) with `KH1_HOST_CD=go KH1_HOST_VU1=1`;
  `KH1_HOST_NATCULL=` as natcull. The gxmcheck build (vita-build.md "The GPU renderer") draws it through the
  GXM stand-in and writes PPMs with `KH1_HOST_GXM_PPM=dir`.
