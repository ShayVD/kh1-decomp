#include "common.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
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

typedef struct { u8 pad[6]; u16 v; u8 pad8[8]; } W29Ent;
typedef struct { u16 n; u8 pad[0xe]; W29Ent e[1]; } W29Tbl;
typedef struct { u8 pad[0x88]; u16 x88; u8 pad8a[0x16]; W29Tbl *xa0; } W29Mdl;
typedef struct { s32 a, b; } W29Pair;
typedef struct { s32 x0, x4; } W29Cnt;
extern W29Pair *D_004D5AF4; /* src/data/bss_004D.c: s32 D_004D5AF4 */

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

#include "data/types/text_00110000_h29_p.h"
extern s32 D_004D9240;
extern W29S70 D_002C5AD0[2];
extern W29S70 D_002BCA00[2];
s32 func_0010f8a0(void);
void func_0011f668(void);
void func_001ba4a8(void);

void func_0010fd40(void) {
    s32 i;
    func_0010f8a0();
    if (D_004D9240) {
        for (i = 0; i < 2; i++) D_002C5AD0[i] = D_002BCA00[i];
    }
    func_0011f668();
    for (i = 0; i < 2; i++) D_002BCA00[i] = D_002C5AD0[i];
    if (D_004D9240) func_001ba4a8();
}

typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct { u64 d, a; } W29Ad;
typedef struct {
    union {
        u128 q;
        struct {
            u64 nloop : 15;
            u64 eop : 1;
            u64 pad16 : 16;
            u64 id : 14;
            u64 pre : 1;
            u64 prim : 11;
            u64 flg : 2;
            u64 nreg : 4;
            u64 regs : 4;
            u64 regs_hi : 60;
        } b;
    } tag;
    W29Ad r[31];
} W29Env;
W29Env D_004D8EF0 ALIGNED(16);

#include "data/types/text_00110000_h29_p3.h"

#include "data/types/text_00110000_h29.h"
typedef struct { u8 b[0x50]; } W29E50;
W29E50 D_004D9380[2] ALIGNED(64);
W29E50 D_004D9420[0x40][2] ALIGNED(32);

static inline f32 w29_dot(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void w29_scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}

static inline void w29_add(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

#include "data/types/text_00110000_h29_p2.h"

static inline void w29_sub(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void w29_outer(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4, $vf5\n"
        "vopmsub.xyz $vf6, $vf5, $vf4\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
extern s32 D_002BD170;

static inline void w29_copy(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "sq $6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "memory");
}

static inline void w29_scale4(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyzw $vf6xyzw, $vf4xyzw, $vf5x\n"
        "sqc2 $vf6, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}

/* needs make: uses rodata */

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
s32 D_002BD170 ALIGNED(16) = 0;
#include "data/bss_004D_typed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_0030.h"
#include "data/data_0035.h"
#include "data/data_0048.h"
#include "data/pieces/D_002BCA00.h"
#include "data/pieces/D_002C5AD0.h"
