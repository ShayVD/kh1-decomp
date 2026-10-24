/* Hand-matched functions, 0x00175ba0..0x00180f10 (worker 11). */
#include "common.h"

/* --- 0x3C-byte entry table (func_00175ba0..func_00175da8) --- */

/* --- relocatable pack: header, n items of 0x20 bytes, then a count and
 * that many offsets (func_001763f0..func_00176578) --- */

/* script handler arguments */
#include "data/types/text_00170000_h11_p4.h"

/* the object D_00575894 points to */
typedef struct Actor {
    u8 pad0[0x3c];
    f32 x3c;    /* 0x3C */
    u8 pad40[0x30];
    s32 x70;    /* 0x70: state */
} Actor;

/* --- 256 entries of 0xC0 bytes at D_00364130 --- */
#include "data/pieces/D_00364130.h"
typedef E0C0_364130_2 E0C0;

#include "data/types/text_00170000_h11.h"

extern Actor *D_00575894; /* src/data/bss_0057.c: void *D_00575894 */
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C5960.h"
extern s32 D_002E27A8;
extern s32 D_00575920; /* src/data/bss_0057.c: S920 D_00575920 */
extern f32 D_005758D0[4];
extern f32 D_005758E0[4];
extern f32 D_00362684;

s32 func_00177218(Actor *);
s32 func_00177258(Actor *);
s32 func_00177288(Actor *);
s32 func_001772c8(Actor *);
s32 func_001773b0(void);
s32 func_0017dc40(void);
void func_00176f08(s32, f32);
void func_00267530(void *, void *, void *);
void func_002675a8(void *, void *);

typedef struct { u8 pad[0x20]; u8 *p20; } Obj20;
void func_001768e8(Arg *a) {
    if (a[1].i) {
        *((Obj20 *)a[0].p)->p20 |= 1;
    } else {
        *((Obj20 *)a[0].p)->p20 &= ~1;
    }
}

f32 atan2f(f32, f32);
void func_00176a18(Arg *a) {
    f32 *p = a[0].p;
    f32 *q = a[1].p;
    a[0].f = atan2f(p[0] - q[0], p[2] - q[2]);
}

void func_0017f580(f32, f32, f32, f32, s32);
void func_00176af0(Arg *a) {
    func_0017f580(a[0].f, a[1].f, a[2].f, a[3].f, a[4].i);
}

typedef struct { u8 pad[0x3c]; s32 x3c; u8 pad40[4]; s32 x44; u8 pad48[0xbe - 0x48]; s16 xbe; } Sub6C;
void func_00176b80(Arg *a) {
    Arg *o = a[0].p;
    ((Sub6C *)o[27].p)->x3c = 1;
    ((Sub6C *)o[27].p)->x44 = 0;
    ((Sub6C *)o[27].p)->xbe = 0;
}

s32 func_00177218(Actor *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    if (o->x70 < 11) { if (o->x70 >= 9) return 1; }
    return 0;
}

s32 func_00177258(Actor *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    return o->x70 == 15;
}

s32 func_00177288(Actor *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    if (o->x70 < 15) { if (o->x70 >= 13) return 1; }
    return 0;
}

s32 func_001772c8(Actor *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    return o->x70 == 18;
}

s32 func_001773b0(void) {
    Actor **p = &D_00575894;
    s32 k;
    if (func_00177218(*p)) { func_00176f08(4, 60.0f); return 0; }
    if (func_00177258(*p)) k = 5;
    else if (func_00177288(*p)) k = 6;
    else if (func_001772c8(*p)) k = 8;
    else goto ret1;
    func_00176f08(k, 60.0f);
    return 0;
ret1:
    return 1;
}

s32 func_00119688(void *);
s32 func_00177440(void *a, void *b) {
    f32 v[4];
    f32 m[12];
    func_00267530(m, b, a);
    func_002675a8(v, a);
    return func_00119688(v) != -1;
}

