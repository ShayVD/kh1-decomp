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
the limit. On with `renderer=native` (config.txt), `natp0=0` keeps P0 on the VU1 program with P18 still native;
host `KH1_HOST_NATIVE=1`, `KH1_HOST_NATP0=0`.

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

## The stages after

2. **P13 (skinned, flat, cull)** (next: P0 went first, above): the same flow with the bone palette: op 0 with w = 1 marks the palette record,
   op 2 the bone index lists, each vertex a weighted sum of up to 4 bones (renderer-spec 2.3, "g & 1"). The
   palette goes to `u_m` (more rows, or a second uniform buffer: GXM's vertex default buffer allows 4 KiB, so 64
   matrices); the vertex carries its bone indices and weights (`p_i = xyz_i / w_i`). Late in the Dive this is
   the biggest single program (~740 ms per 2 s).
3. **P0 (map strips)**: renderer A's flags in the vertex w (strip restart, winding) become the triangle list, and
   its clipping becomes the GPU's. Over half of the Dive's VU1 time. The map's chains do not change between
   frames; once the CPU side parses a chain the triangle list can be cached by the chain's address and the
   matrices' change alone uploaded, which removes most of the game thread's work for it.
4. **P11, P10, P4**: P11 is P18 plus a near-plane cull and a guard band (the GPU clips; the near cull is a
   z test in the shader), P10 the lit variant (3 lights and ambient in the shader with the same clamps), P4 the
   lit A program.
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
