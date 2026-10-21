#include "common.h"
#include "data/bss_0052.h"

#include "data/types/nostrict_text_00120000_b02.h"
typedef struct { u8 p0[4]; u32 f4; u8 p8[0x4c - 8]; u16 h4c; } K14;
typedef struct { s32 f0; s32 f4; u8 p8[4]; u8 c[4]; } Q14;
typedef struct { s32 f0; s32 f4; } R14;
typedef struct {
    u32 f0;
    u8 p4[0x48 - 4];
    f32 f48;
    u8 p4c[4];
    V4 f50;
    u8 p60[0xd0 - 0x60];
    f32 fd0[4][4];
    u8 p110[0x130 - 0x110];
    K14 *f130;
    u8 p134[0x14c - 0x134];
    Q14 *f14c;
    u8 p150[0x15c - 0x150];
    s32 f15c;
    u64 f160;
    u8 p168[0x370 - 0x168];
    u64 f370;
    u8 p378[0x410 - 0x378];
    f32 f410;
    f32 f414;
    u8 p418[8];
    s32 f420;
} O14;
typedef struct {
    u32 f40;
    s32 f44;
    s32 f48;
    u8 c[4];
    u8 b[4];
    s32 f54;
    u8 d[4];
    u8 e[4];
    void *fn;
    void *p;
    u32 fl;
    s32 f6c;
    void *fn1;
    void *fn2;
    u64 g[2];
} S14;
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002E26C0.h"
extern void func_00122770(void);
extern void func_001229c0(void);
extern void func_00135ed0(void);
extern void func_00175600(void);
extern R14 *func_001357b8(void);
extern void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
extern void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern void func_002675a8(f32 *, V4 *);
extern void func_00135a68(u8 *, f32, f32);
extern s32 func_00121000(f32 (*)[4], u8 *);
extern void func_001621e0(s32, f32 (*)[4], S14 *, O14 *);
void func_00136428(O14 *o, u32 fl, s32 a2, f32 *col, f32 alpha) {
    f32 m[4][4];
    S14 s;
    u8 buf[128];
    s32 i;
    Q14 *q;
    R14 *r;

    s.f44 = o->f420;
    s.f48 = -1;
    s.fn1 = func_00122770;
    s.fn2 = func_001229c0;
    s.b[0] = D_002BC0F0.i[4];
    s.b[1] = D_002BC0F0.i[5];
    s.b[2] = D_002BC0F0.i[6];
    s.b[3] = (s32)alpha;
    s.f40 = 0;
    switch (o->f130->h4c) {
    case 35:
    case 516:
        r = func_001357b8();
        r->f0 = (s32)o;
        r->f4 = o->f48 * 128.0f;
        s.p = r;
        s.fn = func_00135ed0;
        break;
    case 507:
        if ((s32)(o->f160 >> 10) & 1) {
            fl |= 4;
            s.fn = func_00175600;
        } else {
            s.fn = 0;
        }
        break;
    default:
        s.p = o;
        s.fn = 0;
        break;
    }
    s.fl = fl;
    s.f6c = a2;
    for (i = 0; i < 4; i++) s.c[i] = (s32)col[i];
    q = o->f14c;
    if (q && q->f0 && (o->f0 & 0x4000)) {
        s.f54 = q->f4;
        for (i = 0; i < 4; i++) {
            s.d[i] = s.c[i];
            s.e[i] = q->c[i];
        }
    } else {
        s.f54 = 0;
    }
    sceVu0CopyMatrix(m, o->fd0);
    func_002675a8(m[3], &o->f50);
    m[3][3] = 1.0f;
    sceVu0MulMatrix(m, D_002E26C0, m);
    if (!((o->f370 >> 49) & 1)) {
        func_00135a68(buf, o->f410, o->f414);
        if (func_00121000(m, buf)) s.f40 |= 0x100;
    }
    if (o->f130->f4 & 4) s.f40 |= 0x200;
    {
        u64 t = 0x000800d0;
        s.g[0] = 0x31000070;
        s.g[1] = t;
    }
    func_001621e0(o->f15c, D_002E26C0, &s, o);
}

