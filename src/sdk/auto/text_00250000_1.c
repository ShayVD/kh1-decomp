/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00257b98(s32, s16);
M2C_UNK func_0025f9a8(s32);
extern M2C_UNK func_00255708;
extern void *D_0046A9C8;
void func_00255538(void *, M2C_UNK, M2C_UNK, void *);

void srand(s64 arg0) {
    M2C_FIELD(D_0046A9C8, u64 *, 0xA8) = (u64) ((u64) (arg0 << 0x20) >> 0x20);
}

s32 func_00258918(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x48) = 0;
    M2C_FIELD(arg1, s32 *, 4) = 0x2000;
    return 0;
}

s32 func_00258930(void) {
    return 1;
}

s32 func_00258938(s32 arg0, s32 arg1) {
    if (arg0 == 1) {
        func_0025f9a8(arg1);
    }
    return 0;
}
