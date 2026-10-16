/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_002676c0(s32, s32, f32);
M2C_UNK func_00267768(f32);
M2C_UNK func_00267810(s32, s32, f32);

void func_00236d98(s32 arg0, s32 arg1, void *arg2) {
    func_00267768(M2C_FIELD(arg2, f32 *, 0));
    func_00267810(arg0, arg0, M2C_FIELD(arg2, f32 *, 4));
    func_002676c0(arg0, arg0, M2C_FIELD(arg2, f32 *, 8));
}
