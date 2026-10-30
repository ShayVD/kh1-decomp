/* wm.x func_00f78350: matched by hand. */
#include "ovl.h"

s32 func_0011ef10(s32, void (*)());
void func_001bfac8(void);
s32 func_001f31a8(void *, s32);
void func_0020bc48(s32, s32, s32);
void func_0020bda8(s32);
void func_0020be10(s32);
void func_00f77ed0();
extern u8 D_00FB5B30[];
extern s32 D_0108F194;
extern s32 D_0108F198;
extern s32 D_0108F1A8;
extern s32 D_0108F1AC;
extern s32 D_0108F1B0;
extern s32 D_0108F258;
extern s32 D_0108F568;
extern s32 D_0108F56C;
extern s32 D_0108F570;
extern s32 D_0108F574;
extern s32 D_0108F578;

s32 func_00f78350(s32 arg0, s32 arg1) {
    func_001bfac8();
    func_0020bda8(0x10);
    D_0108F568 = arg1;
    D_0108F258 = 1;
    D_0108F1A8 = 1;
    D_0108F1B0 = arg0;
    D_0108F56C = arg1;
    D_0108F1AC = 0;
    func_0011ef10(0x2BFE9, func_00f77ed0);
    D_0108F574 = 1;
    D_0108F570 = 1;
    D_0108F578 = -8;
    func_001f31a8(D_00FB5B30, 1);
    for (;;) {
        func_0020bc48(8, D_0108F194, D_0108F198);
        if (D_0108F1AC == 2)
            break;
        func_001bfac8();
    }
    func_0020be10(0x10);
    return D_0108F56C;
}
