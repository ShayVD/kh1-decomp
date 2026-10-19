#include "common.h"
typedef struct {
    s32 f0; s32 f4; s32 f8;
    s8 c[4]; s8 d[4];
    s32 f14;
    s8 e[4]; s8 f[4];
    s32 f20; s32 f24; s32 f28; s32 f2c; s32 f30; s32 f34;
    u64 f38; u64 f40;
} Pkt;
typedef struct { f32 f0; f32 f4; u8 pad[8]; s32 f10; s32 f14; s32 f18; } Cam;
extern Cam D_002BC0F0;
extern s32 D_004F82C0;
extern s32 D_004F82C4;
typedef struct { s32 f4; s32 f0; } L14c;
typedef struct { u32 f0; u8 pad[0x114]; f32 f118; u8 p2[0x14c-0x11c]; s32 *f14c; u8 p3[0x15c-0x150]; s32 f15c; u8 p4[0x390-0x160]; s32 f390; } E1;
extern f32 func_00135ca0(f32);
extern void func_001621e0(s32, s32, Pkt *, E1 *);
void func_00127960(E1 *e, s32 a1, s32 a2) {
    Pkt p;
    s32 i;
    s32 *q;
    u64 k;
    if (e->f0 & 0x100) {
        p.c[0] = 0x80;
        p.c[1] = 0x80;
        p.c[2] = 0x80;
        p.c[3] = 0x80;
        p.f0 = 0x101;
        p.d[0] = D_002BC0F0.f10;
        p.d[1] = D_002BC0F0.f14;
        p.d[2] = D_002BC0F0.f18;
        p.d[3] = func_00135ca0(e->f118);
    } else {
        p.f0 = 0x101;
        p.c[3] = a2;
        p.c[0] = 0; p.c[1] = 0; p.c[2] = 0;
        p.d[0] = 0x80; p.d[1] = 0x80;
        p.d[2] = 0x80;
        p.d[3] = 0xff;
    }
    p.f4 = 0;
    q = &D_004F82C0;
    p.f8 = D_004F82C4 + *q;
    *q += 10;
    p.f20 = 0;
    p.f28 = e->f390;
    if (e->f390 & 0x40000000) p.f28 = -1;
    p.f2c = 0;
    if (e->f14c && e->f14c[0] && (e->f0 & 0x4000)) {
        p.f14 = e->f14c[1];
        for (i = 0; i < 4; i++) {
            p.e[i] = p.c[i];
            p.f[i] = p.d[i];
        }
    } else {
        p.f14 = 0;
    }
    k = 0x1000401d0LL;
    p.f38 = 0x3a0001c0;
    p.f40 = k;
    p.f30 = 0;
    p.f34 = 0;
    func_001621e0(e->f15c, a1, &p, e);
}
typedef struct { f32 x, y, z, w; } V4;
typedef struct { V4 a; V4 b; V4 c; s16 f30; s16 pad32; s32 f34; } Ray2;
typedef struct { s32 type; u32 flags; u8 pad8[4]; f32 fc; V4 v10; V4 v20; u8 pad30[0x10]; } Lt2;
extern Lt2 D_002C5C80[31];
typedef union { u64 x; struct { u32 lo:24; u32 b3:8; u32 b4:8; u32 k:2; u32 hi:22; } b; } F370;
typedef struct { u8 pad[0x50]; V4 pos; u8 p60[0x2c4-0x60]; f32 f2c4; u8 p2c8[4]; s32 f2cc; u8 p2d0[0x320-0x2d0]; V4 v320; u8 p330[0x370-0x330]; F370 f370; } E2;
extern s32 func_001232f0(E2 *);
extern void func_002675a8(V4 *, V4 *);
extern void func_00267530(V4 *, V4 *, V4 *);
extern void func_00121fc4(V4 *, V4 *);
extern void func_00118668(Ray2 *);
extern void func_00127c20(E2 *, V4 *, f32);
void func_00128218(E2 *e, f32 k) {
    V4 v;
    Ray2 r;
    Lt2 *l;
    s32 i;
    if (e->f370.b.k == 3) return;
    if (!func_001232f0(e)) {
        func_002675a8(&r.a, &e->pos);
        r.b.w = r.a.w = 1.0f;
        r.b.x = 0;
        r.b.z = 0;
        r.a.y -= e->f2c4;
        r.b.y = e->f2c4 + 300.0f;
        func_00118668(&r);
        if (r.f30 < 0) return;
        func_002675a8(&e->v320, &r.c);
        e->f2cc = r.f34;
    }
    k *= e->f370.b.b3 * 0.0078125f;
    l = D_002C5C80;
    for (i = 0; i < 31; i++, l++) {
        if (!(l->flags & 4)) continue;
        switch (l->type) {
        case 2:
            func_002675a8(&v, &l->v20);
            v.w = 1.0f;
            func_00127c20(e, &v, k);
            break;
        case 3:
        case 5:
            func_002675a8(&v, &e->pos);
            v.y -= e->f2c4;
            func_00267530(&v, &v, &l->v10);
            func_00121fc4(&v, &v);
            if (v.w < l->fc && v.y > 0.5f) {
                v.w = 1.0f;
                func_00127c20(e, &v, k);
            }
            break;
        }
    }
}
typedef struct { u8 pad[0x4c]; u16 f4c; } I3;
typedef struct { u32 f0; u8 p4[0x2c]; f32 f30[3]; f32 f3c; f32 f40[2]; u8 p48[0xc0-0x48]; V4 fc0; u8 pd0[0x130-0xd0]; I3 *f130; u8 p134[0x2d4-0x134]; f32 f2d4; u8 p2d8[0x350-0x2d8]; s32 f350[3]; } E3;
typedef struct { u8 p0[4]; s32 *rot; u8 p8[4]; f32 *scl; } R3;
extern s32 D_0029B410;
extern s8 D_002E2FB8[];
extern V4 D_002C58A0;
extern s32 func_00176578(s32, s32, u32, s64);
extern R3 *func_00147ed8(s32, s32, s32, f32 *);
extern void func_00267370(V4 *, V4 *, V4 *);
extern void func_002673b8(V4 *, V4 *);
extern void func_00121a78(V4 *, f32 *);
R3 *func_0012bd98(E3 *e, s32 kind, u32 c, f32 *out) {
    V4 m;
    V4 a;
    V4 b;
    V4 pad;
    f32 ang[3];
    s32 j;
    s32 idx;
    R3 *r;
    s32 i;
    if (!D_0029B410) return 0;
    if (e->f130->f4c < 20) j = D_002E2FB8[e->f130->f4c];
    else j = 16;
    if (j < 0) return 0;
    idx = func_00176578(D_0029B410, 1 << kind, c, 1 << j);
    r = 0;
    if (idx < 0) goto end;
    switch (kind) {
    case 0:
        ang[0] = 0;
        ang[1] = e->f3c;
        ang[2] = 0;
        break;
    case 10: case 11: case 12:
        ang[0] = 0;
        ang[1] = e->f3c;
        ang[2] = 0;
        if (e->f0 & 0x400000) out[1] = e->f2d4;
        break;
    default:
        func_00267530(&a, &D_002C58A0, &e->fc0);
        func_00267370(&b, (V4 *)e->f30, &a);
        func_002673b8(&b, &b);
        func_00267370(&m, &a, &b);
        func_002673b8(&m, &m);
        func_00121a78(&m, ang);
        break;
    }
    r = func_00147ed8(D_0029B410, idx, 10000, out);
    if (r) {
        r->rot[0] = (u16)(s32)(ang[0] / 6.2831855f * 65536.0f);
        r->rot[1] = (u16)(s32)(ang[1] / 6.2831855f * 65536.0f);
        r->rot[2] = (u16)(s32)(ang[2] / 6.2831855f * 65536.0f);
        for (i = 0; i < 3; i++) r->scl[i] = e->f350[i] * 0.0078125f;
        r->scl[3] = 1.0f;
    }
end:
    return r;
}
typedef struct { u8 pad[0x4c]; u16 f4c; } I4;
typedef struct { u8 pad[0x6c]; u32 *f6c; } O4;
typedef struct { u8 pad[0x130]; I4 *f130; u8 p134[0x164-0x134]; s32 f164; } A4;
typedef struct { s32 state; s32 f4; s32 f8; O4 *fc; u8 p10[0x20]; s32 f30; } W4;
typedef struct { u8 pad[0x10]; A4 *f10; u8 p14[8]; f32 f1c; W4 *f20; } T4;
extern f32 D_002BBDFC;
extern s32 D_00350CE0;
extern void *D_002E26A0[3];
extern s32 func_00122ff8(void *);
extern s32 func_001375d8(A4 *);
extern void func_001315c0(void *, s32, f32 *, f32);
extern void func_0013c9e0(s32, s32);
extern void func_0012c238(A4 *, s32, void *);
extern void func_001586a8(s32);
extern void func_00121eb0(W4 *);
s32 func_0012c328(T4 *t) {
    W4 *w = t->f20;
    s32 done;
    s32 i;
    f32 buf[4];
    if (w->f30 == 0xfff) w->f30 = t->f10->f164;
    t->f1c -= D_002BBDFC;
    if (!func_00122ff8(t->f10) || func_001375d8(t->f10)) goto kill;
    done = 0;
    switch (w->state) {
    case 0:
        if (t->f1c < 0.0f) {
            A4 *a = t->f10;
            if (a->f164 == w->f30) {
                u16 k = a->f130->f4c;
                func_001315c0(a, k == 6 ? 29 : 28, buf, k == 9 ? 3.0f : 1.0f);
                func_00147ed8(D_00350CE0, w->f4, 20000, buf);
            }
            w->state = 1;
            t->f1c = 30.0f;
        }
        break;
    case 1:
        if (w->fc) {
            if (!func_00122ff8(w->fc) || (*w->fc->f6c >> 2 & 1)) {
kill:
                done = 1;
                func_0013c9e0(w->f8, t->f10->f130->f4c);
                break;
            }
        }
        if (t->f1c < 0.0f) {
            A4 *a;
            done = 1;
            a = t->f10;
            if (w->fc) {
                func_0012c238(a, w->f8, w->fc);
                a = t->f10;
            } else {
                for (i = 0; i < 3; i++) {
                    if (D_002E26A0[i]) {
                        func_0012c238(a, w->f8, D_002E26A0[i]);
                        a = t->f10;
                    }
                }
            }
            if (a->f130->f4c == 0) func_001586a8(12);
        }
        break;
    }
    if (done) {
        func_00121eb0(w);
        return 4;
    }
    return 0;
}

