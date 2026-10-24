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

s32 func_00123118(void *arg0, void *arg1) {
    s32 temp_a1;
    s32 var_v1;

    var_v1 = 0;
    if (!(M2C_FIELD(arg1, s32 *, 0) & 0x200)) {
        temp_a1 = (s32) ((u64) M2C_FIELD(arg1, u64 *, 0x370) >> 0x25) & 3;
        if (temp_a1 != 0) {
            var_v1 = temp_a1 != ((s32) ((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x25) & 3);
        }
    }
    return var_v1;
}
#include "data/data_002E.h"
