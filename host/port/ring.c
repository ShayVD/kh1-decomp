/* Per-frame vertex and uniform rings (include/platform/ring.h, docs/renderer-spec.md 4.13 "Session 125"),
 * checked by tests/host/ring_test.c; host/null/pipes.c prints a run's use against the sizes (`ring:`).
 * Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/ring.h"
#include "platform/vertex.h"

void kh1_ring_init(KH1Ring *r, void *mem, u32 slot) {
    r->base = (u8 *)mem;
    r->slot = slot;
    r->cur = 0;
    r->head = 0;
    r->frames = 0;
    r->high = 0;
    r->overflows = 0;
}

void *kh1_ring_alloc(KH1Ring *r, u32 bytes, u32 align) {
    u32 at = (r->head + align - 1) & ~(align - 1);
    if (at > r->slot || bytes > r->slot - at) {
        r->overflows++;
        return 0;
    }
    r->head = at + bytes;
    return r->base + r->cur * r->slot + at;
}

void kh1_ring_frame(KH1Ring *r) {
    if (r->head > r->high) r->high = r->head;
    r->cur = (r->cur + 1) % KH1_RING_FRAMES;
    r->head = 0;
    r->frames++;
}

u32 kh1_ring_vertex_bytes(u32 v) { return v * (u32)sizeof(KH1GpuVert); }

u32 kh1_ring_uniform_bytes(u32 b, u32 p) { return (b + p) * KH1_RING_UNIFORM_SLOT; }
