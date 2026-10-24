/* worker c06: nostrict, no delay-slot filling. */
#include "common.h"

typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern PppMtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern PppMtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
#include "data/pieces/D_003701F0.h"
void sceVu0UnitMatrix(PppMtx);
void func_002676c0(PppMtx, PppMtx, f32);
void func_00267518(f32 *, f32 *, f32 *);

typedef struct {
    f32 pos[4];
    u8 pad10[0x1C];
    f32 rot;      /* +0x2C */
    u8 pad30[8];
    f32 sx, sy;   /* +0x38 */
} KeyD020;

typedef struct {
    u8 pad[0xCC];
    u8 mode;
} ObjD020;

void func_0019d020(PppMtx a, PppMtx m, ObjD020 *o, PppMtx c, KeyD020 *k, PppMtx b, PppMtx out, u8 flag) {
    sceVu0UnitMatrix(m);
    m[0][0] = k->sx * D_003701F0[0];
    m[1][1] = k->sy * D_003701F0[1];
    m[2][2] = k->sx * D_003701F0[0];
    if (k->rot != 0.0f) {
        func_002676c0(m, m, k->rot * 3.141592562f / 180.0f);
    }
    func_00267518(m[3], m[3], k->pos);
    switch (o->mode) {
    case 0:
        __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 16(%0)\n"
        "lqc2 $vf3, 32(%0)\n"
        "lqc2 $vf4, 48(%0)\n"
        "lqc2 $vf9, 0(%1)\n"
        "lqc2 $vf10, 16(%1)\n"
        "lqc2 $vf11, 32(%1)\n"
        "lqc2 $vf12, 48(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "lqc2 $vf6, 16(%2)\n"
        "lqc2 $vf7, 32(%2)\n"
        "lqc2 $vf8, 48(%2)\n"
        "vmulax.xyzw ACC, $vf9, $vf4x\n"
        "vmadday.xyzw ACC, $vf10, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf12, $vf4w\n"
        "beql $0, %4, 1f\n"
        "sqc2 $vf1, 0(%3)\n"
        "sqc2 $vf2, 16(%3)\n"
        "sqc2 $vf3, 32(%3)\n"
        "sqc2 $vf4, 48(%3)\n"
        "1:\n"
        "vmulax.xyzw ACC, $vf5, $vf1x\n"
        "vmadday.xyzw ACC, $vf6, $vf1y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf8, $vf1w\n"
        "vmulax.xyzw ACC, $vf5, $vf2x\n"
        "vmadday.xyzw ACC, $vf6, $vf2y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf2z\n"
        "vmaddw.xyzw $vf2, $vf8, $vf2w\n"
        "vmulax.xyzw ACC, $vf5, $vf3x\n"
        "vmadday.xyzw ACC, $vf6, $vf3y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf3z\n"
        "vmaddw.xyzw $vf3, $vf8, $vf3w\n"
        "vmulax.xyzw ACC, $vf5, $vf4x\n"
        "vmadday.xyzw ACC, $vf6, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf8, $vf4w\n"
        "sqc2 $vf1, 0(%0)\n"
        "sqc2 $vf2, 16(%0)\n"
        "sqc2 $vf3, 32(%0)\n"
        "sqc2 $vf4, 48(%0)\n"
        : : "r"(m), "r"(a), "r"(D_00616040), "r"(out), "r"(flag) : "memory");
        break;
    case 1:
        __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 16(%0)\n"
        "lqc2 $vf3, 32(%0)\n"
        "lqc2 $vf4, 48(%0)\n"
        "lqc2 $vf9, 0(%1)\n"
        "lqc2 $vf10, 16(%1)\n"
        "lqc2 $vf11, 32(%1)\n"
        "lqc2 $vf12, 48(%1)\n"
        "lqc2 $vf13, 0(%2)\n"
        "lqc2 $vf14, 16(%2)\n"
        "lqc2 $vf15, 32(%2)\n"
        "lqc2 $vf16, 48(%2)\n"
        "lqc2 $vf17, 0(%3)\n"
        "lqc2 $vf18, 16(%3)\n"
        "lqc2 $vf19, 32(%3)\n"
        "lqc2 $vf20, 48(%3)\n"
        "lqc2 $vf5, 0(%4)\n"
        "lqc2 $vf6, 16(%4)\n"
        "lqc2 $vf7, 32(%4)\n"
        "lqc2 $vf8, 48(%4)\n"
        "vmulax.xyzw ACC, $vf9, $vf17x\n"
        "vmadday.xyzw ACC, $vf10, $vf17y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf17z\n"
        "vmaddw.xyzw $vf17, $vf12, $vf17w\n"
        "vmulax.xyzw ACC, $vf9, $vf18x\n"
        "vmadday.xyzw ACC, $vf10, $vf18y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf18z\n"
        "vmaddw.xyzw $vf18, $vf12, $vf18w\n"
        "vmulax.xyzw ACC, $vf9, $vf19x\n"
        "vmadday.xyzw ACC, $vf10, $vf19y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf19z\n"
        "vmaddw.xyzw $vf19, $vf12, $vf19w\n"
        "vmulax.xyzw ACC, $vf9, $vf20x\n"
        "vmadday.xyzw ACC, $vf10, $vf20y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf20z\n"
        "vmaddw.xyzw $vf20, $vf12, $vf20w\n"
        "vmulax.xyzw ACC, $vf13, $vf17x\n"
        "vmadday.xyzw ACC, $vf14, $vf17y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf17z\n"
        "vmaddw.xyzw $vf9, $vf16, $vf17w\n"
        "vmulax.xyzw ACC, $vf13, $vf18x\n"
        "vmadday.xyzw ACC, $vf14, $vf18y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf18z\n"
        "vmaddw.xyzw $vf10, $vf16, $vf18w\n"
        "vmulax.xyzw ACC, $vf13, $vf19x\n"
        "vmadday.xyzw ACC, $vf14, $vf19y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf19z\n"
        "vmaddw.xyzw $vf11, $vf16, $vf19w\n"
        "vmulax.xyzw ACC, $vf13, $vf20x\n"
        "vmadday.xyzw ACC, $vf14, $vf20y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf20z\n"
        "vmaddw.xyzw $vf12, $vf16, $vf20w\n"
        "vmulax.xyzw ACC, $vf9, $vf4x\n"
        "vmadday.xyzw ACC, $vf10, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf12, $vf4w\n"
        "beql $0, %6, 1f\n"
        "sqc2 $vf1, 0(%5)\n"
        "sqc2 $vf2, 16(%5)\n"
        "sqc2 $vf3, 32(%5)\n"
        "sqc2 $vf4, 48(%5)\n"
        "1:\n"
        "vmulax.xyzw ACC, $vf5, $vf1x\n"
        "vmadday.xyzw ACC, $vf6, $vf1y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf8, $vf1w\n"
        "vmulax.xyzw ACC, $vf5, $vf2x\n"
        "vmadday.xyzw ACC, $vf6, $vf2y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf2z\n"
        "vmaddw.xyzw $vf2, $vf8, $vf2w\n"
        "vmulax.xyzw ACC, $vf5, $vf3x\n"
        "vmadday.xyzw ACC, $vf6, $vf3y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf3z\n"
        "vmaddw.xyzw $vf3, $vf8, $vf3w\n"
        "vmulax.xyzw ACC, $vf5, $vf4x\n"
        "vmadday.xyzw ACC, $vf6, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf8, $vf4w\n"
        "sqc2 $vf1, 0(%0)\n"
        "sqc2 $vf2, 16(%0)\n"
        "sqc2 $vf3, 32(%0)\n"
        "sqc2 $vf4, 48(%0)\n"
        : : "r"(m), "r"(b), "r"(D_00615EB0), "r"(D_00615E68->m), "r"(D_00616040), "r"(out), "r"(flag) : "memory");
        break;
    case 2:
        __asm__ volatile(
        "lqc2 $vf1, 0(%0)\n"
        "lqc2 $vf2, 16(%0)\n"
        "lqc2 $vf3, 32(%0)\n"
        "lqc2 $vf4, 48(%0)\n"
        "lqc2 $vf9, 0(%1)\n"
        "lqc2 $vf10, 16(%1)\n"
        "lqc2 $vf11, 32(%1)\n"
        "lqc2 $vf12, 48(%1)\n"
        "lqc2 $vf13, 0(%2)\n"
        "lqc2 $vf14, 16(%2)\n"
        "lqc2 $vf15, 32(%2)\n"
        "lqc2 $vf16, 48(%2)\n"
        "lqc2 $vf17, 0(%3)\n"
        "lqc2 $vf18, 16(%3)\n"
        "lqc2 $vf19, 32(%3)\n"
        "lqc2 $vf20, 48(%3)\n"
        "lqc2 $vf5, 0(%4)\n"
        "lqc2 $vf6, 16(%4)\n"
        "lqc2 $vf7, 32(%4)\n"
        "lqc2 $vf8, 48(%4)\n"
        "vmulax.xyzw ACC, $vf17, $vf9x\n"
        "vmadday.xyzw ACC, $vf18, $vf9y\n"
        "vmaddaz.xyzw ACC, $vf19, $vf9z\n"
        "vmaddw.xyzw $vf9, $vf20, $vf9w\n"
        "vmulax.xyzw ACC, $vf17, $vf10x\n"
        "vmadday.xyzw ACC, $vf18, $vf10y\n"
        "vmaddaz.xyzw ACC, $vf19, $vf10z\n"
        "vmaddw.xyzw $vf10, $vf20, $vf10w\n"
        "vmulax.xyzw ACC, $vf17, $vf11x\n"
        "vmadday.xyzw ACC, $vf18, $vf11y\n"
        "vmaddaz.xyzw ACC, $vf19, $vf11z\n"
        "vmaddw.xyzw $vf11, $vf20, $vf11w\n"
        "vmulax.xyzw ACC, $vf17, $vf12x\n"
        "vmadday.xyzw ACC, $vf18, $vf12y\n"
        "vmaddaz.xyzw ACC, $vf19, $vf12z\n"
        "vmaddw.xyzw $vf12, $vf20, $vf12w\n"
        "vmulax.xyzw ACC, $vf13, $vf9x\n"
        "vmadday.xyzw ACC, $vf14, $vf9y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf9z\n"
        "vmaddw.xyzw $vf9, $vf16, $vf9w\n"
        "vmulax.xyzw ACC, $vf13, $vf10x\n"
        "vmadday.xyzw ACC, $vf14, $vf10y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf10z\n"
        "vmaddw.xyzw $vf10, $vf16, $vf10w\n"
        "vmulax.xyzw ACC, $vf13, $vf11x\n"
        "vmadday.xyzw ACC, $vf14, $vf11y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf11z\n"
        "vmaddw.xyzw $vf11, $vf16, $vf11w\n"
        "vmulax.xyzw ACC, $vf13, $vf12x\n"
        "vmadday.xyzw ACC, $vf14, $vf12y\n"
        "vmaddaz.xyzw ACC, $vf15, $vf12z\n"
        "vmaddw.xyzw $vf12, $vf16, $vf12w\n"
        "vmulax.xyzw ACC, $vf9, $vf4x\n"
        "vmadday.xyzw ACC, $vf10, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf11, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf12, $vf4w\n"
        "beql $0, %6, 1f\n"
        "sqc2 $vf1, 0(%5)\n"
        "sqc2 $vf2, 16(%5)\n"
        "sqc2 $vf3, 32(%5)\n"
        "sqc2 $vf4, 48(%5)\n"
        "1:\n"
        "vmulax.xyzw ACC, $vf5, $vf1x\n"
        "vmadday.xyzw ACC, $vf6, $vf1y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf8, $vf1w\n"
        "vmulax.xyzw ACC, $vf5, $vf2x\n"
        "vmadday.xyzw ACC, $vf6, $vf2y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf2z\n"
        "vmaddw.xyzw $vf2, $vf8, $vf2w\n"
        "vmulax.xyzw ACC, $vf5, $vf3x\n"
        "vmadday.xyzw ACC, $vf6, $vf3y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf3z\n"
        "vmaddw.xyzw $vf3, $vf8, $vf3w\n"
        "vmulax.xyzw ACC, $vf5, $vf4x\n"
        "vmadday.xyzw ACC, $vf6, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf7, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf8, $vf4w\n"
        "sqc2 $vf1, 0(%0)\n"
        "sqc2 $vf2, 16(%0)\n"
        "sqc2 $vf3, 32(%0)\n"
        "sqc2 $vf4, 48(%0)\n"
        : : "r"(m), "r"(b), "r"(D_00615EB0), "r"(c), "r"(D_00616040), "r"(out), "r"(flag) : "memory");
        break;
    }
}

typedef f32 Mtx2830[4][4] __attribute__((aligned(16)));
void func_00267518(f32 *, f32 *, f32 *);

static inline f32 vlen3_2830(f32 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 %0, $vf10\n"
        : "=r"(r) : "r"(v) : "memory");
    return r;
}
