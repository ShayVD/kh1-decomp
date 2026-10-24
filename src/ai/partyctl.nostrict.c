/* The party members' control, without strict aliasing (docs/modules.md
 * "Session 52"): the action handlers the AI tables of src/ai/partyai name
 * (each takes a member and its work area and returns whether the action
 * applies: func_0016a3f8 / func_0016abc0 / func_0016b1f0 pick an action
 * from D_00575328, func_0016c480 ... func_0016d768 attack and follow
 * tests), the follow positions D_00575020 / D_00575050 / D_00575090
 * (func_0016e1f0, func_0016e3f8), the target search func_0016ea58, the
 * party's callback list (D_00575528 nodes, free list D_00575784, active
 * list D_00575780: func_0016e0d0, func_0016f3d0, func_0016f548) and its
 * reset func_0016f640.  Read from the code, not proved by a boot.
 *
 * Traps: struct Actor is completed differently by the old files, so the
 * functions that read D_002E26A0 or the node lists through their own
 * types use `__asm__` aliases (`extern T *D_X_<addr>[] __asm__("D_X")`);
 * a cast view `((T **) D_X)` changed the address folding. */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002E27C8.h"
#include "platform/math.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h59.h"
#include "data/bss_0057.h"
#include "data/pieces/D_0035BD40.h"
#include "data/types/nostrict_text_00160000_h60_p.h"
#include "data/types/nostrict_text_00160000_h60.h"
#include "data/pieces/D_002C5C60.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/types/nostrict_text_00150000_s6_08.h"
#include "data/pieces/D_00351BC8.h"
#include "data/types/nostrict_text_00160000_c04.h"
#include "data/types/nostrict_text_00160000_s10_r2_1.h"
#include "data/pieces/D_002E3168.h"

/* func_00168618 (s7 w34): MATCH hand/nostrict. From w31 4w draft: the e->b8 = 1 tails as `t = e->u.w; t |= 0x100; e->u.w = t;` with a function-level u64 t (global pseudo: no local-alloc tie, so the 256 constant gets v0 first). */
/* func_00168618 (from hand/nostrict/text_s7_w34.c). */
typedef struct { u8 pad[0x4C]; u16 h4C; } Ch130;
typedef struct {
    u8 pad0[0x70];
    s32 x70;
    u8 pad74[0x130 - 0x74];
    Ch130 *x130;
    u8 pad134[0x164 - 0x134];
    s32 x164;
    u8 pad168[0x3B0 - 0x168];
    f32 x3B0;
    f32 x3B4;
    f32 x3B8;
} Obj18;
typedef struct {
    u8 pad0[0x38];
    union { struct { u32 lo:8; u32 b8:1; u32 r9:23; u32 hi; } b; u64 w; } u;
    u8 pad40[0x120 - 0x40];
    u8 x120[4];
} __attribute__((aligned(8))) Ent18;
extern u32 D_002C5958;
void func_0014dcd8(Obj18 *, void *);
void func_0014c580(Obj18 *);
void func_0014c530(Obj18 *);
void func_0013dfb8(Obj18 *, void *);
/* func_00168618 (s7 w34): MATCH hand/nostrict. From w31 4w draft: the e->b8 = 1 tails as `t = e->u.w; t |= 0x100; e->u.w = t;` with a function-level u64 t (global pseudo: no local-alloc tie, so the 256 constant gets v0 first). */
s32 func_00168618(Obj18 *o, Ent18 *e) {
    s32 k, x;
    u64 t;
    if (o->x70 == 2) {
        if (!e->u.b.b8) goto r0;
        if (o->x3B0 >= o->x3B8 || o->x164 == 6) {
            if (D_002C5958 >> 5 & 1) {
                func_0014dcd8(o, e->x120);
                if (o->x70 != 8) goto r0;
                e->u.b.b8 = 0;
                return 1;
            } else {
                if ((u16)(o->x130->h4C - 1) >= 2) return 0;
                if ((*(u32 *)&D_002E27C8) >> 8 & 1) func_0014c580(o);
                else if ((*(u32 *)&D_002E27C8) >> 7 & 1) func_0014c530(o);
                else goto r0;
                if (o->x70 != 21) goto r0;
                e->u.b.b8 = 0;
                return 1;
            }
        }
    } else {
        if (e->u.b.b8) goto r0;
        if (D_002C5958 >> 5 & 1) { func_0013dfb8(o, e->x120); t = e->u.w; t |= 0x100; e->u.w = t; goto r0; }
        if ((u16)(o->x130->h4C - 1) >= 2) return 0;
        if ((*(u32 *)&D_002E27C8) >> 8 & 1) { func_0013dfb8(o, e->x120); t = e->u.w; t |= 0x100; e->u.w = t; goto r0; }
        if ((*(u32 *)&D_002E27C8) >> 7 & 1) { func_0013dfb8(o, e->x120); t = e->u.w; t |= 0x100; e->u.w = t; goto r0; }
    }
    r0:
    return 0;
}

/* func_001687d8 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { u8 pad[0x70]; s32 x70; } O87d8;
typedef struct {
    u8 pad0[4];
    f32 *x4;
    u8 pad8[0x38 - 8];
    u64 x38;
    u8 pad40[0xa4 - 0x40];
    f32 xa4;
    u8 pada8[0xdc - 0xa8];
    f32 xdc;
    u8 pade0[0xfc - 0xe0];
    f32 xfc;
    u8 pad100[0x12c - 0x100];
    f32 x12c;
} Q87d8;
void func_001687d8(O87d8 *o, Q87d8 *q, s32 k) {
    switch (k) {
    case 0:
        if (o->x70 == 8) {
            if ((s32)(q->x38 >> 7) & 1) {
                if (q->x4[3] < q->xfc) {
                    q->x12c = 10.0f;
                    return;
                }
                q->x12c = 0.0f;
                return;
            }
            if ((s32)q->x38 & 1) {
                q->x12c = 20.0f;
                return;
            }
            if (q->xfc <= q->x4[5]) {
                q->x12c = 0.0f;
                return;
            }
            if (q->x4[4] <= q->xfc) {
                q->x12c = 20.0f;
                return;
            }
            q->x12c = 10.0f;
            return;
        } else {
            u64 f = q->x38;
            if ((s32)(f >> 7) & 1) {
                if (q->x4[0] < q->xfc) {
                    q->x12c = 10.0f;
                } else {
                    q->x12c = 0.0f;
                }
            } else if ((s32)q->x38 & 1) {
                q->x12c = 20.0f;
            } else if (q->xfc <= q->x4[2]) {
                q->x12c = 0.0f;
            } else if (q->x4[1] <= q->xfc) {
                q->x12c = 20.0f;
            } else {
                q->x12c = 10.0f;
            }
            if (((s32)(f >> 19) & 1) && q->x4[0] < fabsf(q->xa4)) {
                q->x12c = 10.0f;
            }
            if (((s32)(f >> 14) & 1) && q->xfc < q->x4[0]) {
                q->x12c = 0.0f;
            }
        }
        break;
    case 1:
        if (q->x4[1] <= q->xdc) {
            q->x12c = 20.0f;
            return;
        }
        q->x12c = 10.0f;
        break;
    }
}

/* func_001689d0 (from hand/nostrict/text_00160000_h60.c). */
typedef Chr_35BD40 Chr;
typedef struct {
    u8 pad[0x20]; f32 v20[4]; u8 pad30[8]; u64 w38; u8 pad40[0x18]; s32 w58; u8 pad5c[0x34];
    Chr *tgt; u8 pad94[0xC]; f32 fA0; u8 padA4[0x40]; f32 fE4;
} L60;
s32 func_00119688(f32 *);
f32 func_00162a58(f32 *);
void func_001689d0(Chr *self, L60 *l) {
    f32 a[4];
    f32 b[4];
    f32 c[8];
    if (((s32)((s64)(l->w38 << 22) >> 32) & 1) || l->tgt == 0) {
        if (l->fE4 < 0.0f) {
            PlatVu0AddVector(a, D_0035BD40.chr[0]->pos, l->v20);
            PlatVu0SubVector(b, self->pos, D_0035BD40.chr[0]->pos);
        } else {
            PlatVu0AddVector(a, self->pos, l->v20);
            PlatVu0SubVector(b, D_0035BD40.chr[0]->pos, self->pos);
        }
    } else {
        if (l->fA0 < 0.0f) {
            PlatVu0AddVector(a, l->tgt->pos, l->v20);
            PlatVu0SubVector(b, self->pos, l->tgt->pos);
        } else {
            PlatVu0AddVector(a, self->pos, l->v20);
            PlatVu0SubVector(b, l->tgt->pos, self->pos);
        }
    }
    if (func_00119688(a) < 0 && func_00162a58(b) < 500.0f) l->w58 = 0;
}

/* func_00168b30 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { u8 pad[8]; f32 f8; u8 pad0c[4]; f32 f10; } Prm6C;
typedef struct {
    u8 pad[0x10]; f32 pos[4]; u8 pad20[0x10]; f32 v30[4]; u8 pad40[0x2C]; Prm6C *p6C; s32 w70; u8 pad74[0x1C];
    u64 w90; u8 pad98[0x28]; f32 vC0[4];
} Ent68;
typedef struct { u8 pad[4]; f32 f4; } Sub4;
typedef struct {
    u8 pad[4]; Sub4 *p4; u8 pad8[0x18]; f32 v20[4]; f32 f30; u8 pad34[4]; u64 w38; u8 pad40[0x18]; u32 w58;
    u8 pad5c[0x90]; f32 fEC; u8 padF0[0x30]; u8 x120[0x10];
} Wk68;
typedef struct { f32 p[4]; f32 d[4]; u8 pad[0x10]; s16 h; u8 pad32[2]; s32 x; u8 pad38[8]; } Ray68;
typedef struct { f32 x, y, z, w; } Hit68;
extern f32 D_002BBDFC;
s32 func_00105ad0(s32, s32, Hit68 *);
void func_00118608(Ray68 *);
#define func_0013dfb8 ((void (*)(Ent68 *, void *)) func_0013dfb8)
s32 func_00168b30(Ent68 *e, Wk68 *w, s32 flag, f32 *unused) {
    Ray68 r;
    f32 a[4];
    f32 b[4];
    f32 pad[8];
    Hit68 h[4];
    s32 n;
    f32 m, d;
    s32 i;
    if (e->w90 == 0) return 0;
    PlatVu0AddVector(r.p, e->pos, w->v20);
    PlatVu0OuterProduct(b, e->vC0, e->v30);
    PlatVu0OuterProduct(a, b, e->vC0);
    PlatVu0Normalize(a, a);
    PlatVu0ScaleVector(r.d, a, w->f30 + e->p6C->f8 * D_002BBDFC);
    func_00118608(&r);
    if (r.h < 0) goto fail;
    n = func_00105ad0(r.x, r.h, h);
    m = 0.0f;
    for (i = 0; i < n; i++) {
        d = e->pos[1] - h[i].y;
        if (d > 0.0f) d = 0.0f;
        d = -d;
        if (!(m < d)) d = m;
        m = d;
    }
    if (m < e->p6C->f10) {
        if (e->w70 == 8 || e->w70 == 21 || e->w70 == 2 || e->w70 == 24) goto fail;
        if (e->w70 == 17) goto z;
    } else goto z;
    if (flag == 0 && D_0057508C == 0 && w->fEC < w->p4->f4) w->w38 |= 0x80;
    if (w->w58 < 80) {
        if (e->w70 != 2) func_0013dfb8(e, w->x120);
        return 1;
    }
z:    return 0;
fail:
    return 0;
}
#undef func_0013dfb8

/* func_00168d20 (from hand/nostrict/text_00150000_s6_08.c). */
typedef struct {
    u8 pad0[0x38];
    u32 lo:8;
    u32 b8:1;
    u32 r9:23;
    u32 hi;
    u8 pad40[0x120 - 0x40];
    u8 x120[4];
} __attribute__((aligned(8))) Ent18_68d20;
typedef struct { u8 pad[0x10]; f32 pos[4]; f32 v20[4]; f32 v30[4]; u8 pad40[0x30]; s32 w70; u8 pad74[0xBC]; Ch130 *x130; u8 pad134[0x30]; s32 w164; } E8D;
typedef struct {
    s32 w0; void *p4; u8 pad8[0x30]; u64 w38; u8 pad40[0x50]; s32 w90; s32 w94; u8 pad98[0x18];
    f32 vB0[4]; u8 padC0[0x1C]; f32 fDC; u8 padE0[0x1C]; f32 fFC; u8 pad100[0x20]; f32 v120[4]; u8 pad130[0]; 
} W8D;
#define W8D_F12C(w) (*(f32 *)((u8 *)(w) + 0x12C))
extern f32 D_00575020[][4];
extern f32 D_0035B054;
f32 func_00162c20(f32 *);
#define G27C8 D_002E27C8
static inline s32 inl_chk(E8D *e) { if ((u16)(e->x130->h4C - 1) >= 2) return 0; if (G27C8.b8) return 1; return G27C8.b7 != 0; }
#define func_00168b30 ((s32 (*)(E8D *, W8D *, s32, f32 *)) func_00168b30)
#define func_001687d8 ((void (*)(void *, void *, s32)) func_001687d8)
void func_00168d20(E8D *e, W8D *w) {
    f32 v[4];
    f32 u[4];
    s32 lock;
    f32 y, k;
    s32 f;
    if ((D_002C5958 & 1) && w->w90 != 0 && w->w94 >= 0 && !((s32)w->w38 & 1)) {
        PlatVu0CopyVector(v, w->vB0);
        lock = 1;
        w->w38 &= ~0x400;
    } else {
        lock = 0;
        PlatVu0CopyVector(v, D_00575020[w->w0]);
        w->w38 |= 0x400;
    }
    if (func_00168b30(e, w, lock, v) != 0) return;
    PlatVu0SubVector(w->v120, v, e->pos);
    y = w->v120[1];
    w->v120[1] = 0.0f;
    func_00162c20(w->v120);
    func_001687d8(e, w, lock);
    k = !lock ? w->fFC : w->fDC;
    if (e->w70 == 17) {
        if (!(D_0035B054 < k)) return;
        PlatVu0CopyVector(u, e->v30);
        u[1] = 0.0f;
        PlatVu0Normalize(u, u);
        if (!(PlatVu0InnerProduct(w->v120, u) > 0.97999996f)) return;
        func_0013dfb8((Obj18 *)e, w->pad100 + 0x20);
        if ((*(u32 *)&D_002E27C8) >> 6 & 1) W8D_F12C(w) = 30.0f;
        else W8D_F12C(w) = 20.0f;
        return;
    }
    if (e->w70 != 0) return;
    if (D_002C5958 >> 5 & 1) {
        if (y < -300.0f || (y < 0.0f && e->w164 == 6)) func_00168618((Obj18 *)e, (Ent18_68d20 *)w);
        return;
    }
    f = inl_chk(e);
    if (!f) return;
    if (!(D_0035B054 < k)) return;
    PlatVu0CopyVector(u, e->v30);
    u[1] = 0.0f;
    PlatVu0Normalize(u, u);
    if (!(PlatVu0InnerProduct(w->v120, u) > 0.97999996f)) return;
    func_00168618((Obj18 *)e, (Ent18_68d20 *)w);
    W8D_F12C(w) = 30.0f;
}
#undef func_00168b30
#undef func_001687d8
#undef W8D_F12C
#undef G27C8

