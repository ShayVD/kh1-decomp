/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00121eb0(s32);
M2C_UNK func_00164ba8(void *, s32);

s32 func_00162368(void ***arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x30) + M2C_FIELD(**arg0, s32 *, 4)), s32 *, 0x2C) & 0x3FF;
}

void func_001675c0(void *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a1;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x15C);
    if (temp_a0 != 0) {
        func_00121eb0(temp_a0);
    }
    temp_a0_2 = M2C_FIELD(arg0, s32 *, 0x160);
    if (temp_a0_2 != 0) {
        func_00121eb0(temp_a0_2);
    }
    temp_a0_3 = M2C_FIELD(arg0, s32 *, 0x164);
    if (temp_a0_3 != 0) {
        func_00121eb0(temp_a0_3);
    }
    temp_a0_4 = M2C_FIELD(arg0, s32 *, 0x168);
    if (temp_a0_4 != 0) {
        func_00121eb0(temp_a0_4);
    }
    temp_a0_5 = M2C_FIELD(arg0, s32 *, 0x16C);
    if (temp_a0_5 != 0) {
        func_00121eb0(temp_a0_5);
    }
    temp_a1 = M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x15C) = 0;
    M2C_FIELD(arg0, s32 *, 0x160) = 0;
    M2C_FIELD(arg0, s32 *, 0x164) = 0;
    M2C_FIELD(arg0, s32 *, 0x168) = 0;
    M2C_FIELD(arg0, s32 *, 0x16C) = 0;
    if (temp_a1 != 0) {
        func_00164ba8(arg0, temp_a1);
    }
}

s32 func_00167678(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}
