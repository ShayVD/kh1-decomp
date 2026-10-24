/* The party members' AI, without strict aliasing (docs/modules.md "Session
 * 51"): func_00170400 starts a member's AI (its work area, its party slot
 * in D_002E26A0, the kind's setup from D_0035BC80), func_001705c0 and
 * func_001707d0 (steering toward the leader), the action helpers
 * (func_00171118 ... func_00171e50: targets, distances, a free slot of
 * D_00574FC0), and the action handlers of the kinds' tables (func_00172028
 * ... func_00174ca8).  partyai.nostrict_nosib.c has func_00170170 (turn the
 * stick input into a move for some states); partyai.c has the rest.  Each
 * section names the file its code came from.  Read from the code, not
 * proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/bss_0057.h"
#include "data/pieces/D_0035BD40.h"
#include "data/types/nostrict_text_00160000_h60_p.h"
#include "data/types/nostrict_text_00160000_h60.h"
#include "data/pieces/D_002C5C60.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002E31B0.h"
#include "data/types/nostrict_text_00160000_c04.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_00351BC8.h"
#include "data/types/nostrict_text_00170000_h61.h"

/* func_00170400 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { s32 a, b; } P870;
typedef struct { u8 pad[0xC]; void *pC; } Ent70;
typedef struct {
    s32 w0; void *p4; void *p8; void *pC; s32 w10; s32 w14; s32 w18; Ent70 *p1C; u8 pad20[0x240];
} Wk70;
typedef struct { u8 pad[0x30]; u64 w30; } Sub148;
typedef struct { u8 pad[0x2C]; s32 w2C; } Sub14C;
typedef struct { u8 pad[0x4C]; u16 h4C; } Sub130;
typedef struct Actor_70400 { u8 pad[0x130]; Sub130 *p130; u8 pad134[0x10]; Wk70 *p144; Sub148 *p148; Sub14C *p14C; } Obj70;
typedef struct { s32 o0, o4, o8, oC, n; s32 ofs[1]; } Tbl70;
extern Prm35AE80 D_0035AE80;
/* the setup function of each kind of party member (partyai.c), by o->p130->h4C (moved from h60) */
void func_00172010();
void func_00172d90();
void func_00173740();
void func_00173ad8();
void func_00173ea8();
void func_00174398();
void func_00174950();
void func_00174d98();
void (*D_0035BC80[0xa])(Obj70 *, Wk70 *) ALIGNED(16) = {
    0, (void *)func_00172010, (void *)func_00172d90, (void *)func_00173740,
    0, (void *)func_00173ad8, (void *)func_00173ea8, (void *)func_00174398,
    (void *)func_00174950, (void *)func_00174d98,
};
Wk70 *func_00121e28(s32, Wk70 **);
void func_0016f7b8(void);
void *memset(void *, s32, u32);
void func_00170400(Obj70 *o) {
    u32 k;
    Wk70 *w;
    s32 i, n;
    Tbl70 *t;
    u8 *base;
    o->p148->w30 &= ~0x100000000ULL;
    o->p14C->w2C = 0;
    k = o->p130->h4C;
    w = func_00121e28(608, &o->p144);
    memset(w, 0, 608);
    w->w0 = -1;
    for (i = 0; i < 3; i++) {
        if (D_002E26A0[i] == o) {
            w->w0 = i;
            break;
        }
    }
    if (D_0035BC80[k] != 0) D_0035BC80[k](o, w);
    base = (u8 *)&D_0035AE80;
    if (w->p1C == 0) w->w18 = 0;
    t = (Tbl70 *)(((s32 *)base)[k] + (s32)base);
    if (!t->o0) w->p4 = base + 40;
    else w->p4 = (void *)(t->o0 + (s32)base);
    if (!t->o4) w->p8 = base + 64;
    else w->p8 = (void *)((s32)base + t->o4);
    if (!t->o8) w->pC = base + 92;
    else w->pC = (void *)((s32)base + t->o8);
    if (t->oC == 0) {
        w->w10 = 0;
        w->w14 = 0;
    } else {
        *(P870 *)&w->w10 = *(P870 *)(base + t->oC);
        w->w14 = (s32)base + w->w14;
    }
    {
        s32 *q = t->ofs;
        n = t->n;
        for (i = 0; i < n; i++) w->p1C[i].pC = (void *)((s32)base + q[i]);
    }
    func_0016f7b8();
}

/* func_001705c0 (from hand/nostrict/text_00160000_h60.c). */
typedef struct {
    u8 pad0[0x38]; u64 w38; u8 pad40[8]; s32 w48; u8 pad4c[0x0C]; s32 w58; u8 pad5c[8]; f32 f64; u8 pad68[0x28];
    void *p90; s32 w94;
} Wk705;
extern f32 D_002BBDFC;
extern P870 D_00575080;
void func_00157a30(void *, s32, void *);
void func_001586a8(s32);
void func_001705c0(void *e, Wk705 *w) {
    f32 f;
    if ((s32)((s64)(w->w38 << 29) >> 32) & 1) {
        f32 t;
        func_001586a8(20);
        t = D_0035AE80.fBC;
        w->w38 &= ~8;
        w->f64 = t;
        *(P870 *)&w->p90 = D_00575080;
        if (!((s32)((s64)(w->w38 << 27) >> 32) & 1)) {
            w->w38 |= 0x20;
            if ((*(s32 *)&D_002E31B0) != 0) func_00157a30(e, 21, 0);
            else func_00157a30(e, 22, D_0035BD40.chr[0]);
        }
        if (w->p90 == 0) {
            w->w38 |= 1;
            w->w94 = -1;
            w->w38 &= ~0x800;
            w->w38 &= ~0x10;
            w->p90 = 0;
        } else {
            w->w38 |= 0x800;
            w->w38 |= 0x10;
        }
        w->w58 += 20;
    } else {
        f = w->f64;
        if (f > 0.0f) {
            f = w->f64 = f - D_002BBDFC;
        }
        if (f < 0.0f) {
            w->f64 = 0.0f;
            f = 0.0f;
        }
        if ((double)w->f64 < (double)D_0035AE80.fBC - 90.0) w->w38 &= ~0x20;
        if (f <= 0.0f) w->w38 &= ~0x10;
        if (f <= 0.0f && w->w48 == 0) w->w38 &= ~0x800;
    }
}

/* func_001707d0 (from hand/nostrict/text_00160000_c04.c). */
extern u32 D_002C5958;
typedef FVec4 V4D0;
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
static inline s32 inl_rng(ObjD0 *o, WkD0 *w) {
    if (o->x164 < 13) { if (o->x164 >= 3) return 1; }
    return o->x164 == w->w4C;
}
#define func_001705c0 ((void (*)(ObjD0 *, WkD0 *)) func_001705c0)
/* ---- func_001707d0 ---- */
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
    PlatVu0CopyVector(&w->v110, &w->v120);
    w->b9 = 0;
    w->b12 = 0;
    w->b20 = 0;
    PlatVu0CopyVector(&w->v120, &D_002C58B0);
    w->w80.c.m = 0;
    w->w80.w |= 0x200000000000000ULL;
    if ((u32)(o->x164 - 71) < 37) w->b1 = 0;
    if (!inl_rng(o, w)) w->b18 = 0;
    PlatVu0SubVector(&t, &o->x10, &w->v100);
    PlatVu0Normalize(&t, &t);
    if (!w->b7 && (PlatVu0InnerProduct(&w->v110, &t) < 0.5f || o->x90 != 0)) w->w58++;
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
    if (PlatVu0InnerProduct(&w->v120, &w->v120) != 0.0f) PlatVu0CopyVector(out, &w->v120);
    if (w->w80.c.m) {
        out->w = 0.0f;
        if (w->w80.c.m != 1) func_0013f0c0(o, &w->w80.c.m, out);
        else if (w->p74->w4 & 8) {
            PlatVu0CopyVector(out, &w->vD0);
            out->w = 8.0f;
        }
    } else {
        func_00169f28(o, w);
    }
    func_001689d0(o, w);
    if (o->x70 == 8 && w->b9) {
        PlatVu0ScaleVectorXYZ(&o->x3C0, out, out->w);
        o->x3C0.y = out->y;
        o->x2C = 0;

    }
    PlatVu0CopyVector(&w->v100, &o->x10);
}
#undef func_001705c0

