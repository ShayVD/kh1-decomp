/* Motion curves and poses, without strict aliasing (docs/modules.md
 * "Session 52"): func_00164768 evaluates a key curve (pre / post modes),
 * func_00164f18 collects a motion's events between two times, the pose
 * builders func_001655e0, func_00165cf8, func_00166248 and func_00166570
 * (the bone chain with ground contact).  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/math.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h59.h"
#include "data/pieces/D_00351BC8.h"
#include "data/types/nostrict_text_00150000_h36.h"
#include "data/pieces/D_002BC0F0.h"

/* func_00164768 (from hand/nostrict/text_00150000_s6_08.c). */
typedef struct { s32 w; f32 v; f32 in; f32 out; } Key;
typedef struct { u16 h0; u16 r0:4; u16 pre:2; u16 post:2; u16 r1:8; u16 start; } CurveX;
typedef struct { u8 b0; u8 b1; u8 b2; u8 n; u16 start; } CurveB;
typedef union { CurveX c; CurveB b; } Curve;
f32 func_00164768(Key *k, Curve *c, s32 t) {
    s32 lo, hi, mid, t0, t1, tm;
    Key *a, *b;
    f32 slope, dt, span, ft;
    if (c->b.n == 1) return k[c->c.start].v;
    lo = c->c.start;
    a = (Key *)((u32)(lo << 4) + (u32)k);
    t0 = a->w >> 8;
    if (t <= t0) {
        switch (c->c.pre) {
        case 0:
            return a->v;
        case 1:
            {
            Key *p, *n1; k = a; p = k; n1 = k + 1;
            dt = (f32)((n1->w >> 8) - t0);
            if ((u8)p->w == 1 && dt != 0.0f) slope = (n1->v - p->v) / dt;
            else slope = p->in;
            return p->v - (f32)((p->w >> 8) - t) * slope;
            }
        case 2:
            dt = (f32)t0;
            span = (f32)((k[lo + c->b.n - 1].w >> 8) - t0);
            while ((f32)t < dt) t = (f32)t + span;
            break;
        }
    }
    b = &k[lo + c->b.n] - 1;
    t1 = b->w >> 8;
    if (t >= t1) {
        switch (c->c.post) {
        case 0:
            return b->v;
        case 1:
            {
            Key *p1 = b - 1;
            dt = (f32)(t1 - (p1->w >> 8));
            if ((u8)b->w == 1 && dt != 0.0f) slope = (b->v - p1->v) / dt;
            else slope = b->out;
            return b->v + (f32)(t - (b->w >> 8)) * slope;
            }
        case 2:
            dt = (f32)t1;
            span = (f32)(t1 - (k[c->c.start].w >> 8));
            while (dt < (f32)t) t = (f32)t - span;
            break;
        }
    }
    hi = lo + c->b.n - 1;
    while (hi - lo >= 2) {
        mid = (lo + hi) / 2;
        tm = k[mid].w >> 8;
        if (t < tm) hi = mid;
        else if (tm < t) lo = mid;
        else return k[mid].v;
    }
    k += hi;
    {
        f32 va, ta, oa; u8 ty;
        f32 tb, vb, ib;
        vb = k->v;
        tb = (f32)(k->w >> 8);
        ib = k->in;
        k--; //dep:0,1,2
        oa = k->out; //dep:3
        ta = (f32)(k->w >> 8); //dep:3
        va = k->v; //dep:3
        ty = (u8)k->w; //dep:3

        switch (ty) {
        case 0:
            return va;
        case 1:
            return va + ((vb - va) * ((f32)t - ta)) / (tb - ta);
        default: {
            f32 inv, d2, inv2, d3, r, q, p, s;
            inv = 1.0f / (tb - ta);
            dt = (f32)t - ta;
            d2 = dt * dt;
            inv2 = inv * inv;
            d3 = d2 * dt;
            r = d2 * 3.0f * inv2;
            q = d2 * inv;
            p = d3 * inv2;
            s = p * 2.0f * inv;
            return va * (s - r + 1.0f) + vb * (r - s) + oa * (p - q * 2.0f + dt) + ib * (p - q);
        }
        }
    }
}

