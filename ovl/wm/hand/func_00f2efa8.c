/* wm.x func_00f2efa8: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
s32 func_00f2cae8(void);
void func_00f2cf78(s32);
void func_00f2ee20(s32);
s32 func_00f680c0(s32);
s32 func_00f68770(s32, s32, s32, s32, s32);
extern s32 D_00F87048;
void func_00f2efa8(s32 arg0) {
    s32 h = func_00f68770(0x44, 2000, func_00f2cae8() + 0x20, 0, D_00F87048);
    while (func_00f680c0(h) != 0) {
        func_00f2ee20(arg0 | 0x8000);
        func_001bfac8();
    }
    func_00f2cf78(arg0);
}
