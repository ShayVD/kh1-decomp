#include "common.h"
#include "platform/math.h"
#include "data/bss_0057.h"

#include "data/pieces/D_0035BD40.h"
typedef ChrHp_35BD40 ChrHp;
typedef Chr_35BD40 Chr;

#include "data/types/nostrict_text_00160000_h60_p.h"
typedef struct { u8 pad[0x70]; s32 w70; } Ent6C4;
typedef struct { u8 pad[0x10]; f32 pos[4]; u8 pad20[0x350]; u64 f370; } Ent370;
typedef struct { f32 ang, y, scale, a, b; } Tbl6E;
typedef struct {
    u8 pad0[0x10]; s32 w10; Tbl6E *p14; u8 pad18[0x20]; u64 w38; u8 pad40[8]; s32 w48; s32 w4C; u8 pad50[0x18];
    f32 f68; u8 pad6C[0x24]; void *p90; u8 pad94[0x2C]; f32 vC0[4]; u8 padD0[0x50]; f32 v120[4];
} Wk6E;
#include "data/types/nostrict_text_00160000_h60.h"
typedef struct { u8 pad[0xC]; void *pC; } Ent70;
typedef struct {
    s32 w0; void *p4; void *p8; void *pC; s32 w10; s32 w14; s32 w18; Ent70 *p1C; u8 pad20[0x240];
} Wk70;
typedef struct { u8 pad[0x30]; u64 w30; } Sub148;
typedef struct { u8 pad[0x2C]; s32 w2C; } Sub14C;
typedef struct { u8 pad[0x4C]; u16 h4C; } Sub130;
typedef struct Actor { u8 pad[0x130]; Sub130 *p130; u8 pad134[0x10]; Wk70 *p144; Sub148 *p148; Sub14C *p14C; } Obj70;
extern u32 D_002C5958;
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31B0.h"
extern void (*D_0035BC80[])(Obj70 *, Wk70 *);
s32 D_00575014 ALIGNED(4);
s32 func_00122ff8(void *);
Ent370 *func_00123158(void *, Ent370 *);
s32 func_00123368(Ent370 *);
s32 func_0012ee70(void *, s32);
s32 func_0012f040(void *, s32);
s32 func_00133000(Ent6C4 *, s32);
f32 func_00267390(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);

static inline s32 inl_ok(Ent6C4 *e, s32 K) {
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

/* inline copy of func_001715b0 */
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

static inline s32 inl_in(s32 k, Wk6E *w) {
    if (k < 13) { if (k >= 3) return 1; }
    return k == w->w4C;
}

static inline s32 inl_same(Wk6F3 *w) {
    if (w->w38.s.p3C != 0 && w->p40 != 0) {
        if ((u64 *)*w->w38.s.p3C == w->p40) return 1;
    }
    return 0;
}

static inline s32 inl_alive2(Chr *a, u8 *kp) {
    s32 k = *kp;
    if (a->flags & 0x200) return 0;
    if (a->p6C->w40 * k < a->p6C->w3C * 255) return 0;
    return 1;
}

/* inline copy of func_00171118 */
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

/* needs make: uses rodata */

#include "data/data_002B.h"
#include "data/data_0035.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C5958.h"
