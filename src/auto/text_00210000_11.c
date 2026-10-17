/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_001f94f0(s32, s32, s32, s32, s32, s32, s32);
s32 func_0021b800(s32);
void func_0021b860(s32, s32, s32, s32, s32, s32);

s32 func_0021cbc8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_s2;

    func_0021b860(arg0, arg1 - 0x19, arg2 - 6, 0, 0, 0x22);
    temp_s2 = arg3 - 0x28;
    func_0021b860(arg0, arg1, arg2, 0, 0, 0x23);
    func_0021b860(arg0, arg1 + 0x14, arg2, temp_s2, 0, 0x25);
    func_0021b860(arg0, arg1 + temp_s2 + 0x14, arg2, 0, 0, 0x24);
    return func_001f94f0(arg0, 0, arg1 + 8, arg2 + 2, func_0021b800(arg4), 0xF, arg5);
}