/* func_00169008 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { u8 pad[0x10]; f32 pos[4]; f32 v20[4]; f32 v30[4]; u8 pad40[0x30]; s32 w70; } Ent69;
typedef struct { u8 pad[4]; f32 f4; } Sub69;
typedef struct {
    s32 w0; Sub69 *p4; u8 pad8[0x30]; u64 w38; u8 pad40[0x28]; f32 f68; u8 pad6c[0x24]; s32 w90; s32 w94; u8 pad98[0x18];
    f32 vB0[4]; u8 padC0[0x60]; f32 v120[4];
} Wk69;
extern Prm35AE80 D_0035AE80;
void func_0014f658(void *, s32);
#define func_001687d8 ((void (*)(void *, void *, s32)) func_001687d8)
void func_00169008(Ent69 *e, Wk69 *w) {
    f32 v[4];
    f32 u[4];
    s32 lock;
    f32 y, len, k;
    if ((D_002C5958 & 1) && w->w90 != 0 && w->w94 >= 0 && !((s32)w->w38 & 1)) {
        PlatVu0CopyVector(v, w->vB0);
        lock = 1;
        w->w38 &= ~0x400;
    } else {
        lock = 0;
        PlatVu0CopyVector(v, D_00575020[w->w0]);
        w->w38 |= 0x400;
    }
    if (func_00168b30((Ent68 *)e, (Wk68 *)w, lock, v) != 0) return;
    PlatVu0SubVector(w->v120, v, e->pos);
    y = w->v120[1];
    w->v120[1] = 0.0f;
    k = -10.0f;
    len = func_00162c20(w->v120);
    if (!(y < -100.0f)) {
        k = 10.0f;
        if (!(100.0f < y)) k = 0.0f;
    }
    func_001687d8(e, w, lock);
    w->v120[1] = k;
    if (k == 0.0f && D_0035AE80.f1D4 < len && (((*(u32 *)&D_002E27C8) >> 6) & 1)) {
        PlatVu0CopyVector(u, e->v30);
        u[1] = 0.0f;
        PlatVu0Normalize(u, u);
        if (PlatVu0InnerProduct(w->v120, u) > 0.97999996f) {
            func_0014f658(e, 25);
            w->f68 = D_0035AE80.f1D8;
        }
    }
}
#undef func_001687d8

/* func_00169210 (from hand/nostrict/text_00160000_h60.c). */
void func_0014c448(Ent69 *);
#define func_001687d8 ((void (*)(void *, void *, s32)) func_001687d8)
void func_00169210(Ent69 *e, Wk69 *w) {
    f32 v[4];
    s32 lock;
    f32 y, len, k;
    if ((D_002C5958 & 1) && w->w90 != 0 && w->w94 >= 0 && !((s32)w->w38 & 1)) {
        PlatVu0CopyVector(v, w->vB0);
        lock = 1;
        w->w38 &= ~0x400;
    } else {
        lock = 0;
        PlatVu0CopyVector(v, D_00575020[w->w0]);
        w->w38 |= 0x400;
    }
    if (func_00168b30((Ent68 *)e, (Wk68 *)w, lock, v) != 0) return;
    PlatVu0SubVector(w->v120, v, e->pos);
    y = w->v120[1];
    w->v120[1] = 0.0f;
    k = -10.0f;
    len = func_00162c20(w->v120);
    if (!(y < -100.0f)) {
        k = 10.0f;
        if (!(100.0f < y)) k = 0.0f;
    }
    func_001687d8(e, w, lock);
    w->v120[1] = k;
    if (e->w70 == 21) {
        if (len < w->p4->f4 || PlatVu0InnerProduct(e->v20, w->v120) <= 0.0f) func_0014c448(e);
    }
}
#undef func_001687d8

/* func_001693c8 (from hand/nostrict/text_00160000_h60.c). */
typedef struct {
    u8 pad0[0x38]; u64 w38; u8 pad40[0xB0]; f32 vF0[4]; u8 pad100[0x20]; f32 v120[4]; f32 f130;
} Wk6B;
s32 func_00169688();
#define func_00168d20 ((void (*)(Ent69 *, Wk6B *)) func_00168d20)
#define func_00169688 ((s32 (*)(Ent69 *, Wk6B *)) func_00169688)
void func_001693c8(Ent69 *e, Wk6B *w) {
    f32 v[4];
    switch (e->w70) {
    case 24:
        func_00169008(e, w);
        break;
    case 8:
    case 21:
    case 4:
        func_00169210(e, w);
        break;
    default:
        if (func_00169688(e, w)) return;
        func_00168d20(e, w);
        break;
    }
    if (w->v120[1] == 0.0f && w->v120[3] == 0.0f) {
        if ((s32)((s64)(w->w38 << 22) >> 32) & 1) {
            w->w38 |= 0x80;
            PlatVu0ScaleVector(v, w->vF0, 0.39999998f);
            PlatVu0AddVector(v, v, e->v30);
            v[1] = 0.0f;
            PlatVu0Normalize(w->v120, v);
        }
    } else {
        w->w38 &= ~0x80;
    }
}
#undef func_00168d20
#undef func_00169688

/* func_00169510 (from hand/nostrict/text_00150000_s6_08.c). */
typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0xF0]; s32 w164; } Ent6C;
typedef struct { u8 pad[0x4C]; s32 w4C; u8 pad50[0x40]; void *p90; } Wk6C;
s32 func_00122ff8(void *);
s32 func_00123368(void *);
static inline s32 inl95_1890(Ent6C *a, Wk6C *b, s32 v) {
    s32 w = v;
    if (w < 3 && v >= 0) return 1;
    return v == b->w4C;
}
static inline s32 inl95_18b8(Ent6C *a, Wk6C *b, s32 v) {
    s32 w = v;
    if (v < 124 && w >= 117) return 1;
    return v == b->w4C;
}
static inline s32 inl95_18e0(Ent6C *a, Wk6C *b, s32 v) {
    s32 w = v;
    if (v >= 0 && (v < 3 || (v < 131 && w >= 124))) return 1;
    return v == b->w4C;
}
static inline s32 inl95_ok(Ent6C *e, Wk6C *w, u32 fl) {
    s32 ok;
    switch (e->w70) {
    case 0:
        if (!inl95_1890(e, w, e->w164)) { ok = 0; break; }
        if (fl & 6) { ok = 0; break; }
        goto yes;
    case 8:
        if (!inl95_18b8(e, w, e->w164)) { ok = 0; break; }
        if (fl & 3) { ok = 0; break; }
        goto yes;
    case 24:
        if (!inl95_18e0(e, w, e->w164)) { ok = 0; break; }
        if (fl & 5) { ok = 0; break; }
        goto yes;
    default:
        ok = 0;
        break;
    }
    goto out;
yes:
    ok = 1;
out:
    return ok;
}
s32 func_00169510(Ent6C *e, Wk6C *w, s32 flag) {
    s32 r;
    if (!inl95_ok(e, w, flag)) return 0;
    if (w->p90 == 0) return 0;
    if (!func_00122ff8(w->p90)) return 0;
    return func_00123368(w->p90) != 0;
}

/* func_00169688 (hand/nostrict), rodata jtbl_0048E870 (verify with wqb03_rr.py 0048E870), s11w64. Natural, no flagged code.
   From session9 w3's 4w draft; new: case 10 as two paths that each load p = o->x148 and jump to one
   shared block: `if (!(D & 1)) { p = o->x148; if (hi & 1) goto c10b; goto r1; } p = o->x148; c10b: B; r1: return 1;`
   The hi path's `goto c10b` is not a jump to the next insn (the D path's p load sits between), so it
   survives jump2 and reorg fills it from c10b (`b L+4; ld v1,48(a2)`); the bnez to the D path gets the hi
   path's p load in its slot and is redirected past the duplicate load. r1 sits after B's fall-through, so
   jump.c does not hoist `li v0,1` above the hi test (the test keeps v0). */
/* func_00169688 (from hand/nostrict/text_00160000_s11_w64.c). */
typedef struct { f32 x, y, z, w; } Vec;
typedef struct { f32 a, b, c; } Lim;
typedef struct {
    u8 pad0[0x30];
    union { u64 x; struct { u64 lo:32; u64 hi:32; } b; } x30;
    u8 pad38[0xc0 - 0x38];
    Vec xc0;
} O148;
typedef struct {
    u8 pad0[8];
    s32 x8;
    u8 padc[4];
    Vec x10;
    u8 pad20[0x70 - 0x20];
    s32 x70;
    u8 pad74[0x90 - 0x74];
    s64 x90;
    u8 pad98[0x148 - 0x98];
    O148 *x148;
    u8 pad14c[0x3cc - 0x14c];
    f32 x3cc;
} Obj;
typedef struct {
    s32 x0;
    Lim *x4;
    u8 pad8[0x38 - 8];
    union { s64 x; s32 i; } x38;
    u8 pad40[0x58 - 0x40];
    s32 x58;
    u32 x5c;
    u8 pad60[0x68 - 0x60];
    f32 x68;
    u8 pad6c[0x90 - 0x6c];
    s32 x90;
    s32 x94;
    u8 pad98[0xb0 - 0x98];
    Vec xb0;
    u8 padc0[0x120 - 0xc0];
    Vec x120;
} Wk;
void func_0014cce0(Obj *, f32);
s32 func_00162a88(Vec *);
void func_00171790(Obj *, Wk *);
#define GETDIR(o, w, v, r) \
    if ((D_002C5958 & 1) && w->x90 != 0 && w->x94 >= 0 && !(w->x38.i & 1)) { \
        PlatVu0CopyVector(v, &w->xb0); \
        r = 1; \
        w->x38.x &= ~0x400; \
    } else { \
        PlatVu0CopyVector(v, &D_00575020[w->x0]); \
        r = 0; \
        w->x38.x |= 0x400; \
    } \
    PlatVu0SubVector(v, v, &o->x10);
static inline void Tail(Obj *o, Wk *w) {
    if (o->x70 != 2) {
        func_0013dfb8(o, &w->x120);
    }
}
#define D_002C5958 (*(s32 (*)) &D_002C5958)
#define D_00575020 ((Vec *) D_00575020)
#define func_0013dfb8 ((void (*)(Obj *, Vec *)) func_0013dfb8)
#define func_0014f658 ((void (*)(Obj *, s32)) func_0014f658)
#define func_00162c20 ((f32 (*)(Vec *)) func_00162c20)
#define func_00168618 ((s32 (*)(Obj *, Wk *)) func_00168618)
/* func_00169688 (hand/nostrict), rodata jtbl_0048E870 (verify with wqb03_rr.py 0048E870), s11w64. Natural, no flagged code.
   From session9 w3's 4w draft; new: case 10 as two paths that each load p = o->x148 and jump to one
   shared block: `if (!(D & 1)) { p = o->x148; if (hi & 1) goto c10b; goto r1; } p = o->x148; c10b: B; r1: return 1;`
   The hi path's `goto c10b` is not a jump to the next insn (the D path's p load sits between), so it
   survives jump2 and reorg fills it from c10b (`b L+4; ld v1,48(a2)`); the bnez to the D path gets the hi
   path's p load in its slot and is redirected past the duplicate load. r1 sits after B's fall-through, so
   jump.c does not hoist `li v0,1` above the hi test (the test keeps v0). */
