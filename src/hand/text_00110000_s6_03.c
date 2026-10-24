#include "common.h"
#include "data/bss_004E.h"
void func_001ed2d8(s32, s32, s32);
void func_001ed370(s32, s32, s32, s32, s32);
CONTEXT_ONLY void func_0011c850(s32 a, s32 b, s32 c) { func_001ed2d8(a, b, c); }
CONTEXT_ONLY void func_0011c868(s32 a, s32 b, s32 c, s32 d, s32 e) { func_001ed370(a, b, c, d, e); }
extern s32 D_002C1390;
CONTEXT_ONLY void func_0011e528(void) { D_002C1390 = 0; }
typedef struct { u32 b0 : 1; u32 rest : 31; } Bits5958;
extern Bits5958 D_002C5958;
extern s32 D_004E3438, D_004E343C, D_004E3440;
extern s32 D_002C1364;
void func_0011c7c0(s32, s32, s32);
void func_0011c7a8(s32, s32, s32, s32, s32, s32);
CONTEXT_ONLY void func_0011e610(void) {
    if (D_002C5958.b0 == 1) {
        func_0011c7c0(0, 0, 240);
        if (D_004E3440 == 0) func_0011c7a8(1, 0x3000, 0x3000, 0, 0, 120);
        else func_0011c7a8(1, 0, D_004E3438, D_004E343C, 0, 120);
        D_002C1364 = 1;
    } else {
        func_0011c7c0(1, 0, 240);
        if (D_004E3440 == 0) func_0011c7a8(0, 0x3000, 0x3000, 0, 0, 120);
        else func_0011c7a8(0, 0, D_004E3438, D_004E343C, 0, 120);
        D_002C1364 = 0;
    }
}

typedef int u128 __attribute__((mode(TI)));
/* lq/sq quadword copy with one trailing nop. */
static inline void CopyQword1(void *dst, void *src) {
    __asm__ volatile("lq $6, 0(%1)\nsq $6, 0(%0)\nnop" : : "r"(dst), "r"(src) : "$6");
}
/* 64-byte table entries at D_004E2450 (= D_004E2430 + 0x20). */

s32 func_001197e0(f32 *a, f32 *b, f32 *c) {
    s32 t;
    t = c[0] < a[0];
    if (b[0] < c[0]) { t ^= 1; if (!t) goto z1; } else if (!t) goto zero;
    t = c[1] < a[1];
    if (b[1] < c[1]) { t ^= 1; if (!t) goto z1; } else if (!t) goto zero;
    t = c[2] < a[2];
    if (b[2] < c[2]) { t ^= 1; if (!t) goto z1; } else if (!t) goto zero;
    return 1;
z1:
    return 0;
zero:
    return 0;
}

typedef f32 V4[4] __attribute__((aligned(16)));
static inline f32 vdot(f32 *a, f32 *b) {
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
void func_0011a9c8(s32, s32, V4 *);

f32 func_00119e80(s32 a0, s32 a1, f32 *n, f32 *p) {
    V4 v;
    f32 d;
    func_0011a9c8(a0, a1, &v);
    d = -vdot(n, v);
    return vdot(p, n) + d;
}

static inline f32 vdist2(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
/* 16-byte collision entries at D_003044D8, D_003044D0 of them. */
#include "data/pieces/D_003044D8.h"
typedef ColFlags_3044d8 ColFlags;
typedef ColEnt_3044d8 ColEnt;

typedef struct { f32 mn[3]; f32 mx[3]; s16 cnt; u8 pad[6]; } Qry;
typedef struct { V4 x0; V4 x10; f32 x20; u8 pad24[12]; V4 x30; } Mov;
typedef struct { u8 pad[0x20]; f32 r; f32 h; s32 flags; u8 pad2[0x54]; } ColObj;
extern f32 D_002C1250;
extern s32 D_002A62EC;
#include "data/pieces/D_002BD250.h"
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);
void func_001047c8(void);
void func_00104528(void);
void func_00104f10(s32, f32 *);
u64 func_0011b6a0(ColObj *, f32 *, s32);
void func_00116368(Qry *, s32);
void func_00117db0(Qry *);
s32 func_00119a20(s32, f32 *, f32 *, f32 *, f32 *);
s32 func_00119ad8(s32, s32, f32 *, f32 *, f32 *, f32 *);

s32 func_00118868(Mov *o) {
    V4 a, b, c;
    Qry q;
    s32 miss[512];
    ColObj obj;
    s32 hit, retry;
    s64 res;
    s32 i, n, id;
    o->x0[3] = 1.0f;
    o->x10[3] = 1.0f;
    retry = 0;
    D_002C1250 = o->x20 - 0.007999999681f;
    func_00267518(a, o->x0, o->x10);
    obj.r = o->x20;
    obj.h = 0.0f;
    func_001047c8();
loop:
    hit = 0;
    res = ((s32 (*)(ColObj *, f32 *, s32))func_0011b6a0)(&obj, a, 1);
    q.mn[0] = a[0] - o->x20;
    q.mn[2] = a[2] - o->x20;
    q.mn[1] = a[1] - o->x20;
    q.mx[2] = a[2] + o->x20;
    q.mx[0] = a[0] + o->x20;
    q.mx[1] = a[1] + o->x20;
    if (D_002A62EC == 0) func_00116368(&q, 7);
    else func_00117db0(&q);
    b[3] = 1.0f;
    n = 0;
    for (i = 0; i < (u16)q.cnt; i++) {
        id = D_002BD250[i];
        func_00104f10(id, c);
        if (func_00119a20(id, c, a, b, &D_002C1250)) {
            hit = 1;
            func_00267e90(c, c, o->x20);
            func_00267518(a, b, c);
        } else {
            miss[n++] = id;
        }
    }
    for (i = 0; i < n; i++) {
        id = miss[i];
        func_00104f10(id, c);
        if (func_00119ad8(-1, id, c, a, b, &D_002C1250)) {
            func_00267530(a, a, b);
            hit = 1;
            func_002673b8(a, a);
            func_00267e90(a, a, o->x20);
            func_00267518(a, b, a);
        }
    }
    func_002675a8(o->x30, a);
    if ((hit || res) && retry < 3) {
        retry++;
        goto loop;
    }
    func_00104528();
    return retry != 0;
}

static inline void vapply(void *d, void *m, void *v) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 16(%1)\n"
        "lqc2 $vf6, 32(%1)\n"
        "lqc2 $vf7, 48(%1)\n"
        "lqc2 $vf8, 0(%2)\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf9xyzw, $vf7xyzw, $vf8w\n"
        "sqc2 $vf9, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(m), "r"(v) : "memory");
}

#include "data/bss_004E_mixed.h"
#include "data/data_002A.h"
#include "data/data_002C.h"
#include "data/data_0030.h"
#include "data/data_0048.h"
