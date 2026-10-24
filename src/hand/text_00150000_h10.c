/* Hand-matched functions near 0x157000-0x176000 (worker 10). */
#include "common.h"
#include "data/bss_0055.h"

/* ---- shared types ---- */
typedef struct { s8 b0, b1, b2, b3; s32 w4; s32 w8; s32 wC; s32 w10; } E551670;
typedef struct { u8 pad[0x4A8]; s32 *tbl; } O4A8;
typedef struct { u8 pad[0xBD]; s8 idx; } O6C;
typedef struct { u8 pad[0x6C]; O6C *p6C; } A157560;

typedef struct { u8 pad[0xC]; void *cb; } Task;

typedef struct { u8 pad[0x18]; f32 f18; f32 x, y, z; u8 pad28[0x20]; s16 h48; u8 pad4a[2]; u16 h4C; } Sub130;
typedef struct { u8 pad[0x130]; Sub130 *p130; } Act130;
typedef struct { u8 pad[8]; u8 e[3][2]; } Tbl144;

typedef struct { u32 flags; u8 pad[0x3BC]; u8 x3C0[4]; } Obj15A;
typedef struct { s32 w0; Act130 *w4; } Node15A;

typedef struct { u8 b0; u8 pad[19]; } Ent20;
typedef struct { u8 pad[4]; u8 n4, n5, n6, n7; u8 pad8[8]; Ent20 *p10, *p14, *p18, *p1C; Ent20 data[1]; } Hdr;
typedef struct { u8 pad[0x134]; Hdr *h; u8 pad138[0x274]; u32 mask; } ObjC9;

typedef struct { u8 pad[0x10]; f32 f10; } Sub6C;
typedef struct { u8 pad[0x6C]; Sub6C *p6C; u8 pad70[0xD8]; u8 *p148; } ObjDA;
typedef struct { u8 pad[4]; union { f32 f; void *p; } f4; } RetDA;

typedef union { u8 b; u32 w; } U2E3190;
typedef struct { u32 lo:16; u32 b16:1; u32 m:6; u32 b23:1; u32 hi:8; } Flg2C5958;
typedef union { u32 w; Flg2C5958 f; } U2C5958;

/* ---- data ---- */
extern E551670 D_00551670[];
extern U2E3190 D_002E3190;
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
extern s32 D_005516EC;
extern U2C5958 D_002C5958;
extern s32 D_005516E8;
extern s32 *D_005516E4;
#include "data/pieces/D_00308CDC.h"
extern s32 D_00351A48;
extern s32 D_0029B418;
extern u8 D_00351AA0[];
extern u8 D_00351AB0[];
#include "data/pieces/D_002C58B0.h"
typedef struct { u8 b[32]; } E551970;
extern E551970 D_00551970[];
extern s32 D_00351AC0;
#include "data/pieces/D_002C58A0.h"
extern f32 D_002BBDFC;
extern f32 D_00551D74;
#include "data/pieces/D_002BBDF8.h"
extern volatile s32 D_00559DB4;

/* ---- callees ---- */
s32 D_00F20000(); /* code at a fixed address (overlay) */
void func_001ed828(s32, s32);
void func_001ed6b0(s32);
void func_001ece70(s32, s32, s32, s32);
void func_001ecc68(s32, s32, s32, s32);
void func_001576a8(E551670 *);
void func_0013dc10(void *, s32);
void func_00130398(void *, s32, f32);
Task *func_00130578(void *, s32, f32);
void func_002673b8(void *, void *, void *);
s32 func_0013c968(s32, s32);
void func_00131498(s32, s32);
void func_001412f8(s32, s32);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_00158ec8(void);
void func_001315c0(void *, s32, void *, f32);
void func_00147ed8(s32, s32, s32, void *);
void func_00135800(void *, f32, f32);
void func_0015a758(void *, void *);
Node15A *func_00134928(void *);
void func_001350d0(Node15A *);
s32 func_0015a498(void *, s32);
void *func_00144e88(s32);
s32 func_00122ff8(Act130 *);
void func_00150d30(s32, s32);
void func_00146188(s32, f32 *, s32);
void func_0014cce0(void *, f32);
void func_002675a8(void *, void *);
void func_0015ac30(void);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
void func_0014cc88(void *, f32);
void func_00267560(void *, void *, f32);
RetDA *func_0014cb90(void *);
void func_0014f658(void *, s32);
void func_0015dac0(void);
void func_00118548(void *);
void func_00121fc4(f32 *, f32 *);
f32 func_00121b08(void *, f32);
s32 sceGsSyncPath(s32, u16);
s32 DisableDmac(s32);
s32 func_001684e0(s32);

s32 func_00157560(A157560 *a) {
    E551670 *e = &D_00551670[a->p6C->idx];
    if (e->b0 == 0) return 0;
    return ((s32)e->w4 != (s32)a) ? 1 : 2;
}

void func_001575b0(s32 i) {
    E551670 *e = &D_00551670[i];
    s32 t = e->b0;
    if (t < 5) {
        if (t >= 2) {
            switch (e->b1) {
            case 0:
                func_001ed828(e->b2, e->b3);
                break;
            case 1:
                func_001ed6b0(e->wC);
                break;
            }
        }
    }
    e->b0 = 0;
}

