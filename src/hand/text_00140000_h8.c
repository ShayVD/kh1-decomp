/* Hand-matched functions near 0x145000-0x14C600 (worker 8). */
#include "common.h"
#include "data/bss_0053.h"
#include "data/bss_0054.h"

typedef struct W8Node { u8 pad[8]; struct W8Node *next; u8 pad2[10]; u8 x16; u8 p17; f32 x18; } W8Node;
extern W8Node *D_0052EB58; /* src/data/bss_0052.c: Snd *D_0052EB58 */
void func_00150d70(void);
extern s32 D_00304E3C;
extern u8 D_0052EB50[], D_0052EB60[];
void func_00176340(s32);
void func_0011efa8(void *, void *, s32, s32);
void func_001460b8(void);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
s32 func_00148e20(void);
s32 func_0014dab8(void);
extern s32 D_00531B64, D_00531B68;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x144-8]; s32 x144; u8 pad148[0x376-0x148]; u16 x376; } W8Obj;
void func_0012bce0(s32, s32, s32, void *, s32);
void func_001c48c8(s32, s32, s32);

typedef struct { u8 pad[16]; u64 x10; u64 b0:8; u64 b8:1; u64 b9:55; } W8Ent35;
extern W8Ent35 D_0035C710[];
typedef struct { u8 pad[4]; void *x4; s32 x8; } W8Ent78;
extern void *D_002E26A0[];
extern u32 D_002C5958;
W8Ent78 *func_00134928(void *);
void func_001350d0(W8Ent78 *);
s32 func_0012ba98(s32);
typedef struct {
    union { u64 x; struct { u64 b0:1; u64 b1:1; u64 b2:1; u64 b3:1; u64 f4:1; u64 r:59; } b; struct { u32 w0; s32 x4; } w; } f;
    u16 x8; u16 xa; s32 xc; u8 x10[16];
} W8S78;
void func_0011d2d0(s32, s32, s32);
s32 func_001ecfd8(void *);
typedef struct { u8 pad[0x38]; void (*x38)(void); } W8X38;
void func_00146600(W8Obj *a, s32 b);
void func_00146678(void *a, void (*cb)(void *, W8Ent78 *));
s32 func_00146a68(s32, s32, s32, s32);
W8S78 *func_00146bd0(s32, s32);
s32 func_00147240(s32, s32);
void func_002675a8(void *, void *);
void func_0011d1e0(s32, s32, void *, s32);
W8S78 *func_001473a8(s32 a, s32 b, void *c);
extern W8S78 D_00532B90[]; /* src/data/bss_0053.c: Ent32 D_00532B90[128] */
typedef struct { u8 pad[0x34]; s32 x34; } W8Y2;
typedef struct { u8 pad[0x18]; W8Y2 *x18; } W8Y1;
typedef struct { u8 pad[0x14c]; W8Y1 *x14c; } W8Y;
extern s32 D_00308874[];
void func_00176ba8(void *, s32);
extern u8 D_00533BA0[];
typedef struct { u8 pad[0xc]; f32 xc; } W8Fc;
typedef struct { u8 pad[0x8]; f32 *x8; W8Fc *xc; u8 pad10[0x14 - 0x10]; u32 x14; u8 pad18[0x30 - 0x18]; s32 x30; u8 pad34[0x38 - 0x34]; s32 x38; } W8O60;
typedef struct { u8 pad[0x2c]; f32 x2c; } W8F2c;
typedef struct { f32 m[4][4]; W8O60 sub; s32 x7c; s32 x80; W8F2c *x84; } W8Mdl;
extern W8Mdl D_0054C120;
extern W8O60 D_00547C00[]; /* src/data/bss_0054.c: W34Mdl3C D_00547C00[256] */
extern W8O60 *D_0054B800; /* src/data/bss_0054.c: W34Mdl3C *D_0054B800 */
void func_00147e08(W8O60 *, W8Mdl *);
u8 *func_001623e0(s32);
void sceVu0CopyMatrix(void *, void *);
s32 func_00176488(s32, W8O60 *, s32, s32);
typedef struct { u8 pad[0x10]; s32 x10; W8O60 *x14; s32 x18; f32 x1c; u8 x20[0x10]; } W8Task;
extern f32 D_002BBDFC;
extern u8 D_0054B808[];
void func_00176310(W8O60 *);
W8Task *func_0011f090(void *, s32, void *);
s32 func_00147ff0(W8Task *t);
W8O60 *func_00147c30(void);
typedef struct { u8 pad[0x54]; s32 x54; f32 x58; f32 x5c; f32 x60; } W8C;
typedef struct { s32 x0; s32 x4:8; s32 x5:8; s32 x6:16; s32 x8; f32 xc; s32 x10; f32 x14; s32 x18; s32 x1c; u8 pad20[0x6c - 0x20]; W8C *x6c; } W8R;
typedef W8R W8B;
W8Task *func_00147d18(void *);
s32 func_001480d0();
W8R *func_00121e28(s32, void *);
W8R *func_00148438(W8O60 *o, W8B *b);
W8R *func_00148570(W8O60 *, s32, s32);
W8O60 *func_00147c98(s32 a, s32 b, s32 c);
typedef union { s32 i; u32 u; f32 f; void *p; u8 b[4]; s16 h[2]; } W8Arg;
typedef struct { u8 pad[0x370]; union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b; } x370; } W8Ply;
#include "data/pieces/D_00350CE0.h"
W8R *func_001486d8(W8O60 *a, W8B *b);
W8R *func_00148cb0(s32, f32);
typedef struct { u8 pad[6]; s16 x6; } W8H6;
W8H6 *func_00147840(s32);
#include "data/pieces/D_00350CE8.h"
typedef struct { u8 pad[88]; } W8E88;
u8 *func_001477c8(s32 a);
typedef struct { u32 x0; s32 x4; u8 pad8[4]; s32 xc; s32 x10; u8 pad14[0xc]; } W8E32;
extern W8E32 D_0054C1B0[]; /* src/data/bss_0054.c: Ent9c D_0054C1B0[0x3] */
extern u32 D_0054C434;
extern W8O60 D_0054C218[]; /* src/data/bss_0054.c: W34E3C D_0054C218[0x9] */
typedef struct { u8 pad[4]; s32 x4; s32 x8; u8 padc[4]; s32 x10; } W8Q;
extern char D_0048E410[];
extern s32 D_00350D10;
s32 sprintf(char *, const char *, ...);
void func_00149a88();
void func_00120748(char *, s32, void *, s32);
s32 func_00149eb8(s32);
s32 func_00123488(s32);
void func_00149860(s32);
s32 func_00149c80(s32, void *);
void func_00149e60(s32);
extern void *D_0054C210;
extern u8 D_006A0000[];
extern s32 D_00350D18[];
typedef struct { u8 pad[0x28]; s32 x28; } W8Z5c;
typedef struct { u8 pad[8]; s32 x8; u8 padc[0x5c - 0xc]; W8Z5c *x5c; } W8Z;
s32 func_00176578(s32, s32, s32, s32);
s32 func_00147ed8(s32, s32, s32, s32);
typedef struct {
    union { u64 x; struct { u64 b0:11; u64 f11:1; u64 b12:2; u64 f14:1; u64 f15:1; u64 f16:1; u64 r:47; } b; struct { u32 lo; u32 hi; } w; } f;
    u8 pad8[8];
    u8 x10[0x30];
    u8 x40[0x14];
    u32 x54;
    u8 x58[0x18];
    u8 x70[0x10];
    u8 x80[0x34];
    void (*xb4)(void *, s32);
    s32 xb8;
    u8 xbc[4];
} W8P;
extern W8P D_0054C440[];
extern u32 D_0054F440;
W8P *func_0014a398(W8P *p);
void func_0014aa50(u32 m);
void func_0014aab0(W8P *p);
void func_002674f0(f32 *, void *, void *, f32);
s32 func_0014b768(W8P *, f32 *, f32 *);
void func_0014c130();
typedef struct { u8 pad[0x100]; union { f32 f; u64 x; struct { u64 lo:32; u64 b32:1; u64 r:31; } b; } x100; } W8A148;
typedef struct { u8 pad[0x148]; W8A148 *x148; u8 pad14c[0x1cc - 0x14c]; u32 x1cc; u8 pad1d0[0x3c0 - 0x1d0]; u8 x3c0[0x14]; f32 x3d4; } W8Act;
void func_00267560(void *, void *, f32);
void func_0014cce0(W8Act *, f32);
void func_00130398(W8Act *, s32, f32);
void func_0014f658(W8Act *, s32);
s32 func_0014c4a8(W8Act *a);
typedef struct { u8 pad[0x36]; u8 x36; } W8Save;
extern W8Save *D_00304BE8;