/* func_00164ba8 (from hand/nostrict/text_00150000_h59.c). */
typedef struct {
    Mdl59 **x0;
    u8 pad4[8];
    s32 xC;
    u8 pad10[0x150 - 0x10];
    M64_59 *x150;
    M64_59 *x154;
    M64_59 *x158;
} Ent63;
typedef struct { u16 idx; u16 kind; f32 v; } Key59;
typedef struct { u8 pad[0x14]; u32 *flags; u8 pad18[0x34 - 0x18]; s32 nk; Key59 *k; } Anim59;
void func_00162cd0(f32 *, f32 *, M64_59 *);
void func_00164ba8(Ent63 *e, Anim59 *a) {
    s32 i, j;
    for (i = 0; i < (*e->x0)->n; i++) {
        for (j = 0; j < 3; j++) {
            e->x150[i].m[0][j] = (*e->x0)->src[i].a[j];
            e->x150[i].m[2][j] = (*e->x0)->src[i].b[j];
            e->x150[i].m[3][j] = (*e->x0)->src[i].c[j];
        }
    }
    for (j = 0; j < a->nk; j++) {
        u32 kind = a->k[j].kind;
        f32 v = a->k[j].v;
        switch (kind) {
        case 1: case 2: case 3:
            e->x150[a->k[j].idx].m[-1][kind + 3] = v;
            break;
        case 4: case 5: case 6:
            e->x150[a->k[j].idx].m[1][kind] = v;
            break;
        case 7: case 8: case 9:
            e->x150[a->k[j].idx].m[1][kind + 1] = v;
            break;
        }
    }
    for (i = 0; i < (*e->x0)->n; i++) {
        u32 f = a->flags[i];
        if (!(f >> 26 & 1) && (f >> 25 & 1)) {
            func_00162cd0(e->x150[i].m[2], e->x150[i].m[3], &e->x158[i]);
        }
    }
}

/* func_00164e00 (from hand/nostrict/text_00150000_h36.c). */
typedef struct { f32 t; u8 pad[12]; } AnimKey;
typedef struct { union { s32 w; struct { u16 lo, hi; } h; } id; s32 n; AnimKey *keys; } AnimTrk;
typedef struct { u8 pad[0x3C]; AnimTrk *trk; } AnimObj;
AnimKey *func_00164e00(AnimObj *o, u32 key, f32 t) {
    AnimTrk *e = o->trk;
    AnimTrk *f;
    u32 lo = key & 0xFFFF;
    u32 hi = key >> 16;
    AnimKey *k;
    s32 a, b, r;
    for (; e->id.w != -1; e++) {
        if (e->id.h.hi == hi && (lo == 0xFFFF || e->id.h.lo == lo)) {
            f = e;
            goto found;
        }
    }
    f = 0;
found:
    if (f == 0) return 0;
    k = f->keys;
    a = 0;
    r = -1;
    b = f->n - 1;
    if (!(t < k[0].t)) {
        if (k[b].t <= t) {
            r = b;
        } else {
            while (b - a >= 2) {
                s32 m = (a + b) / 2;
                if (t < k[m].t) b = m;
                else if (k[m].t < t) a = m;
                else { r = m; goto done; }
            }
            r = a;
        }
    }
done:
    if (r < 0) return 0;
    return &k[r];
}

/* func_00164f18 (from hand/nostrict/text_00160000_c03.c). */
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
/* ---- func_00164f18 ---- */
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