s32 func_00169688(Obj *o, Wk *w) {
    Vec v, t;
    s32 r;
    f32 d, e, len;
    Vec *q;
    O148 *p;

    switch (o->x70) {
    case 13:
        if (o->x8 != 0 && o->x8 == D_0035BD40.i) {
            Tail(o, w);
            return 1;
        }
        GETDIR(o, w, &v, r);
        w->x120.x = w->x120.z = 0.0f;
        w->x120.w = 10.0f;
        if (v.y < -40.0f) {
            w->x120.y = -10.0f;
        } else if (v.y > 40.0f) {
            if (v.y > 200.0f) {
                w->x120.y = 20.0f;
            } else {
                w->x120.y = 10.0f;
            }
        } else if (D_002C5958 & 1) {
            if (v.y < 0.0f) {
            m10:
                w->x120.y = -10.0f;
            } else {
                w->x38.x |= 0x40000;
                w->x58++;
                Tail(o, w);
            }
        } else {
            w->x120.y = 0.0f;
        }
        return 1;
    case 26:
        Tail(o, w);
        return 1;
    case 10:
        GETDIR(o, w, &v, r);
        w->x120.x = w->x120.z = 0.0f;
        w->x120.w = 10.0f;
        if (v.y < 0.0f) {
            w->x120.y = -10.0f;
        } else {
            w->x120.y = 10.0f;
        }
        if (!(D_002C5958 & 1)) {
            p = o->x148;
            if ((s32)p->x30.b.hi & 1) {
                goto c10b;
            }
            goto r1;
        }
        p = o->x148;
    c10b:
        p->x30.x &= ~0x100000000;
        w->x38.x |= 0x40000;
        w->x58++;
        Tail(o, w);
    r1:
        return 1;
    case 15:
        GETDIR(o, w, &v, r);
        w->x120.y = w->x120.x = w->x120.z = 0.0f;
        w->x120.w = 10.0f;
        if (v.y < 0.0f) {
            goto m10;
        }
        Tail(o, w);
        return 1;
    case 18:
        GETDIR(o, w, &v, r);
        d = PlatVu0InnerProduct(&o->x148->xc0, &v);
        PlatVu0ScaleVector(&t, &o->x148->xc0, d);
        PlatVu0SubVector(&v, &v, &t);
        e = PlatVu0InnerProduct(&t, &t);
        if (PlatVu0InnerProduct(&v, &v) < e) {
            if (o->x70 != 2) {
                func_0013dfb8(o, &w->x120);
            }
            if (d < 0.0f) {
                w->x58++;
            }
            return 1;
        }
        if (v.y > 0.0f && func_00162a88(&v)) {
            Tail(o, w);
            return 1;
        }
        q = &w->x120;
        v.y = 0.0f;
        PlatVu0CopyVector(q, &v);
        len = func_00162c20(q);
        switch (r) {
        case 0:
            if ((s32)(w->x38.x >> 7) & 1) {
                if (w->x4->a < len) {
                    w->x120.w = 10.0f;
                } else {
                    w->x120.w = 0.0f;
                }
            } else if (w->x38.i & 1) {
                w->x120.w = 20.0f;
            } else if (len <= w->x4->c) {
                w->x120.w = 0.0f;
            } else if (w->x4->b <= len) {
                w->x120.w = 20.0f;
            } else {
                w->x120.w = 10.0f;
            }
            break;
        case 1:
            if (w->x4->b <= len) {
                w->x120.w = 20.0f;
            } else {
                w->x120.w = 10.0f;
            }
            break;
        }
        return 1;
    case 2:
        if (func_00168618(o, w)) {
            return 1;
        }
        if (++w->x5c >= 91) {
            func_0014cce0(o, 20.0f);
            o->x3cc = 20.0f;
            w->x5c = 0;
            w->x58 += 40;
            return 1;
        }
        if ((s32)(w->x38.x >> 18) & 1) {
            return 1;
        }
        break;
    case 25:
        { s32 *pd = &D_002C5958;
        if ((*pd & 1) && w->x90 != 0 && w->x94 >= 0 && !(w->x38.i & 1)) {
            func_00171790(o, w);
        } }
        GETDIR(o, w, &v, r);
        v.y = 0.0f;
        v.w = func_00162c20(&v);
        PlatVu0CopyVector(&w->x120, &v);
        w->x120.w = 30.0f;
        if (o->x90 != 0 || w->x68 <= 0.0f || v.w < 60.0f) {
            func_0014f658(o, 24);
        }
        return 1;
    }
    return 0;
}
#undef D_002C5958
#undef D_00575020
#undef func_0013dfb8
#undef func_0014f658
#undef func_00162c20
#undef func_00168618
#undef GETDIR

/* func_0016a3f8 (from hand/nostrict/text_00160000_c03.c). */
typedef struct C03Act_6a3f8 C03Act_6a3f8;
typedef struct {
    u8 pad00[0x10];
    f32 pos[4];          /* 0x10 */
    u8 pad20[0x70 - 0x20];
    s32 w70;             /* 0x70 */
    u8 pad74[0x130 - 0x74];
    C03Ch130 *p130;      /* 0x130 */
    u8 pad134[0x164 - 0x134];
    s32 w164;            /* 0x164 */
    u8 pad168[0x370 - 0x168];
    u64 f370;            /* 0x370 */
} C03Chr_6a3f8;
typedef struct { C03Chr_6a3f8 *p; s32 i; } C03Tgt_6a3f8;
typedef struct C03AW_6a3f8 {
    u8 pad00[0x18];
    s32 n18;             /* 0x18 */
    C03Act_6a3f8 *p1C;         /* 0x1C */
    u8 pad20[0x38 - 0x20];
    u64 w38;             /* 0x38 */
    u8 pad40[4];
    void (*cb44)(C03Chr_6a3f8 *, struct C03AW_6a3f8 *);   /* 0x44 */
    u8 pad48[4];
    s32 w4C;             /* 0x4C */
    u32 w50;             /* 0x50 */
    s32 w54;             /* 0x54 */
    u8 pad58[0x64 - 0x58];
    f32 f64;             /* 0x64 */
    u8 pad68[0x74 - 0x68];
    C03Act_6a3f8 *p74;         /* 0x74 */
    s32 n78;             /* 0x78 */
    C03Act_6a3f8 *hist[2];     /* 0x7C */
    u8 pad84[0x90 - 0x84];
    C03Tgt_6a3f8 t90;          /* 0x90 */
    C03Chr_6a3f8 *p98;         /* 0x98 */
} C03AW_6a3f8;
struct C03Act_6a3f8 {
    s32 x0;
    u32 fl;
    s32 (*cb)(C03Chr_6a3f8 *, C03AW_6a3f8 *, C03Act_6a3f8 *, s32);
    s32 pad;
};
extern s32 D_0035BCA8[];
extern C03Act *D_00575328[];
extern s32 D_0035BCB0;
s32 func_00170dd8(u16, s32);
u32 func_001627e8(s32);
void func_00171b18(C03Chr_6a3f8 *, C03AW_6a3f8 *);
static inline s32 inl_1890(C03Chr_6a3f8 *a, C03AW_6a3f8 *b, s32 v) {
    s32 w = v;
    if (w < 3 && v >= 0) return 1;
    return v == b->w4C;
}
static inline s32 inl_18b8(C03Chr_6a3f8 *a, C03AW_6a3f8 *b, s32 v) {
    s32 w = v;
    if (v < 124 && w >= 117) return 1;
    return v == b->w4C;
}
static inline s32 inl_18e0(C03Chr_6a3f8 *a, C03AW_6a3f8 *b, s32 v) {
    s32 w = v;
    if (v >= 0 && (v < 3 || (v < 131 && w >= 124))) return 1;
    return v == b->w4C;
}
static inline s32 inl_ok(C03Chr_6a3f8 *e, C03AW_6a3f8 *w, u32 fl) {
    s32 ok;
    switch (e->w70) {
    case 0:
        if (!inl_1890(e, w, e->w164)) { ok = 0; break; }
        if (fl & 6) { ok = 0; break; }
        goto yes;
    case 8:
        if (!inl_18b8(e, w, e->w164)) { ok = 0; break; }
        if (fl & 3) { ok = 0; break; }
        goto yes;
    case 24:
        if (!inl_18e0(e, w, e->w164)) { ok = 0; break; }
        if (fl & 5) { ok = 0; break; }
        goto yes;
    default:
        ok = 0;
        break;
    }
    goto out;
yes:
    ok = 1;
out:
    return ok;
}
static inline s32 inl_t(C03Chr_6a3f8 *e, C03AW_6a3f8 *w) {
    s32 t = -1;
    if (w->n78 > 0 && w->hist[0]) t = func_00170dd8(e->p130->h4C, w->hist[0]->x0);
    return t;
}
extern C03Act_6a3f8 *D_00575328_6a3f8[] __asm__("D_00575328");
#define D_00575328 D_00575328_6a3f8
s32 func_0016a3f8(C03Chr_6a3f8 *e, C03AW_6a3f8 *w) {
    C03Act_6a3f8 *last;
    s32 again;
    C03Act_6a3f8 *sel;
    C03Act_6a3f8 *a;
    C03Act_6a3f8 *cur;
    u32 m;
    s32 n, i, j, kv, t, r;

    cur = w->p74;
    if (cur && (s32)((s64)(w->w38 << 31) >> 32) & 1) {
        w->w54++;
        if (inl_ok(e, w, cur->fl)) {
            if (cur->cb(e, w, cur, 1)) return w->p74->cb(e, w, w->p74, 2);
        }
        w->w38 &= ~2;
    }
    func_00171b18(e, w);
    w->w38 &= ~0x20000;
    w->w54 = 0;
    if (w->w50 >= 2) return 0;
    if (w->n78 >= 2) {
        for (j = 1; j < 2; j++) if (w->hist[0] != w->hist[j]) break;
        if (j >= 2) { last = w->hist[0]; goto got; }
    }
    last = 0;
got:
    sel = 0;
    again = 0;
    for (m = 0; m < 2; m++) {
        kv = D_0035BCA8[m];
        n = 0;
        if (kv == 1) {
            t = inl_t(e, w);
            if (t == 1) {
                if (!(func_001627e8(100) & 7)) again = t;
                break;
            }
        }
        for (i = 0; i < w->n18; i++) {
            a = &w->p1C[i];
            if (func_00170dd8(e->p130->h4C, a->x0) != kv) continue;
            if (!inl_ok(e, w, a->fl)) continue;
            if (a->cb && a->cb(e, w, a, 1)) {
                if (a != last) {
                    if (n < 128) D_00575328[n++] = a;
                } else again = 1;
            }
        }
        if (n > 0) {
            { C03Act_6a3f8 **tb = D_00575328; i = func_001627e8(n << 12) >> 12; sel = tb[i]; }
            break;
        }
    }
    if (!sel) {
        if (again || !(func_001627e8(100) & 0xF)) {
            kv = D_0035BCB0;
            n = 0;
            for (i = 0; i < w->n18; i++) {
                a = &w->p1C[i];
                if (func_00170dd8(e->p130->h4C, a->x0) != kv) continue;
                if (!inl_ok(e, w, a->fl)) continue;
                if (a->cb && a->cb(e, w, a, 1) && a != last && n < 128) D_00575328[n++] = a;
            }
            if (n > 0) sel = D_00575328[func_001627e8(n << 12) >> 12];

        }
    }
    if (sel) {
        if (w->cb44) {
            w->cb44(e, w);
            w->cb44 = 0;
        }
        w->w50++;
        r = sel->cb(e, w, sel, 2);
        for (j = 1; j > 0; j--) w->hist[j] = w->hist[j - 1];
        w->hist[0] = sel;
        w->p74 = sel;
        if (++w->n78 >= 3) w->n78 = 2;
        return r;
    } else {
        r = 0;
        w->n78 = w->n78 - 1 < 0 ? 0 : w->n78 - 1;
    }
    return r;
}
#undef D_00575328

