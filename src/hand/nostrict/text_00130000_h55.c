/* Hand-matched functions near 0x13b000-0x143000 (worker 55), built without strict aliasing. */
#include "common.h"
#include "data/bss_0052.h"

typedef struct { u8 pad[8]; f32 x8; f32 xc; } W55Dim;
typedef struct { u8 pad[0x10]; W55Dim *x10; } W55Mdl;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x4c - 0x8]; u16 x4c; u8 pad4e[0x54 - 0x4e]; s8 x54; } W55Inf;
typedef struct { u8 pad[0xcc]; f32 xcc; } W55Mv;
typedef struct { f32 *x0; } W55Fx;
typedef struct W55Ob {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob;
typedef struct { s32 x0, x4, x8, xc, x10, x14, x18; } W55Hdr;
typedef struct { s32 x0, x4, x8, xc, x10; } W55Hd5;
typedef struct { u32 type:8; u32 id:16; u32 b24:1; u32 f25:1; u32 hi:6; void *x4; s32 x8; } W55Ev;
typedef struct { u8 x0, x1; s8 x2; } W55EvInf;
typedef struct { f32 pos[4]; u8 pad10[0x10]; f32 x20; f32 x24; s32 x28; } W55Col;
typedef struct { f32 pos[4]; f32 dir[4]; f32 hit[4]; s16 id; s16 pad32; s32 x34; } W55Ray;
#include "data/types/nostrict_text_00130000_h55.h"
typedef struct {
    s32 x0;
    f32 x4, x8;
    u8 pad0c[4];
    f32 x10, x14, x18, x1c, x20, x24, x28, x2c, x30, x34, x38;
    s32 x3c, x40, x44, x48, x4c, x50, x54;
    f32 x58;
    s32 x5c;
    f32 x60, x64;
    s32 x68, x6c, x70, x74;
    f32 x78[16];
    s32 xb8;
    u8 xbc, xbd;
    s16 xbe, xc0, xc2;
    f32 xc4;
    s32 xc8;
    f32 xcc;
    u8 xd0, xd1;
    s16 xd2;
    f32 xd4;
    s32 xd8;
    f32 xdc;
    s32 xe0;
} W55Cam;

extern f32 D_002BBDFC;
extern u32 D_002C5958;
extern u32 D_002C5978;
extern f32 D_002C58B0[4];
extern W55Ob *D_002E26A0[];
extern W55Ev D_002E3190;
extern s32 D_002E3194;
extern f32 D_00304C40;
extern u32 D_0037A378;
extern u8 D_0052AD68[];
extern W55Ob *D_0052AE38; /* src/data/bss_0052.c: s32 D_0052AE38 */
W55Ob *D_0052AE3C ALIGNED(4);
f32 D_0052AE40[4] ALIGNED(16);
extern s32 D_0052AE54;
extern W55Hdr *D_0052AE58; /* src/data/bss_0052.c: void *D_0052AE58 */
extern W55Hd5 *D_0052AE5C; /* src/data/bss_0052.c: void *D_0052AE5C */
extern s32 D_0052AE60;
f32 D_0052AE68 ALIGNED(8);
extern W55Cache D_0052CB20[4];
extern W55Cache *D_0052EB40;
extern s32 D_0052EB44;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
extern s32 D_0029B410;

void D_00F20000(s32 a, void *b);
void func_00105a30(s32 a, s32 id, f32 *v);
void func_00105ad0(s32 a, s32 id, f32 *v);
s32 func_00105b68(s32 a, s32 b);
u32 func_00105bc0(s32 a, s32 id);
s32 func_00117bb0(s32 id, f32 *a, f32 *b, f32 *c);
void func_00118628(W55Ray *r, s32 m);
void func_0011f090(void *a, s32 b, void *c);
f32 func_00120c18(f32 *v);
f32 func_00121550(f32 *o, f32 *a, f32 *d, f32 *p, f32 *v);
void func_00121fc4(f32 *d, f32 *s);
W55Ob *func_001230a0(W55Ob *p);
void func_00123438(W55Ob *p, u32 f);
void func_00123460(W55Ob *p);
void func_00123a88(s32 a, f32 *b);
void func_001247e8(W55Ob *p);
void func_00124d08(void);
void func_0012c560(W55Ob *o, void *a, s32 id);
void func_0012ec60(void *a, s32 b, f32 *v);
void func_00130340(void *o, s32 a, f32 f);
void func_00130398(void *o, s32 a, f32 f);
void *func_00130578(void *, s32, f32);
void func_00131498(W55Ob *o, void *a);
void func_00131500(W55Ob *o);
f32 func_00131a68(W55Ob *o, s32 a);
s32 func_00133000(W55Ob *o, s32 id);
void func_001333e0(W55Ob *o, s32 id, void *p);
void func_00133708(void);
void func_001337e0(s32 a, void *b, s32 c);
void func_00137330(void *a, W55Ob *o, s32 t);
void func_001373f8(W55Ob *o, f32 f);
void func_00137448(W55Ob *o);
s32 func_001375f0(W55Ob *o);
void func_0013aaa0(void);
s32 func_0013b4e8();
void func_0013e638(W55Ob *o, W55Ev *e, void *q);
void func_0013e978(W55Ob *o, W55Ev *e, void *q);
void func_0013ecf8(W55Ob *o, void *a, void *q);
f32 func_0013fd88(f32 y);
void func_00145080(s32 a, s32 b);
W55Fx *func_00147c98(s32 a, s32 b, s32 c);
void func_00147d50(W55Fx *f, f32 *v);
W55EvInf *func_001478c8(s32 t);
s32 func_0014f5c8(W55Ob *o);
s32 func_0014f600(W55Ob *o);
s32 func_0014f658(void *, s32);
void func_00150930(W55Ob *o, s32 a, void *q);
void func_00157a30(W55Ob *o, s32 k, void *a);
void func_00158b88(W55Ob *o, W55Ev *e, s32 t);
s32 func_0015bcb8(W55Ob *o, f32 *r);
void func_00176310(s32 a);
void func_00176388(s32 a);
void func_001763a0(s32 a);
s32 func_00176578(s32 a, s32 b, s32 c, s64 d);
void func_001c4d90(void *a, void *b, void *c);
s32 func_001ecfd8(void);
void func_002414a8(s32 a, s32 b);
f32 func_00267390(f32 *a, f32 *b);
void func_002673b8(f32 *d, f32 *s);
void func_002674f0(f32 *d, f32 *a, f32 *b, f32 t);
void func_00267518(f32 *d, f32 *a, f32 *b);
void func_00267530(f32 *d, f32 *a, f32 *b);
void func_00267560(f32 *d, f32 *s, f32 k);
void func_002675a8(f32 *d, f32 *s);
f32 fmodf(f32 x, f32 y);
f32 atan2f(f32 y, f32 x);
f32 sinf(f32 x);
f32 fabsf(f32);

#define W55MIN(a, b) ((a) < (b) ? (a) : (b))
#define W55MAX2(a, b) ((a) > (b) ? (a) : (b))

s32 func_0013b238(void) {
    W55Ob *p = 0;
    W55Ob **pl;
    W55Hdr **ph;
    u32 *fl;
    u32 f;
    while ((p = func_001230a0(p))) {
        f = p->x0;
        if (p == D_0052AE38) {
            f |= 0x30;
            f &= ~2;
            func_001373f8(p, 0.0f);
            p->x370.x |= 1UL << 52;
        } else {
            f &= ~0x8000;
            func_00137448(p);
            func_002675a8(p->x120, D_002C58B0);
        }
        func_00123438(p, f);
    }
    pl = &D_0052AE38;
    func_002675a8(D_0052AE40, (*pl)->pos);
    D_0052AE40[3] = (*pl)->x3c;
    func_00123a88((*pl)->x4, D_002C58B0);
    func_00176310(D_0052AE60);
    func_001763a0(0);
    func_00176388(1);
    fl = &D_002C5958;
    *fl = (*fl & ~0x100000) | 0x4000;
    if ((s32)((D_002C5978 >> 8) & 3) < 2) {
        ph = &D_0052AE58;
        if ((*ph)->x14 != (*ph)->x10) {
            func_00131498(*pl, (u8 *)*ph + (*ph)->xc);
            func_001c4d90((u8 *)*ph + (*ph)->x10, (u8 *)*ph + (*ph)->x14, (u8 *)*ph + (*ph)->x18);
        }
    }
    return 4;
}

void func_0013b5d8(void) {
    W55Ob *p;
    W55Ob **pl;
    u32 *fl;
    func_00133708();
    func_00124d08();
    func_002414a8(0, 1);
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if ((s32)(p->x370.x >> 33) & 1) continue;
        if (p == D_002E26A0[1]) continue;
        if (p == D_002E26A0[2]) continue;
        func_00123460(p);
    }
    pl = &D_0052AE38;
    func_0014f658(*pl, 0);
    func_00123a88((*pl)->x4, D_0052AE40);
    func_00131500(*pl);
    func_00130340(*pl, 0x40000000, 0.0f);
    (*pl)->x370.x &= ~(1UL << 52);
    (*pl)->x0 &= ~0x200000;
    (*pl)->x444 = 0;
    func_00176388(0);
    fl = &D_002C5958;
    *fl &= ~0x4000;
    func_00145080(0, 4);
    func_0011f090(D_0052AD68, 0, func_0013b4e8);
}