/* func_00165450 (from hand/nostrict/text_00150000_h59.c). */
typedef struct { u8 pad[0xC]; u32 xC; } E5450;
typedef struct { u8 pad[4]; u8 on; } K5450;
#define func_00164e00 ((K5450 *(*)(void *, s32, f32)) func_00164e00)
void func_00165450(E5450 *e, void *a, f32 t) {
    K5450 *k;
    k = func_00164e00(a, 0x10000, t);
    if (k && k->on) e->xC |= 0x10000;
    k = func_00164e00(a, 0x10001, t);
    if (k && k->on) e->xC |= 0x20000;
    k = func_00164e00(a, 0x10002, t);
    if (k && k->on) e->xC |= 0x40000;
    k = func_00164e00(a, 0x10003, t);
    if (k && k->on) e->xC |= 0x80000;
    k = func_00164e00(a, 0, t);
    if (k && k->on) e->xC |= 0x100000;
    k = func_00164e00(a, 0x50000, t);
    if (k && k->on) e->xC |= 0x400000;
    k = func_00164e00(a, 0x70000, t);
    if (k && k->on) e->xC |= 0x800000;
}
#undef func_00164e00

/* func_001655e0 (from hand/nostrict/text_00160000_c03.c). */
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
extern C03Mtx D_00573F10[];
extern f32 D_00574F10[4];
extern f32 D_00574F20[4];
void func_001626f0(f32 *, f32 *, f32 *, C03Mtx);
void func_00162c5c(C03Mtx, C03Mtx, C03Mtx);
void func_00163490(C03Mdl *);
void func_001636d0(C03Mdl *, C03Bits *);
static inline f32 inl_wrap(f32 v) {
    for (;;) {
        if (v > 3.14159251f) { v -= 6.28318501f; continue; }
        if (v < -3.14159251f) { v += 6.28318501f; continue; }
        break;
    }
    return v;
}
#define func_00164ba8 ((void (*)(C03Mdl *, C03Bits *)) func_00164ba8)
#define func_00164768 ((f32 (*)(void *, C03Ch *, s32)) func_00164768)
#define func_00165450 ((void (*)(C03Mdl *, C03Bits *, f32)) func_00165450)
void func_001655e0(f32 (*pos)[4], C03Mdl *o, f32 f, C03Bits *b) {
    C03Mtx m;
    s32 fi;
    s32 i, k;
    f32 v;
    C03Jnt *jp;
    C03Mtx *mp;
    s32 j;

    fi = f * 256.0f;
    D_00574F20[0] = PlatSqrtf(PlatVu0InnerProduct(pos[0], pos[0]));
    D_00574F20[1] = PlatSqrtf(PlatVu0InnerProduct(pos[1], pos[1]));
    D_00574F20[2] = PlatSqrtf(PlatVu0InnerProduct(pos[2], pos[2]));
    if (o->p4 != b && b) func_00164ba8(o, b);
    o->p4 = b;
    o->wC &= 0xFFFF;
    o->f8 = f;
    PlatVu0CopyMatrix(D_00573F10[0], pos);
    D_00573F10[0][1][0] = -D_00573F10[0][1][0];
    D_00573F10[0][1][1] = -D_00573F10[0][1][1];
    D_00573F10[0][1][2] = -D_00573F10[0][1][2];
    D_00573F10[0][2][0] = -D_00573F10[0][2][0];
    D_00573F10[0][2][1] = -D_00573F10[0][2][1];
    D_00573F10[0][2][2] = -D_00573F10[0][2][2];
    PlatVu0CopyMatrix(o->mD0, D_00573F10[0]);
    PlatVu0DivVector(D_00573F10[0][0], D_00573F10[0][0], D_00574F20[0]);
    PlatVu0DivVector(D_00573F10[0][1], D_00573F10[0][1], D_00574F20[1]);
    PlatVu0DivVector(D_00573F10[0][2], D_00573F10[0][2], D_00574F20[2]);
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
        PlatVu0UnitMatrix(m);
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
#undef func_00164ba8
#undef func_00164768
#undef func_00165450

/* func_00165cf8 (from hand/nostrict/text_00160000_c03.c). */
s16 D_00574F30[0x40] ALIGNED(16);
void *func_00121e28(s32, void *);
void func_00121eb0(void *);
void func_00121f30(void *, void *);
void func_001625c8(C03Mtx *, C03Mtx *);
void func_00162848(f32 *, C03Mtx *, f32 *);
#define func_00164ba8 ((void (*)(C03Mdl *, C03Bits *)) func_00164ba8)
/* ---- func_00165cf8 ---- */
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
    PlatVu0CopyVector(o->vB0, o->vA0);
    PlatVu0CopyMatrix(o->m110, o->mD0);
    o->p15C = o->p158;
    func_00121f30(o->p158, &o->p15C);
    func_00121e28((*o->p0)->n * 16, &o->p164);
    for (i = 0; i < (*o->p0)->n; i++) PlatVu0CopyVector(o->p164[i], o->p150[i][0]);
    func_00121e28((*o->p0)->n * 64, &o->p158);
    func_00164ba8(o, b);
    func_001655e0((f32 (*)[4])pos, o, f, b);
    PlatVu0CopyVector(o->vC0, o->vA0);
    o->p160 = o->p158;
    func_00121f30(o->p158, &o->p160);
    func_00121e28((*o->p0)->n * 16, &o->p168);
    for (i = 0; i < (*o->p0)->n; i++) PlatVu0CopyVector(o->p168[i], o->p150[i][0]);
    func_001625c8(&o->mD0, &m);
    for (i = 0; o->p16C[i].h0 >= 0; i++) {
        if (o->p16C[i].h2 == 1) func_00162848(o->p16C[i].v20, &m, o->p154[o->p16C[i].h0 + 1][3]);
        else func_00162848(o->p16C[i].v20, &m, o->p154[o->p16C[i].h0 + 2][3]);
    }
    func_00121e28((*o->p0)->n * 64, &o->p158);
}
#undef func_00164ba8