/* func_00171118 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_71118 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40;
extern s32 func_00122ff8(void *); /* an actor (D_002E26A0[k] or an ObjBD40) */
extern s32 func_0012f040(ObjBD40 *, s32);
extern s32 func_0012ee70(ObjBD40 *, s32);
s32 func_00171118(ObjBD40 *t, s32 i) {
    s32 r = 0;
    if (!(D_002C5958 & 1)) return r;
    if (t == 0) return r;
    if (func_00122ff8(t)) {
        if (i >= 0) return func_0012f040(t, i);
        for (i = -1; (i = func_0012ee70(t, i)) >= 0;) {
            if (func_0012f040(t, i)) return 1;
        }
    }
    return 0;
}

/* func_001711d0 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x350]; u64 f370; } Ent370;
typedef struct { Ent370 *tgt; s32 part; } Lock71;
extern f32 D_0048EA68;
Ent370 *func_00123158(void *, Ent370 *);
s32 func_00123368(Ent370 *);
f32 func_0012ec60(void *, s32, f32 *);
s32 func_00141200(void *, s32);
#define func_0012ee70 ((s32 (*)(void *, s32)) func_0012ee70)
#define func_0012f040 ((s32 (*)(void *, s32)) func_0012f040)
void func_001711d0(Ent370 *self, Lock71 *out, f32 r) {
    f32 a[4];
    f32 b[4];
    Ent370 *p;
    s32 i;
    f32 best, d;
    out->part = -1;
    out->tgt = 0;
    if (r <= 0.0f) best = D_0048EA68;
    else best = r * r;
    p = 0;
    while ((p = func_00123158(self, p)) != 0) {
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        if (func_00141200(p, 0)) continue;
        for (i = -1; (i = func_0012ee70(p, i)) >= 0;) {
            if (!func_0012f040(p, i)) continue;
            func_0012ec60(p, i, a);
            PlatVu0SubVector(b, a, self->pos);
            d = PlatVu0InnerProduct(b, b);
            if (d < best) {
                out->tgt = p;
                best = d;
                out->part = i;
            }
        }
    }
}
#undef func_0012ee70
#undef func_0012f040

/* func_00171320 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_71320 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_71320;
typedef struct { u8 pad[0x10]; f32 pos[4]; } ObjPos;
extern f32 D_0048EA6C;
#define func_0012f040 ((s32 (*)(ObjBD40_71320 *, s32)) func_0012f040)
#define func_0012ee70 ((s32 (*)(ObjBD40_71320 *, s32)) func_0012ee70)
#define func_0012ec60 ((f32 (*)(ObjBD40_71320 *, s32, f32 *)) func_0012ec60)
s32 func_00171320(ObjPos *self, ObjBD40_71320 *t) {
    f32 a[4];
    f32 b[4];
    s32 i, best;
    f32 bd, d;
    best = -1;
    if (t != 0) {
        bd = D_0048EA6C;
        for (i = -1; (i = func_0012ee70(t, i)) >= 0;) {
            if (func_0012f040(t, i)) {
                func_0012ec60(t, i, a);
                PlatVu0SubVector(b, a, self->pos);
                d = PlatVu0InnerProduct(b, b);
                if (d < bd) {
                    bd = d;
                    best = i;
                }
            }
        }
    }
    return best;
}
#undef func_0012f040
#undef func_0012ee70
#undef func_0012ec60

/* func_001713f8 (from hand/nostrict/text_00160000_s6_09.c). */
typedef struct { u8 pad[0x4C]; u16 h4C; } Mdl13;
typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0xBC]; Mdl13 *p130; } Act13;
s32 func_001713f8(Act13 *a) {
    if ((u16)(a->p130->h4C - 1) >= 2) return 0;
    if (a->w70 != 0 && a->w70 != 2) return 0;
    if (D_002E27C8.b8) return 1;
    if (D_002E27C8.b7) return 1;
    return 0;
}

/* func_001714f0 (from hand/nostrict/text_00160000_h37.c). */
typedef struct { u8 pad[0x21]; u8 n; u8 ids[1]; } ListC8;
typedef struct { u8 pad[0xC8]; ListC8 *pC8; } Sub6Cx;
typedef struct { u8 pad[0x6C]; Sub6Cx *p6C; s32 w70; } Obj14F;
extern s32 func_0012ca98(Obj14F *);
s32 func_001714f0(Obj14F *o, s32 id) {
    ListC8 *l;
    s32 i;
    if (!func_0012ca98(o)) return 0;
    switch (o->w70) {
    case 0:
    case 8:
    case 24:
        l = o->p6C->pC8;
        for (i = 0; i < l->n; i++) {
            if (l->ids[i] == id) return 1;
        }
        break;
    }
    return 0;

}

/* func_001715b0 (from hand/nostrict/text_00160000_h37.c). */
s32 func_001715b0(void *grp, Ent370 *self, f32 r) {
    f32 v[4];
    Ent370 *p = 0;
    s32 n = 0;
    f32 r2 = r * r;
    while ((p = func_00123158(grp, p)) != 0) {
        if (p == self) continue;
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        PlatVu0SubVector(v, p->pos, self->pos);
        if (PlatVu0InnerProduct(v, v) < r2) n++;
    }
    return n;
}

/* func_00171680 (from hand/nostrict/text_00160000_h37.c). */
extern f32 func_00162c20(f32 *);
s32 func_00171680(Ent370 *self, Ent370 *tgt) {
    f32 dir[4];
    f32 v[4];
    Ent370 *p = 0;
    s32 n = 0;
    f32 c;
    PlatVu0SubVector(dir, tgt->pos, self->pos);
    c = 0.7f;
    func_00162c20(dir);
    while ((p = func_00123158(self, p)) != 0) {
        if (p == tgt) continue;
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        PlatVu0SubVector(v, p->pos, self->pos);
        func_00162c20(v);
        if (c < PlatVu0InnerProduct(v, dir)) n++;
    }
    return n;
}

/* func_00171790 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_71790 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_71790;
typedef struct {
    u8 pad[0x38]; u64 w38; u8 pad40[0x50];
    ObjBD40_71790 *tgt; s32 part; s32 w98; f32 f9C; f32 fA0; u8 padA4[0xC];
    f32 vB0[4]; f32 vC0[3]; f32 fCC; f32 vD0[3]; f32 fDC;
} Lock90;
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x50]; s32 w70; u8 pad74[0x250]; f32 f2C4; } Obj2C4;
extern void func_0016fc60(Obj2C4 *, Lock90 *);
#define func_0012ec60 ((f32 (*)(ObjBD40_71790 *, s32, f32 *)) func_0012ec60)
void func_00171790(Obj2C4 *self, Lock90 *l) {
    func_0016fc60(self, l);
    if (l->tgt != 0 && l->part >= 0) {
        l->f9C = func_0012ec60(l->tgt, l->part, l->vB0);
        if (((s32)((s64)(l->w38 << 12) >> 32) & 1) || self->w70 == 8 || self->w70 == 24 || self->w70 == 25)
            l->vB0[1] += self->f2C4;
        PlatVu0SubVector(l->vC0, l->vB0, self->pos);
        PlatVu0CopyVector(l->vD0, l->vC0);
        l->fA0 = l->vD0[1];
        l->vD0[1] = 0;
        l->fCC = func_00162c20(l->vC0);
        l->fDC = func_00162c20(l->vD0);
        return;
    }
    l->tgt = 0;
    l->part = -1;
}
#undef func_0012ec60

/* func_00171970 (from hand/nostrict/text_00170000_s7_w6.c). */
typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0xF0]; s32 w164; } Act19;
typedef struct { u8 pad[0x4C]; s32 w4C; } Tgt19;
/* func_00171970 (session 7, w6): `ok` shared by cases 0 and 8 at function
 * scope (gets a1, so t moves to a3), its own `ok2` in case 24; the n2 copy
 * keeps the two slti range tests; each case ends `if (m & K) return 0;`
 * so jump2 cross-jumps the tail. Matches in strict mode too. */