s32 func_0013b740(void) {
    W55Ob *p;
    W55Ob **q;
    W55Ob **pl;
    W55Hd5 **ph;
    if ((D_0037A378 >> 2) & 1) goto fail;
    if (D_0052AE54 != 4 || func_001ecfd8()) {
    fail:
        return 0;
    }
    func_0013b5d8();
    D_0052AE3C = 0;
    for (p = 0; (p = func_001230a0(p));) {
        if (((u8 *)p)[6] == 7) {
            D_0052AE3C = p;
            break;
        }
    }
    q = &D_0052AE3C;
    if (*q) {
        if (D_0052AE5C->x8 - D_0052AE5C->x4 > 0) {
            func_00131498(*q, (u8 *)D_0052AE5C + D_0052AE5C->x4);
            func_00130340(*q, 0, 0.0f);
            (*q)->x0 &= ~0x30;
        }
        (*q)->x444 = 0;
    }
    if (((D_002C5978 >> 8) & 3) != 1) {
        ph = &D_0052AE5C;
        if ((*ph)->xc - (*ph)->x8 > 0) {
            W55Ob **pm = &D_0052AE38;
            func_00131498(*pm, (u8 *)*ph + (*ph)->x8);
            func_00130340(*pm, 0, 0.0f);
        }
        D_00F20000(0, (*ph)->x10 - (*ph)->xc > 0 ? (u8 *)*ph + (*ph)->xc : 0);
        return 1;
    }
    func_001247e8(D_0052AE3C);
    pl = &D_0052AE38;
    func_00131500(*pl);
    func_00130340(*pl, 0x40000000, 0.0f);
    return 1;
}

