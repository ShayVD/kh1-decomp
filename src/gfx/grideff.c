/* A 1024-cell grid surface (a guess at the name), 0x00106e18-0x00108900:
 * func_00106ed0 reads its file, func_00107548 updates it through the
 * camera (double buffered by D_00351BD0: D_0046E150 / D_00472190 ...),
 * func_001081c8 / func_001083d8 / func_00108708 build its packets and
 * func_00107d30 queues them; func_00107e60 / func_00107ec0 its light. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/types/text_00100000_s6_00.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0048CC30.h"
#include "data/pieces/D_002A6238.h"
#include "data/types/text_00100000_s6_00_p.h"
#include "data/pieces/D_002A6250.h"
#include "data/pieces/D_002A624C.h"
#include "data/bss_0049.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6274.h"
#include "data/types/text_00100000_h1.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C10.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "data/types/text_00100000_s11_w71_p.h"
#include "data/types/text_00100000_s11_w71.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002A6234.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002BBDE4.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/types/text_00100000_s11_w74.h"
#include "data/pieces/D_002BBFE0.h"
#include "m2c.h"
#include "data/pieces/D_002BC098.h"
#include "data/pieces/D_002BC020.h"
#include "data/pieces/D_002BBF60.h"
#include "data/pieces/D_002A6C60.h"

/* func_00106e18 (from hand/text_00100000_s6_00.c). */
extern s32 D_002A6B84;
extern s32 D_002A6C54;
extern s32 D_002A6C50;
extern u8 D_002BC270[];
void iFlushCache(s32);
void func_00266f38(s32, void *);
s32 func_00106e18(void) {
    func_0011fbb0(0x3600, 2, 0, 0, 0, 128, D_002A6C50 << 7, D_002A6C50 << 12, D_002A6C54, D_002BC270);
    iFlushCache(0);
    func_00266f38(D_002A6B84, D_002BC270);
    return 2;
}

/* func_00106e98 (from hand/text_00100000_h1.c). */
typedef struct { u8 pad[16]; u32 w16; } DmaReq;
DmaReq *func_0015ed80(s32, void *);
void func_00106e98(s32 a) {
    if (D_002A6C50) func_0015ed80(a, func_00106e18);
}

/* func_00106ed0 (from hand/text_00100000_s11_w71.c). */
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
/* func_00106ed0: MATCH (hand, strict), no context. s11w71, from w48's 31w draft. Natural shape apart from climbed statement orders (no dead statements, no flags, no asm). Alias-set levers: h accesses and q->v stores go through a one-field struct F1 (MEM_IN_STRUCT), so the D_00494BAC/BA8 scalar-global loads are not ordered behind the h stores in sched1 (fixed_scalar_and_varying_struct_p); the four prologue tables use structs with a 4-byte enum EN (its own alias set) and sub->b is read as EN, so the load waits only on the EN-typed stores and their output deps fix the sched2 store order; block-local pointers to the four tables, declared in the order 761C0, 7A200, 6E140, 72180, set the address registers and the lo_sum order. */
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
#undef BA8
#undef SA
#undef SB
#undef HL
#undef HS
#undef HS27
#undef QS

/* func_00107120 (from hand/text_00100000_s6_00.c). */
#define SWK(a, b) { s32 t_ = *(a); *(a) = *(b); *(b) = t_; }
#define SWV(a, b) { u64 t_ = *(u64 *)(a); *(u64 *)(a) = *(u64 *)(b); *(u64 *)(b) = t_; }
void func_00107120(s32 *k, u32 *v, s32 n, s32 w) {
    s32 *lk;
    u32 *lv;
    s32 *pk;
    u32 *pv;
    s32 cnt, i, m;
    pk = k + 1;
    pv = v + w;
    cnt = 0;
    if (n < 2) return;
    if (n == 2) {
        if (k[0] < k[1]) {
            SWK(k, pk);
            SWV(v, pv);
        }
        return;
    }
    m = n >> 1;
    SWK(k, k + m);
    SWV(v, v + m * w);
    lk = k;
    lv = v;
    for (i = 1; i < n; i++) {
        if (k[0] < *pk) {
            lk++;
            lv += w;
            cnt++;
            if (pk != lk) {
                SWK(pk, lk);
                SWV(pv, lv);
            }
        }
        pk++;
        pv += w;
    }
    if (lk != k) {
        SWK(k, lk);
        SWV(v, lv);
    }
    func_00107120(k, v, cnt, w);
    func_00107120(lk + 1, lv + w, n - cnt - 1, w);
}
#undef SWK
#undef SWV

