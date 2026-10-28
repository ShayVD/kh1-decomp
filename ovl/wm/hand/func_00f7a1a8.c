/* wm.x func_00f7a1a8: the twin of gb.x func_00f42cf8 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u64 lo, hi; } GQ;
typedef union { kh1_u128 q; u32 w[4]; GQ d; } GPkt;
extern GPkt *D_0108FA60[];
static inline void ad(GQ *q, u64 v, u64 r) {
    q->lo = v;
    q->hi = r;
}
typedef struct { u8 r, g, b, a; } Rgba;
void func_00f7a1a8(Rgba *rgba, s32 *x, s32 *y, u32 alpha) {
    GPkt *p = D_0108FA60[0];
    s32 *w;
    s32 i;
    p[0].q = KH1_Q(0);
    ad(&p[1].d, 0x1000000000000005, 14);
    ad(&p[2].d, 0, 0x3F);
    ad(&p[3].d, alpha, 0x42);
    ad(&p[4].d, 0x5001D, 0x47);
    ad(&p[5].d, 0, 0x49);
    ad(&p[6].d, 0, 0x14);
    ad(&p[7].d, 0x8026400000008001, 0x41414141);
    for (i = 0, w = (s32 *)&p[8]; i < 4; i++) {
        s32 px = (x[i] + 1792) << 4;
        s32 py = (y[i] + 1856) << 4;
        w[0] = rgba[i].r;
        w[1] = rgba[i].g;
        w[2] = rgba[i].b;
        w[3] = rgba[i].a;
        w += 4;
        w[0] = px;
        w[1] = py;
        w[2] = 0xFFFFFF;
        w[3] = 0;
        w += 4;
    }
    p[0].w[0] = 0x1000000F;
    D_0108FA60[0] = p + 16;
}
