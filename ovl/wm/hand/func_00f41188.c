/* wm.x func_00f41188: matched by hand. */
#include "ovl.h"

s32 func_001c01b0(s32, void (*)(), ...);
extern s32 D_00F9B2B8;
void func_00f40d20();
void func_00f41188(s32 arg0, s32 arg1, s32 arg2) {
    if (D_00F9B2B8 == 0) {
        D_00F9B2B8 = 1;
        func_001c01b0(-1, func_00f40d20, arg0, arg1, arg2);
    }
}
