#include "common.h"

typedef struct { u32 dir:1; u32 b1:1; u32 mod:2; u32 asp:2; u32 tte:1; u32 tie:1; u32 rest:24; } DmaChcr;
typedef struct { u8 pad[0x48]; s8 x48; } O48;
typedef struct { O48 *o; u32 fl; } E10;
typedef struct { u8 pad[0x10]; E10 *e; } A0;
extern DmaChcr *D_0055C640;
extern u8 D_00277E40[];
extern u8 D_00278210[];
extern void *D_00351BE0[];
void func_00266f38(void *, void *);

void func_0015fc00(A0 *a) {
    E10 *e = a->e;
    s32 v;
    u32 fl;
    D_0055C640->dir = 1;
    D_0055C640->mod = 1;
    D_0055C640->asp = 0;
    D_0055C640->tte = 1;
    D_0055C640->tie = 0;
    __asm__ volatile("sync");
    fl = e->fl;
    v = e->o->x48;
    if (fl & 8) {
        if (v & 0x10) {
            func_00266f38(D_0055C640, D_00277E40);
            return;
        }
        func_00266f38(D_0055C640, D_00278210);
        return;
    }
    if (!((fl >> 4) & 2)) v &= ~4;
    if ((u8)((fl >> 4) & 1)) v |= 2; else v &= ~2;
    func_00266f38(D_0055C640, D_00351BE0[v]);
}

f32 func_001629e8(void) {
    u32 r;
    __asm__ volatile(
        "qmtc2 %1, $vf1\n"
        "vrnext.w $vf2w, R\n"
        "vitof0.x $vf1x, $vf1x\n"
        "vsub.w $vf2w, $vf2w, $vf0w\n"
        "vmulw.x $vf1x, $vf1x, $vf2w\n"
        "vftoi0.x $vf1x, $vf1x\n"
        "qmfc2 %0, $vf1\n"
        : "=r"(r)
        : "r"(30001));
    return (f32)r / 30000.0f;
}

typedef f32 Mtx[4][4];
typedef struct { u8 pad[0x2c]; u32 x2c; } Bone;
typedef struct { u8 pad[0x10]; s32 x10; u8 pad14[0xc]; s32 x20; } MHdr;
typedef struct { s32 x0; Bone *bones; MHdr *h; } Mdl;
typedef struct { f32 a[4]; f32 s[4]; f32 r[4]; f32 t[4]; } Xf;
typedef struct {
    Mdl **mdl;
    u8 pad4[8];
    u32 xC;
    u8 pad10[0x78];
    f32 *x88;
    u8 pad8c[0x150 - 0x8c];
    Xf *x150;
    Mtx *x154;
    Mtx *x158;
} Obj;
extern Mtx D_00351E10[];
extern Mtx D_00573F10;
extern f32 D_00574F10[];
void func_001625c8(void *, void *);
void func_00162878(f32 *, void *, f32 *);
void func_00162c5c(void *, void *, void *);
void func_002673b8(f32 *, f32 *);
void func_00267e60(f32 *, f32 *, f32 *, f32);
void func_00267370(f32 *, f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);

