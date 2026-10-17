/* Hand-matched functions (worker c04), built without strict aliasing. */
#include "common.h"

typedef struct { s16 h0; s16 pad2; s32 w4; f32 f8; } Res8;
typedef struct { u8 pad[4]; s32 w4; } Res04;
typedef struct { u8 pad[0x30]; s32 w30; } Res30;
typedef struct { u8 pad[0xC]; void *cb; } Task0C;
typedef struct { u8 pad[0xB4]; void *cb; void **slot; } Sub2C;
typedef struct { u8 pad[0x2C]; Sub2C *p2C; } Sub14C;
typedef struct { u8 pad[0x10]; f32 f10; } Sub6C;
typedef struct {
    u8 pad[8]; void *w8; u8 padC[0x60]; Sub6C *p6C; s32 w70; u8 pad74[0xD8]; Sub14C *p14C;
} ObjB6;
typedef union { u64 x; struct { u64 lo:40; u64 id:16; u64 hi:8; } b; struct { u32 lo; u8 b4; } c; } Bf80;
typedef struct {
    u8 pad[0x3C]; void **slot; Sub2C *p40; u8 pad44[8]; s32 w4C; u8 pad50[0x30];
    Bf80 w80; u8 pad88[8]; void *p90; s32 w94; s32 w98; f32 f9C; f32 fA0; u8 padA4[0x2C];
    f32 vD0[3]; f32 fDC; u8 padE0[0x40]; f32 v120[3]; s32 w12C;
} WkB6;
typedef union { u16 h; s32 w; } RngId;
typedef struct { RngId id; f32 f4, f8, fC, f10; } RngB6;
typedef struct { u8 pad[4]; s32 flags; u8 pad8[4]; RngB6 *rng; } KB6;

extern u32 D_002C5958;
extern f32 D_002BBDFC;
extern s32 D_00574FB8;
extern void *D_00574FC0[20];
extern s32 func_00122ff8(void *);
extern s32 func_0012f040(void *, s32);
extern s32 func_0012ee70(void *, s32);
extern void func_00130340(ObjB6 *, s32, f32);
extern Task0C *func_00130578(ObjB6 *, s32, f32);
extern void func_001376e8(void *, f32 *);
extern Res8 *func_0013dbe0(ObjB6 *, s32);
extern Res8 *func_0013dc10(ObjB6 *, s32);
extern s32 func_00141288(ObjB6 *, s32);
extern void func_001412f8(ObjB6 *, s32);
extern Res30 *func_001477c8(s32);
extern void func_0014cce0(ObjB6 *, f32);
extern s32 func_00169510(ObjB6 *, WkB6 *, s32);
extern void func_00171f38(void);
extern void func_002675a8(void *, void *);

static inline s32 inl_00171118(void *t, s32 i) {
    s32 r = 0;
    if (!(D_002C5958 & 1)) return r;
    if (t == 0) return r;
    if (!func_00122ff8(t)) return 0;
    if (i >= 0) return func_0012f040(t, i);
    for (i = -1; (i = func_0012ee70(t, i)) >= 0;) {
        if (func_0012f040(t, i)) return 1;
    }
    return 0;
}

static inline Res8 *inl_00171b80(ObjB6 *o, WkB6 *l, u16 k) {
    s32 i = D_00574FB8;
    s32 n = 0;
    Res8 *r;
    Sub2C *p;
    while (D_00574FC0[i] != 0) {
        i++;
        n++;
        if (i >= 20) i = 0;
        if (n >= 20) goto out;
    }
out:
    D_00574FB8 = i + 1;
    if (i + 1 >= 20) D_00574FB8 = 0;
    r = func_0013dc10(o, k);
    p = o->p14C->p2C;
    if (p != 0) {
        void **s = &D_00574FC0[i];
        p->slot = s;
        p->cb = func_00171f38;
        l->slot = s;
        *s = p;
        l->p40 = p;
    } else {
        l->p40 = 0;
    }
    return r;
}