void func_00145138(void) {
    W8Node *n;
    for (n = D_0052EB58; n; n = n->next) { n->x16 = 3; n->x18 = 12.0f; }
    func_00150d70();
}

void func_00146508(void) {
    s32 i;
    if (D_00304E3C) { func_00176340(D_00304E3C); D_00304E3C = 0; }
    func_0011efa8(D_0052EB50, D_0052EB60, 48, 256);
    for (i = 0; i < 256; i++) D_0035C710[i].b8 = 0;
}

void func_00146590(void) {
    func_00146508();
    if (!func_0011ef38(func_001460b8)) func_0011ef10(0x17318, func_001460b8);
    D_00304E3C = func_00148e20();
    D_00531B64 = 0;
    D_00531B68 = func_0014dab8();
}

void func_00146600(W8Obj *a, s32 b) {
    s32 buf[2];
    s64 t = (s32)a->x376;
    if ((s32)t & 1) {
        if (a->x144) { buf[0] = (s32)&b; buf[1] = 4; func_0012bce0(a->x144, 0, 1, buf, 0); }
    } else func_001c48c8(a->x4, 2, b);
}

void func_00146678(void *a, void (*cb)(void *, W8Ent78 *)) {
    W8Ent78 *e;
    while ((e = func_00134928(a)) != 0) {
        if (!((D_002C5958 >> 20) & 1)) {
            if (e->x8 > 0 || e->x4 == D_002E26A0[0]) cb(a, e);
        }
        func_001350d0(e);
    }
}

