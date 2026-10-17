#include "common.h"
typedef struct { u8 pad[8]; s32 x8; } F8;
extern F8 *D_00425BC8;
typedef struct { u8 pad[0xb0]; s32 xb0; s32 xb4; u8 p1[6]; s16 xbe; s16 xc0; s16 xc2; s16 xc4; s16 xc6; u8 p2[0xd2-0xc8]; s16 xd2; u8 p3[4]; s16 xd8; s16 xda; } O;
extern s32 D_006469B0, D_006469B4;
extern s32 D_003F7308[];
extern u8 D_003F7210[], D_003F47A8[];
s32 func_001f42b8(void *);
void func_001f3708(void *, s32);
void func_0011d768(s32);
s32 func_00219428(void);
void func_00219418(s32);
void func_0020bc48(s32, s32, s32);
void func_001fd858(void *);
s32 func_001fe570(void *);
s32 func_001fd518(void *);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
s32 func_001fa808(void *, s32, s32, s32, s32);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_00209820(void *, s32, s32, s32, void *);


void func_0022c960(O *a0) {
    s32 i, y; s32 *p;
    if (func_001f42b8(a0) != 0) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            if ((D_006469B4 = D_006469B0, func_00219428()) != 0) {
                D_006469B0--;
            } else {
                D_006469B0 = 0;
            }
        } else {
            func_0020bc48(8, (a0->xb0 + a0->xc2 + a0->xbe - 0x7000) >> 4,
                          (a0->xb4 + a0->xc4 * a0->xd2 / 16 + a0->xc0 - 0x7400) >> 4);
            func_001fd858(a0);
            if (func_001fe570(a0) != 0) {
                func_001f3708(a0, 11);
                func_00219418(func_001fd518(a0));
                D_006469B4 = D_006469B0;
                D_006469B0++;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80C2726E, 0x80C2726E);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80C2726E, 0x80C2726E);
    func_001fa808(a0, 161, 88, 15, 0x80E6E6E6);
    y = 166;
    p = D_003F7308;
    for (i = 0; i < 3; i++) {
        func_001f9438(a0, 0, 211, y, *p++, 15, 0x80E6E6E6);
        y += 28;
    }
    func_00209820(a0, 2, 2, 111, D_003F47A8);
}

void func_001fdfd0(void *);
s32 func_001fd538(void *);
void func_002193e0(s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);

void func_0022cba8(O *a0) {
    s32 v;
    if (func_001f42b8(a0) != 0) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0--;
        } else {
            func_001fdfd0(a0);
            func_0020bc48(8, (a0->xb0 + a0->xc2 + (a0->xbe - 0x7000) + a0->xda * 202 - a0->xc6) >> 4,
                          (a0->xb4 + a0->xc4 * a0->xd2 / 16 + a0->xc0 - 0x7400) >> 4);
            if (func_001fe570(a0) != 0) {
                func_001f3708(a0, 11);
                func_002193e0(func_001fd538(a0));
                D_006469B4 = D_006469B0;
                D_006469B0++;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80C2726E, 0x80C2726E);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80C2726E, 0x80C2726E);
    func_001fa808(a0, 161, 449, 15, 0x80E6E6E6);
    v = func_001fd538(a0);
    func_002078f0(a0, v == 0, 2, 2, 85, 174, 140, 155, 447);
    func_002078f0(a0, v == 1, 2, 2, 231, 174, 196, 329, 448);
}

typedef struct { u8 pad0[0xA0]; f32 xa0; } Ob;
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
s16 *func_0011ef10(s32, void *);
s32 func_0022d498(void);
extern u8 D_003F74D0[], D_003F74A0[], D_003F73B0[], D_003F73E0[], D_003F7410[], D_003F7440[], D_003F7470[];
extern s32 D_003F34A4;
extern s32 D_006469B8[];

void func_0022d4d8(s32 arg0) {
    Ob *o[7];
    s32 i;
    func_001f3110();
    o[0] = func_001f31a8(D_003F74D0, 48);
    if (o[0] != NULL) {
        func_001f3d58(o[0], 0);
        o[1] = func_001f31a8(D_003F74A0, 46);
        if (o[1] != NULL) {
            func_001f3e90(o[0], o[1]);
            func_001f3e20(o[1], o[0]);
            func_001f3d58(o[1], 47);
            o[2] = func_001f31a8(D_003F73B0, 48);
            if (o[2] != NULL) {
                func_001f3e90(o[1], o[2]);
                func_001f3e20(o[2], o[1]);
                func_001f3d58(o[2], 49);
                o[3] = func_001f31a8(D_003F73E0, 48);
                if (o[3] != NULL) {
                    func_001f3e90(o[2], o[3]);
                    func_001f3e20(o[3], o[2]);
                    func_001f3d58(o[3], 49);
                    o[3]->xa0 = 1.0f;
                    o[4] = func_001f31a8(D_003F7410, 48);
                    if (o[4] != NULL) {
                        func_001f3e90(o[3], o[4]);
                        func_001f3e20(o[4], o[3]);
                        func_001f3d58(o[4], 49);
                        o[4]->xa0 = 2.0f;
                        o[5] = func_001f31a8(D_003F7440, 48);
                        if (o[5] != NULL) {
                            func_001f3e90(o[4], o[5]);
                            func_001f3e20(o[5], o[4]);
                            func_001f3d58(o[5], 49);
                            o[5]->xa0 = 3.0f;
                            o[6] = func_001f31a8(D_003F7470, 48);
                            if (o[6] != NULL) {
                                func_001f3e90(o[5], o[6]);
                                func_001f3e20(o[6], o[5]);
                                func_001f3d58(o[6], 49);
                                o[6]->xa0 = 4.0f;
                                func_001f3dc0(o[0]);
                            }
                        }
                    }
                }
            }
        }
    }
    D_003F34A4 = 1;
    for (i = 5; i >= 0; i--) D_006469B8[i] = 0;
    func_0011ef10(0x2BFE9, func_0022d498)[1] = arg0;
}

