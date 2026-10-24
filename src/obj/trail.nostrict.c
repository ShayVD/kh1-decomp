/* The leader's trail, without strict aliasing (docs/modules.md "Session
 * 52"): func_00159ea8 starts following an object (D_00551700) and records
 * its positions in a ring of 32 (D_00551740, func_00159b48); the task
 * func_00159cd8, func_00159978, func_00159f78 (an object's move step).  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "platform/math.h"
#include "data/types/nostrict_text_00150000_h58_p.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E3168.h"
#include "data/bss_0055.h"
#include "data/types/nostrict_text_00150000_h35.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003519E0.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002C5960.h"

/* func_00159978 (from hand/nostrict/text_00150000_h58.c). */
typedef S31b0_2e31b0 P8;
typedef struct {
    u32 w0; s32 w4; s32 w8; s32 wC; s32 x10; f32 f14; s32 x18; f32 f1c; s32 x20; u8 pad24[0xc]; V4 v30; f32 f40; f32 f44; s32 x48; s32 x4c;
} S144;
typedef struct {
    u8 pad0[0x10]; V4 pos; u8 pad20[0x10]; V4 v30; u8 pad40[0x30]; s32 x70; u8 pad74[0xf0]; s32 x164;
} S98;
typedef struct { u8 pad0[5]; u8 b5; u8 pad6[0xe]; struct { u8 pad0[1]; u8 b1; } *x14; } S134;
#define ACT_BODY(T144) \
    u32 w0; u8 pad4[4]; s32 x8; u8 padc[4]; V4 pos; V4 x20; V4 x30; V4 x40; u8 pad50[0x18]; s32 x68; struct { u8 pad[0x3c]; s32 x3c; } *x6c; s32 x70; P8 x74; u8 pad7c[0xc]; s32 x88; s32 x8c; u64 x90; S98 *x98; u8 pad9c[0x24]; V4 xc0; f32 xd0[4][4]; u8 pad110[0x10]; V4 x120; \
    struct { u8 pad[0x44]; f32 x44; s16 x48; u8 pad4a[2]; u16 x4c; } *x130; S134 *x134; u8 pad138[0xc]; T144 *x144; \
    struct { u8 pad[0x160]; V4 v160; } *x148; u8 pad14c[0x1d4]; V4 x320; u8 pad330[0x40]; u64 x370; u8 pad378[0x26]; u8 x39e; u8 pad39f[0x11]; f32 x3b0; u8 pad3b4[0xc]; V4 x3c0; u8 pad3d0[0x14]; f32 x3e4; u8 pad3e8[8]; V4 x3f0; s32 x400; u8 pad404[0x9c]; void *x4a0;
typedef struct Actor_59978 { ACT_BODY(S144) } Act;
void func_001315c0(void *, s32, void *, f32);
s32 func_00122ff8(void *);
void func_00121fc4(void *, void *);
typedef struct { Act *p; s32 w4; } Arg159178;
s32 func_00123368(Act *);
Act *func_001230a0(Act *);
void func_0013dfb8(Act *, V4 *);
void func_00159178(Act *, s32, Arg159178 *, V4 *);
/* ---- func_00159978 ---- */
void func_00159978(Act *a, V4 *o) {
    Arg159178 s;
    V4 d;
    Act *p = D_002E26A0[0];
    if (!func_00122ff8(p)) return;
    a->x98 = (S98 *)p;
    PlatVu0SubVector(o, &p->x320, &a->pos);
    o->y = 0.0f;
    func_00121fc4(o, o);
    if (o->w < 200.0f) {
        PlatVu0SubVector(o, &D_002C58A0, o);
        o->w = 1.0f;
    } else if (o->w > 250.0f) {
        o->w = 1.0f;
    } else {
        o->w = 0.0f;
    }
    if (D_002E3168 & 1) {
        func_0013dfb8(a, o);
        return;
    }
    s.p = 0;
    s.w4 = 0;
    while ((s.p = func_001230a0(s.p)) != 0) {
        if (((s32)(s.p->x370 >> 37) & 3) == 1) continue;
        if (!func_00123368(s.p)) continue;
        func_001315c0(s.p, 0x8003, &d, 0.0f);
        PlatVu0SubVector(&d, &d, &a->pos);
        func_00121fc4(&d, &d);
        if (d.w < 300.0f && PlatVu0InnerProduct(&d, &a->x30) > 0.7f) {
            func_00159178(a, 11, &s, o);
            return;
        }
    }
}