s32 func_0016b670(ObjB6 *o, WkB6 *w, KB6 *k, s32 mode) {
    RngB6 *rng = k->rng;
    Res8 *r;
    f32 f;
    s32 fl;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (rng == 0) return 0;
        if (!func_00169510(o, w, k->flags)) return 0;
        if (!inl_00171118(w->p90, w->w94)) return 0;
        if (o->w8 != w->p90) {
            if (w->fDC < rng->f4 - w->f9C) goto r4;
            if (rng->f8 + w->f9C < w->fDC) goto r4;
            if (w->fA0 < rng->fC - w->f9C) goto r4;
            if (rng->f10 + w->f9C < w->fA0) { r4: return 0; }
        }
        r = func_0013dbe0(o, rng->id.w);
        if (r->f8 != 0.0f) k->flags |= 8;
        if (!func_00141288(o, func_001477c8(r->w4)->w30)) return 0;
        break;
    case 2:
        w->w80.c.b4 = 1;
        w->w80.b.id = rng->id.h;
        func_001376e8(o, w->vD0);
        func_002675a8(w->v120, w->vD0);
        w->w12C = 0;
        r = inl_00171b80(o, w, w->w80.b.id);
        w->w4C = r->h0;
        func_001412f8(o, func_001477c8(r->w4)->w30);
        if (o->w70 != 8 && o->w70 != 24 && w->fA0 < 0.0f && ((fl = k->flags) & 8)) {
            f = r->f8 - w->fA0;
            if (o->p6C->f10 < f) f = o->p6C->f10;
            if (r->h0 >= 0) {
                if (fl & 2) func_00130578(o, 0x40000000, 8.0f);
                else if (fl & 4) func_00130578(o, 0x40000075, 8.0f);
                else func_00130578(o, 0x40000006, 8.0f);
            }
            func_0014cce0(o, f);
        } else if (r->h0 >= 0) {
            if (k->flags & 0x10) {
                f = 0.0f;
                func_0014cce0(o, f);
                func_00130340(o, r->h0 | 0x1800000, f);
            }
            if (r->h0 >= 0) {
                s32 fl2 = k->flags;
                if (fl2 & 2) func_00130578(o, 0x40000000, 8.0f);
                else if (fl2 & 4) func_00130578(o, 0x40000075, 8.0f);
                else if (fl2 & 0x10) func_00130578(o, 0x40000006, 8.0f);
                else func_00130578(o, 0x40000000, 8.0f);
            }
        }
        w->w12C = 0;
        return 1;
    }
    return 1;
}

/* ---- func_0016c650 ---- */
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x350]; u64 f370; } Ent370;
typedef struct { f32 a0, a1, b0, b1, r, c0, c1, d0, d1; } ZoneC6;
typedef struct { u8 pad[0xA8]; s32 cnt[3]; u8 padB4[0x34]; ZoneC6 z[3]; } PrmC6;
typedef struct { void *p; s32 i; } P8C6;
typedef union { u64 x; struct { u64 lo:32; u64 m:8; u64 id:16; u64 hi:8; } b; } Bf80C6;
typedef struct {
    u8 pad[0x38]; u64 w38; u8 pad40[0x40];
    Bf80C6 w80; P8C6 q88; P8C6 q90; u8 pad98[8]; f32 fA0; u8 padA4[0x2C];
    f32 vD0[3]; f32 fDC; u8 padE0[0x40]; f32 v120[3]; s32 w12C;
} WkC6;
typedef struct { u8 pad[0x70]; s32 w70; } ObjC6;

extern PrmC6 D_0035AE80;
extern Ent370 *func_00123158(void *, Ent370 *);
extern s32 func_00123368(Ent370 *);
extern s32 func_00132fe0(s32);
extern s32 func_00133000(ObjC6 *, s32);
extern s32 func_00141200(void *, s32);
extern void func_00267530(void *, void *, void *);
extern f32 func_00267390(void *, void *);

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

static inline s32 inl_ok(ObjC6 *e, s32 K) {
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}