typedef struct { s32 f0; s32 f4; s32 f8; s32 fc; volatile s32 n; u8 ids[8]; } Q5;
typedef struct { s32 f0; s32 f4; s32 f8; s32 fc; s32 n; u8 ids[8]; } L5;
typedef struct { u8 pad[0x48f]; u8 f48f; u8 f490; u8 p491[0x7d0-0x491]; s8 f7d0[7]; u8 p7d7[0x874-0x7d7]; u32 f874; u8 p878[0x880-0x878]; u8 f880; } W5;
extern Q5 D_002E3010;
extern L5 D_002E3080;
extern W5 *D_00304BE8;
extern u32 D_00304B78;
extern u32 D_002C5958;
extern u32 D_002E31A8;
extern void func_0013ab08() __attribute__((weak));
extern void func_0012cb40(Q5 *, s32, s32);
extern s32 func_0013a910(s32);
void func_0012d188(s32 a0, u32 *a1) {
    s32 buf[7];
    s32 n, i, m;
    Q5 *q = &D_002E3010;
    L5 *l;
    if (func_0013ab08 && (D_00304B78 >> 3 & 1)) {
        func_0012cb40(q, q->n++, 79);
        return;
    }
    l = &D_002E3080;
    n = 0;
    m = -1;
    for (i = 0; i < 7; i++) {
        s32 v = D_00304BE8->f7d0[i];
        if (v != -1) {
            l->ids[n] = v + 47;
            buf[n] = v;
            if (func_0013a910(v)) m &= ~(1 << n);
            n++;
        }
    }
    l->n = n;
    if (n > 0) {
        n = q->n++;
        func_0012cb40(q, n, 6);
        if ((D_00304BE8->f874 & 4) || (D_002C5958 >> 13 & 1) || (D_002E31A8 >> 1 & 1)) {
            q->f4 |= 1 << n;
            q->f8 |= 1 << n;
        } else if (m == -1) {
            q->f4 |= 1 << n;
        }
    }
    l->f8 = m;
    l->f4 = m;
}