/* func_001072c0 (from hand/text_00100000_h28.c). */
extern s32 D_00351BD0;
extern s32 D_004761D0[];
extern s32 D_0047A210[];
extern s32 D_00494AA0[];
#define func_00107120 ((void (*)(s32 *, s32 *, s32, s32)) func_00107120)
void func_001072c0(s32 unused, s32 *out) {
    s32 i;
    s32 a = 0;
    s32 b = 0;
    if (D_00351BD0 != 0) {
        for (i = 0; i < D_00494BA0; i++) {
            func_00107120(&out[a], &D_0047A210[b], D_00494AA0[i], 4);
            a += D_00494AA0[i];
            b += D_00494AA0[i] * 4;
        }
    } else {
        for (i = 0; i < D_00494BA0; i++) {
            func_00107120(&out[a], &D_004761D0[b], D_00494AA0[i], 4);
            a += D_00494AA0[i];
            b += D_00494AA0[i] * 4;
        }
    }
}
#undef func_00107120

/* func_001073f0 (from hand/text_00100000_h28.c). */
extern s32 D_00494B20[];
extern s32 D_0046E150_001073f0[] __asm__("D_0046E150");
#define D_0046E150 D_0046E150_001073f0
extern s32 D_00472190_001073f0[] __asm__("D_00472190");
#define D_00472190 D_00472190_001073f0
#define func_00107120 ((void (*)(s32 *, s32 *, s32, s32)) func_00107120)
void func_001073f0(s32 unused, s32 *out) {
    s32 i;
    s32 a = 0;
    s32 b = 0;
    if (D_00351BD0 != 0) {
        for (i = 0; i < D_00494BA4; i++) {
            func_00107120(&out[a], &D_00472190[b], D_00494B20[i], 4);
            a += D_00494B20[i];
            b += D_00494B20[i] * 4;
        }
    } else {
        for (i = 0; i < D_00494BA4; i++) {
            func_00107120(&out[a], &D_0046E150[b], D_00494B20[i], 4);
            a += D_00494B20[i];
            b += D_00494B20[i] * 4;
        }
    }
}
#undef D_0046E150
#undef D_00472190
#undef func_00107120

/* func_00107520 (from hand/text_00100000_h1.c). */
typedef struct { s32 w0, w4, w8, w12; } Ent16_07520;
extern s32 D_002BCC98;
#define D_00494BA8 (*(Ent16_07520 *(*)) &D_00494BA8)
s32 func_00107520(s32 i) {
    Ent16_07520 *e = &D_00494BA8[i]; return (D_002BCC98 & e->w8) != 0;
}
#undef D_00494BA8

/* func_00107548 (from hand/text_00100000_s11_w74.c). */
typedef struct { u8 pad[8]; s32 key; s32 state; } Ent;
typedef struct { u8 pad[8]; f32 x, y; u8 pad10[8]; f32 z; u8 pad1c[4]; } Pt;
typedef struct { f32 v[4]; f32 p[3]; f32 w; f32 m[4][4]; E16 *t0; E16 *t1; u8 pad68[8]; } Work;
typedef struct { u8 pad[4]; s32 off; u8 pad8[8]; u8 e[1][128]; } Src;
void *func_00122048(s32, s32);
void func_001220b8(void *);
s32 func_00107ab8(f32 (*)[4], void *);
void func_002672f8(f32 *, f32 (*)[4], f32 *);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
typedef struct { EN v; } IE;
extern P8 D_0047A1D0;
extern P8 D_00472150;
IE D_00494BE0 ALIGNED(16);
extern s32 D_0029B300;
extern s32 D_0029B2F4;
extern s32 D_0029B2FC;
extern s32 D_0029B2F8;
#define func_001072c0 ((void (*)(s32, f32 *)) func_001072c0)
#define func_001073f0 ((void (*)(s32, f32 *)) func_001073f0)
extern E16 D_0046E150_00107548[] __asm__("D_0046E150");
#define D_0046E150 D_0046E150_00107548
extern E16 D_00472190_00107548[] __asm__("D_00472190");
#define D_00472190 D_00472190_00107548
extern E16 D_0047A210_00107548[] __asm__("D_0047A210");
#define D_0047A210 D_0047A210_00107548
extern E16 D_004761D0_00107548[] __asm__("D_004761D0");
#define D_004761D0 D_004761D0_00107548
extern s32 D_00494AA0_00107548[32] __asm__("D_00494AA0");
#define D_00494AA0 D_00494AA0_00107548
extern s32 D_00494B20_00107548[32] __asm__("D_00494B20");
#define D_00494B20 D_00494B20_00107548
extern Ent *D_00494BA8_00107548 __asm__("D_00494BA8");
#define D_00494BA8 D_00494BA8_00107548
extern Pt *D_00494BAC_00107548 __asm__("D_00494BAC");
#define D_00494BAC D_00494BAC_00107548
/* func_00107548 (s11w74, hand/strict). FLAGGED dead statement: the dead FP test
 * "if ((f32)i < 0.0f) b = 0;" in the loop (from s11w66) is removed by flow2 and leaves no code;
 * it only lengthens the loop so loop.c does not hoist &D_00494BA4 (144 words off without it).
 * The tail needs no barriers in strict mode: D_00494BE0 as a one-field struct with a 4-byte enum
 * field (own alias set), sources as P8 globals, destinations through s32 pointers. */
