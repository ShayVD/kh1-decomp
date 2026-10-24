/* Hand-matched functions (worker c03). Built without strict aliasing. */
#include "common.h"
#include "platform/math.h"

/* ---- func_00164f18 ---- */
typedef union { s32 w; struct { u16 lo, hi; } h; } C03Key;
typedef struct { f32 t; union { u8 b4; s32 w3[3]; } u; } C03KeyF;
typedef struct { C03Key k; s32 n; C03KeyF *keys; } C03Trk;
typedef struct { u8 pad[0x3C]; C03Trk *tbl; } C03Mot;

static inline C03Trk *inl_001677e0(C03Mot *o, u32 key) {
    C03Trk *e;
    u32 lo = key & 0xFFFF;
    u32 hi = key >> 16;
    e = o->tbl;
    for (e = o->tbl; e->k.w != -1; e++) {
        if (e->k.h.hi == hi && (lo == 0xFFFF || e->k.h.lo == lo)) return e;
    }
    return 0;
}

static inline C03KeyF *inl_001676f8(C03Mot *o, u32 key, s32 *idx, f32 lo, f32 hi) {
    C03Trk *e = inl_001677e0(o, key);
    s32 i;
    if (e == 0) return 0;
    for (i = *idx; i < e->n; i++) {
        if (lo <= e->keys[i].t && e->keys[i].t < hi) {
            *idx = i;
            return &e->keys[i];
        }
    }
    return 0;
}

/* ---- func_00165cf8 ---- */

s16 D_00574F30[0x40] ALIGNED(16);

typedef struct C03Act C03Act;
typedef struct { u8 pad[0x4C]; u16 h4C; } C03Ch130;
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
} C03Chr;
typedef struct { C03Chr *p; s32 i; } C03Tgt;
typedef struct C03AW {
    u8 pad00[0x18];
    s32 n18;             /* 0x18 */
    C03Act *p1C;         /* 0x1C */
    u8 pad20[0x38 - 0x20];
    u64 w38;             /* 0x38 */
    u8 pad40[4];
    void (*cb44)(C03Chr *, struct C03AW *);   /* 0x44 */
    u8 pad48[4];
    s32 w4C;             /* 0x4C */
    u32 w50;             /* 0x50 */
    s32 w54;             /* 0x54 */
    u8 pad58[0x64 - 0x58];
    f32 f64;             /* 0x64 */
    u8 pad68[0x74 - 0x68];
    C03Act *p74;         /* 0x74 */
    s32 n78;             /* 0x78 */
    C03Act *hist[2];     /* 0x7C */
    u8 pad84[0x90 - 0x84];
    C03Tgt t90;          /* 0x90 */
    C03Chr *p98;         /* 0x98 */
} C03AW;
struct C03Act {
    s32 x0;
    u32 fl;
    s32 (*cb)(C03Chr *, C03AW *, C03Act *, s32);
    s32 pad;
};
typedef struct { u8 pad[0xBC]; f32 fBC; u8 padC0[0xCC - 0xC0]; f32 fCC; } C03Prm;
extern C03Prm D_0035AE80;

s32 func_00170dd8(u16, s32);
s32 func_00123368(C03Chr *);
s32 func_00141200(C03Chr *, s32);
s32 func_0012f040(C03Chr *, s32);
void func_0012ec60(C03Chr *, s32, f32 *);
s32 func_0012ee70(C03Chr *, s32);
C03Chr *func_00123158(C03Chr *, C03Chr *);
f32 func_00267390(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);

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

static inline s32 inl_same(C03AW *w) {
    s32 j;
    for (j = 1; j < 2; j++) if (w->hist[0] != w->hist[j]) break;
    return j < 2;
}

static inline s32 inl_t(C03Chr *e, C03AW *w) {
    s32 t = -1;
    if (w->n78 > 0 && w->hist[0]) t = func_00170dd8(e->p130->h4C, w->hist[0]->x0);
    return t;
}

/* needs make: uses rodata */
f32 func_00267390(f32 *, f32 *);

static inline f32 inl_wrap(f32 v) {
    for (;;) {
        if (v > 3.14159251f) { v -= 6.28318501f; continue; }
        if (v < -3.14159251f) { v += 6.28318501f; continue; }
        break;
    }
    return v;
}
#include "data/data_0035.h"
