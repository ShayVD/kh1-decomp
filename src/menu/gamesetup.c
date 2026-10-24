/* The game settings screen (docs/modules.md "Session 43"), 0x0022bd58-0x0022d138.
 * func_0022d080 opens it by itself (D_003F34A4 = 1, the frame D_003F7380, the
 * task func_0022d038) at step D_006469B0 = 1, or 2 when func_00219428 is 0
 * (D_006469B4 the step before, so a window knows whether it was reached
 * forwards or backwards).  func_0022cde8, the frame's handler, opens one
 * window per step, each setting one of the settings of src/menu/settings.c:
 * 1 D_003F7350 (func_0022c960, the setting of func_00219418, three choices
 * D_003F7308), 2 D_003F7320 (func_0022cba8, func_002193e0), 3 D_003F72E0
 * (func_0022c730, func_00219320, two choices D_003F7240), 4 D_003F72B0
 * (func_0022c4e8, func_00219370), 5 D_003F7280 (func_0022c2a0, func_002193a8),
 * 6 D_003F7250 (func_0022bd58: every value again, yes or no); step 0 (back
 * from the first) resets them and closes, step 7 closes with D_003F73A4 = 1.
 * Each window draws the panel D_003F7210 (func_00201440) and its title.
 * Most likely asked before a new game starts; not proved by a boot. */
#include "common.h"
#include "platform/pad.h"
#include "data/bss_0064.h"
#include "data/pieces/D_003E8E08.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003F47A8.h"
#include "data/pieces/D_003F7238.h"
#include "menu/settings.h"
#include "text/textwin.h"

extern s32 D_003F34A4;
extern s32 D_003F73A4;
extern u8 D_003F7210[];
extern s32 D_003F7228[];
extern s32 D_003F7230[];
extern s32 D_003F7240[];
extern s32 D_003F7248[];
extern s32 D_003F7308[];
extern u8 D_003F7250[], D_003F7280[], D_003F72B0[], D_003F72E0[], D_003F7320[], D_003F7350[];
extern u8 D_003F7380[];

