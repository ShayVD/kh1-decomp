/* wm.x func_00f2f188: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 pad[0x20];
    OvlMtx m;
} Obj;
Obj *func_00f2cae8(s32);
void func_001be9f0(OvlVec);

void func_00f2f188(s32 arg0, s32 arg1) {
    OvlVec rot;
    OvlMtx m;
    Obj *o = func_00f2cae8(arg0);
    rot[2] = 0.0f;
    if (arg1 != 0) {
        rot[1] = 0.349065810442f;
    } else {
        rot[1] = -0.349065810442f;
    }
    rot[0] = 0.0f;
    rot[3] = 1.0f;
    func_001be9f0(rot);
    PlatVu0UnitMatrix(m);
    PlatVu0RotMatrixY(m, m, rot[1]);
    PlatVu0RotMatrixZ(m, m, rot[2]);
    PlatVu0MulMatrix(o->m, o->m, m);
}
