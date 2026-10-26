/* wm.x func_00f3d758: matched by hand. */
#include "ovl.h"

f32 func_00f2c7f8(void);
f32 *func_00f2c848(void);
s32 func_00f33a90(void);
f32 *func_00f35058(s32);
s32 func_00f3caf0(f32 *, s32, f32, f32);
extern OvlMtx D_00F8C240;

s32 func_00f3d758(s32 arg0, f32 r) {
    OvlVec v;
    s32 i;
    f32 *p = func_00f2c848();
    if (func_00f3caf0(p, arg0, func_00f2c7f8(), r) != 0) {
        for (i = 0; i < func_00f33a90(); i++) {
            f32 *q = func_00f35058(i);
            f32 w;
            v[0] = q[0];
            v[1] = q[1];
            v[2] = q[2];
            v[3] = 1.0f;
            w = q[3];
            PlatVu0ApplyMatrix(v, D_00F8C240, v);
            if (func_00f3caf0(v, arg0, w, r) != 0) return 1;
        }
    }
    return 0;
}
