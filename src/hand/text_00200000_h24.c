#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"

typedef W606Mem_304be8 S4BE8e;

#include "data/pieces/D_003F34B8.h"

extern s32 D_00642EA0;
extern u8 D_00642E98[];
#include "data/pieces/D_003F5C18.h"
void func_0021cfc8(void) {
    s32 i;
    D_00642EA0 = 0;
    for (i = 0; i < 6; i++) {
        if (D_003F5C18[i]) D_00642E98[D_00642EA0++] = i;
    }
}

extern s32 D_00643010, D_00643014;
extern s32 D_003F5C30[];
void func_0021fb50(void);
void func_002205c0(void);
void func_002210f0(void);
void func_00223978(void);
void func_00222b80(void);
void func_002234e8(void);
void func_0021db30(void) {
    s32 i;
    D_00643010 = 0;
    D_00643014 = 0;
    D_003F34B8->b112[1] = 0;
    for (i = 5; i >= 0; i--) D_003F5C30[i] = 0;
    func_0021fb50();
    func_002205c0();
    func_002210f0();
    func_00223978();
    func_00222b80();
    func_002234e8();
}

extern s32 D_0064324C, D_00643250;
extern s32 D_00643258[], D_00643268[];
extern s32 D_00643118, D_0064311C, D_00643120;
void func_0021fb50(void) {
    s32 i;
    D_0064324C = 0;
    D_00643250 = 0;
    for (i = 0; i < 3; i++) {
        D_00643258[i] = 0;
        D_00643268[i] = 0;
    }
    D_0064311C = -1;
    D_00643120 = -1;
    D_00643118 = 0;
}

extern s32 D_00643418;
extern u8 D_006433F8[];
s32 func_00206ee8(s32);
void func_00207298(s32);
void func_002072e0(s32);
void func_002204f0(void) {
    s32 i;
    for (i = 0; i < D_00643418; i++) {
        if (!func_00206ee8(D_006433F8[i])) {
            func_00207298(0);
            return;
        }
    }
    func_002072e0(0);
}

extern u8 D_003F6300[], D_003F62D0[];
s32 func_001f31a8(void *, s32);
void func_001f3e48(s32, s32);
void func_00220fe8(s32 a0) {
    s32 a[2];
    a[0] = func_001f31a8(D_003F6300, 50);
    if (a[0]) {
        func_001f3e48(a[0], a0);
        a[1] = func_001f31a8(D_003F62D0, 50);
        if (a[1]) func_001f3e48(a[1], a[0]);
    }
}

void func_0021b800(s32);
void func_002213a8(s32 a0) {
    if (a0 <= 0) func_0021b800(48);
    else if (a0 < 6) func_0021b800(49);
    else if (a0 < 10) func_0021b800(50);
    else if (a0 < 15) func_0021b800(a0 + 41);
    else func_0021b800(56);
}

extern s32 D_00643674;
extern u8 D_00643668[];
s32 func_00207250(s32);
void func_00222ab0(void) {
    s32 i;
    for (i = 0; i < D_00643674; i++) {
        if (!func_00207250(D_00643668[i])) {
            func_00207298(5);
            return;
        }
    }
    func_002072e0(5);
}

/* needs make: uses rodata */
#include "data/data_003F.h"
