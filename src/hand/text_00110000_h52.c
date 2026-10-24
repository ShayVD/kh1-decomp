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

#include "data/types/text_00110000_h52.h"

#include "data/types/text_00110000_h52_p.h"
#include "data/pieces/D_0048C630.h"
typedef Blk32_48c630 Tpl52;

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