void func_0013dd40(void) {
    f32 v[4];
    W55Ob *pl, *p;
    s32 i, near;
    f32 lim;
    u32 *fl = &D_002C5958;
    if (*fl & 0x12010) { *fl |= 1; return; }
    if ((*fl >> 12) & 1) { *fl &= ~1; return; }
    lim = 1440000.0f;
    near = 0;
    for (i = 0; i < 3; i++) {
        pl = D_002E26A0[i];
        if (!pl) continue;
        for (p = 0; (p = func_001230a0(p));) {
            if (p->x370.b.kind != 2) continue;
            func_00267530(v, pl->pos, p->pos);
            v[1] = 0.0f;
            if (func_00267390(v, v) < lim) { near = 1; break; }
        }
    }
    if (D_00304C40 > 0.0f) D_00304C40 -= D_002BBDFC;
    if ((D_002C5958 & 1) != near) {
        if (D_00304C40 > 0.0f) {
            D_00304C40 = 0.0f;
            D_002C5958 = (D_002C5958 & ~1) | near;
        } else if ((D_0052AE68 -= D_002BBDFC) <= 0.0f) {
            D_002C5958 = (D_002C5958 & ~1) | near;
        }
        if ((D_002C5958 & 1) != near) return;
    }
    if (D_002C5958 & 1) D_0052AE68 = 120.0f;
    else D_0052AE68 = 45.0f;
}