s32 func_00171970(Act19 *a, Tgt19 *t, s32 m) {
    s32 ok, n, n2;
    switch (a->w70) {
    case 0:
        n = a->w164; n2 = n;
        if (n < 3 && n2 >= 0) ok = 1; else ok = (n == t->w4C);
        if (!ok) return 0;
        if (m & 6) return 0;
        break;
    case 8:
        n = a->w164; n2 = n;
        if (n < 124 && n2 >= 117) ok = 1; else ok = (n == t->w4C);
        if (!ok) return 0;
        if (m & 3) return 0;
        break;
    case 24: {
        s32 ok2;
        n = a->w164; n2 = n;
        if (n2 >= 0 && (n < 3 || (n < 131 && n2 >= 124))) ok2 = 1; else ok2 = (n == t->w4C);
        if (!ok2) return 0;
        if (m & 5) return 0;
        break;
    }
    default:
        return 0;
    }
    return 1;
}

/* func_00171b80 (from hand/nostrict/text_00160000_h37.c). */
typedef struct { u8 pad[0xB4]; void *cb; void **slot; } Sub2C;
typedef struct { u8 pad[0x2C]; Sub2C *p2C; } Sub14C_71b80;
typedef struct { u8 pad[0x14C]; Sub14C_71b80 *p14C; } Obj14C;
typedef struct { u8 pad[0x3C]; void **slot; Sub2C *p40; } Arg3C;
extern void *D_00574FC0[20];
extern s32 func_0013dc10(Obj14C *, s32);
extern void func_00171f38(void);
s32 func_00171b80(Obj14C *o, Arg3C *l, s32 k) {
    s32 i = D_00574FB8;
    s32 n = 0;
    s32 r;
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

/* func_00171c80 (from hand/nostrict/text_00160000_h37.c). */
typedef struct { u8 pad[4]; u32 flags; } Sub74;
typedef struct {
    u8 pad[0x10]; s32 w10; s32 w14; u8 pad18[0x20]; u64 w38; u8 pad40[8];
    void *cb48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[8]; Sub74 *p74; u8 pad78[0x18]; s32 w90;
} Wk171;
typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0x35C]; s32 w3D0; } Obj3D0;
extern void func_00130340(Obj3D0 *, s32, f32);
extern void func_0016df30(void);
s32 func_00171c80(Obj3D0 *o, Wk171 *w, s32 unused, s32 mode) {
    switch (mode) {
    case 0:
        if (w->w10 <= 0 || !w->w14) return 0;
        if (o->w70 != 0) return 0;
        if (w->w90 == 0) return 0;
        if (w->p74 == 0) return 0;
        if (w->p74->flags & 0xC00) return 0;
        goto ret1;
    case 1:
        return 0;
    case 2:
        w->w4C = 4;
        o->w3D0 = 0;
        func_00130340(o, 0x1000004, 0.0f);
        w->w38 |= 0x8000;
        w->f68 = 4.0f;
        w->cb48 = func_0016df30;
    ret1:
        return 1;
    }
    return 1;
}

/* func_00171d80 (from hand/nostrict/text_00160000_h37.c). */
typedef struct { u8 pad[0x18]; f32 f18; } Sub130x;
typedef struct { u8 pad[0x130]; Sub130x *p130; } Obj130x;
typedef struct { u8 pad[0x38]; u64 w38; u8 pad40[0x18]; s32 w58; u8 pad5C[4]; s32 w60; u8 pad64[0xC]; f32 f70; } Wk70_71d80;
extern s32 D_002E27A8;
extern void func_00124060(Obj130x *, s32);
extern void func_00135800(Obj130x *, f32, f32);
extern void func_001373f8(Obj130x *, f32);
void func_00171d80(Obj130x *o, Wk70_71d80 *w, s32 k) {
    func_00124060(o, k);
    func_00135800(o, 0.0f, 0.0f);
    func_00135800(o, 1.0f, 30.0f);
    o->p130->f18 = 1.0f;
    func_001373f8(o, 30.0f);
    w->w38 |= 0x40;
    w->w58 = 0;
    w->w60 = 0;
    if (D_002E27A8 == 2) w->f70 = 600.0f;
    else w->f70 = 240.0f;
}

/* func_00171e50 (from hand/nostrict/text_00160000_s6_09.c). */
typedef struct { s32 w0; u8 pad[0x94]; void *p98; } Wk1E;
void func_00171e50(void *e, Wk1E *w, void *t) {
    if (t != 0 && e != t && w->p98 == t) do { func_00157a30(e, 26, t); } while (0);
}

/* func_00172028 (from hand/nostrict/text_00160000_s6_09.c). */
typedef struct { s32 x0; u8 pad4[0x20]; f32 x24; } Prm20;
typedef struct { u8 pad[0xc]; Prm20 *xc; } P170;
typedef struct {
    u8 pad0[0x4c]; s32 x4c;
    u8 pad50[0x164 - 0x50]; f32 x164;
    u8 pad168[0x170 - 0x168]; P170 *x170; s32 x174; s32 x178;
} Ob20;
typedef struct { u8 pad0[0x14]; f32 x14; u8 pad18[0x144 - 0x18]; Ob20 *x144; } Wk20;
typedef struct { u8 pad[0xc]; void *xc; } Ret20;
typedef struct { u8 pad[4]; s32 x4; } R13d;
typedef struct { u8 pad[0x30]; s32 x30; } R147;
extern u8 D_0035BE40[];
Ret20 *func_00130578(Wk20 *, s32, f32);
void func_001731f8();
void func_00148a40(Wk20 *, s32);
void func_00170f90(void);
void func_00170fa8(Wk20 *, Ob20 *, void *, void *, f32);
R13d *func_0013dbe0(Wk20 *, s32);
R147 *func_001477c8(s32);
void func_001412f8(Wk20 *, s32);
#define func_00130340 ((s32 (*)(Wk20 *, s32, f32)) func_00130340)
void func_00172028(Wk20 *w) {
    Ob20 *o = w->x144;
    Prm20 *p = o->x170->xc;
    f32 k = 8.0f;
    func_00130340(w, 0x10000CE, k);
    o->x4c = 206;
    o->x178 = 0x40000006;
    o->x174 = 0;
    o->x164 = w->x14 - p->x24;
    func_00130578(w, 0x40000006, k)->xc = func_001731f8;
    func_00148a40(w, 0);
    func_00170fa8(w, o, func_00170f90, D_0035BE40, 30.0f);
    func_001412f8(w, func_001477c8(func_0013dbe0(w, p->x0)->x4)->x30);
}
#undef func_00130340

