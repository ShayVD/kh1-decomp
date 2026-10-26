/* wm.x func_00f20ba0: matched by hand. */
#include "ovl.h"

void func_00f68770(s32, s32, void *, f32 *, s32);
extern s32 D_00F87058;
extern s32 D_00FBAA58;

void func_00f20ba0(OvlMtx arg0) {
    OvlMtx m;
    OvlMtx r;
    OvlVec rot;
    OvlVec trans;
    OvlVec scale;
    scale[0] = scale[1] = scale[2] = 10.0f;
    scale[3] = 1.0f;
    trans[0] = 3883.0f;
    trans[1] = -5305.0f;
    trans[2] = -7814.0f;
    trans[3] = 1.0f;
    rot[0] = 0.13561206f;
    rot[1] = 2.53718472f;
    rot[2] = 2.9565871f;
    rot[3] = 1.0f;
    PlatVu0UnitMatrix(r);
    PlatVu0RotMatrixX(r, r, rot[0]);
    PlatVu0RotMatrixY(r, r, rot[1]);
    PlatVu0RotMatrixZ(r, r, rot[2]);
    PlatVu0TransMatrix(m, r, trans);
    PlatVu0UnitMatrix(r);
    PlatVu0RotMatrixX(r, r, 3.141592503f);
    PlatVu0MulMatrix(m, r, m);
    PlatVu0MulMatrix(m, arg0, m);
    func_00f68770(1, 1, m, scale, D_00F87058);
    D_00FBAA58 = 1;
}
