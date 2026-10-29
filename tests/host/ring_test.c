/* The per-frame vertex and uniform rings (host/port/ring.c, renderer-spec 4.13 "Session 125", vita-port-plan
 * 5.1bm), with made-up sizes and the batcher's counts (no game data): tests/selftest.sh builds it with
 * gcc -m32 when that works.
 *
 *   bump      allocations are aligned, in order, inside the current frame's slot.
 *   overflow  one that does not fit returns 0, is counted, and leaves the slot as it was; a smaller one
 *             still fits.
 *   frames    kh1_ring_frame alternates the two slots, each starts empty, the high-water mark is kept; a frame
 *             that wrote nothing keeps its slot (session 145).
 *   sizes     the rings hold the static packets' worst send, every static send at once and 4,096
 *             batches' uniforms; a vertex is 32 bytes. */
#include "common.h"
#include "platform/ring.h"
#include "platform/vertex.h"

int printf(const char *, ...);

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("ring_test: %s\n", name); fails++; } } while (0)

static u8 mem[2 * 1024] __attribute__((aligned(256)));

int main(void) {
    KH1Ring r;
    u8 *a, *b, *c, *d;
    kh1_ring_init(&r, mem, 1024);

    a = kh1_ring_alloc(&r, 52, 64);
    b = kh1_ring_alloc(&r, 52, 64);
    c = kh1_ring_alloc(&r, 96, 16);
    CHECK("bump: aligned and in order", a == mem && b == mem + 64 && c == mem + 128 && r.head == 224);

    d = kh1_ring_alloc(&r, 1024 - 224 + 1, 16);
    CHECK("overflow: too big returns 0 and is counted", !d && r.overflows == 1 && r.head == 224);
    d = kh1_ring_alloc(&r, 1024 - 224, 16);
    CHECK("overflow: what is left still fits", d == mem + 224 && r.head == 1024);
    CHECK("overflow: a full slot takes nothing more", !kh1_ring_alloc(&r, 1, 1) && r.overflows == 2);

    kh1_ring_frame(&r);
    a = kh1_ring_alloc(&r, 32, 32);
    CHECK("frames: the second slot starts empty", a == mem + 1024 && r.head == 32 && r.high == 1024);
    kh1_ring_frame(&r);
    a = kh1_ring_alloc(&r, 16, 16);
    CHECK("frames: back to the first slot, the high-water mark kept", a == mem && r.frames == 2 && r.high == 1024);
    kh1_ring_frame(&r);
    kh1_ring_frame(&r); /* the second slot's frame wrote nothing: the next one writes it again */
    a = kh1_ring_alloc(&r, 16, 16);
    CHECK("frames: an empty frame keeps its slot", a == mem + 1024 && r.frames == 4);

    CHECK("sizes: a GPU vertex is 32 bytes", kh1_ring_vertex_bytes(1) == 32);
    CHECK("sizes: the vertex ring holds every static send at once 34 times over",
          kh1_ring_vertex_bytes(3770) * 34 <= KH1_RING_VERTEX_BYTES && kh1_ring_vertex_bytes(864) <= KH1_RING_VERTEX_BYTES);
    CHECK("sizes: the uniform ring holds 8,192 slots (the static packets: 42 batches, 40 passes)",
          kh1_ring_uniform_bytes(8192, 0) == KH1_RING_UNIFORM_BYTES && kh1_ring_uniform_bytes(42, 40) * 40 <
          KH1_RING_UNIFORM_BYTES);
    printf("ring_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
