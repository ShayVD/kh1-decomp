/* func_00106ed0 47 LCS (hand, strict, right size/frame, no context). NEW FINDING, not a lower count than w18's 41: in this build the then-block's f32 accesses (h loads/stores, q->v stores) all conflict, and so do the loads of the pointer globals D_00494BAC/D_00494BA8 (sched1 dump: lw D_00494BA8 has deps on every earlier swc1), so the orig's memory order is the SOURCE order: *p7=1, t=*p23, *p23=1, v[0]=*p11, v[1]=*p15, v[4]=*p19, then *p11/*p15/*p19/h[27] = 1.0f, and both pointer globals are read right after *p7 = 1.0f. w18's 41 has v[4] before v[1] and p15 before p11, a different basin that cannot reach 0. This file uses the natural order with the c store last (47; the whole prologue now matches exactly). Reading D_00494BA8 early (as the orig does) or putting the c statement before v[1] costs a 3rd s-register (592 bytes): the loop-bound copy loses t9 to sub in global-alloc. Left: s0/s1 swap, test-block k+44/k+92 and k+60/k+76 order, the then-block c chain (BA8 load early, i*16 and li 1 at the top). */
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
        *pb += (s32)h;
        *pd += (s32)h;
        }
        {
        s32 k = i * 128;
        s32 k7;
        f32 *p7;
        k7 = k + 28;
        p7 = (f32 *)((s32)h + k7);
        if (*p7 != 0.0f) {
            f32 t;
            Ent32 *q;
            f32 *q8;
            s32 k23 = k + 92, k11 = k + 44, k15 = k + 60, k19 = k + 76;
            f32 *p23 = (f32 *)((s32)h + k23);
            f32 *p11 = (f32 *)((s32)h + k11);
            f32 *p15 = (f32 *)((s32)h + k15);
            f32 *p19 = (f32 *)((s32)h + k19);

            *p7 = 1.0f;
            q = D_00494BAC;
            q8 = (f32 *)((s32)q + 8);
            t = *p23;
            *p23 = 1.0f;
            { s32 o0 = i * 32; *(f32 *)((s32)q8 + o0) = *p11; }
            { s32 o1 = i * 32; ((Ent32 *)((s32)q + o1))->v[1] = *p15; }
            { s32 o = i * 32 + 16; *(f32 *)(o + (s32)q8) = *p19; }
            { s32 c = 1; c <<= (s32)t; { s32 o2 = i * 16; ((Ent16 *)((s32)D_00494BA8 + o2))->c = c; } }
            *p11 = 1.0f;
            *p15 = 1.0f;
            *p19 = 1.0f;
            h[i * 32 + 27] = 1.0f;

        }
        }
    }
}