/* func_0016abc0 (from hand/nostrict/text_00150000_s6_08.c). */
typedef struct { u8 pad[0xB8]; u32 xB8; f32 fBC; u8 padC0[0xCC - 0xC0]; f32 fCC; } PrmB1;
extern f32 D_0048E94C;
C03Chr *func_00123158(C03Chr *, C03Chr *);
s32 func_00141200(C03Chr *, s32);
s32 func_0012ee70(C03Chr *, s32);
s32 func_0012f040(C03Chr *, s32);
void func_0012ec60(C03Chr *, s32, f32 *);
static inline s32 inl_1890_6abc0(C03Chr *a, C03AW *b, s32 v) {
    s32 w = v;
    if (w < 3 && v >= 0) return 1;
    return v == b->w4C;
}
static inline s32 inl_18b8_6abc0(C03Chr *a, C03AW *b, s32 v) {
    s32 w = v;
    if (v < 124 && w >= 117) return 1;
    return v == b->w4C;
}
static inline s32 inl_18e0_6abc0(C03Chr *a, C03AW *b, s32 v) {
    s32 w = v;
    if (v >= 0 && (v < 3 || (v < 131 && w >= 124))) return 1;
    return v == b->w4C;
}
static inline s32 inl_ok_6abc0(C03Chr *e, C03AW *w, u32 fl) {
    s32 ok;
    switch (e->w70) {
    case 0:
        if (!inl_1890_6abc0(e, w, e->w164)) { ok = 0; break; }
        if (fl & 6) { ok = 0; break; }
        goto yes;
    case 8:
        if (!inl_18b8_6abc0(e, w, e->w164)) { ok = 0; break; }
        if (fl & 3) { ok = 0; break; }
        goto yes;
    case 24:
        if (!inl_18e0_6abc0(e, w, e->w164)) { ok = 0; break; }
        if (fl & 5) { ok = 0; break; }
        goto yes;
    default:
        ok = 0;
        break;
    }
    goto out;
yes:
    ok = 1;
out:
    return ok;
}
static inline f32 inl_d(C03Chr *p, s32 j, C03Chr *tg) {
    f32 v[4];
    f32 d2[4];
    func_0012ec60(p, j, v);
    PlatVu0SubVector(d2, v, tg->pos);
    return PlatVu0InnerProduct(d2, d2);
}
#define D_0035AE80 (*(PrmB1 (*)) &D_0035AE80)
#define func_00171b18 ((void (*)(C03Chr *, C03AW *)) func_00171b18)
s32 func_0016abc0(C03Chr *e, C03AW *w) {
    C03Tgt best;
    C03Tgt *bp;
    s32 r;
    C03Act *sel;
    C03Act *a;
    C03Chr *tg, *p;
    u32 m;
    s32 kv, n, i, j;
    f32 lim, f, d;

    r = 0;
    sel = 0;
    w->w38 |= 4;
    for (m = 0; m < 3; m++) {
        kv = D_0035BCA8[m];
        n = 0;
        for (i = 0; i < w->n18; i++) {
            a = &w->p1C[i];
            if (!(a->fl & 0x100)) continue;
            if (func_00170dd8(e->p130->h4C, a->x0) != kv) continue;
            if (!inl_ok_6abc0(e, w, a->fl)) continue;
            if (a->cb && a->cb(e, w, a, 1) && n < 128) D_00575328[n++] = a;
        }
        if (n > 0) {
            sel = D_00575328[func_001627e8(n << 12) >> 12];
            goto found;
        }
    }
    for (m = 0; m < 3; m++) {
        kv = D_0035BCA8[m];
        n = 0;
        for (i = 0; i < w->n18; i++) {
            a = &w->p1C[i];
            if (!(a->fl & 0x200)) continue;
            if (func_00170dd8(e->p130->h4C, a->x0) != kv) continue;
            if (!inl_ok_6abc0(e, w, a->fl)) continue;
            if (a->cb && a->cb(e, w, a, 1) && n < 128) D_00575328[n++] = a;
        }
        if (n > 0) {
            sel = D_00575328[func_001627e8(n << 12) >> 12];
            goto found;
        }
    }
    tg = w->p98;
    if (e != tg) {
        bp = &best;
        bp->p = 0;
        bp->i = -1;
        f = D_0035AE80.fCC;
        if (f <= 0.0f) lim = D_0048E94C;
        else lim = f * f;
        p = 0;
        while ((p = func_00123158(tg, p)) != 0) {
            if (((s32)(p->f370 >> 37) & 3) != 2) continue;
            if (!func_00123368(p)) continue;
            if (func_00141200(p, 0)) continue;
            for (j = -1; (j = func_0012ee70(p, j)) >= 0;) {
                                if (!func_0012f040(p, j)) continue;
                d = inl_d(p, j, tg);
                if (d < lim) {
                    bp->p = p;
                    lim = d;
                    bp->i = j;
                }
            }
        }
        if (best.p != 0 && best.i >= 0) {
            w->w38 |= 0x10;
            w->f64 = D_0035AE80.fBC;
            w->t90 = best;
        }
    }
found:
    if (sel) {
        if (w->cb44) {
            w->cb44(e, w);
            w->cb44 = 0;
        }
        func_00171b18(e, w);
        w->w38 &= ~2;
        r = sel->cb(e, w, sel, 2);
    }
    return r;
}
#undef D_0035AE80
#undef func_00171b18

/* func_0016b1f0 (from hand/nostrict/text_00150000_s6_08.c). */
extern C03Act D_0035BCB8;
s32 func_00171c80(C03Chr *, C03AW *, C03Act *, s32);
static inline s32 inl_1890_6b1f0(C03Chr *a, C03AW *b, s32 v) {
    s32 w = v;
    if (w < 3 && v >= 0) return 1;
    return v == b->w4C;
}
static inline s32 inl_18b8_6b1f0(C03Chr *a, C03AW *b, s32 v) {
    s32 w = v;
    if (v < 124 && w >= 117) return 1;
    return v == b->w4C;
}
static inline s32 inl_18e0_6b1f0(C03Chr *a, C03AW *b, s32 v) {
    s32 w = v;
    if (v >= 0 && (v < 3 || (v < 131 && w >= 124))) return 1;
    return v == b->w4C;
}
static inline s32 inl_ok_6b1f0(C03Chr *e, C03AW *w, u32 fl) {
    s32 ok;
    switch (e->w70) {
    case 0:
        if (!inl_1890_6b1f0(e, w, e->w164)) { ok = 0; break; }
        if (fl & 6) { ok = 0; break; }
        goto yes;
    case 8:
        if (!inl_18b8_6b1f0(e, w, e->w164)) { ok = 0; break; }
        if (fl & 3) { ok = 0; break; }
        goto yes;
    case 24:
        if (!inl_18e0_6b1f0(e, w, e->w164)) { ok = 0; break; }
        if (fl & 5) { ok = 0; break; }
        goto yes;
    default:
        ok = 0;
        break;
    }
    goto out;
yes:
    ok = 1;
out:
    return ok;
}
#define D_0035AE80 (*(PrmB1 (*)) &D_0035AE80)
#define func_00169210 ((void (*)(C03Chr *, C03AW *)) func_00169210)
#define func_00169688 ((s32 (*)(C03Chr *, C03AW *)) func_00169688)
s32 func_0016b1f0(C03Chr *e, C03AW *w) {
    C03Act *sel;
    C03Act *a;
    s32 i, n;
    C03Act *d;
    PrmB1 *p;
    if (inl_ok_6b1f0(e, w, D_0035BCB8.fl)) {
        d = &D_0035BCB8;
        if (func_00171c80(e, w, d, 0)) {
            p = &D_0035AE80;
            if ((func_001627e8(0x1000) >> 4) < p->xB8) {
                sel = d;
                if (w->cb44) {
                    w->cb44(e, w);
                    w->cb44 = 0;
                }
                func_00171c80(e, w, sel, 2);
                goto done;
            }
        }
    }
    {
        sel = 0;
        n = 0;
        for (i = 0; i < w->n18; i++) {
            a = &w->p1C[i];
            if (!(a->fl & 0xc00)) continue;
            if (!inl_ok_6b1f0(e, w, a->fl)) continue;
            if (a->cb && a->cb(e, w, a, 0) && n < 128) D_00575328[n++] = a;
        }
        if (n <= 0) {
            sel = 0;
            if (e->w70 == 21) {
                func_00169210(e, w);
            } else if (!func_00169688(e, w)) {
                if (((s32)w->w38 & 1) || w->t90.p == 0) {
                    func_001693c8(e, w);
                } else {
                    PlatVu0CopyVector(w->v120, e->v30);
                    w->v120[1] = w->f12C = 0.0f;
                }
            }
        } else {
            sel = D_00575328[func_001627e8(n << 12) >> 12];
            if (w->cb44) {
                w->cb44(e, w);
                w->cb44 = 0;
            }
            sel->cb(e, w, sel, 2);
        }
    }
done:
    w->p74 = sel;
    w->w50 = 0;
    return 1;
}
#undef D_0035AE80
#undef func_00169210
#undef func_00169688

/* func_0016b670 (from hand/nostrict/text_00160000_c04.c). */
typedef struct { s16 h0; s16 pad2; s32 w4; f32 f8; } Res8;
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
extern void *D_00574FC0[20];
extern void func_00130340(ObjB6 *, s32, f32);
extern Task0C *func_00130578(ObjB6 *, s32, f32);
extern void func_001376e8(void *, f32 *);
extern Res8 *func_0013dbe0(ObjB6 *, s32);
extern Res8 *func_0013dc10(ObjB6 *, s32);
extern s32 func_00141288(ObjB6 *, s32);
extern void func_001412f8(ObjB6 *, s32);
extern Res30 *func_001477c8(s32);
extern void func_00171f38(void);
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
#define func_0012f040 ((s32 (*)(void *, s32)) func_0012f040)
#define func_0012ee70 ((s32 (*)(void *, s32)) func_0012ee70)
#define func_0014cce0 ((void (*)(ObjB6 *, f32)) func_0014cce0)
#define func_00169510 ((s32 (*)(ObjB6 *, WkB6 *, s32)) func_00169510)
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
        PlatVu0CopyVector(w->v120, w->vD0);
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
#undef func_0012f040
#undef func_0012ee70
#undef func_0014cce0
#undef func_00169510

/* func_0016bb68 (from hand/nostrict/text_00160000_s8_w10.c). */
typedef EntB_35BD40 EntB;
typedef struct { u8 pad[0x21]; u8 n; u8 ids[1]; } ItB;
typedef struct { u8 pad[0xc8]; ItB *xc8; } SubB;
typedef struct { u32 x0; u8 pad4[0x68]; SubB *x6c; s32 w70; } ObjB;
typedef union { u64 x; struct { u64 lo:40; u64 id:16; u64 hi:8; } b; struct { u32 lo; u8 b4; } c; } BfB;
typedef struct {
    u32 x0; u8 pad4[0x7c]; BfB w80; EntB *x88; s32 x8c; u8 pad90[8]; EntB *x98;
} WkB;
typedef struct { u8 pad[0x78]; u8 x78; u8 pad79[3]; u8 x7c; } PrmB;
typedef struct { u8 pad[4]; u32 x4; } ResB;
extern s32 D_0035BCC8[2][5];
s32 func_0012ca98(void);
void func_00157a30(ObjB *, s32, void *);
ResB *func_00147840(u16);
static inline s32 inl_hp(EntB *e, s32 k) {
    if (e->x0 & 0x200) return 0;
    if (e->x6c->x40 * k < e->x6c->x3c * 255) return 0; return 1;
}
static inline s32 inl_has(ObjB *o, s32 id) {
    ItB *p; s32 n;
    s32 i;
    if (!func_0012ca98()) return 0;
    switch (o->w70) {
    case 0:
    case 8:
    case 24:
        p = o->x6c->xc8;
        for (i = 0; i < p->n; i++) {
            if (p->ids[i] == id) return 1;
        }
    }
    return 0;
}
#define D_0035AE80 (*(PrmB (*)) &D_0035AE80)
s32 func_0016bb68(ObjB *o, WkB *w, s32 unused, s32 mode) {
    EntB *arr[3];
    s32 cnt = 0; s32 k;
    EntB *t, *e; s32 r;
    s32 i, id;
    
    arr[0] = (EntB *)o;
    arr[1] = D_0035BD40.entB[0];
    arr[2] = D_0035BD40.entB[w->x0 ^ 3];
    e = w->x98;
    if (e != 0 && inl_hp(e, D_0035AE80.x78)) t = e;
    else t = 0;
    for (i = 0; i < 3; i++) {
        if (arr[i] != 0 && inl_hp(arr[i], D_0035AE80.x78)) {
            if (t == 0) t = arr[i];
            cnt++;
        }
    }
    switch (mode) {
    case 1:
        if (cnt == 0) return 0;
        for (i = 0; i < 5; i++) {
            id = D_0035BCC8[0][i];
            r = inl_has(o, id); if (r) break;
        }
        if (i >= 5) return 0; break;
    case 2:
        w->w80.c.b4 = 3;
        w->x8c = 0;
        w->x88 = t;
        if (t != 0 && (EntB *)o != t && e == t) func_00157a30(o, 26, e);
        if (cnt >= 2) {
            for (i = 0; i < 5; i++) {
                r = inl_has(o, D_0035BCC8[1][i]);
                if (r) {
                    w->w80.b.id = D_0035BCC8[1][i];
                    break;
                }
            }
        } else {
            for (i = 0; i < 5; i++) {
                r = inl_has(o, D_0035BCC8[0][i]);
                if (r) {
                    w->w80.b.id = D_0035BCC8[0][i];
                    break;
                }
            }
        }
        if (func_00147840(w->w80.b.id)->x4 & 1) {
            w->x88 = 0;
            w->x8c = -1;
        }
    }
    return 1;
}
#undef D_0035AE80

/* func_0016bfe8 (from hand/nostrict/text_00160000_s8_w10.c). */
extern s32 D_0035BCF0[2][4];
static inline s32 inl_hp2(EntB *e, s32 k) {
    if (e->x0 & 0x200) return 0;
    if (e->x6c->x48 * k < e->x6c->x44 * 255) return 0; return 1;
}
#define D_0035AE80 (*(PrmB (*)) &D_0035AE80)
s32 func_0016bfe8(ObjB *o, WkB *w, s32 unused, s32 mode) {
    EntB *arr[3];
    s32 cnt = 0; s32 k;
    EntB *t, *e; s32 r;
    s32 i, id;
    
    arr[0] = (EntB *)o;
    arr[1] = D_0035BD40.entB[0];
    arr[2] = D_0035BD40.entB[w->x0 ^ 3];
    e = w->x98;
    if (e != 0 && inl_hp2(e, D_0035AE80.x7c)) t = e;
    else t = 0;
    for (i = 0; i < 3; i++) {
        if (arr[i] != 0 && inl_hp2(arr[i], D_0035AE80.x7c)) {
            if (cnt == 0) t = arr[i];
            cnt++;
        }
    }
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (cnt == 0) return 0;
        for (i = 0; i < 4; i++) {
            id = D_0035BCF0[0][i];
            r = inl_has(o, id); if (r) break;
        }
        if (i >= 4) return 0; break;
    case 2:
        w->w80.c.b4 = 3;
        w->x8c = 0;
        w->x88 = t;
        if (t != 0 && (EntB *)o != t && e == t) func_00157a30(o, 26, e);
        if (cnt >= 2) {
            for (i = 0; i < 4; i++) {
                r = inl_has(o, D_0035BCF0[1][i]);
                if (r) {
                    w->w80.b.id = D_0035BCF0[1][i];
                    break;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                r = inl_has(o, D_0035BCF0[0][i]);
                if (r) {
                    w->w80.b.id = D_0035BCF0[0][i];
                    break;
                }
            }
        }
        if (func_00147840(w->w80.b.id)->x4 & 1) {
            w->x88 = 0;
            w->x8c = -1;
        }
    }
    return 1;
}
#undef D_0035AE80