/* func_00172118 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { s32 w0; u8 pad4[0x10]; f32 f14, f18, f1C, f20, f24; } Sub170C;
typedef struct { u8 pad[0xC]; Sub170C *pC; } Sub170;
typedef struct {
    u8 pad[0x38]; u64 w38; u8 pad40[8]; void *w48; s32 w4C; u8 pad50[0x40]; s32 w90; u8 pad94[0xD0];
    f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178;
} Wk172;
typedef struct { u8 pad[0x14]; f32 f14; } Obj172;
typedef struct { u8 pad[0xC]; void *cb; } Task0C;
typedef struct { u8 pad[0x30]; s32 w30; } Res30;
typedef struct { u8 pad[4]; s32 w4; } Res04;
s32 func_0016b670(Obj172 *, Wk172 *, Sub170 *, s32);
void func_00170f50(Obj172 *, Wk172 *, void *, s32, s32);
s32 func_00171a88(void *, void *, s32);
s32 func_001734f8();
void func_00173610();
#define func_00130340 ((void (*)(Obj172 *, s32, f32)) func_00130340)
#define func_00130578 ((Task0C *(*)(Obj172 *, s32, f32)) func_00130578)
#define func_0013dbe0 ((Res04 *(*)(Obj172 *, s32)) func_0013dbe0)
#define func_001412f8 ((void (*)(Obj172 *, s32)) func_001412f8)
#define func_001477c8 ((Res30 *(*)(s32)) func_001477c8)
#define func_00148a40 ((void (*)(void *, s32)) func_00148a40)
#define func_00170f90 ((s32 (*)()) func_00170f90)
#define func_00170fa8 ((void (*)(void *, void *, void *, void *, f32)) func_00170fa8)
s32 func_00172118(Obj172 *o, Wk172 *w, Sub170 *k, s32 mode) {
    Sub170C *c = k->pC;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 31)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (w->w90 == 0) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        w->w38 |= 0x800;
        func_00130340(o, 0x10000CE, 8.0f);
        w->w4C = 206;
        w->p170 = k;
        w->w178 = 0x40000075;
        w->w174 = 0;
        w->f164 = o->f14 - c->f24;
        func_00130578(o, 0x40000075, 8.0f)->cb = func_001731f8;
        func_00148a40(o, 0);
        func_00170fa8(o, w, func_00170f90, D_0035BE40, 30.0f);
        func_001412f8(o, func_001477c8(func_0013dbe0(o, c->w0)->w4)->w30);
        w->w48 = func_00173610;
        func_00170f50(o, w, func_001734f8, 3, 0);
        return 1;
    }
    return 1;
}
#undef func_00130340
#undef func_00130578
#undef func_0013dbe0
#undef func_001412f8
#undef func_001477c8
#undef func_00148a40
#undef func_00170f90
#undef func_00170fa8

/* func_001722e8 (from hand/nostrict/text_00160000_h60.c). */
typedef Chr_35BD40 Chr;
typedef struct {
    u8 pad[0x80];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    Chr *p88; s32 w8C; u8 pad90[8]; Chr *p98;
} Wk172_22e8;
void func_00141540(Chr *, s32);
Chr *func_00171078(Chr *, Wk172_22e8 *);
s32 func_001710d8(Chr *, s32);
void func_00173718();
#define func_00148a40 ((void (*)(void *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(void *, void *, void *, void *, f32)) func_00170fa8)
#define func_00171e50 ((void (*)(Chr *, Wk172_22e8 *, Chr *)) func_00171e50)
s32 func_001722e8(Chr *o, Wk172_22e8 *w, s32 unused, s32 mode) {
    Chr *t = 0;
    Chr *q;
    if (w->p98 != 0 && w->p98 != o && func_001710d8(w->p98, 84)) {
        t = w->p98;
    } else if (D_0035BD40.chr[0] != 0 && func_001710d8(D_0035BD40.chr[0], 84)) {
        t = D_0035BD40.chr[0];
    } else {
        q = func_00171078(o, w);
        if (q != 0) t = func_001710d8(q, 84) ? q : 0;
    }
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (t == 0) return 0;
        if (o->p6C->w44 < 2) return 0;
        if (!func_00171a88(o, w, 32)) return 0;
        break;
    case 2:
        func_00148a40(o, 0);
        func_00170fa8(o, w, func_00173718, D_0035BE40, 30.0f);
        w->w80.b.m = 3;
        w->p88 = t;
        w->w8C = 0;
        w->w80.b.z = 0x403;
        func_00171e50(o, w, t);
        func_00141540(o, -2);
        break;
    }
    return 1;
}
#undef func_00148a40
#undef func_00170fa8
#undef func_00171e50

/* func_001724b8 (from hand/nostrict/text_00160000_h60.c). */
s32 func_00171098(Chr *, s32);
#define func_00148a40 ((void (*)(void *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(void *, void *, void *, void *, f32)) func_00170fa8)
#define func_00171e50 ((void (*)(Chr *, Wk172_22e8 *, Chr *)) func_00171e50)
s32 func_001724b8(Chr *o, Wk172_22e8 *w, s32 unused, s32 mode) {
    Chr *list[3];
    Chr *t;
    s32 i;
    list[0] = o;
    list[1] = D_0035BD40.chr[0];
    list[2] = func_00171078(o, w);
    if (w->p98 != 0 && func_00171098(w->p98, 84)) t = w->p98;
    else t = 0;
    for (i = 0; i < 3; i++) {
        if (list[i] != 0 && func_00171098(list[i], 84) && t == 0) t = list[i];
    }
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (t == 0) return 0;
        if (o->p6C->w44 < 3) return 0;
        if (!func_00171a88(o, w, 63)) return 0;
        break;
    case 2:
        func_00148a40(o, 0);
        func_00170fa8(o, w, func_00173718, D_0035BE40, 30.0f);
        w->w80.b.m = 3;
        w->w8C = -1;
        w->p88 = 0;
        w->w80.b.z = 0x406;
        func_00171e50(o, w, t);
        func_00141540(o, -3);
        break;
    }
    return 1;
}
#undef func_00148a40
#undef func_00170fa8
#undef func_00171e50

/* func_00172690 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { u8 pad[8]; void *w8; u8 padC[0x64]; s32 w70; } Ent6D;
typedef struct { u8 pad[0xC]; f32 fC; f32 f10; f32 f14; f32 f18; } Rng6D;
typedef struct { u8 pad[4]; u32 w4; } Arg6D;
typedef struct {
    u8 pad0[8]; Rng6D *p08; Rng6D *p0C; u8 pad10[0x20]; f32 f30; u8 pad34[4]; u64 w38; u8 pad40[0x14]; s32 w54; u8 pad58[0xC];
    f32 f64; f32 f68; f32 f6C; u8 pad70[4]; Arg6D *p74; u8 pad78[0x18]; void *p90; u8 pad94[8]; f32 f9C; u8 padA0[0x2C];
    f32 fCC; u8 padD0[0xC]; f32 fDC; u8 padE0[0x40]; f32 v120[4];
} Wk6D;
typedef struct { s32 w0; u8 pad4[0x10]; f32 f14, f18, f1C; } Sub170C_2690;
typedef struct { u8 pad[0xC]; Sub170C_2690 *pC; } Sub170_2690;
typedef struct { u64 w0; u8 pad8[0x48]; f32 f50; } Sub40;
typedef struct { u8 pad[0x40]; Sub40 *p40; u8 pad44[0x10]; s32 w54; u8 pad58[0x10]; f32 f68; } Wk172_2690;
typedef struct { u8 pad[0x70]; s32 w70; } Obj172_2690;
void func_0013df40(Obj172_2690 *, s32);
void func_0014a0f0(Sub40 *);
f32 func_00171aa8(f32, f32);
s32 func_00171ae8(Obj172_2690 *, Wk172_2690 *);
#define func_00171b80 ((void *(*)(Obj172_2690 *, Wk172_2690 *, s32)) func_00171b80)
s32 func_00172690(Obj172_2690 *o, Wk172_2690 *w, Sub170_2690 *k, s32 mode) {
    Sub170C_2690 *c = k->pC;
    switch (mode) {
    case 1:
        if (o->w70 == 24) return 0;
    case 0:
        if (c == 0) return 0;
        if (o->w70 == 8) return 0;
        return func_0016db80((Ent6D *)o, (Wk6D *)w, (Arg6D *)k, mode);
    case 2:
        func_0016db80((Ent6D *)o, (Wk6D *)w, (Arg6D *)k, mode);
        if (w->w54 == 0) {
            func_0013df40(o, 0);
            w->f68 = func_00171aa8(c->f14, c->f18);
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
        break;
    }
    return 1;
}
#undef func_00171b80

/* func_00172810 (from hand/nostrict/text_00170000_h61.c). */
typedef struct Prm {
    s32 x0;         /* 0x00 */
    u8 pad4[0x10];
    f32 x14;        /* 0x14 */
    f32 x18;        /* 0x18 */
    f32 x1c;        /* 0x1C */
    f32 x20;        /* 0x20 */
} Prm;
typedef struct { u8 pad[0xc]; Prm *xc; } P160;
typedef struct P40 {
    u64 b0:2;
    u64 b2:2;
    u64 rest:60;
    u8 pad8[0x50 - 8];
    f32 x50;
} P40;
typedef struct Ob {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[4];
    s32 x54;        /* 0x54 */
    u8 pad58[0x68 - 0x58];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x160 - 0x6c];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob;
typedef struct Wk {
    u8 pad0[0x70];
    s32 x70;
    u8 pad74[0x144 - 0x74];
    Ob *x144;       /* 0x144 */
} Wk;
s32 func_0016dd30(Wk *, Ob *, P160 *, s32);
#define func_0013df40 ((void (*)(Wk *, s32)) func_0013df40)
#define func_00171ae8 ((s32 (*)(Wk *, Ob *)) func_00171ae8)
#define func_00171b80 ((s16 *(*)(Wk *, Ob *, s32)) func_00171b80)
#define func_0014a0f0 ((void (*)(P40 *)) func_0014a0f0)
s32 func_00172810(Wk *w, Ob *o, P160 *p, s32 a3) {
    Prm *q = p->xc;
    switch (a3) {
    case 1:
        if (w->x70 == 24) return 0;
    case 0:
        if (w->x70 == 8) return 0;
        if (!q) return 0;
        return func_0016dd30(w, o, p, a3);
    case 2:
        func_0016dd30(w, o, p, a3);
        if (o->x54 == 0) {
            func_0013df40(w, 0);
            o->x68 = func_00171aa8(q->x14, q->x18);
        }
        if (!func_00171ae8(w, o)) {
            func_00171b80(w, o, q->x0);
            if (func_00171ae8(w, o)) {
                o->x40->b2 = 1;
                o->x40->x50 = q->x1c;
            }
        } else {
            o->x40->b2 = 1;
            func_0014a0f0(o->x40);
        }
        return 1;
    }
    return 1;
}
#undef func_0013df40
#undef func_00171ae8
#undef func_00171b80
#undef func_0014a0f0

