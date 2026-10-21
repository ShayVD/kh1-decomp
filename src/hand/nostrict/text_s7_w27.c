#include "common.h"
/* func_0016fc60: MATCH hand/nostrict */
#define A a
#define B b
typedef struct { f32 x, y, z, w; } V4FC;
typedef struct { u8 pad0[0x10]; V4FC pos; } ChrFC;
typedef struct { u8 pad0[0x90]; void *p90; s32 part; } WkFC;
extern u32 D_002C5958;
extern f32 D_0048E9EC;
extern s32 func_00122ff8(void *);
extern void func_0012ec60(void *, s32, f32 *);
extern s32 func_0012ee70(void *, s32);
extern s32 func_0012f040(void *, s32);
extern f32 func_00267390(void *, void *);
extern void func_00267530(void *, void *, void *);

static inline s32 inl_valid(void *p, s32 part) {
    if (!(D_002C5958 & 1)) return 0;
    if (p == 0 || !func_00122ff8(p)) return 0; return func_0012f040(p, part);
}

static inline s32 inl_best(void *p, ChrFC *c) {
    f32 a[4];
    f32 b[4];
    s32 i, best;
    f32 bd, d;
    best = -1;
    if (p != 0) {
        i = -1;
        bd = D_0048E9EC;
        while ((i = func_0012ee70(p, i)) >= 0) {
            if (!func_0012f040(p, i)) continue;
            func_0012ec60(p, i, a);
            func_00267530(b, a, &c->pos);
            d = func_00267390(b, b);
            if (d < bd) {
                bd = d;
                best = i;
            }
        }
    }
    return best;
}

void func_0016fc60(ChrFC *c, WkFC *w) {
    if (func_00122ff8(w->p90)) {
        if (w->part < 0 || !inl_valid(w->p90, w->part)) w->part = inl_best(w->p90, c);
    } else {
        w->p90 = 0;
    }
}

/* func_0017b4f8: MATCH hand/nostrict */
typedef struct { f32 x, y, z, len; } SegB;
typedef struct { f32 len, x, y, z; } SegL;
typedef struct { s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[0x2c - 0x1c]; SegL seg[1]; } PathB;
#include "data/pieces/D_00362438.h"

s32 func_0017b4f8(s32 *pi, f32 *pt, f32 dt) {
    s32 i = *pi;
    PathB *p = ((PathB *)D_00362438);
    s32 changed = 0;
    f32 inv, t, rem;
    s32 nl;
    inv = 1.0f / ((SegL *)((u8 *)p + 0x2c))[i].len;
    { s32 f = p->flags & 1; nl = f != 0; }
    t = *pt;
    t += dt * inv;
    if (!(t < 0.0f)) goto pos;
    if (!nl || i != 0) goto neg;
    t = 0.0f;
    i = 0;
    goto store;
neg:
    rem = (t - 0.0f) / inv;
    { s32 j = i - 1; if (j < 0) j = p->n - 1; i = j; }
    t = 1.0f;
    changed = 1;
    goto again;
pos:
    if (!(1.0f < t)) goto store;
    if (nl && !(i < p->n - 2)) {
        i = p->n - 2;
        t = 1.0f;
        goto store;
    }
    i = (i + 1 < p->n) ? i + 1 : 0;
    rem = (t - 1.0f) / inv;
    changed = 1;
    t = 0.0f;
again:
    inv = 1.0f / ((SegL *)((u8 *)p + 0x2c))[i].len;
    t += rem * inv;
    if (!(t < 0.0f)) goto pos;
    if (!nl || i != 0) goto neg;
    t = 0.0f;
store:
    *pi = i;
    *pt = t;
    return changed;
}
#include "data/data_0048.h"
#include "data/pieces/D_002C5958.h"
