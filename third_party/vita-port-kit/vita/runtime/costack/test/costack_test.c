/* vpk_costack: pool alignment and rounding, owns(), the malloc fallback.  Any host C compiler:
 *   cc -std=c99 -Wall -I.. ../vpk_costack.c costack_test.c -o costack_test && ./costack_test */
#include <stdint.h>
#include <stdio.h>
#include "vpk_costack.h"

static int fails;
#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); fails++; } } while (0)

static unsigned char mem[4096 + 64];

int main(void) {
    unsigned char *base = mem + 3; /* misaligned on purpose */
    unsigned char *a, *b, *c;
    void *d;
    unsigned char local;

    /* before a pool: malloc'd, and nothing is owned */
    d = vpk_costack_alloc(100);
    CHECK(d != 0);
    CHECK(!vpk_costack_owns((unsigned long)mem, 1));

    vpk_costack_pool(base, 1024);
    a = vpk_costack_alloc(100); /* rounded to 112 */
    b = vpk_costack_alloc(16);
    CHECK(((uintptr_t)a & 15) == 0);
    CHECK(a >= base && a < base + 16);
    CHECK(b == a + 112);
    CHECK(vpk_costack_owns((unsigned long)a, 112));
    CHECK(vpk_costack_owns((unsigned long)(base + 1024 - 4), 4));
    CHECK(!vpk_costack_owns((unsigned long)(base + 1024 - 4), 8));

    /* the rest of the pool, then the fallback (outside the pool) */
    c = vpk_costack_alloc((unsigned int)(base + 1024 - (b + 16)) & ~15u);
    CHECK(c == b + 16);
    d = vpk_costack_alloc(64);
    CHECK(d != 0);
    CHECK(!vpk_costack_owns((unsigned long)d, 64));

    /* the whole stack the pool came from */
    vpk_costack_stack(&local - 256, 512);
    CHECK(vpk_costack_owns((unsigned long)&local, 1));

    printf(fails ? "costack_test: %d failed\n" : "costack_test: ok\n", fails);
    return fails != 0;
}
