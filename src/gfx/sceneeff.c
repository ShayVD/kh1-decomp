/* Full-screen effects (a guess at the name), 0x00102a48-0x00104528: rings
 * of glow around the screen's centre (func_00102a48), a zoom toward a
 * point (func_00102da8), a colour pulse with cosf (func_001032b0), a
 * 25x25 warp grid (func_00103c48), and their start / stop tasks. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "platform/vu.h"
#include "platform/dma.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "data/pieces/D_002B6778.h"
#include "data/pieces/D_002A624C.h"
#include "data/bss_0049.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A6274.h"
#include "data/types/text_00100000_h1.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C10.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/pieces/D_002BC098.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002A6210.h"
#include "data/pieces/D_002A6220.h"
#include "data/pieces/D_002A6234.h"
#include "data/pieces/D_002A623C.h"
#include "data/pieces/D_002A6244.h"
#include "data/pieces/D_002A6250.h"
#include "data/pieces/D_002A62AC.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A62B4.h"
#include "data/pieces/D_002A62BC.h"
#include "data/pieces/D_002A62C0.h"
#include "data/pieces/D_002A62C4.h"
#include "data/pieces/D_002A62C8.h"
#include "data/pieces/D_002A62CC.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002A62D4.h"
#include "data/pieces/D_002A62D8.h"
#include "data/pieces/D_002A62DC.h"
#include "data/pieces/D_002A62E0.h"
#include "data/pieces/D_002A62E4.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002BBDE4.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002A6C60.h"

/* func_00102a48 (from hand/text_00100000_s7_w33.c). */
extern u64 D_002A49A0[];
extern u8 D_002A4B60[];
extern u8 D_002A4DD0[];
s32 func_0010a470(void);
void func_00106b18(void *);
#define rgba(c, a) ((u64)(c) | ((u64)(c) << 8) | ((u64)(c) << 16) | ((u64)(a) << 24) | 0x100000000)
#define xyz(x, y) ((u64)(x) | ((u64)(y) << 16) | 0x100000000)
/* func_00102a48: MATCH (hand). The two repeated colours are chained assignments (D[9] = D[15] = D[21] = D[27] = ...), written right after D[3]; every other store in index order. */
void func_00102a48(s32 c, s32 o) {
    s32 i;
    s32 *p;
    func_0010a470();
    p = ((s32 *)D_002B6778);
    for (i = 0; i < 0x9000; i++) {
        if (p[i] != 0) goto found;
    }
    func_00106b18(D_002A4DD0);
    return;
found:
    D_002A49A0[3] = rgba(c, 0x80);
    D_002A49A0[9] = D_002A49A0[15] = D_002A49A0[21] = D_002A49A0[27] = rgba(c, 0x40);
    D_002A49A0[33] = D_002A49A0[39] = D_002A49A0[45] = D_002A49A0[51] = rgba(c, 0x20);
    D_002A49A0[11] = xyz(0x6fe0 - o, 0x73e0 - o);
    D_002A49A0[13] = xyz(0x8fe0 - o, 0x8be0 - o);
    D_002A49A0[17] = xyz(0x6fe0 + o, 0x73e0 + o);
    D_002A49A0[19] = xyz(0x8fe0 + o, 0x8be0 + o);
    D_002A49A0[23] = xyz(0x6fe0 - o, 0x73e0 + o);
    D_002A49A0[25] = xyz(0x8fe0 - o, 0x8be0 + o);
    D_002A49A0[29] = xyz(0x6fe0 + o, 0x73e0 - o);
    D_002A49A0[31] = xyz(0x8fe0 + o, 0x8be0 - o);
    D_002A49A0[35] = xyz(0x6fe0, 0x73e0 - o);
    D_002A49A0[37] = xyz(0x8fe0, 0x8be0 - o);
    D_002A49A0[41] = xyz(0x6fe0 - o, 0x73e0);
    D_002A49A0[43] = xyz(0x8fe0 - o, 0x8be0);
    D_002A49A0[47] = xyz(0x6fe0, 0x73e0 + o);
    D_002A49A0[49] = xyz(0x8fe0, 0x8be0 + o);
    D_002A49A0[53] = xyz(0x6fe0 + o, 0x73e0);
    D_002A49A0[55] = xyz(0x8fe0 + o, 0x8be0);
    func_00106b18(D_002A4B60);
}
#undef rgba
#undef xyz