typedef struct { s32 f0, f4, f8, fc; s32 n; u8 ids[0x24]; } Q38;
extern Q38 D_002E2FD8[7];
extern u8 D_00524F68[];
typedef struct { u8 pad[0x21]; u8 n; u8 f22[1]; } T7;
typedef struct { u8 pad[0xc8]; T7 *fc8; } U7;
typedef struct { u8 pad[0x6c]; U7 *f6c; } A7;
extern void func_0012ccb0(s32);
void func_0012d6c0(A7 *a0, u32 *a1) {
    Q38 *g;
    Q38 *p;
    T7 *t;
    s32 m, cnt, i;
    if (D_00304BE8->f874 & 0x10) return;
    g = D_002E2FD8;
    func_0012cb40((Q5 *)g, 2, 3);
    p = &g[2];
    p->f8 = 0;
    m = -1;
    p->f4 = 0;
    i = 0;
    t = a0->f6c->fc8;
    cnt = 0;
    for (; i < t->n; i++) {
        if (t->f22[i]) {
            D_00524F68[cnt] = i;
            m &= ~(1 << cnt);
            p->ids[cnt] = t->f22[i] + 30;
            cnt++;
        }
    }
    p->n = cnt;
    if (cnt > 0) {
        if (!(p->fc < cnt)) p->fc = cnt - 1;
        if (!(D_00304BE8->f874 & 2)) {
            if (!(*a1 >> 6 & 1)) {
                m = -1;
                g->f4 |= 4;
            }
            p->f8 = m;
            p->f4 = m;
            return;
        }
    }
    do { func_0012ccb0(2); } while (0);
}

