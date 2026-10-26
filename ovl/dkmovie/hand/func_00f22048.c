/* dkmovie.x func_00f22048: matched by hand. */
#include "ovl.h"

void func_00f21da0(s32, s32, s32, void *, s32);
void func_00f22290(s32, s32);
extern u8 D_00F283D0[];
extern s8 D_00F28680;
s32 func_00f22048(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n = arg1 / 0x800;
    if (arg1 % 0x800 != 0) {
        n++;
    }
    D_00F28680 = 1;
    func_00f21da0(arg0, n, arg2, D_00F283D0, arg3);
    func_00f22290(0, arg3);
    return 1;
}
