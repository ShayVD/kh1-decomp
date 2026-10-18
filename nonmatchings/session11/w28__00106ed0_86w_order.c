/* 00106ed0 86 LCS FINDING (hand, strict, 592 bytes, no context; best stays w18 41 / w24 47). The test block comes out in EXACTLY the original instruction order (k, j<<4, k+92, +sub, k+44, pb, pd, p23, k+60, p11, lw *pb, p15, k+28, p7, k+76, lwc1, ..., p19, c.eq.s, hk, lw *pd) when all pointers are computed in the test block through two REUSED variables: o = k+92/k+60/k+28/k+76 and then o = *pd, w = k+44 and then w = *pb (anti/output deps on o and w fix the sched1 order; the p7 test chain pulls the whole o chain early). Separate offset locals cannot give this order: k+28 (prio 8, own block) always beats p15 (prio 7) and k+60 ties k+28, whether the pointers are lifted from the then-block or written in the test block. Left: registers are a permutation (o a2, w v0, k a0, j<<4 v1, pb a1 vs orig v0/v1/a1/a0/a2): o and w die more than once, so local-alloc leaves them to global-alloc and the single-death locals (k, j<<4 chain, pb) take v0/v1 first. Needs the same order with single-death pseudos, or a reason v0/v1 stay free. With w24 then-block (c last): 63 at 588, .s11w28_m shape. */
#include "common.h"
typedef struct { s32 a, b, c, d; } Ent16;
typedef struct { u8 pad[8]; f32 v[6]; } Ent32;
extern Ent16 D_0046E140, D_00472180, D_004761C0, D_0047A200;
extern Ent16 D_0046E150[1024];
extern Ent32 D_00472190[];
extern Ent16 *D_00494BA8;
extern Ent32 *D_00494BAC;
extern s32 D_00494BB0;
extern s32 D_002A6C50;
extern s32 D_002A6C54;
void func_00106ed0(f32 *h, s32 sz) {
    s32 i, j, a, b;
    Ent16 *sub;
    D_00494BA8 = D_0046E150;
    D_00494BAC = D_00472190;
    for (i = 0; i < 1024; i++) D_00494BA8[i].c = 0;
    D_00494BB0 = ((s32 *)h)[0];
    sub = (Ent16 *)(((s32 *)h)[1] + (s32)h);
    D_002A6C50 = 0;
    D_0047A200.a = D_0046E140.a = D_00472180.a = D_004761C0.a = sub->a;
    D_0047A200.b = D_0046E140.b = D_00472180.b = D_004761C0.b = sub->b + (s32)h;
    D_0047A200.d = D_0046E140.d = D_00472180.d = D_004761C0.d = 0;
    D_004761C0.c = D_0047A200.c = D_0046E140.c = D_00472180.c = 0;
    if (h[31] != 1.0f) {
        D_002A6C50 = (s32)h[31] - 20;
        D_002A6C54 = (s32)h + sz - (D_002A6C50 << 16);
        h[31] = 1.0f;
    }
    for (i = 0; i < D_00494BB0; i = j) {
        j = i + 1;
        {
        s32 *pb = &((Ent16 *)((j << 4) + (s32)sub))->b, *pd = &((Ent16 *)((j << 4) + (s32)sub))->d;
        s32 k = i * 128;
        s32 o, w;
        f32 *p23, *p11, *p15, *p7, *p19;
        o = k + 92;
        p23 = (f32 *)((s32)h + o);
        w = k + 44;
        p11 = (f32 *)((s32)h + w);
        o = k + 60;
        p15 = (f32 *)((s32)h + o);
        w = *pb;
        *pb = w + (s32)h;
        o = k + 28;
        p7 = (f32 *)((s32)h + o);
        o = k + 76;
        p19 = (f32 *)((s32)h + o);
        o = *pd;
        *pd = o + (s32)h;
        if (*p7 != 0.0f) {
            f32 t;
            Ent32 *q;
            f32 *q8;
            Ent16 *e;
            *p7 = 1.0f;
            q = D_00494BAC;
            e = D_00494BA8;
            q8 = (f32 *)((s32)q + 8);
            t = *p23;
            *p23 = 1.0f;
            { s32 o0 = i * 32; *(f32 *)((s32)q8 + o0) = *p11; }
            { s32 c = 1; c <<= (s32)t; { s32 o2 = i * 16; ((Ent16 *)((s32)e + o2))->c = c; } }
            { s32 o1 = i * 32; ((Ent32 *)((s32)q + o1))->v[1] = *p15; }
            { s32 o = i * 32 + 16; *(f32 *)(o + (s32)q8) = *p19; }
            *p11 = 1.0f;
            *p15 = 1.0f;
            *p19 = 1.0f;
            h[i * 32 + 27] = 1.0f;

        }
        }
    }
}