typedef struct { u8 p0[0x10]; O15 *f10; void (*f14)(O15 *); } T15;
#include "data/pieces/D_00304AD8.h"
extern f32 D_002BBDFC;
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
extern s32 D_0052AA68;
extern O15 *D_0052AA70[];
extern void func_00137990(O15 *);
extern void func_00137a20(O15 *);
extern void func_00137db0(O15 *);
extern s32 func_001375d8(O15 *);
extern void *func_00134928(O15 *);
extern void func_001350d0(void *);
extern void func_00131b50(O15 *);
extern void func_001342c8(O15 *);
extern void func_00137748(O15 *);
extern void func_0014fe48(O15 *);
extern void func_00137cf8(O15 *);
extern void func_00137d40(O15 *);
extern void func_001441b8(O15 *);
extern void func_00137ab8(O15 *);
extern void func_00136d38(O15 *);
extern void func_00137c70(O15 *);
extern void func_0012c760(O15 *);
extern void func_00137868(O15 *);
s32 func_00137ea8(T15 *t) {
    O15 *o = t->f10;
    void *e;

    (*(O15 **)&D_00304AD8) = o;
    func_00137990(o);
    func_00137a20(o);
    if (o->f488 && (o->f488->f14 & 3) != 1) o->f488 = 0;
    func_00137db0(o);
    if (func_001375d8(o)) o->f88 &= ~1;
    if (!o->b33 && (o->f0 & 0x8000)) {
        if (o->f88 & 1) {
            if (o->f408 && o->f3ec && ((o->f3ec->d8 >> 38) & 0xf) == 9) {
                e = func_00134928(o);
                o->f408(o, e);
                func_001350d0(e);
            }
            o->f3e4 -= D_002BBDFC;
            if (o->f3e4 <= 0.0f) o->f88 &= ~1;
        } else {
            o->f2c = 0;
            func_00131b50(o);
            if (o->f440) func_001342c8(o);
            func_00137748(o);
            if (!(((*(u32 *)&D_002C5960) >> 2) & 1) && t->f14) t->f14(o);
            o->f8 = 0;
            o->f0 &= ~0x400;
            func_0014fe48(o);
            func_00137cf8(o);
            func_00137d40(o);
            func_001441b8(o);
        }
        if (o->f8c > 0) func_00137ab8(o);
        else func_00136d38(o);
        if (o->b39) func_00137c70(o);
        o->b34 = 1;
        D_0052AA70[D_0052AA68++] = o;
    } else {
        func_002675a8(&o->f120.x, ((V4 *)&D_002C58B0));
    }
    if (o->f14c) func_0012c760(o);
    if (o->b33) {
        func_00137868(o);
        return 4;
    }
    return 0;
}

/* needs make: uses rodata */
typedef struct { s32 off[64]; } Hd10;
typedef struct {
    u8 p0[2];
    u8 kind;
    u8 p3[5];
    u8 *f8;
    u8 *fc;
    u8 p10[0x54 - 0x10];
    s8 f54;
    u8 p55;
    s8 f56;
    u8 p57[0x60 - 0x57];
    s32 f60;
    s32 f64;
    u8 p68[0x78 - 0x68];
} En10;
typedef struct {
    Hd10 *f0;
    s32 *f4;
    s32 *f8;
    s32 fc;
    En10 *f10;
    u8 *f14;
    u8 *f18;
    u8 *f1c;
    u8 *f20;
    u8 *f24;
    u8 *f28;
} Ou10;
extern void func_00132678(u8 *);
extern void func_00132718(u8 *);
#define SECT(h, n) (((h)->off[(n) + 1] - (h)->off[n] > 0) ? (u8 *)(h) + (h)->off[n] : 0)
void func_00132790(Hd10 *f, s32 idx, Ou10 *o) {
    Hd10 *e;
    Hd10 *g;
    u8 *a3;
    En10 *en;
    s32 i;
    s32 *p;

    o->f0 = f;
    if (f->off[2] - f->off[1] > 0) {
        o->f4 = (s32 *)((u8 *)f + f->off[1]);
        for (i = 0; i < o->f4[0]; i++) func_00132678((u8 *)o->f4 + o->f4[i + 1]);
    } else {
        o->f4 = 0;
    }
    if (f->off[3] - f->off[2] > 0) {
        o->f8 = (s32 *)((u8 *)f + f->off[2]);
        for (i = 0; i < o->f8[0]; i++) func_00132718((u8 *)o->f8 + o->f8[i + 1]);
    } else {
        o->f8 = 0;
    }
    e = (Hd10 *)((u8 *)f + f->off[7 + idx]);
    p = (s32 *)((u8 *)e + e->off[1]);
    o->fc = p[0];
    o->f10 = (En10 *)(p + 1);
    o->f14 = SECT(e, 2);
    o->f18 = SECT(e, 3);
    if (e->off[5] - e->off[4] > 0) {
        o->f1c = (u8 *)e + e->off[4];
    } else {
        g = (Hd10 *)((u8 *)f + f->off[32]);
        if (g->off[5] - g->off[4] > 0) o->f1c = (u8 *)g + g->off[4];
        else o->f1c = 0;
    }
    a3 = (u8 *)f + f->off[6];
    en = o->f10;
    for (i = 0; i < o->fc; i++, en++) {
        switch (en->kind) {
        case 4:
        case 8:
        case 9:
            en->f8 = (u8 *)o->f4 + o->f4[en->f56 + 1];
            break;
        case 5:
        case 10:
            en->f8 = (u8 *)o->f8 + o->f8[en->f56 + 1];
            break;
        case 6:
        case 7:
            break;
        }
        if (en->f54 < 0) { s32 k = en->f54; en->fc = ((e->off + 2)[-k] - *((1 - k) + e->off) > 0) ? (u8 *)e + e->off[1 - k] : 0; }
        en->f60 = (s32)(a3 + en->f60 * 32);
        en->f64 = (s32)(a3 + en->f64 * 32);
    }
    o->f20 = SECT(f, 3);
    o->f24 = SECT(f, 4);
    o->f28 = SECT(f, 5);
}

