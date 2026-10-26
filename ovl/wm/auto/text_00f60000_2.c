/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00FB4F78;
extern f32 D_0108EEC8;
extern f32 D_0108EECC;
extern f32 D_0108EED0;
extern f32 D_0108EED4;
extern s32 D_00FB49E8;
void func_0024bc08(s32, s32);

void func_00f66990(s32 arg0, s32 arg1, void *arg2) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    D_0108EEC8 = (f32) arg1;
    D_0108EECC = temp_f0;
    D_0108EED4 = (temp_f0 * M2C_FIELD(arg2, f32 *, 0x28)) + M2C_FIELD(arg2, f32 *, 0x38);
    D_0108EED0 = 1.0f / temp_f0;
}

s32 func_00f68140(s32 arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (arg0 < 0) {
        return var_v0;
    }
    var_v0 = M2C_FIELD(((arg0 * 0x48) + D_00FB49E8), s32 *, 0x14) != 0;
    return var_v0;
}

void func_00f6a428(s32 arg0) {
    func_0024bc08(arg0, (s32) &D_00FB4F78);
}