/* func_00159b48 (from hand/nostrict/text_00150000_h35.c). */
typedef struct { f32 x, y, z, w; } Vec154768;
typedef struct { s32 w0; s32 idx; u8 pad8[8]; Vec154768 e[32]; } S551740;
extern S551740 D_00551740;
f32 D_00551734 ALIGNED(4);
f32 func_00120bf8(void *);
/* ---- func_00159b48 ---- */
void func_00159b48(Vec154768 *p) {
    S551740 *s = &D_00551740;
    Vec154768 *e = s->e;
    Vec154768 t;
    PlatVu0SubVector(&t, p, &e[s->idx]);
    t.w = func_00120bf8(&t);
    if (D_00551734 * 0.03125f <= t.w) {
        s->idx = (s->idx + 1) % 32;
        PlatVu0CopyVector(&e[s->idx], p);
        s->e[s->idx].w = t.w;
    }
}

/* func_00159cd8 (from hand/nostrict/text_00150000_h58.c). */
typedef struct Actor_59cd8 { ACT_BODY(S144) } Act_59cd8;
typedef union { u32 w; struct { u32 b0:1; u32 b1:1; u32 p2:14; u32 b16:1; u32 p17:6; u32 b23:1; u32 b24:1; u32 b25:1; u32 p26:6; } b; } F5958;
extern F5958 D_002C5958;
s32 func_0014f600(void *);
typedef struct { s32 w0; Act_59cd8 *obj; s32 pad[2]; V4 a; V4 b; f32 f30; f32 f34; } Tr700;
typedef struct { union { u64 d; s32 w; } h; u8 pad8[0x208]; V4 v210; V4 v220; } Trail;
extern Tr700 D_00551700;
extern s32 D_002E27A8;
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00159c10(f32, V4 *);
#else
void func_00159c10(V4 *, f32);
#define func_00159c10(a1, a2) (func_00159c10)(a2, a1)
#endif
void func_00124c68(f32);
#define D_00551740 (*(Trail (*)) &D_00551740)
#define func_00159b48 ((void (*)(V4 *)) func_00159b48)
/* ---- func_00159cd8 ---- */
s32 func_00159cd8(void) {
    f32 m[4][4];
    V4 u;
    V4 w;
    if (!func_00122ff8(D_00551700.obj)) return 4;
    if (D_002C5958.b.b1 || D_002E27A8 == 9) return 0;
    if (!(D_00551700.w0 & 1)) {
        PlatVu0CopyMatrix(m, D_00551700.obj->xd0);
        if (func_0014f600(D_00551700.obj))
            PlatVu0InterVector(m[3], &D_00551700.obj->pos, &D_00551700.obj->x320, 0.5f);
        else
            PlatVu0CopyVector(m[3], &D_00551700.obj->pos);
        func_00159b48((V4 *)m[3]);
        PlatVu0ApplyMatrix(&u, D_00551700.obj->xd0, &D_00551700.a);
        func_00159c10(D_00551700.f34, (V4 *)m[3]);
        PlatVu0ApplyMatrix(&w, m, &D_00551700.b);
        if (D_00551740.h.w & 1) {
            PlatVu0CopyVector(&D_00551740.v220, &u);
            PlatVu0CopyVector(&D_00551740.v210, &w);
            D_00551740.h.d &= ~1;
        } else {
            PlatVu0InterVector(&D_00551740.v220, &u, &D_00551740.v220, D_00551700.f30);
            PlatVu0InterVector(&D_00551740.v210, &w, &D_00551740.v210, D_00551700.f30);
        }
    }
    PlatVu0CopyVector(&D_002E2790, &D_00551740.v220);
    PlatVu0CopyVector(&D_002E2780, &D_00551740.v210);
    func_00124c68(70.0f);
    return 0;
}
#undef D_00551740
#undef func_00159b48

