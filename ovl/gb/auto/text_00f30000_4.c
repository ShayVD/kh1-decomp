/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001bbbd0(M2C_UNK *, s32);
M2C_UNK func_001bbce0(M2C_UNK *, s32);
M2C_UNK sceVu0MulMatrix(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK sceVu0RotMatrixX(M2C_UNK *, M2C_UNK *, f32);
M2C_UNK sceVu0UnitMatrix(M2C_UNK *);

void func_00f36c80(M2C_UNK *arg0, M2C_UNK *arg1, M2C_UNK *arg2, M2C_UNK *arg3, s32 arg4) {
    s32 sp[32];
    func_001bbbd0(sp, arg4);
    func_001bbce0(&M2C_FIELD(sp, M2C_UNK *, 0x40), arg4);
    sceVu0UnitMatrix(arg0);
    sceVu0RotMatrixX(arg0, arg0, 3.141592503f);
    sceVu0MulMatrix(sp, sp, arg0);
    sceVu0MulMatrix(arg1, arg3, sp);
    sceVu0MulMatrix(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x40), sp);
    sceVu0MulMatrix(arg0, arg2, arg0);
}
