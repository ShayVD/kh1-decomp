/* wm.x func_00f324f0: matched by hand. */
#include "ovl.h"

extern f32 D_00F85270;
extern s32 D_00FBB5C4;
extern OvlMtx D_00FCC520;
extern OvlMtx D_00F8C240;
extern OvlMtx D_00F85200;
extern OvlMtx D_00F85180;
void func_00f324f0(OvlMtx m) {
    OvlVec v;
    if (D_00FBB5C4 == 0) {
        v[0] = 0.0f;
        v[3] = 1.0f;
        v[1] = 0.0f;
        v[2] = D_00F85270 + 20000.0f;
        PlatVu0UnitMatrix(m);
        PlatVu0TransMatrix(m, m, v);
        PlatVu0MulMatrix(m, D_00F8C240, m);
        PlatVu0CopyMatrix(D_00FCC520, m);
        PlatVu0MulMatrix(m, D_00F85200, m);
        PlatVu0MulMatrix(m, D_00F85180, m);
    } else {
        PlatVu0CopyMatrix(m, D_00FCC520);
        PlatVu0MulMatrix(m, D_00F85200, m);
        PlatVu0MulMatrix(m, D_00F85180, m);
    }
}
