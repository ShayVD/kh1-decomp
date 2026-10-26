/* wm.x func_00f22a78: matched by hand. */
#include "ovl.h"

extern s32 D_00F87900[];
extern OvlMtx D_00F87910;
extern OvlMtx D_00F9A580;
extern s32 D_00FBAA90;

void func_00f22a78(s32 arg0, s32 arg1, OvlVec *arg2) {
    D_00F87900[0] = arg0;
    D_00F87900[1] = arg1;
    D_00FBAA90 |= 2;
    PlatVu0MulMatrix(D_00F87910, arg2, D_00F9A580);
}
