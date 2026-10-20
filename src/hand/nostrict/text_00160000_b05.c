/* Hand-matched functions from 0x0016d040..0x00170170 (worker b05).
 * Built with -fno-strict-aliasing. */
#include "common.h"

/* shared tuning table */
typedef struct {
    u8 pad0[0x84];
    u32 x84, x88, x8c, k[3], x9c, xa0, xa4;
    u8 padA8[0x168 - 0xa8];
    f32 x168, x16c, x170, x174, x178, x17c;
    struct { f32 a, b, c, d, r; } rng[3];
    f32 x1bc, x1c0, x1c4, x1c8;
} Prm05;
extern Prm05 D_0035AE80;
extern u8 D_0035AF20;
extern void *D_0035BD40[];

s32 func_00133000(void *, s32);
s32 func_00141200(void *, s32);
s32 func_00132fe0(s32);
u32 func_001627e8(s32);
f32 func_001376e8(void *, f32 *);
void func_002675a8(void *, void *);
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x350]; u64 f370; } Ent370;
Ent370 *func_00123158(void *, Ent370 *);
s32 func_00123368(Ent370 *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);

/* --- func_0016d040 --- */
typedef struct { u8 pad[0x3c]; u32 x3c; u32 x40; } Hp6D0;
typedef struct { u8 pad[0x6c]; Hp6D0 *x6c; } Tg6D0;
typedef struct { u8 pad[0x70]; s32 w70; } Ent6D0;
typedef struct { s32 a, b; } P8_6D0;
typedef struct {
    u8 pad0[0x38]; u64 w38; u8 pad40[0x40];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    P8_6D0 p88; Tg6D0 *p90; u8 pad94[0xc]; f32 fA0; u8 padA4[0x2c]; f32 vD0[3]; f32 fDC; u8 padE0[0x40]; f32 v120[4];
} Wk6D0;
typedef struct { u8 pad[0x88]; u32 x88; } T88;

/* --- func_0016d768 --- */
typedef struct { u8 pad[0x3c]; s32 x3c; s32 x40; } Hp7;
typedef struct { u8 pad[0x170]; f32 x170; } Sb7;
typedef struct { u32 x0; u8 pad4[0x68]; Hp7 *x6c; s32 w70; u8 pad74[0xd4]; Sb7 *x148; } Ent7;
typedef struct { u8 pad[0x6c]; Hp7 *x6c; } Tg7;
typedef struct {
    s32 x0; u8 pad4[0x34]; u64 w38; u8 pad40[0x40];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    Ent7 *x88; s32 x8c; Tg7 *p90; u8 pad94[0x48]; f32 fDC;
} Wk7;
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

s32 func_0016d040(Ent6D0 *e, Wk6D0 *w, s32 unused, s32 mode) {
    f32 f;
    u32 a, t;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok((Ent7 *)e, 4)) return 0;
        if (w->p90 == 0) return 0;
        if (func_00141200(w->p90, 8)) return 0;
        switch (func_00132fe0(4)) {
        case 1:
            f = w->fDC;
            if (f < D_0035AE80.x168 || D_0035AE80.x16c < f) return 0;
            if (inl_thr(w, D_0035AE80.x84)) return 0;
            break;
        case 2:
            f = w->fDC;
            if (f < D_0035AE80.x170 || D_0035AE80.x174 < f) return 0;
            if (inl_thr(w, D_0035AE80.x88)) return 0;
            break;
        case 3:
            f = w->fDC;
            if (f < D_0035AE80.x178 || D_0035AE80.x17c < f) return 0;
            if (inl_thr(w, D_0035AE80.x8c)) return 0;
            break;
        default:
            return 0;
        }
        break;
    case 2:
        func_001376e8(e, w->vD0);
        func_002675a8(w->v120, w->vD0);
        w->v120[3] = 0;
        w->w80.b.m = mode;
        w->w80.b.z = 4;
        w->p88 = *(P8_6D0 *)&w->p90;
        break;
    }
    return 1;
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

#define CASE_6D2(i) \
            f = w->fDC; \
            if (f < D_0035AE80.rng[i].a || D_0035AE80.rng[i].b < f) return 0; \
            f = w->fA0; \
            if (f < D_0035AE80.rng[i].c || D_0035AE80.rng[i].d < f) return 0; \
            if ((u32)((inl_001715b0(e, (Ent370 *)w->p90, D_0035AE80.rng[i].r) + 1) * D_0035AE80.k[i]) < (func_001627e8(0x1000) >> 4)) return 0; \
            break;

s32 func_0016d2d0(Ent6D0 *e, Wk6D0 *w, s32 unused, s32 mode) {
    f32 f;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok((Ent7 *)e, 5)) return 0;
        if (w->p90 == 0) return 0;
        if (((T88 *)w->p90)->x88 & 1) return 0;
        if (func_00141200(w->p90, 9)) return 0;
        switch (func_00132fe0(5)) {
        case 1:
            CASE_6D2(0)
        case 2:
            CASE_6D2(1)
        case 3:
            CASE_6D2(2)
        default:
            return 0;
        }
        break;
    case 2:
        func_001376e8(e, w->vD0);
        func_002675a8(w->v120, w->vD0);
        w->v120[3] = 0;
        w->w80.b.m = mode;
        w->w80.b.z = 5;
        w->p88 = *(P8_6D0 *)&w->p90;
        break;
    }
    return 1;
}