#define ZONE(i) \
        f = w->fDC; \
        if (f < D_0035AE80.z[i].a0) goto r0; \
        if (D_0035AE80.z[i].a1 < f) goto r0; \
        f = w->fA0; \
        if (f < D_0035AE80.z[i].b0) goto r0; \
        if (D_0035AE80.z[i].b1 < f) return 0; \
        if (inl_001715b0(o, w->q90.p, D_0035AE80.z[i].r) < D_0035AE80.cnt[i]) return 0; \
        f = w->fDC; \
        if (!(D_0035AE80.z[i].c0 <= f)) break; \
        if (!(f <= D_0035AE80.z[i].c1)) break; \
        f = w->fA0; \
        if (f < D_0035AE80.z[i].d0) return 0; \
        if (D_0035AE80.z[i].d1 < f) return 0; \
        break;

s32 func_0016c650(ObjC6 *o, WkC6 *w, s32 k, s32 mode) {
    f32 f;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok(o, 1)) return 0;
        if (w->q90.p == 0) return 0;
        if (func_00141200(w->q90.p, 3)) goto r0;
        switch (func_00132fe0(1)) {
        case 1:
            ZONE(0)
        case 2:
            ZONE(1)
        case 3:
            ZONE(2)
        default:
        r0:    return 0;
        }
        break;
    case 2:
        func_001376e8(o, w->vD0);
        func_002675a8(w->v120, w->vD0);
        w->w12C = 0;
        w->w80.b.m = mode;
        w->w80.b.id = 1;
        w->q88 = w->q90;
        break;
    }
    return 1;
}

/* ---- func_0016e3f8 ---- */
typedef struct { f32 x, y, z, w; } V4E3;
typedef struct { u8 pad[8]; f32 f8; } Sub4E3;
typedef struct {
    u8 pad0[4]; Sub4E3 *p4; u8 pad8[0x30]; u64 w38; u8 pad40[0x64]; f32 fA4; u8 padA8[0x38];
    V4E3 vE0; V4E3 vF0;
} WkE3;
typedef struct {
    u8 pad0[0x10]; V4E3 pos; u8 pad20[0x30]; V4E3 x50; u8 pad60[0x10]; s32 x70; u8 pad74[0x5C]; V4E3 xd0;
    u8 padE0[0x64]; WkE3 *p144;
} ChrE3;

extern V4E3 D_00575060[2];
extern V4E3 D_00575030[2];
extern ChrE3 *D_0035BD40[3];
extern V4E3 D_0035BD20[2];

extern void func_00162878(V4E3 *, V4E3 *, V4E3 *);
extern f32 func_001629b0(V4E3 *, V4E3 *);
extern f32 func_00162c20(V4E3 *);
extern void func_0016e1f0(s32);
extern void func_00267518(V4E3 *, V4E3 *, V4E3 *);
extern void func_00267560(V4E3 *, V4E3 *, f32);

static inline s32 inl_k(void) {
    if (D_0035BD40[0]->x70 == 13 || D_0035BD40[0]->x70 == 10) return 1;
    return 0;
}

