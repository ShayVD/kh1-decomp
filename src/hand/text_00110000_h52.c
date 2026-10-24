#include "common.h"
#include "data/bss_004D.h"
typedef struct { u16 active; u8 x2, x3; u32 cur; union { u64 d; u32 w; } press; u64 rep; } Pad52;
extern Pad52 D_002C5AD0;
typedef struct { s32 min, max; void (*fn)(s32); } Range52;
typedef struct { s32 a, b; } Pair52;
extern s32 D_004D5AF8;
extern Pair52 *D_004D5AF4; /* src/data/bss_004D.c: s32 D_004D5AF4 */
extern s32 D_002BBBA0;
extern s32 D_002C5BB8;
void func_0011d768(s32);
void func_0010f0d0(s32, s32, s32);
void func_00121ee0(void *);

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

extern s32 D_002BBDE8;
extern volatile s32 D_002BD114;
extern s32 D_002BCC24;
#include "data/pieces/D_002BBDF0.h"
#include "data/pieces/D_002BBDF4.h"
#include "data/pieces/D_002BBDF8.h"
extern volatile u32 D_004D90F0; /* src/data/bss_004D.c: volatile s32 D_004D90F0 */
extern volatile s32 D_004D90F4;
s32 func_00111798(void);
void func_001117b8(void);
void func_0010c378(void);

s32 func_00110218(void) {
    if (*(volatile u64 *)0x12001000 & 0x2000) {
        D_002BBDE8 = 1;
    } else {
        D_002BBDE8 = 0;
    }
    if (D_002BD114 == 0 && D_002BCC24 == 0) {
        D_002BBDF0++;
    }
    if (D_002BBDF4 < D_004D90F0) {
        D_002BBDF4 = D_002BBDF4 + 1;
    } else if (func_00111798() < 3) {
        if (D_002BBDF4 < D_004D90F0 + 60) {
            D_002BBDF4 = D_002BBDF4 + 1;
        } else {
            func_001117b8();
            D_002BBDF4 = 0;
        }
    } else {
        D_002BBDF4 = D_004D90F0;
    }
    D_002BBDF8++;
    D_004D90F4++;
    func_0010c378();
    return 0;
}

#include "data/types/text_00110000_h52.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBF60.h"
extern Mtx52 D_004D8E40, D_004D9100, D_004D9140, D_004D9180, D_004D91C0, D_004D8E80;
extern f32 D_004D90F8;
void func_00110ce0(void);
void sceVu0CopyMatrix(void *, void *);
void func_00110618(void *, void *, void *, void *, void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32);

void func_00110a48(f32 x) {
    func_00110ce0();
    sceVu0CopyMatrix(D_004D8E40, D_002BBE20);
    sceVu0CopyMatrix(D_004D9100, D_002BBE60);
    sceVu0CopyMatrix(D_004D9140, D_002BBEA0);
    sceVu0CopyMatrix(D_004D9180, D_002BBEE0);
    sceVu0CopyMatrix(D_004D91C0, D_002BBF20);
    sceVu0CopyMatrix(D_004D8E80, D_002BBF60);
    func_00110618(D_002BBE20, D_002BBE60, D_002BBEA0, D_002BBEE0, D_002BBF20, D_002BBF60, x,
                  0.7999999523162842f, 0.839999854564666748046875f, 2048.0f, 2048.0f, 1.0f, 16777000.0f, 1.0f,
                  400000000.0f, D_004D90F8);
}

#include "data/pieces/D_002BD118.h"
extern s32 D_002BD11C;
#include "data/pieces/D_0037A378.h"
typedef Bits_37a378 Bits52;
extern s32 D_004D9320;
extern Bits52 D_002C5958;
extern s32 D_002C1308, D_002C130C;
#include "data/pieces/D_002BBDE0.h"
extern s32 D_002BC0BC, D_002A6204;
#include "data/pieces/D_002BC070.h"
s32 func_001336a0(void);