/* func_00172998 (from hand/nostrict/text_s7_w30.c). */
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
#define func_0013df40 ((void (*)(Ob29 *, s32)) func_0013df40)
#define func_00171ae8 ((s32 (*)(Ob29 *, Wk29 *)) func_00171ae8)
#define func_00171b80 ((void *(*)(Ob29 *, Wk29 *, s32)) func_00171b80)
#define func_0014a0f0 ((void (*)(Sub40_29 *)) func_0014a0f0)
#define func_001693c8 ((void (*)(Ob29 *, Wk29 *)) func_001693c8)
/* func_00172998: MATCH hand/nostrict. Shared labels against if-conversion: r0 (return 0) reached from the p90 test, r1 (the final return 1) from the x90 test and after the range tests; r = 0 before the range tests (w13). */
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
        if (PlatVu0InnerProduct(&w->vD0, &o->v30) < 0.0f) goto out;
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
            if (w->p90 != 0) PlatVu0CopyVector(&w->v160, &w->vD0);
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
        PlatVu0CopyVector(&w->v120, &w->v160);
        w->v120.w = 20.0f;
        break;
    }
r1:
    return 1;
}
#undef func_0013df40
#undef func_00171ae8
#undef func_00171b80
#undef func_0014a0f0
#undef func_001693c8

/* func_00172bc8 (from hand/nostrict/text_00170000_h61.c). */
typedef struct Task { u8 pad[0xc]; void *cb; } Task;
typedef struct Prm3 {
    s32 x0;
    f32 x4, x8, xc, x10, x14, x18, x1c, x20, x24;
} Prm3;
typedef struct { u8 pad[0xc]; Prm3 *xc; } R160;
typedef struct Ac3 {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    void *x48;      /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x90 - 0x50];
    s32 x90;        /* 0x90 */
    u8 pad94[0x164 - 0x94];
    f32 x164;
    u8 pad168[0x170 - 0x168];
    R160 *x170;
    s32 x174;
    s32 x178;
} Ac3;
typedef struct Wk3 {
    u8 pad0[0x14];
    f32 x14;
} Wk3;
#define func_00171a88 ((s32 (*)(Wk3 *, void *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Wk3 *, void *, R160 *, s32)) func_0016b670)
#define func_00130340 ((s32 (*)(Wk3 *, s32, f32)) func_00130340)
#define func_00130578 ((Task *(*)(Wk3 *, s32, f32)) func_00130578)
#define func_00148a40 ((void (*)(Wk3 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Wk3 *, void *, void *, void *, f32)) func_00170fa8)
#define func_0013dbe0 ((s32 *(*)(Wk3 *, s32)) func_0013dbe0)
#define func_001477c8 ((s32 *(*)(s32)) func_001477c8)
#define func_001412f8 ((void (*)(Wk3 *, s32)) func_001412f8)
#define func_00170f50 ((void (*)(Wk3 *, void *, void *, s32, s32)) func_00170f50)
s32 func_00172bc8(Wk3 *w, Ac3 *o, R160 *p, s32 a3) {
    Prm3 *q = p->xc;
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 31)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        if (!o->x90) return 0;
        return func_0016b670(w, o, p, 1);
    case 2:
        o->flags |= 0x800;
        func_00130340(w, 0x10000ce, 8.0f);
        o->x4c = 206;
        o->x170 = p;
        o->x178 = 0x40000000;
        o->x174 = 0;
        o->x164 = w->x14 - q->x24;
        func_00130578(w, 0x40000000, 8.0f)->cb = func_001731f8;
        func_00148a40(w, 0);
        func_00170fa8(w, o, func_00170f90, D_0035BE40, 30.0f);
        func_001412f8(w, func_001477c8(func_0013dbe0(w, q->x0)[1])[12]);
        o->x48 = func_00173610;
        func_00170f50(w, o, func_001734f8, 3, 0);
        return 1;
    }
    return 1;
}
#undef func_00171a88
#undef func_0016b670
#undef func_00130340
#undef func_00130578
#undef func_00148a40
#undef func_00170fa8
#undef func_0013dbe0
#undef func_001477c8
#undef func_001412f8
#undef func_00170f50

/* func_00172df8 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_72df8 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_72df8;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_72df8;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_72df8 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_72df8 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144;
#define func_00148a40 ((void (*)(Obj144 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Obj144 *, Wk144 *, void *, void *, f32)) func_00170fa8)
#define func_00170f90 ((s32 (*)()) func_00170f90)
#define func_00171a88 ((s32 (*)(Obj144 *, Wk144 *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Obj144 *, Wk144 *, s32, s32)) func_0016b670)
s32 func_00172df8(Obj144 *o, Wk144 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 29)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035BE40, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00148a40
#undef func_00170fa8
#undef func_00170f90
#undef func_00171a88
#undef func_0016b670

/* func_00172f00 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_72f00 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_72f00;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_72f00;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_72f00 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_72f00 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_72f00;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_72f00 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_72f00;
#define func_00148a40 ((void (*)(Obj144_72f00 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Obj144_72f00 *, Wk144_72f00 *, void *, void *, f32)) func_00170fa8)
#define func_00170f90 ((s32 (*)()) func_00170f90)
#define func_00171a88 ((s32 (*)(Obj144_72f00 *, Wk144_72f00 *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Obj144_72f00 *, Wk144_72f00 *, s32, s32)) func_0016b670)
s32 func_00172f00(Obj144_72f00 *o, Wk144_72f00 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 30)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035BE40, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00148a40
#undef func_00170fa8
#undef func_00170f90
#undef func_00171a88
#undef func_0016b670

/* func_00173008 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73008 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73008;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73008;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73008 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73008 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73008;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73008 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73008;
extern void func_0014f658(Obj144_73008 *, s32);
#define func_00171a88 ((s32 (*)(Obj144_73008 *, Wk144_73008 *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Obj144_73008 *, Wk144_73008 *, s32, s32)) func_0016b670)
s32 func_00173008(Obj144_73008 *o, Wk144_73008 *w, Sub170 *k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 31)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (w->w90 == 0) return 0;
        return func_0016b670(o, w, (s32)k, 1);
    case 2:
        w->p170 = k;
        w->w38 |= 0x800;
        func_0014f658(o, 50);
        return 1;
    }
    return 1;
}
#undef func_00171a88
#undef func_0016b670

/* func_001730f0 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_730f0 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_730f0;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_730f0;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_730f0 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_730f0 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_730f0;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_730f0 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_730f0;
#define func_00148a40 ((void (*)(Obj144_730f0 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Obj144_730f0 *, Wk144_730f0 *, void *, void *, f32)) func_00170fa8)
#define func_00170f90 ((s32 (*)()) func_00170f90)
#define func_00171a88 ((s32 (*)(Obj144_730f0 *, Wk144_730f0 *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Obj144_730f0 *, Wk144_730f0 *, s32, s32)) func_0016b670)
s32 func_001730f0(Obj144_730f0 *o, Wk144_730f0 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 29)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035BE40, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00148a40
#undef func_00170fa8
#undef func_00170f90
#undef func_00171a88
#undef func_0016b670

/* func_001731f8 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_731f8 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_731f8;
typedef struct { u8 pad[0x2C]; Sub2C *p2C; } Sub14C_731f8;
typedef struct { u8 pad[0x14C]; Sub14C_731f8 *p14C; } Obj14C_731f8;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_731f8;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_731f8 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_731f8 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_731f8;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_731f8 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_731f8;
#define func_00171ae8 ((s32 (*)(Obj144_731f8 *, Wk144_731f8 *)) func_00171ae8)
void func_001731f8(Obj144_731f8 *o) {
    Wk144_731f8 *w = o->p144;
    Sub170C *c;
    if ((s32)((s64)(w->w38 << 15) >> 32) & 1) {
        w->w38 &= ~0x20000LL;
        return;
    }
    c = w->p170->pC;
    w->f68 = func_00171aa8(c->f14, c->f18);
    w->w4C = *(s16 *)func_00171b80((Obj14C_731f8 *)o, (Arg3C *)w, c->w0);
    if (func_00171ae8(o, w)) w->p40->f50 = c->f1C;
    w->w174 = 1;
}
#undef func_00171ae8

/* func_00173360 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73360 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73360;
typedef struct {
    u8 pad[0x38]; u64 w38; u8 pad40[0x50];
    ObjBD40_73360 *tgt; s32 part; s32 w98; f32 f9C; f32 fA0; u8 padA4[0xC];
    f32 vB0[4]; f32 vC0[3]; f32 fCC; f32 vD0[3]; f32 fDC;
} Lock90_73360;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73360;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73360 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73360 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73360;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73360 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73360;
#define func_0014f658 ((void (*)(Obj144_73360 *, s32)) func_0014f658)
#define func_00171118 ((s32 (*)(ObjBD40_73360 *, s32)) func_00171118)
#define func_00171790 ((void (*)(Obj2C4 *, Lock90_73360 *)) func_00171790)
void func_00173360(Obj144_73360 *o) {
    Wk144_73360 *w = o->p144;
    s32 st = o->w70;
    if (!func_00171118(w->w90, -1)) {
        st = 0;
    } else {
        w->w38 |= 0x100000;
        func_00171790((Obj2C4 *)o, (Lock90_73360 *)w);
    }
    switch (w->w174) {
    case 0:
        if (!(o->w160 & 1) && o->w164 != 206) st = 0;
        break;
    case 1:
        if ((o->w160 & 1) || o->w164 == w->w4C) {
            if (w->f68 <= 0.0f) st = 0;
        } else {
            st = 0;
        }
        break;
    }
    if (o->w70 != st) func_0014f658(o, st);
}
#undef func_0014f658
#undef func_00171118
#undef func_00171790

/* func_00173478 (from hand/nostrict/text_00160000_s6_09.c). */
typedef struct { u8 pad[0x20]; f32 x20; } Prm34;
typedef struct { u8 pad[0xc]; Prm34 *xc; } P34;
typedef struct {
    u8 pad0[0xc0]; f32 xc0[4];
    u8 padd0[0x164 - 0xd0]; f32 x164;
    u8 pad168[0x170 - 0x168]; P34 *x170; s32 x174;
} Ob34;
typedef struct { u8 pad0[0x14]; f32 x14; u8 pad18[0x144 - 0x18]; Ob34 *x144; } Wk34;
void func_00173478(Wk34 *w, f32 *v) {
    Ob34 *o = w->x144;
    Prm34 *p = o->x170->xc;
    if (o->x174 == 1) {
        PlatVu0ScaleVectorXYZ(v, o->xc0, p->x20);
        if (w->x14 + v[1] < o->x164) v[1] = o->x164 - w->x14;
    }
}

