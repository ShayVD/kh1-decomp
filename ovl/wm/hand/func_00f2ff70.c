/* wm.x func_00f2ff70: matched by hand. */
#include "ovl.h"

s32 func_00f2cfd8(s32, s32, s32, s32, s32, s32, f32 *, void (*)(void), s32, s32);
void func_001c0310(s32, void (*)(void), ...);
extern s32 D_00F8C2D0;
extern s32 D_00F8C2D4;
extern s32 D_00F8C2D8;
extern s32 D_00F8C2DC;
void func_00f2ff18(void);

void func_00f2ff70(void) {
    D_00F8C2D8 = -1;
    D_00F8C2DC = -1;
    if (D_00F8C2D0 >= 0) {
        D_00F8C2D8 = func_00f2cfd8(0, -3, -1, 28, 2, 28, 0, 0, 0, -1);
    }
    if (D_00F8C2D4 >= 0) {
        D_00F8C2DC = func_00f2cfd8(1, -3, -1, 28, 2, 28, 0, 0, 0, -1);
    }
    func_001c0310(9, func_00f2ff18);
}