void func_0011d768(s32);
s16 *func_0011ef10(s32, void *);
s32 func_001efbb8(s32);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void *func_001f3520(void *, s32);
void func_001f36b8(void *);
void func_001f3708(void *, s32);
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
s32 func_001f40c8(void);
s32 func_001f42b8(void *);
void func_001f82b0(void);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001fa808(void *, s32, s32, s32, s32);
s32 func_001fd518(void *);
s32 func_001fd538(void *);
void func_001fd858(void *);
void func_001fdfd0(void *);
s32 func_001fe570(void *);
void func_00201440(void *, s32, s32, s32, s32, s32, s32, void *, s32);
void func_002053e8(void *, s32, s32, s32, s32, s32);
void func_00205938(void *, s32);
void func_002066b0(void *, s32, s32, s32, s32, s32);
void func_002078f0(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00209820(void *, s32, s32, s32, void *);
void func_0020b998(void);
void func_0020bb90(s32, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
s32 func_00219458(s32);

void func_0022bd58(TextWin *a0) {
    s32 s, x, y;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0 = D_006469B0 - 1;
        } else {
            func_001fdfd0(a0);
            x = a0->xb0 + a0->xda * 96 + (u32)(a0->xbe - 0x7000);
            y = a0->xb4 + a0->xc4 * a0->ud0.s.xd2 / 16;
            func_0020bc48(8, (s32)(x + a0->xc2 - a0->xc6) >> 4, (y + a0->xc0 - 0x7400) >> 4);
            if (func_001fe570(a0)) {
                if (func_001fd538(a0) == 0) {
                    D_006469B4 = D_006469B0;
                    D_006469B0 = D_006469B0 + 1;
                    func_001f3708(a0, 11);
                } else {
                    D_006469B4 = D_006469B0;
                    D_006469B0 = func_00219428() ? 1 : 2;
                    func_001f3708(a0, 12);
                }
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80c2726e, 0x80c2726e);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80c2726e, 0x80c2726e);
    if (func_00219428()) {
        func_001f9438(a0, 0, 40, 230, 94, 15, 0x80e6e6e6);
        (*(S4_3e8e08 *)&D_003E8E08).a = func_001efbb8(D_003F7230[func_002193b8()]);
        func_001f9438(a0, 0, 128, 126, 450, 15, 0x66ffc8b4);
        (*(S4_3e8e08 *)&D_003E8E08).a = func_00219458(func_002193f0());
        func_001f9438(a0, 0, 128, 146, 92, 15, 0x66ffc8b4);
        (*(S4_3e8e08 *)&D_003E8E08).a = func_001efbb8(D_003F7238[func_002192f8()]);
        func_001f9438(a0, 0, 128, 166, 471, 15, 0x66ffc8b4);
        (*(S4_3e8e08 *)&D_003E8E08).a = func_001efbb8(D_003F7228[func_00219348()]);
        func_001f9438(a0, 0, 128, 186, 93, 15, 0x66ffc8b4);
        (*(S4_3e8e08 *)&D_003E8E08).a = func_001efbb8(D_003F7248[func_00219380()]);
        func_001f9438(a0, 0, 128, 206, 476, 15, 0x66ffc8b4);
    } else {
        func_001f9438(a0, 0, 40, 230, 94, 15, 0x80e6e6e6);
        (*(S4_3e8e08 *)&D_003E8E08).a = func_00219458(func_002193f0());
        func_001f9438(a0, 0, 128, 130, 92, 15, 0x66ffc8b4);
        (*(S4_3e8e08 *)&D_003E8E08).a = func_001efbb8(D_003F7238[func_002192f8()]);
        func_001f9438(a0, 0, 128, 150, 471, 15, 0x66ffc8b4);
        (*(S4_3e8e08 *)&D_003E8E08).a = func_001efbb8(D_003F7228[func_00219348()]);
        func_001f9438(a0, 0, 128, 170, 93, 15, 0x66ffc8b4);
        (*(S4_3e8e08 *)&D_003E8E08).a = func_001efbb8(D_003F7248[func_00219380()]);
        func_001f9438(a0, 0, 128, 190, 476, 15, 0x66ffc8b4);
    }
    s = func_001fd538(a0);
    func_002078f0(a0, s == 0, 2, 2, 256, a0->xc0 >> 4, 90, 301, 44);
    func_002078f0(a0, s == 1, 2, 2, 352, a0->xc0 >> 4, 90, 397, 45);
}

void func_0022c2a0(TextWin *a0) {
    s32 s, x, y;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0 = D_006469B0 - 1;
        } else {
            func_001fdfd0(a0);
            x = a0->xb0 + a0->xda * 96 + (u32)(a0->xbe - 0x7000);
            y = a0->xb4 + a0->xc4 * a0->ud0.s.xd2 / 16;
            func_0020bc48(8, (s32)(x + a0->xc2 - a0->xc6) >> 4, (y + a0->xc0 - 0x7400) >> 4);
            if (func_001fe570(a0)) {
                func_001f3708(a0, 11);
                func_002193a8(func_001fd538(a0));
                D_006469B4 = D_006469B0;
                D_006469B0 = D_006469B0 + 1;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80c2726e, 0x80c2726e);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80c2726e, 0x80c2726e);
    func_001fa808(a0, 161, 475, 15, 0x80e6e6e6);
    s = func_001fd538(a0);
    func_002078f0(a0, s == 0, 2, 2, 163, 174, 90, 208, 477);
    func_002078f0(a0, s == 1, 2, 2, 259, 174, 90, 304, 478);
}

void func_0022c4e8(TextWin *a0) {
    s32 s, x, y;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0 = D_006469B0 - 1;
        } else {
            func_001fdfd0(a0);
            x = a0->xb0 + a0->xda * 96 + (u32)(a0->xbe - 0x7000);
            y = a0->xb4 + a0->xc4 * a0->ud0.s.xd2 / 16;
            func_0020bc48(8, (s32)(x + a0->xc2 - a0->xc6) >> 4, (y + a0->xc0 - 0x7400) >> 4);
            if (func_001fe570(a0)) {
                func_001f3708(a0, 11);
                func_00219370(func_001fd538(a0));
                D_006469B4 = D_006469B0;
                D_006469B0 = D_006469B0 + 1;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80c2726e, 0x80c2726e);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80c2726e, 0x80c2726e);
    func_001fa808(a0, 161, 89, 15, 0x80e6e6e6);
    s = func_001fd538(a0);
    func_002078f0(a0, s == 0, 2, 2, 163, 174, 90, 208, 46);
    func_002078f0(a0, s == 1, 2, 2, 259, 174, 90, 304, 47);
}

