/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK memset(s32, M2C_UNK, s32);
extern s32 D_00615E64;
s32 func_0017f958(s32, s32);

void pppRyjMegaPlaceFrame(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    void *temp_a0;
    void *temp_s0;

    temp_a0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
    temp_s0 = temp_a0 + 0xA0;
    if (M2C_FIELD(temp_s0, s32 *, 0xC) == 0) {
        temp_v0 = M2C_FIELD(temp_a0, s32 *, 0xA0);
        if (temp_v0 != 0) {
            temp_v0_2 = func_0017f958(D_00615E64, temp_v0 << 5);
            M2C_FIELD(temp_s0, s32 *, 0xC) = temp_v0_2;
            memset(temp_v0_2, 0, M2C_FIELD(temp_a0, s32 *, 0xA0) << 5);
        }
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x10) == 0) {
        temp_a1 = M2C_FIELD(temp_s0, s32 *, 4);
        if (temp_a1 != 0) {
            temp_v0_3 = func_0017f958(D_00615E64, temp_a1 << 5);
            M2C_FIELD(temp_s0, s32 *, 0x10) = temp_v0_3;
            memset(temp_v0_3, 0, M2C_FIELD(temp_s0, s32 *, 4) << 5);
        }
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x14) == 0) {
        temp_v1 = M2C_FIELD(temp_s0, s32 *, 8);
        if (temp_v1 != 0) {
            temp_v0_4 = func_0017f958(D_00615E64, temp_v1 * 0x30);
            M2C_FIELD(temp_s0, s32 *, 0x14) = temp_v0_4;
            memset(temp_v0_4, 0, M2C_FIELD(temp_s0, s32 *, 8) * 0x30);
        }
    }
}
#include "data/bss_0061_mixed.h"
