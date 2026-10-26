/* wm.x func_00f3caf0: matched by hand. */
#include "ovl.h"

s32 func_00f3caf0(OvlVec arg0, OvlVec arg1, f32 arg2, f32 arg3) {
    OvlVec d;
    f32 r;
    PlatVu0SubVector(d, arg0, arg1);
    r = arg2 + arg3;
    if (r < __builtin_fabsf(d[2])) {
        return 0;
    }
    if (r < __builtin_fabsf(d[0])) {
        return 0;
    }
    if (r < __builtin_fabsf(d[1])) {
        return 0;
    }
    r = r * r;
    if (PlatVu0InnerProduct(d, d) < r) {
        return 1;
    }
    return 0;
}