void func_00118d78(void *);
typedef struct { f32 a[4]; f32 b[4]; s16 c; u8 pad[14]; } M30;
s32 func_00177608(void *out, void *a, void *b) {
    f32 v[4];
    M30 m;
    func_00267530(&m, b, a);
    func_002675a8(v, a);
    func_00118d78(v);
    if (m.c != -1) {
        func_002675a8(out, m.b);
        return 1;
    }
    return 0;
}

s32 func_00177ac0(void);
s32 func_00177ef8(void);
s32 func_00178468(void) {
    s32 a = func_00177ac0();
    s32 b = func_00177ef8();
    return b || a;
}

extern s32 D_00362444;
#include "data/types/text_00170000_h11_p3.h"
Rec *func_0017adf8(Rec *p, s32 n) {
    s32 i;
    for (i = 0; i < D_00362444 && i != n; i++) {
        p = (Rec *)((u8 *)p + p->n * 16 + 32);
    }
    return p;
}

#include "data/pieces/D_003626C0.h"
typedef struct { u8 pad[0x28]; f32 x28; } S5970;
extern S5970 D_00575970;
f32 func_00120c18(void *);
s32 func_0017b170(void) {
    f32 v[4];
    Blk26C0 *s = &D_003626C0;
    f32 r;
    if (!s->flag) return 0;
    func_002675a8(D_005758D0, &s->a);
    func_002675a8(D_005758E0, &s->b);
    func_00267530(v, &D_00575970, D_005758D0);
    r = func_00120c18(v);
    s->flag = 0;
    D_00575970.x28 = r;
    return 1;
}

extern u64 D_002C5BB0;
#include "data/pieces/D_00362438.h"
u8 D_005759A4 ALIGNED(4);
s32 func_001770b8(void);
s32 func_0017b7e8(void) {
    if (!(D_002C5BB0 & 0x300000000000ULL)) {
        if (D_00575920 && !(D_00362438->x18 & 0x10)) goto one;
        if (func_001770b8()) return 1;
        if (!D_005759A4) return 0;
    }
one:
    return 1;
}

extern s32 D_002C5BB8;
typedef struct { u8 pad[0x66]; u8 x66; } S5940;
extern S5940 D_00575940;
void func_0017ba80(s32);
s32 func_0017c190(void);
void func_0017c4c8(void) {
    if (D_002C5BB8 & 0x200) {
        if (D_00575940.x66 != 3) {
            D_00575940.x66 = 2;
            func_0017ba80(4);
        }
    }
    if ((u8)(D_00575940.x66 - 2) < 2) {
        if (!func_0017c190()) D_00575940.x66 = 0;
    }
}

#include "data/pieces/D_00362434.h"
void func_0017ae48(void);
void func_0017d238(void);
f32 func_00124d28(void *, void *);
void func_0017d5d0(void) {
    if (D_00362434) func_0017ae48();
    else func_0017d238();
    D_00362684 = func_00124d28(D_005758D0, D_005758E0);
}

extern s32 D_003623F0;
void func_0017e840(void) {
    if (D_003623F0) {
        if ((D_00575894 = D_002E26A0[0]) != 0) {
            if (!func_0017dc40()) func_00176f08(1, 30.0f);
        }
        D_003623F0 = 0;
    }
}

#include "data/pieces/D_003626F0.h"
void func_0017e8c8(void) {
    Arg *p = ((Arg *)&D_003626F0);
    p[0].i = 1;
    p[1].f = D_00362684 - D_00575894->x3c;
    func_00176f08(0, 0.0f);
}

void func_0017d5a0(void);
void func_0017eff8(void) {
    D_00575920 = 0;
    if (D_002E27A8 != 9 && D_002E27A8 != 2) {
        if (D_00575894 && func_001773b0()) func_00176f08(1, 45.0f);
    } else {
        func_0017d5a0();
    }
}

extern V3 D_00362640[];
extern f32 D_00362660[4];
extern f32 D_00362670[4];
#include "data/pieces/D_003626F8.h"
void func_0017f178(void);
void func_0017f078(s32 i) {
    if (i >= 2) return;
    if (i < 0) return;
    D_003626F8[0] = D_00362660[0];
    D_003626F8[1] = D_00362660[3];
    D_003626F8[2] = D_00362670[1];
    D_00362660[0] = D_00362640[i].x;
    D_00362660[3] = D_00362640[i].y;
    D_00362670[1] = D_00362640[i].z;
    func_0017f178();
}

