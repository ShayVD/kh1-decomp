/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

f32 func_001376e8(s32, s32);
s32 func_002675a8(s32, s32);

void func_00153bb0(s32 arg0, s32 arg1) {
    if ((M2C_FIELD(arg1, f32 *, 0) != 0.0f) && (M2C_FIELD(arg1, f32 *, 8) != 0.0f)) {
        func_001376e8(arg0, arg1);
        func_002675a8(arg0 + 0x20, arg1);
        return;
    }
    func_002675a8(arg0 + 0x20, arg0 + 0x30);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}
