#include "common.h"
typedef f32 V4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));
typedef struct { u16 v[10]; } Rec20;
typedef struct {
    V4 *x0;
    u128 *x4;
    Rec20 *x8;
    f32 *xc;
    u8 pad[48];
} Ent2450b;
extern Ent2450b D_004E2450[];
extern V4 D_002C1260[6];
static inline s32 vsubflags(void *a, void *b) {
    s32 f;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2 %0, $vi17\n"
        : "=&r"(f) : "r"(a), "r"(b));
    return f;
}

s32 func_0011ab88(s32 a0, s32 a1, void *a2) {
    V4 t;
    s32 m;
    Ent2450b *e = &D_004E2450[a0];
    u16 *r = e->x8[a1].v;
    f32 *p0 = e->x0[*r++];
    f32 *p1 = e->x0[*r++];
    f32 *p2 = e->x0[*r++];
    s16 k = ((s16 *)e->x8[a1].v)[3];
    if (k >= 0) goto quad;
    if (k < -2) goto quad;
    {
        t[0] = p0[0]; t[1] = p1[0]; t[2] = p2[0];
        if ((vsubflags(D_002C1260[3], t) & 0xe0) == 0xe0) return 0;
        if ((vsubflags(t, D_002C1260[0]) & 0xe0) == 0xe0) return 0;
        t[0] = p0[1]; t[1] = p1[1]; t[2] = p2[1];
        if ((vsubflags(D_002C1260[4], t) & 0xe0) == 0xe0) return 0;
        if ((vsubflags(t, D_002C1260[1]) & 0xe0) == 0xe0) return 0;
        t[0] = p0[2]; t[1] = p1[2]; t[2] = p2[2];
        if ((vsubflags(D_002C1260[5], t) & 0xe0) == 0xe0) return 0;
        m = vsubflags(t, D_002C1260[2]) & 0xe0;
        if (m != 0xe0) goto one;
        return 0;
    }
quad:
    {
        f32 *p3 = e->x0[*r];
        t[0] = p0[0]; t[1] = p1[0]; t[2] = p2[0]; t[3] = p3[0];
        if ((vsubflags(D_002C1260[3], t) & 0xf0) == 0xf0) return 0;
        if ((vsubflags(t, D_002C1260[0]) & 0xf0) == 0xf0) return 0;
        t[0] = p0[1]; t[1] = p1[1]; t[2] = p2[1]; t[3] = p3[1];
        if ((vsubflags(D_002C1260[4], t) & 0xf0) == 0xf0) return 0;
        if ((vsubflags(t, D_002C1260[1]) & 0xf0) == 0xf0) return 0;
        t[0] = p0[2]; t[1] = p1[2]; t[2] = p2[2]; t[3] = p3[2];
        if ((vsubflags(D_002C1260[5], t) & 0xf0) == 0xf0) return 0;
        m = vsubflags(t, D_002C1260[2]) & 0xf0;
        if (m == 0xf0) return 0;
    }
one:
    return 1;
zero:
    return 0;
}
