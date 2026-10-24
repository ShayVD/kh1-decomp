/* The objects' update tasks: func_00138400 picks an object's update task and
 * priority by its kind, func_00137ea8 / func_00138130 / func_00138258 are
 * the updates (the current object D_00304AD8, the lists D_0052AA58 /
 * D_0052AA68 / D_0052AA70), and small per-frame helpers (func_00137748
 * bobbing, func_00137868). Flag mode: nostrict (the other modes are in the
 * sibling files). Read from the code, not proved by a boot (docs/modules.md
 * "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_004F.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/nostrict_text_00120000_h54.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/types/nostrict_text_00120000_b02.h"
#include "data/pieces/D_002E26C0.h"
#include "data/pieces/D_00304AD8.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_00304B84.h"
#include "data/pieces/D_002E27D4.h"
#include "data/pieces/D_00304B6C.h"

/* func_00137ab8 (from hand/nostrict/text_00120000_h54.c). */
typedef FMtx4 Mtx;
typedef struct E22 { u8 p0[6]; u8 f6; u8 p7[0x10 - 7]; V4 f10; f32 f20[3]; s32 f2c; f32 f30[3]; s32 f3c; u8 p40[0x70 - 0x40]; s32 f70; u8 p74[0xd0 - 0x74]; Mtx fd0; V4 f110; V4 f120; u8 p130[0x370 - 0x130]; u64 f370; u8 p378[0x398 - 0x378]; struct E22 *f398; } E22;
extern void func_001625c8(Mtx, Mtx);
extern void func_00136d38(E22 *);
extern void *func_001230a0(void *);
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
        PlatVu0CopyVector(&v, &p->f10);
        v.w = 1.0f;
        PlatVu0ApplyMatrix(&v, m, &v);
        v.w = 1.0f;
        PlatVu0ApplyMatrix(&v, e->fd0, &v);
        PlatVu0SubVector(&v, &v, &p->f10);
        if ((s32)(p->f370 >> 34) & 1) {
            func_00143d20(p, &v, 0);
            func_00136d38(p);
        } else {
            PlatVu0AddVector(&p->f120, &p->f120, &v);
        }
        if ((u32)(p->f6 - 9) < 2) {
            p->f3c = 0;
            PlatVu0ApplyMatrix(&v, m, (V4 *)p->f30);
            PlatVu0ApplyMatrix(&v, e->fd0, &v);
            func_00137688(p, atan2f(v.x, v.z));
        } else if (p->f70 == 0 || p->f70 == 40 || p->f70 == 41) {
            p->f2c = 0;
            PlatVu0ApplyMatrix(&v, m, (V4 *)p->f20);
            PlatVu0ApplyMatrix((V4 *)p->f20, e->fd0, &v);
        }
    }
}

/* func_00137ea8 (from hand/nostrict/text_00120000_b02.c). */
typedef struct { u8 p0[0x10]; O15 *f10; void (*f14)(O15 *); } T15;
extern f32 D_002BBDFC;
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
extern void func_00137c70(O15 *);
extern void func_0012c760(O15 *);
extern void func_00137868(O15 *);
#define func_00137ab8 ((void (*)(O15 *)) func_00137ab8)
#define func_00136d38 ((void (*)(O15 *)) func_00136d38)
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
        PlatVu0CopyVector(&o->f120.x, &D_002C58B0);
    }
    if (o->f14c) func_0012c760(o);
    if (o->b33) {
        func_00137868(o);
        return 4;
    }
    return 0;
}
#undef func_00137ab8
#undef func_00136d38

/* func_00138258 (from hand/nostrict/text_00120000_h54.c). */
extern u32 D_002C5958;
extern O23 D_002C64A0[96];
extern s32 D_0052ACF0[];
extern s32 D_003044D0;
extern u8 D_0052AA58[];
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

/* func_00138400 (from hand/nostrict/text_00120000_b02.c). */
typedef struct { u8 p0[4]; u32 f4; u8 p8[0x4c - 8]; u16 h4c; u8 p4e[6]; s8 b54; } K16;
typedef struct { u8 p0[6]; u8 f6; u8 p7[0x130 - 7]; K16 *f130; u8 p134[0x408 - 0x134]; void *f408; } O16;
typedef struct { u8 p0[0x10]; O16 *f10; void *f14; } T16;
extern s32 D_002C5C4C;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BC134;
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

