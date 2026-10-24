/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_002490f0(s32 *);
#include "data/pieces/D_00426850.h"
extern M2C_UNK D_00469FC8[];
extern s32 D_00469F60;
s32 func_0023d700(s32, s32, s32, s32, s32, f32);
s32 memcpy(s32, s32, s32);

s32 func_00240ae0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    if (!(M2C_FIELD(arg0, s32 *, 0x250) != 0)) {
        return arg3;
    }
    return func_0023d700(M2C_FIELD(arg0, s32 *, 0), (s32) &D_00426850, arg1, arg2, arg3, fparg0);
    return arg3;
}

s32 func_002491f8(void) {
    if (D_00469F60 == 0) {
        return 0;
    }
    func_002490f0(&D_00469F60);
    return 0;
}

void func_00249820(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_a2;

    var_a2 = 0;
    do {
        temp_v0 = var_a2 * 4;
        var_a2 += 1;
        *(M2C_UNK *)((s32) temp_v0 + (s32) arg0) = *(M2C_UNK *)((s32) temp_v0 + (s32) arg1);
    } while (var_a2 < 4);
}

s32 func_0024b0c8(s32 arg0, s32 arg1, s32 arg2) {
    u32 wide;
    s32 temp_s0;

    wide = M2C_FIELD(arg0, u8 *, 1);

    temp_s0 = wide + (M2C_FIELD(arg0, u8 *, 4) << 0x18) + ((M2C_FIELD(arg0, u8 *, 3) << 0x10) + (M2C_FIELD(arg0, u8 *, 2) << 8));
    memcpy(arg1, arg0 + 5, temp_s0);
    *(M2C_UNK *)arg2 = temp_s0;
    return temp_s0;
}

s32 func_0024b138(s32 arg0, u8 *arg1) {
    s32 sp[4];
    (*(M2C_UNK (**)())((s32) &D_00469FC8 + (s32) ((*arg1 * 4))))(arg1, arg0, sp);
    return M2C_FIELD(sp, M2C_UNK *, 0x0);
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_0024e75c();
void func_0024e8d4();
M2C_UNK D_00469FC8[0x4] ALIGNED(8) = {
    (s32)func_0024b0c8, (s32)func_0024e75c, (s32)func_0024e8d4, 0,
};
#include "data/data_0046.h"
