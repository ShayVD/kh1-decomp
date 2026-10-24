#include "common.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
typedef int u128 __attribute__((mode(TI)));
typedef struct { s32 x0, x4, x8; } Slot12;
#include "data/types/text_00110000_h30.h"
Slot12 D_004E3818[0x28] ALIGNED(8);

extern s32 D_002BD150[];
extern s32 D_002BD160[];
s32 func_0011aa18(s32, s32, V4 *);

static inline void vsubv(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vcross(f32 *d, f32 *a, f32 *b) {
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

s32 func_0011b908(s32 a0, s32 a1, f32 *a2) {
    V4 e, f, c;
    V4 pts[4];
    s32 i;
    s32 *idx;
    s32 n = func_0011aa18(a0, a1, pts);
    if (n == 3) idx = D_002BD150;
    else idx = D_002BD160;
    for (i = 0; i < n; i++) {
        vsubv(e, pts[idx[i]], pts[i]);
        vsubv(f, a2, pts[i]);
        vcross(c, e, f);
        if (c[1] < 0.0f) return 0;
    }
    return 1;
}

static inline f32 vdist(void *a, void *b) {
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

#include "data/types/text_00110000_h30_p.h"
u8 D_004E3A58[0x828] ALIGNED(8);
#ifdef KH1_OVL_FIXUPS
#endif

extern char D_0048D278[] __attribute__((aligned(8)));
#include "data/bss_004E_mixed.h"
#include "data/bss_004F_mixed.h"
#include "data/bss_004F_typed.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_0035.h"
#include "data/data_0049.h"
#include "data/data_0048.h"
