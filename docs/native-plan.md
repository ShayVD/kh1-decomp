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

### Native payloads straight to the GPU thread (2026-11-02, config.txt `natdirect=1`, host-measured)

The Vita's fight log of 9a95cf9 (frame 10,444, a 2.12 s window, renderer=native) had the GS worker saturated: 2,094 ms
busy, the game waiting 512 ms for it. Its two biggest ops, mapped with this build's symbols (dmawalk.o compiled with
vitasdk's flags: the log's `81134f79` is `w_native_ref` at dmawalk.o + 0x2d8, so the log's base for that file is
0x81134ca0): **`w_block` 853 ms** (6,357 calls: the GIF channel's and DIRECT's blocks, gif_block on stream 0) and
**`w_native_ref` 565 ms** (15,546 calls, ~36 us a native run). The rest: w_load 188, w_qwords (0x6f0) 152, the frame op
123, w_load_big 95, w_path1 (0x254) 38, w_send (0x30) 12, w_xshift / w_xstretch (0x1c / 0x24) 6 each, w_kick (0xb84) 8.

On x86 (callgrind, the same fight, frames 10,400-10,460 on the host's gxmcheck binary) w_native_ref is only ~6 % of the
worker's instructions, so on the A9 its cost is mostly memory, not instructions: the worker read each payload's header,
matrices (the join checks) and every record's first qword, all written on the game thread's core, then copied the header
and matrices into the recording queue for each op it opened, and put three ops a run.

**What natdirect does** (dmawalk.c `nat_sum` / `w_native_dir`, gsregs.c `kh1_gs_native_sum`, pipes.c `nat_direct` /
`r_nat_dir` / `r_nat_dend`):

- **The game thread sums up each payload as it hands it over** (path1_take, path1_draw): the vertices, the triangles, the
  PRIM the first record's PRE writes, the records and the program, read from the records it has just written (still in
  its cache). The summary rides in the GS queue's op beside the reference (two qwords a payload).
- **The worker reads none of the payload** when its records are all drawn in one PRIM (the first record's PRE, or none,
  and every later PRE the same PRIM): one PRIM write and one gs_native_n from the summary, which are exactly the bulk
  path's writes and counts for such a payload. It keeps only what decides a join without the payload's bytes: the PRIM
  and GS state generation the GPU thread's open op was drawn in. When either changed (or the worker's own op is open) it
  ends the op first (nat_flush, as nat_rec would have); the state op goes as before (prim_state, a no-op on a join); then
  one recording op with the payload's reference.
- **The GPU thread does nat_hook's and nat_rec's work for it** (r_nat_dir): P0's join (same header and matrix), P13's
  (same header, its matrices added), an op opened at the first record that fits, ended where a record would not fit and
  at the payload's end unless it is P0's or P13's; then it frees the pool up to the payload's end. It read every record
  already (r_nat_rec), and now reads the header and matrices from the pool instead of from the recording queue's copy.
- **nat_flush ends an op the GPU thread may hold** (r_nat_dend) before any other recording op, as it ends the worker's own.
- A payload with a PRIM change among its records goes natref's way (w_native_ref's body). In the Dive and its fights
  there are none: 1,325,562 payloads to frame 12,000, all direct.

One case is not op-for-op the same: a P13 run whose header joins the open op but whose PRIM or GS state changed. natref
added its matrices to the old op and then ended it (an op with matrices no vertex uses); natdirect ends it first. The
pictures cannot differ (the unused matrices draw nothing), and the host's hashes did not.

**Checked (host, en.iso, dive_en.txt, gxmcheck binary, `KH1_HOST_TRACE=5 KH1_HOST_GSQ=1 KH1_HOST_GPUQ=1 KH1_HOST_RECQ=1
KH1_HOST_VU1=1 KH1_HOST_VU1TR=1 KH1_HOST_NATIVE=1 KH1_HOST_WIDE=1 KH1_HOST_NATCHAIN=1 KH1_HOST_CD=go`, to frame 12,000,
through the fights the Vita log measured)**: all 96 GPU target hashes (KH1_HOST_GXM=250, KH1_HOST_GXM_HASH=1) identical
with main (9a95cf9) and with natdirect, also with `KH1_HOST_NATPOOL=262144` (a 256 KiB pool that wraps often); the 240 GS
digests at trace 2 (`KH1_HOST_GSQ_CHECK=50`) identical; the same native run, triangle and join counts.
`natdirect=0` (host `KH1_HOST_NATDIRECT=0`) is natref's path, unchanged.

**w_block, the 853 ms op.** In the host's fight the blocks carry the 3D target slot's texture streams: 11 T8 uploads of
128 x 128 (16 KiB, BITBLTBUF 0x3600, bw 4) and their 11 CLUTs (16 x 16 CT32 at 0x3700) a picture, one texture after
another through the same slot, so the same-bytes skip (kh1_gsmem_image_same) never matches. On x86 the decode
(kh1_gsmem_image) and the compares are half the worker, but on the Vita band_t8 stores a block with NEON, so ~180 KiB a
picture should cost a few ms, not 850. The VPK's new `gs blocks:` line measures it: the IMAGE pieces' time, KiB and skips
inside the worker's blocks and kicks, against w_block's total. If the images are small there, the rest of w_block is
the GS path's register and vertex packets (gif_qword, gs_kick), and the next step is counting those, not the uploads.