void func_0016e3f8(void) {
    V4E3 v0, v1, a1, a2, b1, b2;
    WkE3 *w1 = 0;
    WkE3 *w2 = 0;
    f32 d1, d2, d3, d4;
    s32 k;
    func_002675a8(&D_00575060[0], &D_00575030[0]);
    func_002675a8(&D_00575060[1], &D_00575030[1]);
    func_00162878(&v0, &D_0035BD40[0]->xd0, &D_0035BD20[0]);
    func_00162878(&v1, &D_0035BD40[0]->xd0, &D_0035BD20[1]);
    d1 = d2 = d3 = d4 = 0.0f;
    if (D_0035BD40[1] != 0 && (w1 = D_0035BD40[1]->p144) != 0) {
        w1->w38 &= ~0x80000ULL;
        func_00267530(&w1->vE0, &D_0035BD40[0]->pos, &D_0035BD40[1]->pos);
        w1->fA4 = w1->vE0.y;
        func_002675a8(&w1->vF0, &w1->vE0);
        w1->vF0.y = 0.0f;
        w1->vE0.w = func_00162c20(&w1->vE0);
        w1->vF0.w = func_00162c20(&w1->vF0);
        func_00267560(&a1, &v0, w1->p4->f8);
        func_00267518(&a1, &a1, &D_0035BD40[0]->pos);
        func_00267560(&a2, &v1, w1->p4->f8);
        func_00267518(&a2, &a2, &D_0035BD40[0]->pos);
        d1 = func_001629b0(&a1, &D_0035BD40[1]->pos);
        d2 = func_001629b0(&a2, &D_0035BD40[1]->pos);
    }
    if (D_0035BD40[2] != 0 && (w2 = D_0035BD40[2]->p144) != 0) {
        w2->w38 &= ~0x80000ULL;
        func_00267530(&w2->vE0, &D_0035BD40[0]->pos, &D_0035BD40[2]->pos);
        w2->fA4 = w2->vE0.y;
        func_002675a8(&w2->vF0, &w2->vE0);
        w2->vF0.y = 0.0f;
        w2->vE0.w = func_00162c20(&w2->vE0);
        w2->vF0.w = func_00162c20(&w2->vF0);
        func_00267560(&b1, &v0, w2->p4->f8);
        func_00267518(&b1, &b1, &D_0035BD40[0]->pos);
        func_00267560(&b2, &v1, w2->p4->f8);
        func_00267518(&b2, &b2, &D_0035BD40[0]->pos);
        d3 = func_001629b0(&b1, &D_0035BD40[2]->pos);
        d4 = func_001629b0(&b2, &D_0035BD40[2]->pos);
    }
    if (w1 != 0) {
        if (w2 != 0) {
            if (d1 <= d2 && d1 <= d3 && d1 <= d4) {
                func_002675a8(&D_00575030[0], &a1);
                d3 = func_001629b0(&b1, &D_00575030[0]);
                if (d3 <= func_001629b0(&b2, &D_00575030[0])) func_002675a8(&D_00575030[1], &b2);
                else func_002675a8(&D_00575030[1], &b1);
            } else if (d2 <= d1 && d2 <= d3 && d2 <= d4) {
                func_002675a8(&D_00575030[0], &a2);
                d3 = func_001629b0(&b1, &D_00575030[0]);
                if (d3 <= func_001629b0(&b2, &D_00575030[0])) func_002675a8(&D_00575030[1], &b2);
                else func_002675a8(&D_00575030[1], &b1);
            } else if (d3 <= d1 && d3 <= d2 && d3 <= d4) {
                func_002675a8(&D_00575030[1], &b1);
                d1 = func_001629b0(&a1, &D_00575030[1]);
                if (d1 <= func_001629b0(&a2, &D_00575030[1])) func_002675a8(&D_00575030[0], &a2);
                else func_002675a8(&D_00575030[0], &a1);
            } else if (d4 <= d1 && d4 <= d2 && d4 <= d3) {
                func_002675a8(&D_00575030[1], &b2);
                d1 = func_001629b0(&a1, &D_00575030[1]);
                if (d1 <= func_001629b0(&a2, &D_00575030[1])) func_002675a8(&D_00575030[0], &a2);
                else func_002675a8(&D_00575030[0], &a1);
            }
            if (inl_k()) {
                if (w1->vE0.w < w2->vE0.w) {
                    w1->w38 |= 0x80000ULL;
                    func_002675a8(&D_00575030[0], &D_0035BD40[0]->x50);
                } else {
                    w2->w38 |= 0x80000ULL;
                    func_002675a8(&D_00575030[1], &D_0035BD40[0]->x50);
                }
            }
            func_0016e1f0(1);
            func_0016e1f0(2);
        } else {
            if (d1 <= d2) func_002675a8(&D_00575030[0], &a1);
            else func_002675a8(&D_00575030[0], &a2);
            if (inl_k()) {
                w1->w38 |= 0x80000ULL;
                func_002675a8(&D_00575030[0], &D_0035BD40[0]->x50);
            }
            func_0016e1f0(1);
        }
    } else if (w2 != 0) {
        if (d3 <= d4) func_002675a8(&D_00575030[1], &b1);
        else func_002675a8(&D_00575030[1], &b2);
        if (inl_k()) {
            w2->w38 |= 0x80000ULL;
            func_002675a8(&D_00575030[1], &D_0035BD40[0]->x50);
        }
        func_0016e1f0(2);
    }
}

