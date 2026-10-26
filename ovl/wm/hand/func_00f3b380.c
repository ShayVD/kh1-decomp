/* wm.x func_00f3b380: matched by hand. */
#include "ovl.h"

f32 *func_00f2c848(void);
s32 func_00f3b380(f32 *arg0, f32 r) {
    OvlVec d;
    f32 *p = func_00f2c848();
    f32 dist;
    r = r * r;
    d[0] = p[0] - arg0[0];
    d[1] = p[1] - arg0[1];
    d[2] = p[2] - arg0[2];
    dist = d[0] * d[0] + d[1] * d[1] + d[0] * d[0];
    if (r < dist) return 1;
    if (dist < r) return 2;
    return 0;
}