void func_0022c730(TextWin *a0) {
    s32 i, y;
    if (func_001f42b8(a0)) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0 = D_006469B0 - 1;
        } else {
            func_0020bc48(8, (a0->xb0 + a0->xc2 + a0->xbe - 0x7000) >> 4,
                          (a0->xb4 + a0->xc4 * a0->ud0.s.xd2 / 16 + a0->xc0 - 0x7400) >> 4);
            func_001fd858(a0);
            if (func_001fe570(a0)) {
                func_001f3708(a0, 11);
                func_00219320(func_001fd518(a0));
                D_006469B4 = D_006469B0;
                D_006469B0 = D_006469B0 + 1;
            }
        }
    }
    func_00201440(a0, 2, 2, 11, 81, 122, 72, D_003F7210, 87);
    func_002066b0(a0, -64, 112, 640, 0x80c2726e, 0x80c2726e);
    func_002053e8(a0, -64, 114, 640, 156, 0x40000000);
    func_002066b0(a0, -64, 270, 640, 0x80c2726e, 0x80c2726e);
    func_001fa808(a0, 161, 466, 15, 0x80e6e6e6);
    y = 166;
    for (i = 0; i < 2; i++) {
        func_001f9438(a0, 0, 131, y, D_003F7240[i], 15, 0x80e6e6e6);
        y += 28;
    }
    func_00209820(a0, 2, 2, 71, D_003F7238);
}

void func_0022c960(TextWin *a0) {
    s32 i, y; s32 *p;
    if (func_001f42b8(a0) != 0) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            if ((D_006469B4 = D_006469B0, func_00219428()) != 0) {
                D_006469B0--;
            } else {
                D_006469B0 = 0;
            }
        } else {
            func_0020bc48(8, (a0->xb0 + a0->xc2 + a0->xbe - 0x7000) >> 4,
                          (a0->xb4 + a0->xc4 * a0->ud0.s.xd2 / 16 + a0->xc0 - 0x7400) >> 4);
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

void func_0022cba8(TextWin *a0) {
    s32 v;
    if (func_001f42b8(a0) != 0) {
        if (D_00425BC8->x8 & PAD_CROSS) {
            func_001f3708(a0, 12);
            func_0011d768(3);
            D_006469B4 = D_006469B0;
            D_006469B0--;
        } else {
            func_001fdfd0(a0);
            func_0020bc48(8, (a0->xb0 + a0->xc2 + (a0->xbe - 0x7000) + a0->xda * 202 - a0->xc6) >> 4,
                          (a0->xb4 + a0->xc4 * a0->ud0.s.xd2 / 16 + a0->xc0 - 0x7400) >> 4);
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

void func_0022cde8(TextWin *a) {
    TextWin *o;
    s32 k;
    if (func_001f42b8(a)) {
        k = D_006469B0 < D_006469B4 ? 11 : 12;
        switch (D_006469B0) {
        case 0:
            func_001f36b8(a);
            func_0020be10(16);
            func_002193e0(0);
            func_00219418(1);
            func_00219320(0);
            func_00219370(0);
            func_002193a8(0);
            break;
        case 1:
            if (!(o = func_001f3520(D_003F7350, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->xda = func_002193b8() << 4;
            break;
        case 2:
            if (!(o = func_001f31a8(D_003F7320, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->ud0.s.xd2 = func_002193f0() << 4;
            break;
        case 3:
            if (!(o = func_001f31a8(D_003F72E0, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->ud0.s.xd2 = func_002192f8() << 4;
            break;
        case 4:
            if (!(o = func_001f3520(D_003F72B0, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->xda = func_00219348() << 4;
            break;
        case 5:
            if (!(o = func_001f3520(D_003F7280, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            o->xda = func_00219380() << 4;
            break;
        case 6:
            if (!(o = func_001f3520(D_003F7250, k))) break;
            func_001f3e90(a, o);
            func_001f3e20(o, a);
            break;
        case 7:
            func_001f36b8(a);
            func_0020be10(16);
            D_003F73A4 = 1;
            break;
        }
    }
    func_00205938(a, 0x70000000);
}

s32 func_0022d038(void) {
    if (func_001f40c8()) {
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    D_003F34A4 = 0;
    return 4;
}

void func_0022d080(s32 arg0) {
    void *objs[4];
    s32 v;
    s32 *p = &D_006469B4, *q = &D_006469B0;
    func_001f3110();
    objs[0] = func_001f31a8(D_003F7380, 12);
    v = func_00219428() != 0 ? 1 : 2;
    *q = v;
    *p = v;
    func_0020bb90(0, 0);
    func_0020bda8(0x10);
    D_003F34A4 = 1;
    D_003F73A4 = 0;
    func_0011ef10(0x2BFE7, func_0022d038)[1] = arg0;
}