/* func_00102cc8 (from hand/text_00100000_h1.c). */
extern s32 D_002BC090;
extern s32 D_002BC0A4;
extern s32 D_002BC094;
extern s32 D_002BC0A0;
void func_00102cc8(s32 *x0, s32 *x1, s32 *y0, s32 *y1) {
    s32 ox = D_002BC0A0, cx = D_002BC090, oy = D_002BC0A4, cy = D_002BC094;
    s32 x = (cx + ox) * 16, y = (cy + oy) * 16;
    *x0 = x - 4096; *x1 = x + 4096; *y0 = y - 3072; *y1 = y + 3072;
}

/* func_00102d20 (from auto/text_00100000_2.c). */
void func_00102d20(s32 arg0, void *arg1, s32 *arg2, s32 *arg3) {
    PlatVu0ApplyMatrix(arg1, arg0, arg1);
    *arg2 = (s32) ((M2C_FIELD(arg1, f32 *, 0) * 16.0f) + 4096.0f);
    *arg3 = (s32) ((M2C_FIELD(arg1, f32 *, 4) * 16.0f) + 3072.0f);
}

/* func_00102da8 (from hand/text_00100000_b00.c). */
extern u8 D_002A4ED0[];
extern u8 D_002A4FC0[];
extern s32 D_002BC09C;
extern s32 D_002BC730;
extern s32 D_002BC080[4];
extern volatile u64 D_002A4F60[];
#define func_00102d20 ((void (*)(void *, f32 *, s32 *, s32 *)) func_00102d20)
void func_00102da8(s32 arg0) {
    f32 mat[16];
    f32 v[4];
    s32 sx[4];
    s32 sy[4];
    s32 x0, x1, y0, y1;
    f32 f;

    if (arg0 == 4) {
        func_00106b18(D_002A4ED0);
    }
    f = D_002BC730 * (D_002BC098 / D_002BC09C);
    if (D_002BC098 < f) {
        f = D_002BC098;
    } else {
        D_002BC730++;
    }
    D_002A4F60[3] = (u64)D_002BC080[0] | ((u64)D_002BC080[1] << 8) | ((u64)D_002BC080[2] << 16) | ((u64)D_002BC080[3] << 24) | ((u64)1 << 32);
    func_00102cc8(&x0, &x1, &y0, &y1);
    PlatVu0RotMatrixZ(mat, D_002BCAF0, f);
    v[0] = (x0 >> 4) - 256;
    v[1] = (y0 >> 4) - 192;
    func_00102d20(mat, v, &sx[0], &sy[0]);
    v[0] = (x1 >> 4) - 256;
    v[1] = (y0 >> 4) - 192;
    func_00102d20(mat, v, &sx[1], &sy[1]);
    v[0] = (x0 >> 4) - 256;
    v[1] = (y1 >> 4) - 192;
    func_00102d20(mat, v, &sx[2], &sy[2]);
    v[0] = (x1 >> 4) - 256;
    v[1] = (y1 >> 4) - 192;
    func_00102d20(mat, v, &sx[3], &sy[3]);
    D_002A4F60[5] = (u64)(sx[0] + 28664) | ((u64)(sy[0] + 29680) << 16) | ((u64)-2 << 32);
    D_002A4F60[7] = (u64)(sx[1] + 28664) | ((u64)(sy[1] + 29680) << 16) | ((u64)-2 << 32);
    D_002A4F60[9] = (u64)(sx[2] + 28664) | ((u64)(sy[2] + 29680) << 16) | ((u64)-2 << 32);
    D_002A4F60[11] = (u64)(sx[3] + 28664) | ((u64)(sy[3] + 29680) << 16) | ((u64)-2 << 32);
    func_00106b18(D_002A4FC0);
}
#undef func_00102d20