void func_0013e000(W55Ob *o) {
    f32 v[4], w[4], pos[4], out[4];
    u32 id = o->x316;
    W55Fx *fx;
    u32 k;
    s32 h;
    s32 *gp;
    if (id == 0xffff) return;
    if (o->x0 & 0x1000080) return;
    func_00105a30(-1, id, v);
    v[1] = 0.0f;
    func_002673b8(v, v);
    func_002675a8(pos, o->pos);
    pos[1] -= o->x134->x10->x8 * o->x44;
    pos[3] = 1.0f;
    func_00267560(w, v, o->x134->x10->xc * o->x40 * -2.0f);
    w[3] = 1.0f;
    if (!func_00117bb0(id, pos, w, out)) return;
    fx = o->x488;
    if (!fx) {
        if (!D_0029B410) goto skip;
        k = func_00105bc0(-1, id);
        switch (k) {
        case 1: k = 2; break;
        case 2: k = 4; break;
        case 3: k = 8; break;
        default: k = 0; break;
        }
        gp = &D_0029B410;
        h = func_00176578(*gp, k, 0, (1 << o->x130->x4c) | 0x400);
        if (h >= 0) {
            fx = func_00147c98(*gp, h, 20000);
            o->x48c = id;
            o->x488 = fx;
        }
    } else if (o->x48c != id) fx = 0;
skip:
    if (fx) {
        func_002675a8(fx->x0, out);
        func_00147d50(fx, v);
    }
}

s32 func_0013ff00(W55Ob *o, f32 *seg, f32 *v, f32 *r) {
    f32 d[4], w[4], tmp[4];
    f32 t;
    if (fabsf(seg[1] - seg[5]) > 5.0f) seg += 4;
    func_00267530(d, seg + 4, seg);
    func_00121fc4(d, d);
    t = func_00121550(tmp, seg, d, o->pos, v);
    if (t < 0.0f) {
        if (t < -20.0f) return 0;
        t = 0.0f;
    } else if (d[3] < t) {
        if (d[3] + 20.0f < t) return 0;
        t = d[3];
    }
    func_00267560(w, v, o->x2c0 - 1.0f);
    r[0] = seg[0] + d[0] * t + w[0];
    r[1] = o->pos[1];
    r[2] = seg[2] + d[2] * t + w[2];
    r[3] = 1.0f;
    return 1;
}

s32 func_00140070(W55Ob *o, f32 *dir, f32 *r) {
    f32 pts[4][4];
    f32 v[4], d[4];
    f32 h;
    if (o->x2de == 0xffff) return 0;
    func_00105a30(-1, o->x2de, v);
    func_002675a8(d, dir);
    d[1] = 0.0f;
    func_002673b8(d, d);
    if (func_00267390(v, d) > -0.7f) return 0;
    func_00105ad0(-1, o->x2de, pts[0]);
    h = o->pos[1] - o->x2c4;
    if (h < W55MIN(pts[0][1], W55MIN(pts[1][1], pts[2][1]))) return 0;
    if (!func_0013ff00(o, pts[0], v, r)) return 0;
    if (func_0015bcb8(o, r)) return 0;
    func_002675a8(o->x148, v);
    return 1;
}

