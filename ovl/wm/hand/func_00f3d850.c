/* wm.x func_00f3d850: matched by hand. */
#include "ovl.h"

f32 func_00f2c7f8(void);
f32 *func_00f2c848(void);
s32 func_00f33a90(void);
f32 *func_00f35058(s32);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
s32 func_00f3cb90(f32 *, s32, f32, s32, s32);
#else
s32 func_00f3cb90(f32 *, s32, s32, s32, f32);
static __inline__ s32 ee_00f3cb90(f32 * x0, s32 x1, f32 x2, s32 x3, s32 x4) { return func_00f3cb90(x0, x1, x3, x4, x2); }
#undef func_00f3cb90
#define func_00f3cb90 ee_00f3cb90
#endif
extern OvlMtx D_00F8C240;

s32 func_00f3d850(s32 arg0, s32 arg1, s32 arg2, f32 *out) {
    OvlVec v;
    s32 i;
    f32 *p = func_00f2c848();
    if (func_00f3cb90(p, arg0, func_00f2c7f8(), arg1, arg2) != 0) {
        for (i = 0; i < func_00f33a90(); i++) {
            f32 *q = func_00f35058(i);
            f32 w;
            v[0] = q[0];
            v[1] = q[1];
            v[2] = q[2];
            v[3] = 1.0f;
            w = q[3];
            PlatVu0ApplyMatrix(v, D_00F8C240, v);
            if (func_00f3cb90(v, arg0, w, arg1, arg2) != 0) {
                PlatVu0CopyVector(out, v);
                return 1;
            }
        }
    }
    return 0;
}
