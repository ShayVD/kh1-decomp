/* wm.x func_00f40b38: matched by hand. */
#include "ovl.h"

#include "ovl.h"

f32 *func_00f2c848(void);
f32 *func_00f3f2c0(void);
extern OvlMtx D_00F85200;
extern s32 D_00F8C23C;

void func_00f40b38(f32 z) {
    OvlVec a;
    OvlVec t;
    OvlVec u;
    OvlVec w; /* unused, keeps the frame size */
    f32 *p;
    f32 *q;
    if (D_00F8C23C != 0) return;
    t[2] = z + 3000.0f;
    p = func_00f3f2c0();
    a[0] = p[0];
    a[1] = p[1];
    q = func_00f2c848();
    if (a[0] < 6000.0f) {
        t[0] = 0.0f;
    } else {
        t[0] = -q[0] * (a[0] - 6000.0f) / a[0];
    }
    if (a[1] < 2240.0f) {
        t[1] = 0.0f;
    } else {
        t[1] = -q[1] * (a[1] - 2240.0f) / a[1];
    }
    u[2] = -3000.0f;
    t[3] = 1.0f;
    u[3] = 1.0f;
    u[0] = 0.0f;
    u[1] = 0.0f;
    t[1] += 500.0f;
    PlatVu0UnitMatrix(D_00F85200);
    PlatVu0TransMatrix(D_00F85200, D_00F85200, u);
    PlatVu0RotMatrixX(D_00F85200, D_00F85200, 0.17453291f);
    PlatVu0TransMatrix(D_00F85200, D_00F85200, t);
}