s32 func_00140370(W55Ob *o, f32 *d) {
    f32 r[4];
    f32 m;
    s32 k;
    k = func_00140070(o, d, r);
    if (k == 1) {
        if (o->x30c != 0xffff) return 0;
        m = fmodf(o->pos[1], 66.66666412353516f);
        if (m < 0.0f) m += 66.66666412353516f;
        if (m < 10.0f) r[1] -= m;
        else if (m > 56.66666412353516f) r[1] += 66.66666412353516f - m;
        else return 0;
        if (func_0015bcb8(o, r)) return 0;
        func_0014f658(o, 10);
        func_00130398(o, 0x1000014, 0.0f);
        func_00130578(o, 0x40000011, 0.0f);
        func_002675a8(o->pos, r);
        func_00267560(d, o->x148, -1.0f);
        d[3] = 0.0f;
        o->x20[3] = 0.0f;
        o->x150 = atan2f(-o->x148[0], -o->x148[2]);
    }
    return k;
}

s32 func_001404d8(W55Ob *o, f32 *d) {
    f32 pts[4][4];
    f32 v[4], r[4];
    f32 t;
    if (o->x30c == 0xffff || !func_001375f0(o)) goto fail;
    func_00105a30(-1, o->x30c, v);
    if (func_00267390(v, d) < -0.7f) return 0;
    func_00105ad0(-1, o->x30c, pts[0]);
    if (!func_0013ff00(o, pts[0], v, r)) return 0;
    r[1] = W55MAX2(W55MAX2(pts[0][1], pts[1][1]), pts[2][1]) + o->x2c4;
    t = func_0013fd88(r[1]);
    if (t > 0.015f && t < 0.985f) r[1] += (1.0f - t) * 66.66666412353516f;
    if (func_0015bcb8(o, r)) {
    fail:
        return 0;
    }
    func_002675a8(o->x148 + 4, o->pos);
    func_002675a8(o->x148 + 8, r);
    o->x148[12] = 0.0f;
    func_002675a8(o->x148, v);
    func_0014f658(o, 9);
    func_00130398(o, 0x1010012, 0.0f);
    func_002675a8(d, o->x148);
    d[3] = 0.0f;
    return 1;
}

void func_001406d0(W55Ob *o, f32 *d) {
    f32 t;
    o->x148[12] += D_002BBDFC;
    t = o->x148[12] / func_00131a68(o, 18);
    if (t >= 1.0f) {
        func_0014f658(o, 10);
        func_00130398(o, 20, 0.0f);
        func_00130578(o, 0x40000011, 0.0f);
        func_002675a8(o->pos, o->x148 + 8);
        o->x20[1] = 0.0f;
        o->x20[3] = 0.0f;
        return;
    }
    func_002674f0(d, o->x148 + 8, o->x148 + 4, t);
    d[1] -= sinf(t * 3.1415928f) * 50.0f;
    func_00267530(d, d, o->pos);
    func_00121fc4(o->x20, d);
    o->x20[3] /= D_002BBDFC;
    o->x150 = atan2f(-o->x148[0], -o->x148[2]);
}

void func_001418b8(W55Cam *c) {
    s32 i;
    c->x4 = 2.0f;
    c->x0 = 0;
    c->x8 = 8.0f;
    c->x10 = 190.0f;
    c->x14 = 0.1f;
    c->x18 = 0.95f;
    c->x1c = 1.04719746112823486328125f;
    c->x20 = 1.22173035144805908203125f;
    c->x24 = 0.034906583f;
    c->x2c = 3.1415928f;
    c->x30 = 3.1415928f;
    c->x28 = 0.523598730564117431640625f;
    c->x34 = 3.1415928f;
    c->x38 = 3.1415928f;
    c->x40 = 18;
    c->x48 = 3;
    c->x4c = 0;
    c->x50 = 0;
    c->xe0 = 0;
    c->x54 = 0;
    c->x5c = 0;
    c->x3c = 18;
    c->x60 = 1.0f;
    c->x64 = 1.0f;
    c->x68 = 0;
    c->x44 = 3;
    c->x70 = 0;
    c->x58 = 0.5f;
    c->x74 = 0;
    c->x6c = 0x1000;
    for (i = 15; i >= 0; i--) c->x78[i] = 1.0f;
    c->xb8 = 0;
    c->xbc = 0;
    c->xbe = 0;
    c->xbd = 3;
    c->xc0 = 0;
    c->xc2 = 0;
    c->xc4 = 1.0f;
    c->xc8 = 0;
    c->xcc = 0.19634955f;
    c->xd1 = 3;
    c->xd0 = 3;
    c->xd2 = 0;
    c->xd4 = 1.0f;
    c->xd8 = 0;
    c->xdc = 1.0f;
}