void func_00146718(W8Obj *a) {
    s64 t;
    func_00146678(a, (void *)func_00146600);
    t = (s32)a->x376;
    if ((s32)t & 1) {
        if (a->x144 && func_0012ba98(a->x144) < 0) a->x144 = 0;
    }
}

void func_00146778(W8S78 *p, s32 v) {
    if (((s32)(p->f.x >> 4) & 1) != v) {
        func_0011d2d0(p->x8, p->f.w.x4, v);
        p->f.b.f4 = v;
    }
}

s32 func_001468b0(W8X38 *a) {
    if (!func_001ecfd8(a)) {
        if (a->x38) a->x38();
        return 4;
    }
    return 8;
}

s32 func_00146b90(s32 a, s32 b, s32 c, s32 d) {
    if ((D_002C5958 >> 18) & 1) return 0;
    return func_00146a68(a, b, c, d);
}

W8S78 *func_00146fb8(W8Y *a, s32 b, s32 c) {
    W8S78 *r = 0;
    if (a->x14c) r = func_001473a8(c + a->x14c->x18->x34, b, (u8 *)a + 16);
    return r;
}

W8S78 *func_001471e8(s32 a, s32 b) {
    s32 i;
    for (i = 0; i < 128; i++) {
        if ((D_00532B90[i].f.w.w0 & 1) && D_00532B90[i].x8 == a && D_00532B90[i].f.w.x4 == b) return &D_00532B90[i];
    }
    return 0;
}

W8S78 *func_001473a8(s32 a, s32 b, void *c) {
    W8S78 *e = func_00146bd0(a, b);
    if (e) {
        func_002675a8(e->x10, c);
        func_0011d1e0(e->x8, e->f.w.x4, e->x10, 0);
    }
    return e;
}

W8S78 *func_00147410(s32 a, s32 b, s32 c) {
    W8S78 *e;
    if (!func_00147240(a, b)) {
        e = func_00146bd0(a, b);
        if (e) {
            func_0011d1e0(e->x8, e->f.w.x4, (u8 *)c + 16, 0);
            e->f.b.b2 = 1;
            e->xc = c;
        }
        return e;
    }
    return 0;
}

