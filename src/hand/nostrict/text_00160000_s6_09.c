#include "common.h"

void func_002675a8(void *, void *);
void func_00267530(void *, void *, void *);
void func_00267518(void *, void *, void *);
void func_00267560(void *, void *, f32);
void func_00157a30(void *, s32, void *);

/* 0016ce10 */
typedef struct { u8 pad[0x80]; u8 b80; } Prm6x;
extern Prm6x D_0035AE80;
#include "data/pieces/D_0035BD40.h"
typedef Hp6C_35BD40 Hp6C;
typedef Act6C_35BD40 Act6C;

typedef struct {
    s32 w0; u8 pad4[0x34]; u64 w38; u8 pad40[0x40];
    union { u64 w; struct { u64 lo:32; u64 m:8; u64 z:16; u64 hi:8; } b; } w80;
    Act6C *p88; s32 w8C; void *p90; u8 pad94[4]; Act6C *p98;
} Wk6CE;
s32 func_00133000(Act6C *, s32);

static inline s32 inl_ok(Act6C *e, s32 K) {
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
    s32 k = D_0035AE80.b80;
    if (a->flags & 0x200) return 0;
    if (a->p6C->w40 * k < a->p6C->w3C * 255) return 0;
    return 1;
}

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
        if (!inl_ok(e, 3)) return 0;
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

/* 001713f8 */
typedef struct { u8 pad[0x4C]; u16 h4C; } Mdl13;
typedef struct { u8 pad[0x70]; s32 w70; u8 pad74[0xBC]; Mdl13 *p130; } Act13;
#include "data/pieces/D_002E27C8.h"

s32 func_001713f8(Act13 *a) {
    if ((u16)(a->p130->h4C - 1) >= 2) return 0;
    if (a->w70 != 0 && a->w70 != 2) return 0;
    if (D_002E27C8.b8) return 1;
    if (D_002E27C8.b7) return 1;
    return 0;
}

/* 00171e50 */
typedef struct { s32 w0; u8 pad[0x94]; void *p98; } Wk1E;

void func_00171e50(void *e, Wk1E *w, void *t) {
    if (t != 0 && e != t && w->p98 == t) do { func_00157a30(e, 26, t); } while (0);
}

/* 00172028 */
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
s32 func_00130340(Wk20 *, s32, f32);
Ret20 *func_00130578(Wk20 *, s32, f32);
void func_001731f8(void);
void func_00148a40(Wk20 *, s32);
void func_00170f90(void);
void func_00170fa8(Wk20 *, Ob20 *, void *, void *, f32);
R13d *func_0013dbe0(Wk20 *, s32);
R147 *func_001477c8(s32);
void func_001412f8(Wk20 *, s32);

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

/* 00173478 */
typedef struct { u8 pad[0x20]; f32 x20; } Prm34;
typedef struct { u8 pad[0xc]; Prm34 *xc; } P34;
typedef struct {
    u8 pad0[0xc0]; f32 xc0[4];
    u8 padd0[0x164 - 0xd0]; f32 x164;
    u8 pad168[0x170 - 0x168]; P34 *x170; s32 x174;
} Ob34;
typedef struct { u8 pad0[0x14]; f32 x14; u8 pad18[0x144 - 0x18]; Ob34 *x144; } Wk34;
void func_00267e90(f32 *, f32 *, f32);

void func_00173478(Wk34 *w, f32 *v) {
    Ob34 *o = w->x144;
    Prm34 *p = o->x170->xc;
    if (o->x174 == 1) {
        func_00267e90(v, o->xc0, p->x20);
        if (w->x14 + v[1] < o->x164) v[1] = o->x164 - w->x14;
    }
}

