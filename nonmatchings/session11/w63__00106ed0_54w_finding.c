/* 00106ed0 54w LCS (hand, strict, right size 588), no context. FINDING only (best stays w48 31w): w28's reused-variable test block (o = k+92/k+60/k+28/k+76 then *pd, w = k+44 then *pb) + w48's prologue and then-block. Test block comes out in the exact original instruction order at 588 bytes; registers permuted (o a2, w v0, k a0, j<<4 v1, pb a1; orig o v0, w v1, k a1, j<<4 a0, pb a2) because o/w die more than once and go to global-alloc after the single-death locals took v0/v1. s11w63 analysis: with separate temps the original register reuse needs sched1 to issue p15 (prio 7) before k+28 (prio 8: add, add, lwc1 2, c.eq.s 4); k+60 can be made to beat k+28 in the prio-8 tie by making it the last use of k (REG_DEAD -> reg weight 0; compute h27's k+h earlier), but p15 never beats k+28. The then-block chain cannot be lengthened: store->store and load->store deps cost 0, and the D_00494BA8 scalar-global load has no dep on q->v[] struct-member stores (fixed_scalar_and_varying_struct_p), only on the h stores. */
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
    s32 x, y;
    f32 w31;
    D_00494BA8 = D_0046E150;
    D_00494BAC = D_00472190;
    for (i = 0; i < 1024; i++) D_00494BA8[i].c = 0;

sub = (Ent16 *)(((s32 *)h)[1] + (s32)h);
D_00494BB0 = ((s32 *)h)[0];
x = sub->a;
D_004761C0.a = x;
D_0046E140.a = x;
w31 = h[31];
D_0047A200.a = x;
D_00472180.c = 0;
y = sub->b + (s32)h;
D_00472180.b = y;
D_0046E140.b = y;
D_0047A200.b = y;
D_0046E140.d = 0;
D_0046E140.c = 0;
D_00472180.d = 0;
D_004761C0.b = y;
D_0047A200.d = 0;
D_0047A200.c = 0;
D_00472180.a = x;
D_004761C0.d = 0;
D_004761C0.c = 0;
D_002A6C50 = 0;

    if (w31 != 1.0f) {
        D_002A6C50 = (s32)w31 - 20;
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
            q8 = (f32 *)((s32)q + 8);
            t = *p23;
            *p23 = 1.0f;
            { s32 o0 = i * 32; *(f32 *)((s32)q8 + o0) = *p11; }
            { s32 o = i * 32 + 16; *(f32 *)(o + (s32)q8) = *p19; }
            { s32 o1 = i * 32; ((Ent32 *)((s32)q + o1))->v[1] = *p15; }
            { s32 c = 1; c <<= (s32)t; { s32 o2 = i * 16; ((Ent16 *)((s32)D_00494BA8 + o2))->c = c; } }
            *p15 = 1.0f;
            *p11 = 1.0f;
            *p19 = 1.0f;
            h[i * 32 + 27] = 1.0f;

        }
        }
    }
}
