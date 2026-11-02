/* wm.x func_00f7ef20: matched by hand. */
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

static inline void rgba(Qw *q, u32 r, u32 g, u32 b, u32 a) {
    q->w[0] = r;
    q->w[1] = g;
    q->w[2] = b;
    q->w[3] = a;
}

static inline void xyz(Qw *q, s32 x, s32 y, s32 z) {
    q->w[0] = x;
    q->w[1] = y;
    q->w[2] = z;
    q->w[3] = 0;
}

Qw *func_00f7ef20(Qw *p, s32 x, s32 y, s32 w, s32 h, u8 *col, u64 a, u64 b) {
    s32 x0 = x + 1792;
    s32 y0 = y + 1856;
    s32 x1 = x0 + w;
    s32 y1 = y0 + h;
    u32 r, g, bl, al;

    p[0].q = KH1_Q(0);
    put(&p[1], 0x1000000000000004, 14);
    put(&p[2], a, 66);
    put(&p[3], b, 71);
    put(&p[4], 0, 73);
    put(&p[5], 96, 20);
    put(&p[6], 0x8022400000008001, 0x41414141);
    r = col[0];
    g = col[1];
    bl = col[2];
    al = col[3];
    rgba(&p[7], r, g, bl, al);
    xyz(&p[8], x1 << 4, y1 << 4, 0xFFFFFF);
    rgba(&p[9], r, g, bl, al);
    xyz(&p[10], x1 << 4, y0 << 4, 0xFFFFFF);
    rgba(&p[11], r, g, bl, al);
    xyz(&p[12], x0 << 4, y1 << 4, 0xFFFFFF);
    rgba(&p[13], r, g, bl, al);
    xyz(&p[14], x0 << 4, y0 << 4, 0xFFFFFF);
    p[0].w[0] = 0x1000000E;
    return p + 15;
}