void func_00163150(Obj *o, s32 i) {
    Mtx tmp;
    f32 d[4];
    f32 save[4];
    f32 a[4];
    f32 b[4];
    Mdl *m = *o->mdl;
    MHdr *h = m->h;
    if (i == h->x20 - 1 || (h->x20 == -1 && i == h->x10 - 1)) {
        f32 (*ml)[4];
        f32 (*par)[4];
        f32 (*tm)[4];
        f32 (*w)[4];
        f32 *s;
        u32 k; Bone *bn;
        f32 *r1, *r2;
        bn = &m->bones[i];
        save[0] = o->x154[i][3][0];
        tm = D_00351E10[i];
        save[1] = o->x154[i][3][1];
        save[2] = o->x154[i][3][2];
        k = bn->x2c & 0x3ff; //dep:4
        ml = o->x158[i];

        if (k == 0x3ff) {
            par = D_00573F10;
            func_001625c8(par, tmp);
        } else {
            par = D_00351E10[k];
            func_001625c8(o->x154[k], tmp);
        }
        if (o->xC & 4) {
            d[0] = o->x88[0] - (save[0] + D_00574F10[0]);
            d[1] = o->x88[1] - (save[1] + D_00574F10[1]);
            d[2] = o->x88[2] - (save[2] + D_00574F10[2]);
        } else {
            d[0] = o->x88[0];
            d[1] = o->x88[1];
            d[2] = o->x88[2];
        }
        d[3] = 0;
        func_00162878(d, tmp, d);
        r1 = ml[1];
        func_002673b8(d, d);
        func_002673b8(r1, r1);
        func_00267e60(r1, d, r1, o->x88[3]);
        func_002673b8(r1, r1);
        a[0] = ml[0][0];
        a[1] = ml[0][1];
        a[2] = ml[0][2];
        func_002673b8(a, a);
        b[0] = ml[2][0];
        b[1] = ml[2][1];
        b[2] = ml[2][2];
        func_002673b8(b, b);
        r2 = ml[2];
        func_00267370(r2, a, r1);
        func_002673b8(r2, r2);
        func_00267370(ml[0], r1, r2);
        func_002673b8(ml[0], ml[0]);
        func_00267370(r2, ml[0], r1);
        func_002673b8(r2, r2);
        func_00162c5c(tm, par, ml);
        w = (f32 (*)[4])((u32)(i << 6) + (u32)o->x154);
        s = ((Xf *)((u32)(i << 6) + (u32)o->x150))->s;
        func_00267e90(w[0], tm[0], s[0]);
        func_00267e90(w[1], tm[1], s[1]);
        func_00267e90(w[2], tm[2], s[2]);
        func_002675a8(w[3], tm[3]);
        o->x154[i][3][0] = save[0];
        o->x154[i][3][1] = save[1];
        o->x154[i][3][2] = save[2];
        func_00162c5c(ml, tmp, o->x154[i]);
    }
}

typedef struct { s32 w; f32 v; f32 in; f32 out; } Key;
typedef struct { u8 b0; u8 b1; u16 r0:4; u16 pre:2; u16 post:2; u16 r1:8; } CurveHdrX;
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
extern u32 D_002E27C8;
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
            if (D_002E27C8 >> 8 & 1) func_0014c580(o);
            else if (D_002E27C8 >> 7 & 1) func_0014c530(o);
            else return 0;
            if (o->x70 != 21) return 0;
        }
        e->b8 = 0;
        return 1;
    } else {
        if (e->b8) return 0;
        if (!(D_002C5958 >> 5 & 1)) {
            if ((u16)(o->x130->h4C - 1) >= 2) return 0;
            if (!(D_002E27C8 >> 8 & 1) && !(D_002E27C8 >> 7 & 1)) return 0;
        }
        func_0013dfb8(o, e->x120);
        e->b8 = 1;
        return 0;
    }
}

