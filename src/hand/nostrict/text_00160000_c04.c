/* Hand-matched functions (worker c04), built without strict aliasing. */
#include "common.h"
#include "data/bss_0057.h"

typedef struct { s16 h0; s16 pad2; s32 w4; f32 f8; } Res8;
typedef struct { u8 pad[4]; s32 w4; } Res04;
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

extern u32 D_002C5958;
extern s32 D_00574FB8;
extern void *D_00574FC0[20];
extern s32 func_00122ff8(void *);
extern s32 func_0012f040(void *, s32);
extern s32 func_0012ee70(void *, s32);
extern Res8 *func_0013dc10(ObjB6 *, s32);
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

/* ---- func_0016c650 ---- */
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x350]; u64 f370; } Ent370;
typedef struct { u8 pad[0x70]; s32 w70; } ObjC6;
extern Ent370 *func_00123158(void *, Ent370 *);
extern s32 func_00123368(Ent370 *);
extern s32 func_00133000(ObjC6 *, s32);
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

/* ---- func_0016e3f8 ---- */
#include "data/types/nostrict_text_00160000_c04.h"
#include "data/pieces/D_0035BD40.h"
typedef Sub4E3_35BD40 Sub4E3;
typedef ChrE3_35BD40 ChrE3;

static inline s32 inl_k(void) {
    if (D_0035BD40.chrE3[0]->x70 == 13 || D_0035BD40.chrE3[0]->x70 == 10) return 1;
    return 0;
}

/* ---- func_001707d0 ---- */
#include "data/types/fvec.h"
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

static inline s32 inl_rng(ObjD0 *o, WkD0 *w) {
    if (o->x164 < 13) { if (o->x164 >= 3) return 1; }
    return o->x164 == w->w4C;
}
#include "data/bss_0057_mixed.h"
#include "data/pieces/D_002C5958.h"
