/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK sceVu0AddVector(s32, s32, M2C_UNK *);
M2C_UNK sceVu0CopyVector(void *);
M2C_UNK sceVu0ScaleVectorXYZ(M2C_UNK *, void *, f32);
extern M2C_UNK D_00FC1DE0;
extern M2C_UNK func_00f22010;

void func_00f22258(void) {
    memset(&D_00FC1DE0, 0, 0x1040);
    func_0011ef10(0x21728, &func_00f22010);
}

void func_00f22530(s32 arg0, f32 fparg0) {
    s32 sp[8];
    sceVu0CopyVector(sp);
    M2C_FIELD(sp, s32 *, 0xC) = 0;
    sceVu0ScaleVectorXYZ(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, fparg0);
    sceVu0AddVector(arg0, arg0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
}
