/* wm.x func_00f4e318: matched by hand. */
#include "ovl.h"

double cos(double);
extern u32 D_00FA5AE0;
extern f32 D_0108BCA8;

void func_00f4e318(void) {
    f32 x = (D_00FA5AE0 & 0x3F);
    f32 *p = &D_0108BCA8;
    f32 t = (f32)cos(x * 6.28318500519f * 0.015625f) * 0.3f;
    D_00FA5AE0++;
    *p = t + 0.7f;
}