/* --- func_0016d768 (cont.) --- */
static inline s32 inl_hp(Ent7 *o, s32 k) {
    if (o->x0 & 0x200) return 0;
    if (o->x6c->x40 * k < o->x6c->x3c * 255) return 0;
    return 1;
}

s32 func_0016d768(Ent7 *e, Wk7 *w, s32 unused, s32 mode) {
    Ent7 *arr[3];
    s32 i, r, k, ok;
    u32 t;
    f32 f;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok(e, 6)) return 0;
        r = func_00132fe0(6);
        arr[0] = e;
        arr[1] = D_0035BD40[0];
        arr[2] = D_0035BD40[w->x0 ^ 3];
        D_00574FB0 = 0;
        switch (r) {
        case 1: k = *(u8 *)&D_0035AE80.x9c; break;
        case 2: k = D_0035AF20; break;
        case 3: k = *(u8 *)&D_0035AE80.xa4; break;
        default: k = 0; break;
        }
        for (i = 0; i < 3; i++) {
            if (arr[i] == 0) continue;
            if (!inl_hp(arr[i], k)) continue;
            if (0.0f < arr[i]->x148->x170) continue;
            if (D_00574FB0 == 0) {
                D_00574FB0 = arr[i];
                break;
            }
        }
        if (D_00574FB0) break;
        if (w->p90 == 0) goto end;
        ok = 0;
        switch (r) {
        case 1:
            f = w->fDC;
            if (D_0035AE80.x1bc <= f && f <= D_0035AE80.x1c0) {
                t = w->p90->x6c->x3c;
                t *= D_0035AE80.x9c;
                t = t < w->p90->x6c->x40 * (func_001627e8(0x1000) >> 4);
                if (!t) ok = 1;
            }
            break;
        case 2:
            f = w->fDC;
            if (D_0035AE80.x1c4 <= f && f <= D_0035AE80.x1c8) {
                t = w->p90->x6c->x3c;
                t *= D_0035AE80.xa0;
                t = t < w->p90->x6c->x40 * (func_001627e8(0x1000) >> 4);
                if (!t) ok = 1;
            }
            break;
        case 3:
            f = w->fDC;
            if (D_0035AE80.x1c4 <= f && f <= D_0035AE80.x1c8) {
                t = w->p90->x6c->x3c;
                t *= D_0035AE80.xa0;
                t = t < w->p90->x6c->x40 * (func_001627e8(0x1000) >> 4);
                if (!t) ok = 1;
            }
            break;
        }
        if (!ok) goto end2;
        for (i = 0; i < 3; i++) {
            if (arr[i] == 0) continue;
            if (arr[i]->x0 & 0x200) continue;
            if (0.0f < arr[i]->x148->x170) continue;
            if (D_00574FB0 == 0) {
                D_00574FB0 = arr[i];
                break;
            }
        }
    end:
    end2:
        if (D_00574FB0) break;
        return 0;
    case 2:
        w->w80.b.m = mode;
        w->w80.b.z = 6;
        w->x88 = D_00574FB0;
        w->x8c = 0;
        break;
    }
    return 1;
}

/* --- func_0016fd98 --- */
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x50]; s32 w70; u8 pad74[0x250]; f32 f2C4; } EntF;
typedef struct { u8 pad[4]; f32 f4; } RngF;
typedef struct { Ent370 *tgt; s32 part; } LockF;
typedef struct {
    u8 pad0[8]; RngF *p08; RngF *p0C; u8 pad10[0x28]; u64 w38; u8 pad40[0x24]; f32 f64; u8 pad68[0x28];
    LockF l90; u8 pad98[4]; f32 f9C; f32 fA0; u8 padA4[0xc]; f32 vB0[4]; f32 vC0[3]; f32 fCC; f32 vD0[3]; f32 fDC;
} WkF;
extern f32 D_0048E9F0;
s32 func_0012ee70(void *, s32);
s32 func_0012f040(void *, s32);
f32 func_0012ec60(void *, s32, f32 *);
f32 func_00162c20(f32 *);
void func_0016fa10(EntF *, WkF *, RngF *);
void func_0016fc60(EntF *, WkF *);

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

void func_0016fd98(EntF *e, WkF *w) {
    RngF *rng;
    LockF l;
    if (w->f64 > 0.0f) rng = w->p0C;
    else rng = w->p08;
    func_0016fa10(e, w, rng);
    if ((s32)w->w38 & 1) return;
    inl_find((Ent370 *)e, &l, rng->f4);
    if (l.tgt == 0 || l.part < 0) inl_find(D_0035BD40[0], &l, rng->f4);
    if (l.part < 0) l.tgt = 0;
    if ((s32)(w->w38 >> 11) & 1) func_0016fc60(e, w);
    else if (l.tgt) w->l90 = l;
    if (w->l90.tgt != 0 && w->l90.part >= 0) {
    w->f9C = func_0012ec60(w->l90.tgt, w->l90.part, w->vB0);
    if (((s32)(w->w38 >> 20) & 1) || e->w70 == 8 || e->w70 == 24 || e->w70 == 25) w->vB0[1] += e->f2C4;
    func_00267530(w->vC0, w->vB0, e->pos);
    func_002675a8(w->vD0, w->vC0);
    w->fA0 = w->vD0[1];
    w->vD0[1] = 0;
    w->fCC = func_00162c20(w->vC0);
    w->fDC = func_00162c20(w->vD0);
    } else {
        w->l90.tgt = 0;
        w->l90.part = -1;
    }
}
#include "data/data_0048.h"