/* func_00166248 (from hand/nostrict/text_00160000_s10_r2_10.c). */
typedef struct { s16 h0; s16 h2; u8 pad4[0xC]; f32 v10[4]; f32 v20[4]; } __attribute__((aligned(8))) C03Lnk_66248;
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
    C03Lnk_66248 *p16C;        /* 0x16C */
} C03Mdl_66248;
/* func_00166248 (r2_10 s10): MATCH, hand/nostrict. session9 r2_1 4w draft plus CONTEXT_ONLY {} stubs of func_00164ba8 and func_001655e0 above it (both matched in src/hand/nostrict/text_00150000_h59.c and text_00160000_c03.c; a stub for func_00121e28 must NOT be added: it costs 2w). With the stubs the calls get REG_EH_REGION 0 and the entry bltz is no longer bltzl. */
void func_00166248(f32 *pos, C03Mdl_66248 *o, C03Bits *b, f32 f) {
    C03Mtx m;
    s32 i, j, n;
    if (o->p15C) {
        func_00121eb0(o->p15C);
        o->p15C = o->p160;
        func_00121f30(o->p160, &o->p15C);
        o->p160 = 0;
    }
    if (o->p164) {
        func_00121eb0(o->p164);
        o->p164 = o->p168;
        func_00121f30(o->p168, &o->p164);
        o->p168 = 0;
    }
    PlatVu0CopyVector(o->vB0, o->vC0);
    PlatVu0CopyMatrix(o->m110, o->mD0);
    n = 0;
    while (o->p16C[n].h0 >= 0) {
        u32 k = b->p14[o->p16C[n].h0].k;
        if (k == 0 || k != o->p16C[n].h2) {
            for (j = n; o->p16C[j].h0 >= 0; j++) o->p16C[j] = o->p16C[j + 1];
        } else {
            PlatVu0CopyVector(o->p16C[n].v10, o->p16C[n].v20);
            n++;
        }
    }
    func_00164ba8(o, b);
    func_001655e0((f32 (*)[4])pos, o, f, b);
    PlatVu0CopyVector(o->vC0, o->vA0);
    o->p160 = o->p158;
    func_00121f30(o->p158, &o->p160);
    func_00121e28((*o->p0)->n * 16, &o->p168);
    for (i = 0; i < (*o->p0)->n; i++) PlatVu0CopyVector(o->p168[i], o->p150[i][0]);
    func_001625c8(&o->mD0, &m);
    for (i = 0; o->p16C[i].h0 >= 0; i++) {
        if (o->p16C[i].h2 == 1) func_00162848(o->p16C[i].v20, &m, o->p154[o->p16C[i].h0 + 1][3]);
        else func_00162848(o->p16C[i].v20, &m, o->p154[o->p16C[i].h0 + 2][3]);
    }
    func_00121e28((*o->p0)->n * 64, &o->p158);
}