/* func_001734f8 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_734f8 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_734f8;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_734f8;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_734f8 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_734f8 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_734f8;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_734f8 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_734f8;
s32 func_001734f8(Obj144_734f8 *o, Wk144_734f8 *w, s32 mode) {
    s32 r = 0;
    switch (mode) {
    case 1:
        switch (w->w174) {
        case 0:
            if (!(o->w160 & 1) && o->w164 != 206) r = 1;
            break;
        case 1:
            if (!(o->w160 & 1) && o->w164 != w->w4C) r = 1;
            break;
        }
        break;
    case 2:
        r = w->w48 == 0;
        break;
    }
    if (r == 1) {
        w->w38 = ((w->w38 & ~0x800LL) | 0x20000) & ~0x200LL;
        w->w48 = 0;
        if (o->w164 == 206 || o->w164 == w->w4C) func_00130340((Obj3D0 *)o, w->w178, 8.0f);
    }
    return r;
}

/* func_00173610 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73610 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73610;
typedef struct {
    u8 pad[0x38]; u64 w38; u8 pad40[0x50];
    ObjBD40_73610 *tgt; s32 part; s32 w98; f32 f9C; f32 fA0; u8 padA4[0xC];
    f32 vB0[4]; f32 vC0[3]; f32 fCC; f32 vD0[3]; f32 fDC;
} Lock90_73610;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73610;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73610 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73610 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73610;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73610 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73610;
#define func_00171118 ((s32 (*)(ObjBD40_73610 *, s32)) func_00171118)
#define func_00171790 ((void (*)(Obj2C4 *, Lock90_73610 *)) func_00171790)
void func_00173610(Obj144_73610 *o, Wk144_73610 *w) {
    f32 v[4];
    Sub170C *c = w->p170->pC;
    if (!func_00171118(w->w90, -1)) {
        w->w48 = 0;
        return;
    }
    w->w38 |= 0x100000;
    func_00171790((Obj2C4 *)o, (Lock90_73610 *)w);
    switch (w->w174) {
    case 0:
        return;
    case 1:
        if (w->f68 <= 0.0f) w->w48 = 0;
        w->w38 |= 0x1000;
        if (o->w70 == 8) w->w38 |= 0x200;
        PlatVu0ScaleVectorXYZ(v, w->vC0, c->f20);
        w->f124 = v[1];
        v[1] = 0.0f;
        w->f12C = func_00162c20(v);
        w->f120 = v[0];
        w->f128 = v[2];
        break;
    }
}
#undef func_00171118
#undef func_00171790

/* func_00173758 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73758 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73758;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73758;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73758 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73758 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73758;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73758 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73758;
extern u8 D_0035C080[];
#define func_00148a40 ((void (*)(Obj144_73758 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Obj144_73758 *, Wk144_73758 *, void *, void *, f32)) func_00170fa8)
#define func_00170f90 ((s32 (*)()) func_00170f90)
#define func_00171a88 ((s32 (*)(Obj144_73758 *, Wk144_73758 *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Obj144_73758 *, Wk144_73758 *, s32, s32)) func_0016b670)
s32 func_00173758(Obj144_73758 *o, Wk144_73758 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 33)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035C080, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00148a40
#undef func_00170fa8
#undef func_00170f90
#undef func_00171a88
#undef func_0016b670

/* func_00173860 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73860 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73860;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73860;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73860 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73860 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73860;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73860 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73860;
#define func_00148a40 ((void (*)(Obj144_73860 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Obj144_73860 *, Wk144_73860 *, void *, void *, f32)) func_00170fa8)
#define func_00170f90 ((s32 (*)()) func_00170f90)
#define func_00171a88 ((s32 (*)(Obj144_73860 *, Wk144_73860 *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Obj144_73860 *, Wk144_73860 *, s32, s32)) func_0016b670)
s32 func_00173860(Obj144_73860 *o, Wk144_73860 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 34)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035C080, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00148a40
#undef func_00170fa8
#undef func_00170f90
#undef func_00171a88
#undef func_0016b670

/* func_00173968 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73968 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73968;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73968;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73968 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73968 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73968;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73968 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73968;
extern s32 func_0016ce10(Obj144_73968 *, Wk144_73968 *, s32, s32);
#define func_00171a88 ((s32 (*)(Obj144_73968 *, Wk144_73968 *, s32)) func_00171a88)
s32 func_00173968(Obj144_73968 *o, Wk144_73968 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 35)) return 0;
        return func_0016ce10(o, w, k, 1);
    case 2:
        func_0016ce10(o, w, k, 2);
        return 1;
    }
    return 1;
}
#undef func_00171a88

/* func_00173a20 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73a20 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73a20;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73a20;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73a20 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73a20 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73a20;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73a20 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73a20;
extern s32 func_0016d768(Obj144_73a20 *, Wk144_73a20 *, s32, s32);
#define func_00171a88 ((s32 (*)(Obj144_73a20 *, Wk144_73a20 *, s32)) func_00171a88)
s32 func_00173a20(Obj144_73a20 *o, Wk144_73a20 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 36)) return 0;
        return func_0016d768(o, w, k, 1);
    case 2:
        func_0016d768(o, w, k, 2);
        return 1;
    }
    return 1;
}
#undef func_00171a88

/* func_00173af0 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73af0 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73af0;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73af0;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73af0 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73af0 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73af0;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73af0 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73af0;
extern u8 D_0035C130[];
#define func_00148a40 ((void (*)(Obj144_73af0 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Obj144_73af0 *, Wk144_73af0 *, void *, void *, f32)) func_00170fa8)
#define func_00170f90 ((s32 (*)()) func_00170f90)
#define func_00171a88 ((s32 (*)(Obj144_73af0 *, Wk144_73af0 *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Obj144_73af0 *, Wk144_73af0 *, s32, s32)) func_0016b670)
s32 func_00173af0(Obj144_73af0 *o, Wk144_73af0 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 37)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035C130, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00148a40
#undef func_00170fa8
#undef func_00170f90
#undef func_00171a88
#undef func_0016b670

/* func_00173bf8 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73bf8 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73bf8;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73bf8;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73bf8 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73bf8 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73bf8;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73bf8 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73bf8;
#define func_00148a40 ((void (*)(Obj144_73bf8 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Obj144_73bf8 *, Wk144_73bf8 *, void *, void *, f32)) func_00170fa8)
#define func_00170f90 ((s32 (*)()) func_00170f90)
#define func_00171a88 ((s32 (*)(Obj144_73bf8 *, Wk144_73bf8 *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Obj144_73bf8 *, Wk144_73bf8 *, s32, s32)) func_0016b670)
s32 func_00173bf8(Obj144_73bf8 *o, Wk144_73bf8 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 38)) return 0;
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        return func_0016b670(o, w, k, 1);
    case 2:
        func_00148a40(o, 0);
        func_0016b670(o, w, k, 2);
        func_00170fa8(o, w, func_00170f90, D_0035C130, 30.0f);
        return 1;
    }
    return 1;
}
#undef func_00148a40
#undef func_00170fa8
#undef func_00170f90
#undef func_00171a88
#undef func_0016b670

/* func_00173d00 (from hand/nostrict/text_00170000_h61.c). */
typedef struct Ac4 {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    void *x48;      /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x90 - 0x50];
    s32 x90;
    u8 pad94[0x160 - 0x94];
    R160 *x160;
    s32 x164;
} Ac4;
void func_001740e8();
extern u8 D_0035C1E0[];
void func_001742b0();
s32 func_001741a0();
#define func_00171a88 ((s32 (*)(Wk3 *, void *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Wk3 *, void *, R160 *, s32)) func_0016b670)
#define func_00130340 ((s32 (*)(Wk3 *, s32, f32)) func_00130340)
#define func_00130578 ((Task *(*)(Wk3 *, s32, f32)) func_00130578)
#define func_00148a40 ((void (*)(Wk3 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Wk3 *, void *, void *, void *, f32)) func_00170fa8)
#define func_0013dbe0 ((s32 *(*)(Wk3 *, s32)) func_0013dbe0)
#define func_001477c8 ((s32 *(*)(s32)) func_001477c8)
#define func_001412f8 ((void (*)(Wk3 *, s32)) func_001412f8)
#define func_00170f50 ((void (*)(Wk3 *, void *, void *, s32, s32)) func_00170f50)
s32 func_00173d00(Wk3 *w, Ac4 *o, R160 *p, s32 a3) {
    Prm3 *q = p->xc;
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 49)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, p, 1);
    case 2:
        o->flags |= 0x800;
        func_00130340(w, 0x10000ca, 8.0f);
        o->x4c = 202;
        func_00130578(w, 0x40000000, 8.0f)->cb = func_001740e8;
        o->x160 = p;
        o->x164 = 0;
        func_00148a40(w, 0);
        func_00170fa8(w, o, func_00170f90, D_0035C1E0, 30.0f);
        func_001412f8(w, func_001477c8(func_0013dbe0(w, q->x0)[1])[12]);
        o->x48 = func_001742b0;
        func_00170f50(w, o, func_001741a0, 3, 0);
        return 1;
    }
    return 1;
}
#undef func_00171a88
#undef func_0016b670
#undef func_00130340
#undef func_00130578
#undef func_00148a40
#undef func_00170fa8
#undef func_0013dbe0
#undef func_001477c8
#undef func_001412f8
#undef func_00170f50

