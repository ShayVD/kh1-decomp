/* Session 147: whether two byte runs are equal (memcmp's == 0 without the order), for the large compares
 * on the Vita's game thread.  vitasdk's newlib memcmp is a C loop: a word every ~10 instructions when both
 * pointers are word aligned, a byte every ~6 otherwise; the title compares ~2 MB of upload bytes a frame
 * with it (gsmem.c kh1_gsmem_image_same).  On ARM with NEON: 256 bytes a step, the two runs' XORs ORed
 * together and moved to a core register once a step (a NEON -> core move stalls the A9's pipeline), with
 * each 32-byte cache line prefetched 1 KiB ahead (s147a prefetched 2 of a step's 8 lines and compared at only
 * ~125 MB/s on a Vita); the tail through memcmp.  Elsewhere memcmp itself (glibc's is vectorised already).
 * tests/host/bytesame_test.c checks it against memcmp, under qemu-arm too. */
#ifndef KH1_BYTESAME_H
#define KH1_BYTESAME_H

int memcmp(const void *, const void *, __SIZE_TYPE__);

#if defined(__ARM_NEON) && !defined(KH1_BYTESAME_PLAIN)
#include <arm_neon.h>
static __inline__ int kh1_bytes_same(const void *pa, const void *pb, u32 n) {
    const u8 *a = (const u8 *)pa, *b = (const u8 *)pb;
    while (n >= 256) {
        uint8x16_t d = vdupq_n_u8(0);
        uint32x2_t m;
        int i;
        for (i = 0; i < 256; i += 32) { /* session 147b: the A9's lines are 32 bytes: each one PLD'd, 1 KiB ahead */
            __builtin_prefetch(a + 1024 + i);
            __builtin_prefetch(b + 1024 + i);
        }
        for (i = 0; i < 256; i += 64) {
            d = vorrq_u8(d, veorq_u8(vld1q_u8(a + i), vld1q_u8(b + i)));
            d = vorrq_u8(d, veorq_u8(vld1q_u8(a + i + 16), vld1q_u8(b + i + 16)));
            d = vorrq_u8(d, veorq_u8(vld1q_u8(a + i + 32), vld1q_u8(b + i + 32)));
            d = vorrq_u8(d, veorq_u8(vld1q_u8(a + i + 48), vld1q_u8(b + i + 48)));
        }
        m = vorr_u32(vget_low_u32(vreinterpretq_u32_u8(d)), vget_high_u32(vreinterpretq_u32_u8(d)));
        m = vpmax_u32(m, m);
        if (vget_lane_u32(m, 0)) return 0;
        a += 256;
        b += 256;
        n -= 256;
    }
    return n == 0 || memcmp(a, b, n) == 0;
}
#else
static __inline__ int kh1_bytes_same(const void *a, const void *b, u32 n) {
    return memcmp(a, b, n) == 0;
}
#endif

#endif
