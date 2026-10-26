/* wm.x func_00f5de50: matched by hand. */
#include "ovl.h"

s32 func_00f667b8(s32, void *, s32);
extern u8 D_00FA5E50[];
extern u8 D_00FA5F00[];

void func_00f5de50(s32 *arg0, s32 arg1) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (arg1 == 0) {
            arg0[i] = func_00f667b8(arg0[i], D_00FA5E50, 6);
        } else {
            arg0[i] = func_00f667b8(arg0[i], D_00FA5F00, 6);
        }
    }
}