/* func_00166570 (from hand/nostrict/text_00160000_s16_s16m1.c). */
typedef f32 G2Mtx[4][4];
typedef struct { u32 par:10; u32 pad:20; u32 flag:1; u32 top:1; } G2BBits;
typedef struct { f32 s[4]; f32 r[4]; f32 t[3]; G2BBits b; } G2Bone;
typedef struct { f32 f[4]; u8 pad[0x90 - 0x10]; s32 x90[4]; } G2Sk8;
typedef struct { s16 n; s16 pad2; G2Bone *bones; G2Sk8 *p8; s32 xC; } G2Hdr;
typedef struct { s16 h0; s16 h2; s32 w4; u8 pad8[8]; f32 v10[4]; f32 v20[4]; } G2Lnk;
typedef struct {
    G2Hdr **p0;          /* 0x0 */
    void *p4;            /* 0x4 */
    f32 f8;              /* 0x8 */
    s32 wC;              /* 0xC */
    u8 pad10[0x90 - 0x10];
    f32 v90[4];          /* 0x90 */
    f32 vA0[4];          /* 0xA0 */
    f32 vB0[4];          /* 0xB0 */
    f32 vC0[4];          /* 0xC0 */
    G2Mtx mD0;           /* 0xD0 */
    G2Mtx m110;          /* 0x110 */
    G2Mtx *p150;         /* 0x150 */
    G2Mtx *p154;         /* 0x154 */
    G2Mtx *p158;         /* 0x158 */
    G2Mtx *p15C;         /* 0x15C */
    G2Mtx *p160;         /* 0x160 */
    f32 (*p164)[4];      /* 0x164 */
    f32 (*p168)[4];      /* 0x168 */
    G2Lnk *p16C;         /* 0x16C */
} G2Mdl;
typedef struct { f32 p[4]; f32 d[4]; f32 out[4]; s16 hit; } G2Ray;
void func_00118590(G2Ray *, s32);
void func_001627d0(f32 *, f32 *, f32 *);
void func_001628a0(G2Mtx, G2Mtx, f32 *);
f32 func_00162c20(f32 *);
void func_00162d00(f32 *, s32, G2Mtx, G2Mtx, f32 *, f32, f32, f32, f32);
static inline void inl_scl(G2Mtx d, G2Mtx s, f32 *v) {
    PlatVu0ScaleVectorXYZ(d[0], s[0], v[0]);
    PlatVu0ScaleVectorXYZ(d[1], s[1], v[1]);
    PlatVu0ScaleVectorXYZ(d[2], s[2], v[2]);
    PlatVu0CopyVector(d[3], s[3]);
}
extern G2Mtx D_00573F10_00166570[] __asm__("D_00573F10");
#define D_00573F10 D_00573F10_00166570
#define func_001625c8 ((void (*)(G2Mtx, G2Mtx)) func_001625c8)
#define func_00162848 ((void (*)(f32 *, G2Mtx, f32 *)) func_00162848)
#define func_00162c5c ((void (*)(G2Mtx, G2Mtx, G2Mtx)) func_00162c5c)
/* func_00166570: MATCHED (session 16, s16m1), hand/nostrict. From s7 w7's 21w draft: the three
 * work matrices are one local array mm[3] (same frame offsets 0/64/128), the bone-chain loop uses
 * mm[1]/mm[2] directly (s11w37's preheader), and a pointer mp = mm, set after `bones = ...`, is used
 * for the two post-loop mm[2][0]/mm[1][0] arguments. mp is a REG copy of the soft frame pointer:
 * gcse neither hashes it as an expression nor copy-propagates a hard register, so (plus mp 128) /
 * (plus mp 64) are not PRE-redundant with the pre-loop (plus $fp N); mp gets REG_EQUIV $fp, no hard
 * register, and reload rematerialises it as sp: the original's fresh `addiu a1,sp,128 / addiu
 * a2,sp,64` after the loop and the `move s6,s2; move s2,s0` preheader copies. */
