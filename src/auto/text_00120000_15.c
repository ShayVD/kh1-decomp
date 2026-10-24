/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
s32 func_00121de0(s32);

void func_00121f30(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_00121de0(arg0);
    *(M2C_UNK *)arg1 = arg0;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg1;
    M2C_FIELD(temp_v0, s32 *, 0) = 0;
}
#include "data/data_002E.h"
