/* A value selector (a guess at the name), 0x0010ef90-0x0010f580: a text
 * object (func_0010ef90) whose value D_004D5AF8 steps with the pad's
 * repeat between a range's min and max (func_0010f368, with a sound) and
 * is drawn with a cosf pulse (func_0010f0d0). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "m2c.h"
#include "data/bss_0049.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002BC0A8.h"

/* func_0010ef90 (from hand/text_00110000_h29.c). */
typedef struct { u16 x0; u8 pad2[10]; u8 xc; } W29Sub;
typedef struct {
    s32 x0;
    s32 x4;
    s16 x8, xa;
    u16 xc, xe;
    u8 x10, x11, x12, x13;
    s32 x14;
    f32 x18, x1c;
    W29Sub *x20;
    void *x24;
    s32 x28;
} W29Obj;
extern s32 D_004D59F0[];
extern s32 D_004D5AF0;
void *func_00121e28(s32, void *);
void func_00121ee0(void *);
void func_0010d470(W29Obj *, W29Sub *);
s32 func_0010ef90(s32 a, s32 *out) {
    struct { W29Obj *o; W29Sub *s; } l;
    W29Obj *p, *p2, *p3, *p4, *p5;
    s32 i, m;
    p = l.o = func_00121e28(0x2C, &l.o);
    p->x12 = 0;
    p2 = l.o;
    p2->x10 = 1;
    p2->x0 = 0;
    p3 = l.o;
    p3->x4 = a;
    p3->x13 |= 2;
    p3->x8 = 0;
    p3->xa = 0;
    p3->x24 = 0;
    p3->x14 = 0;
    p4 = l.o;
    p4->x11 = 0;
    p5 = l.o;
    p5->xc = 0;
    p5->xe = 0;
    p5->x18 = 0;
    p5->x1c = 0;
    p5->x20 = 0;
    p5->x28 = 0;
    l.s = func_00121e28(0x1890, &l.s);
    func_0010d470(l.o, l.s);
    func_00121ee0(l.s);
    func_00121ee0(l.o);
    m = 0;
    for (i = 0; i < D_004D5AF0; i++) {
        if (m < D_004D59F0[i]) m = D_004D59F0[i];
    }
    *out = D_004D5AF0;
    return m;
}

/* func_0010f098 (from auto/text_00100000_9.c). */
#define func_0010ef90 ((s32 (*)(s32, s32)) func_0010ef90)
s32 func_0010f098(s32 arg0) {
    s32 sp[4];
    return (func_0010ef90(arg0, (s32) sp) / 24) + 1;
}
#undef func_0010ef90

/* func_0010f0d0 (from hand/text_00100000_h51.c). */
void func_00106b18(void *);
typedef struct { u8 pad[0x30]; f32 x; f32 y; u8 pad38[0x38]; f32 ox; f32 oy; } Obj70;
extern f32 D_002BBDFC;
extern f32 D_004D5AFC;
extern u64 D_002BBAF0[];
extern u64 D_002BBB90[];
f32 cosf(f32);
void func_0010f0d0(s32 px, s32 py, Obj70 *o) {
    s32 c, x2;
    D_004D5AFC += D_002BBDFC * 0.2f;
    if (D_004D5AFC > 3.14159275f) D_004D5AFC -= 6.2831854820251465f;
    if (D_004D5AFC < -3.14159275f) D_004D5AFC += 6.2831854820251465f;
    c = cosf(D_004D5AFC) * 64.0f + 64.0f;
    px = px + (o->x - o->ox);
    py = py + (o->y - o->oy);
    {
    u64 a, b, d, e;
/*P*/
    x2 = px + 40;
    a = (u64)(px * 16 - c + 0x7000);
    b = (u64)(x2 * 16 - c + 0x7000);
    { s32 y2 = py + 24; d = (u64)(py * 16 + 0x7400) << 16; e = (u64)(y2 * 16 + 0x7400) << 16; }
/*Q*/
    D_002BBAF0[17] = a | d | (u64)1 << 32;
    D_002BBAF0[19] = b | e | (u64)1 << 32;
    }
    func_00106b18(D_002BBB90);
}