typedef f32 Mtx[4][4];
extern Mtx D_002C58D0;

typedef struct { u8 p[0x3c]; s32 f3c; u8 p40[0x9c - 0x40]; f32 f9c; f32 fa0; } M6c;
typedef struct { u8 p[0x170]; f32 f170; } M148;
typedef struct { u32 f0; u8 p4[0x68]; M6c *f6c; u8 p70[0x18]; s32 f88; u8 p8c[0x148 - 0x8c]; M148 *f148; u8 p14c[0x3e4 - 0x14c]; f32 f3e4; } E19;
typedef struct { u64 f0; union { s64 d; s32 w; } f8; } A19;
extern s32 func_00157560(E19 *);
extern void func_00157648(E19 *);
extern void func_00138808(E19 *, f32);
extern void func_00141468(E19 *, s32);
s32 func_001349d0(E19 *e, A19 *m) {
    s64 x = m->f8.d;
    s32 v;
    if ((u32)(((s32)(x >> 32) & 0x1f) - 6) < 2 || ((s32)((s64)m->f0 >> 5) & 1)) return e->f6c->f3c;
    if ((e->f0 & 0x1000080) || ((D_002E31A8 >> 1) & 1)) v = 0;
    else v = -m->f8.w;
    switch ((s32)((u64)x >> 38) & 0xf) {
    case 11:
        v = m->f8.w;
        break;
    case 9:
        if (e->f6c->f9c > 0.0f) {
            e->f88 |= 1;
            e->f3e4 = (f32)m->f8.w * 60.0f * e->f6c->f9c;
            if (func_00157560(e) == 2) func_00157648(e);
        }
        m->f0 |= 2;
        v = 0;
        break;
    case 10:
        func_00138808(e, e->f6c->fa0 * 1800.0f);
        break;
    case 12:
        v = 0;
        if (e->f148) {
            e->f88 |= 8;
            e->f148->f170 = (f32)m->f8.w * 60.0f;
        }
        break;
    }
    func_00141468(e, v);
    return e->f6c->f3c;
}