/* func_0016c480 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { u8 pad[0x70]; s32 w70; } Ent6C4;
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x350]; u64 f370; } Ent370;
typedef struct { s32 a, b; } P8;
typedef struct {
    u8 pad0[0x38]; u64 w38; u8 pad40[0x40]; union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80; u8 pad88[0]; P8 p88; Ent370 *p90; u8 pad94[4]; u8 pad98[8]; f32 fA0;
    u8 padA4[0x2C]; f32 vD0[3]; f32 fDC; u8 padE0[0x40]; f32 v120[4]; 
} Wk6C4;
s32 func_00133000(Ent6C4 *, s32);
static inline s32 inl_ok_6c480(Ent6C4 *e, s32 K) {
    s32 r;
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}
#define func_001376e8 ((f32 (*)(void *, f32 *)) func_001376e8)
#define func_00141200 ((s32 (*)(void *, s32)) func_00141200)
s32 func_0016c480(Ent6C4 *e, Wk6C4 *w, s32 unused, s32 mode) {
    s32 ok;
    f32 f;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok_6c480(e, 0)) return 0;
        if (w->p90 == 0) return 0;
        if (func_00141200(w->p90, 2)) return 0;
        f = w->fDC;
        if (f < D_0035AE80.fD0) return 0;
        if (D_0035AE80.fD4 < f) return 0;
        if (!(D_0035AE80.fD8 <= f)) return 1;
        if (!(f <= D_0035AE80.fDC)) return 1;
        f = w->fA0;
        if (f < D_0035AE80.fE0) return 0;
        if (D_0035AE80.fE4 < f) return 0;
        break;
    case 2:
        func_001376e8(e, w->vD0);
        PlatVu0CopyVector(w->v120, w->vD0);
        w->v120[3] = 0;
        w->w80.b.m = mode;
        w->w80.b.z = 0;
        w->p88 = *(P8 *)&w->p90;
        break;
    }
    return 1;
}
#undef func_001376e8
#undef func_00141200

/* func_0016c650 (from hand/nostrict/text_00160000_c04.c). */
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
extern s32 func_00132fe0(s32);
static inline s32 inl_001715b0(void *grp, Ent370 *self, f32 r) {
    f32 v[4];
    s32 n = 0;
    Ent370 *p = 0;
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
static inline s32 inl_ok_6c650(ObjC6 *e, s32 K) {
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
#define D_0035AE80 (*(PrmC6 (*)) &D_0035AE80)
#define func_00123158 ((Ent370 *(*)(void *, Ent370 *)) func_00123158)
#define func_00123368 ((s32 (*)(Ent370 *)) func_00123368)
#define func_00133000 ((s32 (*)(ObjC6 *, s32)) func_00133000)
#define func_00141200 ((s32 (*)(void *, s32)) func_00141200)
/* ---- func_0016c650 ---- */
s32 func_0016c650(ObjC6 *o, WkC6 *w, s32 k, s32 mode) {
    f32 f;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok_6c650(o, 1)) return 0;
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
        PlatVu0CopyVector(w->v120, w->vD0);
        w->w12C = 0;
        w->w80.b.m = mode;
        w->w80.b.id = 1;
        w->q88 = w->q90;
        break;
    }
    return 1;
}
#undef D_0035AE80
#undef func_00123158
#undef func_00123368
#undef func_00133000
#undef func_00141200
#undef ZONE

/* func_0016cb98 (from hand/nostrict/text_00160000_h60.c). */
static inline s32 inl_ok_6cb98(Ent6C4 *e, s32 K) {
    s32 r;
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}
#define func_00123158 ((Ent370 *(*)(void *, Ent370 *)) func_00123158)
#define func_00123368 ((s32 (*)(Ent370 *)) func_00123368)
#define func_001376e8 ((f32 (*)(void *, f32 *)) func_001376e8)
#define func_00141200 ((s32 (*)(void *, s32)) func_00141200)
s32 func_0016cb98(Ent6C4 *e, Wk6C4 *w, s32 unused, s32 mode) {
    f32 f;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok_6cb98(e, 2)) return 0;
        if (w->p90 == 0) return 0;
        if (func_00141200(w->p90, 4)) return 0;
        f = w->fDC;
        if (f < D_0035AE80.f154) return 0;
        if (D_0035AE80.f158 < f) return 0;
        f = w->fA0;
        if (!(D_0035AE80.f160 <= f)) break;
        if (!(f <= D_0035AE80.f164)) break;
        if (inl_001715b0(e, w->p90, D_0035AE80.f15C) < D_0035AE80.wB4) return 0;
        break;
    case 2:
        func_001376e8(e, w->vD0);
        PlatVu0CopyVector(w->v120, w->vD0);
        w->v120[3] = 0;
        w->w80.b.m = mode;
        w->w80.b.z = 2;
        w->p88 = *(P8 *)&w->p90;
        break;
    }
    return 1;
}
#undef func_00123158
#undef func_00123368
#undef func_001376e8
#undef func_00141200

/* func_0016ce10 (from hand/nostrict/text_00160000_s6_09.c). */
typedef struct { u8 pad[0x80]; u8 b80; } Prm6x;
typedef Act6C_35BD40 Act6C;
typedef struct {
    s32 w0; u8 pad4[0x34]; u64 w38; u8 pad40[0x40];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    Act6C *p88; s32 w8C; void *p90; u8 pad94[4]; Act6C *p98;
} Wk6CE;
static inline s32 inl_ok_6ce10(Act6C *e, s32 K) {
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}
static inline s32 inl_alive(Act6C *a) {
    s32 k = ((Prm6x *) &D_0035AE80)->b80;
    if (a->flags & 0x200) return 0;
    if (a->p6C->w40 * k < a->p6C->w3C * 255) return 0;
    return 1;
}
#define func_00157a30 ((void (*)(void *, s32, void *)) func_00157a30)
#define D_0035AE80 (*(Prm6x (*)) &D_0035AE80)
#define func_00133000 ((s32 (*)(Act6C *, s32)) func_00133000)
s32 func_0016ce10(Act6C *e, Wk6CE *w, s32 unused, s32 mode) {
    Act6C *list[3];
    Act6C *t;
    Act6C *s;
    s32 i;
    list[0] = e;
    list[1] = D_0035BD40.act6C[0];
    list[2] = D_0035BD40.act6C[w->w0 ^ 3];
    t = w->p98;
    if (t != 0 && inl_alive(t)) s = t;
    else s = 0;
    for (i = 0; i < 3; i++) {
        if (list[i] != 0 && inl_alive(list[i]) && s == 0) {
            s = list[i];
            break;
        }
    }
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok_6ce10(e, 3)) return 0;
        if (s == 0) return 0;
        break;
    case 2:
        w->w80.b.m = mode;
        w->w8C = 0;
        w->p88 = s;
        w->w80.b.z = 3;
        if (s != 0 && e != s && t == s) func_00157a30(e, 26, t);
        break;
    }
    return 1;
}
#undef func_00157a30
#undef D_0035AE80
#undef func_00133000

/* func_0016d040 (from hand/nostrict/text_00160000_b05.c). */
typedef struct {
    u8 pad0[0x84];
    u32 x84, x88, x8c, k[3], x9c, xa0, xa4;
    u8 padA8[0x168 - 0xa8];
    f32 x168, x16c, x170, x174, x178, x17c;
    struct { f32 a, b, c, d, r; } rng[3];
    f32 x1bc, x1c0, x1c4, x1c8;
} Prm05;
typedef struct { u8 pad[0x3c]; u32 x3c; u32 x40; } Hp6D0;
typedef struct { u8 pad[0x6c]; Hp6D0 *x6c; } Tg6D0;
typedef struct { u8 pad[0x70]; s32 w70; } Ent6D0;
typedef struct { s32 a, b; } P8_6D0;
typedef struct {
    u8 pad0[0x38]; u64 w38; u8 pad40[0x40];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    P8_6D0 p88; Tg6D0 *p90; u8 pad94[0xc]; f32 fA0; u8 padA4[0x2c]; f32 vD0[3]; f32 fDC; u8 padE0[0x40]; f32 v120[4];
} Wk6D0;
typedef struct { u8 pad[0x3c]; s32 x3c; s32 x40; } Hp7;
typedef struct { u8 pad[0x170]; f32 x170; } Sb7;
typedef struct { u32 x0; u8 pad4[0x68]; Hp7 *x6c; s32 w70; u8 pad74[0xd4]; Sb7 *x148; } Ent7;
static inline s32 inl_ok_6d040(Ent7 *e, s32 K) {
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
#define D_0035AE80 (*(Prm05 (*)) &D_0035AE80)
#define func_00133000 ((s32 (*)(void *, s32)) func_00133000)
#define func_00141200 ((s32 (*)(void *, s32)) func_00141200)
#define func_001376e8 ((f32 (*)(void *, f32 *)) func_001376e8)
/* --- func_0016d040 --- */
s32 func_0016d040(Ent6D0 *e, Wk6D0 *w, s32 unused, s32 mode) {
    f32 f;
    u32 a, t;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok_6d040((Ent7 *)e, 4)) return 0;
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
        PlatVu0CopyVector(w->v120, w->vD0);
        w->v120[3] = 0;
        w->w80.b.m = mode;
        w->w80.b.z = 4;
        w->p88 = *(P8_6D0 *)&w->p90;
        break;
    }
    return 1;
}
#undef D_0035AE80
#undef func_00133000
#undef func_00141200
#undef func_001376e8

/* func_0016d2d0 (from hand/nostrict/text_00160000_b05.c). */
typedef struct { u8 pad[0x88]; u32 x88; } T88;
static inline s32 inl_ok_6d2d0(Ent7 *e, s32 K) {
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}
#define CASE_6D2(i) \
            f = w->fDC; \
            if (f < D_0035AE80.rng[i].a || D_0035AE80.rng[i].b < f) return 0; \
            f = w->fA0; \
            if (f < D_0035AE80.rng[i].c || D_0035AE80.rng[i].d < f) return 0; \
            if ((u32)((inl_001715b0(e, (Ent370 *)w->p90, D_0035AE80.rng[i].r) + 1) * D_0035AE80.k[i]) < (func_001627e8(0x1000) >> 4)) return 0; \
            break;
#define D_0035AE80 (*(Prm05 (*)) &D_0035AE80)
#define func_00133000 ((s32 (*)(void *, s32)) func_00133000)
#define func_00141200 ((s32 (*)(void *, s32)) func_00141200)
#define func_001376e8 ((f32 (*)(void *, f32 *)) func_001376e8)
#define func_00123158 ((Ent370 *(*)(void *, Ent370 *)) func_00123158)
#define func_00123368 ((s32 (*)(Ent370 *)) func_00123368)
/* --- func_0016d2d0 --- */
s32 func_0016d2d0(Ent6D0 *e, Wk6D0 *w, s32 unused, s32 mode) {
    f32 f;
    switch (mode) {
    case 0:
        return 0;
    case 1:
        if (!((s32)((s64)(w->w38 << 30) >> 32) & 1)) return 0;
        if (!inl_ok_6d2d0((Ent7 *)e, 5)) return 0;
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
        PlatVu0CopyVector(w->v120, w->vD0);
        w->v120[3] = 0;
        w->w80.b.m = mode;
        w->w80.b.z = 5;
        w->p88 = *(P8_6D0 *)&w->p90;
        break;
    }
    return 1;
}
#undef D_0035AE80
#undef func_00133000
#undef func_00141200
#undef func_001376e8
#undef func_00123158
#undef func_00123368
#undef CASE_6D2

