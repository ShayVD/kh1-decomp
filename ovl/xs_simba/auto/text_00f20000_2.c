/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0012ec60(s32, s32, void *);
M2C_UNK sceVu0SubVector(void *, void *, s32);
extern M2C_UNK D_002E31B0;
f32 atan2f(f32, f32);
f32 fabsf(f32);
f32 func_00120c88(f32);
s32 func_00122ff8(s32);

void func_00f200a0(void *arg0) {
    s32 sp[4];
    f32 temp_f0;

    if (func_00122ff8(M2C_FIELD(&D_002E31B0, s32 *, 0)) != 0) {
        func_0012ec60(M2C_FIELD(&D_002E31B0, s32 *, 0), M2C_FIELD(&D_002E31B0, s32 *, 4), sp);
        sceVu0SubVector(sp, sp, arg0 + 0x10);
        temp_f0 = atan2f(M2C_FIELD(sp, f32 *, 0x0), M2C_FIELD(sp, f32 *, 0x8));
        if (fabsf(func_00120c88(temp_f0 - M2C_FIELD(arg0, f32 *, 0x150))) > 0.523598731f) {
            M2C_FIELD(arg0, f32 *, 0x150) = temp_f0;
        }
    }
}
