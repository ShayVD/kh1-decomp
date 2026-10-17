/* Hand-matched functions (worker c03). Built without strict aliasing. */
#include "common.h"

/* ---- func_00164f18 ---- */
typedef union { s32 w; struct { u16 lo, hi; } h; } C03Key;
typedef struct { f32 t; union { u8 b4; s32 w3[3]; } u; } C03KeyF;
typedef struct { C03Key k; s32 n; C03KeyF *keys; } C03Trk;
typedef struct { u8 pad[0x3C]; C03Trk *tbl; } C03Mot;
typedef struct { s32 kind; s32 v[3]; } C03Ev;

void func_00167ac0(void *, s32, u32);

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

s32 func_00164f18(void *a, C03Mot *o, C03Ev *out, s32 max, f32 lo, f32 hi) {
    s32 idx;
    C03KeyF *k;
    s32 n, j;
    u32 m;

    if (o == 0) return 0;
    idx = 0;
    k = inl_001676f8(o, 0x2FFFF, &idx, lo, hi);
    if (k) func_00167ac0(a, 0, k->u.b4);
    idx = 0;
    k = inl_001676f8(o, 0x3FFFF, &idx, lo, hi);
    n = 0;
    for (j = 0; j < 4; j++) {
        idx = 0;
        for (;;) {
            k = inl_001676f8(o, 0x40000 | j, &idx, lo, hi);
            if (!k) break;
            if (n++ < max) {
                out[n - 1].kind = 0;
                for (m = 0; m < 3; m++) out[n - 1].v[m] = k->u.w3[m];
            }
            idx++;
        }
    }
    for (j = 0; j < 4; j++) {
        idx = 0;
        for (;;) {
            k = inl_001676f8(o, 0x60000 | j, &idx, lo, hi);
            if (!k) break;
            if (n++ < max) {
                out[n - 1].kind = 1;
                for (m = 0; m < 3; m++) out[n - 1].v[m] = k->u.w3[m];
            }
            idx++;
        }
    }
    return max < n ? max : n;
}

/* ---- func_00165cf8 ---- */
typedef f32 C03Mtx[4][4];
typedef struct { u32 n; u32 ids[1]; } C03Ids;
typedef struct { u8 pad[0x90]; s32 x90[4]; } C03Sk8;
typedef struct { C03Ids *p; s32 pad[3]; } C03HdE;
typedef struct { s16 n; s16 pad2; s32 x4; C03Sk8 *p8; s32 xC; C03HdE e[1]; } C03Hdr;
typedef struct { u32 lo:21; u32 k:2; u32 hi:9; } C03BF;
typedef struct { u8 pad[0x10]; s32 n10; C03BF *p14; } C03Bits;
typedef struct { s16 h0; s16 h2; u8 pad4[0xC]; f32 v10[4]; f32 v20[4]; } C03Lnk;
typedef struct {
    C03Hdr **p0;         /* 0x0 */
    C03Bits *p4;         /* 0x4 */
    u8 pad8[0xA0 - 0x8];
    f32 vA0[4];          /* 0xA0 */
    f32 vB0[4];          /* 0xB0 */
    f32 vC0[4];          /* 0xC0 */
    C03Mtx mD0;          /* 0xD0 */
    C03Mtx m110;         /* 0x110 */
    C03Mtx *p150;        /* 0x150 */
    C03Mtx *p154;        /* 0x154 */
    void *p158;          /* 0x158 */
    void *p15C;          /* 0x15C */
    void *p160;          /* 0x160 */
    f32 (*p164)[4];      /* 0x164 */
    f32 (*p168)[4];      /* 0x168 */
    C03Lnk *p16C;        /* 0x16C */
} C03Mdl;

extern s16 D_00574F30[];

void *func_00121e28(s32, void *);
void func_00121eb0(void *);
void func_00121f30(void *, void *);
void func_001625c8(C03Mtx *, C03Mtx *);
void func_00162848(f32 *, C03Mtx *, f32 *);
void func_00164ba8(C03Mdl *, C03Bits *);
void func_001655e0(f32 *, C03Mdl *, f32, C03Bits *);
void func_002675a8(f32 *, f32 *);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);

void func_00165cf8(f32 *pos, C03Mdl *o, C03Bits *b, f32 f) {
    C03Mtx m;
    s32 n, i;
    s32 j;
    C03Hdr *h;
    C03Ids *t;

    if (o->p15C) { func_00121eb0(o->p15C); o->p15C = 0; }
    if (o->p160) { func_00121eb0(o->p160); o->p160 = 0; }
    if (o->p164) { func_00121eb0(o->p164); o->p164 = 0; }
    if (o->p168) { func_00121eb0(o->p168); o->p168 = 0; }
    if (o->p16C) { func_00121eb0(o->p16C); o->p16C = 0; }
    n = 0;
    h = *o->p0;
    t = h->e[h->xC].p;
    if (t) t = (C03Ids *)((u8 *)t + 8);
    for (i = 0; i < o->p4->n10; i++) {
        u32 wa = *(u32 *)&o->p4->p14[i];
        u32 wb = *(u32 *)&b->p14[i];
        u32 a = (wa >> 21) & 3;
        u32 c;
        if (a == 0) continue;
        c = (wb >> 21) & 3;
        if (c == 0 || a != c) continue;
        if (t) {
            for (j = 0; j < t->n; j++) {
                if (i == ((u32 *)t)[j + 1]) { D_00574F30[n] = i; n++; break; }
            }
            if (j < t->n) continue;
        }
        for (j = 0; j < 4; j++) {
            if (i == (*o->p0)->p8->x90[j] - 1) { D_00574F30[n] = i; n++; break; }
        }
    }
    func_00121e28(n * 48 + 48, &o->p16C);
    func_001625c8(&o->mD0, &m);
    for (i = 0; i < n; i++) {
        u32 c;
        c = o->p4->p14[D_00574F30[i]].k;
        o->p16C[i].h0 = D_00574F30[i];
        o->p16C[i].h2 = c;
        if (c == 1) func_00162848(o->p16C[i].v10, &m, o->p154[D_00574F30[i] + 1][3]);
        else func_00162848(o->p16C[i].v10, &m, o->p154[D_00574F30[i] + 2][3]);
    }
    o->p16C[n].h0 = -1;
    func_002675a8(o->vB0, o->vA0);
    sceVu0CopyMatrix(o->m110, o->mD0);
    o->p15C = o->p158;
    func_00121f30(o->p158, &o->p15C);
    func_00121e28((*o->p0)->n * 16, &o->p164);
    for (i = 0; i < (*o->p0)->n; i++) func_002675a8(o->p164[i], o->p150[i][0]);
    func_00121e28((*o->p0)->n * 64, &o->p158);
    func_00164ba8(o, b);
    func_001655e0(pos, o, f, b);
    func_002675a8(o->vC0, o->vA0);
    o->p160 = o->p158;
    func_00121f30(o->p158, &o->p160);
    func_00121e28((*o->p0)->n * 16, &o->p168);
    for (i = 0; i < (*o->p0)->n; i++) func_002675a8(o->p168[i], o->p150[i][0]);
    func_001625c8(&o->mD0, &m);
    for (i = 0; o->p16C[i].h0 >= 0; i++) {
        if (o->p16C[i].h2 == 1) func_00162848(o->p16C[i].v20, &m, o->p154[o->p16C[i].h0 + 1][3]);
        else func_00162848(o->p16C[i].v20, &m, o->p154[o->p16C[i].h0 + 2][3]);
    }
    func_00121e28((*o->p0)->n * 64, &o->p158);
}
