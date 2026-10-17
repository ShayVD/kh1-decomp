/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00615E70;
extern s32 D_00615E68;
void func_002672f8(void *, M2C_UNK *, void *);

void func_00199908(void *arg0, void *arg1, void *arg2) {
    s32 sp[4];    f32 temp_f20;

    temp_f20 = M2C_FIELD(arg0, f32 *, 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    M2C_FIELD(sp, s32 *, 0x0) = 0;
    M2C_FIELD(sp, s32 *, 0x8) = 0;
    M2C_FIELD(sp, f32 *, 0x4) = temp_f20 * 0.5f;
    func_002672f8(arg1, D_00615E68 + 0x10, sp);
    M2C_FIELD(sp, f32 *, 0x4) = -temp_f20 * 0.5f;
    func_002672f8(arg2, D_00615E68 + 0x10, sp);
    if (M2C_FIELD(arg0, u8 *, 0x15) != 0) {
        func_002672f8(arg1, &D_00615E70, arg1);
        func_002672f8(arg2, &D_00615E70, arg2);
    }
}
