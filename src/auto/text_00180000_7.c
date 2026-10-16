/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_002672f8(s32, M2C_UNK *, s32);
M2C_UNK func_00267328(s32, M2C_UNK *, s32);
M2C_UNK func_00267560(s32, s32, f32);
extern M2C_UNK D_003701F0;
extern M2C_UNK D_00615FC0;
extern M2C_UNK D_00616040;
extern M2C_UNK D_00616080;
extern s32 D_00615E68;

void func_00185ee8(void) {
    func_00267328(D_00615E68 + 0x50, &D_00616080, D_00615E68 + 0x10);
}

void func_00185f18(void) {
    s32 temp_a0;

    func_00267560(D_00615E68 + 0x50, D_00615E68 + 0x10, M2C_FIELD(&D_003701F0, f32 *, 0));
    func_00267560(D_00615E68 + 0x60, D_00615E68 + 0x20, M2C_FIELD(&D_003701F0, f32 *, 4));
    func_00267560(D_00615E68 + 0x70, D_00615E68 + 0x30, M2C_FIELD(&D_003701F0, f32 *, 8));
    func_002672f8(D_00615E68 + 0x80, &D_00615FC0, D_00615E68 + 0x40);
    temp_a0 = D_00615E68 + 0x50;
    func_00267328(temp_a0, &D_00616040, temp_a0);
}
