/* Hand-matched functions from 0x0016d040..0x00170170 (worker b05).
 * Built with -fno-strict-aliasing. */
#include "common.h"

/* shared tuning table */

s32 func_00133000(void *, s32);
s32 func_00141200(void *, s32);
u32 func_001627e8(s32);
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x350]; u64 f370; } Ent370;
Ent370 *func_00123158(void *, Ent370 *);
s32 func_00123368(Ent370 *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);

/* --- func_0016d040 --- */
typedef struct { u8 pad[0x3c]; u32 x3c; u32 x40; } Hp6D0;
typedef struct { u8 pad[0x6c]; Hp6D0 *x6c; } Tg6D0;
typedef struct { s32 a, b; } P8_6D0;
typedef struct {
    u8 pad0[0x38]; u64 w38; u8 pad40[0x40];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    P8_6D0 p88; Tg6D0 *p90; u8 pad94[0xc]; f32 fA0; u8 padA4[0x2c]; f32 vD0[3]; f32 fDC; u8 padE0[0x40]; f32 v120[4];
} Wk6D0;

/* --- func_0016d768 --- */
typedef struct { u8 pad[0x3c]; s32 x3c; s32 x40; } Hp7;
typedef struct { u8 pad[0x170]; f32 x170; } Sb7;
typedef struct { u32 x0; u8 pad4[0x68]; Hp7 *x6c; s32 w70; u8 pad74[0xd4]; Sb7 *x148; } Ent7;
Ent7 *D_00574FB0 ALIGNED(16);

static inline s32 inl_ok(Ent7 *e, s32 K) {
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}

static inline s32 inl_thr(Wk6D0 *w, u32 a) {
    u32 t = w->p90->x6c->x3c * a;
    u32 r = func_001627e8(0x1000) >> 4;
    return t < w->p90->x6c->x40 * r;
}

/* --- func_0016d2d0 --- */
static inline s32 inl_001715b0(void *grp, Ent370 *self, f32 r) {
    f32 v[4];
    s32 n = 0;
    Ent370 *p = 0;
    f32 r2 = r * r;
    while ((p = func_00123158(grp, p)) != 0) {
        if (p == self) continue;
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        func_00267530(v, p->pos, self->pos);
        if (func_00267390(v, v) < r2) n++;
    }
    return n;
}

/* --- func_0016d768 (cont.) --- */
static inline s32 inl_hp(Ent7 *o, s32 k) {
    if (o->x0 & 0x200) return 0;
    if (o->x6c->x40 * k < o->x6c->x3c * 255) return 0;
    return 1;
}

/* --- func_0016fd98 --- */
typedef struct { Ent370 *tgt; s32 part; } LockF;
extern f32 D_0048E9F0;
s32 func_0012ee70(void *, s32);
s32 func_0012f040(void *, s32);
f32 func_0012ec60(void *, s32, f32 *);

static inline void inl_find(Ent370 *self, LockF *out, f32 r) {
    f32 a[4];
    f32 b[4];
    Ent370 *p;
    s32 i;
    f32 best, d;
    out->part = -1;
    out->tgt = 0;
    if (r <= 0.0f) best = D_0048E9F0;
    else best = r * r;
    p = 0;
    while ((p = func_00123158(self, p)) != 0) {
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        if (func_00141200(p, 0)) continue;
        for (i = -1; (i = func_0012ee70(p, i)) >= 0;) {
            if (!func_0012f040(p, i)) continue;
            func_0012ec60(p, i, a);
            func_00267530(b, a, self->pos);
            d = func_00267390(b, b);
            if (d < best) {
                out->tgt = p;
                best = d;
                out->part = i;
            }
        }
    }
}
#include "data/data_0048.h"