/* func_00103258 (from auto/text_00100000_3.c). */
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
void func_00103058();
void func_00103258(void) {
    func_0011ef10(0x280A2, &func_00103058);
}

/* func_00103280 (from auto/text_00100000_7.c). */
void func_00103280(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    M2C_FIELD((M2C_UNK *)&D_002A6210, f32 *, 0) = fparg0;
    M2C_FIELD((M2C_UNK *)&D_002A6210, f32 *, 4) = fparg1;
    M2C_FIELD((M2C_UNK *)&D_002A6210, f32 *, 8) = fparg2;
    M2C_FIELD((M2C_UNK *)&D_002A6210, f32 *, 0xC) = fparg3;
    M2C_FIELD((M2C_UNK *)&D_002A6220, s32 *, 0) = 0;
    M2C_FIELD((M2C_UNK *)&D_002A6220, s32 *, 4) = 0;
    M2C_FIELD((M2C_UNK *)&D_002A6220, s32 *, 8) = 0;
}

/* func_001032b0 (from hand/text_00100000_c00.c). */
f32 cosf(f32);
f32 sinf(f32);
u64 *func_00106ca8(s32);
s32 func_00106cd0(void *, s32);
void func_00106d48(s32);
extern u8 D_002A46D0[];
extern u8 D_002A4710[];
extern u8 D_002A4770[];
extern u8 D_002A4790[];
extern u8 D_002A47B0[];
extern u8 D_002A4730[];
extern u8 D_002A4750[];
extern u8 D_002A46F0[];
extern u8 D_002A47F0[];
extern u8 D_002A4850[];
extern u8 D_002A47D0[];
extern u8 D_002A4890[];
extern u8 D_002A48B0[];
extern u8 D_002A4810[];
extern u8 D_002A4870[];
extern u8 D_002A4830[];
extern u8 D_002A48D0[];
extern u8 D_002A5FE0[];
extern u8 D_002A5CE0[];
extern f32 D_002A6200;
extern f32 D_00494890;
s32 func_001032b0(void) {
    s32 rgb[3];
    s32 h;
    s32 i;
    s32 u0, v0, u1, v1;
    u64 *p;
    f32 *a;

    h = func_00106cd0(D_002A5CE0, 47);
    func_00106cd0(D_002A5FE0, 3);
    if (D_002A6210[3] != 1.0f) {
        for (i = 0; i < 3; i++) {
            D_002A6220[i] += D_002A6210[3];
            if (D_002A6220[i] > 3.1415928f) D_002A6220[i] -= 6.2831855f;
            if (D_002A6220[i] < -3.1415928f) D_002A6220[i] += 6.2831855f;
            rgb[i] = (s32)((D_002A6210[i] + (1.0f - D_002A6210[i]) * cosf(D_002A6220[i])) * 128.0f);
            if (rgb[i] < 0) rgb[i] = 0;
        }
    } else {
        rgb[2] = 128; rgb[1] = 128; rgb[0] = 128;
    }
    a = &D_00494890;
    *a += D_002A6200;
    if (*a > 3.1415928f) *a -= 6.2831855f;
    if (*a < -3.1415928f) *a += 6.2831855f;
    u0 = (s32)(cosf(*a) * 48.0f + 64.0f);
    v0 = (s32)(sinf(*a) * 48.0f + 64.0f);
    u1 = 0x2000 - u0;
    v1 = 0x1800 - v0;
    p = func_00106ca8(6);
    p[0] = 0xA400000000008001;
    p[1] = 0x5353535310;
    p[4] = u0 | ((u64)v0 << 16);
    p[2] = 0x115;
    p[3] = (u64)rgb[0] | ((u64)rgb[1] << 8) | ((u64)rgb[2] << 16) | ((u64)0x80 << 24) | ((u64)1 << 32);
    p[6] = u1 | ((u64)v0 << 16);
    p[8] = u1 | ((u64)v1 << 16);
    p[10] = u0 | ((u64)v1 << 16);
    p[5] = 0xFFFFFFFE74007000;
    p[7] = 0xFFFFFFFE74009000;
    p[9] = 0xFFFFFFFE8C009000;
    p[11] = 0xFFFFFFFE8C007000;
    func_00106cd0(D_002A46D0, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A46F0, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4710, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4730, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4750, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4770, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4790, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A47B0, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A47D0, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A47F0, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4810, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4830, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4850, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4870, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A4890, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A48B0, 2); func_00106cd0(p, 6);
    func_00106cd0(D_002A48D0, 3);
    func_00106d48(h);
    return 4;
}