/* func_00173ec0 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73ec0 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73ec0;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73ec0;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73ec0 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73ec0 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73ec0;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73ec0 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73ec0;
extern s32 func_0016cb98(Obj144_73ec0 *, Wk144_73ec0 *, s32, s32);
#define func_00171a88 ((s32 (*)(Obj144_73ec0 *, Wk144_73ec0 *, s32)) func_00171a88)
s32 func_00173ec0(Obj144_73ec0 *o, Wk144_73ec0 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 50)) return 0;
        return func_0016cb98(o, w, k, 1);
    case 2:
        func_0016cb98(o, w, k, 2);
        return 1;
    }
    return 1;
}
#undef func_00171a88

/* func_00173f78 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_73f78 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_73f78;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_73f78;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_73f78 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_73f78 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_73f78;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_73f78 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_73f78;
#define func_00171a88 ((s32 (*)(Obj144_73f78 *, Wk144_73f78 *, s32)) func_00171a88)
#define func_0016ce10 ((s32 (*)(Obj144_73f78 *, Wk144_73f78 *, s32, s32)) func_0016ce10)
s32 func_00173f78(Obj144_73f78 *o, Wk144_73f78 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 51)) return 0;
        return func_0016ce10(o, w, k, 1);
    case 2:
        func_0016ce10(o, w, k, 2);
        return 1;
    }
    return 1;
}
#undef func_00171a88
#undef func_0016ce10

/* func_00174030 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_74030 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_74030;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_74030;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_74030 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_74030 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_74030;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_74030 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_74030;
#define func_00171a88 ((s32 (*)(Obj144_74030 *, Wk144_74030 *, s32)) func_00171a88)
#define func_0016d768 ((s32 (*)(Obj144_74030 *, Wk144_74030 *, s32, s32)) func_0016d768)
s32 func_00174030(Obj144_74030 *o, Wk144_74030 *w, s32 k, s32 mode) {
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(o, w, 52)) return 0;
        return func_0016d768(o, w, k, 1);
    case 2:
        func_0016d768(o, w, k, 2);
        return 1;
    }
    return 1;
}
#undef func_00171a88
#undef func_0016d768

/* func_001740e8 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_740e8 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_740e8;
typedef struct { u8 pad[0x2C]; Sub2C *p2C; } Sub14C_740e8;
typedef struct { u8 pad[0x14C]; Sub14C_740e8 *p14C; } Obj14C_740e8;
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_740e8;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_740e8 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0x24]; ObjBD40_740e8 *w90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 f120, f124, f128, f12C; u8 pad130[0x34]; f32 f164; u8 pad168[8]; Sub170 *p170; s32 w174; s32 w178; } Wk144_740e8;
typedef struct { u8 pad[0x14]; f32 f14; u8 pad18[0x58]; s32 w70; u8 pad74[0xD0]; Wk144_740e8 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj144_740e8;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_740e8 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0xF4]; Sub170 *p160; s32 w164; } Wk160;
typedef struct { u8 pad[0x144]; Wk160 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj160;
#define func_00171ae8 ((s32 (*)(Obj144_740e8 *, Wk144_740e8 *)) func_00171ae8)
void func_001740e8(Obj160 *o) {
    Wk160 *w = o->p144;
    Sub170C *c;
    if ((s32)((s64)(w->w38 << 15) >> 32) & 1) {
        w->w38 &= ~0x20000LL;
        return;
    }
    c = w->p160->pC;
    w->f68 = func_00171aa8(c->f14, c->f18);
    w->w4C = *(s16 *)func_00171b80((Obj14C_740e8 *)o, (Arg3C *)w, c->w0);
    if (func_00171ae8((Obj144_740e8 *)o, (Wk144_740e8 *)w)) w->p40->f50 = c->f1C;
    w->w164 = 1;
}
#undef func_00171ae8

/* func_001741a0 (from hand/nostrict/text_00160000_h37.c). */
typedef struct { u8 pad[0x50]; f32 f50; } Sub40_741a0;
typedef struct { u8 pad[0x38]; u64 w38; Sub40_741a0 *p40; u8 pad44[4]; void *w48; s32 w4C; u8 pad50[0x18]; f32 f68; u8 pad6C[0xF4]; Sub170 *p160; s32 w164; } Wk160_741a0;
typedef struct { u8 pad[0x144]; Wk160_741a0 *p144; u8 pad148[0x18]; s32 w160; s32 w164; } Obj160_741a0;
s32 func_001741a0(Obj160_741a0 *o, Wk160_741a0 *w, s32 mode) {
    s32 r = 0;
    switch (mode) {
    case 1:
        switch (w->w164) {
        case 0:
            if (!(o->w160 & 1) && o->w164 != 202) r = 1;
            break;
        case 1:
            if (!(o->w160 & 1) && o->w164 != w->w4C) r = 1;
            break;
        }
        break;
    case 2:
        r = w->w48 == 0;
        break;
    }
    if (r == 1) {
        w->w38 = (w->w38 & ~0x800LL) | 0x20000;
        w->w48 = 0;
        if (o->w164 == 202 || o->w164 == w->w4C) func_00130340((Obj3D0 *)o, 0x40000000, 8.0f);
    }
    return r;
}

