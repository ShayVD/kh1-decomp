/* wm.x func_00f300a8: matched by hand. */
#include "ovl.h"

s32 func_00f2cfd8(s32, s32, s32, s32, s32, s32, f32 *, void (*)(void), s32, s32);
extern s32 D_00F8C128;
extern f32 D_00F8C150;
extern s32 D_00F8C280;
extern s32 D_00F8C2D0;
extern s32 D_00F8C2D4;

void func_00f300a8(void) {
    OvlVec c;
    c[0] = D_00F8C150;
    c[1] = D_00F8C150;
    c[2] = D_00F8C150;
    c[3] = 1.0f;
    if (D_00F8C128 == 0) {
        D_00F8C2D0 = func_00f2cfd8(0, -3, -1, 27, 2, 27, 0, 0, 0, -1);
        if (D_00F8C280 >= 2) {
            D_00F8C2D4 = func_00f2cfd8(1, -3, -1, 27, 2, 27, 0, 0, 0, -1);
        } else {
            D_00F8C2D4 = -1;
        }
    }
}