void func_00166570(G2Mtx pos, G2Mdl *o, f32 f) {
    G2Mtx mm[3];
    G2Mtx *mp;
    f32 v[4];
    f32 w[4];
    f32 e[4];
    f32 ff[4];
    G2Mtx m100;
    G2Ray q;
    s32 i;
    G2Bone *bones;
    G2Lnk *lnk;
    s32 fl4;
    s32 par;
    s32 j, found;
    f32 h;
    G2Sk8 *p8;
    s32 fl;

    fl4 = (o->wC >> 4) & 1;
    D_00574F20[0] = PlatSqrtf(PlatVu0InnerProduct(pos[0], pos[0]));
    D_00574F20[1] = PlatSqrtf(PlatVu0InnerProduct(pos[1], pos[1]));
    D_00574F20[2] = PlatSqrtf(PlatVu0InnerProduct(pos[2], pos[2]));
    PlatVu0CopyMatrix(D_00573F10[0], pos);
    D_00573F10[0][1][0] = -D_00573F10[0][1][0];
    D_00573F10[0][1][1] = -D_00573F10[0][1][1];
    D_00573F10[0][1][2] = -D_00573F10[0][1][2];
    D_00573F10[0][2][0] = -D_00573F10[0][2][0];
    D_00573F10[0][2][1] = -D_00573F10[0][2][1];
    D_00573F10[0][2][2] = -D_00573F10[0][2][2];
    PlatVu0DivVector(D_00573F10[0][0], D_00573F10[0][0], D_00574F20[0]);
    PlatVu0DivVector(D_00573F10[0][1], D_00573F10[0][1], D_00574F20[1]);
    PlatVu0DivVector(D_00573F10[0][2], D_00573F10[0][2], D_00574F20[2]);
    PlatVu0InterVectorXYZ(o->vA0, o->vC0, o->vB0, f);
    o->v90[0] = o->vA0[0] * D_00574F20[0] + D_00573F10[0][3][0];
    o->v90[1] = o->vA0[1] * D_00574F20[1] + D_00573F10[0][3][1];
    o->v90[2] = o->vA0[2] * D_00574F20[2] + D_00573F10[0][3][2];
    D_00574F10[0] = D_00573F10[0][3][0];
    D_00574F10[1] = D_00573F10[0][3][1];
    D_00574F10[2] = D_00573F10[0][3][2];
    D_00573F10[0][3][0] = 0.0f;
    D_00573F10[0][3][1] = 0.0f;
    D_00573F10[0][3][2] = 0.0f;
    for (i = 0; o->p16C[i].h0 >= 0; i++) {
        o->p16C[i].w4 = (*o->p0)->bones[(*o->p0)->bones[o->p16C[i].h0].b.par].b.flag;
        (*o->p0)->bones[(*o->p0)->bones[o->p16C[i].h0].b.par].b.flag = 1;
    }
    lnk = o->p16C;
    bones = (*o->p0)->bones;
    mp = mm;
    for (i = 0; i < (*o->p0)->n; i++) {
        PlatVu0InterVector(o->p150[i][0], o->p168[i], o->p164[i], f);
        if (bones[i].b.par == 0x3FF) {
            o->p150[i][1][0] = o->p150[i][0][0];
            o->p150[i][1][1] = o->p150[i][0][1];
            o->p150[i][1][2] = o->p150[i][0][2];
        } else {
            func_001627d0(o->p150[i][1], o->p150[bones[i].b.par][1], o->p150[i][0]);
        }
        if (lnk->h0 == i) {
            PlatVu0InterVectorXYZ(v, lnk->v20, lnk->v10, f);
            v[3] = 1.0f;
            func_00162848(v, D_00573F10[0], v);
            o->p158[i][3][0] = o->p150[i][3][0];
            o->p158[i][3][1] = o->p150[i][3][1];
            o->p158[i][3][2] = o->p150[i][3][2];
            PlatVu0InterVectorXYZ(w, o->p160[i][1], o->p15C[i][1], f);
            PlatVu0AddVector(w, w, o->p150[i][3]);
            w[3] = 0.0f;
            switch (lnk->h2) {
            case 1:
                lnk++;
                func_001625c8(o->p154[bones[i].b.par], m100);
                func_00162848(v, m100, v);
                { f32 ln = o->p150[i][0][0] * bones[i + 1].t[0]; func_00162d00(v, 0, o->p158[i], 0, w, ln, 0.0f, 0.0f, 0.0f); }
                inl_scl(mm[0], o->p158[i], o->p150[i][0]);
                func_00162c5c(o->p154[i], o->p154[bones[i].b.par], mm[0]);
                func_00162848(o->p154[i][3], o->p154[bones[i].b.par], o->p150[i][3]);
                o->p154[i][3][3] = 1.0f;
                func_001628a0(o->p158[i], o->p154[i], o->p150[i][1]);
                continue;
            case 2:
            case 3:
                PlatVu0CopyVector(e, o->p164[i + 1]);
                PlatVu0CopyVector(ff, o->p168[i + 1]);
                ff[3] = inl_wrap(ff[3] - e[3]);
                e[3] = 0.0f;
                PlatVu0InterVector(o->p150[i + 1][0], ff, e, f);
                o->p150[i + 1][0][3] = inl_wrap(o->p150[i + 1][0][3] + o->p164[i + 1][3]);
                h = 0.0f;
                func_001625c8(o->p154[bones[i].b.par], m100);
                found = 0;
                if (o->wC & 3) {
                    for (j = 0; j < 4; j++) {
                        if (i == (*o->p0)->p8->x90[j] - 1) {
                            found = 1;
                            if (!(o->wC & 0x20)) h = (*o->p0)->p8->f[j];
                        }
                    }
                }
                if (found) {
                    q.p[0] = v[0] * D_00574F20[0] + D_00574F10[0];
                    q.p[1] = (v[1] - bones[i + 2].t[0]) * D_00574F20[1] + D_00574F10[1];
                    q.p[2] = v[2] * D_00574F20[2] + D_00574F10[2];
                    q.p[3] = 1.0f;
                    q.d[0] = 0.0f;
                    q.d[1] = (bones[i + 2].t[0] + bones[i + 2].t[0] + h) * D_00574F20[1];
                    q.d[2] = 0.0f;
                    q.d[3] = 1.0f;
                    func_00118590(&q, fl4);
                    if (q.hit != -1) {
                        fl = o->wC;
                        if ((fl & 2) || q.out[1] < (v[1] + h) * D_00574F20[1] + D_00574F10[1]) {
                            v[0] = (q.out[0] - D_00574F10[0]) / D_00574F20[0];
                            v[1] = (q.out[1] - D_00574F10[1]) / D_00574F20[1] - h;
                            v[2] = (q.out[2] - D_00574F10[2]) / D_00574F20[2];
                            o->wC = fl | 0x200000;
                        }
                    }
                }
                func_00162848(v, m100, v);
                {
                    f32 ln = o->p150[i][0][0] * bones[i + 1].t[0];
                    f32 *s1 = o->p150[i + 1][0];
                    func_00162d00(v, lnk->h2 - 2, o->p158[i], o->p158[i + 1], w,
                                  ln, o->p150[i][0][0] * s1[0] * bones[i + 2].t[0], 0.0f, s1[3]);
                }
                lnk++;
                inl_scl(mm[0], o->p158[i], o->p150[i][0]);
                func_00162c5c(o->p154[i], o->p154[bones[i].b.par], mm[0]);
                func_00162848(o->p154[i][3], o->p154[bones[i].b.par], o->p150[i][3]);
                o->p154[i][3][3] = 1.0f;
                func_001628a0(o->p158[i], o->p154[i], o->p150[i][1]);
                PlatVu0UnitMatrix(mm[0]);
                mm[0][0][0] = 1.0f / o->p150[i][0][0];
                mm[0][1][1] = 1.0f / o->p150[i][0][1];
                mm[0][2][2] = 1.0f / o->p150[i][0][2];
                func_00162c5c(mm[0], mm[0], o->p158[i + 1]);
                func_001627d0(o->p150[i + 1][1], o->p150[i][0], o->p150[i + 1][0]);
                inl_scl(mm[0], mm[0], o->p150[i + 1][1]);
                func_00162c5c(o->p154[i + 1], o->p154[i], mm[0]);
                func_00162848(o->p154[i + 1][3], o->p154[i], bones[i + 1].t);
                o->p154[i + 1][3][3] = 1.0f;
                func_001628a0(o->p158[i + 1], o->p154[i + 1], o->p150[i + 1][1]);
                i++;
                continue;
            }
        }
        par = bones[i].b.par;
        if (bones[i].b.flag) {
            PlatVu0CopyMatrix(mm[1], o->p15C[i]);
            PlatVu0CopyMatrix(mm[2], o->p160[i]);
            {
            while (par != 0x3FF && !bones[par].b.flag) {
                func_00162c5c(mm[1], o->p15C[par], mm[1]);
                func_00162c5c(mm[2], o->p160[par], mm[2]);
                par = bones[par].b.par;
            } }
            PlatVu0InterVectorXYZ(mm[0][3], mm[2][3], mm[1][3], f);
            PlatVu0InterVectorXYZ(mm[0][0], mp[2][0], mp[1][0], f);
            func_00162c20(mm[0][0]);
            PlatVu0InterVectorXYZ(mm[0][1], mm[2][1], mm[1][1], f);
            func_00162c20(mm[0][1]);
            PlatVu0OuterProduct(mm[0][2], mm[0][0], mm[0][1]);
            func_00162c20(mm[0][2]);
            PlatVu0OuterProduct(mm[0][1], mm[0][2], mm[0][0]);
            func_00162c20(mm[0][1]);
            if (par == 0x3FF) {
                func_00162c5c(o->p158[i], D_00573F10[0], mm[0]);
                inl_scl(o->p154[i], o->p158[i], o->p150[i][1]);
                func_00162848(o->p154[i][3], D_00573F10[0], mm[0][3]);
            } else {
                func_00162c5c(o->p158[i], o->p158[par], mm[0]);
                inl_scl(o->p154[i], o->p158[i], o->p150[i][1]);
                func_00162848(o->p154[i][3], o->p154[par], mm[0][3]);
            }
        }
    }
    for (i = 0; o->p16C[i].h0 >= 0; i++) {
        (*o->p0)->bones[(*o->p0)->bones[o->p16C[i].h0].b.par].b.flag = o->p16C[i].w4;
    }
    if (fabsf(D_00574F20[0] - 1.0f) > 0.005f || fabsf(D_00574F20[1] - 1.0f) > 0.005f
        || fabsf(D_00574F20[2] - 1.0f) > 0.005f) {
        PlatVu0UnitMatrix(mm[1]);
        mm[1][0][0] = D_00574F20[0];
        mm[1][1][1] = D_00574F20[1];
        mm[1][2][2] = D_00574F20[2];
        for (i = 0; i < (*o->p0)->n; i++) func_00162c5c(o->p154[i], mm[1], o->p154[i]);
    }
    for (i = 0; i < (*o->p0)->n; i++) {
        o->p154[i][3][0] += D_00574F10[0];
        o->p154[i][3][1] += D_00574F10[1];
        o->p154[i][3][2] += D_00574F10[2];
    }
}
#undef D_00573F10
#undef func_001625c8
#undef func_00162848
#undef func_00162c5c

