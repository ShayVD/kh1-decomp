#include "common.h"
/* func_00126f18: MATCH hand/nostrict (func_0014cc88 takes (o, f32): the 5.0f goes in f12 as its argument) */
typedef struct { u8 pad[8]; f32 x8; } S6c8;
typedef struct { u8 pad[0x29]; u8 x29; } S14c;
typedef struct {
    u32 flags; u8 pad4[0x68]; S6c8 *x6c; s32 x70; u8 pad74[0xd8]; S14c *x14c;
    u8 pad150[0x260]; f32 x3b0; u8 pad3b4[4]; f32 x3b8; u8 pad3bc[0x14]; s32 x3d0;
} Obj3d0;
typedef struct { u8 pad[4]; s32 x4; } Ctx4;
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { void (*fn)(Obj3d0 *, Ctx4 *, V4f *); u8 pad[28]; } Handler;
extern u32 D_002E27C8;
extern u32 D_002E3190;
extern Handler D_00350DA0[];
extern u8 D_002E31B0[];
void func_00126e80(Obj3d0 *, Ctx4 *, V4f *);
void func_0014c580(Obj3d0 *);
void func_0013dfb8(Obj3d0 *, V4f *);
s32 func_001443a8(Obj3d0 *);
void func_0013ecf8(Obj3d0 *, u8 *, V4f *);
void func_0013dc10(Obj3d0 *, s32);
void func_00130578(Obj3d0 *, f32, s32);
f32 func_001376e8(Obj3d0 *, V4f *);
void func_00137688(Obj3d0 *, f32);
void func_0015abd0(Obj3d0 *);
f32 func_0014cc88(Obj3d0 *, f32);
void func_00126f18(Obj3d0 *o, Ctx4 *c, V4f *v) {
    u32 fl;
    switch (o->x70) {
    case 2:
        func_00126e80(o, c, v);
        if ((D_002E27C8 >> 8) & 1) {
            if ((D_002E3190 >> 26) & 1) {
                func_0014c580(o);
                return;
            }
        }
        break;
    case 4:
        func_00126e80(o, c, v);
        break;
    default:
        if (D_00350DA0[o->x70].fn) D_00350DA0[o->x70].fn(o, c, v);
        break;
    }
    if ((D_002E3190 >> 24) & 1) {
        do { func_0013dfb8(o, v); } while (0);
        return;
    }
    if (((D_002E3190 >> 26) & 1) && o->x70 == 0 && func_001443a8(o) == 0) {
        if (((D_002E27C8 >> 4) & 1) && (!((D_002E27C8 >> 5) & 1) || v->w < o->x6c->x8)) {
            func_0013ecf8(o, D_002E31B0, v);
            func_0013dc10(o, 61);
            func_00130578(o, 0.0f, 0x40000000);
            o->x14c->x29 = 1;
            return;
        }
        if ((D_002E27C8 >> 5) & 1) {
            func_00137688(o, func_001376e8(o, v));
            do { func_0015abd0(o); } while (0);
        }
        return;
    }
    fl = o->flags;
    if (!(fl & 0x40000)) return;
    if (o->x3b8 <= o->x3b0 + 5.0f || o->x70 != 2) {
        o->flags = fl & ~0x40000;
        return;
    }
    if (fl & 0x20000) {
        if (c->x4 & 4) return;
        o->flags = fl & ~0x20000;
        return;
    }
    if (6.0f <= o->x3b0) {
        s32 save = o->x3d0;
        func_0014cc88(o, 5.0f);
        o->x3d0 = save;
        o->flags &= ~0x40000;
    }
}

/* func_00172998: MATCH hand/nostrict. Shared labels against if-conversion: r0 (return 0) reached from the p90 test, r1 (the final return 1) from the x90 test and after the range tests; r = 0 before the range tests (w13). */
typedef struct { f32 x, y, z, w; } V4_29;
typedef struct { u64 w0; u8 pad8[0x48]; f32 f50; } Sub40_29;
typedef struct { s32 w0; f32 f4, f8, fC, f10, f14, f18, f1C; } Prm29;
typedef struct { u8 pad[0xC]; Prm29 *pC; } K29;
typedef struct { u8 pad0[0x30]; V4_29 v30; u8 pad40[0x30]; s32 w70; u8 pad74[0x1C]; u64 x90; } Ob29;
typedef struct {
    u8 pad0[0x38]; u64 w38; Sub40_29 *p40; u8 pad44[0x10]; s32 w54; u8 pad58[0x10]; f32 f68;
    u8 pad6c[0x24]; void *p90; u8 pad94[8]; f32 f9C; f32 fA0; u8 padA4[0x28]; f32 fCC; V4_29 vD0;
    u8 padE0[0x40]; V4_29 v120; V4_29 v130; u8 pad140[0x20]; V4_29 v160;
} Wk29;
f32 func_00267390(V4_29 *, V4_29 *);
void func_002675a8(V4_29 *, V4_29 *);
void func_0013df40(Ob29 *, s32);
f32 func_00171aa8(f32, f32);
s32 func_00171ae8(Ob29 *, Wk29 *);
void *func_00171b80(Ob29 *, Wk29 *, s32);
void func_0014a0f0(Sub40_29 *);
void func_001693c8(Ob29 *, Wk29 *);

static inline s32 inl_free(Ob29 *o) {
    s32 r = 1;
    if (o->x90 != 0) r = 0;
    return r;
}

s32 func_00172998(Ob29 *o, Wk29 *w, K29 *k, s32 mode) {
    Prm29 *c = k->pC;
    switch (mode) {
    case 0:
    case 1:
        if (c == 0) return 0;
        if (o->w70 != 0) return 0;
        if (w->w54 != 0) {
            if (w->f68 <= 0.0f) {
            r0:
                return 0;
            }
            if (o->x90 == 0) goto r1;
            return 0;
        }
        {
        s32 r;
        if (w->p90 == 0) goto r0;
        r = 0;
        if (func_00267390(&w->vD0, &o->v30) < 0.0f) goto out;
        if (w->fCC < c->f4 - w->f9C) goto out;
        if (c->f8 + w->f9C < w->fCC) goto out;
        if (w->fA0 < c->fC - w->f9C) goto out;
        if (c->f10 + w->f9C < w->fA0) goto out;
        goto r1;
        out:
        return r;
        }
    case 2:
        if (w->w54 == 0) {
            func_0013df40(o, 0);
            w->f68 = func_00171aa8(c->f14, c->f18);
            w->w38 |= 2;
            if (w->p90 != 0) func_002675a8(&w->v160, &w->vD0);
        }
        if (!func_00171ae8(o, w)) {
            func_00171b80(o, w, c->w0);
            if (func_00171ae8(o, w)) {
                w->p40->w0 = (w->p40->w0 & ~0xC) | 4;
                w->p40->f50 = c->f1C;
            }
        } else {
            w->p40->w0 = (w->p40->w0 & ~0xC) | 4;
            func_0014a0f0(w->p40);
        }
        if ((u32)w->w38 & 1) {
            func_001693c8(o, w);
            return 1;
        }
        func_002675a8(&w->v120, &w->v160);
        w->v120.w = 20.0f;
        break;
    }
r1:
    return 1;
}
