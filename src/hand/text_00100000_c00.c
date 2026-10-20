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
extern f32 D_002A6210[4];
extern f32 D_002A6220[3];
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

typedef struct { s16 h0; s16 h2; } Tsk;

extern volatile u32 D_002BBDE0;
extern volatile s32 D_002BBE08;
extern s32 D_002B6774;
extern s32 D_004D9334;
extern u32 D_002BD118;
s32 D_004D933C ALIGNED(4);
s32 D_004D9338 ALIGNED(8);
extern s32 D_004D9340;
extern volatile s32 D_004D9364;
extern s32 D_002BBE0C;
extern f32 D_002BBDFC;
extern volatile s32 D_002BD114;
extern volatile s32 D_002C5AD0[3];
extern s32 D_004D9348, D_004D9344, D_004D9354, D_004D934C, D_004D9350, D_004D9358, D_004D935C, D_004D9360;
extern volatile s32 D_002C1308;
extern s32 D_002C130C;
s32 D_004D9324 ALIGNED(4);
extern u32 D_004D9330;
extern s32 D_002C5AD8;
extern s32 D_002C596C;
extern s32 (*D_0046A6A4)(void);
extern s32 D_002B6478;
extern s32 D_003F34A4, D_003F6E28, D_002BD110, D_003F76B4;

void func_00113df8(s32);
void func_00113e28(s32);
void func_00113a00(void);
void func_00113af8(s32);
void func_001220d0(void);
void func_0010fd40(void);
s32 func_00109658(void);
s32 func_0010f918(void);
void func_00113ab0(s32);
void func_001104e0(void);
void func_00114220(void);
void func_0011c778(void);
void func_0011c798(void);
void func_00114200(void);
void func_00113f60(void);
void func_00114028(void);
Tsk *func_0011ef10(s32, void (*)(void));
void func_00114250(void);
void func_00157668(void);
void func_0020d6c8(s32);
void func_0022daa0(s32);
void func_0022e368(s32);
void func_00111510(void);
void func_002295a0(s32, s32);
void func_002297a0(s32);
void func_001dcd98(s32);
void func_00114210(void);

s32 func_00114280(void) {
    u32 s;
    s32 save;
    f32 fsave;

    s = D_002BBDE0;
    if (s != 3 && s != 5) {
        return 1;
    }
    if (D_002B6774 != 0) {
        return 1;
    }
    if (D_004D9334 != 0) {
        return 1;
    }
    switch (D_002BD118) {
    case 1:
    case 2:
        D_004D933C = 1;
        D_004D9338 = 0;
        D_004D9340 = 0;
        D_004D9364 = 0;
        save = D_002BBE0C;
        fsave = D_002BBDFC;
        do {
            if (D_004D9364 == 0 && (D_002C5AD0[2] & 8)) {
                D_002BBE0C = 0;
                D_004D9338 ^= 1;
                D_004D9364 = 1;
                D_004D9348 = 0;
                D_004D9344 = 0;
                switch (D_004D9340) {
                case 0:
                    if (D_002BD118 == 2) {
                        func_00113df8(1);
                    } else {
                        func_00113e28(1);
                    }
                    D_004D9340 = 1;
                    D_004D934C = 128;
                    D_004D9350 = 128;
                    D_004D9354 = 255;
                    D_004D9358 = 0;
                    D_004D935C = 0;
                    D_004D9360 = 0;
                    break;
                case 1:
                    D_004D9340 = 2;
                    func_00113a00();
                    break;
                }
                D_002BD114 ^= 1;
            }
            if (D_004D9340 != 0) {
                func_00113af8(D_004D9338);
                D_002BD114 = 1;
                func_001220d0();
                func_0010fd40();
                if (func_00109658() == 0) {
                    goto end;
                }
                if (func_0010f918()) {
                    func_00113ab0(D_004D9338);
                }
                func_001104e0();
            } else {
                D_004D933C = 0;
                D_002BD114 = 0;
                D_002BBE0C = save;
                D_002BBDFC = fsave;
            }
        } while (D_004D933C != 0);
        break;
    case 4:
        if (D_002C1308 != 0) {
            func_00114220();
            D_004D9324 = D_002C1308;
            func_0011c778();
        }
        break;
    case 5:
        if (D_002C130C != 0) {
            func_00114220();
            func_0011c798();
        }
        break;
    case 3:
    default:
        if (D_004D9330 == 0 && (D_002C5AD8 & 8)) {
            func_00114220();
        }
        break;
    }
    switch (D_004D9330) {
    case 0:
        D_002C596C = 0;
        break;
    case 1:
        func_00114200();
        func_0011ef10(0x2e644, func_00113f60)->h2 = 1;
        D_004D9330 = 2;
        break;
    case 2:
        func_00114200();
        break;
    case 3:
        func_00114200();
        func_00113df8(1);
        switch (D_002BD118) {
        case 0:
            func_00114250();
            D_002B6478 = D_0046A6A4();
            func_00157668();
            func_0020d6c8(1);
            break;
        case 3:
            func_00114250();
            func_0022daa0(1);
            break;
        case 7:
            func_00114250();
            func_0022e368(1);
            break;
        case 4:
            func_00114250();
            func_00111510();
            func_00157668();
            func_002295a0(1, D_004D9324);
            break;
        case 5:
            func_00114250();
            func_00157668();
            func_002297a0(1);
            break;
        }
        D_004D9330 = 4;
        break;
    case 4:
        func_00114200();
        if (D_003F34A4 == 0) {
            if (D_003F6E28 != 0) {
                D_002BD110 = 1;
            }
            if (D_002BD118 == 3) {
                func_001dcd98(D_003F76B4);
            }
            func_00113df8(0);
            D_004D9330 = 5;
        }
        break;
    case 5:
        D_002BBE0C = 1;
        func_0011ef10(0x2e645, func_00114028)->h2 = -1;
        func_00114210();
        D_004D9330 = 6;
        break;
    case 6:
        func_00114210();
        break;
    default:
        func_00114210();
        break;
    }
end:
    return D_002BBE08;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_0024e078();
s32 (*D_0046A6A4)(void) ALIGNED(4) = (void *)func_0024e078;
#include "data/bss_0049_mixed.h"
#include "data/bss_004D_mixed.h"
#include "data/data_002A.h"
