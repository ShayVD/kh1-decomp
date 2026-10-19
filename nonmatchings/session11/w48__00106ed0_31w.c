/* 00106ed0 31 LCS (hand, strict, right size 588/frame, no context; was w18 41). w18 loop + prologue written as single statements (x = sub->a, y = sub->b + h, per-field stores), climbed: sub BEFORE the D_00494BB0 store (lets lw 4(t1) issue before sw BB0), h[31] read into f32 w31 early (the s32 global stores have deps on the h[31] load, which made D_002A6C50 = 0 issue first), D_002A6C50 = 0 last (bc1t slot). Prologue now 6 words (lui a1/a2 order, 72180.a store late, .d 12(a0)/12(a1) swap); test block 4 (k+60/k+76); then-block 21 (w18 basin). Finding: D_00494BAC/BA8 loads are alias set 0 (mem/f ... 0), so they wait on the *pd int store at the end of the test block; reading t through a union (alias set 0 too) makes the *p23 load wait as well, so q/e/p23 issue in LUID order like the original; the 592-byte 3rd s-register in w24/w28 shapes is the fix_truncsfsi2 GR scratch reload (no free caller-saved reg at the trunc), not a pseudo. */
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