void func_001577a0(E551670 *e) {
    if (e->b1 == 0) {
        func_001ece70(e->b2, e->b3, 0, 0);
    } else {
        s32 *p = ((O4A8 *)e->w4)->tbl;
        func_001ecc68(e->wC, p[e->b3 + 2] - p[e->b3 + 1], 0, 0);
    }
    func_001576a8(e);
}

typedef struct { u8 pad[0xC]; f32 fC; } F158068;
void func_00158068(void *a, s32 b, F158068 *c) {
    if (D_002E3190.b == 1) {
        f32 f;
        func_0013dc10(a, 13);
        f = 0.0f;
        func_00130578(a, 0x40000000, 0.0f);
        c->fC = f;
    } else {
        f32 f = c->fC;
        func_002673b8(c, c, c);
        c->fC = f;
    }
}

void func_001586a8(s32 i) {
    if (D_00304BE8->cnt_848[i] < 9999) D_00304BE8->cnt_848[i]++;
}

void func_001586f0(void) {
    s32 i;
    u8 *p = D_00351A30.b;
    D_005516EC = 0;
    for (i = 0; i < 5; i++, p += 2) {
        if (func_0013c968(*p, 0)) D_005516EC |= 1 << i;
    }
}

void func_00158af0(s32 a, s32 b) {
    volatile u32 *f = &D_002C5958.w;
    *f = (*f | 0x10000) & ~0x800000;
    func_00131498(a, D_005516E8);
    D_00F20000(b, (s32)D_005516E4 + D_005516E4[b + 2]);
    func_001412f8(a, (*(Cfg_308cdc **)&D_00308CDC)->hF4[b]);
}

void func_001590a8(void) {
    Flg2C5958 *f = &D_002C5958.f;
    if (f->b16) {
        D_00F20000(6, 0);
    }
    D_00351A48 = 0;
    f->b16 = 0;
    f->b23 = 0;
    func_001586f0();
    if (func_0011ef38(func_00158ec8) == 0) {
        func_0011ef10(0xCF08, func_00158ec8);
    }
}

s32 func_0015a520(u32 *a, s32 b) {
    u8 buf[16];
    f32 z;
    if (*a & 8) return 0;
    z = 0.0f;
    func_001315c0(a, 0x8003, buf, z);
    func_00147ed8(D_0029B418, b, 20000, buf);
    func_00135800(a, z, 8.0f);
    *a |= 0x68;
    return 1;
}

void func_0015aa30(Act130 *a, Act130 *b);

void func_0015a8f0(void *a) {
    Node15A *p;
    func_0015a758(a, D_00351AA0);
    while ((p = func_00134928(a)) != 0) {
        if (func_0015a520(a, 6)) func_0015aa30(a, p->w4);
        func_001350d0(p);
    }
    if (func_0015a498(a, 23)) func_0015a520(a, 6);
}

void func_0015a990(void *a) {
    Node15A *p;
    func_0015a758(a, D_00351AB0);
    while ((p = func_00134928(a)) != 0) {
        if (func_0015a520(a, 6)) func_0015aa30(a, p->w4);
        func_001350d0(p);
    }
    if (func_0015a498(a, 24)) func_0015a520(a, 3);
}

void func_0015aa30(Act130 *a, Act130 *b) {
    Tbl144 *t = func_00144e88(a->p130->h48);
    s32 i;
    for (i = 0; i < 3; i++) {
        u8 c = t->e[i][0];
        if (c) {
            func_00150d30(c, func_00122ff8(b) ? b->p130->h4C : 12);
        }
    }
}

s32 func_0015aac0(Sub130 *a) {
    u8 *t = func_00144e88(a->h48);
    s32 i;
    f32 v[4];
    for (i = 0; i < 7; i++) {
        if (t[i]) {
            v[0] = a->x;
            v[1] = a->y;
            v[2] = a->z;
            v[3] = 1.0f;
            func_00146188(i, v, 2);
            return 1;
        }
    }
    return 0;
}

void func_0015ac58(Obj15A *a) {
    f32 z = 0.0f;
    func_00130398(a, 0x10000DC, z);
    func_00130578(a, 0x40000006, 8.0f)->cb = func_0015ac30;
    func_0014cce0(a, z);
    a->flags &= ~0x400;
    func_002675a8(a->x3C0, &D_002C58B0);
}

typedef struct { u8 pad[4]; f32 r; f32 h; u8 padc[4]; f32 pos[4]; } Coll;
s32 func_0015b628(Coll *a, Coll *b) {
    f32 d[4];
    f32 r;
    func_00267530(d, b->pos, a->pos);
    if (a->h + b->h <= fabsf(d[1])) return 0;
    r = a->r + b->r;
    d[1] = 0.0f;
    if (func_00267390(d, d) < r * r) return 1;
    return 0;
}

