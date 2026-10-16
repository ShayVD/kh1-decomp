/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00121eb0(s32);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_00162110(s32 *arg0, void **arg1) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    void *temp_s0;

    if (*arg0 == 0x4A424F4D) {
        temp_s0 = *arg1;
        func_00121eb0(M2C_FIELD(temp_s0, s32 *, 0x154));
        func_00121eb0(M2C_FIELD(temp_s0, s32 *, 0x158));
        func_00121eb0(M2C_FIELD(temp_s0, s32 *, 0x150));
        temp_a0 = M2C_FIELD(temp_s0, s32 *, 0x15C);
        if (temp_a0 != 0) {
            func_00121eb0(temp_a0);
        }
        temp_a0_2 = M2C_FIELD(temp_s0, s32 *, 0x160);
        if (temp_a0_2 != 0) {
            func_00121eb0(temp_a0_2);
        }
        temp_a0_3 = M2C_FIELD(temp_s0, s32 *, 0x164);
        if (temp_a0_3 != 0) {
            func_00121eb0(temp_a0_3);
        }
        temp_a0_4 = M2C_FIELD(temp_s0, s32 *, 0x168);
        if (temp_a0_4 != 0) {
            func_00121eb0(temp_a0_4);
        }
        temp_a0_5 = M2C_FIELD(temp_s0, s32 *, 0x16C);
        if (temp_a0_5 != 0) {
            func_00121eb0(temp_a0_5);
        }
        memset(temp_s0, 0, 0x190);
    }
}