typedef struct { u8 p[0x170]; u64 f170; } P148;
typedef struct { u8 p[0xc8]; u8 *fc8; u8 pcc[0xd8 - 0xcc]; s32 fd8; } P6c;
typedef struct { u8 p[0x6c]; P6c *f6c; u8 p70[0x148 - 0x70]; P148 *f148; } O20;
typedef struct { u8 p[0x2c]; s32 f2c; } P5c;
typedef struct { u8 p[0x34]; O20 *f34; void *f38; u8 p3c[0x54 - 0x3c]; s32 f54; u8 p58[4]; P5c *f5c; u8 p60[0xa0 - 0x60]; s32 fa0; } E20;
typedef struct { u8 p[0x94]; u8 f94; u8 f95; u16 f96; } D20;
typedef struct { void *p; s32 n; } Arg20;
extern D20 *D_00308CDC;
extern s32 func_00123368(O20 *);
extern s32 func_001350d8(E20 *, s32, O20 *);
extern void func_00141608(O20 *, s32);
extern void func_0012bbc8(s32, void *, s32, Arg20 *, s32);
static inline s32 min54(s32 a, s32 b) { return a < b ? a : b; }
static inline s32 max54(s32 a, s32 b) { return a > b ? a : b; }
s32 func_001354b8(E20 *e, O20 *x) {
    s32 r;
    O20 *o;
    u8 *q;
    s32 n;
    if (!func_00123368(x)) return 0;
    r = func_001350d8(e, e->f54, x);
    if (r) {
    o = e->f34;
    if (o && (q = o->f6c->fc8) != 0 && (n = x->f6c->fd8) > 0) {
        f32 f = (f32)(n - *q) * (f32)D_00308CDC->f94 / 100.0f + 1.0f;
        s32 t, m;
        if (o->f148 && ((s32)(o->f148->f170 >> 32) & 1)) f += (f32)D_00308CDC->f95 / 100.0f;
        func_00141608(o, min54(max54(1, (s32)((f32)e->f5c->f2c * f)), e->f5c->f2c * D_00308CDC->f96 / 100));
    }
    if (e->f38) {
        Arg20 a;
        a.p = &x;
        a.n = 4;
        func_0012bbc8(e->fa0, e->f38, 1, &a, 0);
    }
    }
    return r;
}

typedef struct { u8 p[0x4c]; u16 f4c; } I21;
typedef struct { u32 f0; u8 p4[2]; u8 f6; u8 p7[0x118 - 7]; f32 f118; u8 p11c[0x130 - 0x11c]; I21 *f130; u8 p134[0x144 - 0x134]; s32 f144; u8 p148[0x370 - 0x148]; u64 f370; u8 p378[0x38c - 0x378]; s32 f38c; u8 p390[4]; s32 f394; u8 p398[0x430 - 0x398]; V4 f430; } E21;
typedef struct { void *p; s32 n; } Arg21;
extern f32 func_00135ca0(f32);
extern void func_00122588(E21 *);
extern void func_00135df0(E21 *, V4 *);
extern void func_00267548(V4 *, V4 *, V4 *);
extern s32 func_00135bb0(E21 *);
extern s32 func_00136428(E21 *, f32, s32, s32, V4 *);
extern void func_0012bce0(s32, s32, s32, Arg21 *, s32);
extern void func_00128218(E2 *, f32);
void func_00136768(E21 *e) {
    Arg21 a;
    V4 v;
    s32 w;
    f32 s = func_00135ca0(e->f118);
    func_00122588(e);
    func_00135df0(e, &v);
    func_00267548(&v, &v, &e->f430);
    if (v.w <= 0.0f) return;
    if (func_00135bb0(e) && (e->f0 & 1)) {
        s32 f = e->f38c;
        if (e->f130->f4c == 8) {
            if (e->f6 == 3) {
                if (e->f0 & 0x4000) f |= 2;
            }
        }
        w = func_00136428(e, s, f, e->f394, &v);
        if (((s32)(e->f370 >> 48) & 1) && e->f144) {
            a.p = &w;
            a.n = 4;
            func_0012bce0(e->f144, 4, 1, &a, 0);
        }
        e->f370 |= 0x800000000LL;
    }
    if (e->f0 & 2) {
        if (e == D_002E26A0[0] && D_00304BE8->f880) return;
        func_00128218((E2 *)e, v.w * s * (1.0f / 32640.0f));
    }
}

