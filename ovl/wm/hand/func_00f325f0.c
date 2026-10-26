/* wm.x func_00f325f0: matched by hand. */
#include "ovl.h"

typedef struct { s32 used; s32 id; s32 pad[2]; OvlVec pos; } S;
extern S D_00FBB5D0[];
extern OvlMtx D_00F85180;
extern OvlMtx D_00F85200;

f32 func_00f325f0(s32 arg0, f32 *arg1) {
    OvlMtx m;
    OvlVec v;
    f32 dx, dy;
    PlatVu0MulMatrix(m, D_00F85180, D_00F85200);
    PlatVu0ApplyMatrix(v, m, arg1);
    dx = D_00FBB5D0[arg0].pos[0] / D_00FBB5D0[arg0].pos[3] - arg1[0];
    dy = D_00FBB5D0[arg0].pos[1] / D_00FBB5D0[arg0].pos[3] - arg1[1];
    return dx * dx + dy * dy;
}