void func_00147790(s32 i) {
    func_00176ba8((u8 *)D_00308874 - 4 + D_00308874[i], 0);
}

s32 func_00147a68(void) {
    W8Mdl *m = &D_0054C120;
    W8O60 *s = &m->sub;
    f32 v[4];
    if (&m->sub == 0 || (s->x14 & 3) != 1) return 4;
    if (m->x84) {
        f32 f = m->x84->x2c;
        v[2] = f;
        v[1] = f;
        v[0] = f;
        func_002675a8((void *)m->sub.x8, v);
    }
    func_00147e08(s, m);
    sceVu0CopyMatrix(m, func_001623e0(m->x7c) + m->x80 * 64);
    return 0;
}

W8O60 *func_00147be0(s32 a) {
    s32 i;
    for (i = 0; i < 256; i++) {
        W8O60 *p = &D_00547C00[i];
        if (p && (p->x14 & 3) == 1 && p->x38 == a) return p;
    }
    return 0;
}

W8O60 *func_00147c30(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        D_0054B800++;
        if (D_0054B800 >= &D_00547C00[256]) D_0054B800 = D_00547C00;
        if (!(D_0054B800->x14 & 3)) return D_0054B800;
    }
    return 0;
}

W8O60 *func_00147c98(s32 a, s32 b, s32 c) {
    W8O60 *e;
    if (!a) return 0;
    e = func_00147c30();
    if (e) {
        if (func_00176488(a, e, b & 0x7ff, c)) return e;
        e->x14 = 0;
    }
    return 0;
}

s32 func_00147f20(W8Task *t) {
    W8O60 *e = t->x14;
    W8Fc *p;
    f32 v;
    s32 r;
    if (!e || (e->x14 & 3) != 1) return 4;
    p = e->xc;
    v = p->xc - t->x1c * D_002BBDFC;
    r = 0;
    if (v <= 0.0f) { v = 0.0f; r = 4; }
    p->xc = v;
    return r;
}

void func_00148068(W8O60 *o, f32 f) {
    W8Task *t = func_0011f090(D_0054B808, -1, func_00147ff0);
    t->x14 = o;
    t->x18 = (s32)((W8O60 **)o)[12];
    t->x1c = 1.0f / f;
}

W8R *func_00148438(W8O60 *o, W8B *b) {
    W8Task *t = func_00147d18(func_001480d0);
    W8R *r;
    s32 v;
    if (!t) {
        func_00176340((s32)o);
        return 0;
    }
    *(s32 *)&t->x14 = (s32)o;
    v = o->x30;
    t->x10 = (s32)b;
    t->x18 = v;
    r = func_00121e28(112, t->x20);
    r->x6 = -2;
    r->x0 = 0;
    o->x14 |= 0x20;
    return r;
}

W8R *func_001486d8(W8O60 *a, W8B *b) {
    W8Arg *r = (W8Arg *)func_00148438(a, b);
    f32 f;
    if (r) {
        f = b->x6c->x60;
        a->x8[2] = f;
        a->x8[1] = f;
        a->x8[0] = f;
        r[1].b[0] = 1;
        r[2].i = b->x6c->x54;
        r[3].f = b->x6c->x58;
        r[4].i = 0;
        r[5].f = b->x6c->x5c;
        r[6].i = 0;
        r[7].i = 0;
        return (W8R *)a;
    }
    return (W8R *)r;
}

W8O60 *func_001487f8(s32 a, s32 b, s32 c, s32 d) {
    W8O60 *e = func_00147c98(a, b, 20000);
    if (e) {
        W8R *r = func_00148570(e, c, d);
        if (r && (b & 0x800)) r->x6 = -1;
    }
    return e;
}

W8O60 *func_00148908(W8Ply *a) {
    W8O60 *e = func_00147c98(D_00350CE0, a->x370.b.kind == 1 ? 24 : 19, 20000);
    if (e) e = (W8O60 *)func_001486d8(e, (W8B *)a);
    return e;
}

void func_00148d50(s32 a, f32 x, f32 y, s32 b, s32 c) {
    W8R *r = func_00148cb0(a, y);
    if (r) {
        r->xc = x;
        r->x5 = b;
        r->x8 = c;
        r->x4 = 1;
    }
}

