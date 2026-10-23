/* Three choice screens (docs/modules.md "Session 43"), 0x0022d728-0x0022e458.
 * Each is opened by itself (func_0022daa0, func_0022dee0, func_0022e368:
 * D_003F34A4 = 1, a task func_0022da58 / func_0022de98 / func_0022e320) as
 * a chain of three windows: a backdrop (func_0022da40 ...), a title
 * (func_0022da10, message 0x5f; func_0022de50, 0x1ce; func_0022e2c0, 0x1d8
 * through func_001efc10) and the list of choices, the handlers of
 * choice.nofill.c (they need -fno-fill: 3 rows D_003F7500, 2 rows D_003F7598,
 * 2 rows D_003F7628).  The answer is left in D_003F76B4 / D_003F76B8 /
 * D_003F76BC (0 when cancelled).  What each one asks is not known; not
 * proved by a boot. */
#include "common.h"
#include "text/textwin.h"

extern s32 D_003F34A4;
extern s32 D_003F76B4, D_003F76B8, D_003F76BC;
extern u8 D_003F7510[], D_003F7540[], D_003F7570[];
extern u8 D_003F75A0[], D_003F75D0[], D_003F7600[];
extern u8 D_003F7630[], D_003F7660[], D_003F7690[];

s16 *func_0011ef10(s32, void *);
s32 func_001efc10(s32);
void func_001f3110(void);
void *func_001f31a8(void *, s32);
void func_001f3e48(void *, void *);
s32 func_001f40c8(void);
void func_001f82b0(void);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
s32 func_001f94f0(void *, s32, s32, s32, s32, s32, s32);
s32 func_00205938(void *, s32);
void func_0020b998(void);
void func_0020bbc0(void *);
void func_0020bd18(void *, s32);
void func_0020bda8(s32);

void func_0022d728(void) {

}


void func_0022da10(TextWin *arg0) {
    func_001f9438(arg0, 2, 0x100, 0x90, 0x5F, 0x12, 0x801E4696);
}


s32 func_0022da40(TextWin *arg0) {
    return func_00205938(arg0, 0x56000000);
}


s32 func_0022da58(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    D_003F34A4 = 0;
    return 4;
}


void func_0022daa0(s32 arg0) {
    TextWin *o[3];
    func_001f3110();
    D_003F76B4 = 0;
    o[0] = func_001f31a8(D_003F7570, 1);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F7540, 1);
        if (o[1] != NULL) {
            func_001f3e48(o[1], o[0]);
            o[2] = func_001f31a8(D_003F7510, 1);
            if (o[2] != NULL) {
                func_001f3e48(o[2], o[1]);
                o[2]->xa0 = 16.0f;
            }
        }
    }
    D_003F34A4 = 1;
    func_0020bbc0(o[2]);
    func_0020bd18(o[2], 8);
    func_0020bda8(0x10);
    func_0011ef10(0x2BFE9, func_0022da58)[1] = arg0;
}


void func_0022db90(void) {

}


void func_0022de50(TextWin *arg0) {
    func_001f9438(arg0, 2, 0x100, 0x90, 0x1CE, 0x12, 0x801E4696);
}


s32 func_0022de80(TextWin *arg0) {
    return func_00205938(arg0, 0x56000000);
}


s32 func_0022de98(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    D_003F34A4 = 0;
    return 4;
}


void func_0022dee0(s32 arg0) {
    TextWin *o[3];
    func_001f3110();
    D_003F76B8 = 0;
    o[0] = func_001f31a8(D_003F7600, 1);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F75D0, 1);
        if (o[1] != NULL) {
            func_001f3e48(o[1], o[0]);
            o[2] = func_001f31a8(D_003F75A0, 1);
            if (o[2] != NULL) {
                func_001f3e48(o[2], o[1]);
                o[2]->xa0 = 16.0f;
            }
        }
    }
    D_003F34A4 = 1;
    func_0020bbc0(o[2]);
    func_0020bd18(o[2], 8);
    func_0020bda8(0x10);
    func_0011ef10(0x2BFE9, func_0022de98)[1] = arg0;
}


void func_0022dfd0(void) {

}


void func_0022e2c0(TextWin *arg0) {
    func_001f94f0(arg0, 2, 0x100, 0x90, func_001efc10(0x1D8), 0x12, 0x801E4696);
}


s32 func_0022e308(TextWin *arg0) {
    return func_00205938(arg0, 0x56000000);
}


s32 func_0022e320(void) {
    if (func_001f40c8() != 0) {
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    D_003F34A4 = 0;
    return 4;
}


void func_0022e368(s32 arg0) {
    TextWin *o[3];
    func_001f3110();
    D_003F76BC = 0;
    o[0] = func_001f31a8(D_003F7690, 1);
    if (o[0] != NULL) {
        o[1] = func_001f31a8(D_003F7660, 1);
        if (o[1] != NULL) {
            func_001f3e48(o[1], o[0]);
            o[2] = func_001f31a8(D_003F7630, 1);
            if (o[2] != NULL) {
                func_001f3e48(o[2], o[1]);
                o[2]->xa0 = 16.0f;
            }
        }
    }
    D_003F34A4 = 1;
    func_0020bbc0(o[2]);
    func_0020bd18(o[2], 8);
    func_0020bda8(0x10);
    func_0011ef10(0x2BFE9, func_0022e320)[1] = arg0;
}