/* func_0016d768 (from hand/nostrict/text_00160000_b05.c). */
extern u8 D_0035AF20;
typedef struct { u8 pad[0x6c]; Hp7 *x6c; } Tg7;
typedef struct {
    s32 x0; u8 pad4[0x34]; u64 w38; u8 pad40[0x40];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    Ent7 *x88; s32 x8c; Tg7 *p90; u8 pad94[0x48]; f32 fDC;
} Wk7;
Ent7 *D_00574FB0 ALIGNED(16);
static inline s32 inl_ok_6d768(Ent7 *e, s32 K) {
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}
static inline s32 inl_hp_6d768(Ent7 *o, s32 k) {
    if (o->x0 & 0x200) return 0;
    if (o->x6c->x40 * k < o->x6c->x3c * 255) return 0;
    return 1;
}
#define D_0035AE80 (*(Prm05 (*)) &D_0035AE80)
#define func_00133000 ((s32 (*)(void *, s32)) func_00133000)
/* --- func_0016d768 --- */
/* --- func_0016d768 (cont.) --- */
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
        if (!inl_ok_6d768(e, 6)) return 0;
        r = func_00132fe0(6);
        arr[0] = e;
        arr[1] = D_0035BD40.vp[0];
        arr[2] = D_0035BD40.vp[w->x0 ^ 3];
        D_00574FB0 = 0;
        switch (r) {
        case 1: k = *(u8 *)&D_0035AE80.x9c; break;
        case 2: k = D_0035AF20; break;
        case 3: k = *(u8 *)&D_0035AE80.xa4; break;
        default: k = 0; break;
        }
        for (i = 0; i < 3; i++) {
            if (arr[i] == 0) continue;
            if (!inl_hp_6d768(arr[i], k)) continue;
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
#undef D_0035AE80
#undef func_00133000

/* func_0016db80 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { u8 pad[8]; void *w8; u8 padC[0x64]; s32 w70; } Ent6D;
typedef struct { u8 pad[0xC]; f32 fC; f32 f10; f32 f14; f32 f18; } Rng6D;
typedef struct { u8 pad[4]; u32 w4; } Arg6D;
typedef struct {
    u8 pad0[8]; Rng6D *p08; Rng6D *p0C; u8 pad10[0x20]; f32 f30; u8 pad34[4]; u64 w38; u8 pad40[0x14]; s32 w54; u8 pad58[0xC];
    f32 f64; f32 f68; f32 f6C; u8 pad70[4]; Arg6D *p74; u8 pad78[0x18]; void *p90; u8 pad94[8]; f32 f9C; u8 padA0[0x2C];
    f32 fCC; u8 padD0[0xC]; f32 fDC; u8 padE0[0x40]; f32 v120[4];
} Wk6D;
f32 func_001629e8(void);
s32 func_0016dd30();
s32 func_0016db80(Ent6D *e, Wk6D *w, Arg6D *x, s32 mode) {
    Rng6D *p;
    f32 f, a, b;
    if (w->f64 > 0.0f) p = w->p0C;
    else p = w->p08;
    switch (mode) {
    case 1:
        if (!(x->w4 & 0x800) && w->w54 == 0) return 0;
    case 0:
        if (w->p90 == 0) return 0;
        if ((s32)w->w38 & 1) return 0;
        if (w->w54 == 0) {
            if (!func_0016dd30(e, w, x)) return 1;
            if (w->p74 == x) return 0;
            break;
        }
        f = w->f68;
        if (f <= 0.0f) return 0;
        if (w->f6C - f >= p->fC * 0.5f && func_0016dd30(e, w, x)) return 0;
        break;
    case 2:
        if (w->w54 == 0) {
            a = p->fC;
            b = p->f10;
            f = func_001629e8();
            w->w38 |= 2;
            w->f6C = w->f68 = a + f * (b - a);
        }
        func_001693c8((Ent69 *)e, (Wk6B *)w);
        w->v120[3] = 0;
        break;
    }
    return 1;
}

/* func_0016dd30 (from hand/nostrict/text_00160000_h60.c). */
s32 func_0016dd30(Ent6D *e, Wk6D *w, Arg6D *x, s32 mode) {
    Rng6D *p;
    void *t;
    f32 a, b, f;
    if (w->f64 > 0.0f) p = w->p0C;
    else p = w->p08;
    switch (mode) {
    case 1:
        if (!(x->w4 & 0x800) && w->w54 == 0) return 0;
    case 0:
        t = w->p90;
        if (t == 0) return 0;
        if (w->w54 != 0 && w->f68 <= 0.0f) return 0;
        if (e->w70 == 0) {
            if (w->fDC < w->f9C + w->f30 + D_0035AE80.f1DC) return 0;
        } else if (e->w70 == 8 || e->w70 == 24) {
            if (w->fCC < w->f9C + w->f30 + D_0035AE80.f1DC) return 0;
        }
        if (e->w8 == t) return 0;
        break;
    case 2:
        if (w->w54 == 0) {
            a = p->f14;
            b = p->f18;
            f = func_001629e8();
            w->w38 |= 2;
            w->f68 = a + f * (b - a);
        }
        func_001693c8((Ent69 *)e, (Wk6B *)w);
        if (w->v120[3] == 0.0f) return 1;
        if (w->f64 > 0.0f || ((s32)w->w38 & 1)) w->v120[3] = 20.0f;
        else w->v120[3] = 10.0f;
        break;
    }
    return 1;
}

/* func_0016df30 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { f32 ang, y, scale, a, b; } Tbl6E;
typedef struct { u8 pad[0x30]; f32 v30[3]; f32 f3C; u8 pad40[0x30]; s32 w70; u8 pad74[0xF0]; s32 w164; } Ent6E;
typedef struct {
    u8 pad0[0x10]; s32 w10; Tbl6E *p14; u8 pad18[0x20]; u64 w38; u8 pad40[8]; s32 w48; s32 w4C; u8 pad50[0x18];
    f32 f68; u8 pad6C[0x24]; void *p90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 v120[4];
} Wk6E;
f32 cosf(f32);
void func_00137688(Ent6E *, f32);
void func_0014d428(Ent6E *, f32 *, f32, f32);
f32 sinf(f32);
static inline s32 inl_in(s32 k, Wk6E *w) {
    if (k < 13) { if (k >= 3) return 1; }
    return k == w->w4C;
}
#define func_001376e8 ((f32 (*)(void *, f32 *)) func_001376e8)
#define func_00171790 ((void (*)(Ent6E *, Wk6E *)) func_00171790)
void func_0016df30(Ent6E *e, Wk6E *w) {
    f32 v[4];
    Tbl6E *t;
    f32 ang;
    if (e->w70 == 0) w->w38 |= 0x10000;
    if (!inl_in(e->w164, w)) {
        w->w48 = 0;
        w->w38 &= ~0x8000;
        return;
    }
    func_00171790(e, w);
    if (w->p90 != 0) {
        func_00137688(e, func_001376e8(e, w->vC0));
        PlatVu0ScaleVectorXYZ(w->v120, e->v30, 1.0f);
    }
    if (w->f68 <= 0.0f && ((s32)((s64)(w->w38 << 17) >> 32) & 1)) {
        t = &w->p14[func_001627e8(w->w10 << 12) >> 12];
        ang = e->f3C + t->ang;
        v[0] = sinf(ang);
        v[1] = 0.0f;
        v[2] = cosf(ang);
        v[3] = 0.0f;
        PlatVu0ScaleVector(v, v, t->scale);
        v[1] = t->y;
        func_0014d428(e, v, t->a, t->b);
        w->w38 &= ~0x8000;
    }
}
#undef func_001376e8
#undef func_00171790

/* func_0016e0d0 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_6e0d0 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40;
typedef struct Node57 { s32 id; s32 mask; s32 (*cb)(ObjBD40 *, s32, s32, s32); s32 arg; struct Node57 *next; } Node57;
extern Node57 *D_00575780;
extern Node57 *D_00575784;
void func_0016e0d0(s32 mask) {
    Node57 *n = D_00575780;
    Node57 *prev = 0;
    Node57 *next;
    while (n != 0) {
        s32 r = 1;
        next = n->next;
        if (n->cb != 0 && (u32)(n->id - 1) < 2) {
            ObjBD40 *o = D_0035BD40.objBD40[n->id];
            if (o != 0) {
                r = 0;
                if ((o->flags & 0x8000) && (n->mask & mask)) {
                    r = n->cb(o, o->w144, mask, n->arg);
                }
            }
        }
        if (r == 1) {
            if (prev == 0) D_00575780 = n->next;
            else prev->next = n->next;
            n->cb = 0;
            n->next = D_00575784;
            D_00575784 = n;
        } else {
            prev = n;
        }
        n = next;
    }
}

/* func_0016e1f0 (from hand/nostrict/text_00160000_h60.c). */
typedef Wk144_35BD40 Wk144;
typedef struct { f32 p[4]; f32 d[4]; f32 hit[4]; s16 h; u8 pad32[0xE]; } Ray6E;
extern f32 D_0035BD10[4];
extern f32 D_00575050[][4];
extern f32 D_00575090[40][4];
void func_00118668(Ray6E *);
void func_0016e1f0(s32 i) {
    f32 a[4];
    Ray6E r;
    Wk144 *w;
    f32 best, d;
    s32 j, k;
    w = D_0035BD40.chr[i]->p144;
    w->w38 &= ~0x4000;
    if (D_0035BD40.chr[i]->w70 == 8 || D_0035BD40.chr[i]->w70 == 24 || D_0035BD40.chr[i]->w70 == 25) return;
    if (D_00575020[i][1] < D_0035BD40.chr[i]->pos[1] - D_0035BD40.chr[i]->p6C->f10) return;
    if (D_0035BD40.chr[i]->pos[1] + D_0035BD40.chr[i]->p6C->f10 < D_00575020[i][1]) return;
    PlatVu0ScaleVector(a, D_0035BD10, D_0035BD40.chr[i]->p6C->f10);
    PlatVu0SubVector(r.p, D_00575020[i], a);
    PlatVu0ScaleVector(r.d, a, 2.0f);
    func_00118668(&r);
    if (r.h < 0) {
    w->w38 |= 0x4000;
    k = 0;
    PlatVu0SubVector(a, D_00575090[0], D_00575020[i]);
    best = PlatVu0InnerProduct(a, a);
    for (j = 1; j < 40; j++) {
        PlatVu0SubVector(a, D_00575090[j], D_00575020[i]);
        d = PlatVu0InnerProduct(a, a);
        if (d < best) {
            best = d;
            k = j;
        }
    }
    PlatVu0AddVector(a, D_00575090[k], D_00575050[i]);
    PlatVu0ScaleVector(D_00575020[i], a, 0.5f);
    } else {
        PlatVu0CopyVector(D_00575020[i], r.hit);
    }
}

/* func_0016e3f8 (from hand/nostrict/text_00160000_c04.c). */
typedef WkE3_35BD40 WkE3;
extern V4E3 D_00575060[2];
extern V4E3 D_00575030[2];
extern V4E3 D_0035BD20[2];
extern void func_00162878(V4E3 *, V4E3 *, V4E3 *);
extern f32 func_001629b0(V4E3 *, V4E3 *);
static inline s32 inl_k(void) {
    if (D_0035BD40.chrE3[0]->x70 == 13 || D_0035BD40.chrE3[0]->x70 == 10) return 1;
    return 0;
}
#define func_00162c20 ((f32 (*)(V4E3 *)) func_00162c20)
/* ---- func_0016e3f8 ---- */
void func_0016e3f8(void) {
    V4E3 v0, v1, a1, a2, b1, b2;
    WkE3 *w1 = 0;
    WkE3 *w2 = 0;
    f32 d1, d2, d3, d4;
    s32 k;
    PlatVu0CopyVector(&D_00575060[0], &D_00575030[0]);
    PlatVu0CopyVector(&D_00575060[1], &D_00575030[1]);
    func_00162878(&v0, &D_0035BD40.chrE3[0]->xd0, &D_0035BD20[0]);
    func_00162878(&v1, &D_0035BD40.chrE3[0]->xd0, &D_0035BD20[1]);
    d1 = d2 = d3 = d4 = 0.0f;
    if (D_0035BD40.chrE3[1] != 0 && (w1 = D_0035BD40.chrE3[1]->p144) != 0) {
        w1->w38 &= ~0x80000ULL;
        PlatVu0SubVector(&w1->vE0, &D_0035BD40.chrE3[0]->pos, &D_0035BD40.chrE3[1]->pos);
        w1->fA4 = w1->vE0.y;
        PlatVu0CopyVector(&w1->vF0, &w1->vE0);
        w1->vF0.y = 0.0f;
        w1->vE0.w = func_00162c20(&w1->vE0);
        w1->vF0.w = func_00162c20(&w1->vF0);
        PlatVu0ScaleVector(&a1, &v0, w1->p4->f8);
        PlatVu0AddVector(&a1, &a1, &D_0035BD40.chrE3[0]->pos);
        PlatVu0ScaleVector(&a2, &v1, w1->p4->f8);
        PlatVu0AddVector(&a2, &a2, &D_0035BD40.chrE3[0]->pos);
        d1 = func_001629b0(&a1, &D_0035BD40.chrE3[1]->pos);
        d2 = func_001629b0(&a2, &D_0035BD40.chrE3[1]->pos);
    }
    if (D_0035BD40.chrE3[2] != 0 && (w2 = D_0035BD40.chrE3[2]->p144) != 0) {
        w2->w38 &= ~0x80000ULL;
        PlatVu0SubVector(&w2->vE0, &D_0035BD40.chrE3[0]->pos, &D_0035BD40.chrE3[2]->pos);
        w2->fA4 = w2->vE0.y;
        PlatVu0CopyVector(&w2->vF0, &w2->vE0);
        w2->vF0.y = 0.0f;
        w2->vE0.w = func_00162c20(&w2->vE0);
        w2->vF0.w = func_00162c20(&w2->vF0);
        PlatVu0ScaleVector(&b1, &v0, w2->p4->f8);
        PlatVu0AddVector(&b1, &b1, &D_0035BD40.chrE3[0]->pos);
        PlatVu0ScaleVector(&b2, &v1, w2->p4->f8);
        PlatVu0AddVector(&b2, &b2, &D_0035BD40.chrE3[0]->pos);
        d3 = func_001629b0(&b1, &D_0035BD40.chrE3[2]->pos);
        d4 = func_001629b0(&b2, &D_0035BD40.chrE3[2]->pos);
    }
    if (w1 != 0) {
        if (w2 != 0) {
            if (d1 <= d2 && d1 <= d3 && d1 <= d4) {
                PlatVu0CopyVector(&D_00575030[0], &a1);
                d3 = func_001629b0(&b1, &D_00575030[0]);
                if (d3 <= func_001629b0(&b2, &D_00575030[0])) PlatVu0CopyVector(&D_00575030[1], &b2);
                else PlatVu0CopyVector(&D_00575030[1], &b1);
            } else if (d2 <= d1 && d2 <= d3 && d2 <= d4) {
                PlatVu0CopyVector(&D_00575030[0], &a2);
                d3 = func_001629b0(&b1, &D_00575030[0]);
                if (d3 <= func_001629b0(&b2, &D_00575030[0])) PlatVu0CopyVector(&D_00575030[1], &b2);
                else PlatVu0CopyVector(&D_00575030[1], &b1);
            } else if (d3 <= d1 && d3 <= d2 && d3 <= d4) {
                PlatVu0CopyVector(&D_00575030[1], &b1);
                d1 = func_001629b0(&a1, &D_00575030[1]);
                if (d1 <= func_001629b0(&a2, &D_00575030[1])) PlatVu0CopyVector(&D_00575030[0], &a2);
                else PlatVu0CopyVector(&D_00575030[0], &a1);
            } else if (d4 <= d1 && d4 <= d2 && d4 <= d3) {
                PlatVu0CopyVector(&D_00575030[1], &b2);
                d1 = func_001629b0(&a1, &D_00575030[1]);
                if (d1 <= func_001629b0(&a2, &D_00575030[1])) PlatVu0CopyVector(&D_00575030[0], &a2);
                else PlatVu0CopyVector(&D_00575030[0], &a1);
            }
            if (inl_k()) {
                if (w1->vE0.w < w2->vE0.w) {
                    w1->w38 |= 0x80000ULL;
                    PlatVu0CopyVector(&D_00575030[0], &D_0035BD40.chrE3[0]->x50);
                } else {
                    w2->w38 |= 0x80000ULL;
                    PlatVu0CopyVector(&D_00575030[1], &D_0035BD40.chrE3[0]->x50);
                }
            }
            func_0016e1f0(1);
            func_0016e1f0(2);
        } else {
            if (d1 <= d2) PlatVu0CopyVector(&D_00575030[0], &a1);
            else PlatVu0CopyVector(&D_00575030[0], &a2);
            if (inl_k()) {
                w1->w38 |= 0x80000ULL;
                PlatVu0CopyVector(&D_00575030[0], &D_0035BD40.chrE3[0]->x50);
            }
            func_0016e1f0(1);
        }
    } else if (w2 != 0) {
        if (d3 <= d4) PlatVu0CopyVector(&D_00575030[1], &b1);
        else PlatVu0CopyVector(&D_00575030[1], &b2);
        if (inl_k()) {
            w2->w38 |= 0x80000ULL;
            PlatVu0CopyVector(&D_00575030[1], &D_0035BD40.chrE3[0]->x50);
        }
        func_0016e1f0(2);
    }
}
#undef func_00162c20

/* func_0016ea58 (hand/nostrict): the target search is matched func_001711d0 written as a static inline helper (inl_001711d0, its exact body); the set1/set2 gotos written out as separate w1->w38 |= 8 / w2->w38 |= 8 statements (jump2 cross-jumps them; the extra refs give w1/w2 s4/s5 over the hoisted const 2), the d2<d1 arm as one && / || condition, w2 = 0 before w1 = 0. */
/* func_0016ea58 (from hand/nostrict/text_00160000_s10_r2_1.c). */
typedef struct { u8 pad[0xC8]; f32 fC8; } PrmEA;
extern LockEA D_00575080;
extern f32 D_0035AF40;
extern f32 D_0048E950;
extern TalkEA D_00575310;
extern void func_00122768();
extern void func_001224c8(s32 *, void *, void *, f32);
extern s32 func_00153d78(ChrEA *);
static inline void inl_001711d0(ChrEA *self, LockEA *out, f32 r) {
    f32 a[4];
    f32 b[4];
    EntEA *p;
    s32 i;
    f32 best, d;
    out->f4 = -1;
    out->f0 = 0;
    if (r <= 0.0f) best = D_0048E950;
    else best = r * r;
    p = 0;
    while ((p = func_00123158(self, p)) != 0) {
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        if (func_00141200(p, 0)) continue;
        for (i = -1; (i = func_0012ee70(p, i)) >= 0;) {
            if (!func_0012f040(p, i)) continue;
            func_0012ec60(p, i, a);
            PlatVu0SubVector(b, a, &self->pos);
            d = PlatVu0InnerProduct(b, b);
            if (d < best) {
                out->f0 = p;
                best = d;
                out->f4 = i;
            }
        }
    }
}
static inline s32 inl_dead(ChrEA *c) {
    if (func_00153d78(c) || (c->flags & 0x200)) return 1;
    return 0;
}
#define D_00575090 ((V4EA *) D_00575090)
#define D_0035AE80 (*(PrmEA (*)) &D_0035AE80)
#define func_00123158 ((EntEA *(*)(ChrEA *, EntEA *)) func_00123158)
#define func_00123368 ((s32 (*)(EntEA *)) func_00123368)
#define func_0012ec60 ((void (*)(EntEA *, s32, f32 *)) func_0012ec60)
#define func_0012ee70 ((s32 (*)(EntEA *, s32)) func_0012ee70)
#define func_0012f040 ((s32 (*)(void *, s32)) func_0012f040)
#define func_00141200 ((s32 (*)(EntEA *, s32)) func_00141200)
#define func_001629b0 ((f32 (*)(V4EA *, V4EA *)) func_001629b0)
/* func_0016ea58 (hand/nostrict): the target search is matched func_001711d0 written as a static inline helper (inl_001711d0, its exact body); the set1/set2 gotos written out as separate w1->w38 |= 8 / w2->w38 |= 8 statements (jump2 cross-jumps them; the extra refs give w1/w2 s4/s5 over the hoisted const 2), the d2<d1 arm as one && / || condition, w2 = 0 before w1 = 0. */
s32 func_0016ea58(void) {
    V4EA v;
    WkEA *w1;
    WkEA *w2;
    s32 i, j, n;
    f32 d1, d2, k;
    for (i = 2; i >= 0; i--) D_0035BD40.vp[i] = 0;
    w2 = 0;
    w1 = 0;
    if (func_00122ff8(D_002E26A0[0])) D_0035BD40.vp[0] = D_002E26A0[0];
    if (func_00122ff8(D_002E26A0[1]) && (w1 = D_002E26A0[1]->p144) != 0) D_0035BD40.vp[1] = D_002E26A0[1];
    if (func_00122ff8(D_002E26A0[2]) && (w2 = D_002E26A0[2]->p144) != 0) D_0035BD40.vp[2] = D_002E26A0[2];

    if (D_0035BD40.chrEA[0] == 0 || (D_0035BD40.chrEA[1] == 0 && D_0035BD40.chrEA[2] == 0)) return 0;
    func_0016e0d0(1);
    D_0057508C = 0;
    if (D_00575088 == 0) {
        n = 39;
        for (i = 39; i >= 0; i--) {
            PlatVu0CopyVector(&D_00575090[n--], &D_0035BD40.chrEA[0]->pos);
            D_00575090[i].w = D_0035BD40.chrEA[0]->f3C;
        }
        D_00575088 = 1;
    } else {
        PlatVu0SubVector(&v, &D_00575090[0], &D_0035BD40.chrEA[0]->pos);
        if (PlatVu0InnerProduct(&v, &v) > 1600.0f) {
            D_0057508C = 1;
            for (i = 38; i >= 0; i--) PlatVu0CopyVector(&D_00575090[i + 1], &D_00575090[i]);
            PlatVu0CopyVector(&D_00575090[0], &D_0035BD40.chrEA[0]->pos);
            D_00575090[0].w = D_0035BD40.chrEA[0]->f3C;
        }
    }
    func_0016e3f8();
    if (w1 != 0 && inl_dead(D_0035BD40.chrEA[1])) {
        w1->f64 = 0;
        w1 = 0;
    }
    if (w2 != 0 && inl_dead(D_0035BD40.chrEA[2])) {
        w2->f64 = 0;
        w2 = 0;
    }
    if ((D_002C5958 & 1) && (D_002E3168 & 1)) {
        if (D_002E31B0.f0 != 0) {
            D_00575080 = D_002E31B0;
        } else {
            inl_001711d0(D_0035BD40.chrEA[0], &D_00575080, D_0035AF40);
            if (D_00575080.f4 < 0) D_00575080.f0 = 0;
        }
        if (D_00575080.f0 != 0) {
            if (w1 != 0 && func_0012f040(D_0035BD40.chrEA[1], -1)) d1 = func_001629b0(&D_00575080.f0->pos, &D_0035BD40.chrEA[1]->pos);
            else d1 = D_0048E950;
            if (w2 != 0 && func_0012f040(D_0035BD40.chrEA[2], -1)) d2 = func_001629b0(&D_00575080.f0->pos, &D_0035BD40.chrEA[2]->pos);
            else d2 = D_0048E950;
            if (d1 < d2) {
                if (w2 != 0 && w1->f64 > 0.0f && w1->p90 == D_00575080.f0) w2->w38 |= 8;
                else w1->w38 |= 8;
            } else if (d2 < d1) {
                if (w1 != 0 && w2->f64 > 0.0f && w2->p90 == D_00575080.f0) w1->w38 |= 8;
                else w2->w38 |= 8;
            }
        } else if (w1 != 0) {
            if (w2 != 0) {
                d1 = func_001629b0(&D_0035BD40.chrEA[0]->pos, &D_0035BD40.chrEA[1]->pos);
                d2 = func_001629b0(&D_0035BD40.chrEA[0]->pos, &D_0035BD40.chrEA[2]->pos);
                k = D_0035AE80.fC8 * D_0035AE80.fC8;
                if (d1 < k && d2 < k) {
                    if (w2->f64 < w1->f64) w2->w38 |= 8;
                    else w1->w38 |= 8;
                } else if (d2 < d1) {
                    if (w2->f64 > 0.0f && ((s32)w2->w38 & 1 || d2 < D_0035AE80.fC8 * D_0035AE80.fC8)) w1->w38 |= 8;
                    else w2->w38 |= 8;
                } else {
                    if (!(w1->f64 > 0.0f)) w1->w38 |= 8;
                    else if ((s32)w1->w38 & 1) w2->w38 |= 8;
                    else if (d1 < D_0035AE80.fC8 * D_0035AE80.fC8) w2->w38 |= 8;
                    else w1->w38 |= 8;
                }
            } else w1->w38 |= 8;
        } else if (w2 != 0) {
            w2->w38 |= 8;
        }
    }
    if (D_00575310.p8 != 0 && *D_00575310.p8 != 1) D_00575310.p8 = 0;
    if (D_00575310.p10 != 0 && *D_00575310.p10 != 1) D_00575310.p10 = 0;
    if (D_00575310.p8 != 0) {
        if (w1 == 0 || D_00575310.fC == 0 || !D_00575310.fC(D_0035BD40.chrEA[1], w1) || !(D_0035BD40.chrEA[1]->flags & 0x8000)) {
            func_001224c8(D_00575310.p8, &D_002C5C60, func_00122768, 30.0f);
            D_00575310.p8 = 0;
        }
    }
    if (D_00575310.p10 != 0) {
        if (w2 == 0 || D_00575310.f14 == 0 || !D_00575310.f14(D_0035BD40.chrEA[2], w2) || !(D_0035BD40.chrEA[2]->flags & 0x8000)) {
            func_001224c8(D_00575310.p10, &D_002C5C60, func_00122768, 30.0f);
            D_00575310.p10 = 0;
        }
    }
    return 0;
}
#undef D_00575090
#undef D_0035AE80
#undef func_00123158
#undef func_00123368
#undef func_0012ec60
#undef func_0012ee70
#undef func_0012f040
#undef func_00141200
#undef func_001629b0

/* func_0016f1f0 (from hand/nostrict/text_00160000_h60.c). */
void func_00242b00(Chr *);
void func_00242b38(Chr *);
void func_00245f90(s32, Chr *);
void func_00245ff0(Chr *);
void func_002464f8(s32 *);
s32 func_0016f1f0(void) {
    s32 st[2];
    Wk144 *w1 = 0;
    Wk144 *w2 = 0;
    if (D_0035BD40.chr[1] != 0) w1 = D_0035BD40.chr[1]->p144;
    if (D_0035BD40.chr[2] != 0) w2 = D_0035BD40.chr[2]->p144;
    func_002464f8(st);
    if (w1 != 0) {
        if (st[0] && !(D_0035BD40.chr[1]->flags & 0x8000)) {
            func_00245ff0(D_0035BD40.chr[1]);
            w1->w38 &= ~0x20;
            st[0] = 0;
        }
        if ((s32)((s64)(w1->w38 << 28) >> 32) & 1) func_00242b00(D_0035BD40.chr[1]);
        else func_00242b38(D_0035BD40.chr[1]);
        if ((s32)((s64)(w1->w38 << 27) >> 32) & 1) {
            if (st[0] == 0) func_00245f90(0, D_0035BD40.chr[1]);
        } else if (st[0] != 0) {
            func_00245ff0(D_0035BD40.chr[1]);
        }
    }
    if (w2 != 0) {
        if (st[1] && !(D_0035BD40.chr[2]->flags & 0x8000)) {
            func_00245ff0(D_0035BD40.chr[2]);
            w2->w38 &= ~0x20;
            st[1] = 0;
        }
        if ((s32)((s64)(w2->w38 << 28) >> 32) & 1) func_00242b00(D_0035BD40.chr[2]);
        else func_00242b38(D_0035BD40.chr[2]);
        if ((s32)((s64)(w2->w38 << 27) >> 32) & 1) {
            if (st[1] == 0) func_00245f90(0, D_0035BD40.chr[2]);
        } else if (st[1] != 0) {
            func_00245ff0(D_0035BD40.chr[2]);
        }
    }
    func_0016e0d0(2);
    return 0;
}

/* func_0016f3d0 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { s32 *a; s32 b; } P86F;
extern Node6F D_00575528[30];
void *memset(void *, s32, u32);
static inline s32 inl_same(Wk6F3 *w) {
    if (w->w38.s.p3C != 0 && w->p40 != 0) {
        if ((u64 *)*w->w38.s.p3C == w->p40) return 1;
    }
    return 0;
}
#define D_00575310 ((P86F *) &D_00575310)
#define func_001224c8 ((void (*)(s32 *, void *, void (*)(), f32)) func_001224c8)
void func_0016f3d0(void *o, Wk6F3 *w) {
    s32 i;
    s32 *p;
    w->w94 = -1;
    w->w90 = 0;
    w->w48 = 0;
    for (i = 0; i < 30; i++) {
        if (D_00575528[i].id == w->w0 && D_00575528[i].cb != 0) {
            D_00575528[i].cb(o, w, 2, D_00575528[i].arg);
            D_00575528[i].cb = 0;
        }
    }
    p = D_00575310[w->w0].a;
    if (p != 0 && *p == 1) {
        func_001224c8(p, &D_002C5C60, func_00122768, 30.0f);
        D_00575310[w->w0].a = 0;
    }
    w->w38.w &= ~0x10;
    w->w38.w &= ~0x20;
    if (inl_same(w)) {
        *w->p40 &= ~0x100;
        *w->p40 &= ~0xC;
    }
    w->w38.s.p3C = 0;
    w->p40 = 0;
    memset(&w->w38, 0, 0x128);
}
#undef D_00575310
#undef func_001224c8

/* func_0016f548 (from hand/nostrict/text_00160000_h37.c). */
typedef struct Actor_6f548 { u32 flags; u8 pad[0x140]; s32 w144; } ObjBD40_6f548;
typedef struct Node57_6f548 { s32 id; s32 mask; s32 (*cb)(ObjBD40_6f548 *, s32, s32, s32); s32 arg; struct Node57_6f548 *next; } Node57_6f548;
extern Node57_6f548 *D_00575780_6f548 __asm__("D_00575780");
#define D_00575780 D_00575780_6f548
extern Node57_6f548 *D_00575784_6f548 __asm__("D_00575784");
#define D_00575784 D_00575784_6f548
#define func_0016f3d0 ((void (*)(void *, s32)) func_0016f3d0)
#define D_00575310 ((P8 *) &D_00575310)
extern Node57_6f548 D_00575528_6f548[] __asm__("D_00575528");
#define D_00575528 D_00575528_6f548
extern ObjBD40_6f548 *D_002E26A0_6f548[3] __asm__("D_002E26A0");
#define D_002E26A0 D_002E26A0_6f548
void func_0016f548(void) {
    s32 i;
    Node57_6f548 **pp;
    if (func_00122ff8(D_002E26A0[1]) && D_002E26A0[1]->w144 != 0)
        func_0016f3d0(D_002E26A0[1], D_002E26A0[1]->w144);
    if (func_00122ff8(D_002E26A0[2]) && D_002E26A0[2]->w144 != 0)
        func_0016f3d0(D_002E26A0[2], D_002E26A0[2]->w144);
    { s32 j; for (j = 2; j >= 0; j--) D_00575310[j].a = 0; }
    pp = &D_00575784;
    for (i = 0; i < 30; i++) {
        D_00575528[i].cb = 0;
        *pp = &D_00575528[i];
        pp = &D_00575528[i].next;
    }
    *pp = 0;
    D_00575780 = 0;
}
#undef D_00575780
#undef D_00575784
#undef func_0016f3d0
#undef D_00575310
#undef D_00575528
#undef D_002E26A0

/* func_0016f640 (from hand/nostrict/text_00160000_h60.c). */
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_00575010;
s32 D_00575014 ALIGNED(4);
s32 func_0011ef38(s32 (*)());
s32 func_001383d8(s32, s32 (*)());
void func_00170e30(s32);
#define D_00575310 ((P86F *) &D_00575310)
#define D_00575780 ((Node6F *) D_00575780)
#define D_00575784 (*(Node6F *(*)) &D_00575784)
#define func_0016ea58 ((s32 (*)()) func_0016ea58)
void func_0016f640(void) {
    s32 i;
    Node6F **pp;
    D_00575088 = 0;
    if (!func_0011ef38(func_0016ea58)) D_00575010 = func_001383d8(2500, func_0016ea58);
    if (!func_0011ef38(func_0016f1f0)) D_00575014 = func_001383d8(3499, func_0016f1f0);
    { s32 j; for (j = 2; j >= 0; j--) D_00575310[j].a = 0; }
    D_00574FB8 = 0;
    { s32 j; for (j = 19; j >= 0; j--) D_00574FC0[j] = 0; }
    pp = &D_00575784;
    for (i = 0; i < 30; i++) {
        D_00575528[i].cb = 0;
        *pp = &D_00575528[i];
        pp = &D_00575528[i].next;
    }
    *pp = 0;
    D_00575780 = 0;
    D_00574FB4 = 2;
    if (D_002BC128 == 10 && D_002BC130 == 7) func_00170e30(0);
}
#undef D_00575310
#undef D_00575780
#undef D_00575784
#undef func_0016ea58

/* func_0016f7b8 (from hand/nostrict/text_00160000_h37.c). */
extern s32 func_0013c968(s32, s32);
extern u8 D_00575788[8];
#define memset ((void (*)(void *, s32, s32)) memset)
void func_0016f7b8(void) {
    s32 i;
    s32 k;
    memset(D_00575788, 0, 8);
    for (i = 0; i < 64; i++) {
        switch (i) {
        case 29: case 30: case 31: case 32: case 63:
            k = 2; break;
        case 33: case 34: case 35: case 36:
            k = 3; break;
        case 37: case 38:
            k = 5; break;
        case 39: case 40: case 41: case 42: case 43:
            k = 7; break;
        case 44: case 45: case 46:
            k = 8; break;
        case 47: case 48:
            k = 9; break;
        case 49: case 50: case 51: case 52:
            k = 6; break;
        default:
            k = -1; break;
        }
        if (k >= 0) {
            s32 b = i >> 3;
            s32 m = i & 7;
            if (func_0013c968(i, k)) D_00575788[b] |= 1 << m;
        }
    }
}
#undef memset

/* func_0016f8b8 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { s32 w0; u8 pad4[4]; u8 *p8; u8 *pC; u8 pad10[0x54]; f32 f64; } Wk6F8;
static inline s32 inl_alive2(Chr *a, u8 *kp) {
    s32 k = *kp;
    if (a->flags & 0x200) return 0;
    if (a->p6C->w40 * k < a->p6C->w3C * 255) return 0;
    return 1;
}
Chr *func_0016f8b8(Chr *e, Wk6F8 *w) {
    Chr *o;
    if (D_0035BD40.chr[0] != 0 && inl_alive2(D_0035BD40.chr[0], w->p8)) return D_0035BD40.chr[0];
    if (inl_alive2(e, w->p8)) return e;
    o = D_0035BD40.chr[w->w0 ^ 3];
    if (o != 0 && inl_alive2(o, w->p8)) return o;
    if (w->f64 > 0.0f && D_0035BD40.chr[0] != 0 && inl_alive2(D_0035BD40.chr[0], w->pC)) return D_0035BD40.chr[0];
    return 0;
}

/* func_0016fa10 (from hand/nostrict/text_00160000_h60.c). */
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x50]; s32 w70; } Ent6FA;
typedef struct { u8 pad[8]; f32 f8; } Sub6FA;
typedef struct {
    s32 w0; Sub6FA *p4; u8 pad8[0x28]; f32 f30; u8 pad34[4]; u64 w38; u8 pad40[0x18]; s32 w58; u8 pad5c[0x34];
    void *p90; s32 w94; u8 pad98[0xC]; f32 fA4; u8 padA8[0x44]; f32 fEC; u8 padF0[0xC]; f32 fFC;
} Wk6FA;
s32 func_0012eaf8(void *);
f32 func_00162978(f32 *, f32 *);
#define func_0012ec60 ((f32 (*)(void *, s32, f32 *)) func_0012ec60)
#define func_0012ee70 ((s32 (*)(void *, s32)) func_0012ee70)
#define func_0012f040 ((s32 (*)(void *, s32)) func_0012f040)
void func_0016fa10(Ent6FA *e, Wk6FA *w, Sub6FA *pr) {
    f32 v[4];
    f32 h[4];
    void *t;
    if ((s32)w->w38 & 1) {
        if (w->fEC <= D_0035AE80.fC8) {
            w->w38 &= ~1;
        } else {
            if (e->w70 == 0 && w->fFC < fabsf(w->fA4)) {
                if (w->fFC <= w->p4->f8) w->w38 &= ~1;
                PlatVu0SubVector(v, D_00575020[w->w0], e->pos);
                v[1] = 0.0f;
                if (func_00162a58(v) <= w->f30) w->w38 &= ~1;
            }
            if (!((s32)w->w38 & 1)) w->w58++;
        }
    }
    t = w->p90;
    if (t == 0) return;
    if (!((s32)w->w38 & 1) && inl_00171118(t, -1)) {
        if (!func_0012eaf8(w->p90)) return;
        func_0012ec60(w->p90, w->w94, h);
        if (pr->f8 <= func_00162978(h, e->pos) && pr->f8 <= func_00162978(h, D_0035BD40.chr[0]->pos)) w->p90 = 0;
        if (!(D_0035AE80.fC4 <= w->fEC)) return;
    }
    w->w38 |= 1;
    w->w94 = -1;
    w->p90 = 0;
    w->w38 &= ~0x800;
}
#undef func_0012ec60
#undef func_0012ee70
#undef func_0012f040