/* func_001037e8 (from auto/text_00100000_3.c). */
void func_001037e8(void) {
    func_0011ef10(0x280A4, &func_001032b0);
}

/* func_00103810 (from auto/text_00100000.c). */
extern s32 D_002BC734;
extern s32 D_00494890_00103810 __asm__("D_00494890");
#define D_00494890 D_00494890_00103810
void func_00103810(void) {
    D_002BC734 = 1;
    D_00494890 = 0;
}
#undef D_00494890

/* func_00103828 (from auto/text_00100000_2.c). */
void func_00103828(void) {
    D_002BC734 = 0;
}

/* func_00103838 (from auto/text_00100000_2.c). */
extern f32 D_002BBDFC;
extern s32 D_002A6204;
s32 func_00103838(void) {
    s32 temp_f1;

    temp_f1 = (s32) ((f32) D_00494894 - D_002BBDFC);
    D_00494894 = temp_f1;
    if (temp_f1 <= 0) {
        D_002A6204 = 0xFF;
        return 4;
    }
    D_002A6204 = (s32) (255.0f - (D_00494898 * (f32) temp_f1));
    return 0;
}

/* func_001038b0 (from hand/text_00100000_h1.c). */
#define func_0011ef10 ((void (*)(s32, void *)) func_0011ef10)
void func_001038b0(s32 n) {
    func_0011ef10(0x280a2, func_00103838);
    D_00494894 = n * 2;
    if (n == 0) n = 1;
    D_00494898 = 255.0f / (f32)(n * 2);
}
#undef func_0011ef10

/* func_00103920 (from auto/text_00100000_2.c). */
s32 func_00103920(void) {
    s32 temp_f1;

    temp_f1 = (s32) ((f32) D_00494894 - D_002BBDFC);
    D_00494894 = temp_f1;
    if (temp_f1 <= 0) {
        D_002A6204 = 0;
        return 4;
    }
    D_002A6204 = (s32) (D_00494898 * (f32) temp_f1);
    return 0;
}

/* func_00103988 (from hand/text_00100000_h1.c). */
#define func_0011ef10 ((void (*)(s32, void *)) func_0011ef10)
void func_00103988(s32 n) {
    func_0011ef10(0x280a2, func_00103920);
    D_00494894 = n * 2;
    if (n == 0) n = 1;
    D_00494898 = 255.0f / (f32)(n * 2);
}
#undef func_0011ef10

/* func_001039f8 (from hand/text_00100000_h1.c). */
extern u64 D_002A6058;
extern u8 D_002A6070[];
extern s32 D_002A61F0;
s32 func_001039f8(void) {
    if (D_002A6204 != 0) {
        if (D_002A61F0 == 0) D_002A6058 = ((u64)D_002A6204 << 24) | 0x100000000;
        else D_002A6058 = ((u64)D_002A6204 << 24) | 0x100FFFFFF;
        func_00106b18(D_002A6070);
    }
    return 0;
}

