#include "common.h"
extern void *D_00351BE0[];
void func_002673b8(f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
typedef struct { u8 b0; u8 b1; u16 r0:4; u16 pre:2; u16 post:2; u16 r1:8; } CurveHdrX;

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
    u32 lo:8;
    u32 b8:1;
    u32 r9:23;
    u32 hi;
    u8 pad40[0x120 - 0x40];
    u8 x120[4];
} __attribute__((aligned(8))) Ent18;
extern u32 D_002C5958;
#include "data/pieces/D_002E27C8.h"
void func_0014dcd8(Obj18 *, void *);
void func_0014c580(Obj18 *);
void func_0014c530(Obj18 *);
void func_0013dfb8(Obj18 *, void *);
CONTEXT_ONLY s32 func_00168618(Obj18 *o, Ent18 *e) {
    if (o->x70 == 2) {
        if (!e->b8) return 0;
        if (!(o->x3B8 <= o->x3B0) && o->x164 != 6) return 0;
        if (D_002C5958 >> 5 & 1) {
            func_0014dcd8(o, e->x120);
            if (o->x70 != 8) return 0;
        } else {
            if ((u16)(o->x130->h4C - 1) >= 2) return 0;
            if ((*(u32 *)&D_002E27C8) >> 8 & 1) func_0014c580(o);
            else if ((*(u32 *)&D_002E27C8) >> 7 & 1) func_0014c530(o);
            else return 0;
            if (o->x70 != 21) return 0;
        }
        e->b8 = 0;
        return 1;
    } else {
        if (e->b8) return 0;
        if (!(D_002C5958 >> 5 & 1)) {
            if ((u16)(o->x130->h4C - 1) >= 2) return 0;
            if (!((*(u32 *)&D_002E27C8) >> 8 & 1) && !((*(u32 *)&D_002E27C8) >> 7 & 1)) return 0;
        }
        func_0013dfb8(o, e->x120);
        e->b8 = 1;
        return 0;
    }
}

typedef struct { u8 pad[0x10]; f32 pos[4]; f32 v20[4]; f32 v30[4]; u8 pad40[0x30]; s32 w70; u8 pad74[0xBC]; Ch130 *x130; u8 pad134[0x30]; s32 w164; } E8D;
void func_002675a8(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);

#define G27C8 D_002E27C8
static inline s32 inl_chk(E8D *e) { if ((u16)(e->x130->h4C - 1) >= 2) return 0; if (G27C8.b8) return 1; return G27C8.b7 != 0; }

typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0xF0]; s32 w164; } Ent6C;
typedef struct { u8 pad[0x4C]; s32 w4C; u8 pad50[0x40]; void *p90; } Wk6C;

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

#include "data/types/nostrict_text_00150000_s6_08.h"
void func_00169210(C03Chr *, C03AW *);
s32 func_00169688(C03Chr *, C03AW *);
void func_001693c8(C03Chr *, C03AW *);
void func_002675a8(f32 *, f32 *);
void func_0012ec60(C03Chr *, s32, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);

static inline s32 inl_1890(C03Chr *a, C03AW *b, s32 v) {
    s32 w = v;
    if (w < 3 && v >= 0) return 1;
    return v == b->w4C;
}
static inline s32 inl_18b8(C03Chr *a, C03AW *b, s32 v) {
    s32 w = v;
    if (v < 124 && w >= 117) return 1;
    return v == b->w4C;
}
static inline s32 inl_18e0(C03Chr *a, C03AW *b, s32 v) {
    s32 w = v;
    if (v >= 0 && (v < 3 || (v < 131 && w >= 124))) return 1;
    return v == b->w4C;
}
static inline s32 inl_ok(C03Chr *e, C03AW *w, u32 fl) {
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

static inline f32 inl_d(C03Chr *p, s32 j, C03Chr *tg) {
    f32 v[4];
    f32 d2[4];
    func_0012ec60(p, j, v);
    func_00267530(d2, v, tg->pos);
    return func_00267390(d2, d2);
}

void func_00169008(C03Chr *, C03AW *);

void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
CONTEXT_ONLY void func_001693c8(C03Chr *e, C03AW *w) {
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
        func_00168d20((void *)e, (void *)w);
        break;
    }
    if (w->v120[1] == 0.0f && w->f12C == 0.0f) {
        if ((s32)((s64)(w->w38 << 22) >> 32) & 1) {
            w->w38 |= 0x80;
            func_00267560(v, w->vF0, 0.39999998f);
            func_00267518(v, v, e->v30);
            v[1] = 0.0f;
            func_002673b8(w->v120, v);
        }
    } else {
        w->w38 &= ~0x80;
    }
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_00272E20[];
extern u8 D_002732A0[];
extern u8 D_002736B0[];
extern u8 D_00273B30[];
extern u8 D_00274110[];
extern u8 D_002747C0[];
extern u8 D_002757A0[];
extern u8 D_00276870[];
extern u8 D_00277AE0[];
void *D_00351BE0[0x18] ALIGNED(32) = {
    (void *)D_002732A0, (void *)D_002736B0, (void *)D_00273B30, (void *)D_00274110,
    (void *)D_00272E20, (void *)D_00272E20, (void *)D_00273B30, (void *)D_00273B30,
    (void *)D_002747C0, (void *)D_002757A0, (void *)D_00276870, (void *)D_00274110,
    (void *)D_00272E20, (void *)D_00272E20, (void *)D_00273B30, (void *)D_00273B30,
    (void *)D_00277AE0, (void *)D_002736B0, (void *)D_00273B30, (void *)D_00274110,
    (void *)D_00272E20, (void *)D_00272E20, (void *)D_00273B30, (void *)D_00273B30,
};
#include "data/bss_0057_typed.h"
#include "data/data_0035.h"
#include "data/data_0027.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C5958.h"