/* func_0016fc60 (from hand/nostrict/text_s7_w27.c). */
typedef struct { f32 x, y, z, w; } V4FC;
typedef struct { u8 pad0[0x10]; V4FC pos; } ChrFC;
typedef struct { u8 pad0[0x90]; void *p90; s32 part; } WkFC;
extern f32 D_0048E9EC;
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
            PlatVu0SubVector(b, a, &c->pos);
            d = PlatVu0InnerProduct(b, b);
            if (d < bd) {
                bd = d;
                best = i;
            }
        }
    }
    return best;
}
#define func_0012ec60 ((void (*)(void *, s32, f32 *)) func_0012ec60)
#define func_0012ee70 ((s32 (*)(void *, s32)) func_0012ee70)
#define func_0012f040 ((s32 (*)(void *, s32)) func_0012f040)
/* func_0016fc60: MATCH hand/nostrict */
void func_0016fc60(ChrFC *c, WkFC *w) {
    if (func_00122ff8(w->p90)) {
        if (w->part < 0 || !inl_valid(w->p90, w->part)) w->part = inl_best(w->p90, c);
    } else {
        w->p90 = 0;
    }
}
#undef func_0012ec60
#undef func_0012ee70
#undef func_0012f040

/* func_0016fd98 (from hand/nostrict/text_00160000_b05.c). */
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x50]; s32 w70; u8 pad74[0x250]; f32 f2C4; } EntF;
typedef struct { u8 pad[4]; f32 f4; } RngF;
typedef struct { Ent370 *tgt; s32 part; } LockF;
typedef struct {
    u8 pad0[8]; RngF *p08; RngF *p0C; u8 pad10[0x28]; u64 w38; u8 pad40[0x24]; f32 f64; u8 pad68[0x28];
    LockF l90; u8 pad98[4]; f32 f9C; f32 fA0; u8 padA4[0xc]; f32 vB0[4]; f32 vC0[3]; f32 fCC; f32 vD0[3]; f32 fDC;
} WkF;
extern f32 D_0048E9F0;
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
#define func_00141200 ((s32 (*)(void *, s32)) func_00141200)
#define func_00123158 ((Ent370 *(*)(void *, Ent370 *)) func_00123158)
#define func_00123368 ((s32 (*)(Ent370 *)) func_00123368)
#define func_0012ee70 ((s32 (*)(void *, s32)) func_0012ee70)
#define func_0012f040 ((s32 (*)(void *, s32)) func_0012f040)
#define func_0012ec60 ((f32 (*)(void *, s32, f32 *)) func_0012ec60)
#define func_0016fa10 ((void (*)(EntF *, WkF *, RngF *)) func_0016fa10)
#define func_0016fc60 ((void (*)(EntF *, WkF *)) func_0016fc60)
/* --- func_0016fd98 --- */
void func_0016fd98(EntF *e, WkF *w) {
    RngF *rng;
    LockF l;
    if (w->f64 > 0.0f) rng = w->p0C;
    else rng = w->p08;
    func_0016fa10(e, w, rng);
    if ((s32)w->w38 & 1) return;
    inl_find((Ent370 *)e, &l, rng->f4);
    if (l.tgt == 0 || l.part < 0) inl_find(D_0035BD40.vp[0], &l, rng->f4);
    if (l.part < 0) l.tgt = 0;
    if ((s32)(w->w38 >> 11) & 1) func_0016fc60(e, w);
    else if (l.tgt) w->l90 = l;
    if (w->l90.tgt != 0 && w->l90.part >= 0) {
    w->f9C = func_0012ec60(w->l90.tgt, w->l90.part, w->vB0);
    if (((s32)(w->w38 >> 20) & 1) || e->w70 == 8 || e->w70 == 24 || e->w70 == 25) w->vB0[1] += e->f2C4;
    PlatVu0SubVector(w->vC0, w->vB0, e->pos);
    PlatVu0CopyVector(w->vD0, w->vC0);
    w->fA0 = w->vD0[1];
    w->vD0[1] = 0;
    w->fCC = func_00162c20(w->vC0);
    w->fDC = func_00162c20(w->vD0);
    } else {
        w->l90.tgt = 0;
        w->l90.part = -1;
    }
}
#undef func_00141200
#undef func_00123158
#undef func_00123368
#undef func_0012ee70
#undef func_0012f040
#undef func_0012ec60
#undef func_0016fa10
#undef func_0016fc60