typedef struct { u8 pad[0x10]; f32 pos[4]; f32 v20[4]; f32 v30[4]; u8 pad40[0x30]; s32 w70; u8 pad74[0xBC]; Ch130 *x130; u8 pad134[0x30]; s32 w164; } E8D;
typedef struct {
    s32 w0; void *p4; u8 pad8[0x30]; u64 w38; u8 pad40[0x50]; s32 w90; s32 w94; u8 pad98[0x18];
    f32 vB0[4]; u8 padC0[0x1C]; f32 fDC; u8 padE0[0x1C]; f32 fFC; u8 pad100[0x20]; f32 v120[4]; u8 pad130[0]; 
} W8D;
#define W8D_F12C(w) (*(f32 *)((u8 *)(w) + 0x12C))
extern f32 D_00575020[][4];
extern f32 D_0035B054;
void func_002675a8(f32 *, f32 *);
s32 func_00168b30(E8D *, W8D *, s32, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00162c20(f32 *);
void func_001687d8(void *, void *, s32);
void func_002673b8(f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);

typedef struct { u32 b0:6; u32 b6:1; u32 b7:1; u32 b8:1; u32 r:23; } F27C8;
#define G27C8 (*(F27C8 *)&D_002E27C8)
static inline s32 inl_chk(E8D *e) { if ((u16)(e->x130->h4C - 1) >= 2) return 0; if (G27C8.b8) return 1; return G27C8.b7 != 0; }

void func_00168d20(E8D *e, W8D *w) {
    f32 v[4];
    f32 u[4];
    s32 lock;
    f32 y, k;
    s32 f;
    if ((D_002C5958 & 1) && w->w90 != 0 && w->w94 >= 0 && !((s32)w->w38 & 1)) {
        func_002675a8(v, w->vB0);
        lock = 1;
        w->w38 &= ~0x400;
    } else {
        lock = 0;
        func_002675a8(v, D_00575020[w->w0]);
        w->w38 |= 0x400;
    }
    if (func_00168b30(e, w, lock, v) != 0) return;
    func_00267530(w->v120, v, e->pos);
    y = w->v120[1];
    w->v120[1] = 0.0f;
    func_00162c20(w->v120);
    func_001687d8(e, w, lock);
    k = !lock ? w->fFC : w->fDC;
    if (e->w70 == 17) {
        if (!(D_0035B054 < k)) return;
        func_002675a8(u, e->v30);
        u[1] = 0.0f;
        func_002673b8(u, u);
        if (!(func_00267390(w->v120, u) > 0.97999996f)) return;
        func_0013dfb8((Obj18 *)e, w->pad100 + 0x20);
        if (D_002E27C8 >> 6 & 1) W8D_F12C(w) = 30.0f;
        else W8D_F12C(w) = 20.0f;
        return;
    }
    if (e->w70 != 0) return;
    if (D_002C5958 >> 5 & 1) {
        if (y < -300.0f || (y < 0.0f && e->w164 == 6)) func_00168618((Obj18 *)e, (Ent18 *)w);
        return;
    }
    f = inl_chk(e);
    if (!f) return;
    if (!(D_0035B054 < k)) return;
    func_002675a8(u, e->v30);
    u[1] = 0.0f;
    func_002673b8(u, u);
    if (!(func_00267390(w->v120, u) > 0.97999996f)) return;
    func_00168618((Obj18 *)e, (Ent18 *)w);
    W8D_F12C(w) = 30.0f;
}

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

#include "data/types/nostrict_text_00150000_s6_08.h"
typedef struct { u8 pad[0xB8]; u32 xB8; f32 fBC; u8 padC0[0xCC - 0xC0]; f32 fCC; } PrmB1;
extern C03Act D_0035BCB8;
extern C03Act *D_00575328[];
extern PrmB1 D_0035AE80;
u32 func_001627e8(s32);
s32 func_00171c80(C03Chr *, C03AW *, C03Act *, s32);
void func_00169210(C03Chr *, C03AW *);
s32 func_00169688(C03Chr *, C03AW *);
void func_001693c8(C03Chr *, C03AW *);
void func_002675a8(f32 *, f32 *);

extern s32 D_0035BCA8[];
extern f32 D_0048E94C;
s32 func_00170dd8(u16, s32);
void func_00171b18(C03Chr *, C03AW *);
C03Chr *func_00123158(C03Chr *, C03Chr *);

s32 func_00141200(C03Chr *, s32);
s32 func_0012ee70(C03Chr *, s32);
s32 func_0012f040(C03Chr *, s32);
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
            if (!inl_ok(e, w, a->fl)) continue;
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
            if (!inl_ok(e, w, a->fl)) continue;
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

s32 func_0016b1f0(C03Chr *e, C03AW *w) {
    C03Act *sel;
    C03Act *a;
    s32 i, n;
    C03Act *d;
    PrmB1 *p;
    if (inl_ok(e, w, D_0035BCB8.fl)) {
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
            if (!inl_ok(e, w, a->fl)) continue;
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
                    func_002675a8(w->v120, e->v30);
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
