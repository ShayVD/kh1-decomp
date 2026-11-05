/* Per-frame vertex and uniform rings (include/platform/ring.h, docs/renderer-spec.md 4.13 "Session 125"): the ring is
 * vita-port-kit's vpk_ring; what is left here is this port's sizes, checked by tests/host/ring_test.c;
 * host/null/pipes.c prints a run's use against the sizes (`ring:`).
 * Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/ring.h"
#include "platform/vertex.h"

u32 kh1_ring_vertex_bytes(u32 v) { return v * (u32)sizeof(KH1GpuVert); }

u32 kh1_ring_uniform_bytes(u32 b, u32 p) { return (b + p) * KH1_RING_UNIFORM_SLOT; }