void func_00107548(f32 (*mtx)[4], Src *src) {
    s32 k;
    Work *w;
    f32 *z0, *z1;
    s32 *tbl;
    s32 last0, last1;
    s32 i, j, r, n;
    s32 *st, *b;

    w = func_00122048(0x70, 0x10);
    z0 = func_00122048(0x1000, 4);
    z1 = func_00122048(0x1000, 4);
    if (D_00351BD0 != 0) {
        w->t0 = D_0047A210;
        w->t1 = D_00472190;
    } else {
        w->t0 = D_004761D0;
        w->t1 = D_0046E150;
    }
    D_0029B2F4 = 0;
    D_0029B2F8 = 0;
    D_0029B2FC = 0;
    D_0029B300 = 0;
    w->w = 1.0f;
    sceVu0MulMatrix(w->m, D_002BBFE0, mtx);
    tbl = (s32 *)(src->off + (s32)src);
    D_00494BA0 = 0;
    last0 = 0;
    D_00494BA4 = 0;
    last1 = 0;
        D_00494AA0[0] = 0;
    D_00494B20[0] = 0;
        for (i = 0; i < D_00494BB0; i = j) {
        j = i + 1;
        k = j * 4;
        if (func_00107520(i)) {
            r = func_00107ab8(w->m, src->e[i]);
            b = &D_00494BA8->state; st = b + i * 4;
            *st = 2;
            if ((f32)i < 0.0f) b = 0; /* dead FP test (flagged) */
            switch (r) {
            case 0:
                if (tbl[k] != 0) {
                    *st = 1;
                    { s32 n = D_0029B2FC * 4;
                    if (D_002BC0A8.flags_3.b2) {
                        { Pt *pt = D_00494BAC; f32 *q8 = (f32 *)((s32)pt + 8);
                        { s32 o0 = i * 32; w->p[0] = *(f32 *)((s32)q8 + o0); }
                        { s32 o1 = i * 32; w->p[1] = ((Pt *)((s32)pt + o1))->y; }
                        { s32 o = i * 32 + 16; w->p[2] = *(f32 *)(o + (s32)q8); } }
                        func_002672f8(w->v, w->m, w->p);
                        z0[D_0029B2FC] = w->v[2] * 16.0f;
                        { s32 *kb = &D_00494BA8->key; s32 *key = kb + i * 4;
                        if (last0 != *key) {
                            D_00494AA0[++D_00494BA0] = 0;
                        }
                        D_00494AA0[D_00494BA0 - 1]++;
                        last0 = *key; }
                    }
                    { s32 *d = (s32 *)(n * 4 + (s32)w->t0); d[0] = tbl[k]; d[1] = tbl[k + 1]; }
                    D_0029B2FC++; }
                }
                break;
            case 1:
                if (tbl[k] != 0) {
                    *st = r;
                    { s32 n = D_0029B2F4 * 4;
                    if (D_002BC0A8.flags_3.b2) {
                        { Pt *pt = D_00494BAC; f32 *q8 = (f32 *)((s32)pt + 8);
                        { s32 o0 = i * 32; w->p[0] = *(f32 *)((s32)q8 + o0); }
                        { s32 o1 = i * 32; w->p[1] = ((Pt *)((s32)pt + o1))->y; }
                        { s32 o = i * 32 + 16; w->p[2] = *(f32 *)(o + (s32)q8); } }
                        func_002672f8(w->v, w->m, w->p);
                        z1[D_0029B2F4] = w->v[2] * 16.0f;
                        { s32 *kb = &D_00494BA8->key; s32 *key = kb + i * 4;
                        if (last1 != *key) {
                            D_00494B20[++D_00494BA4] = 0;
                        }
                        D_00494B20[D_00494BA4 - 1]++;
                        last1 = *key; }
                    }
                    { s32 *d = (s32 *)(n * 4 + (s32)w->t1); d[0] = tbl[k]; d[1] = tbl[k + 1]; }
                    D_0029B2F4++; }
                }
                break;
            default:
                *st = 0;
                break;
            }
        } else {
            { s32 *sb = &D_00494BA8->state; sb[i * 4] = 0; }
        }
    }
    {
        s32 *d, *e;
        d = (s32 *)(D_0029B2F4 * 16 + (s32)w->t1);
        d[0] = D_00472150.a;
        d[1] = D_00472150.b;
        D_00494BE0.v = 0;
        e = (s32 *)(D_0029B2FC * 16 + (s32)w->t0);
        e[0] = D_0047A1D0.a;
        e[1] = D_0047A1D0.b;
    }
    if (D_002BC0A8.flags_3.b2) {
        if (D_0029B2FC != 0) {
            func_001072c0(D_0029B2FC, z0);
        }
        if (D_0029B2F4 != 0) {
            func_001073f0(D_0029B2F4, z1);
        }
    }
    func_001220b8(z1);
    func_001220b8(z0);
    func_001220b8(w);
}
#undef func_001072c0
#undef func_001073f0
#undef D_0046E150
#undef D_00472190
#undef D_0047A210
#undef D_004761D0
#undef D_00494AA0
#undef D_00494B20
#undef D_00494BA8
#undef D_00494BAC

