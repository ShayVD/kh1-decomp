/* Hand-matched functions (worker c03). Built without strict aliasing. */
#include "common.h"
#include "platform/math.h"

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
typedef struct { u16 idx; u8 type; u8 pad3[3]; } C03Ch;
typedef struct { f32 t[3]; s32 parent; f32 r[3]; f32 s[3]; } C03Jnt;
typedef struct { f32 t[4]; f32 x[4]; f32 r[4]; f32 s[4]; } C03Pose;
typedef struct {
    u8 pad[0x10];
    s32 n10;             /* 0x10 */
    C03BF *p14;          /* 0x14 */
    s32 n18;             /* 0x18 */
    C03Ch *p1C;          /* 0x1C */
    s32 n20;             /* 0x20 */
    C03Ch *p24;          /* 0x24 */
    void *p28;           /* 0x28 */
    s32 n2C;             /* 0x2C */
    C03Jnt *p30;         /* 0x30 */
} C03Bits;
typedef struct { s16 h0; s16 h2; u8 pad4[0xC]; f32 v10[4]; f32 v20[4]; } C03Lnk;
typedef struct {
    C03Hdr **p0;         /* 0x0 */
    C03Bits *p4;         /* 0x4 */
    f32 f8;              /* 0x8 */
    u32 wC;              /* 0xC */
    u8 pad10[0x90 - 0x10];
    f32 v90[4];          /* 0x90 */
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

s16 D_00574F30[0x40] ALIGNED(16);

void *func_00121e28(s32, void *);
void func_00121eb0(void *);
void func_00121f30(void *, void *);
void func_001625c8(C03Mtx *, C03Mtx *);
void func_00162848(f32 *, C03Mtx *, f32 *);
void func_00164ba8(C03Mdl *, C03Bits *);
void func_001655e0(f32 (*)[4], C03Mdl *, f32, C03Bits *);
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
    func_001655e0((f32 (*)[4])pos, o, f, b);
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

extern s32 D_0035BCA8[];
extern C03Act *D_00575328[];
extern C03Prm D_0035AE80;
extern s32 D_0035BCB0;

s32 func_00170dd8(u16, s32);
u32 func_001627e8(s32);
s32 func_00123368(C03Chr *);
s32 func_00141200(C03Chr *, s32);
s32 func_0012f040(C03Chr *, s32);
void func_0012ec60(C03Chr *, s32, f32 *);
s32 func_0012ee70(C03Chr *, s32);
C03Chr *func_00123158(C03Chr *, C03Chr *);
void func_00171b18(C03Chr *, C03AW *);
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

s32 func_0016a3f8(C03Chr *e, C03AW *w) {
    C03Act *last;
    s32 again;
    C03Act *sel;
    C03Act *a;
    C03Act *cur;
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
            { C03Act **tb = D_00575328; i = func_001627e8(n << 12) >> 12; sel = tb[i]; }
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

/* needs make: uses rodata */

extern C03Mtx D_00573F10[];
extern f32 D_00574F10[4];
extern f32 D_00574F20[4];

void func_001626f0(f32 *, f32 *, f32 *, C03Mtx);
void func_00162c5c(C03Mtx, C03Mtx, C03Mtx);
void func_00163490(C03Mdl *);
void func_001636d0(C03Mdl *, C03Bits *);
f32 func_00164768(void *, C03Ch *, s32);
void func_00165450(C03Mdl *, C03Bits *, f32);
f32 func_00267390(f32 *, f32 *);
void func_002674b0(f32 *, f32 *, f32);
void sceVu0UnitMatrix(f32 (*)[4]);

static inline f32 inl_wrap(f32 v) {
    for (;;) {
        if (v > 3.14159251f) { v -= 6.28318501f; continue; }
        if (v < -3.14159251f) { v += 6.28318501f; continue; }
        break;
    }
    return v;
}

void func_001655e0(f32 (*pos)[4], C03Mdl *o, f32 f, C03Bits *b) {
    C03Mtx m;
    s32 fi;
    s32 i, k;
    f32 v;
    C03Jnt *jp;
    C03Mtx *mp;
    s32 j;

    fi = f * 256.0f;
    D_00574F20[0] = PlatSqrtf(func_00267390(pos[0], pos[0]));
    D_00574F20[1] = PlatSqrtf(func_00267390(pos[1], pos[1]));
    D_00574F20[2] = PlatSqrtf(func_00267390(pos[2], pos[2]));
    if (o->p4 != b && b) func_00164ba8(o, b);
    o->p4 = b;
    o->wC &= 0xFFFF;
    o->f8 = f;
    sceVu0CopyMatrix(D_00573F10[0], pos);
    D_00573F10[0][1][0] = -D_00573F10[0][1][0];
    D_00573F10[0][1][1] = -D_00573F10[0][1][1];
    D_00573F10[0][1][2] = -D_00573F10[0][1][2];
    D_00573F10[0][2][0] = -D_00573F10[0][2][0];
    D_00573F10[0][2][1] = -D_00573F10[0][2][1];
    D_00573F10[0][2][2] = -D_00573F10[0][2][2];
    sceVu0CopyMatrix(o->mD0, D_00573F10[0]);
    func_002674b0(D_00573F10[0][0], D_00573F10[0][0], D_00574F20[0]);
    func_002674b0(D_00573F10[0][1], D_00573F10[0][1], D_00574F20[1]);
    func_002674b0(D_00573F10[0][2], D_00573F10[0][2], D_00574F20[2]);
    D_00574F10[0] = D_00573F10[0][3][0];
    D_00574F10[1] = D_00573F10[0][3][1];
    D_00574F10[2] = D_00573F10[0][3][2];
    o->vA0[2] = D_00573F10[0][3][2] = o->vA0[1] = D_00573F10[0][3][1] = o->vA0[0] = D_00573F10[0][3][0] = 0.0f;
    if (b) {
        for (i = 0; i < b->n18; i++) {
            v = func_00164768(b->p28, &b->p1C[i], fi);
            k = b->p1C[i].type & 0xF;
            switch (k) {
            case 1: case 2: case 3:
                ((C03Pose *)o->p150)[b->p1C[i].idx].t[k - 1] = v;
                break;
            case 4: case 5: case 6:
                v = inl_wrap(v);
                ((C03Pose *)o->p150)[b->p1C[i].idx].r[k - 4] = v;
                break;
            case 7: case 8: case 9:
                ((C03Pose *)o->p150)[b->p1C[i].idx].s[k - 7] = v;
                break;
            }
        }
        for (i = 0; i < b->n20; i++) {
            v = func_00164768(b->p28, &b->p24[i], fi);
            k = b->p24[i].type & 0xF;
            switch (k) {
            case 1: case 2: case 3:
                b->p30[b->p24[i].idx].t[k - 1] = v;
                break;
            case 4: case 5: case 6:
                v = inl_wrap(v);
                b->p30[b->p24[i].idx].r[k - 4] = v;
                break;
            case 7: case 8: case 9:
                b->p30[b->p24[i].idx].s[k - 7] = v;
                break;
            }
        }
        jp = &b->p30[1];
        for (j = 1; j < b->n2C; j++, jp++) {
            func_001626f0(jp->t, jp->r, jp->s, m);
            func_00162c5c(D_00573F10[j], D_00573F10[jp->parent], m);
        }
        o->vA0[0] = D_00573F10[b->n2C - 1][3][0] * D_00574F20[0];
        o->vA0[1] = D_00573F10[b->n2C - 1][3][1] * D_00574F20[1];
        o->vA0[2] = D_00573F10[b->n2C - 1][3][2] * D_00574F20[2];
        func_001636d0(o, b);
        func_00165450(o, b, f);
    } else {
        func_00163490(o);
    }
    if (fabsf(D_00574F20[0] - 1.0f) > 0.005f || fabsf(D_00574F20[1] - 1.0f) > 0.005f
        || fabsf(D_00574F20[2] - 1.0f) > 0.005f) {
        sceVu0UnitMatrix(m);
        m[0][0] = D_00574F20[0];
        m[1][1] = D_00574F20[1];
        m[2][2] = D_00574F20[2];
        for (i = 0; i < (*o->p0)->n; i++) func_00162c5c(o->p154[i], m, o->p154[i]);
    }
    o->v90[0] = o->vA0[0] + D_00574F10[0];
    o->v90[1] = o->vA0[1] + D_00574F10[1];
    o->v90[2] = o->vA0[2] + D_00574F10[2];
    for (i = 0; i < (*o->p0)->n; i++) {
        o->p154[i][3][0] += D_00574F10[0];
        o->p154[i][3][1] += D_00574F10[1];
        o->p154[i][3][2] += D_00574F10[2];
    }
}