/* func_00103a70 (from hand/text_00100000_h28.c). */
extern s32 D_0048CAE0[];
extern s32 D_0048CB28[];
extern s32 D_0048CB70[];
extern s32 D_0048CBB8[];
extern s32 D_004948B0[4][4];
extern s32 D_004948F0[4][4];
s32 D_00494930[4][4] ALIGNED(16);
s32 D_00494970[4][4] ALIGNED(16);
void func_00103a70(void) {
    s32 i, j, k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            D_0048CBB8[k] = D_00494930[i][j];
            D_0048CB70[k] = D_00494970[i][j];
            D_0048CB28[k] = D_004948B0[i][j];
            D_0048CAE0[k] = D_004948F0[i][j];
            k++;
        }
    }
}

/* func_00103b68 (from auto/text_00100000_9.c). */
void func_00103b68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    s32 sp[28];
    PlatVu0UnitMatrix(sp);
    PlatVu0RotMatrixX(sp, sp, M2C_FIELD(arg4, f32 *, 0));
    PlatVu0RotMatrixY(sp, sp, M2C_FIELD(arg4, f32 *, 4));
    PlatVu0RotMatrixZ(sp, sp, M2C_FIELD(arg4, f32 *, 8));
    PlatVu0ApplyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, arg2);
    PlatVu0ApplyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x50), sp, arg3);
    PlatVu0ApplyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x60), sp, arg1);
    PlatVu0CameraMatrix(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x60), &M2C_FIELD(sp, M2C_UNK *, 0x40), &M2C_FIELD(sp, M2C_UNK *, 0x50));
}

