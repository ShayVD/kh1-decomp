/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00237018(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_002370c8(M2C_UNK *);
M2C_UNK func_00248140(s32 *);
M2C_UNK func_00248238(s32 *);
M2C_UNK func_002490f0(s32 *);
extern M2C_UNK D_00426850;
extern M2C_UNK D_00469FC8;
M2C_UNK D_00669070[0x58] ALIGNED(16);
extern s32 D_00469F60;
extern s32 D_00662A30;
extern s32 D_00669350;
s32 func_0023d700(s32, s32, s32, s32, s32, f32);
s32 memcpy(s32, s32, s32);

s32 func_00240ae0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    if (!(M2C_FIELD(arg0, s32 *, 0x250) != 0)) {
        return arg3;
    }
    return func_0023d700(M2C_FIELD(arg0, s32 *, 0), (s32) &D_00426850, arg1, arg2, arg3, fparg0);
    return arg3;
}

s32 func_00245f18(void) {
    s32 *var_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_v0;

    var_a1 = 0;
    var_a0 = &D_00662A30;
loop_1:
    temp_v1 = *var_a0;
    var_a0 += 536;
    var_v0 = 1;
    if (temp_v1 != 0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 0xA) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

s32 func_00248380(void) {
    if (D_00669350 == 0) {
        return 0;
    }
    func_002370c8(&D_00669070);
    M2C_FIELD(&D_00669070, s64 *, 0xE0) = 5;
    M2C_FIELD(&D_00669070, s64 *, 0x60) = 0x30003;
    func_00237018(&D_00669070, 0x16, 1);
    func_00248140(&D_00669350);
    func_00248238(&D_00669350);
    return 0;
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