typedef struct E22 { u8 p0[6]; u8 f6; u8 p7[0x10 - 7]; V4 f10; f32 f20[3]; s32 f2c; f32 f30[3]; s32 f3c; u8 p40[0x70 - 0x40]; s32 f70; u8 p74[0xd0 - 0x74]; Mtx fd0; V4 f110; V4 f120; u8 p130[0x370 - 0x130]; u64 f370; u8 p378[0x398 - 0x378]; struct E22 *f398; } E22;
extern void func_001625c8(Mtx, Mtx);
extern void func_00136d38(E22 *);
extern void *func_001230a0(void *);
extern void func_002672f8(V4 *, Mtx, V4 *);
extern void func_00267518(V4 *, V4 *, V4 *);
extern void func_00143d20(E22 *, V4 *, s32);
extern void func_00137688(E22 *, f32);
extern f32 atan2f(f32, f32);
void func_00137ab8(E22 *e) {
    Mtx m;
    V4 v;
    E22 *p = 0;
    func_001625c8(e->fd0, m);
    func_00136d38(e);
    while ((p = func_001230a0(p)) != 0) {
        if (p->f398 != e) continue;
        func_002675a8(&v, &p->f10);
        v.w = 1.0f;
        func_002672f8(&v, m, &v);
        v.w = 1.0f;
        func_002672f8(&v, e->fd0, &v);
        func_00267530(&v, &v, &p->f10);
        if ((s32)(p->f370 >> 34) & 1) {
            func_00143d20(p, &v, 0);
            func_00136d38(p);
        } else {
            func_00267518(&p->f120, &p->f120, &v);
        }
        if ((u32)(p->f6 - 9) < 2) {
            p->f3c = 0;
            func_002672f8(&v, m, (V4 *)p->f30);
            func_002672f8(&v, e->fd0, &v);
            func_00137688(p, atan2f(v.x, v.z));
        } else if (p->f70 == 0 || p->f70 == 40 || p->f70 == 41) {
            p->f2c = 0;
            func_002672f8(&v, m, (V4 *)p->f20);
            func_002672f8((V4 *)p->f20, e->fd0, &v);
        }
    }
}

typedef struct O23 { u8 p0[0x8c]; s32 f8c; u8 p90[0x370 - 0x90]; u64 f370; u8 p378[0x398 - 0x378]; struct O23 *f398; u8 p39c[0x4b0 - 0x39c]; } O23;
extern O23 D_002C64A0[96];
extern s32 D_0052ACF0[];
extern s32 D_0052ACF8;
extern s32 D_003044D0;
extern s32 D_0052AA68;
extern u8 D_0052AA58[];
extern s32 D_00304AD8;
extern s32 D_00304B84;
extern s32 func_0011f130(void *, s32);
extern void func_0013dd40(void);
s32 func_00138258(void) {
    s32 i;
    O23 *p;
    D_0052ACF0[D_0052ACF8] = 0;
    D_003044D0 = 0;
    D_0052AA68 = 0;
    p = D_002C64A0;
    for (i = 0; i < 96; i++, p++) { p->f370 &= ~(1LL << 34); p->f370 &= ~(1LL << 55); }
    func_0011f130(D_0052AA58, 0);
    D_00304AD8 = 0;
    p = D_002C64A0;
    for (i = 0; i < 96; i++, p++) p->f8c = 0;
    p = 0;
    while ((p = func_001230a0(p)) != 0) {
        O23 *q;
        for (q = p->f398; q; q = q->f398) q->f8c++;
        p->f370 |= 1LL << 57;
    }
    func_0013dd40();
    if (!(D_002C5958 & 1)) D_00304B84 = 0;
    D_0052ACF8 ^= 1;
    return 0;
}

