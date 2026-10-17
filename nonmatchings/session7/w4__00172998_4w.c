/* 4w off (hand/nostrict; s6 draft 6w). Fix: 'if (w->p90 == 0 || func_00267390(...) < 0.0f) return 0;' as one test (shared return-0 block stops the ce pass hoisting v0=0 above the branch, so p90 loads into v0). Still off: x90 'return 1' and the final 'return 1' blocks: ce (if-conversion after combine) hoists v0=1 above the branch (ld x90 -> v1, bc1f instead of bc1fl, extra move v0,zero). Mechanism found with -da: 15.ce hoists single-pred return blocks. */
#include "common.h"
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
            if (!(w->f68 <= 0.0f) && o->x90 == 0) return 1;
            return 0;
        }
        if (w->p90 == 0 || func_00267390(&w->vD0, &o->v30) < 0.0f) return 0;
        if (w->fCC < c->f4 - w->f9C) return 0;
        if (c->f8 + w->f9C < w->fCC) return 0;
        if (w->fA0 < c->fC - w->f9C) return 0;
        if (c->f10 + w->f9C < w->fA0) return 0;
        return 1;
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
    return 1;
}
