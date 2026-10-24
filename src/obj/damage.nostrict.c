/* Damage: the damage kinds and thresholds of the tuning block *D_00308CDC
 * (func_001347f0), the damage an attack does to an object (func_001349d0,
 * func_00134ba8), and the hit records D_005267C0 (64) and D_005277C0 (128)
 * with the hit test func_001350d8 and func_001354b8. Flag mode: nostrict
 * (the other modes are in the sibling files). Read from the code, not proved
 * by a boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/pieces/D_00308CDC.h"
#include "data/bss_004F.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00120000_h54.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_002E3170.h"
#include "data/pieces/D_002E319C.h"
#include "data/pieces/D_002E31A0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E2780.h"
#include "data/types/nostrict_text_00120000_s6_05_p.h"
#include "data/pieces/D_002E3168.h"
#include "data/pieces/D_002C5960.h"
#include "data/types/nostrict_text_00120000_s6_05.h"
#include "m2c.h"

/* func_001349d0 (from hand/nostrict/text_00120000_h54.c). */
typedef struct { u8 p[0x3c]; s32 f3c; u8 p40[0x9c - 0x40]; f32 f9c; f32 fa0; } M6c;
typedef struct { u8 p[0x170]; f32 f170; } M148;
typedef struct { u32 f0; u8 p4[0x68]; M6c *f6c; u8 p70[0x18]; s32 f88; u8 p8c[0x148 - 0x8c]; M148 *f148; u8 p14c[0x3e4 - 0x14c]; f32 f3e4; } E19;
typedef struct { u64 f0; union { s64 d; s32 w; } f8; } A19;
extern s32 func_00157560(E19 *);
extern void func_00157648(E19 *);
extern void func_00138808(E19 *, f32);
extern void func_00141468(E19 *, s32);
s32 func_001349d0(E19 *e, A19 *m) {
    s64 x = m->f8.d;
    s32 v;
    if ((u32)(((s32)(x >> 32) & 0x1f) - 6) < 2 || ((s32)((s64)m->f0 >> 5) & 1)) return e->f6c->f3c;
    if ((e->f0 & 0x1000080) || ((D_002E31A8 >> 1) & 1)) v = 0;
    else v = -m->f8.w;
    switch ((s32)((u64)x >> 38) & 0xf) {
    case 11:
        v = m->f8.w;
        break;
    case 9:
        if (e->f6c->f9c > 0.0f) {
            e->f88 |= 1;
            e->f3e4 = (f32)m->f8.w * 60.0f * e->f6c->f9c;
            if (func_00157560(e) == 2) func_00157648(e);
        }
        m->f0 |= 2;
        v = 0;
        break;
    case 10:
        func_00138808(e, e->f6c->fa0 * 1800.0f);
        break;
    case 12:
        v = 0;
        if (e->f148) {
            e->f88 |= 8;
            e->f148->f170 = (f32)m->f8.w * 60.0f;
        }
        break;
    }
    func_00141468(e, v);
    return e->f6c->f3c;
}

