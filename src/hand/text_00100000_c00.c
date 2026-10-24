#include "common.h"
#include "data/bss_004D.h"

f32 cosf(f32);
f32 sinf(f32);
u64 *func_00106ca8(s32);
s32 func_00106cd0(void *, s32);
void func_00106d48(s32);
extern u8 D_002A46D0[], D_002A46F0[], D_002A4710[], D_002A4730[], D_002A4750[], D_002A4770[], D_002A4790[], D_002A47B0[];
extern u8 D_002A47D0[], D_002A47F0[], D_002A4810[], D_002A4830[], D_002A4850[], D_002A4870[], D_002A4890[], D_002A48B0[], D_002A48D0[];
extern u8 D_002A5CE0[], D_002A5FE0[];
extern f32 D_002A6200;
#include "data/pieces/D_002A6210.h"
#include "data/pieces/D_002A6220.h"
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

/* needs make: uses rodata */
s32 D_004D933C ALIGNED(4);
s32 D_004D9338 ALIGNED(8);
s32 D_004D9324 ALIGNED(4);

/* D_0046A6A4 is the last entry of D_0046A688's function table (src/data/data_0046.s, a piece since
 * session 23). */
#include "data/bss_0049_mixed.h"
#include "data/bss_004D_mixed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_003F.h"
#include "data/pieces/D_003F6DF0.h"
