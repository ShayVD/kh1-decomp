# Past 30 fps: emulating less, using the Vita natively (plan, 2026-10-31)

A plan only: nothing here is implemented yet. **Work on it starts once the three current steps are merged**
(the 30 fps plan's three: P13 on the GPU, the GS worker's frame op and native parse moved to the GPU thread, and
the GS memory model's upload work cut). Every figure below is an estimate from the Vita logs and host counts
named in each stage, not a measurement, until a Vita log says otherwise.

Port code only, as for the native renderer: kh1.elf and src/ stay byte-identical and matching. Everything here
lives in host/port, host/null and host/vita, behind a config.txt switch with today's path as the fallback, so a
wrong guess costs speed, not a picture.

Read with: native-renderer.md (the native path so far), renderer-spec.md sections 2 (the VU1 programs), 4 (the
per-frame packet flow) and 5 (mapping to a modern API), vita-build.md (the timings), sound-spec.md section 6.

## Where it starts

The 30 fps plan's table (Shay's Vita, `renderer=native`, the floor-fix build, Dive frames 5000-8000, per 2.4 s of
wall time; 30 fps is 72 pictures in that window):

| Thread | Busy now | After the three steps (their estimates) |
|---|---|---|
| GS worker (core 1) | 2,259 ms: the limit | ~1.0-1.3 s |
| Game thread (core 0) | ~1,960 ms + 437 waiting | ~1.4 s |
| GPU thread (core 2) | 792 frame jobs + 726 recording | **~2.0-2.2 s**: it takes the frame op and the native parse (~0.5-0.7 s) |
| Sound | sndprio=-4 since 2026-10-31 | unmeasured cost |