void func_0011d3c8(s32, s32, s32);
void func_00182788(E0C0 *);
void func_001827f0(E0C0 *);
void func_0017f9d8(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        E0C0 *e = &D_00364130.e0C0_2[i];
        if (e->flags & 1) {
            if (e->p8c && e->p8c->xfc) func_0011d3c8(e->p8c->xfc, e->xa8, 60);
            func_00182788(e);
            func_001827f0(e);
        }
    }
}

void func_0017fa68(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00364130.e0C0_2[i].flags & 1) D_00364130.e0C0_2[i].flags |= 0x20;
    }
}

void func_0017faa8(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00364130.e0C0_2[i].flags & 1) D_00364130.e0C0_2[i].flags &= ~0x20;
    }
}

void func_0017fae8(s32 key) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if ((D_00364130.e0C0_2[i].flags & 1) && D_00364130.e0C0_2[i].key == key) {
            D_00364130.e0C0_2[i].flags |= 0x20;
            return;
        }
    }
}

void func_0017fb40(s32 key) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if ((D_00364130.e0C0_2[i].flags & 1) && D_00364130.e0C0_2[i].key == key) {
            D_00364130.e0C0_2[i].flags &= ~0x20;
            return;
        }
    }
}

void func_00182840(E0C0 *);
void func_0017fc48(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        E0C0 *e = &D_00364130.e0C0_2[i];
        if (e->flags & 1) {
            if (e->p8c && e->p8c->xfc) func_0011d3c8(e->p8c->xfc, e->xa8, 60);
            func_00182788(e);
            func_00182840(e);
        }
    }
}

typedef struct { u8 pad[0x104]; s32 x104; } S104;
s32 func_0017ff98(s32 key) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00364130.e0C0_2[i].key == key) return ((S104 *)D_00364130.e0C0_2[i].p8c)->x104;
    }
    return -2;
}
#if 2 == 1
#define TBL ((void *)0x370200)
#else
extern u8 D_00370200[];
#define TBL D_00370200
#endif

/* needs make: uses rodata */
s32 func_001772f8(Actor *o) {
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return 0;
    switch (o->x70) {
    case 4: case 5: case 8: case 21: case 24: case 26:
        return 1;
    }
    return 0;
}

#include "data/types/text_00170000_h11_p2.h"
#include "data/pieces/D_00362430.h"
typedef E30_362430 E30;
#include "data/types/text_00170000_h11_p.h"
#include "data/pieces/D_00362424.h"
extern s32 D_00362440, D_00362448;
#include "data/pieces/D_00362428.h"
#include "data/pieces/D_0036242C.h"
extern f32 D_00362674;

void func_0017d9c8(Hdr *h) {
    s32 i;
    if (((*(u32 *)&D_002C5960) >> 4) & 1) return;
    D_00362434 = 0;
    D_00362438 = 0;
    D_00362424 = h;
    D_00362440 = h->x1;
    D_00362444 = h->x2;
    D_00362448 = h->x3;
    D_00362428 = (Rec32 *)(h->x4 + (s32)h);
    D_0036242C = (Rec *)(h->x8 + (s32)h);
    D_00362430 = (E30 *)(h->xc + (s32)h);
    for (i = 0; i < D_00362448; i++) {
        E30 *e = &D_00362430[i];
        if ((s32)e->x20 < 0) e->x20 = 0;
        else if (e->x24 & 2) e->x20 = func_0017adf8(D_0036242C, (s32)e->x20);
        else e->x20 = &D_00362428[(s32)e->x20];
    }
    D_00362660[0] = D_00362424->x10;
    D_00362660[3] = D_00362424->x14;
    D_00362674 = D_00362424->x18;
    func_0017f178();
}
#include "data/data_002E.h"
#include "data/data_0036.h"
#include "data/data_0037.h"
#include "data/pieces/D_00362640.h"
