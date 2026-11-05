#ifndef PLATFORM_RING_H
#define PLATFORM_RING_H

/* Per-frame GPU memory: the vertex and uniform ring buffers a port writes each batch into
 * (docs/renderer-spec.md 4.13 "Session 125", vita-port-plan 5.1bm): port code, not game code.
 *
 * A ring is KH1_RING_FRAMES equal slots, one per frame in flight (double-buffered: the GPU reads frame
 * n's slot while the CPU writes frame n + 1's).  kh1_ring_alloc bumps the current slot's head (aligned);
 * kh1_ring_frame moves to the next slot and starts it empty, so nothing is ever freed one by one.  The
 * port must not write a slot before the GPU is done with the frame that last used it (on the Vita a
 * notification or sceGxmFinish per frame: the ring does not wait).  An allocation that does not fit in
 * what is left of the slot returns 0 and is counted (`overflows`): the caller drops or splits the batch;
 * nothing wraps into the slot the GPU may be reading.
 *
 * The sizes, from session 124 / 125's batcher counts (batch.h; 32-byte vertices, vertex.h):
 *   vertices  the static packets' worst send 864 vertices (27 KB: the menu blur), every static send at
 *             once 3,770 (118 KB), the fake disc at most 3 draw calls / 390 vertices a frame.  The real
 *             disc adds renderers A / B's meshes as independent triangles (primasm.h: 3 vertices each).
 *             4 MiB a frame is 131,072 vertices (43,690 triangles), 34 times every static send at once:
 *             the room run's `ring:` line (KH1_HOST_TRACE=5) says how much of it a frame takes.
 *   uniforms  one 64-byte slot per batch (KH1DrawUniforms is 52 bytes; 64 is a common GPU uniform
 *             alignment) and one per render pass (the vertex shader's pixel-to-clip vec4): 256 KiB is
 *             4,096 slots against the static packets' 42 batches and 40 passes (session 125, with the
 *             column groups) and the fake disc's 3.
 * Two frames in flight: 8.5 MiB of GPU memory.  Not part of the PS2 build. */
#ifndef KH1_PS2
#define KH1_RING_FRAMES 2
#define KH1_RING_VERTEX_BYTES (4u << 20)   /* a frame's vertices */
#define KH1_RING_UNIFORM_BYTES (512u << 10) /* a frame's uniforms (session 141: a slot for each of 4,096 commands and 256 passes) */
#define KH1_RING_UNIFORM_SLOT 64u           /* a batch's or a pass's uniform block */

/* the ring itself is vita-port-kit's (third_party/vita-port-kit/vita/runtime/ring, vendored: docs/vita-port-kit.md),
 * under the kh1_ names the port code calls, with KH1_RING_FRAMES slots */
#include "../../third_party/vita-port-kit/vita/runtime/ring/vpk_ring.h"

typedef VpkRing KH1Ring;

/* a ring over mem (KH1_RING_FRAMES x slot bytes, slot a multiple of 16) */
#define kh1_ring_init(r, mem, slot) vpk_ring_init((r), (mem), (slot), KH1_RING_FRAMES)
/* bytes from the current frame's slot, aligned to align (a power of two up to 256); 0 when it does not fit */
#define kh1_ring_alloc vpk_ring_alloc
/* the frame ends: its use into the high-water mark, the next slot starts empty */
#define kh1_ring_frame vpk_ring_frame
/* a frame's bytes for v vertices / b batches and p passes (what the rings above must hold) */
u32 kh1_ring_vertex_bytes(u32 v);
u32 kh1_ring_uniform_bytes(u32 b, u32 p);
#endif

#endif
