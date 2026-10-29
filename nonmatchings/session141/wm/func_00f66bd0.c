/* score 102 (66 words; 344 vs 352 bytes). Image-upload packet (DMA cnt + GIF tag + BITBLTBUF/TRXPOS/TRXREG/TRXDIR + image tag + DMA ref). Nibbles-per-pixel if-chain gives the movz chain; qwc = n/32, +1 if n&31. The original copies p (move t7,a0), writes all qwords through one base t = p+16 and computes the final DMA tag address as t+112, not p+128. An inline `Qw *hdr(Qw *t, ...) { ...; return t + 7; }` gets the size right (352) but spills 3 more saved registers (score 110). */
#include "ovl.h"

typedef union {
    kh1_u128 q;
    u64 d[2];
    u32 w[4];
} Qw;

static inline void put(Qw *q, u64 a, u64 b) {
    q->d[0] = a;
    q->d[1] = b;
}

Qw *func_00f66bd0(Qw *p, u32 addr, s32 dbp, s32 dbw, s32 dpsm, s32 dx, s32 dy, s32 w, s32 h) {
    s32 k;
    s32 n;
    s32 q;
    Qw *t;

    k = 8;
    if ((dpsm & 7) == 1) k = 6;
    if ((dpsm & 7) == 2) k = 4;
    if ((dpsm & 7) == 3) k = 2;
    if ((dpsm & 7) == 4) k = 1;
    n = w * h * k;
    q = n / 32;
    if (n & 31) q++;
    p[0].w[0] = 0x10000007;
    p[0].w[1] = 0;
    p[0].w[2] = 0;
    p[0].w[3] = 0;
    t = p + 1;
    t[0].d[0] = 0x1000000000000005;
    t[0].d[1] = 14;
    t[1].d[0] = 0;
    t[1].d[1] = 63;
    t[2].d[0] = ((u64)dbp << 32) | ((u64)dbw << 48) | ((u64)dpsm << 56);
    t[2].d[1] = 80;
    t[3].d[0] = ((u64)dx << 32) | ((u64)dy << 48);
    t[3].d[1] = 81;
    t[4].d[0] = (s64)w | ((u64)h << 32);
    t[4].d[1] = 82;
    t[5].d[0] = 0;
    t[5].d[1] = 83;
    t[6].d[0] = (q | 0x8000) | 0x0800000000000000;
    t[6].d[1] = 0;
    p = t + 7;
    p->w[0] = q | 0x30000000;
    p->w[1] = addr;
    p->w[2] = 0;
    p->w[3] = 0;
    return p + 1;
}
