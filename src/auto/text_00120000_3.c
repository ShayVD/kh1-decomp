/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_004F.h"

M2C_UNK func_00121f6c(s32, s32, s32);
M2C_UNK func_0025ed48(s32, s32, s32, s32);
M2C_UNK func_002676c0(f32);
M2C_UNK func_00267768(s32, s32, f32);
M2C_UNK func_00267810(s32, s32, f32);
extern M2C_UNK D_004F45B0; /* src/data/bss_004F.c: Block D_004F45B0[0x200] */
#include "data/pieces/D_002E26A0.h"
s32 func_00120930();

void func_00120a20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0025ed48(func_00120930(), arg1, arg2, arg3);
}

void func_00120c38(s32 arg0, s32 arg1, void *arg2) {
    func_002676c0(M2C_FIELD(arg2, f32 *, 8));
    func_00267768(arg0, arg0, M2C_FIELD(arg2, f32 *, 0));
    func_00267810(arg0, arg0, M2C_FIELD(arg2, f32 *, 4));
}

s32 func_00121b98(void) {
    M2C_UNK *var_a1;
    M2C_UNK *var_s0;
    s32 temp_s1;
    s32 temp_v0;
    u32 temp_a0;
    u32 var_s2;

    var_a1 = &D_004F45B0;
    var_s0 = M2C_FIELD(&D_004F45B0, M2C_UNK **, 0x10);
    var_s2 = 0;
    if (var_s0 != NULL) {
        do {
            temp_a0 = M2C_FIELD(var_s0, u32 *, 0) + 1;
            M2C_FIELD(var_s0, u32 *, 0) = temp_a0;
            if (M2C_FIELD(var_s0, s32 **, 0xC) == NULL) {
                M2C_FIELD(var_s0, s32 *, 4) = 0;
                M2C_FIELD(var_a1, M2C_UNK **, 0x10) = (M2C_UNK *) M2C_FIELD(var_s0, M2C_UNK **, 0x10);
            } else {
                if ((var_s2 <= 0x1FFFFU) && (temp_a0 >= 4U)) {
                    temp_v0 = M2C_FIELD(var_s0, s32 *, 4);
                    temp_s1 = M2C_FIELD(var_a1, s32 *, 4) + M2C_FIELD(var_a1, s32 *, 8);
                    if ((temp_v0 - temp_s1) > 0) {
                        func_00121f6c(temp_v0, temp_s1, M2C_FIELD(var_s0, s32 *, 8));
                        M2C_FIELD(var_s0, s32 *, 4) = temp_s1;
                        *M2C_FIELD(var_s0, s32 **, 0xC) = temp_s1;
                        var_s2 += M2C_FIELD(var_s0, s32 *, 8);
                    }
                }
                var_a1 = var_s0;
            }
            var_s0 = M2C_FIELD(var_s0, M2C_UNK **, 0x10);
        } while (var_s0 != NULL);
    }
    return 0;
}
#include "data/bss_0052_mixed.h"
#include "data/data_002E.h"