/* func_001742b0 (from hand/nostrict/text_00170000_h38.c). */
typedef struct { f32 x, y, z; } V3;
typedef struct Ob_742b0 {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    void *x40;      /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x68 - 0x50];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x90 - 0x6c];
    s32 x90;        /* 0x90 */
    u8 pad94[0xc0 - 0x94];
    V3 xc0;         /* 0xC0 */
    u8 padcc[0x120 - 0xcc];
    f32 x120, x124, x128, x12c; /* 0x120 */
    u8 pad130[0x160 - 0x130];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob_742b0;
typedef struct Wk_742b0 {
    u8 pad0[0x160];
    s32 x160;       /* 0x160 */
    s32 x164;       /* 0x164 */
} Wk_742b0;
#define func_00171118 ((s32 (*)(s32, s32)) func_00171118)
#define func_00171790 ((void (*)(Wk_742b0 *, Ob_742b0 *)) func_00171790)
void func_001742b0(Wk_742b0 *w, Ob_742b0 *o) {
    f32 v[3];
    Prm *q = o->x160->xc;
    if (!func_00171118(o->x90, -1)) {
        o->x48 = 0;
        return;
    }
    o->flags |= 0x100000;
    func_00171790(w, o);
    if (o->x164 == 0) return;
    if (o->x164 != 1) return;
    if (o->x68 < 0.0f) o->x48 = 0;
    o->flags |= 0x1000;
    PlatVu0ScaleVectorXYZ(v, &o->xc0, q->x20);
    o->x124 = v[1];
    v[1] = 0.0f;
    o->x12c = func_00162c20(v);
    o->x120 = v[0];
    o->x128 = v[2];
}
#undef func_00171118
#undef func_00171790

/* func_00174798 (from hand/nostrict/text_00170000_h61.c). */
void func_00174ad8(void);
extern u8 D_0035C350[];
void func_00174ca8();
s32 func_00174b90();
#define func_00171a88 ((s32 (*)(Wk3 *, void *, s32)) func_00171a88)
#define func_0016b670 ((s32 (*)(Wk3 *, void *, R160 *, s32)) func_0016b670)
#define func_00130340 ((s32 (*)(Wk3 *, s32, f32)) func_00130340)
#define func_00130578 ((Task *(*)(Wk3 *, s32, f32)) func_00130578)
#define func_00148a40 ((void (*)(Wk3 *, s32)) func_00148a40)
#define func_00170fa8 ((void (*)(Wk3 *, void *, void *, void *, f32)) func_00170fa8)
#define func_0013dbe0 ((s32 *(*)(Wk3 *, s32)) func_0013dbe0)
#define func_001477c8 ((s32 *(*)(s32)) func_001477c8)
#define func_001412f8 ((void (*)(Wk3 *, s32)) func_001412f8)
#define func_00170f50 ((void (*)(Wk3 *, void *, void *, s32, s32)) func_00170f50)
s32 func_00174798(Wk3 *w, Ac4 *o, R160 *p, s32 a3) {
    Prm3 *q = p->xc;
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 44)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        if (!o->x90) return 0;
        return func_0016b670(w, o, p, 1);
    case 2:
        o->flags |= 0x800;
        func_00130340(w, 0x10000ca, 8.0f);
        o->x4c = 202;
        func_00130578(w, 0x40000075, 8.0f)->cb = func_00174ad8;
        o->x160 = p;
        o->x164 = 0;
        func_00148a40(w, 0);
        func_00170fa8(w, o, func_00170f90, D_0035C350, 30.0f);
        func_001412f8(w, func_001477c8(func_0013dbe0(w, q->x0)[1])[12]);
        o->x48 = func_00174ca8;
        func_00170f50(w, o, func_00174b90, 3, 0);
        return 1;
    }
    return 1;
}
#undef func_00171a88
#undef func_0016b670
#undef func_00130340
#undef func_00130578
#undef func_00148a40
#undef func_00170fa8
#undef func_0013dbe0
#undef func_001477c8
#undef func_001412f8
#undef func_00170f50

/* func_00174b90 (from hand/nostrict/text_00170000_h38.c). */
typedef struct Ob_74b90 {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    void *x40;      /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x68 - 0x50];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x90 - 0x6c];
    s32 x90;        /* 0x90 */
    u8 pad94[0xc0 - 0x94];
    V3 xc0;         /* 0xC0 */
    u8 padcc[0x120 - 0xcc];
    f32 x120, x124, x128, x12c; /* 0x120 */
    u8 pad130[0x160 - 0x130];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob_74b90;
typedef struct Wk_74b90 {
    u8 pad0[0x160];
    s32 x160;       /* 0x160 */
    s32 x164;       /* 0x164 */
} Wk_74b90;
#define func_00130340 ((void (*)(Wk_74b90 *, s32, f32)) func_00130340)
s32 func_00174b90(Wk_74b90 *w, Ob_74b90 *o, s32 a2) {
    s32 r = 0;
    switch (a2) {
    case 1:
        switch (o->x164) {
        case 0:
            if (!(w->x160 & 1)) {
                if (w->x164 != 202) r = 1;
            }
            break;
        case 1:
            if (!(w->x160 & 1)) {
                if (w->x164 != o->x4c) r = 1;
            }
            break;
        }
        break;
    case 2:
        r = o->x48 == 0;
        break;
    }
    if (r == 1) {
        o->x48 = 0;
        o->flags &= ~0x800;
        o->flags &= ~0x200;
        o->flags |= 0x20000;
        if (w->x164 == 202 || w->x164 == o->x4c) func_00130340(w, 0x40000075, 8.0f);
    }
    return r;
}
#undef func_00130340

/* func_00174ca8 (from hand/nostrict/text_00170000_h38.c). */
typedef struct Ob_74ca8 {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    void *x40;      /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x68 - 0x50];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x90 - 0x6c];
    s32 x90;        /* 0x90 */
    u8 pad94[0xc0 - 0x94];
    V3 xc0;         /* 0xC0 */
    u8 padcc[0x120 - 0xcc];
    f32 x120, x124, x128, x12c; /* 0x120 */
    u8 pad130[0x160 - 0x130];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob_74ca8;
typedef struct Wk_74ca8 {
    u8 pad0[0x160];
    s32 x160;       /* 0x160 */
    s32 x164;       /* 0x164 */
} Wk_74ca8;
#define func_00171118 ((s32 (*)(s32, s32)) func_00171118)
#define func_00171790 ((void (*)(Wk_74ca8 *, Ob_74ca8 *)) func_00171790)
void func_00174ca8(Wk_74ca8 *w, Ob_74ca8 *o) {
    f32 v[3];
    Prm *q = o->x160->xc;
    if (!func_00171118(o->x90, -1)) {
        o->x48 = 0;
        return;
    }
    o->flags |= 0x100000;
    func_00171790(w, o);
    if (o->x164 == 0) return;
    if (o->x164 != 1) return;
    if (o->x68 < 0.0f) o->x48 = 0;
    o->flags |= 0x1000;
    o->flags |= 0x200;
    PlatVu0ScaleVectorXYZ(v, &o->xc0, q->x20);
    o->x124 = v[1];
    v[1] = 0.0f;
    o->x12c = func_00162c20(v);
    o->x120 = v[0];
    o->x128 = v[2];
}
#undef func_00171118
#undef func_00171790

