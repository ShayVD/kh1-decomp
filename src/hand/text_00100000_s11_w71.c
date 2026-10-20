/* func_00106ed0: MATCH (hand, strict), no context. s11w71, from w48's 31w draft. Natural shape apart from climbed statement orders (no dead statements, no flags, no asm). Alias-set levers: h accesses and q->v stores go through a one-field struct F1 (MEM_IN_STRUCT), so the D_00494BAC/BA8 scalar-global loads are not ordered behind the h stores in sched1 (fixed_scalar_and_varying_struct_p); the four prologue tables use structs with a 4-byte enum EN (its own alias set) and sub->b is read as EN, so the load waits only on the EN-typed stores and their output deps fix the sched2 store order; block-local pointers to the four tables, declared in the order 761C0, 7A200, 6E140, 72180, set the address registers and the lo_sum order. */
#include "common.h"
#include "data/bss_0049.h"
typedef struct { s32 a, b, c, d; } Ent16;
#include "data/types/text_00100000_s11_w71.h"
typedef enum { EZ } EN;
typedef struct { EN a; s32 b; EN c, d; } EntD;
typedef struct { EN a, b, c, d; } EntE;
typedef struct { s32 a; EN b; s32 c, d; } EntLb;
extern EntE D_0046E140;
extern EntE D_00472180;
extern EntD D_004761C0;
extern EntE D_0047A200;
extern Ent16 D_0046E150[1024];
extern Ent32 D_00472190[];
extern Ent16 *D_00494BA8;
#define BA8 D_00494BA8
typedef struct { f32 f; } F1;
#define SA sub->a
#define SB ((EntLb *)sub)->b
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

{
EntD *p004761C0 = &D_004761C0;
EntE *p0047A200 = &D_0047A200, *p0046E140 = &D_0046E140, *p00472180 = &D_00472180;
x = SA;
p00472180->a = x;
p0046E140->a = x;
p0047A200->a = x;
p004761C0->a = x;
y = SB + (s32)h;
p00472180->b = y;
p0046E140->b = y;
p0047A200->b = y;
p00472180->d = 0;
p0046E140->d = 0;
p0047A200->d = 0;
w31 = h[31];
p004761C0->b = y;
p004761C0->d = 0;
D_002A6C50 = 0;
p00472180->c = 0;
p0046E140->c = 0;
p0047A200->c = 0;
p004761C0->c = 0;
}

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
