/* wm.x func_00f68698: matched by hand. */
#include "ovl.h"

f32 *func_00176630(s32);
extern s32 D_00FB49E8;

s32 func_00f68698(f32 *center, f32 *ext, s32 idx) {
    f32 lo[4];
    f32 hi[4];
    f32 *m;

    if (idx < 0) {
        return 0;
    }
    m = func_00176630(D_00FB49E8 + idx * 72);
    lo[0] = m[4];
    lo[1] = m[9];
    lo[2] = m[14];
    hi[0] = m[0];
    hi[1] = m[13];
    hi[2] = m[10];
    ext[0] = (hi[0] - lo[0]) * 0.5f;
    ext[1] = (hi[1] - lo[1]) * 0.5f;
    ext[2] = (hi[2] - lo[2]) * 0.5f;
    center[0] = lo[0] + ext[0];
    center[1] = lo[1] + ext[1];
    center[2] = lo[2] + ext[2];
    return 1;
}
