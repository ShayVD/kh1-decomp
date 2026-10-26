/* wm.x func_00f3cb90: matched by hand. */
#include "ovl.h"

#include "ovl.h"

s32 func_00f3cb90(f32 *p, f32 *o, f32 *b, OvlMtx m, f32 r) {
    OvlMtx t;
    OvlVec v;
    OvlVec u; /* unused, keeps the frame size */
    PlatVu0CopyMatrix(t, m);
    t[3][0] = 0.0f;
    t[3][1] = 0.0f;
    t[3][2] = 0.0f;
    PlatVu0TransposeMatrix(t, t);
    PlatVu0SubVector(v, p, o);
    PlatVu0ApplyMatrix(v, t, v);
    if (-b[0] < v[0] && v[0] < b[0] && -b[1] < v[1] && v[1] < b[1] && -b[2] < v[2] && v[2] < b[2]) return 1;
    if (-(b[0] + r) < v[0] && v[0] < b[0] + r && -b[1] < v[1] && v[1] < b[1] && -b[2] < v[2] && v[2] < b[2]) return 1;
    if (-b[0] < v[0] && v[0] < b[0] && -(b[1] + r) < v[1] && v[1] < b[1] + r && -b[2] < v[2] && v[2] < b[2]) return 1;
    if (-b[0] < v[0] && v[0] < b[0] && -b[1] < v[1] && v[1] < b[1] && -(b[2] + r) < v[2] && v[2] < b[2] + r) return 1;
    return 0;
}