void func_00142058(s32 lim) {
    W55Cache *best = D_0052CB20;
    W55Cache *e;
    s32 key, i;
    D_0052EB40 = 0;
    key = (D_002BC128 << 16) | (D_002BC130 << 8) | D_002BC134;
    e = D_0052CB20;
    for (i = 0; i < 4; i++, e++) {
        if (e->key == key && e->age >= D_0052EB44 - lim) {
            if (!D_0052EB40 || D_0052EB40->age < e->age) D_0052EB40 = e;
        }
        if (e->key < 0 || (best->key >= 0 && e->age < best->age)) best = e;
    }
    if (!D_0052EB40) {
        D_0052EB40 = best;
        best->key = key;
        for (i = 0; i < 256; i++) D_0052EB40->e[i].a = -1;
    } else {
        for (i = 0; i < 4; i++) {
            if (D_0052CB20[i].age < D_0052EB40->age) D_0052CB20[i].age++;
        }
    }
    D_0052EB40->age = D_0052EB44++;
}

s32 func_00142480(f32 *from, f32 *vec, s32 mask, f32 *out) {
    W55Ray r;
    s32 n, i;
    func_002675a8(r.pos, from);
    n = func_00120c18(vec) / 100.0f;
    if (n >= 2) {
        func_00267560(r.dir, vec, 1.0f / n);
    } else {
        func_002675a8(r.dir, vec);
        n = 1;
    }
    r.dir[3] = 1.0f;
    for (i = 0; i < n; i++) {
        r.pos[3] = 1.0f;
        func_00118628(&r, mask);
        if (r.id >= 0) {
            func_002675a8(out, r.hit);
            return func_00105b68(r.x34, r.id);
        }
        func_00267518(r.pos, r.pos, r.dir);
    }
    return -1;
}

f32 func_001427d0(W55Ob *o, W55Col *c) {
    if ((u32)(o->x70 - 18) < 2) {
        c->x24 = o->x134->x10->x8;
        c->x20 = 25.0f;
    } else if (o->x0 & 0x4000000) {
        c->x24 = o->x134->x10->x8;
        c->x20 = o->x134->x10->xc;
    } else {
        c->x24 = o->x134->x10->x8 * o->x44;
        c->x20 = o->x134->x10->xc * o->x40;
    }
    func_002675a8(c->pos, o->pos);
    c->pos[3] = 1.0f;
    c->x28 = 0;
    if (o->x398 || func_0014f5c8(o) || func_0014f600(o)) c->x28 |= 1;
    if (o->x370.b.b39 || (o->x130->x4 & 0x200)) c->x28 |= 2;
    if (o->x370.b.kind == 2 || (o->x0 & 0x100)) {
        if (func_0014f5c8(o)) c->x28 |= 0x10;
        else c->x28 |= 4;
    } else {
        switch (((u8 *)o)[6]) {
        case 9: case 10:
            if (o->x130->x54 == 9) c->x28 |= 8;
            else c->x28 |= 0x40;
            break;
        case 8:
            c->x28 |= 0x20;
            break;
        }
    }
    return (c->x20 < c->x24 ? c->x20 : c->x24) * 0.7f;
}

