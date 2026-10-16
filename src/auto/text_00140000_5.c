/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00141e68(s32);
M2C_UNK func_00149170(s32, s32);
M2C_UNK func_0014cc38();
M2C_UNK func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK *);
M2C_UNK func_00176310(M2C_UNK *);
M2C_UNK func_002675a8(s32, s32);
extern M2C_UNK D_002E26A0;
extern M2C_UNK D_00547C00;
extern M2C_UNK func_00144350;
extern M2C_UNK func_00144958;
extern M2C_UNK func_00144ce0;
extern M2C_UNK func_00144d08;
extern M2C_UNK func_00148bc0;
s32 *func_00147c98();
s32 func_00121e28(s32, s32);
s32 func_0013daa8(s32);
s32 func_00147d18(s32);

void func_00144e38(void) {
    func_0014f830(0x11, 1, &func_00144350, 0, &func_00144958, &func_00144ce0, 0, 0, &func_00144d08);
}

s32 * func_00147ed8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *temp_v0;

    temp_v0 = func_00147c98();
    if (temp_v0 != NULL) {
        func_002675a8(*temp_v0, arg3);
    }
    return temp_v0;
}

s32 func_00148cb0(s32 arg0, f32 fparg0) {
    s32 temp_v0;

    temp_v0 = func_00147d18((s32) &func_00148bc0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
        M2C_FIELD(temp_v0, f32 *, 0x1C) = fparg0;
        return func_00121e28(0x70, temp_v0 + 0x20);
    }
    return temp_v0;
}

void func_00148e98(void) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = &D_00547C00;
    var_s1 = 0xFF;
    do {
        if ((var_s0 != NULL) && ((M2C_FIELD(var_s0, s32 *, 0x14) & 3) == 1)) {
            func_00176310(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x3C;
    } while (var_s1 >= 0);
}

void func_00149600(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_0013daa8(arg1);
    if (temp_v0 >= 0) {
        func_00141e68(*(M2C_UNK *)((s8 *)&D_002E26A0 + (temp_v0 * 4)));
    }
    func_00149170(arg0, arg1 | 0x10000);
}

f32 func_0014cc88(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x3B8) = fparg0;
    M2C_FIELD(arg0, f32 *, 0x3BC) = (f32) (fparg0 * fparg0 * -0.48469386f * 0.5f);
    func_0014cc38();
    return -M2C_FIELD(arg0, f32 *, 0x3BC);
}