/* ---- func_001707d0 ---- */
typedef struct { f32 x, y, z, w; } V4D0;
typedef struct { u8 pad[0x18]; f32 f18; } Sub130D0;
typedef struct { u8 pad[0x44]; s32 w44; s32 w48; } Sub6CD0;
typedef struct { u8 pad[1]; u8 b1; } SubB1;
typedef struct { u8 pad[4]; s32 w4; } Sub74D0;
typedef union { u64 w; struct { u32 lo; u8 m; } c; } Bf80D0;
typedef struct WkD0 {
    u8 pad0[8]; SubB1 *p8; SubB1 *pC; u8 pad10[0x10];
    f32 f20, f24, f28, f2C, f30, f34; u32 b0:1, b1:1, b2:1, b3:4, b7:1, b8:1, b9:1, b10:2, b12:1, b13:1, b14:2, b16:1, b17:1, b18:1, b19:1, b20:1, b21:11; u32 w3C; u8 pad40[8];
    void (*p48)(void *, struct WkD0 *); s32 w4C; u8 pad50[8]; s32 w58; s32 w5C; u8 pad60[4]; f32 f64; f32 f68;
    u8 pad6C[8]; Sub74D0 *p74; u8 pad78[8]; Bf80D0 w80; u8 pad88[0x10]; s32 w98; u8 pad9C[8]; f32 fA4;
    u8 padA8[0x28]; V4D0 vD0; u8 padE0[0x20]; V4D0 v100; V4D0 v110; V4D0 v120; f32 h1[5]; f32 h2[5];
} WkD0;
typedef struct {
    u8 pad0[0x10]; V4D0 x10; u8 pad20[0xC]; s32 x2C; u8 pad30[0x3C]; Sub6CD0 *p6C; s32 x70; u8 pad74[0x1C];
    u64 x90; u8 pad98[0x98]; Sub130D0 *p130; u8 pad134[0x10]; WkD0 *p144; u8 pad148[0x1C]; s32 x164;
    u8 pad168[0x158]; f32 f2C0, f2C4; u8 pad2C8[0xF8]; V4D0 x3C0;
} ObjD0;

extern V4D0 D_002C58B0;

extern s32 func_001375f0(ObjD0 *);
extern void func_0013f0c0(ObjD0 *, u8 *, V4D0 *);
extern u32 func_001627e8(s32);
extern void func_001689d0(ObjD0 *, WkD0 *);
extern void func_001693c8(ObjD0 *, WkD0 *);
extern void func_00169f28(ObjD0 *, WkD0 *);
extern s32 func_0016a3f8(ObjD0 *, WkD0 *);
extern s32 func_0016abc0(ObjD0 *, WkD0 *);
extern void func_0016b1f0(ObjD0 *, WkD0 *);
extern void func_0016f3d0(ObjD0 *, WkD0 *);
extern s32 func_0016f8b8(ObjD0 *, WkD0 *);
extern void func_0016fd98(ObjD0 *, WkD0 *);
extern void func_00170170(ObjD0 *, WkD0 *);
extern void func_001705c0(ObjD0 *, WkD0 *);
extern void func_002673b8(V4D0 *, V4D0 *);
extern void func_00267e90(V4D0 *, V4D0 *, f32);

static inline s32 inl_rng(ObjD0 *o, WkD0 *w) {
    if (o->x164 < 13) { if (o->x164 >= 3) return 1; }
    return o->x164 == w->w4C;
}