/* needs make: uses rodata */
void func_0013eab0(W55Ob *o, W55Ev *e, f32 *q) {
    f32 v[4];
    switch (e->type) {
    case 2:
        if (func_00133000(o, e->id)) {
            if (e->x4) {
                func_0012ec60(e->x4, e->x8, v);
                func_00267530(q, v, o->pos);
                o->x6c->xcc = 0.19634955f;
            }
            if (!e->id) {
                func_00130340(o, 0x1000083, 0.0f);
                func_00130578(o, 138, 0.0f);
            } else {
                func_00130340(o, (e->id + 131) | 0x1000000, 0.0f);
            }
            func_00130578(o, 0x40000075, 8.0f);
            func_001333e0(o, e->id, &e->x4);
        }
        break;
    case 3:
        if (!e->x4 || e->x4 == o) {
            func_00130340(o, 0x100008b, 8.0f);
        } else {
            func_0012ec60(e->x4, e->x8, v);
            func_00267530(q, v, o->pos);
            func_00130340(o, 0x100008c, 8.0f);
        }
        func_00130578(o, 0x40000075, 8.0f);
        func_0012c560(o, e->x4, e->id);
        func_00267560(o->x3c0, o->x3c0, 0.7f);
        break;
    case 4:
        func_001337e0(0, e->x4, 0);
        break;
    case 5:
        func_001337e0(4, e->x4, 0);
        break;
    case 0: case 6: case 28: case 29: case 30:
        break;
    default:
        return;
    }
    func_00121fc4(q, q);
    q[3] = 0.0f;
}

void func_0013ee40(W55Ob *o, W55Ev *e, void *q) {
    W55EvInf *inf = func_001478c8(e->type);
    if (e->f25) {
        if (inf->x2 >= 0) func_00157a30(o, inf->x2, e->x4);
        else if (e->type == 2) func_00157a30(o, e->id + 7, e->x4);
    }
    switch (e->type) {
    case 29: case 30: case 70: case 81: case 84:
        func_00137330(o->x98, o, e->type);
        return;
    case 68:
        if (o->x70 == 0 || o->x70 == 26) func_00150930(o, D_002E3194, q);
        return;
    case 71:
        if (func_001375f0(o) && D_002E3190.f25) {
            func_0013ecf8(o, &D_002E3190.x4, q);
            D_00F20000(3, 0);
        }
        func_00137330(o->x98, o, D_002E3190.type);
        return;
    case 75: case 77: case 78: case 82: case 87: case 88: case 89: case 90: case 91:
    case 94: case 95: case 96:
        func_00158b88(o, &D_002E3190, e->type);
        return;
    case 79:
        func_0013aaa0();
        return;
    case 92: case 93:
        return;
    case 100:
        func_00137330(e->x4, o, e->type);
        return;
    }
    switch (o->x70) {
    case 0: case 6: case 24:
        func_0013e638(o, e, q);
        return;
    case 2:
        func_0013e978(o, e, q);
        return;
    case 8:
        func_0013eab0(o, e, q);
        break;
    }
}

/* uses rodata. func_001401d8 only matches with func_0013fe28 defined above it. */
f32 func_0013fe10();

s32 func_0013fe28(W55Ob *o) {
    f32 t = func_0013fe10(o);
    s32 r = 0;
    if (t < 0.015f || t > 0.985f) r = 1;
    return r;
}

s32 func_001401d8(W55Ob *o, f32 *d) {
    f32 r[4];
    f32 m;
    s32 k;
    if (!func_001375f0(o) || d[3] == 0.0f) return 0;
    k = func_00140070(o, d, r);
    if (k == 1) {
        if (!func_0013fe28(o)) {
            m = fmodf(o->pos[1] + 10.0f, 66.66666412353516f);
            if (m < 0.0f) m += 66.66666412353516f;
            r[1] = r[1] + 10.0f - m;
        }
        if (func_0015bcb8(o, r)) return 0;
        func_002675a8(o->pos, r);
        func_002675a8(o->x148 + 8, r);
        func_0014f658(o, 10);
        func_00130398(o, 0x1000013, 4.0f);
        func_00130578(o, 0x40000011, 0.0f);
        func_00267560(d, o->x148, -1.0f);
        d[3] = 0.0f;
        o->x150 = atan2f(-o->x148[0], -o->x148[2]);
        o->x148[5] = o->pos[1];
    }
    return k;
}
#include "data/bss_0052_typed.h"
