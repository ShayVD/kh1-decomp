/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00121eb0(s32);
M2C_UNK func_00167f68(s32, void *);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_0056A0F0; /* src/data/bss_0056.c: Ent59 D_0056A0F0[96] */
s32 func_001617c0();
s32 func_001681b8(s32, s32);

void func_00161f80(void) {
    s8 *var_s0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 var_s1;

    var_s0 = &D_0056A0F0;
    var_s1 = 0x5F;
    do {
        if (M2C_FIELD(var_s0, s32 *, 0) != 0) {
            func_00121eb0(M2C_FIELD(var_s0, s32 *, 0x154));
            func_00121eb0(M2C_FIELD(var_s0, s32 *, 0x158));
            func_00121eb0(M2C_FIELD(var_s0, s32 *, 0x150));
            temp_a0 = M2C_FIELD(var_s0, s32 *, 0x15C);
            if (temp_a0 != 0) {
                func_00121eb0(temp_a0);
            }
            temp_a0_2 = M2C_FIELD(var_s0, s32 *, 0x160);
            if (temp_a0_2 != 0) {
                func_00121eb0(temp_a0_2);
            }
            temp_a0_3 = M2C_FIELD(var_s0, s32 *, 0x164);
            if (temp_a0_3 != 0) {
                func_00121eb0(temp_a0_3);
            }
            temp_a0_4 = M2C_FIELD(var_s0, s32 *, 0x168);
            if (temp_a0_4 != 0) {
                func_00121eb0(temp_a0_4);
            }
            temp_a0_5 = M2C_FIELD(var_s0, s32 *, 0x16C);
            if (temp_a0_5 != 0) {
                func_00121eb0(temp_a0_5);
            }
            memset(var_s0, 0, 0x190);
        }
        var_s1 -= 1;
        var_s0 += 0x190;
    } while (var_s1 >= 0);
}

void func_00162070(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    if (M2C_FIELD(arg0, s32 *, 0) == 0x4A424F4D) {
        *arg3 = func_001617c0();
        *arg1 = M2C_FIELD(arg0, s32 *, 0x20);
        *arg2 = M2C_FIELD(arg0, s32 *, 0x30);
        func_00167f68(*arg3, arg0);
        return;
    }
    *arg1 = M2C_FIELD(arg0, s32 *, 0x20);
}

void func_00167688(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    M2C_FIELD(arg0, s32 *, 0x88) = arg2;
}

s32 func_001684e0(s32 arg0) {
    return func_001681b8(arg0, 0x41584554);
}