typedef struct { u8 p0[4]; u8 r[0x48e - 4]; u8 sel[0x499 - 0x48e]; u8 cnt[1]; } Base4BE8;
extern Base4BE8 *D_00304BE8;
extern u32 D_003E3D6C;
extern u32 D_00646A24;
extern s32 D_00647630;
extern u8 *D_00647634;
extern s32 D_00646A30[];
extern s32 D_00646E30[];
extern s32 D_00647230[];
s32 func_001ee728(s32);
s32 func_001ef0c0(s32);
void func_0020f290(s32 *, s32, s32);

void func_0022f818(void) {
    u32 sel = D_00646A24;
    s32 i, n, k, c;
    if (sel == -1) {
        D_00647630 = 0;
        return;
    }
    if (sel < D_003E3D6C) {
        D_00647634 = &D_00304BE8->r[D_00304BE8->sel[sel] * 116];
        n = D_00647634[0x21];
        D_00647630 = 0;
        for (i = 0; i < n; i++) {
            k = *(u8 *)(i + (s32)D_00647634 + 0x22);
            if (k != 0 && func_001ee728(k) != 0) {
                D_00646A30[D_00647630] = k;
                D_00646E30[D_00647630] = 1;
                D_00647230[D_00647630++] = i;
            }
        }
        return;
    }
    D_00647630 = 0;
    for (i = 1; i < 256; i++) {
        if (func_001ef0c0(i) != 0 && func_001ee728(i) != 0) {
            c = D_00647630; D_00647630 = c + 1; D_00646A30[c] = i;
        }
    }
    if (D_00647630 == 0) return;
    func_0020f290(D_00646A30, 0, D_00647630 - 1);
    for (i = 0; i < D_00647630; i++) {
        k = D_00646A30[i];
        D_00646E30[i] = func_001ef0c0(k);
        D_00647230[i] = k;
    }
}

extern s32 D_003F7A64;
extern s32 D_003F7A68;
extern s32 D_00646A00, D_00646A04;
extern s32 *D_00646A08;
extern s32 *D_00646A0C;
extern void *D_00646A10;
extern s32 D_00646A28;
extern s32 D_00647640, D_00647644;
extern u8 D_003F78B0[], D_003F79E0[], D_003F7A10[], D_003F7A40[];
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001ef830(void);
void func_0022eee0(s32);
void func_0022fc88(s32);
void func_0011d768(s32);
void func_0020bb90(s32, s32);
void func_0020bda8(s32);
s32 func_001eeb20(void);
s16 *func_0011ef10(s32, void *);
s32 func_002316f8(void);

void func_00231740(s32 mode, s32 *p, s32 a2, s32 a3) {
    if (D_003F7A64 != 0) return;
    func_001f3110();
    D_003F7A64 = 1;
    D_003F7A68 = 1;
    func_001ef830();
    func_0022eee0(-1);
    func_0022fc88(-1);
    D_00646A00 = a2;
    D_00646A04 = a3;
    D_00646A28 = 1;
    D_00647644 = 0;
    func_0011d768(16);
    func_0020bb90(544, -32);
    func_0020bda8(16);
    switch (mode) {
    case 0:
        D_00646A08 = p;
        D_00646A0C = p + 1;
        D_00646A10 = func_001f31a8(D_003F78B0, 6);
        break;
    case 1:
        D_00646A10 = func_001f31a8(D_003F79E0, 6);
        break;
    case 2:
        D_00646A08 = p;
        D_00646A0C = p + 1;
        D_00647640 = func_001eeb20();
        D_00646A10 = func_001f31a8(D_003F7A10, 6);
        break;
    case 3:
        D_00647640 = func_001eeb20();
        D_00646A10 = func_001f31a8(D_003F7A40, 6);
        break;
    }
    func_0011ef10(0x2BF84, func_002316f8);
}