typedef struct { u8 p0[2]; u16 f2; f32 f4; u8 p8[4]; f32 fc; f32 f10; } R24;
typedef struct { u8 p0[6]; u8 f6; u8 p7[0x18 - 7]; R24 *f18; } T24;
typedef struct { u8 p0[0x134]; T24 *f134; u8 p138[0x3a8 - 0x138]; u32 f3a8; } E24;
typedef struct { u8 p0[0x10]; f32 f10; f32 f14; f32 f18; u8 p1c[0x34 - 0x1c]; s32 f34; s32 f38; } P24;
extern void func_00267810(Mtx, Mtx, f32);
extern void func_00267768(Mtx, Mtx, f32);
extern f32 func_00176850(void);
void func_00138a78(E24 *e, P24 *a) {
    Mtx m;
    V4 v;
    V4 o;
    T24 *t;
    R24 *r;
    u32 msk;
    s32 k;
    if (!a->f34 || a->f38 < 0) return;
    func_00267810(m, D_002C58D0, atan2f(a->f10, a->f18));
    func_00267768(m, m, func_00176850() * 3.1415928f - 1.5707964f);
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 1.0f;
    v.w = 1.0f;
    func_002672f8(&v, m, &v);
    k = (s32)(func_00176850() * (f32)e->f134->f6);
    while (e->f3a8 & (1 << k)) k = (k + 1) % e->f134->f6;
    r = &e->f134->f18[k];
    func_001315c0(e, r->f2, (f32 *)&o, r->f4);
    v.x *= r->fc;
    v.y *= r->f10;
    v.z *= r->fc;
    func_00267518(&o, &o, &v);
    func_00147ed8(a->f34, a->f38, -10000, (f32 *)&o);
}

/* needs make: uses rodata */
typedef struct { s32 f0; s32 o[5]; } Hdr16;
typedef struct { u8 p[8]; f32 f8; f32 fc; } Sub16;
typedef struct {
    u8 p0[6]; u8 f6; u8 p7[0x68 - 7];
    void *f68;
    u8 p6c[0x134 - 0x6c];
    Sub16 *f134;
    u8 p138[0x154 - 0x138];
    void *f154; s32 f158; s32 f15c;
    u8 p160[0x1d0 - 0x160];
    void *f1d0; s32 f1d4; s32 f1d8;
    u8 p1dc[0x370 - 0x1dc];
    u64 f370;
} E16;
extern void func_001238c0(E16 *, f32, f32);
extern void func_00162070(void *, s32 *, s32 *, s32 *);
extern void func_001623d0(void *, s32 *);
extern s32 func_0013b9c8(E16 *);
extern s32 func_001559a8(Hdr16 *);
extern void func_00132260(E16 *, Hdr16 *, s32);
s32 func_001323a0(E16 *e, Hdr16 *h) {
    Sub16 *s;
    switch (e->f6) {
    case 5:
    case 10:
        e->f154 = (u8 *)h + h->o[0];
        e->f1d0 = 0;
        if (h->o[2] - h->o[1] > 0) {
            s = (Sub16 *)((u8 *)h + h->o[1]);
            e->f134 = s;
            func_001238c0(e, s->fc, s->f8);
        }
        if (h->o[3] - h->o[2] > 0) e->f68 = (u8 *)h + h->o[2];
        e->f370 |= 0x8000LL << 24;
        break;
    case 4:
    case 8:
    case 9:
        if (h->o[1] - h->o[0] > 0) {
            e->f154 = (u8 *)h + h->o[0];
            func_00162070(e->f154, &e->f158, &e->f1d4, &e->f15c);
        } else {
            e->f154 = 0;
        }
        if (h->o[2] - h->o[1] > 0) {
            e->f1d0 = (u8 *)h + h->o[1];
            func_001623d0(e->f1d0, &e->f1d4);
        } else {
            e->f1d0 = 0;
        }
        e->f1d8 = 0;
        if (h->o[3] - h->o[2] > 0) {
            s = (Sub16 *)((u8 *)h + h->o[2]);
            e->f134 = s;
            func_001238c0(e, s->fc, s->f8);
        }
        if (h->o[4] - h->o[3] > 0) e->f68 = (u8 *)h + h->o[3];
        break;
    case 7:
        return func_0013b9c8(e);
    default:
        func_00132260(e, h, func_001559a8(h));
        break;
    }
}

