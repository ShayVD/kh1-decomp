/* func_00106ed0 123w (hand) but right size 588 (s6 draft 120w at 496 bytes): h read as f32 with per-field address pseudos h + (i*128+K) (index locals k7..k19 = k + K, so each field address is computed once and shared by its load and store, like the orig), sub[j].b/.d via pointers to ((j<<4)+(s32)sub), BAC v[0]/v[4] through q8 = BAC+8. Left: loop.c hoists the 1 of 1<<t into t9 (orig li a1,1 in the if body, t9 = copy of &D_00494BB0, only s0/s1 saved), x and z BAC addresses CSE into one register (orig computes q8+S and S+q8 separately), pre-loop store order (chains are a guess). */
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
    D_00494BAC = D_00472190;
    D_00494BA8 = D_0046E150;
    for (i = 0; i < 1024; i++) D_0046E150[i].c = 0;
    D_00494BB0 = ((s32 *)h)[0];
    sub = (Ent16 *)(((s32 *)h)[1] + (s32)h);
    D_0047A200.a = D_0046E140.a = D_00472180.a = D_004761C0.a = sub->a;
    D_0047A200.b = D_0046E140.b = D_00472180.b = D_004761C0.b = sub->b + (s32)h;
    D_004761C0.c = D_0047A200.c = D_0046E140.c = D_00472180.c = 0;
    D_004761C0.d = D_0047A200.d = D_0046E140.d = D_00472180.d = 0;
    D_002A6C50 = 0;
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
        s32 k7 = k + 28, k23 = k + 92, k11 = k + 44, k15 = k + 60, k19 = k + 76;
        f32 *p7 = (f32 *)((s32)h + k7);
        if (*p7 != 0.0f) {
            f32 t;
            Ent32 *q = D_00494BAC;
            f32 *q8 = (f32 *)((s32)q + 8);
            f32 *p23 = (f32 *)((s32)h + k23);
            f32 *p11 = (f32 *)((s32)h + k11);
            f32 *p15 = (f32 *)((s32)h + k15);
            f32 *p19 = (f32 *)((s32)h + k19);
            *p7 = 1.0f;
            t = *p23;
            *p23 = 1.0f;
            q8[i * 8] = *p11;
            D_00494BA8[i].c = 1 << (s32)t;
            q[i].v[1] = *p15;
            { s32 n4 = i * 8 + 4; q8[n4] = *p19; }
            *p11 = 1.0f;
            *p15 = 1.0f;
            *p19 = 1.0f;
            h[i * 32 + 27] = 1.0f;
        }
        }
    }
}