/* func_001350d8 (from hand/nostrict/text_00120000_s6_05.c). */
typedef struct T23 { u8 b0; u8 pad[19]; } T23;
typedef struct Info { u8 pad[4]; u32 f4; u8 pad8[0x57]; u8 f5f; } Info;
typedef struct Info2 { u8 pad[7]; u8 f7; u8 pad8[0x14]; T23 *f1c; } Info2;
typedef struct Actor_350d8 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Actor_350d8 *f98;
    u8 pad9c[0x130 - 0x9c];
    Info *f130;
    Info2 *f134;
    u8 pad138[0x164 - 0x138];
    s32 f164;
    u8 pad168[4];
    f32 f16c;
    u8 pad170[0x370 - 0x170];
    u64 f370;
    u8 pad378[0x3ac - 0x378];
    u32 f3ac;
    u8 pad3b0[0x440 - 0x3b0];
    u64 f440;
} Ent;
extern Ent *func_001230a0(Ent *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
typedef struct { u8 p0[0x10]; V4D f10; } XD;
typedef struct {
    u32 b0:12;
    u32 k:2;
    u32 b14:9;
    u32 b23:1;
    u32 b24:8;
    s32 f4;
    s32 f8;
    u8 pc[4];
    V4D f10;
    u8 p20[0x30 - 0x20];
    union { u64 d; struct { u32 f30; XD *f34; } s; } u30;
    u8 p38[0x5c - 0x38];
    PD *f5c;
} AD;
typedef struct { u8 p0[5]; u8 f5; u8 p6[0x14 - 6]; f32 *f14; } ID;
typedef struct {
    u8 p0[0x10];
    V4D f10;
    u8 p20[0x30 - 0x20];
    V4D f30;
    u8 p40[0x88 - 0x40];
    u32 f88;
    u8 p8c[0x134 - 0x8c];
    ID *f134;
    u8 p138[0x370 - 0x138];
    u64 f370;
    u8 p378[0x3e0 - 0x378];
    u32 mask;
    u8 p3e4[0x3ec - 0x3e4];
    QD *head;
} BD;
typedef struct GD { u8 p0[0x88]; u32 f88; } GD;
extern QD D_005267C0[];
extern QD D_005277C0[];
extern QD D_005297C0;
extern QD *func_00134f80(QD *, s32);
extern void func_00135000(BD *, QD *);
extern f32 func_00176850(void);
extern s32 func_00176578(s32, s32, s32, s32);
extern s32 func_00134ba8(AD *, BD *, u32 *);
extern void func_00121fc4(V4D *, V4D *);
QD *func_001350d8(AD *a, u32 mask, BD *b) {
    QD *q;
    u32 fl;
    GD *g;
    V4D v;
    f32 lim;
    if (mask && (b->mask & mask)) return 0;
    fl = a->u30.s.f30;
    if (((s32)(a->u30.d >> 6) & 0xf) == 9) {
        q = func_00134f80(D_005267C0, 64);
        if (q) {
            q->next = b->head;
            b->head = q;
        } else {
            q = &D_005297C0;
        }
    } else if ((b->f88 & 1) || (b->head && b->head->u8.b.n > 0)) {
        q = func_00134f80(D_005277C0, 128);
        fl |= 0x800;
        if (b->f88 & 1) fl |= 0x10000;
        if (b->head) {
            { s32 t = func_00176850() * 6.0f; fl &= 0xffff0fff; fl |= ((t + 6) & 0xf) << 12; }
        }
        if (q) func_00135000(b, q);
        else q = &D_005297C0;
        if (a->b23) {
            q->f34 = D_00350CE0;
            q->f38 = 9;
        } else if (a->f8) {
            q->f34 = a->f8;
            q->f38 = func_00176578(a->f8, 128, 1 << a->f5c->f28, 0);
        } else {
            q->f34 = 0;
        }
        if (q - D_005277C0 >= 96) {
            g = 0;
            while ((g = (GD *)func_001230a0((Ent *)g)) != 0) g->f88 &= ~1;
        }
    } else {
        q = func_00134f80(D_005267C0, 64);
        if (q) func_00135000(b, q);
        else q = &D_005297C0;
    }
    q->mask = mask;
    b->mask |= mask;
    q->k = a->k;
    q->u8.w.fc = fl;
    if (((b->f370 >> 37) & 3) == 2) q->u8.b.c0 = a->f5c->fc;

    q->u8.w.f8 = func_00134ba8(a, b, &q->u8.w.fc);
    q->f4 = (s32)a->u30.s.f34;
    q->f2c = a->f5c;
    q->f20 = -1;

    func_00267530((f32 *)&v, (f32 *)&b->f10, (f32 *)&a->f10);
    v.y = 0.0f;
    func_00121fc4(&v, &v);
    if (b->f134 && b->f134->f5) lim = b->f134->f14[3] * 0.5f;
    else lim = 0.0f;
    if (v.w <= lim) {
        if (a->u30.s.f34) {
            func_00267530((f32 *)&v, (f32 *)&b->f10, (f32 *)&a->u30.s.f34->f10);
            v.y = 0.0f;
            func_00121fc4(&q->f10, &v);
        } else {
            func_00267530((f32 *)&q->f10, (*(f32 (*)[0x4])&D_002C58A0), (f32 *)&b->f30);
        }
    } else {
        func_002675a8((f32 *)&q->f10, (f32 *)&v);
    }
    q->f10.w = 1.0f;
    return q;
}

/* func_001354b8 (from hand/nostrict/text_00120000_h54.c). */
typedef struct { u8 p[0x170]; u64 f170; } P148;
typedef struct { u8 p[0xc8]; u8 *fc8; u8 pcc[0xd8 - 0xcc]; s32 fd8; } P6c;
typedef struct { u8 p[0x6c]; P6c *f6c; u8 p70[0x148 - 0x70]; P148 *f148; } O20;
typedef struct { u8 p[0x2c]; s32 f2c; } P5c;
typedef struct { u8 p[0x34]; O20 *f34; void *f38; u8 p3c[0x54 - 0x3c]; s32 f54; u8 p58[4]; P5c *f5c; u8 p60[0xa0 - 0x60]; s32 fa0; } E20;
typedef struct { void *p; s32 n; } Arg20;
extern s32 func_00123368(O20 *);
extern void func_00141608(O20 *, s32);
extern void func_0012bbc8(s32, void *, s32, Arg20 *, s32);
static inline s32 min54(s32 a, s32 b) { return a < b ? a : b; }
static inline s32 max54(s32 a, s32 b) { return a > b ? a : b; }
#define func_001350d8 ((s32 (*)(E20 *, s32, O20 *)) func_001350d8)
s32 func_001354b8(E20 *e, O20 *x) {
    s32 r;
    O20 *o;
    u8 *q;
    s32 n;
    if (!func_00123368(x)) return 0;
    r = func_001350d8(e, e->f54, x);
    if (r) {
    o = e->f34;
    if (o && (q = o->f6c->fc8) != 0 && (n = x->f6c->fd8) > 0) {
        f32 f = (f32)(n - *q) * (f32)(*(Cfg_308cdc **)&D_00308CDC)->f94 / 100.0f + 1.0f;
        s32 t, m;
        if (o->f148 && ((s32)(o->f148->f170 >> 32) & 1)) f += (f32)(*(Cfg_308cdc **)&D_00308CDC)->f95 / 100.0f;
        func_00141608(o, min54(max54(1, (s32)((f32)e->f5c->f2c * f)), e->f5c->f2c * (*(Cfg_308cdc **)&D_00308CDC)->f96 / 100));
    }
    if (e->f38) {
        Arg20 a;
        a.p = &x;
        a.n = 4;
        func_0012bbc8(e->fa0, e->f38, 1, &a, 0);
    }
    }
    return r;
}
#undef func_001350d8

/* func_00135740 (from hand/nostrict/text_00130000.c). */
void func_00137448(s32);
void func_00135740(s32 arg0, s32 arg1, s32 arg2) {
    func_00137448(arg0);
    M2C_FIELD(arg0, s32 *, 0x3A0) = arg1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), s16 *, 0x50) = (s16) arg2;
}

