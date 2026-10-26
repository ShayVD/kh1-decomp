/* gb.x func_00f27220: matched by hand. */
#include "ovl.h"

double cos(double);
extern u32 D_00F61360;
extern f32 D_00F7F4E8;

void func_00f27220(void) {
    f32 x = (D_00F61360 & 0x3F);
    f32 *p = &D_00F7F4E8;
    f32 t = (f32)cos(x * 6.28318500519f * 0.015625f) * 0.3f;
    D_00F61360++;
    *p = t + 0.7f;
}