/* 001752a0 */
typedef struct { u64 a, b; } Q16;
extern Q16 D_0035C430;
extern Q16 D_0035C450;
extern s32 D_0035C420;
extern u8 *D_0035C424;
extern s32 D_0035C428;
extern u8 *D_0035C42C;
#include "data/pieces/D_0035C440.h"
#include "data/pieces/D_0035C460.h"
extern u8 D_0035C470[];
extern u8 D_0035C480[];
#include "data/pieces/D_002C58B0.h"
typedef struct { u8 pad[0x154]; u8 *x154; } Ob52;
void sceVu0CopyMatrix(void *, void *);
void func_001625c8(void *, void *);
void func_00162848(f32 *, void *, f32 *);
f32 func_00162c20(f32 *);
s32 func_00174fc0(void *, f32 *, u8 *, s32, f32 *, f32);

void func_001752a0(Ob52 *o, f32 *c) {
    f32 m[4][4];
    f32 m2[4][4];
    f32 v[4];
    f32 a[4];
    f32 b[4];
    f32 t[4];
    s32 x, y;
    if (D_0035C420 && D_0035C424 && D_0035C428 && D_0035C42C) {
        sceVu0CopyMatrix(m, o->x154 + 0xB80);
        func_001625c8(m, m2);
        func_00162848(v, m2, c);
        func_002675a8(a, (*(f32 (*)[0x4])&D_002C58B0));
        func_002675a8(b, (*(f32 (*)[0x4])&D_002C58B0));
        if (v[1] < 300.0f) v[1] = 300.0f;
        if (func_00174fc0(D_0035C470, v, D_0035C424, D_0035C420, a, c[3])) {
            func_00267530(t, a, D_0035C440);
            t[2] = t[3] = 0.0f;
            if (func_00162c20(t) > 0.015f) {
                func_00267560(t, t, 0.015f);
                func_00267518(D_0035C440, D_0035C440, t);
            } else {
                func_002675a8(D_0035C440, a);
            }
        }
        x = D_0035C440[0] * 128.0f * 2.0f * 16.0f;
        y = D_0035C440[1] * 128.0f * 2.0f * 16.0f;
        D_0035C430.a = (u64)(x - 512) | ((u64)(y - 512) << 16) | ((u64)0xFFFFFFFE << 32);
        D_0035C430.b = (u64)(x + 512) | ((u64)(y + 512) << 16) | ((u64)0xFFFFFFFE << 32);
        if (func_00174fc0(D_0035C480, v, D_0035C42C, D_0035C428, b, c[3])) {
            func_00267530(t, b, D_0035C460);
            t[2] = t[3] = 0.0f;
            if (func_00162c20(t) > 0.015f) {
                func_00267560(t, t, 0.015f);
                func_00267518(D_0035C460, D_0035C460, t);
            } else {
                func_002675a8(D_0035C460, b);
            }
        }
        x = D_0035C460[0] * 128.0f * 2.0f * 16.0f;
        y = D_0035C460[1] * 128.0f * 2.0f * 16.0f;
        D_0035C450.a = (u64)(x - 512) | ((u64)(y - 512) << 16) | ((u64)0xFFFFFFFE << 32);
        D_0035C450.b = (u64)(x + 512) | ((u64)(y + 512) << 16) | ((u64)0xFFFFFFFE << 32);
    }
}

/* 00175be0 */
typedef int u128 __attribute__((mode(TI)));
typedef struct { s32 x0; void *x4; s32 x8; void *xc; u8 pad10[4]; s32 x14; u8 pad18[4]; void *x1c; u8 pad20[0xC]; u8 *x2c; u8 pad30[0xC]; } Ent5B;
typedef struct { s32 x0; void *x4; void *x8; Ent5B ent[64]; s32 idx[64]; u8 pad[4]; f32 vec[64][4]; } W5B;

CONTEXT_ONLY s32 func_00175ba0(W5B *w) {
    s32 i;
    for (i = 0; i < 64; i++) {
        if (!(w->ent[i].x14 & 3)) return i;
    }
    return -1;
}

/* 00176960 */

/* 001784c8 */

/* 0017b308 */
#include "data/data_0035.h"
#include "data/data_0036.h"