W8E88 *func_001496c8(s32 a, s32 b) {
    s32 n;
    if (!b) return 0;
    n = func_00147840(b)->x6;
    if (!n) return 0;
    return &((W8E88 *)func_001477c8(((s32 *)&D_00350CE8)[a]))[n - 1];
}

W8E32 *func_00149780(s32 a) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if ((D_0054C1B0[i].x0 & 1) && D_0054C1B0[i].x4 == a) return &D_0054C1B0[i];
    }
    return 0;
}

s32 func_001497c8(s32 a) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (D_0054C1B0[i].x10 == a) return i;
    }
    return -1;
}

W8O60 *func_00149810(void) {
    s32 i;
    for (i = 0; i < 9; i++) {
        if (!(D_0054C434 & (1 << i))) {
            D_0054C434 |= 1 << i;
            return &D_0054C218[i];
        }
    }
    return 0;
}

void func_00149b40(W8Q *q) {
    char buf[32];
    u8 *base = func_001477c8(((s32 *)&D_00350CE8)[q->x4]);
    sprintf(buf, D_0048E410, &((W8E88 *)base)[q->x8 - 1], D_00350D10);
    func_00120748(buf, q->x10, func_00149a88, 0);
}

void func_00149f10(s32 a, void (*cb)(void)) {
    s32 id = func_00149eb8(a);
    s32 r = func_00123488(id | 0x10000);
    if (r) {
        func_00149860(r);
        D_0054C210 = cb;
        if (!func_00149c80(id, func_00149e60)) func_00149e60(id);
    } else {
        cb();
    }
}

void func_0014a090(void) {
    s32 i;
    s32 p = (s32)D_006A0000;
    for (i = 0; i < 3; i++) {
        D_0054C1B0[i].x10 = p;
        D_0054C1B0[i].x0 &= ~1;
        D_0054C1B0[i].xc = D_00350D18[i];
        p += D_00350D18[i];
    }
    D_0054C210 = 0;
    D_0054C434 = 0;
}

W8P *func_0014a398(W8P *p) {
    if (p == 0) p = D_0054C440;
    else p++;
    for (; p < &D_0054C440[64]; p++) {
        if ((s32)(p->f.x >> 11) & 1) return p;
    }
    return 0;
}

s32 func_0014a408(void) {
    s32 i;
    for (i = 0; i < 31; i++) {
        if (!(D_0054F440 & (1 << i))) return 1 << i;
    }
    return 0;
}

W8P *func_0014a450(void) {
    s32 i;
    W8P *p = D_0054C440;
    for (i = 0; i < 64; i++, p++) {
        if (!((s32)(p->f.x >> 11) & 1)) {
            p->f.w.lo = 0;
            p->f.b.f11 = 1;
            break;
        }
    }
    return p;
}

void func_0014a898(W8P *p, void *v) {
    func_002675a8(p->x70, v);
    func_002675a8(p->x80, v);
    func_002675a8(p->x10, v);
    func_002675a8(p->x40, v);
    p->f.b.f14 = 0;
    p->f.b.f16 = 1;
}

void func_0014aa50(u32 m) {
    W8P *p = 0;
    while ((p = func_0014a398(p)) != 0) {
        if (p->x54 & m) return;
    }
    *(volatile u32 *)&D_0054F440 &= ~m;
}

void func_0014aab0(W8P *p) {
    if (p->xb4) p->xb4(p, p->xb8);
    p->f.w.lo = 0;
    p->f.w.hi = 0;
    func_0014aa50(p->x54);
}

void func_0014b958(W8P *p) {
    f32 a[4];
    f32 b[4];
    if ((s32)(p->f.x >> 16) & 1) {
        func_002674f0(a, p->x70, p->x80, 0.5f);
        func_002674f0(b, p->x10, p->x40, 0.5f);
        func_0014b768(p, a, b);
    }
}