typedef struct { s32 f0; u32 f4; u8 p8[0x4c]; s8 f54; u8 p55[0x78 - 0x55]; } Ent17;
typedef struct { u8 p[0xc]; s32 n; Ent17 *base; } Lst17;
extern Lst17 D_00525298;
extern Ent17 *D_00525354;
s32 D_00525358 ALIGNED(8);
#define INC17 { s32 *p17 = &D_00525358; (*p17)++; }
void (*D_00525290)(void) ALIGNED(16);
extern s32 D_002BC134;
extern void func_00157400(void (*)(s32));
extern void func_0014a058(void (*)(s32));
extern void func_00133578(void (*)(s32));
extern s32 func_001560f8(s32, void (*)(s32));
void func_00132a78(s32 a0) {
    switch (D_00525358) {
    case 0:
        INC17;
        func_00157400(func_00132a78);
        break;
    case 1:
        while (D_00525354 < D_00525298.base + D_00525298.n) {
            if (!(D_00525354->f4 & 1) && (D_002BC134 != 25 || D_00525354->f54 != 1)) {
                if (func_001560f8(D_00525354->f0, func_00132a78)) {
                    D_00525354++;
                    return;
                }
            }
            D_00525354++;
        }
        INC17;
    case 2:
        INC17;
        func_00133578(func_00132a78);
        break;
    case 3:
        INC17;
        func_0014a058(func_00132a78);
        break;
    case 4:
        if (D_00525290) D_00525290();
        break;
    }
}
extern void func_00132a78(s32);
typedef struct { s32 f0; u32 f4; u8 p8[0x40]; s16 f48; u8 p4a[2]; u16 f4c; u8 p4e[6]; s8 f54; s8 f55; s8 f56; u8 p57[0x78 - 0x57]; } Ent18;
typedef struct { u8 p[0xc]; s32 n; Ent18 *base; u8 p14[8]; s32 f1c; } Lst18;
typedef struct { s32 f0, f4, f8; } G18;
extern G18 D_002E2F28;
extern s32 D_002BC128;
extern s32 D_002BC130;
s32 D_00525294 ALIGNED(4);
extern void func_00132790(s32, s32, Lst18 *);
extern void func_001134d8(s32);
extern void *memset(void *, s32, u32);
extern s32 func_0013c6a8(s32);
extern s32 func_0013c2f0(s32);
extern void func_00146928(s32);
void func_00132c70(s32 a0, void (*cb)(void)) {
    Lst18 *l = (Lst18 *)&D_00525298;
    Ent18 *p;
    s32 i = 0, k = -1;
    s32 *pt = &D_002BC134;

    D_00525294 = 0;
    func_00132790(a0, *pt, l);
    func_001134d8(l->f1c);
    memset(&D_002E2F28, 0, 140);
    D_002E2F28.f0 = D_002BC128;
    D_002E2F28.f4 = D_002BC130 + 1;
    D_002E2F28.f8 = *pt;
    p = l->base;
    for (i = 0; i < D_00525298.n; i++, p++) {
        switch (p->f54) {
        case 1:
            if (k < 0) k = p->f55;
            if (p->f4c == D_00304BE8->f48f || p->f4c == D_00304BE8->f490) {
                p->f55 = k;
                k += p->f56;
            } else {
                p->f4 |= 1;
            }
            break;
        case 8:
            if (func_0013c6a8(p->f48)) p->f4 |= 2;
            break;
        case 12:
            if (func_0013c2f0(p->f48)) p->f4 |= 2;
            break;
        }
    }
    D_00525290 = cb;
    func_00146928(-6);
    D_00525358 = 0;
    D_00525354 = (Ent17 *)D_00525298.base;
    func_00132a78(0);
}