/* func_00103c48 (from hand/text_00100000_s11_w7.c). */
typedef struct { f32 x, y, z; } V12;
typedef struct { f32 u, v; } UV;
void *func_00121e28(s32, void *);
void func_00121ee0(void *);
extern u8 D_002A6110[];
extern u8 D_002A5FD0[];
extern f32 D_003732D0[];
extern volatile f32 D_00494A70;
extern f32 D_002A60C0[4];
extern f32 D_004949F0[4][4];
f32 D_004949B0[4][4] ALIGNED(16);
extern f32 D_002A60B0[4];
extern f32 D_002A6090[4];
extern f32 D_002A60A0[4];
extern f32 D_002A6080[4];
extern u8 D_0048C770[];
extern u32 *D_0048CAD4;
#define func_00103b68 ((void (*)(void *, void *, void *, void *, void *)) func_00103b68)
extern f32 D_004948F0_00103c48[4][4] __asm__("D_004948F0");
#define D_004948F0 D_004948F0_00103c48
extern f32 D_004948B0_00103c48[4][4] __asm__("D_004948B0");
#define D_004948B0 D_004948B0_00103c48
/* func_00103c48 (hand): s8 w9/w12 19w draft plus: the z loop indexes the sine table with accumulators (a += dy per row, b += dx per column, instead of j*dy and m*dx) so the dx/dy copies are cprop'd into adds and the divide temps go straight to their LO/LO1 mflo targets; the row counter reuses i; the row's table value is read before sc. */
s32 func_00103c48(void) {
    f32 mt[4][4] __attribute__((aligned(16)));
    V12 *vtx;
    UV *uv;
    u32 *pkt;
    u32 *p;
    s32 w, h, i, j, k, m;
    s32 dx, dy;
    s32 n;
    s32 a;
    u64 tag;
    f32 x, y, u, v;
    f32 *c;
    f32 sc;

    h = 25;
    func_00106b18(D_002A5FD0);
    w = 25;
    func_00106b18(D_002A6110);
    vtx = func_00121e28(7500, &vtx);
    uv = func_00121e28(5000, &uv);
    y = -192.0f;
    v = 0.0f;
    for (i = 0; i < h; i++) {
        x = -192.0f;
        u = 0.125f;
        for (m = 0; m < w; m++) {
            vtx[i * w + m].x = x;
            x += 16.0f;
            vtx[i * w + m].y = y;
            vtx[i * w + m].z = 0;
            uv[i * w + m].u = u;
            u += 0.03125f;
            uv[i * w + m].v = v;
        }
        y += 16.0f;
        v += 0.03125f;
    }
    dy = 2048 / h;
    dx = 2048 / w;
    a = 0;
    for (i = 0; i < h; i++) {
        s32 b = 0;
        for (m = 0; m < w; m++) {
            f32 t = D_003732D0[2048 + a];
            sc = D_00494A70;
            vtx[i * w + m].z = t * sc + D_003732D0[2048 + b] * sc;
            b += dx;
        }
        a += dy;
    }
    pkt = func_00121e28(0xe114, &pkt);
    p = pkt;
    *p++ = 0x10000e40;
    *p++ = 0;
    *p++ = 0x13000000;
    *p++ = 0;
    n = w * 2;
    for (m = 0; m < h - 1; m++) {
        *p++ = 0;
        *p++ = 0x6c008000 | ((n * 3 + 1) << 16);
        tag = 0x300e400000008000 | n;
        *p++ = (u32)tag;
        *p++ = tag >> 32;
        *p++ = 0x412;
        *p++ = 0;
        for (i = 0; i < n / 2; i++) {
            a = i * w + m;
            *(f32 *)p++ = vtx[a].x;
            *(f32 *)p++ = vtx[a].y;
            *(f32 *)p++ = vtx[a].z;
            *(f32 *)p++ = 1.0f;
            a++;
            *(f32 *)p++ = vtx[a].x;
            *(f32 *)p++ = vtx[a].y;
            *(f32 *)p++ = vtx[a].z;
            *(f32 *)p++ = 1.0f;
        }
        for (i = 0; i < n; i++) {
            for (k = 0; k < 4; k++) {
                *(f32 *)p++ = 128.0f;
            }
        }
        for (i = 0; i < n / 2; i++) {
            a = i * w + m;
            *(f32 *)p++ = uv[a].u;
            *(f32 *)p++ = uv[a].v;
            *(f32 *)p++ = 1.0f;
            *p++ = 0;
            a++;
            *(f32 *)p++ = uv[a].u;
            *(f32 *)p++ = uv[a].v;
            *(f32 *)p++ = 1.0f;
            *p++ = 0;
        }
        *p++ = 0x17000000;
        *p++ = 0;
    }
    *p++ = 0x70000000;
    *p++ = 0;
    p[0] = 0;
    p[1] = 0;
    PlatVu0UnitMatrix(mt);
    PlatVu0RotMatrix(D_004948B0, mt, D_002A60C0);
    PlatVu0TransMatrix(D_004948B0, D_004948B0, D_004948A0);
    func_00103b68(D_004949B0, D_002A6080, D_002A6090, D_002A60A0, D_002A60B0);
    PlatVu0ViewScreenMatrix(D_004949F0, 512.0f, 1.0f, 1.0f, 2048.0f, 2048.0f, 1.0f, 16777215.0f, 1.0f, 65536.0f);
    PlatVu0MulMatrix(D_004948F0, D_004949F0, D_004949B0);
    func_00103a70();
    D_0048CAD4 = pkt;
    PlatDmaPutVif1Qwc(0);
    PlatDmaPutVif1Tadr((u32)D_0048C770 & 0x0fffffff);
    PlatDmaPutStat(2);
    PlatFlushCache(0);
    PlatDmaPutVif1Chcr(0x145);
    func_00121ee0(vtx);
    func_00121ee0(uv);
    PlatGsSyncPath(0, 0);
    func_00121ee0(pkt);
    return 4;
}
#undef func_00103b68
#undef D_004948F0
#undef D_004948B0

