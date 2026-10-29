/* Session 147: host/null/bytesame.h's kh1_bytes_same against memcmp == 0: random lengths (0 to past a few
 * NEON steps, and the title's 288 KiB), every alignment of both runs mod 16, equal runs and runs with one
 * byte changed at a random place, at each end of a step, and in the tail.  On ARM with NEON (tests/selftest.sh
 * runs it under qemu-arm) the NEON form; elsewhere the memcmp form. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "../../host/null/bytesame.h"

static u8 A[300 << 10], B[300 << 10];

static int fails;
static void check(const u8 *a, const u8 *b, u32 n, const char *what) {
    int want = memcmp(a, b, n) == 0, got = kh1_bytes_same(a, b, n);
    if (want != got) {
        if (fails++ < 10) printf("bytesame: %s n %u (a %% 16 = %u, b %% 16 = %u): %d, memcmp says %d\n", what, n,
                                 (u32)((unsigned long)a & 15), (u32)((unsigned long)b & 15), got, want);
    }
}

int main(void) {
    u32 it, i, cases = 0;
    srand(147);
    for (i = 0; i < sizeof A; i++) A[i] = (u8)rand();
    for (it = 0; it < 40000; it++) {
        u32 oa = rand() & 15, ob = rand() & 15;
        u32 n = it % 8 == 0 ? (288u << 10) - (rand() & 31) : (u32)(rand() % 1300);
        u8 *a = A + oa, *b = B + ob;
        memcpy(b, a, n);
        check(a, b, n, "equal");
        cases++;
        if (n) {
            u32 at[4], k;
            at[0] = rand() % n;          /* anywhere */
            at[1] = (n / 256) * 256 - 1; /* a step's last byte (wraps to n - 1 past the end when n < 256) */
            at[2] = n - 1;               /* the tail's last */
            at[3] = n >= 256 ? 255u : 0u; /* the first step's last */
            for (k = 0; k < 4; k++) {
                u32 p = at[k] < n ? at[k] : n - 1;
                u8 old = b[p];
                b[p] ^= (u8)(1u << (rand() & 7));
                check(a, b, n, "one byte changed");
                b[p] = old;
                cases++;
            }
        }
    }
    printf("bytesame: %u cases%s, %d failures (%s)\n", cases, "", fails,
#if defined(__ARM_NEON) && !defined(KH1_BYTESAME_PLAIN)
           "NEON"
#else
           "memcmp"
#endif
    );
    return fails != 0;
}
