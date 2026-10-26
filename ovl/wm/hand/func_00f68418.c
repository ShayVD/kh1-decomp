/* wm.x func_00f68418: matched by hand. */
#include "ovl.h"

void func_00f68418(OvlMtx m, OvlVec t, s32 *r) {
    OvlVec rot;
    rot[0] = r[0] * 3.141592503f * (1.0f / 32768.0f);
    rot[1] = r[1] * 3.141592503f * (1.0f / 32768.0f);
    rot[2] = r[2] * 3.141592503f * (1.0f / 32768.0f);
    rot[3] = 1.0f;
    PlatVu0UnitMatrix(m);
    PlatVu0RotMatrixX(m, m, rot[0]);
    PlatVu0RotMatrixY(m, m, rot[1]);
    PlatVu0RotMatrixZ(m, m, rot[2]);
    PlatVu0TransMatrix(m, m, t);
}