s32 func_001140a0(void) {
    s32 *p;
    if (D_004D9320 == 0) {
        p = &D_002BD118;
        *p = 0;
        if (D_002C5958.b0 == 1) *p = 2;
        if (D_002C5958.b4 == 1) *p = 2;
        if ((*(Bits_37a378 *)&D_0037A378).b1 == 1) *p = 1;
        if ((*(Bits_37a378 *)&D_0037A378).b3 == 1) *p = 3;
        if (D_002BD11C == 1) *p = D_002BD11C;
        if (D_002C1308) *p = 4;
        if (D_002C130C) *p = 5;
        if (D_002BBDE0 == 5) *p = 7;
        if (func_001336a0()) *p = 2;
        if (*p == 0) {
            if ((*(s32 *)&D_002BC070) != 128 || D_002BC0BC || D_002A6204) D_002BD118 = 1;
        }
    }
    return D_002BD118;
}

#include "data/types/text_00110000_h52_p.h"
typedef struct { V4i52 a; s32 x10; void *x14; s32 x18; s32 x1c; V4i52 x20; V4i52 x30; V4i52 x40; } Ent52;
#include "data/pieces/D_0048C630.h"
typedef Blk32_48c630 Tpl52;
typedef struct { u8 b[0x90]; } E90_52;
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
extern V4i52 D_00472150, D_00486300;
extern E90_52 D_004DBC20[2][64];

void func_00114c18(Ent52 *o, s32 idx, s32 col) {
    s32 i;
    if (idx == -1) {
        o[0].x14 = D_0048C630.x14;
        o[1].x14 = D_0048C690.x14;
    } else {
        o[0].x14 = &D_004DBC20[0][idx];
        o[1].x14 = &D_004DBC20[1][idx];
    }
    o[0].x10 = D_0048C630.x10;
    o[0].x18 = D_0048C630.x18;
    o[0].x1c = D_0048C630.x1c;
    o[1].x10 = D_0048C690.x10;
    o[1].x18 = D_0048C690.x18;
    o[1].x1c = D_0048C690.x1c;
    o[0].x20.v[0] = D_0048C630.x20.v[0];
    o[0].x20.v[1] = D_0048C630.x20.v[1];
    o[0].x20.v[2] = D_0048C630.x20.v[2];
    o[0].x20.v[3] = D_0048C630.x20.v[3];
    o[1].x20.v[0] = D_0048C690.x20.v[0];
    o[1].x20.v[1] = D_0048C690.x20.v[1];
    o[1].x20.v[2] = D_0048C690.x20.v[2];
    o[1].x20.v[3] = D_0048C690.x20.v[3];
    for (i = 0; i < 2; i++) {
        o[i].a.v[0] = D_0048C6F0[col].v[0];
        o[i].a.v[1] = D_0048C6F0[col].v[1];
        o[i].a.v[2] = D_0048C6F0[col].v[2];
        o[i].a.v[3] = D_0048C6F0[col].v[3];
        o[i].x40.v[0] = D_00472150.v[0];
        o[i].x40.v[1] = D_00472150.v[1];
        o[i].x40.v[2] = D_00472150.v[2];
        o[i].x40.v[3] = D_00472150.v[3];
        o[i].x30.v[0] = D_00486300.v[0];
        o[i].x30.v[1] = D_00486300.v[1];
        o[i].x30.v[2] = D_00486300.v[2];
        o[i].x30.v[3] = D_00486300.v[3];
    }
}

typedef f32 V4_52[4] __attribute__((aligned(16)));

static inline void v52_sub(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void v52_cross(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4xyz, $vf5xyz\n"
        "vopmsub.xyz $vf6xyz, $vf5xyz, $vf4xyz\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void v52_normalize(f32 *d, f32 *s) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf4xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf5x\n"
        "vsub.xyzw $vf6xyzw, $vf0xyzw, $vf0xyzw\n"
        "vwaitq\n"
        "vmulq.xyz $vf6xyz, $vf4xyz, Q\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "memory");
}

static inline f32 v52_dot(f32 *a, f32 *b) {
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
void func_002675a8(void *, void *);

static inline void v52_copy(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "sq $6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "memory");
}

static inline f32 v52_dist2(f32 *a, f32 *b) {
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
void func_002675a8(void *, void *);

static inline f32 v52_dist(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
#include "data/types/text_00110000_h52_p2.h"
#include "data/bss_004D_typed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_0030.h"
#include "data/pieces/D_0046E120.h"
#include "data/pieces/D_002BCC24.h"
#include "data/pieces/D_002BD114.h"
#include "data/pieces/D_002C1308.h"
#include "data/pieces/D_00486300.h"
