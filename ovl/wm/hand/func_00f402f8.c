/* wm.x func_00f402f8: matched by hand. */
#include "ovl.h"

extern OvlMtx D_00F85180;
extern OvlMtx D_00F85200;
s32 func_00f402f8(OvlMtx arg0, f32 r) {
    OvlMtx m;
    OvlVec o;
    OvlVec v;
    PlatVu0MulMatrix(m, D_00F85200, arg0);
    if (m[3][2] <= -r) return 0;
    if (m[3][2] > 70000.0f) return 0;
    v[1] = m[3][1];
    v[3] = 1.0f;
    v[0] = m[3][0] - r;
    v[2] = m[3][2];
    PlatVu0ApplyMatrix(o, D_00F85180, v);
    o[0] = o[0] / o[2];
    if (o[0] > 2304.0f) return 0;
    v[0] = m[3][0] + r;
    PlatVu0ApplyMatrix(o, D_00F85180, v);
    o[0] = o[0] / o[2];
    if (o[0] < 1792.0f) return 0;
    v[0] = m[3][0];
    v[1] = m[3][1] - r;
    PlatVu0ApplyMatrix(o, D_00F85180, v);
    o[1] = o[1] / o[2];
    if (o[1] > 2240.0f) return 0;
    v[1] = m[3][1] + r;
    PlatVu0ApplyMatrix(o, D_00F85180, v);
    o[1] = o[1] / o[2];
    if (o[1] < 1856.0f) return 0;
    return 1;
}
