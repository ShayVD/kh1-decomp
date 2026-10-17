/* 7w off (hand, strict): FP regs of minz/maxz swapped (orig minz=f1, maxz=f7) and init moves. VU0 length helper is inline asm. */
#include "common.h"
typedef f32 V4_52[4] __attribute__((aligned(16)));
typedef struct { u8 pad[0x50]; f32 cx; f32 top; f32 cz; u8 pad5c[4]; f32 r; f32 h; u8 pad68[0xc]; s16 id; } Bnd;
s32 func_00104ae0(s32, V4_52 *);

static inline f32 vlen(f32 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf5, 0(%1)\n"
        "lqc2 $vf4, 0(%1)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2");
    return r;
}

void func_00115758(s32 id, Bnd *b) {
    V4_52 d;
    V4_52 v[4];
    f32 minx, maxx, miny, maxy, minz, maxz;
    s32 i;
    func_00104ae0(id, v);
    miny = 1000000.0f;
    maxy = -1000000.0f;
    minx = miny;
    maxx = maxy;
    maxz = maxy;
    minz = minx;
    for (i = 0; i < 4; i++) {
        if (maxy < v[i][1]) maxy = v[i][1];
        if (v[i][1] < miny) miny = v[i][1];
        if (v[i][0] < minx) minx = v[i][0];
        if (maxx < v[i][0]) maxx = v[i][0];
        if (v[i][2] < minz) minz = v[i][2];
        if (maxz < v[i][2]) maxz = v[i][2];
    }
    b->top = maxy;
    b->id = id;
    b->h = miny - maxy;
    b->cx = (maxx + minx) * 0.5f;
    b->cz = (minz + maxz) * 0.5f;
    d[0] = v[0][0] - b->cx;
    d[1] = 0.0f;
    d[2] = v[0][2] - b->cz;
    b->r = vlen(d);
}