/* func_0010f258 (from hand/text_00110000_h29.c). */
typedef struct { u8 pad[6]; u16 v; u8 pad8[8]; } W29Ent;
typedef struct { u16 n; u8 pad[0xe]; W29Ent e[1]; } W29Tbl;
typedef struct { u8 pad[0x88]; u16 x88; u8 pad8a[0x16]; W29Tbl *xa0; } W29Mdl;
typedef struct { s32 a, b; } W29Pair;
typedef struct { s32 x0, x4; } W29Cnt;
extern W29Pair *D_004D5AF4;
void func_0010f258(W29Cnt *c, W29Mdl *m) {
    s32 idx[32];
    W29Tbl *t;
    s32 i, k;
    u16 id;
    k = 0;
    t = m->xa0;
    c->x0--;
    c->x4--;
    id = m->x88;
    for (i = 0; i < t->n - 1; i++) {
        if (t->e[i].v != t->e[i + 1].v) idx[k++] = i;
    }
    idx[k++] = t->n - 1;
    D_004D5AF4 = func_00121e28(k * 8, &D_004D5AF4);
    for (i = 0; i < k; i++) {
        s32 j = idx[i];
        D_004D5AF4[i].a = id;
        D_004D5AF4[i].b = ((W29Ent *)t)[j + 1].v;
    }
}

/* func_0010f368 (from hand/text_00110000_h52.c). */
typedef struct { u16 active; u8 x2, x3; u32 cur; union { u64 d; u32 w; } press; u64 rep; } Pad52;
extern Pad52 D_002C5AD0;
typedef struct { s32 min, max; void (*fn)(s32); } Range52;
typedef struct { s32 a, b; } Pair52;
extern s32 D_002BBBA0;
extern s32 D_002C5BB8;
void func_0011d768(s32);
extern Pair52 *D_004D5AF4_0010f368 __asm__("D_004D5AF4");
#define D_004D5AF4 D_004D5AF4_0010f368
#define func_0010f0d0 ((void (*)(s32, s32, s32)) func_0010f0d0)
s32 func_0010f368(Range52 *r, s32 arg) {
    s32 old;
    if (D_002C5AD0.rep & 0x10100010) {
        old = D_004D5AF8;
        D_004D5AF8 = old - 1;
        if (D_004D5AF8 < r->min) {
            if (D_002C5AD0.press.d & 0x10100010) {
                D_004D5AF8 = r->max;
                func_0011d768(1);
            } else {
                D_004D5AF8 = old;
            }
        } else {
            func_0011d768(1);
        }
    } else if (D_002C5AD0.rep & 0x40400040) {
        old = D_004D5AF8;
        D_004D5AF8 = old + 1;
        if (r->max < D_004D5AF8) {
            if (D_002C5AD0.press.d & 0x40400040) {
                D_004D5AF8 = r->min;
                func_0011d768(1);
            } else {
                D_004D5AF8 = old;
            }
        } else {
            func_0011d768(1);
        }
    }
    if (!D_002BBBA0 && (D_002C5AD0.press.w & 0x4000)) {
        if (D_004D5AF8 != r->max) func_0011d768(3);
        D_004D5AF8 = r->max;
    }
    func_0010f0d0(D_004D5AF4[D_004D5AF8].a, D_004D5AF4[D_004D5AF8].b, arg);
    if (D_002C5BB8 & 1) {
        func_0011d768(2);
        r->fn(D_004D5AF8 + 1);
        func_00121ee0(D_004D5AF4);
        D_004D5AF4 = 0;
        return 1;
    }
    return 0;
}
#undef D_004D5AF4
#undef func_0010f0d0

/* func_0010f520 (from auto/text_00100000.c). */
#define func_00121ee0 ((M2C_UNK (*)(s32)) func_00121ee0)
extern s32 D_004D5AF4_0010f520 __asm__("D_004D5AF4");
#define D_004D5AF4 D_004D5AF4_0010f520
void func_0010f520(void) {
    if (D_004D5AF4 != 0) {
        func_00121ee0(D_004D5AF4);
    }
}
#undef func_00121ee0
#undef D_004D5AF4

/* func_0010f558 (from auto/text_00100000.c). */
extern s32 D_004D5AF4_0010f558 __asm__("D_004D5AF4");
#define D_004D5AF4 D_004D5AF4_0010f558
extern s32 D_004D5AFC_0010f558 __asm__("D_004D5AFC");
#define D_004D5AFC D_004D5AFC_0010f558
void func_0010f558(s32 arg0, void *arg1, s32 arg2) {
    D_004D5AF8 = arg2 - 1;
    D_004D5AF4 = 0;
    D_004D5AFC = 0;
    M2C_FIELD(arg1, s32 *, 0xA8) = arg0;
}
#undef D_004D5AF4
#undef D_004D5AFC

