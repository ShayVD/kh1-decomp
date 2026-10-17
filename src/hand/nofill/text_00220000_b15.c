#include "common.h"
typedef struct { u8 pad[4]; u32 x4; s32 x8; u8 padc[4]; u32 x10; } Cfg;
typedef struct { u8 pad[0x24]; f32 x24[3]; } Ob3;
extern Cfg *D_00425BC8;
extern s32 D_003F76B4;
extern s32 D_003F7500[];
s32 func_001f42b8(void *);
void func_001f3840(void *);
void func_0011d768(s32);
void func_0020be10(s32);
void func_001fd648(void *, s32);
void func_001fd858(void *);
void func_0020bd18(void *, s32);
s32 func_001fd518(void *);
s32 func_001fe570(void *);
s32 func_001eddc0(s32, s32, f32);
void func_00200648(void *, s32, s32, s32, s32, s32 *);
void func_002066b0(void *, s32, s32, s32, s32, s32);
extern s32 D_003F76B8;
extern s32 D_003F7598[];
/* func_001f9438 is left undeclared on purpose: the implicit declaration gives the original argument load order. */

void func_0022d730(Ob3 *a) {
    s32 c[5];
    s32 i, y, h;

    f32 f;
    if (func_001f42b8(a)) {
        u32 fl = D_00425BC8->x8;
        if (fl & 8) {
            D_003F76B4 = 0;
            func_001f3840(a);
            func_0011d768(3);
            func_0020be10(16);
        } else if (fl & 0x4000) {
            D_003F76B4 = 0;
            func_001fd648(a, 0);
            func_0011d768(3);
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            D_003F76B4 = func_001fd518(a);
            if (func_001fe570(a)) {
                func_001f3840(a);
                func_0020be10(16);
            }
        }
    }
    y = 183;
    for (i = 0; i < 3; i++) {
        if (D_003F76B4 == i) {
            a->x24[i] = 1.0f;
        } else {
            a->x24[i] = a->x24[i] - 0.08;
            if (a->x24[i] < 0.0f) a->x24[i] = 0.0f;
        }
        f = a->x24[i];
        c[0] = func_001eddc0(0x60000000, 0x60000000, f);
        c[1] = func_001eddc0(0x601E0505, 0x60000060, f);
        c[2] = func_001eddc0(0, 0x801428C8, f);
        c[3] = func_001eddc0(0, 0x801428C8, f);
        c[4] = func_001eddc0(0x40E6E6E6, 0x80E6E6E6, f);
        func_00200648(a, 2, 185, y, 142, c);
        func_001f9438(a, 2, 256, y + 5, D_003F7500[i], 15, c[4]);
        h = f * -80.0f + 160.0f;
        func_002066b0(a, 186, y + 13, -h, c[2], 0x1428C8);
        func_002066b0(a, 327, y + 13, h, c[2], 0x1428C8);
        y += 28;
    }
}

void func_0022db98(Ob3 *a) {
    s32 c[5];
    s32 i, y, h;

    f32 f;
    if (func_001f42b8(a)) {
        u32 fl = D_00425BC8->x8;
        if (fl & 8) {
        } else if (fl & 0x4000) {
            D_003F76B8 = 1;
            func_001fd648(a, 1);
            func_0011d768(3);
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            D_003F76B8 = func_001fd518(a);
            if (func_001fe570(a)) {
                func_001f3840(a);
                func_0020be10(16);
            }
        }
    }
    y = 183;
    for (i = 0; i < 2; i++) {
        if (D_003F76B8 == i) {
            a->x24[i] = 1.0f;
        } else {
            a->x24[i] = a->x24[i] - 0.08;
            if (a->x24[i] < 0.0f) a->x24[i] = 0.0f;
        }
        f = a->x24[i];
        c[0] = func_001eddc0(0x60000000, 0x60000000, f);
        c[1] = func_001eddc0(0x601E0505, 0x60000060, f);
        c[2] = func_001eddc0(0, 0x801428C8, f);
        c[3] = func_001eddc0(0, 0x801428C8, f);
        c[4] = func_001eddc0(0x40E6E6E6, 0x80E6E6E6, f);
        func_00200648(a, 2, 185, y, 142, c);
        func_001f9438(a, 2, 256, y + 5, D_003F7598[i], 15, c[4]);
        h = f * -80.0f + 160.0f;
        func_002066b0(a, 186, y + 13, -h, c[2], 0x1428C8);
        func_002066b0(a, 327, y + 13, h, c[2], 0x1428C8);
        y += 28;
    }
}
