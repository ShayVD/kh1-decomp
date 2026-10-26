/* wm.x func_00f5dd78: matched by hand. */
#include "ovl.h"

void func_001bbbd0(OvlMtx, s32);
void func_001bbce0(OvlMtx, s32);

void func_00f5dd78(OvlMtx arg0, OvlMtx arg1, OvlMtx arg2, OvlMtx arg3, s32 arg4) {
    OvlMtx m;
    OvlMtx n;
    func_001bbbd0(m, arg4);
    func_001bbce0(n, arg4);
    PlatVu0UnitMatrix(arg0);
    PlatVu0RotMatrixX(arg0, arg0, 3.141592503f);
    PlatVu0MulMatrix(m, m, arg0);
    PlatVu0MulMatrix(arg1, arg3, m);
    PlatVu0MulMatrix(arg0, n, m);
    PlatVu0MulMatrix(arg0, arg2, arg0);
}