/* func_00159ea8 (from hand/nostrict/text_00150000_h36.c). */
typedef struct { f32 v[3]; f32 len; } Seg16;
typedef struct { s32 w0; void *obj; s32 pad[2]; f32 a[4]; f32 b[4]; f32 f30; f32 f34; } Tr700_59ea8;
typedef union { u64 d; struct { s32 lo; s32 head; s32 w8; s32 wC; } s; } TrHdr;
typedef struct { TrHdr h; Seg16 e[32]; } Trail_59ea8;
typedef struct { u8 pad[0x10]; f32 pos[4]; } ObjP;
s32 func_0011ef38(void *);
typedef struct { u16 h0; s16 h2; } TaskReg;
TaskReg *func_0011ef10(s32, void *);
#define D_00551700 (*(Tr700_59ea8 (*)) &D_00551700)
#define D_00551740 (*(Trail_59ea8 (*)) &D_00551740)
Tr700_59ea8 *func_00159ea8(ObjP *obj, void *a, void *b) {
    D_00551700.obj = obj;
    PlatVu0CopyVector(D_00551700.a, a);
    PlatVu0CopyVector(D_00551700.b, b);
    if (func_0011ef38(func_00159cd8) == 0) {
        D_00551700.f30 = 1.0f;
        D_00551700.f34 = 300.0f;
        D_00551700.w0 = 0;
        D_00551740.h.s.head = 0;
        PlatVu0CopyVector(&D_00551740.e[0], obj->pos);
        D_00551740.e[0].len = 0;
        D_00551740.h.s.w8 = 0;
        D_00551740.h.d |= 1;
        func_0011ef10(0x18894, func_00159cd8);
    }
    return &D_00551700;
}
#undef D_00551700
#undef D_00551740

/* func_00159f78 (from hand/nostrict/text_00140000_b04.c). */
typedef struct { u8 pad[4]; f32 x4; f32 x8; } B4P9;
typedef struct {
    u32 x0; u8 pad4[0x20 - 4]; f32 x20[4]; f32 x30[4]; u8 pad40[0x6c - 0x40]; B4P9 *x6c;
    u8 pad70[0x88 - 0x70]; s32 x88; u8 pad8c[0x164 - 0x8c]; s32 x164; u8 pad168[0x178 - 0x168]; s32 x178;
    u8 pad17c[0x1cc - 0x17c]; u32 x1cc; u8 pad1d0[0x370 - 0x1d0];
    union { u64 x; struct { u64 lo:50; u64 b50:1; u64 r:13; } b; } x370;
    u8 pad378[0x39e - 0x378]; u8 x39e; u8 pad39f[0x440 - 0x39f]; u64 x440;
} B4E9;
extern s32 D_002C5C54;
f32 func_001376e8(B4E9 *, f32 *);
void func_00130398(B4E9 *, s32, f32);
s32 func_00131b08(B4E9 *);
void func_00146c98(B4E9 *, s32);
s32 func_00130010(B4E9 *);
void func_0012bd98(B4E9 *, s32, s32, f32 *);
#define func_001315c0 ((void (*)(void *, s32, void *, f32)) func_001315c0)
#define D_002C5958 (*(u32 (*)) &D_002C5958)
void func_00159f78(B4E9 *e, f32 *v, s32 n) {
    f32 tmp[4];
    u32 *p;
    s32 k;
    if (v[0] == 0.0f && v[1] == 0.0f && v[2] == 0.0f) goto zero;
    func_001376e8(e, v);
    PlatVu0CopyVector(e->x20, v);
    if (e->x0 & 4) return;
    if ((s32)(e->x440 >> 33) & 1) return;
    if (v[3] == 0.0f) {
        if (e->x1cc & 0x100000) return;
        p = &D_002C5958;
        if (((s32)(e->x370.x >> 50) & 1) != (*p & 1)) {
            if ((*p & 1) || (e->x164 == 0 && func_00131b08(e))) {
                e->x370.b.b50 = *p & 1;
                func_00130398(e, n, 16.0f);
                return;
            }
        }
        if (e->x178) return;
        if ((e->x164 == n + 1 || e->x164 == n + 2) && !D_002C5C54) func_00146c98(e, 8);
        func_00130398(e, n, 10.0f);
    } else {
        e->x370.b.b50 = D_002C5958 & 1;
        if (e->x88 & 0x80) v[3] = e->x20[3] = e->x6c->x4;
        k = (v[3] < e->x6c->x8) ? n + 1 : n + 2;
        if (e->x164 == n && !func_00130010(e)) {
            func_001315c0(e, 41, tmp, 1.0f);
            func_0012bd98(e, e->x39e, 0x80000002, tmp);
            func_001315c0(e, 40, tmp, 1.0f);
            func_0012bd98(e, e->x39e, 0x80000002, tmp);
        }
        func_00130398(e, k, 8.0f);
    }
    return;
zero:
    PlatVu0CopyVector(e->x20, e->x30);
    e->x20[3] = 0.0f;
}
#undef func_001315c0
#undef D_002C5958

