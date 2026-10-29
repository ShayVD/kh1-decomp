/* func_00f79700: score 84 (78 words; 344 vs 360 bytes), round 5. Same code as func_00f69278. PUT macro with one reassigned `Qw *q = &p[i]` per qword (the f7ef20/t7 trick) fixes the frame and the base register. Left: the original builds rg = (h<<32)|(u32)w, then `and` with 0xFFFFFFFF + dsll32/dsra32 for the TRXREG low word (ours stores w directly), and the instruction order of the bb/ps/n computations. `rg & 0xFFFFFFFF`, (u32)rg casts made it worse (127). */
#include "ovl.h"

typedef union {
    kh1_u128 q;
    u64 d[2];
    u32 w[4];
} Qw;

#define PUT(i, a, b, c, d) \
    q = &p[i];               \
    q->w[0] = (a);           \
    q->w[1] = (b);           \
    q->w[2] = (c);           \
    q->w[3] = (d)

Qw *func_00f79700(Qw *p, s32 addr, s32 dx, s32 dy, s32 w, s32 h, s32 dbp, s32 dpsm, s32 dbw, s32 bpp) {
    Qw *q;
    s32 n = w * h * bpp / 128;
    s64 bb = ((s64)dpsm << 56) | ((s64)dbw << 48) | ((s64)dbp << 32);
    s64 rg = ((s64)h << 32) | (u32)w;
    s64 ps = ((s64)dy << 48) | ((s64)dx << 32);

    PUT(1, 2, 0x10000000, 14, 0);
    PUT(2, bb, bb >> 32, 0x50, 0);
    PUT(3, rg, rg >> 32, 0x52, 0);
    PUT(5, 2, 0x10000000, 14, 0);
    PUT(6, ps, ps >> 32, 0x51, 0);
    PUT(7, 0, 0, 0x53, 0);
    p[4].d[0] = 0x10000004;
    p[0].d[0] = 0x10000003;
    PUT(8, n | 0x8000, 0x08000000, 0, 0);
    p[9].d[0] = (u32)n | 0x30000000 | ((s64)(addr & ~0xF) << 32);
    return p + 10;
}
