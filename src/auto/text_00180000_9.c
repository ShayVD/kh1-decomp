/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void func_0018d000(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC);
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 0x28) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0x20) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0x24) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0x2C) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x0) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x10) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x18) = 0;
}