Ent20 *func_0015c960(ObjC9 *a, s32 lo, s32 hi, s32 i) {
    Hdr *h = a->h;
    Ent20 *e;
    if (h == 0) return 0;
    e = &h->p1C[i];
    for (; i < h->n7; i++, e++) {
        if (!(a->mask & (1 << i))) {
            u32 v = e->b0;
            if ((v & 0xF) == lo && (hi < 0 || (v >> 4) == hi)) return e;
        }
    }
    return 0;
}

void func_0015c9f8(Hdr *h) {
    Ent20 *p = h->data;
    h->p10 = p;
    p += h->n4;
    h->p14 = p;
    p += h->n5;
    h->p18 = p;
    p += h->n6;
    h->p1C = p;
}

typedef struct { u32 flags; u8 pad[0x2C]; f32 pos[4]; } ObjD1;
void func_0015d1d0(ObjD1 *a, f32 *v) {
    func_00267530(v, (*(f32 (*)[0x4])&D_002C58A0), a->pos);
    v[3] = 0.0f;
    func_0014cc88(a, v[3]);
    a->flags |= 0x10000;
    func_00130398(a, 0x40000006, 16.0f);
}

typedef struct { u32 flags; u8 pad4[0x1FC]; u8 x200[0x1B0]; f32 f3B0; f32 f3B4; u8 pad3b8[8]; u8 x3C0[4]; } ObjD2;
void func_0015d248(ObjD2 *a) {
    func_0014cc88(a, 0.0f);
    a->flags &= ~0x400;
    a->f3B0 = 6.0f;
    a->f3B4 -= 8.724489212036133f;
    func_00267560(a->x3C0, a->x200, 1.0f / D_002BBDFC);
}

RetDA *func_0015da70(ObjDA *a) {
    RetDA *r = func_0014cb90(a);
    r->f4.f = 4.0f;
    func_0014cce0(a, a->p6C->f10);
    return r;
}

void func_0015db80(u32 *a) {
    f32 z = 0.0f;
    *a &= ~0x200010;
    func_00130398(a, 0x1000010, z);
    func_00130578(a, 0x40000032, z)->cb = func_0015dac0;
    func_0014f658(a, 19);
}

RetDA *func_0015e0a8(ObjDA *a, f32 *v) {
    RetDA *r = func_0014cb90(a);
    r->f4.f = 4.0f;
    func_0014cce0(a, a->p6C->f10);
    func_002675a8(v, a->p148 + 0x110);
    v[1] = 0.0f;
    func_00121fc4(v, v);
    return r;
}

void func_0015e840(void *a) {
    if (D_002E3190.w & 0x18000000) D_00551D74 = 30.0f;
    D_00551D74 = func_00121b08(a, D_00551D74);
    if (D_00551D74 == 0.0f) func_0014f658(a, 24);
}

typedef struct { u8 pad[0x30]; f32 pos[4]; u8 pad40[0x38C]; f32 f3CC; } ObjE9;
void func_0015e9c8(ObjE9 *a, void *b) {
    f32 f = a->f3CC;
    if (f < 18.0f) {
        f = a->f3CC = (f + D_002BBDFC * 0.5f < 18.0f) ? f + D_002BBDFC * 0.5f : 18.0f;
    }
    func_00267560(b, a->pos, f * D_002BBDFC);
}

void func_0015ef60(void) {
    D_002BBDF8;
    while (D_00559DB4) ;
    sceGsSyncPath(0, 0);
    DisableDmac(1);
    DisableDmac(2);
}

typedef struct { s32 a, b, c, d; } V16;
typedef struct { u8 pad[8]; V16 *tbl; } Obj623;
void func_001623f8(Obj623 *o, s32 i, V16 *out) {
    *out = o->tbl[i];
}

typedef union { s32 w; struct { u16 lo, hi; } h; } Key677;
typedef struct { Key677 k; u8 pad[8]; } Ent677;
typedef struct { u8 pad[0x3C]; Ent677 *tbl; } Obj677;
Ent677 *func_001677e0(Obj677 *o, u32 key) {
    Ent677 *e = o->tbl;
    u32 hi = key >> 16;
    key &= 0xFFFF;
    for (; e->k.w != -1; e++) {
        if (e->k.h.hi == hi && (key == 0xFFFF || e->k.h.lo == key)) return e;
    }
    return 0;
}

typedef struct { u8 b0; u8 b1; u8 pad[2]; s32 w4; u8 pad8[8]; s32 w10; } Ent67F;
typedef struct { u8 pad[0x10]; s32 w10; u8 pad14[4]; Ent67F e[4]; } Obj67F;
void func_00167f68(Obj67F *o, s32 a) {
    s32 i;
    o->w10 = func_001684e0(a);
    for (i = 0; i < 4; i++) {
        o->e[i].b1 = 0;
        o->e[i].w4 = 0;
        o->e[i].w10 = 0;
    }
}

s32 func_00168318(u32 *p) {
    switch (*p) {
    case 0x4A424F4D:
    case 0x41584554:
    case 0x454E4F42:
    case 0x4E544D4D:
    case 0x4C535255:
    case 0x564E454D:
        return 1;
    }
    return 0;
}
#include "data/bss_0055_mixed.h"
#include "data/bss_0061_mixed.h"
#include "data/data_0029.h"
#include "data/data_0035.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_00351A48.h"