/* func_00107d30 (from hand/text_00100000_h28.c). */
typedef struct { u8 pad[16]; void *p; } Obj10;
extern u8 D_0046E120[];
extern u8 D_00472160[];
extern u8 D_004761A0[];
extern u8 D_0047A1E0[];
extern u8 D_0047E220[];
extern u8 D_00482260[];
extern void func_00106db0(void);
#define func_0015ed80 ((Obj10 *(*)(s32, void (*)(void))) func_0015ed80)
void func_00107d30(s32 arg0, s32 arg1) {
    Obj10 *o = func_0015ed80(arg0, func_00106db0);
    switch (arg1) {
    case 1:
        o->p = D_00351BD0 ? D_00472160 : D_0046E120;
        break;
    case 0:
        o->p = D_00351BD0 ? D_0047A1E0 : D_004761A0;
        break;
    case 3:
        o->p = D_00351BD0 ? D_00482260 : D_0047E220;
        break;
    }
}
#undef func_0015ed80

/* func_00107e10 (from auto/text_00100000_5.c). */
M2C_UNK func_002675a8(M2C_UNK *, void *);
extern s32 D_00494BC0[4][4];
#define D_00494BC0 (*(s8 (*)) &D_00494BC0)
void func_00107e10(void *arg0) {
    func_002675a8(&D_00494BC0, arg0 + 0x10);
    M2C_FIELD(&D_00494BC0, f32 *, 0xC) = (f32) M2C_FIELD(arg0, f32 *, 0xC);
    func_002675a8(&D_00494BC0 + 0x10, arg0 + 0x30);
}
#undef D_00494BC0