typedef struct { u8 p0[4]; u32 f4; u8 p8[0x4c - 8]; u16 h4c; u8 p4e[6]; s8 b54; } K16;
typedef struct { u8 p0[6]; u8 f6; u8 p7[0x130 - 7]; K16 *f130; u8 p134[0x408 - 0x134]; void *f408; } O16;
typedef struct { u8 p0[0x10]; O16 *f10; void *f14; } T16;
#include "data/pieces/D_002E27D4.h"
extern s32 D_002C5C4C;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
extern u32 D_002C5958;
#include "data/pieces/D_00304B6C.h"
extern void func_0014f658(O16 *, s32);
extern T16 *func_001383d8(s32, void *);
extern void func_0013f198(void);
extern void func_0013ab08(void);
extern void func_00146718(void);
extern void func_0014f410(void);
extern void func_00151268(void);
extern void func_00151940(void);
extern void func_00152140(void);
extern void func_001539c0(void);
extern void func_001502e8(void);
extern void func_00156e88(void);
extern void func_00157ea8(void);
extern void func_0015a5b8(void);
extern void func_0015ab50(void);
extern void func_0015a8f0(void);
extern void func_0015a990(void);
extern void func_0015ad08(void);
extern void func_00139cb8(void);
extern void func_0013a0f0(void);
void func_00138400(O16 *o) {
    void *fn = 0;
    s32 pri = 4000;
    T16 *t;

    switch (o->f130->b54) {
    case 0:
        fn = func_0013f198;
        D_002E27D4 = 0;
        pri = 2000;
        if (D_002C5C4C) {
            func_0014f658(o, 24);
        } else if (D_002BC128 == 8 && D_002BC130 == 20 && D_002BC134 < 13) {
            func_0014f658(o, 29);
        } else if (D_002BC128 == 5 && D_002BC130 >= 15 && D_002BC134 < 13) {
            D_002C5958 |= 0x20000;
        }
        break;
    case 1:
        fn = func_0013f198;
        pri = 3000;
        if (D_002C5C4C) {
            func_0014f658(o, 24);
        } else if (o->f130->h4c == 8) {
            func_0014f658(o, 8);
        }
        break;
    case 6:
        fn = 0;
        break;
    case 2:
        D_00304B6C = 0;
        fn = func_0013ab08;
        pri = 7000;
        break;
    case 3:
        fn = func_00146718;
        break;
    case 4:
        fn = func_0014f410;
        break;
    case 7:
        fn = func_00151268;
        break;
    case 8:
        fn = func_00151940;
        break;
    case 9:
        fn = func_00152140;
        break;
    case 10:
        pri = 6000;
        fn = func_001539c0;
        break;
    case 11:
        fn = func_001502e8;
        break;
    case 12:
        fn = func_00156e88;
        break;
    case 13:
        pri = 6000;
        fn = func_00157ea8;
        break;
    case 14:
        break;
    case 15:
        fn = func_0015a5b8;
        break;
    case 16:
        fn = func_0015ab50;
        break;
    case 17:
        fn = func_0015a8f0;
        break;
    case 18:
        fn = func_0015a990;
        break;
    case 19:
        fn = func_0015ad08;
        break;
    case 20:
        break;
    case 5:
    default:
        pri = 4000;
        switch (o->f6) {
        case 3:
            o->f408 = func_00139cb8;
            fn = func_0013a0f0;
            break;
        case 4:
        case 5:
        case 9:
        case 10:
            fn = func_00146718;
            break;
        }
        break;
    }
    if (o->f6 == 5 || o->f6 == 10) pri = 0;
    t = func_001383d8((o->f130->f4 & 0x200) ? -2000 : pri, func_00137ea8);
    t->f10 = o;
    t->f14 = fn;
}
#include "data/bss_0052_typed.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BC128.h"
