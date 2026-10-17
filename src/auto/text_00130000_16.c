/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern void *D_0052AE58;
void func_00132260(s32, s32, s32);

void func_0013b9c8(s32 arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(D_0052AE58, s32 *, 8);
    func_00132260(arg0, (s32) (D_0052AE58 + M2C_FIELD(D_0052AE58, s32 *, 4)), (s32) (((M2C_FIELD(D_0052AE58, s32 *, 0xC) - temp_v1) <= 0) ? NULL : (D_0052AE58 + temp_v1)));
}
