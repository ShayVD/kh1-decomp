/* wm.x func_00f45268: matched by hand. */
#include "ovl.h"

s32 func_001c01b0(s32, void (*)(), ...);
extern s32 D_00F9B328;
extern s32 D_010807F8;
void func_00f446a0();
void func_00f45268(s32 arg0, s32 arg1, s32 arg2) {
    D_010807F8 = 1;
    D_00F9B328 = 1;
    func_001c01b0(-1, func_00f446a0, arg0, arg1, arg2);
}
