/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011d350(s32, s32);
M2C_UNK func_00147260(s32);
s32 func_001471e8();

void func_00147338(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_001471e8();
    if (temp_v0 != 0) {
        func_0011d350(arg0, arg1);
        func_00147260(temp_v0);
    }
}
