/* A text screen (docs/modules.md "Session 43"), 0x0022d138-0x0022d728.
 * func_0022d4d8 opens it by itself (D_003F34A4 = 1, the task func_0022d498):
 * a backdrop D_003F74D0, the window D_003F74A0 (func_0022d400: a button press,
 * D_00425BC8->x8 & 8, starts the timers) and five text lines D_003F73B0 ...
 * D_003F7470 (func_0022d140 ... func_0022d320, messages 0x1d, 0xe, 0x22,
 * 0x20, 0x12).  Each line closes when its timer D_006469B8[k] (set to 1, 1,
 * 3, 5, 7, 9) has counted down by D_002BBDFC a frame, so they leave one after
 * another; func_0022d398 is the backdrop (D_006469B8[0]).  What screen it is
 * is not known; not proved by a boot. */
#include "common.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_00425BC8.h"
#include "text/textwin.h"

extern s32 D_003F34A4;
extern u8 D_003F74D0[], D_003F74A0[], D_003F73B0[], D_003F73E0[], D_003F7410[], D_003F7440[], D_003F7470[];
extern f32 D_006469B8[]; /* src/data/bss_0064.c: s32 D_006469B8[0x6] */

void func_0011d768(s32);
s16 *func_0011ef10(s32, void *);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f36b8(void *);
void func_001f3d58(void *, s32);
void func_001f3dc0(void *);
void func_001f3e20(void *, void *);
void func_001f3e90(void *, void *);
s32 func_001f40c8(void);
s32 func_001f4338(void);
s32 func_001f4400(void);
void func_001f82b0(void);
void func_001fade0(void *, s32, s32, s32, s32, s32);
void func_00205938(void *, s32);

void func_0022d138(void) {

}

void func_0022d140(TextWin *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[1] != 0.0f)) {
        temp_f0 = D_006469B8[1] - D_002BBDFC;
        D_006469B8[1] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x1D, 0x12, arg0->x24);
}

void func_0022d1b8(TextWin *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[2] != 0.0f)) {
        temp_f0 = D_006469B8[2] - D_002BBDFC;
        D_006469B8[2] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0xE, 0x12, arg0->x24);
}

void func_0022d230(TextWin *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[3] != 0.0f)) {
        temp_f0 = D_006469B8[3] - D_002BBDFC;
        D_006469B8[3] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x22, 0x12, arg0->x24);
}

void func_0022d2a8(TextWin *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[4] != 0.0f)) {
        temp_f0 = D_006469B8[4] - D_002BBDFC;
        D_006469B8[4] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x20, 0x12, arg0->x24);
}

void func_0022d320(TextWin *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[5] != 0.0f)) {
        temp_f0 = D_006469B8[5] - D_002BBDFC;
        D_006469B8[5] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_001fade0(arg0, 0, 0, 0x12, 0x12, arg0->x24);
}

void func_0022d398(TextWin *arg0) {
    f32 temp_f0;

    if ((func_001f4400() != 0) && (D_006469B8[0] != 0.0f)) {
        temp_f0 = D_006469B8[0] - D_002BBDFC;
        D_006469B8[0] = temp_f0;
        if (temp_f0 <= 0.0f) {
            func_001f36b8(arg0);
        }
    }
    func_00205938(arg0, 0x33000000);
}

void func_0022d400(TextWin *arg0) {
    if ((func_001f4338() != 0) && (D_00425BC8->x8 & 8)) {
        func_001f36b8(arg0);
        func_0011d768(3);
        D_006469B8[0] = 1.0f;
        D_006469B8[1] = 1.0f;
        D_006469B8[2] = 3.0f;
        D_006469B8[3] = 5.0f;
        D_006469B8[4] = 7.0f;
        D_006469B8[5] = 9.0f;
    }
}

s32 func_0022d498(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        return 0;
    }
    D_003F34A4 = 0;
    return 4;
}

void func_0022d4d8(s32 arg0) {
    TextWin *o[7];
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
