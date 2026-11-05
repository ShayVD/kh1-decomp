/* vpk_ring with made-up sizes (from kh1-decomp tests/host/ring_test.c @ 85befa4a, game sizes left out):
 *   bump      allocations are aligned, in order, inside the current frame's slot.
 *   overflow  one that does not fit returns 0, is counted, and leaves the slot as it was; a smaller one still fits.
 *   frames    vpk_ring_frame steps through the slots, each starts empty, the high-water mark is kept; a frame that
 *             wrote nothing keeps its slot; three slots wrap after the third. */
#include <stdio.h>
#include "vpk_ring.h"

static int fails, checks;
#define CHECK(name, cond) do { checks++; if (!(cond)) { printf("ring_test: %s\n", name); fails++; } } while (0)

static unsigned char mem[3 * 1024] __attribute__((aligned(256)));

int main(void) {
    VpkRing r;
    unsigned char *a, *b, *c, *d;
    vpk_ring_init(&r, mem, 1024, 2);

    a = vpk_ring_alloc(&r, 52, 64);
    b = vpk_ring_alloc(&r, 52, 64);
    c = vpk_ring_alloc(&r, 96, 16);
    CHECK("bump: aligned and in order", a == mem && b == mem + 64 && c == mem + 128 && r.head == 224);

    d = vpk_ring_alloc(&r, 1024 - 224 + 1, 16);
    CHECK("overflow: too big returns 0 and is counted", !d && r.overflows == 1 && r.head == 224);
    d = vpk_ring_alloc(&r, 1024 - 224, 16);
    CHECK("overflow: what is left still fits", d == mem + 224 && r.head == 1024);
    CHECK("overflow: a full slot takes nothing more", !vpk_ring_alloc(&r, 1, 1) && r.overflows == 2);

    vpk_ring_frame(&r);
    a = vpk_ring_alloc(&r, 32, 32);
    CHECK("frames: the second slot starts empty", a == mem + 1024 && r.head == 32 && r.high == 1024);
    vpk_ring_frame(&r);
    a = vpk_ring_alloc(&r, 16, 16);
    CHECK("frames: back to the first slot, the high-water mark kept", a == mem && r.frames == 2 && r.high == 1024);
    vpk_ring_frame(&r);
    vpk_ring_frame(&r); /* the second slot's frame wrote nothing: the next one writes it again */
    a = vpk_ring_alloc(&r, 16, 16);
    CHECK("frames: an empty frame keeps its slot", a == mem + 1024 && r.frames == 4);

    vpk_ring_init(&r, mem, 1024, 3);
    vpk_ring_alloc(&r, 8, 8);
    vpk_ring_frame(&r);
    vpk_ring_alloc(&r, 8, 8);
    vpk_ring_frame(&r);
    a = vpk_ring_alloc(&r, 8, 8);
    vpk_ring_frame(&r);
    b = vpk_ring_alloc(&r, 8, 8);
    CHECK("frames: three slots, then the first again", a == mem + 2048 && b == mem);

    printf("ring_test: %s (%d checks)\n", fails ? "FAIL" : "PASS", checks);
    return fails != 0;
}
