/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00121ee0(s32);
extern M2C_UNK func_001001d8;
extern M2C_UNK func_001001f8;
void *func_0011ef10(M2C_UNK, M2C_UNK *);

void func_00100228(void) {
    M2C_FIELD(func_0011ef10(0x270FE, &func_001001d8), s16 *, 2) = -1;
    M2C_FIELD(func_0011ef10(0x2D29E, &func_001001f8), s16 *, 2) = -1;
}

void func_0010e3f0(void *arg0) {
    s32 temp_v0;

    M2C_FIELD(arg0, s8 *, 0x12) = 0;
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x20);
    if (temp_v0 != 0) {
        func_00121ee0(temp_v0);
        M2C_FIELD(arg0, s32 *, 0x20) = 0;
    }
}