**Vita (Shay, 2026-11-02, the natdirect VPK, defaults, dive_en.txt to frame 29,218; ops mapped at +0x7b001 over
out/vita/kh1.elf)**: no errors; 4,295,310 payloads direct, none read by the worker. This build also has the C sound
driver back (sound ticks ~220-280 ms a window, was ~780), so the frame rates below are both changes together; no
natdirect=0 run was made.

| Stretch (frames) | 9a95cf9 | natdirect VPK |
|---|---|---|
| Fight, 10,092-11,544 (frame 10,444 / 10,460 for the ops) | 17-18 heaviest, 22-29 typical | 27-30 |
| w_native_ref / w_native_dir at that frame | 565 ms, 15,546 runs (36 us a run) | 307 ms, 15,986 runs (19 us a run) |
| Fights 18,000-23,000 (26b3b0b's 13 pictures/s ones) | (not reached) | a steady 22-23 |

In the 18,000-23,000 fights the worker is the limit again: ~2.1 s busy, the game waiting ~770 ms a window, **w_block
~1,000 ms of it, but the `gs blocks:` line puts the IMAGE pieces at only ~180 ms (~11.5 MiB, ~1,400 pieces, ~300
skipped)**. So ~800 ms of w_block is the GS path's register and vertex packets (gif_qword, gs_kick, the A+D writes),
not uploads: the next worker target. w_native_dir's remaining ~19 us a run (prim_state, the recording queue's put,
nat_flush, the op's two clock reads) is the second. In the 10,000-11,500 fight the GPU thread is the limit instead
(1.84 s run clock; the worker's frame op waits ~535 ms for it). Frames 17,300-17,700 run at ~13 with the worker idle
(the game thread at ~1.9-2.0 s): a game-thread stretch, not this path's.

**Measured before that run**: the `gs worker ops:` line's w_native_dir (dmawalk.o's address of it, from this build)
against w_native_ref with `natdirect=0` (in the natdirect VPK's out/vita/kh1.elf: w_native_dir 0x810dd144, w_native_ref
0x810dd0c4, w_block 0x810ddac4; map the log by its w_block, the offset differs per run), the GPU thread's run clock (it does the joins now), and the fight windows'
pictures/s. Expected (estimate): most of w_native_ref's ~0.55 s off the worker, ~0.1 s more on the GPU thread.

### The GS worker's packets by sender, and repeated CLUT loads (2026-11-02, config.txt `clutskip=1`, host-measured)

The natdirect VPK's fights (frames 18,000-23,000) left w_block at ~1,000 ms of the worker's ~2.1 s window with its
IMAGE pieces at only ~180 ms. This change measures the rest by sender and cuts the largest non-image cost the host shows.

**What is counted (dmawalk.c `KH1DmaSender`, `kh1_dma_senders_take`).** PlatDmaSend (plat_null.c) and
kh1_dma_gif_direct store their return address in `kh1_dma_sender` before the walk; gs_block hands it to the worker in
w_block's second argument, and the worker adds each block's time (kh1_vu1_clock, two reads a w_block, ~5,800 a window)
and its qwords by kind to that sender's slot: GIF tags, PACKED register qwords (vertices and the rest but A+D), A+D
writes, REGLIST registers, IMAGE qwords. The Vita prints the eight slowest each window as
`gs senders (w_block by the send's caller): ADDR N ms (blocks, K qw: tags, K packed, K A+D, K reglist, K image), ...`;
the addresses map with out/vita/kh1.elf's symbols at the same offset as the `gs worker ops:` line's (in the VPK built on main 45eecda,
w_block is 0x810ddc60, w_native_dir 0x810dd264; func_0015ff78 0x81065734, func_00237018 0x8102c780, func_00106b18
0x8102a1dc). The host prints the same with `KH1_HOST_SENDERS=FROM:TO KH1_HOST_CLOCK=1` (`addr2line -f -e` the binary).

**Host, frames 18,000-21,000 (en.iso, dive_en.txt, the gxmcheck binary, x86 times):**

| Sender (the send's caller) | worker ms | blocks | what the blocks carry |
|---|---|---|---|
| func_0015ff78 (mdlgs.c: the models' texture streams) | 780 | 137,170 | 35.5 M qwords, 34.9 M of them IMAGE, 466 K A+D (the transfer registers) |
| func_00237018 (gspkt.c: the HUD's and effects' packet sender, 72 callers) | 341 | 19,811 | 604 K PACKED, 462 K A+D (TEX0 / TEX2 with CLUT loads, sprites), 77,840 tags |
| func_00106b18 (dmapool.c's pool send) | 84 | 8,612 | 294 K PACKED, 284 K REGLIST, 34 K A+D |
| func_00242c08 (gauge.c) | 38 | 5,685 | 946 K IMAGE |
| func_001274c8 (shadow.c) | 24 | 9,088 | 125 K A+D |

func_00237018 is a wrapper, so its line is the 72 HUD / effect callers together; the host's call graph splits them.

**Where the non-image part goes (host callgrind, `--separate-threads=yes`, instrumentation on at frame 18,000 for 300
frames; the GS worker 2,657 M instructions):** w_block 925 M, of it the images 720 M (kh1_gsmem_image and the
same-bytes compare) and gif_qword 216 M. Of gif_qword: **TEX0 / TEX2 writes 131 M** (kh1_gsmem_tex0: the CLUT load,
then pipes.c on_clut: the conversion, the palette cache, a recording op, a native op's end, a texture lookup after),
vertex kicks 87 M (gs_kick and the recorder's prim op). w_native_dir 212 M: nat_direct 152 M, **130 M of it prim_state**,
almost all its texture lookups (kh1_texcache_get 163 M in all, 108 M of it decoding the 3,617 textures that changed);
kh1_gs_native_sum 55 M. 935,045 CLUT loads to frame 21,000, about half with the TEX0 and TEXA of the load before.

**clutskip (pipes.c on_clut).** A load is left out when it has the last load's TEX0 and TEXA, its entries are the
same conversion (gsmem.c's id, which changes when the CLUT's words do), the palette cache answers the slot the
recorder still has bound with nothing to fill, the CLUT's corners are not in pages a draw marked (the GPU's pixels,
which the model does not hold), and no palette op, upload or frame op came since. Such a load binds nothing new, so
its clut command (a batch break and a transfer command on the GPU thread), the native op's end before it and the
texture lookup it would set off are not sent. 0 (host `KH1_HOST_CLUTSKIP=0`) sends every load as before.
Also nat_direct calls prim_state only when it has work (a state change, or a texture lookup pending).

**Checked (host, en.iso, dive_en.txt to frame 21,000, the gxmcheck binary, `KH1_HOST_TRACE=5 KH1_HOST_GSQ=1
KH1_HOST_GPUQ=1 KH1_HOST_RECQ=1 KH1_HOST_VU1=1 KH1_HOST_VU1TR=1 KH1_HOST_NATIVE=1 KH1_HOST_WIDE=1 KH1_HOST_NATCHAIN=1
KH1_HOST_CD=go KH1_HOST_GXM=250 KH1_HOST_GXM_HASH=1`)**: all 168 GPU target hashes (84 pictures, display and 3D target)
identical with main (ae76225); 167,282 of the 935,045 CLUT loads left out; GXM draws 2,032,690 -> 1,893,921 (-7 %), GPU
vertices -8 % (the native joins a CLUT command no longer ends); make test passes.

**The Vita's new lines, to read from the next fight log**: `gs senders` (which code the ~800 ms of non-image w_block
belongs to on the A9; the host's x86 split is not the Vita's: images are 78 % of w_block here and ~18 % there), and
`gs worker's CLUT loads (clutskip=1): N, N of them repeats left out, N ms; texture lookups: N, N decoded, N ms` (the
worker's CLUT loads and prim_state's texture lookups, the host's main costs of the non-image packets and of
w_native_dir). If the lookups' decodes are most of w_native_dir's ~19 us a run on the Vita, the next cut is the
texture from its upload's source bytes (stage 4) rather than a second unswizzle out of GS memory.

**Vita A/B (2026-11-02, Shay's Vita, unattended over vitacompanion with tools/vita/hw_run.sh, the merged VPK on main
45eecda, `renderer=native frames=23000 pad=dive_en.txt`, clutskip=1 then 0)**: both runs reached frame 23,000 and
stopped cleanly (each left one psp2core dump at the exit: a data abort in the kh1_gpu thread inside SceGxm during
teardown, the same kind the natvbjoin run left at its frames= exit; not this change's). Frames 18,000-23,000: 25.5 / 25.4
pictures/s. The last window (frame ~22,900):

| | clutskip=1 | clutskip=0 |
|---|---|---|
| gs worker busy; the game's wait for it | 2,110 ms; 107 ms (20 waits) | 2,070 ms; 163 ms (27 waits) |
| gs blocks: blocks, qwords; images' pieces, KiB, ms | 4,628, 682 K; 1,197, 10,156, 142 | 4,593, 670 K; 1,175, 9,995, 147 |
| top sender (the texture streams) | 198 ms, 3,032 blocks, 672 K qw (657 K image) | 202 ms, 2,936 blocks, 651 K qw (638 K image) |
| CLUT loads: all, left out, ms | 4,659, 1,189, 59 | 4,575, 0, 57 |
| texture lookups: all, decoded, ms | **2,770, 0, 243** | **3,819, 0, 229** |

So on the hardware clutskip leaves ~25 % of the loads out but saves no measurable time (the loads cost ~13 us each);
it stays on (fewer draws on the host, no cost seen). In these unattended runs the worker's blocks are light (the game
waits ~0.1-0.16 s for the worker, not the hand-played fight's ~0.77 s), so the ~800 ms of non-image w_block that log
showed was not reproduced. The clear finding is **the texture lookups: ~240 ms a window, none of them decoding**, i.e.
~60-90 us a lookup spent on the stamp and target scans (tex_scan over the texture's pages) and the cache's search, set
off by every upload and CLUT load (tex_look). That is the next cut: no lookup after an upload or load whose pages miss
the bound texture's and CLUT's, and a cheaper hit path.

### Texture lookups by page lists (2026-11-02, config.txt `texskip=1`, host `KH1_HOST_TEXSKIP`)

The clutskip A/B above showed ~240 ms a window of texture lookups on the Vita with none decoding (~60-90 us each),
set off by every upload and every CLUT load (pipes.c `tex_look`), most of them finding the texture they found last
time. Two cuts, both on the GS worker (host/null/pipes.c, host/null/gsmem.c):

- **The stamp and target from a page list (gsmem.c `tex_pages`).** `tex_scan` answered a texture smaller than a page,
  or one whose pages name two targets, by a `kh1_gsmem_addr` a block (a 256 x 256 T8 is 256 calls), and its memo
  goes stale on every upload (`marks` moves). Now each TEX0 layout's pages are listed once, in the block walk's order
  (each page where its first block falls), up to 64 pages, 64 layouts kept by a hash of TEX0's layout bits; the stamp
  is the newest of their `page_seq` and the target the first listed page with drawn bits, which is the walk's answer
  (the first block in a drawn page lies in the first drawn page of the list). A list hangs on the layout only, so it
  never goes stale. Over 64 pages the walk runs as before.
- **No lookup that would find the last one's answer (pipes.c `tex_lookup`).** When the TEX0, stamp and target are
  the last lookup's of this frame, `kh1_texcache_get` would hit the same entry (nothing else touches the cache in
  between) and the texture op would bind the slot the recorder already has (cmdbuf.c `kh1_cmd_texture`: no decode, no
  batch break), so neither runs, and no native op is ended for it. The palette half (the draw's CLUT entries against
  the bound slot) runs only after a CLUT load or a state change (`pal_look`): the CLUT buffer and the bound slot
  change nowhere else. A frame op starts both afresh (the first lookup marks its entries the frame's).
  `texskip=0` (host `KH1_HOST_TEXSKIP=0`) looks every time as before; the page lists stay on either way.

The Vita's lookups line now reads `texture lookups (texskip=1): N, N the last one's texture, N decoded, N ms`, and
the host prints `texskip=1: N texture lookups, N of them the last one's texture, N decoded` at the end.

**Expectation on the Vita.** The GS packet thread's hardware fight run (main 3157883b) has the GPU thread (~1.8 s a
window) and the game thread (~1.65 s) busier than the GS worker (~1.4 s), with the game waiting only 0-100 ms for the
worker, and the lookups at ~220 ms a window. So this frees worker time (the lookups line should drop most of its ms)
without necessarily raising pictures/s by itself.

**Checked (host, en.iso, dive_en.txt to frame 21,000, the gxmcheck binary, the clutskip section's environment, on the
Mac in a colima VM with qemu-i386 8.2)**: all 168 GPU target hashes identical with main (3157883b).

**Vita A/B (2026-11-03, Shay's Vita, tools/vita/hw_run.sh, `renderer=native frames=23000 pad=dive_en.txt`, both with
the black-Dive sinf/cosf fix of main 50d21c96; the branch's build also timed each step of a lookup)**: both reached
frame 23,000 and stopped cleanly. Means over the last 42 windows:

| | main | texskip=1 |
|---|---|---|
| texture lookups a window; ms; us each | 4,344; 603; 139 | 4,092 (~37 % the last one's texture); 544; 133 |
| gs worker busy; the game's wait for it | 2,002 ms; 700 ms | 1,968 ms; 849 ms |
| pictures/s, frames 18,000-23,000 | 19.4 | 18.9 (one run each: noise) |

With the fix the Dive draws its real scene and the lookups cost ~600 ms a window (the earlier ~240 ms was the collapsed
picture's). The page lists took the stamp and target to **5 ms** a window and the repeats save ~60 ms, but
**`kh1_texcache_get` is ~508 ms of the 544**: the time is in the cache on a stamp miss (the texture's pages' stamps
moved, so it reads the pages' raw words, `kh1_gsmem_tex_raw`'s 8 KiB a page copied and compared, and on a miss there
hashes the texels), not in the scans; the op is 8 ms and the palette check 18 ms. That is the next cut: keep the
raw words' check from copying (compare in place, or a per-page content id gsmem.c keeps as it stores), or key the
entries by the upload's source as stage 4 plans.

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

**Batching (2026-11-01, config.txt `natjoin=1`, the default; `natjoin=0` / host `KH1_HOST_NATJOIN=0` a draw a run)**.
The Vita's fight log (build 26b3b0b) had the GPU thread at 65 ms a picture, 57 of it recording, with 492 draws a picture
against the early Dive's 162: each native run was its own draw command (cmdbuf.c `native` broke the batch before and
after it). Now cmdbuf.c `nat_join` appends a run to the native draw before it when that is the list's last command with
the same batch key (pipelines, uniforms, sampler, TEX0, target, scissor), texture entry and palette slot, cull mode and
vertex kind (plain / skinned), the two runs' matrices fit u_m (KH1_NAT_MATS, 32) and both rings' heads are still just
after the command's vertices and matrices. The run's vertices and folded matrices go on the end, its vertices' matrix
indices (pad[0], or a skinned vertex's mi / mi2) moved past the command's earlier matrices: the same triangles in the
same order, in one sceGxmDraw, without new_cmd's uniform block, sampled() lookup or batch bookkeeping for the run. A
transfer, CLUT load or texture upload between two runs is a command of its own, so it ends the join, and a texture bind
without one changes r->tslot, which is checked.

Checked (host, en.iso, dive_en.txt to frame 9000, the gxmcheck binary, `KH1_HOST_TRACE=5 KH1_HOST_GSQ=1 KH1_HOST_GPUQ=1
KH1_HOST_RECQ=1 KH1_HOST_VU1=1 KH1_HOST_NATIVE=1 KH1_HOST_WIDE=1 KH1_HOST_GXM=250 KH1_HOST_GXM_HASH=1`): all 72 GPU
target hashes (36 pictures, display and 3D target) identical with natjoin 0 and 1. GXM draws over the run 612,111 ->
438,963 (-28 %), GXM calls 1,829,870 -> 1,483,574 (-19 %); in the Dive's 3D stretch (frames 4500-8999) the mock's draws a
picture roughly halve (e.g. frame 5999 201 -> 98, 7999 187 -> 95). Of 387,759 native runs, 173,148 joined the draw
before; of the rest 125,925 came after another command (a transfer, CLUT or texture command, or a non-native draw),
88,686 found no room (mostly the 32-matrix limit), none had another state, cull mode or vertex kind. tests/host/cmdbuf_test.c
"natjoin" (5 checks): two runs in one draw with the second's indices moved, a cull change, a transfer and the 32-matrix
limit each ending a join, natjoin=0 a draw a run.

**Not yet measured on a Vita**: the `native renderer:` line's new "N of the draws joined into the one before", and the
`gpu thread` / recording lines with natjoin=1 against natjoin=0, ideally in a fight. Expected (estimate): the GPU thread's
per-draw cost (two default uniform buffer reserves, the uniform copies, the stream and the draw, gxmrec.c's ops) cut by
the ~30-50 % fewer draws, 12-18 ms a picture in fights if the 492 draws cost what the plan assumed.

Next steps the counts suggest: u_m past 32 matrices (u_m[256]: the "no room" runs, if the Vita's shader compiler and
the default uniform buffer take it), and the commands that come between native runs (the 126 K "after another command";
a frame's command list, pipes.c's dump, names them).

**Static vertex buffers: not done, and why.** The plan keyed a cached batch by the record's hash. On the GPU thread a
run's conversion (natdraw.c with recfast: each strip vertex converted once, its triangles 32-byte copies) reads each
record word once, which is what hashing it would cost, and a hit would still copy the cached triangles into the vertex
ring (gxm.c then copies the whole slot into GPU memory). So a CPU-side cache keyed by a hash saves almost nothing. The
cache pays only when it skips both the read and the copy: a key that does not read the records (their address in the
game's memory, which the "Read P18/P0 records straight from the chain" thread is making available; the pool's copies
have no stable address) and a draw that reads persistent GPU memory instead of the ring (gxm.c's stream from a cached
block, which a joined draw cannot mix). That is the follow-up once records come straight from the chain.

### Static vertex buffers by the records' address (2026-11-02, config.txt `natvb=2`, the default)

Built on natchain (records read from the chain's own words, so a run's records have an EE address) and natdirect (a
payload reaches the GPU thread whole). Code: natdraw.h / natdraw.c `kh1_natvb_*` (the cache), vu1_draw.h `nb_hit` and
the natvb branches of `nd_18` / `nd_10` (the game thread), pipes.c `r_native`'s KH1_NAT_VB branch and cmdbuf.c
`kh1_cmd_native_vb` (the GPU thread), gxm.c (the indexed draw, the GPU memory and the fence).

**What is cached.** Renderer B's runs of P18, P11 and P10 whose records natchain reads from one held unpack. Key: the
unpack's words' address and length in qwords, the program, and the run's colour (vf01), F (vi12) and the two flags
(every vertex ADC, the cull bit) since those are baked into the GPU vertices. An entry holds, in GPU memory, each strip
vertex once (natdraw.c's `put`: the same 32-byte KH1GpuVert the uncached path makes, P11's lin bit in mi) and the
triangles kh1_nat_tris would list, as 16-bit indices into them; and on the CPU, the stub records a hit sends and the
matrix plan: each payload matrix either the stream's qword (renderer-spec 2.3: `func_0015fd20` rewrites the op 0
records' matrices in place every frame) or the slot register the run read, plus the slots' last loads.

**A hit** (the entry is there and the stream's words outside the matrix records' bodies hash as they did when it was
made) hands over: the header, one 2-qword `KH1_NAT_VB` record a strip (its first qword as before, so natdirect's
summary, the GS worker's counts and the PRIM are unchanged; then the entry's vertices, the strip's first index, its index
count, a sequence number) and the matrices read from the stream and the registers. The game thread does not parse or
write vertices; the pool gets ~2 qwords a strip instead of 1 + 2 a vertex; the GPU thread folds the matrices and records
one draw command whose vertices and indices are the entry's (`KH1Cmd.xv` / `xi`), with nothing copied into the vertex
ring; gxm.c draws it with `sceGxmDraw(..., U16, xi, n)` from the entry's vertices. The slot registers are left as the
parse would leave them. A miss parses as before; an entry is made the second time the same key and words are seen (a
colour that changes every frame makes none).

**Words changed in place.** `natvb=1` hashes every qword of the stream but the matrix bodies on every hit (4 lanes,
about one multiply a word; on the Vita that costs as much as the parse, see below); `natvb=2`, the default, hashes one
qword in 8 (a rewrite that misses those qwords would go unseen; the Vita logs saw no rewrite at all); a hash that
differs drops the entry. Host `KH1_HOST_NATVB=3` also parses every hit and
compares its matrices, header, slot loads and expanded triangles with the entry's (`hits differed from their parse` in
the host's last lines).

**Memory and reuse.** 16 MiB (config `natvbmb=`) of GPU-mapped uncached memory on the Vita (malloc on the host) and 2 MiB
of CPU memory, both rings in allocation order. The oldest entry goes first, and only once no frame still to be drawn
names it: each hit's sequence number goes into its frame's command list (`KH1CmdRec.xseq`), and gxm.c, after
`sceGxmFinish` at the next frame's start, publishes the previous frame's highest number (`kh1_natvb_done`). An entry
still in flight is taken out of the lookup instead (its number stops growing) and that allocation is skipped. Without a
GPU renderer (the plain host) the frame op publishes at the frame's end.

**Draws.** A cached run is one draw of its own: it does not join the native draw before it (natjoin), because its
vertices carry their matrix indices from the run's own numbering (2026-11-02: cached runs now join each other, see
"Cached runs joined" below). So a frame of cached runs makes more draws than
natjoin's; whether the cheaper runs outweigh that is the Vita A/B's question (the log's `natvb=` line counts the draws
from GPU memory).

**Vita A/B (2026-11-02, three logs of the Dive against the natdirect log of the same morning).** Game-thread time a run
(the `vu1 programs` lines over the whole log): P18 / P11 / P10 43 / 43 / 60 us without the cache, 44 / 45 / 59 with
`natvb=1` (hashing every word reads the whole stream, as the parse does; a guess: both bound by the reads), 20 / 21 /
38 with `natvb=2`. About 1.6 M hits a log, 5-9 % misses, 0 entries whose words changed. Draws a frame 54 -> ~85 (the
cached runs do not join), GPU submit time unchanged (~1.0 s a 2.1 s window). Pictures/s in the same stretches about
equal, +1 at most: the GS worker and the GPU thread are each busy ~1.5-1.7 s a window too, so the game thread's saving
does not show by itself. `natskin=1` on top: P13 55 against 59 us a run, no visible change; it stays off. A freeze at
the Dive's end in one log (game thread stopped after a vblank wait, every queue empty, 88 disc reads, last send
0x814016e0) has the same signature as the 2026-10-30 log's, before natvb: an older hang.

**Host run (2026-11-02, the dive pad, 7000 frames, gxm mock hashing 1 frame in 50):** natvb 0, 1 and 2 draw the same
pictures bit for bit (145 K hits, 12 K misses, 535 entries, none changed); only the draw counts differ. Check mode
(`KH1_HOST_NATVB=3`) first reported 918 hits differing and drew a few triangles differently: kh1_natvb_check called
kh1_nat_tris, whose kh1_nat_once scratch (`sv`) the GPU thread uses at the same time, so the check raced the GPU
thread's own expansion. kh1_natvb_check now expands each triangle itself on the game thread; rerun: 0 hits differed in
145 K, pictures the same as natvb 0-2 (draw counts as natvb 1).

**Not cached**: P0 / P4 (renderer A's map batches: one record a run, joined on the GPU thread into one draw per object
and pass; per-batch cached draws would multiply the draws, so it waits for stage 6's object-level hook), P13 (its parse
reads VU memory), any run natchain does not read from the chain, and runs over 1,024 strip vertices.

**Checked**: tests/host/vu1chain_test.c (in tests/selftest.sh, x86 and qemu-arm with NEON): its six random streams run
three times with natvb 1, 2 and 3 against natchain=1 without the cache (2 only before the words change), comparing what is drawn (each B payload as its
header, record headers, matrices and expanded triangles), the registers at each hand-over, the program runs and VU
memory; then 400 data words flipped and the same again (entries whose words changed are dropped); the last two streams
in a 48 KiB arena so room is made and refused. Mutations each fail it: the hash check skipped, a strip's parity swapped
in an entry, a slot's last load dropped. The test publishes after every run, so it does not exercise the in-flight rule
(an entry freed while a frame still to be drawn names it); that rests on gxm.c's fence as described above.

### Cached runs joined (2026-11-02, config.txt `natvbjoin=1` / `natvbhome=1`, the defaults)

The natvb Vita A/B had draws a frame go from 54 to ~85, because a cached run was always a draw of its own: its vertices
in natvb's memory carry matrix indices from the run's own numbering (0 .. nmat - 1), so two runs could not share one
u_m. Now each entry is given a **home** when it is made (natdraw.c `kh1_natvb_learn`): the slot right after the
previous entry's matrices, back to 0 when the run's matrices would pass KH1_NAT_MATS (32). Its vertices are stored
with their matrix index plus the home (P11's lin bit kept), and the home rides in each stub's index-count word
(natdraw.h `KH1_NAT_VB_HOME` / `KH1_NAT_VB_COUNT`). Entries are made in the order their runs are drawn (each at its
second sighting), so a model's runs get consecutive homes.

On the GPU thread (cmdbuf.c `vb_join`) a cached run joins the cached draw before it on natjoin's conditions (the
list's last command, same batch key, texture entry, palette slot and cull mode, both rings' heads right after the
draw's matrices and indices) and one more: its home is at or after the draw's last matrix. Its matrices go into the
uniform ring at their home (the slots between are zeroed and never read; `KH1Cmd.mlo` is the draw's first slot, so a
lone run whose home is 20 uploads only u_m[20 ..]). The vertices stay where they are; the draw's indices become 32-bit
ones into natvb's whole memory, written into the frame's vertex slot (the first run's 16-bit ones converted when the
second joins), and gxm.c draws them with `SCE_GXM_INDEX_FORMAT_U32` from the memory's base. A run whose home is
before the draw's end (the homes wrapped, or the same entry twice) starts a new draw. Cost on the GPU thread: 4 bytes
written per index of a joined draw, against a draw's uniform reserves, uniform copies and gxmrec ops saved.

`natvbjoin=0` (host `KH1_HOST_NATVBJOIN=0`) draws each cached run on its own as before (with its home);
`natvbhome=0` (host `KH1_HOST_NATVBHOME=0`) gives every entry home 0, so nothing joins. The Vita log's new
`natvbjoin=` line counts the joins and why the rest did not join.

**Checked (host, en.iso, dive_en.txt to frame 11,500, gxmcheck binary, `KH1_HOST_TRACE=5 KH1_HOST_GSQ=1
KH1_HOST_GPUQ=1 KH1_HOST_RECQ=1 KH1_HOST_VU1=1 KH1_HOST_NATIVE=1 KH1_HOST_WIDE=1 KH1_HOST_GXM=250
KH1_HOST_GXM_HASH=1`)**: all 92 GPU target hashes (46 pictures, display and 3D target) identical with natvbjoin 1 and
0. GXM draws over the run 764,869 -> 577,024 (-25 %), GXM calls 2,316,129 -> 1,940,439 (-16 %); in the fights (the
pictures at frames 10,000-11,499) the mock's draws a picture average 101 -> 57 (e.g. frame 10,249: 142 -> 80).
tests/host/cmdbuf_test.c "natvbjoin" (6 checks: a lone run reads its entry's indices; runs with following homes in
one draw, an earlier home in its own; the 32-bit indices and each run's matrices at its home with the gap zeroed; a
lone run after a transfer uploading from its home; the 32-matrix limit; natvbjoin=0) and vu1chain_test (natvb 1-3
with homes: what is drawn, the check mode's comparison with the home taken off) pass.

**Vita A/B (2026-11-02, Shay's Vita, run unattended over vitacompanion with tools/vita/hw_run.sh, the PR's VPK,
`renderer=native frames=11600 pad=dive_en.txt`, natvbjoin=1 then =0; averages over the watchdog windows):**

| | natvbjoin=1 | natvbjoin=0 |
|---|---|---|
| Dive 5k-8k: draws a picture | **112** | 167 |
| Dive 5k-8k: pictures/s; GPU submit, recording, gpu thread (ms a ~2.16 s window) | 24.7; 1,113, 2,052, 1,895 | 24.8; 1,163, 2,035, 1,873 |
| fights 10k-11.6k: draws a picture | **68** | 110 |
| fights 10k-11.6k: pictures/s; GPU submit, recording, gpu thread (ms a ~2.14 s window) | 23.8; 857, 1,526, 1,472 | 24.1; 883, 1,478, 1,474 |
| GXM draws over the run | 586,432 | 767,604 |

The joins work on the hardware (the `natvbjoin=` line: 3,000-5,000 cached runs joined a window in the 3D stretches;
the rest after another command or with an earlier home) and both runs reached frame 11,600 with clean logs (skipped
draws 1,567 / 1,524 and 1,331 bad DMA sends in both: not this change's). But the frame rate did not move: draws a
picture fell by a third, the submit by ~3-4 % and recording not at all (within the ~6 % noise of runs). So the
per-draw GXM cost is small next to the rest of the recording; the GPU thread's time is in the commands' own
conversion and the uploads, not the draw count. In these runs no thread was full (gpu thread ~1.47 s of 2.14 in the
fights), unlike the hand-played fight logs (~1.84 s), so the fights here were lighter or differently paced; the
pictures/s are ~24 in both. Kept as the default: fewer draws, no cost seen. An earlier natvbjoin=0 attempt stopped at
frame 3,093 mid disc read with a crash dump (psp2core-1793629546, not analysed); the same build with natvbjoin=1
and a later =0 attempt both ran to the end, so it is not taken as this change's.

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

**First Vita run (Shay, 2026-11-01, the natchain VPK, natchain=1 only, no natchain=0 run alongside; dive_en.txt to
frame ~12,800)**: Shay found it ran well. The feed into VU memory fell to ~8 % of VIF1's time (e.g. 553 of 6,660 ms
in a 9.8 s window around frame 11,000), where 26b3b0b's fights log had it at about a third (1,383 of 4,224 ms per
5.6 s). The windows from frame 9,100 to 12,500 (enemies) ran at 21-28 pictures/s. 26b3b0b's fight windows ran at
~13, and nothing else was merged in between, but those were frames 20,000-21,700 of a different play-through, so
that comparison is not a clean A/B. The `natchain=` line
counted 36-114 K runs read from the chain per window. Still to do: the same route with `natchain=0` for a clean A/B.

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

## Beyond speed: the rest of the game native (added 2026-11-02)

Stages 0-9 make the Dive fast. They do not make the whole game run: some of it still has no native code, and
the port stops when it gets there. These tracks are about reaching the end of the game on the Vita, not
about frame rate. They are separate from the speed stages and can run alongside them, one thread each.
Same rules apply: kh1.elf, src/ and every overlay build stay byte-identical; the port's code lives in
host/port, host/vita and ovl/NAME/'s tables.

### Track A: the other nine overlays as native modules

Only dktitle.x, dkmovie.x's front end and xs_dh_break.x run as native C (native-overlays.md). wm.x (the
world map), gb.x (the Gummi ship), the six summons (xs_bambi, xs_dumbo, xs_genie, xs_mushu, xs_simba,
xs_tink) and xl_limit.x (limits) have none, so a call into one stops the port (vita-build.md, "Saves").
The mechanism is done (ovl.h, ovl.c, relocs.tsv, drafts.tsv, ovlnative.py); each overlay needs its tables
and C for every function its entry and data reach.

- **Status (session 142)**: wm.x runs as native C on the host from a save to "Select World", Depart and
  back into the field (native-overlays.md "Session 142", tests/host/pads/wm_en.txt). 31 of its 123
  drafts run on that route (tools/host/draftcov.py); none is checked against PCSX2 yet.
- **Order**: wm.x first (no world past Traverse Town without it), then gb.x (the Gummi flights between
  worlds, and gumisave.c's func_001b9c60 calling the editor through a stored pointer), then xs_simba /
  xs_genie / xs_dumbo / xs_bambi / xs_mushu / xs_tink as each summon is reached, xl_limit.x with the first
  limit.
- **Per overlay**: `tools/ovl/relocs.py NAME` for relocs.tsv; drafts.tsv rows for every unmatched function
  (session 141 left a near-miss draft for each one: overlay-plan.md "Stopping point"); the SDK calls it makes
  defined in sdk_host.c (the host link lists the missing ones); its tasks' pointers checked as
  native-overlays.md "What a port still has to do" says.
- **Near-miss drafts are not proven correct.** A matched function is the original's code; a draft that is
  a few words off is usually the same behaviour, but not always (valaudit.py found two drafts passing the
  wrong argument). Before an overlay goes native, the drafts it uses get a check: run the overlay's room
  on the host with each draft against a PCSX2 run of the same pad script (positions, script state, GS
  digests where the host has them), and keep a list of drafts that have been checked this way. Matching
  more of them (overlay-plan.md) shrinks the list.
- **Hard parts in the overlays**: gb.x's VU0 / sq functions and any MMI asm need C or NEON equivalents for
  the ARM build, as dkmovie.x's mpeg_mmi.s did; wm.x is 1,105 functions, so a whole-overlay native run is
  bigger than the three done so far put together.
- **gb.x / wm.x's five Gummi VU1 programs** (renderer-spec 2.5) first run as translated VU1 programs, like
  P1-P8 today (vu1tr=1); moving them to the GPU follows stage 3's pattern once the Gummi ship plays.
- **Tested by**: a pad script for each overlay (world map open and a world chosen, one Gummi flight, each
  summon and a limit), reaching the same frames on the host and the Vita as in PCSX2.

### Track B: movies

dkmovie.x's player is behind `PlatMovie*` but has no decoder: every movie ends at once (opening, world
intros, ending). The PSS files are MPEG-2 video for the IPU, with PCM sound the SPU2 model does not take
yet (vita-build.md, "Sound").

- **The choice** (vita-port-plan 3, still open): transcode the user's PSS files to H.264 MP4 once, at
  install time on their computer (needs ffmpeg there; plays with sceAvPlayer on the Vita's hardware
  decoder), or link a software MPEG-2 decoder (libmpeg2 is GPL: check against the repo's licence first;
  costs CPU on the A9). Transcoding is the likely pick: no decode cost on the Vita and no licence question.
- The movies' sound: either part of the transcode (one audio track in the MP4) or the core PCM input
  (BlockTrans) added to the SPU2 model.
- **Tested by**: the opening and one world intro playing with sound, and the game's own timing (it waits for
  the player's end) unchanged.

### Track C: the gaps the Vita runs still show

From vita-build.md: loading a save, the HUD's party portraits and panels are garbled textures and the Load
Menu's windows and text do not draw (the GPU path's 2D). These are renderer bugs, not missing code, but a
playable port needs them fixed; they go to whichever thread has the 2D path at the time.

### What is already native and needs no track

- The main ELF's game code: 6,982 of 6,988 functions matched; the other 6 run from drafts (shift/drafts.tsv),
  with the same caveat as track A's drafts but on paths every run takes.
- The sound driver (translated at build time, stage 8) and the SPU2 mix in C and NEON.
- VU1 programs with no native form yet are covered by stages 2 and 3, except P9 and P21, which jump outside
  themselves and stay on the interpreter (vita-build.md "VU1"): they need a look once a log shows them hot.

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
- **The overlays' programs** (gb.x / wm.x's five Gummi programs) are not in the speed stages: they come with track
  A ("Beyond speed" above) once the Gummi ship runs natively, and follow stage 3's pattern then.
- **Sound exactness**: steps 1-2 of stage 8 keep the output identical or within an LSB; NGS would not.