/* 0x14bba8 (needs func_0014b958 defined above) */
typedef struct {
    union { u64 flags; s32 w; } u;
    u8 pad8[4];
    f32 f0c;
    f32 v10[4];
    s32 i20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x34-0x2c];
    s32 i34;
    u8 pad38[0x3c-0x38];
    f32 f3c;
    f32 v40[4];
    u8 pad50[0x54-0x50];
    s32 i54;
    u8 pad58[0x70-0x58];
    f32 v70[4];
    f32 v80[4];
    s32 i90;
} Src57;
typedef struct { s32 kind; s32 a4; s32 a8; s32 src; s32 a10; f32 f14; f32 f18; s32 pad1c; f32 v[4]; } Ent57;
void func_001315c0(s32, s32, f32 *, f32);
s32 func_0014b9e0(Src57 *s, f32 *a, f32 *b, f32 f0, f32 f1, Ent57 *tbl, s32 n);
s32 func_0014bba8(Src57 *s, Ent57 *tbl, s32 cnt) {
    s32 k;

    if ((s->u.w & 3) == 1) {
        func_001315c0(s->i90, s->i20, s->v10, s->f24);
    }
    k = (s32)(s->u.flags >> 17) & 7;
    if (k != 1 && k != 4 && k != 2 && ((s32)(s->u.flags >> 16) & 1)) {
        cnt += func_0014b9e0(s, s->v10, s->v70, s->f0c, s->f0c, tbl, cnt);
    }
    switch (s->u.w & 3) {
    case 0:
        func_002675a8(s->v40, s->v10);
        k = (s32)(s->u.flags >> 17) & 7;
        if (k == 1 || k == 4 || k == 2 || !((s32)(s->u.flags >> 16) & 1)) {
            cnt += func_0014b9e0(s, s->v10, s->v10, s->f0c, s->f0c, tbl, cnt);
        }
        break;
    case 1:
        func_001315c0(s->i90, s->i20, s->v40, s->f28);
        cnt += func_0014b9e0(s, s->v10, s->v40, s->f0c, s->f0c, tbl, cnt);
        break;
    case 2:
        cnt += func_0014b9e0(s, s->v10, s->v40, s->f0c, s->f3c, tbl, cnt);
        break;
    }
    if (!((s32)(s->u.flags >> 20) & 1)) {
        if ((s->u.w & 3) != 2 || func_0014b768((W8P *)s, s->v40, s->v10)) {
            func_0014b958((W8P *)s);
        }
    }
    return cnt;
}

void func_0014c330(void) {
    W8P *p = 0;
    while ((p = func_0014a398(p)) != 0) func_0014aab0(p);
}

void func_0014c378(void) {
    s32 i;
    for (i = 63; i >= 0; i--) D_0054C440[i].f.w.lo = 0;
    D_0054F440 = 0;
    if (!func_0011ef38(func_0014c130)) func_0011ef10(0x13881, func_0014c130);
}

void func_0014c400(W8Act *a) {
    a->x148->x100.f = 46.0f;
    a->x1cc &= ~1;
}

void func_0014c428(W8Act *a) {
    a->x148->x100.f = 24.0f;
    a->x1cc |= 1;
}

void func_0014c448(W8Act *a) {
    func_00267560(a->x3c0, a->x3c0, 0.7f);
    func_0014cce0(a, 8.0f);
    func_00130398(a, 6, 8.0f);
}

s32 func_0014c4a8(W8Act *a) {
    if (a->x148->x100.f <= 0.0f && 50.0f < a->x3d4) {
        func_00130398(a, 113, 16.0f);
        func_00267560(a->x3c0, a->x3c0, 0.5f);
        func_0014f658(a, 21);
        return 1;
    }
    return 0;
}

void func_0014c530(W8Act *a) {
    if (func_0014c4a8(a)) a->x148->x100.b.b32 = 0;
}

/* needs make: uses rodata */
s32 func_00149678(void) {
    switch (D_00304BE8->x36) {
    case 88:
    case 91:
    case 99:
        return 0;
    case 82:
    case 86:
    case 89:
    case 94:
    case 95:
    case 97:
    case 100:
    case 102:
        return 2;
    default:
        return 1;
    }
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_0048E408[];
s32 D_00350D10 ALIGNED(16) = (s32)D_0048E408;
#include "data/bss_0052_mixed.h"
#include "data/bss_0054_mixed.h"
#include "data/data_0048.h"
#include "data/data_0030.h"
#include "data/data_0035.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
