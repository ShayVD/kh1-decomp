/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_00130398(s32, s32, f32);
s32 func_00137618(s32);
s32 func_001443a8(s32);
s32 func_0014f658(s32, s32);
s32 func_00153e80(s32);
s32 func_002675a8(s32, s32);
void func_00144958(s32, s32);

s32 func_00144410(s32 arg0, s32 arg1) {
    if (func_001443a8(arg0) != 0) {
        if (M2C_FIELD(arg0, s32 *, 0x164) == 0x43) {
            func_0014f658(arg0, 0x11);
            func_00153e80(arg0);
            return 1;
        }
        if (func_00137618(arg0) != 0) {
            func_0014f658(arg0, 0x11);
            func_00130398(arg0, 0x4000002D, 16.0f);
            func_002675a8(M2C_FIELD(arg0, void **, 0x148) + 0xA0, arg1);
            if (M2C_FIELD(arg1, f32 *, 0xC) > 0.0f) {
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0xB8) = 4.0f;
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0xB0) = 4e+01f;
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0xB4) = 3e+01f;
            }
            func_00144958(arg0, arg1);
            return 1;
        }
        goto block_8;
    }
block_8:
    return 0;
}
