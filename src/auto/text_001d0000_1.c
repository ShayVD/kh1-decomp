/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_00125a28(s32);
void *func_00232cc0(M2C_UNK);

s32 func_001d0b10(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180) = func_00125a28(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180));
    return 2;
}

s32 func_001dc308(void *arg0) {
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = func_00232cc0(1);
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x180) + 1;
    M2C_FIELD(arg0, s32 *, 0x180) = temp_v1;
    M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x184) = (s32) (((u32) M2C_FIELD(temp_v0, u32 *, 0xDC4) >> 4) & 1);
    return 2;
}