void func_001707d0(ObjD0 *o, V4D0 *out) {
    WkD0 *w = o->p144;
    V4D0 t;
    f32 a, b, s1, s2;
    SubB1 *p;
    u32 n;
    s32 i;
    if (w->f30 <= 0.0f) {
        w->f20 = w->f28 = w->f2C = 0.0f;
        w->f24 = -o->f2C4 * 0.5f;
        w->f34 = o->p130->f18;
        a = o->f2C0;
        b = o->f2C4;
        if (a <= 0.0f && b <= 0.0f) w->f30 = 0.0f;
        else if (b <= 0.0f) w->f30 = a;
        else if (a <= 0.0f) w->f30 = b;
        else {
            if (!(a < b)) a = b;
            w->f30 = a;
        }
    }
    if (o->x70 != 2) w->w5C = 0;
    w->f68 -= D_002BBDFC;
    func_002675a8(&w->v110, &w->v120);
    w->b9 = 0;
    w->b12 = 0;
    w->b20 = 0;
    func_002675a8(&w->v120, &D_002C58B0);
    w->w80.c.m = 0;
    w->w80.w |= 0x200000000000000ULL;
    if ((u32)(o->x164 - 71) < 37) w->b1 = 0;
    if (!inl_rng(o, w)) w->b18 = 0;
    func_00267530(&t, &o->x10, &w->v100);
    func_002673b8(&t, &t);
    if (!w->b7 && (func_00267390(&w->v110, &t) < 0.5f || o->x90 != 0)) w->w58++;
    if (fabsf(w->fA4) > 600.0f) w->w58 += 20;
    func_001705c0(o, w);
    if ((D_002C5958 >> 16) & 1) {
        w->b2 = 0;
    } else {
        if (w->f64 > 0.0f) p = w->pC;
        else p = w->p8;
        n = o->p6C->w44 * p->b1;

        if (w->b16) {
            n *= 2;
            w->b16 = 0;
        }
        if (o->p6C->w48 * (func_001627e8(0x1000) >> 4) < n) w->b2 = 1;
        else w->b2 = 0;
    }
    if (!func_001375f0(o)) {
        if (w->p48) w->p48(o, w);
    } else {
        w->p48 = 0;
        if (D_002C5958 & 1) {
            w->b13 = 1;
            if (!(w->w98 = func_0016f8b8(o, w)) || !func_0016abc0(o, w)) {
                func_0016fd98(o, w);
                if (!func_0016a3f8(o, w)) func_0016b1f0(o, w);
            }
        } else {
            if (w->b13) func_0016f3d0(o, w);
            func_001693c8(o, w);
        }
    }
    if (!w->b12) {
        f32 c, d;
        s1 = s2 = 0.0f;
        for (i = 4; i > 0; i--) {
            s1 += (w->h1[i] = w->h1[i - 1]);
            s2 += (w->h2[i] = w->h2[i - 1]);
        }
        c = w->v120.y;
        d = w->v120.w;
        s1 += c;
        s2 += d;
        w->h1[0] = c;
        w->h2[0] = d;
        w->v120.y = s1 / 5.0f;
        w->v120.w = s2 / 5.0f;
        func_00170170(o, w);
    }
    if (func_00267390(&w->v120, &w->v120) != 0.0f) func_002675a8(out, &w->v120);
    if (w->w80.c.m) {
        out->w = 0.0f;
        if (w->w80.c.m != 1) func_0013f0c0(o, &w->w80.c.m, out);
        else if (w->p74->w4 & 8) {
            func_002675a8(out, &w->vD0);
            out->w = 8.0f;
        }
    } else {
        func_00169f28(o, w);
    }
    func_001689d0(o, w);
    if (o->x70 == 8 && w->b9) {
        func_00267e90(&o->x3C0, out, out->w);
        o->x3C0.y = out->y;
        o->x2C = 0;

    }
    func_002675a8(&w->v100, &o->x10);
}