/* func_00107e60 (from hand/text_00100000_h1.c). */
void func_002673b8(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002678b8(void *, void *, void *);
void func_00107e60(void) {
    f32 m[4][4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    f32 *p = v;
    func_00267530(p, &D_002E2790.x, &D_002E2780.x);
    func_002673b8(p, p);
    func_002678b8(D_002A6C10, &D_0029B280, p);
}

/* func_00107ec0 (from hand/text_00100000_b00.c). */
extern s32 D_0048C418[][16];
extern s32 D_0048C518[];
extern s32 D_0048C398[][16];
extern s32 D_0048C558[];
extern s32 D_0048C308[][16];
extern s32 D_0048BFD8[][16];
extern s32 D_0048C1E8[];
extern s32 D_0048C228[];
extern s32 D_0048C068[][16];
extern s32 D_0048C0E8[][16];
extern s32 D_002BC170[4][4];
void func_00107ec0(s32 (*m)[4]) {
    s32 i, j, k;

    func_00107e60();
    if (D_00351BD0) {
        k = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                s32 g0 = D_002A3F60.i[0][i][j];
                s32 a = m[i][j];
                s32 b = D_002BC170[i][j];
                s32 g1 = D_002A3F60.i[1][i][j];
                s32 c = D_002BC020[i][j];
                s32 g2 = D_002A3F60.i[2][i][j];
                s32 d = D_002BBF60[i][j];
                s32 g3 = D_002A3F60.i[3][i][j];
                D_0048C308[0][k] = a;
                D_0048C308[1][k] = b;
                D_0048C398[0][k] = c;
                D_0048C398[1][k] = d;
                D_0048C418[0][k] = g0;
                D_0048C518[k] = D_00494BC0[i][j];
                D_0048C558[k] = D_002A6C10[i][j];
                D_0048C418[1][k] = g1;
                D_0048C418[2][k] = g2;
                D_0048C418[3][k] = g3;
                k++;
            }
        }
    } else {
        k = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                s32 g0 = D_002A3F60.i[0][i][j];
                s32 a = m[0][i * 4 + j];
                s32 b = D_002BC170[i][j];
                s32 g1 = D_002A3F60.i[1][i][j];
                s32 c = D_002BC020[i][j];
                s32 g2 = D_002A3F60.i[2][i][j];
                s32 d = D_002BBF60[i][j];
                s32 g3 = D_002A3F60.i[3][i][j];
                D_0048BFD8[0][k] = a;
                D_0048BFD8[1][k] = b;
                D_0048C068[0][k] = c;
                D_0048C068[1][k] = d;
                D_0048C0E8[0][k] = g0;
                D_0048C1E8[k] = D_00494BC0[i][j];
                D_0048C228[k] = D_002A6C10[i][j];
                D_0048C0E8[1][k] = g1;
                D_0048C0E8[2][k] = g2;
                D_0048C0E8[3][k] = g3;
                k++;
            }
        }
    }
}

/* func_00108180 (from hand/text_00100000_h1.c). */
void func_00108180(s32 n) {
    *(volatile s32 *)&D_002BCC98 = (1 << n) | *(volatile s32 *)&D_002BCC98;
}

/* func_001081a0 (from hand/text_00100000_h1.c). */
void func_001081a0(s32 n) {
    *(volatile s32 *)&D_002BCC98 = ~(1 << n) & *(volatile s32 *)&D_002BCC98;
}

/* func_001085e8 (from hand/text_00100000_h1.c). */
void func_001085e8(s32 a, s32 b) {
    func_0015ed80(a, func_00106db0)->w16 = b;
}

/* func_00108618 (from auto/text_00100000_14.c). */
extern volatile char D_00494C00;
void func_00108618(void) {
  int new_var;
  s32 *var_v0;
  s32 var_v1;
  var_v1 = 0x1F;
  new_var = 0x174;
  var_v0 = (&D_00494C00) + new_var;
  do
  {
    var_v1 -= 1;
    *var_v0 = 0;
    var_v0 -= 3;
  }
  while (var_v1 >= 0);
}

/* func_00108650 (from hand/text_00100000_h1.c). */
typedef Vtx Vec3;
extern Vec3 D_00494C00_00108650[] __asm__("D_00494C00");
#define D_00494C00 D_00494C00_00108650
void func_00108650(s32 i, s32 n) {
    f32 d = (f32)(n * 2);
    D_00494C00[i].x = d;
    D_00494C00[i].y = 1.0f;
    D_00494C00[i].z = -(1.0f / d);
    func_001081a0(i);
}
#undef D_00494C00

/* func_001086b8 (from hand/text_00100000_h1.c). */
extern Vec3 D_00494C00_001086b8[] __asm__("D_00494C00");
#define D_00494C00 D_00494C00_001086b8
void func_001086b8(s32 i, s32 n) {
    f32 d = (f32)(n * 2);
    D_00494C00[i].x = d;
    D_00494C00[i].y = 0.0f;
    D_00494C00[i].z = 1.0f / d;
}
#undef D_00494C00

