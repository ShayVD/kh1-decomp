#include "common.h"
#include "data/bss_004F.h"

#include "data/types/text_00110000_h53_p.h"

static inline f32 w53_dot(void *a, void *b) {
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

static inline void w53_scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}

static inline void w53_add(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

#include "data/types/text_00110000_h53_p2.h"
float cosf(float);
char D_004F7150[0x4][32] ALIGNED(16);
extern char *D_002C6460[];
extern u8 D_00491A18[];

static inline s32 w53_toupper(s32 c) {
    return ((D_00491A18 + 1)[c] & 2) ? c - 32 : c;
}
void func_002675a8(V53 *, V53 *);
float cosf(float);

#include "data/types/text_00110000_h53.h"
extern f32 D_004F7650, D_004F77E0;

#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))

/* needs make: uses rodata */
void func_002675a8(V53 *, V53 *);

#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
extern f32 D_004F77E0;

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
/* D_0046A6A8 stays extern: the dktitle.x overlay also writes it (two %lo fields), so it is shared. */
extern u8 D_0048D2C8[];
extern u8 D_0048D2D0[];
extern u8 D_0048D2D8[];
extern u8 D_0048D2E0[];
extern u8 D_0048D2E8[];
extern u8 D_0048D2F0[];
extern u8 D_0048D2F8[];
extern u8 D_0048D300[];
extern u8 D_0048D308[];
extern u8 D_0048D310[];
extern u8 D_0048D318[];
char *D_002C6460[0xb] ALIGNED(16) = {
    (void *)D_0048D318, (void *)D_0048D310, (void *)D_0048D308, (void *)D_0048D300,
    (void *)D_0048D2F8, (void *)D_0048D2F0, (void *)D_0048D2E8, (void *)D_0048D2E0,
    (void *)D_0048D2D8, (void *)D_0048D2D0, (void *)D_0048D2C8,
};
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_002E.h"
#include "data/data_0049.h"
#include "data/data_0048.h"
