/* 00106ed0 4 LCS (4 pos), hand (strict), right size 588, no context (s11w71; was w48 31). Loop and then-block exact. Lever: every h access and q->v store goes through a one-field struct F1 (HL/HS/QS macros, MEM_IN_STRUCT), so the D_00494BAC/BA8 scalar-global loads (mem/f, fixed after canonicalisation) no longer wait on the *p7 / h stores in sched1 (fixed_scalar_and_varying_struct_p); e = D_00494BA8 read first; then-block f32 ops in the original order; the integer statements and the prologue stores are hill-climbed (hc_s11), so the order is unnatural (D_002A6C50 = 0 mid-prologue, e->c store after *p15 = 1). Left: D_00472180.a must precede y = sub->b (the original's sub->b load waits on all four .a stores) but moving it there swaps the h[0]/D_00472180/D_0046E140 address registers in sched1 (10w); D_00472180.c/.d and D_0047A200.a slots follow. Declaring a prologue global as plain s32 (scalar store, sched2-only edge) scrambles the prologue (19-28w). */
#include "common.h"
typedef struct { s32 a, b, c, d; } Ent16;
typedef struct { u8 pad[8]; f32 v[6]; } Ent32;
extern Ent16 D_0046E140, D_00472180, D_004761C0, D_0047A200;
extern Ent16 D_0046E150[1024];
extern Ent32 D_00472190[];
extern Ent16 *D_00494BA8;
#define BA8 D_00494BA8
typedef struct { f32 f; } F1;
#define ST(g,f,o,v) (g.f = (v))
#define SA sub->a
#define SB sub->b
#define HL(p) (((F1 *)(p))->f)
#define HS(p,v) (((F1 *)(p))->f = (v))
#define HS27 ((F1 *)&h[i * 32 + 27])->f = 1.0f
#define QS(a,v) (((F1 *)(a))->f = (v))
extern Ent32 *D_00494BAC;
extern s32 D_00494BB0;
extern s32 D_002A6C50;
extern s32 D_002A6C54;
void func_00106ed0(f32 *h, s32 sz) {
    s32 i, j, a, b;
    Ent16 *sub;
    s32 x, y;
    f32 w31;
    BA8 = D_0046E150;
    D_00494BAC = D_00472190;
    for (i = 0; i < 1024; i++) BA8[i].c = 0;

sub = (Ent16 *)(((s32 *)h)[1] + (s32)h);
D_00494BB0 = ((s32 *)h)[0];

x = SA;
ST(D_004761C0,a,0,x);
ST(D_0047A200,a,0,x);
ST(D_0046E140,a,0,x);
ST(D_00472180,d,3,0);
y = SB + (s32)h;
ST(D_004761C0,c,2,0);
ST(D_00472180,b,1,y);
ST(D_0046E140,b,1,y);
ST(D_0047A200,b,1,y);
ST(D_00472180,c,2,0);
ST(D_0046E140,d,3,0);
ST(D_0047A200,d,3,0);
ST(D_0046E140,c,2,0);
ST(D_004761C0,d,3,0);
ST(D_00472180,a,0,x);
w31 = h[31];
ST(D_004761C0,b,1,y);
ST(D_0047A200,c,2,0);
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
            Ent16 *e;
            s32 o0, o1, o2, o, c;
            s32 k23 = k + 92, k11 = k + 44, k15 = k + 60, k19 = k + 76;
            f32 *p23 = (f32 *)((s32)h + k23);
            f32 *p11 = (f32 *)((s32)h + k11);
            f32 *p15 = (f32 *)((s32)h + k15);
            f32 *p19 = (f32 *)((s32)h + k19);

            HS(p7, 1.0f);

            e = BA8;
            o2 = i * 16;
            t = HL(p23);
            HS(p23, 1.0f);
            o = i * 32 + 16;
            q = D_00494BAC;
            o1 = i * 32;
            c = 1;
            o0 = i * 32;
            q8 = (f32 *)((s32)q + 8);
            c = c << (s32)t;
            QS((f32 *)((s32)q8 + o0), HL(p11));
            QS(&((Ent32 *)((s32)q + o1))->v[1], HL(p15));
            QS((f32 *)(o + (s32)q8), HL(p19));
            HS(p11, 1.0f);
            HS(p15, 1.0f);
            ((Ent16 *)((s32)e + o2))->c = c;
            HS(p19, 1.0f);
            HS27;

        }
        }
    }
}