/* func_00104220 (from hand/text_00100000_h1.c). */
#define func_0011ef10 ((void (*)(s32, void *)) func_0011ef10)
void func_00104220(void) {
    D_004948A0[0] = D_004948A0[1] = D_004948A0[3] = 0.0f;
    D_004948A0[2] = D_00494A74;
    func_0011ef10(0x280a4, func_00103c48);
}
#undef func_0011ef10

/* func_00104268 (from auto/text_00100000.c). */
extern s32 D_002BC738;
extern f32 D_00494A70_00104268 __asm__("D_00494A70");
#define D_00494A70 D_00494A70_00104268
void func_00104268(f32 fparg0, f32 fparg1) {
    D_002BC738 = 1;
    D_00494A70 = fparg0;
    D_00494A74 = fparg1;
}
#undef D_00494A70

/* func_00104288 (from auto/text_00100000_2.c). */
void func_00104288(void) {
    D_002BC738 = 0;
}

/* func_00104298 (from hand/text_00100000_h1.c). */
extern u64 D_002A6178;
s32 func_00104298(f32 *p) {
    p[4] -= D_002BBDFC;
    if (p[4] <= 0.0f) {
        D_002A6178 = 0x100000000;
        return 4;
    }
    D_002A6178 = ((u64)(s32)(p[5] * p[4]) << 24) | 0x100000000;
    return 0;
}

/* func_00104300 (from hand/text_00100000_h1.c). */
typedef struct { u8 pad[16]; f32 f16; f32 f20; f32 f24; } Fade;
void *func_0011f090(void *, s32, void *);
void func_00104300(s32 n) {
    Fade *o;
    D_002A6208 = 1;
    o = func_0011f090(D_002BC720, 0, func_00104298);
    if (o) {
        o->f16 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

/* func_00104388 (from auto/text_00100000_14.c). */
u32 func_00104388(void *arg0) {
  f32 temp_f2;
  temp_f2 = (*((f32 *) (((s8 *) arg0) + 0x10))) + D_002BBDFC;
  *((f32 *) (((s8 *) arg0) + 0x10)) = temp_f2;
  if ((*((f32 *) (((s8 *) arg0) + 0x18))) <= temp_f2)
  {
    D_002A6208 = 0;
    D_002A6178 = 0xC000;
    D_002A6178 = D_002A6178 << 0x11;
    return 4;
  }
  D_002A6178 = (((s64) ((s32) ((*((f32 *) (((s8 *) arg0) + 0x14))) * temp_f2))) << 0x18) | (((s64) 0x8000) << 0x11);
  return 0;
}

/* func_001043f8 (from hand/text_00100000_h1.c). */
typedef struct { u8 pad[16]; s32 w16; f32 f20; f32 f24; } Fade2;
void func_001043f8(s32 n) {
    Fade2 *o = func_0011f090(D_002BC720, 0, func_00104388);
    if (o) {
        D_002A6208 = 1;
        o->w16 = 0;
        o->f24 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

/* func_00104480 (from auto/text_00100000_2.c). */
void func_00104480(s32 arg0, void *arg1) {
    PlatVu0UnitMatrix(arg1);
    M2C_FIELD(arg1, s32 *, 0x60) = arg0;
}

/* func_001044b8 (from auto/text_00100000_2.c). */
void func_001044b8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x60) = arg0;
}

/* func_001044c0 (from hand/text_00100000_h1.c). */
typedef struct { u8 m[64]; u8 v64[16]; u8 v80[16]; s32 w96; } Xf;
void func_001044c0(Xf *p) {
    PlatVu0RotMatrix(p, D_002BCAF0, p->v64);
    PlatVu0TransMatrix(p, p, p->v80);
    if (p->w96 != -1) PlatVu0MulMatrix(p, (void *)p->w96, p);
}

