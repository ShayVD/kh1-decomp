#include "common.h"
extern s32 D_002B6474, D_002BCDE8, D_002C1388, D_002BCDF0;
void func_0013c6d8(void);
s32 func_001148c8(void);
void func_001136a8(void);
s32 func_001559f0(s32, s32);
void func_0011e9a8(void *, s32);

void func_001136d8(void) {
    if (D_002B6474 == 1) func_0013c6d8();
    func_001148c8();
    if (D_002BCDE8 == 0) {
        D_002C1388 = 1;
        func_0011e9a8(func_001136a8, func_001559f0(52, 4));
        return;
    }
    func_001136a8();
}
extern u8 D_002BCD60[];
void func_00112498(void);
void func_00101680(void);
s32 func_001137c8(s32, s32);
void func_001136d8(void);
s32 func_00120748(void *, s32, void (*)(void), s32);
s32 func_00113768(void) {
    s32 t;
    func_00112498();
    func_00101680();
    t = func_001137c8(D_002BCDF0, 128);
    D_002BCDF0 = t;
    func_00120748(D_002BCD60, t, func_001136d8, 0);
    return 4;
}