So after the three steps the Dive should sit near 25-30 pictures/s, with **the GPU thread as the likely next
limit** (it gains the worker's frame op and parse while still converting and recording every GS-path vertex) and
no core with real headroom. The plan below is ordered to take work off whichever thread limits next, and to end
with the GS model and worker mostly gone, which is what gives headroom past 30.

What still runs as emulation after the three steps:

- **VU1**: every program but P0, P4, P10, P11, P13 and P18 (native on the GPU) and P12 (hand-written NEON on the
  CPU). Left as translated programs: P1, P2, P3, P5, P6, P7, P8 (renderer A), P12, P14-P17, P19, P20 (renderer B),
  and gb.x / wm.x's five Gummi programs (renderer-spec 2.5).
- **DMA / VIF**: dmawalk.c walks every chain the game sends: tags, VIF codes, UNPACKs into VU memory, DIRECT and
  the GIF path into the GS worker's ring. ~1.3 s of the game thread's 2.4 s before P13 (VU1 714 ms of it, so ~0.6
  s of walk, unpack and ring copies alone).
- **GS**: the register file (gsregs.c), the 4 MB memory model (gsmem.c) with its uploads, CLUT and target
  bookkeeping, the GS-path primitive assembly (pipes.c), batch.c's per-vertex conversion.
- **IOP / SPU2**: the disc's LIBSSL.IRX on a MIPS interpreter (five hot functions already C), the SPU2 mixed in
  C.
- **Game math**: the game's own C as compiled for the A9; libvu0.c's sceVu0 calls in plain C.

## The stages

Each stage is about one thread's worth of work, lands behind its own switch, and is measured the same way at
the end: a Vita log of the Dive (`renderer=native`, dive_en.txt's route, frames 5000-8000) with the per-thread
table above, plus the stage's own host checks. Expected gains are per 2.4 s window.

### Stage 0: the baseline after the three PRs (small, first)

- One Vita run with all three merged: the per-thread table, `gputime=1` once and once without, the `vu1:` and
  `native renderer:` lines, the sound line's short buffers.
- One census of what is left: each VU1 program's runs and time, the walk's split (tags / unpack / DIRECT / ring),
  the GS worker's parts, the GPU thread's split (recording / frame jobs / GPU waits). Also a short run of Destiny
  Islands (dive_en.txt past 77,000), which uses programs the Dive does not (P2 / P3's fog and UV scroll, P12 / P14
  lit models).
- **Gain**: none. **Why first**: picks the order of stages 1-3 from measurements, not these estimates.
- **Tested by**: the log itself; nothing in code changes beyond log lines.

**The log lines for it (2026-10-31, host/vita/main.c's watchdog, every 2 s)**, added to what the log already had:

- `vu1 programs:` now lists every program over 1 ms, not the top four.
- `walk split:` the DMA walks' time by channel (VIF0, VIF1, GIF) and their sends; of VIF1, the time its data words
  take into VU memory (dmawalk.c `vif1_feed`: UNPACK, MPG, STROW..., the programs they start not counted); the ops
  and KiB the game thread copied into the GS worker's ring (gsqueue.c `kh1_gsq_puts`, `kh1_gsq_put_bytes_n`).
  VIF1's time less the feed and the `vu1:` line is the walk itself (tags, VIF codes, DIRECT's skim).
- `threads:` each port thread's CPU time in the window from the kernel's run clock (the game, the GS worker, the
  GPU thread, the three sound threads, the watchdog), the core it last ran on, its affinity mask, its priority and
  how often it was preempted. Unlike the busy counters this does not count time another thread took from it, so the
  GPU thread and the sound threads sharing a core shows as the GPU thread's busy time above its run time and its
  preemptions.

**The host's split (2026-10-31, the stage 5 / 6 thread; callgrind, game thread only, renderer=native, GSQ / GPUQ / RECQ
on, en.iso, dive_en.txt, the host's trace prints and per-send GS syncs removed)**: frames 5000-5060, ~1.0 G
instructions: P12's translated program ~730 M, P2 ~50 M, nd_0 62 M, unpack 55 M, the rest of the walk (vif_word, the
skim, the ring's put, dma_walk) ~25 M. Frames 7000-7060, ~0.33 G: nd_13 113 M (11.5 K instructions a run, ~270 a
vertex, in line with the Vita's ~1.3 us a vertex), unpack and vif1_data ~40 M, the rest of the walk ~15 M. So with the
native programs on, the walk's own tag / VIF / ring work is under 10 % of the game thread; the costs are the unpack
into VU memory, the nd_* parse and P12. On the Vita P12 runs as hand-written NEON (vita-build.md "P12 as
hand-written C"), so the host's translated count overstates it there: the Vita's `vu1 programs:` line decides
whether stage 2 (P12 on the GPU) moves up.

**The run**: the stage 0 VPK, config.txt `pad=ux0:data/kh1/dive_en.txt`, `renderer=native`, `latewait=0`,
`frames=8000`, the rest default (sndprio -4, recframe 1); then the same with `gputime=1`. Frames 5000-8000 of the
first log fill the table at the top of this file.

### Stage 0's result (2026-11-01, Shay's Vita, the stage 0 VPK, renderer=native, dive_en.txt)

15 watchdog windows over Dive frames 5144-7683, scaled to 2.4 s (the windows were ~5.1 s, not 2: the watchdog, on
core 2 at the game's priority, is starved). **17.7 pictures/s** (35.5 frames/s): no better than before the three
steps, because every core is full.

| Thread (run clock) | ms per 2.4 s | Where it goes |
|---|---|---|
| GPU thread | **1,946** | the recording 1,790 (the frame op's passes, now here, 614 of it) |
| GS worker | **1,829** | **w_native 800**, uploads 1,305 in all (w_block 491, w_load 313, w_qwords 274, w_load_big 227), w_gpu_frame 200 (152 of it waiting for the GPU thread), w_kick 70 |
| Game | **1,763** | DMA walks 1,168 (VIF1 1,206 with the ring waits: VU1 programs 368, the feed into VU memory 372, the rest ~470; GIF 112), the game's code ~700, waiting for the worker 295, large uploads 137 |
| Sound (3 threads) | **1,736** | ticks (the IOP interpreter) 918, mix 750, output 68; ~3.5 M IOP instructions a second, 10-13 voices |

The three cores have 7.2 s per 2.4 s; the threads took ~7.3 s (the run clocks are read at slightly different
moments). Worker op addresses were mapped with this build's symbols (the log's addresses are 0x6a001 above
out/vita/kh1.elf's).

What it changes in the order:

1. **Sound is a quarter of all CPU.** With sndprio=-4 its threads run above the game's on any core, so they take
   ~1.7 s per 2.4 s from the other three: about one core. The plan's estimate (the Dive has 3 voices) was wrong:
   with the room's SEs fixed (2026-10-30) the Dive plays 10-13. Stage 8 moves to the front (a thread is already
   on it).
2. **w_native is the worker's biggest op** (800 ms): per native record the GIF tag's PRE, the draw counted in gsmem,
   and the recorder's copy of the payload (pipes.c `nat_hook`). Next after sound: hand native payloads to the GPU
   thread directly, with the worker doing only the register and draw-count bookkeeping in bulk (part of stage 7,
   pulled ahead; it touches stage 5's hand-off, so the same thread or one right after it).
3. **Uploads** (1.3 s on the worker): stage 4.
4. **The GPU thread** (full at 1.9 s, mostly the recording): stage 1.
5. Stages 2 / 3 can wait in the Dive: P12 is 19 ms a window here, P1 / P2 ~55 between them. VU1 time is now
   P0's parse 162 and P13's 153.

### After stage 0: w_native on the worker (2026-11-01, host-measured)

A host profile of the GS worker (callgrind `--separate-threads=yes` on the gxmcheck binary, renderer=native, trace 5,
GSQ / GPUQ / RECQ, en.iso, dive_en.txt) puts w_native at 22 M of the worker's 527 M instructions over frames
5000-5060 and 83 M of 586 M over 7000-7060 (Sora, P13): 4-14 %, where the Vita's log has it at ~44 % of the worker
(800 of 1,829 ms). The uploads (kh1_gsmem_image ~280-380 M) lead on x86. So on the A9 w_native costs ~3x its
instruction share: ~43 us a gsq op, ~3.6 us a record, ~520 x86 instructions a record. The likely reason is the
recording queue: nat_rec put every record as its own kh1_recq_put, and each put does sequentially consistent
atomic loads and stores (a `dmb` each on ARM, which waits for the core's pending stores), where x86's are plain
loads.

**First cut (pipes.c `span_flush`, config.txt `natspan=1`, the default)**: a payload's records are contiguous, so
nat_rec now extends one span and puts it as one r_nat_rec op at the payload's end (or before any other op of the
native path: r_nat_mats, the op's end). r_nat_rec already took several records at once, so the GPU thread's side
is unchanged. `natspan=0` (host `KH1_HOST_NATSPAN=0`) puts each record as before. Host: the Dive to frame 7500 at
trace 5 with renderer=native, all 60 GPU picture hashes (KH1_HOST_GXM=250, KH1_HOST_GXM_HASH=1) identical with
natspan 0 and 1; over 7000-7060 w_native 83 M -> 71 M, the worker's kh1_recq_put 16 M -> 8 M. **Not yet measured on
a Vita**: the `gs worker ops:` line's w_native time (the address of `w_native` in out/vita/kh1.elf + the log's
offset) with natspan=1 against natspan=0. If it barely moves, the cost is elsewhere (the payload's cache misses
crossing cores, or kh1_gs_native's per-record bookkeeping) and the next step is handing payloads by reference.

### Native payloads by reference (2026-11-01, config.txt `natref=1` / `natbulk=1`, host-measured)

Stage 0's Vita log had w_native at 785 ms per 2.4 s with natspan=0 and 734 with natspan=1, so the span cut barely
moved it. Two changes, both on by default, both off with `natref=0` (the A/B switch):

- **The payload by reference** (dmawalk.c `path1_draw` / `w_native_ref`, gsqueue.c `kh1_pool_*`, pipes.c `r_nat_ref`).
  Before, a payload was copied three times: the game thread into the GS worker's ring, the worker its records into
  the recording queue, the GPU thread those into its op (`nat_op`). Now the game thread writes it once into a 4 MiB
  pool (a ring of qwords, the gsq's kind: one writer, freed in order) and puts the worker a one-qword reference
  (address, qwords, the pool position after it). The worker reads only what it needs (the header, the matrices for
  the join checks, each record's first qword) and puts each span of records to the recording queue as another
  one-qword reference; r_nat_ref on the GPU thread reads the records in place (r_nat_rec, as before) and frees the
  pool up to the payload's end. The free rides on the payload's last span; a payload whose records all went earlier
  holds its free until the next span, or until the worker goes idle (gsqueue.c `kh1_gsq_idle_hook`). **The
  deadlock the plan thread warned of**: the game thread waits for pool room only after publishing the gsq, and with
  the pool on the worker publishes the recording queue before it sleeps, so a free never sits unpublished while the
  game waits. tests/host/gsqueue_test.c runs that pipeline through a 64 KiB pool (20,000 payloads up to 1,024
  qwords, ~450 waits for room). r_nat_open / r_nat_mats still copy the header and matrices by value (small, and the
  op can outlive the payload), and the GPU thread still assembles `nat_op` (its own copy, same as before).
- **The GS bookkeeping in bulk** (gsregs.c `kh1_gs_native_run(d, bulk)` / `gs_native_n`): the records of a payload
  up to a PRE that writes another PRIM are counted with one gs_find and one kh1_gsmem_draw_n (kicks and triangles
  summed). A PRE that writes the PRIM in force changes nothing a count reads (set() keeps the draw; the vertex
  queue is emptied either way), and kh1_gsmem_draw_n's repeat calls only count, so the counts and marks are the
  same. The hook (nat_rec) still sees every record with its PRIM. `natbulk=0` (host `KH1_HOST_NATBULK=0`) counts
  each record with natref=1; natref=0 always does.

Records' lengths go through natdraw.h's `KH1_NAT_REC_QW(r)` (the skinning thread's 3-qword vertices change only the
macro's body).

**Checked (host)**: the Dive to frame 7000 on en.iso (dive_en.txt, `KH1_HOST_TRACE=2 KH1_HOST_GSQ=1
KH1_HOST_GSQ_CHECK=50 KH1_HOST_GXM=50 KH1_HOST_GXM_HASH=1 KH1_HOST_GPUQ=1 KH1_HOST_RECQ=1 KH1_HOST_VU1=1
KH1_HOST_VU1TR=1 KH1_HOST_NATIVE=1`, the gxmcheck binary): all 140 GS digests and 280 GPU target hashes identical
with `KH1_HOST_NATREF=0`, `=1`, and `=1 KH1_HOST_NATBULK=0 KH1_HOST_NATPOOL=262144` (a 256 KiB pool, so it
wraps often). After #207 (natskin) the same with `KH1_HOST_NATSKIN=1`: natref 0 and 1
identical there too. tests/selftest.sh passes. **Worker profile** (callgrind as above, trace 5, frames 7000-7060, thread 3):

| | natref=0 | natref=1 |
|---|---|---|
| the worker | 575 M | 549 M |
| w_native (w_native_ref) | 72.0 M | 45.1 M |
| kh1_gs_native (gs_native_n) | 26.8 M | 4.2 M |
| span puts (copies into the recording queue) | 4.1 M | 1.5 M |
| nat_rec | 30.3 M | 30.3 M (24.8 M of it prim_state: the state op and the texture lookup, once an op) |

On the Vita the bigger part should be memory, not instructions: the worker no longer reads every byte of each
payload (written on the game's core) or writes it again into the recording queue (~25 MB a window, the
estimate in vita-build.md). **Vita (Shay, 2026-11-01, PR #208's first VPK, before #207; dive_en.txt, watchdog windows over frames 5000-7700
scaled to 2.4 s)**:

| | natref=0 | natref=1 |
|---|---|---|
| pictures/s | 18.5 | 19.1 |
| w_native / w_native_ref | 754 ms | 568 ms |
| the GS worker thread's run time | 1,804 ms | 1,412 ms |
| the GPU thread's run time / its recording | 1,967 / 2,001 ms | 1,692 / 2,153 ms |
| the worker's frame op waiting for the GPU thread | 167 ms | 292 ms |
| waiting for pool room | - | 0 ms |

(The two logs' op addresses sit 0x1 and 0x39001 above out/vita/kh1.elf's: map each log by its own w_block /
w_gpu_frame.) The worker is no longer the limit: it lost ~0.4 s a window and now waits more for the GPU thread,
whose recording fills its core. So the frame rate moved only ~3 %; the next gain is on the GPU thread (stage 1, and
the 'Cut GPU thread recording cost' thread). **Next on the worker's native path**:
prim_state's texture lookup per op (~25 M here), then stage 4's uploads.

### Stage 1: the GPU thread's per-vertex work (static vertex buffers and batching)

The native renderer's stage 5 and P0's caching note, pulled ahead because the GPU thread becomes the limit.

- **Static vertex buffers**: renderer A's map chains do not change between frames (native-renderer.md stage 3).
  Cache each native batch's triangle list and vertices in GPU memory keyed by the chain's source address and a
  hash of its records; a frame then uploads only matrices. The same for renderer B's rigid models (P11 / P18 /
  P10's records are the model's own data) and P13's skinned meshes (only the bone palette changes).
- **Batching**: native runs with the same pipeline, texture and blend state joined into one draw (the per-vertex
  matrix index already allows it), so the recording makes a few dozen GXM calls a frame, not one a run.
- **Gain**: GPU thread −0.4 to −0.8 s (the native share of recording and payload conversion); fewer draws on the
  SGX. **Risk**: a cache keyed wrong draws a stale mesh: the key includes the record hash, and `natcache=0` turns
  it off.
- **Tested by**: `KH1_HOST_NATCHECK` with the cache on (each cached batch compared with a fresh parse every N
  frames), gxmcheck pictures of the Dive identical with `natcache=0` and `=1`, the GPU thread's line on a Vita.

**First cut (2026-11-01, config.txt `recfast=1`, the default; `recfast=0` / host `KH1_HOST_RECFAST=0` the old code)**.
Before static buffers, the two biggest plain costs the host profile showed on the GPU thread (callgrind
`--separate-threads=yes`, gxmcheck binary without KH1_HOST_GXM so the mock rasteriser stays out, renderer=native,
VU1 / VU1TR / VU1NAT on, trace 5, GSQ / GPUQ / RECQ, en.iso, dive_en.txt; the env must include `KH1_HOST_VU1=1`, or
the Dive has no 3D and the profile is empty):

- **The frame op's passes** (Vita: ~550 ms of the GPU thread's ~2.8 s in a 3.2 s window): over frames 7000-7060
  kh1_cmd_frame and its callees took ~50 M instructions, **38 M of it cmd_swap**: hoist (2026-10-31) moved a pass's
  commands with three reversals of whole KH1Cmds (each with its KH1DrawState) and bubbled each of G's uploads down
  one swap at a time. Now cmdbuf.c `cmd_rot` rotates through a scratch copy (memcpy / memmove, each command moved once
  or twice) and the uploads are partitioned in one pass. Same command order: **50 M -> 12 M**.
- **The native triangles** (natdraw.c, ~half the recording ops' instructions: put / put0 three times a strip vertex,
  once for each triangle it is in): now each vertex is converted once into a scratch array and the triangles are
  32-byte copies of it. On x86 this barely moves (39.9 M -> 39.1 M at 7000, 33.6 M -> 32.2 M at 5000: a struct copy is
  not much cheaper than put there); on the A9 a copy is two ldm / stm pairs against put's float and byte stores, so
  the Vita log decides whether it is worth keeping.

Checked: all 60 GPU picture hashes (KH1_HOST_GXM=250, KH1_HOST_GXM_HASH=1, to frame 7500, KH1_HOST_WIDE=1) identical
with the change and without; make test passes. **Not yet measured on a Vita**: the `gs worker's frame op:` line's "the
passes on the GPU thread" and the `recording:` line, recfast=1 against recfast=0. Expected: the passes ~0.3 s lower per
2.4 s if the A9 spends what x86 does in the swaps.

**The Vita's A/B (2026-11-01, Shay's Vita, the recfast VPK, renderer=native, dive_en.txt, watchdog windows inside
frames 5000-8000, scaled to 2.4 s)**:

| | recfast=0 | recfast=1 |
|---|---|---|
| pictures/s | 20.1 | **21.3** |
| the frame op's passes on the GPU thread | 635 ms | **119 ms** |
| recording on the GPU thread (the passes and the GPU frame in it) | 1,985 | 1,867 |
| GS worker (run clock) | 1,670 | 2,097 |
| game (run clock) | 1,495 | 1,874 |

The passes lost ~0.5 s, more than x86's share predicted. The recording total fell less, because with frames coming
faster the GPU frame's submit (554 -> 849 ms) and the worker and game threads each do more work a second: the GS
worker (~2.1 s) is now the busiest thread again. The watchdog's windows were 5.9 s long with recfast=0 and 3.6 s with
1 (it shares core 2 with the GPU thread). Both runs were played by hand, so ~6 % is about the noise floor; the passes'
drop is far outside it. Next on this thread, by the Vita's `gpu parts:` line: the vertex
copy (~150 ms per 2.4 s: gxm.c memcpys the recorder's whole vertex slot into GPU memory each frame; recording into
GPU-mapped memory needs the empty frames' early return to wait for the GPU before the slot is reused) and the
uploads into targets (pend_flush, outside the parts' timers).

### Stage 2: the rest of renderer B on the GPU (P12, P14, P15-P17, P19, P20)

- **P12 / P14 (lit, rigid / skinned)**: the native vertex shader gains renderer B's lighting: 3 parallel lights +
  ambient with the same clamps (saturate before scaling, renderer-spec 5). P14 reuses P13's bone palette and
  weights. P12's hand-written NEON form stays as the CPU fallback.
- **P15-P17 (full clipping)**: the same records as P11 / P12 / P13 with the VU's clipper; the GPU's clipping
  replaces it, as it did for P0.
- **P19 / P20 (special)**: census first (renderer-spec 2.3); native only if they show up in the logs.
- **Gain**: small in the Dive (most of its B models are P11 / P13 / P18); the main gain is in lit rooms (Destiny
  Islands and later: P12 was 140 M of the game thread's ~800 M instructions under qemu in session 147). Expect
  game thread −0.1 to −0.3 s where they are used.
- **Tested by**: NATCHECK per program (each batch's output compared with the program's GIF output: colours, ST,
  F, triangles drawn by one side only), natdraw_test / shadergen_test cases for the lighting clamps, gxmcheck
  pictures of Destiny Islands against the GS path, `natp12=0` style switches.

### Stage 3: the rest of renderer A on the GPU (P1, P2, P3, P5, P6, P7, P8)

- **P2 / P7** (P0 + per-vertex fog): F = clamp(A + B / w) in the vertex shader (renderer-spec 5, within 2 levels
  of the GS's step; the exact form in 4.13 "Session 122").
- **P3** (env map, UV scroll): the scroll table and env matrix as uniforms.
- **P1** (float STQ, no cull; the projected-shadow receivers) and **P6** (point light), **P5** (single-colour
  silhouettes), **P8** (the lens grid, smallest of all).
- **Gain**: like stage 2, mostly outside the Dive; it finishes the list so no 3D draw needs the translated VU1
  programs. Game thread −0.1 to −0.4 s in fogged rooms.
- **Tested by**: as stage 2, with the fog compared value for value against the program's F.
- Stages 2 and 3 are independent and can run as two threads in parallel.

### Stage 4: textures from the source, not from GS memory

The upload half of retiring the GS memory model (the third current step starts this; this stage finishes it).

- At the walk, an IMAGE transfer whose source is in EE memory is recognised (BITBLTBUF / TRXPOS / TRXREG and the
  data's address) and the texture cache keyed by **source pointer + CLUT** (renderer-spec 5) decodes from there
  when a draw first reads it. gsmem stores the pixels only when something reads GS memory back: a target read as
  a texture ("target N"), a local-to-local copy, the font in the Z buffer's top byte, a CLUT load from a region an
  upload just wrote.
- The CLUT cross-fades (renderer-spec 4.13) stay as palette textures with a per-frame palette upload.
- **Gain**: GS worker −0.3 to −0.6 s beyond what step 3 takes (GIF image blocks, big and small uploads, image
  qwords: ~1.1 s today).
- **Tested by**: gxmcheck pictures with `gsstore=lazy` and `gsstore=all` identical over the Dive and the menus;
  a debug mode that does both and compares every texture the GPU reads against gsmem's decode.

### Stage 5: renderer B's draws as native calls (no chain, no walk)

The biggest structural step: the game's draw list hands its renderer B nodes to the native renderer directly.

- Today the game's C (func_00160370 and func_0015fc00, renderer-spec 4.1) builds each object's VIF1 chain;
  dmawalk.c walks it, unpacks the records into VU memory, and `nd_*` parses VU memory back out. In the port, a
  platform hook at the chain's send (the `sceDmaSend` wrapper on channel 1) recognises renderer B's chain shape
  (MPG, then REF to the model's packet, the matrix and palette uploads) and passes the model's EE pointer, its
  matrices and its bone palette to the native renderer, with stage 1's vertex buffer cache keyed by that pointer.
  Chains it does not recognise go to the walk as now.
- No game function changes; the hook is in the platform layer (portability.md's wrappers), so the same shape can
  later become a direct call in phase 4's shiftable code.
- **Gain**: the walk's share for these chains (tags, unpacks into VU memory, the parse) and their GS worker
  kicks: game thread −0.3 to −0.5 s, GS worker −0.1 to −0.2 s.
- **Tested by**: a check mode that both walks and calls natively and compares the payloads (same matrices, same
  vertices, same order in the draw list); the worker-order digests (`KH1_HOST_GSQ_CHECK`) unchanged for the
  draws that stay on the GS path; gxmcheck pictures.

### Stage 5, first cut: records straight from the chain (2026-11-01, config.txt `natchain=1`)

The fights log (Shay's Vita, build 26b3b0b, renderer=native, dive_en.txt into the Dive's enemies; watchdog windows
of ~5-9 s) put VIF1's walk at ~4.2 s of a 5.6 s window: the native programs' parse and hand-off ~1.2 s (P18 ~386 ms,
P0 ~473, P11 ~315, P10 ~167; ~20 us a run), the feed into VU memory ~1.4 s (43 M words), the rest of the walk ~0.8 s.
The clock on the Vita is a system call, `683 ns a read`, and that feed line alone read it twice per feed (a few
hundred thousand feeds a window), the VU1 runs and hand-offs twice each more.

What this cut does (host/port/vu1.c `nc_*`, vu1_draw.h; `natchain=0` / host `KH1_HOST_NATCHAIN=0` is the old path):

- **Unpacks held, not written.** With the native renderer on, a TOPS-relative UNPACK whose data came in one piece (the
  walk's own words; they stay put until the send ends) in a form the native parses read in place (mode 0, no mask,
  CL >= WL; V4-32, V4-16, V4-8, V2-16) is recorded (its words, address, CL / WL) instead of written. Up to 8 are held.
- **The parses read the held words.** Renderer B's packets (renderer-spec 2.3: `STCYCL 1,1; UNPACK V4-32 n -> 0 +TOPS;
  MSCNT`) are one held V4-32 at top: nd_18 (P18, P11) and nd_10 read their records from it, bounds-checked against
  its length. Renderer A's batches (renderer-spec 2.2.2: the tag `V4-32 1 -> @0`, then `STCYCL 3,1` and `V4-32 -> @1`,
  `V4-8 -> @2`, `V2-16` or `V4-16 -> @3`) are exactly four held unpacks: nd_0 (P0, P4) reads the position, the
  colour bytes and the ST halves where they are, sign-extended or not as the unpack would (USN). A handed-over run
  drops what it read: those VU addresses keep what they had.
- **Everything else first writes what is held, in order, as before** (`nc_flush`): any unpack not held, a run of any
  other program (or the interpreter, or a check mode), a parse that cannot read them (a stream longer than the
  unpack, two unpacks where one is expected, a role missing, a vertex w not 1...), and every VIF1 send's end
  (dmawalk.c calls `kh1_vif1_end`). Held unpacks are never kept past their send.
- **The payload written into the pool** (gsqueue.c `kh1_pool_room` / `kh1_pool_take`, dmawalk.c `path1_room_at` /
  `path1_take`): with natref's pool the parse writes the payload where the GS worker reads it, then puts the same
  one-qword reference op path1_draw put, so nd_buf and its copy into the pool are gone (P13 still builds in nd_buf).
- **1 in 8 of the game thread's hot timers** (platform/vu1.h `KH1_TIME_THIS`): a VU1 run, an XGKICK, a feed and a
  hand-off read the clock on 1 call in 8, chosen at random (a fixed 1-in-8 would always time the same call of a
  repeating pattern: P0's five feeds a batch), and count it 8 times. Run counts stay exact; the times are estimates.

**What is not exact, and how it is checked.** The only change to VU1's state is that a dropped unpack's addresses are
not written: the TOPS buffer keeps an older run's input. Nothing reads its TOPS buffer before an unpack fills it, but
that is a claim about the game's chains, so `KH1_HOST_NATCHAIN=2` writes a poison pattern there instead (any reader
would change a picture or a digest), and `=3` parses every held run both ways and compares the payloads
(`natchain=... payloads differed` in the host's last lines). tests/host/vu1chain_test.c feeds 6 random streams of B
packets and A batches with every fallback case through the real VIF1 code path (stand-in programs,
tests/host/vu1chain/vu1_tr.c) with natchain 0-3: the payloads, what each program run reads, the slot registers and
tpc are the same every way, VU memory too except the poisoned words; it runs on x86 and under qemu-arm with NEON
(tests/selftest.sh). Mutations (sign of a USN element, a length off by one, the mode test dropped, the flush's CL not
restored, the flush before another unpack dropped) each fail it.

**Checked on the host** (en.iso c8ee8c77..., dive_en.txt to frame 7000, the gxmcheck binary, `KH1_HOST_TRACE=5
KH1_HOST_QUIET=1 KH1_HOST_GSQ=1 KH1_HOST_GSQ_CHECK=50 KH1_HOST_GXM=50 KH1_HOST_GXM_HASH=1 KH1_HOST_GPUQ=1 KH1_HOST_RECQ=1
KH1_HOST_VU1=1 KH1_HOST_VU1TR=1 KH1_HOST_NATIVE=1 KH1_HOST_CLOCK=1`): all 280 GPU target hashes identical for main
(26b3b0b) and natchain 0, 1, 2 (poisoned) and 3. **The host turns the native renderer on only at trace 5**
(main.c: `kh1_host_trace >= 5 && KH1_HOST_NATIVE`); at trace 2 the same env runs the GS path, where natchain holds
nothing: those runs gave the same 140 GS digests and 280 hashes for all five as well. With natchain=1, 465,834 of the
496,718 native runs (P0 286 K, P18 82 K, P11 65 K, P4 35 K, P10 29 K) read their records from the chain, 77 M qwords
were never unpacked into VU memory, 197 K held unpacks were written late (the rest of the runs: a parse that gave them
back, or another program); natchain=3 found 0 payloads that differ. Host times (x86, not the Vita's): the hand-offs
343 -> 119 ms, P18's runs 116 -> 86 ms. make test passes.

**Expected (estimate, not measured)**: per 5.6 s fight window, the feed's copies for these runs and the payload's
second copy (~0.3-0.5 s together, if the copies are the feed's cost) and ~0.2-0.4 s of clock reads, so the game
thread -0.5 to -0.9 s a fight window, a few ms a picture; less than the ~34 ms a picture the walk's lines add up to,
because the parse itself (the records read and the payload written, now cold pool memory) and the rest of the walk
(VIF codes, the w_path1 op per run, the tags) stay. The Vita's `natchain=` line counts the runs read from the chain,
the qwords never unpacked and the unpacks written late; compare `walk split:`, `vu1 programs:` and `native renderer:`
with natchain=0. If the parse's per-run time does not fall, the cost is cache misses on the model data, which only
stage 1's cache (records not re-read every frame) removes.

**Not changed**: P13 (its parse reads VU memory: held unpacks are written before it runs), the GS path, any check or
trace mode (nothing is held in them). The GS worker's per-op profile (gsqueue.c `prof`, two clock reads an op, ~270 K
ops a fight window) still reads the clock every op: on the worker, ~0.35 s a window at 683 ns a read, a cheap
follow-up for the worker's thread.

### Stage 6: renderer A's object chains as native calls, and the walk's fast path for the rest

- The same for renderer A: per-object chains start with the program's REF (renderer-spec 2.1) and REF the map's
  batches, which stage 1 already caches by address. The hook passes the batches' addresses and the object's
  matrix block (VU qw 0-39: model, params, viewProj, scroll / light / env).
- What still goes through the walk (2D, HUD, text, full-screen passes, P8, the overlays' own programs) gets a
  fast path: DIRECT / PATH3 GIF data handed to the GS side as a pointer and length, not copied qword by qword into
  the ring.
- **Gain**: game thread −0.3 to −0.5 s (the remaining walk is mostly 2D); GS worker −0.1 s.
- **Tested by**: as stage 5, plus the menus and the title (dktitle.x) run with the hooks on, since their chains
  are the ones that must still fall through.

### Stage 7: the GS worker retired

After stages 4-6 the GS worker's remaining work is the 2D GIF traffic and the frame's GS-side bookkeeping
(registers, targets, the frame copies of renderer-spec 4.15-4.17). That is small enough to run where it is
produced.

- The register file and target bookkeeping move into the recording (the GPU thread) as ops, and the GS worker
  thread is removed. Core 1 is then free: the sound's tick and mix threads move there (`sndcore=1`), and the
  game thread no longer waits on the worker.
- The GS memory model stays for what reads it back (stage 4's lazy stores, the frame copies), as a library the
  recording calls, not a thread.
- **Gain**: the game thread's ~0.4 s of waiting for the worker; one whole core for sound and headroom.
- **Tested by**: worker-order digests replaced by recording-order digests over the Dive, the title, the menus
  and Destiny Islands; every gxmcheck picture identical to stage 6's.

### Stage 8: sound on the Vita natively

**Steps 1 and 2 done 2026-10-31** (sound-spec 6, "The driver as C and the mix in passes"): the whole driver is
translated to C at build time rather than function by function, and the mix runs in passes with NEON sums; host
output byte-identical, ~2.5x fewer ARM instructions. Waiting on a Vita log for the real numbers.

Three steps, cheapest first; each stops if the sound line shows no short buffers and its threads' time is small:

1. **More of the driver as C**: profile the IOP instructions per function on the Vita (the interpreter counts
   them), and turn the hot ones into C the way func_00150 / 00434 / 004f0 / 0d8dc were (patched only on a
   matching hash, `KH1_HOST_IOP=nonative` turns them off). The per-tick sequencer and voice loop are the
   candidates. Gain: the tick thread's time roughly halved.
2. **The mix in NEON**: spu2.c's ADPCM decode, the 4-point interpolation and the volume mix four or eight
   samples at a time, and the reverb's taps. Gain: the mixer thread's time roughly halved (the title's music kept
   it busy ~1.2 s per 2 s).
3. **The Vita's own voices (optional)**: sceNgs plays PS-ADPCM (VAG) voices and has a reverb, so the SPU2's voices
   could map to NGS voices and the mix leave the A9. It does not match the SPU2 exactly (ADSR rates, the reverb
   algorithm, no pitch modulation), so it is a choice to make only if 1 and 2 are not enough.

- The driver itself (sequences, banks, the SE table) stays the disc's: rewriting it from its formats is not
  planned (sound-spec 6 explains why the port runs it).
- **Tested by**: tools/host/sndplay.c's WAV over music110 and the Dive run's WAV byte-identical for steps 1-2 (a
  NEON mix may differ by rounding: then within one LSB, checked by a sample compare); the Vita's sound line.

### Stage 9: NEON in the game's hot math

Last, because it only matters once the game thread's own code (~0.66 s per 2.4 s in the Dive) is the limit.

- First a profile of game code on the A9 (the qemu instruction counter of session 143 per function, then a Vita
  log): matrix and vector helpers (libvu0.c's sceVu0 calls, port code already), the skeleton build
  (func_00163490 and P21's Euler to matrix, renderer-spec 2.4), collision (mapcoll / colobj), particles (ppp).
- libvu0.c is port code: NEON it directly. For game functions, a **port override table**: the Vita build links a
  hand-written NEON function in place of the matching C by name, listed in one file, with the matching C kept
  and a host test comparing both on recorded inputs (bit-exact, or within the tolerance the caller allows, as
  vu1nat=2 does for the VU1 programs).
- **Gain**: game thread −0.1 to −0.2 s; more in busy rooms with many skeletons.
- **Tested by**: per-function differential tests on inputs captured from a Dive run; the census and pad
  scripts reaching the same frames with the same positions (dive_en.txt to 91,000).

## Where that should end

If the estimates hold: the game thread near 0.8-1.0 s per 2.4 s window (the game's own code and a little 2D
walk), the GS worker gone, the GPU thread near 1.2-1.5 s with static buffers and batching, sound on the freed
core. That is a steady 30 pictures/s in the Dive with roughly a third of each core spare, which is the room
busier scenes (Traverse Town, battles with many skinned enemies) will need. 60 is not the goal: in rooms the
game paces itself to two fields a frame (`D_002BBE0C` = 1, renderer-spec 4.15). Its time step scales with the
fields passed, so a 60 fps mod (that interval 0 in rooms) is possible in principle once there is that much
headroom, but whether the game's logic behaves at half the step is untested; it is not part of this plan.

| Stage | Main thread helped | Expected gain (per 2.4 s) | Size |
|---|---|---|---|
| 0 Baseline | (measurement) | none | small |
| 1 Static buffers, batching | GPU thread | −0.4 to −0.8 s | one thread |
| 2 Renderer B's rest | game (lit rooms) | −0.1 to −0.3 s | one thread |
| 3 Renderer A's rest | game (fogged rooms) | −0.1 to −0.4 s | one thread, parallel with 2 |
| 4 Textures from source | GS worker | −0.3 to −0.6 s | one thread |
| 5 Renderer B as native calls | game, GS worker | −0.4 to −0.7 s | one to two threads |
| 6 Renderer A as native calls, fast 2D walk | game | −0.3 to −0.5 s | one thread |
| 7 GS worker retired | game (no waits), a free core | ~−0.4 s of waiting | one thread |
| 8 Sound native | sound threads | about half their time | one thread |
| 9 NEON game math | game | −0.1 to −0.2 s | one thread |

Stages 2 / 3 and 8 can run alongside the others. Stage 1 waits for stage 0's numbers; 5 and 6 build on 1's
cache; 7 needs 4-6.

## Hard parts (be direct)

- **Draw order**: the draw list's key order is the painter's order (renderer-spec 4.2). Native calls in stages
  5-6 must record into the same place in the frame as the chain would have; batching (stage 1) only joins
  consecutive draws with the same state.
- **Things that read VU memory or GS memory back**: native-renderer.md lists what `nd_*` leaves unwritten; a
  native call skips VU memory entirely, so any later reader of it must be found first (the check modes above are
  for this). The same for GS memory in stage 4.
- **The overlays' programs** (gb.x / wm.x's five Gummi programs) are not in any stage: they are needed only once
  the Gummi ship runs natively, and should follow stage 3's pattern then.
- **Sound exactness**: steps 1-2 of stage 8 keep the output identical or within an LSB; NGS would not.
