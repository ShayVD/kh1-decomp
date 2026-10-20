/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00176310(s32);
M2C_UNK func_00176340(s32);
M2C_UNK func_0017fae8(s32);
M2C_UNK func_0017fb40(s32);
extern M2C_UNK D_0035BE50;
extern M2C_UNK D_00362660;
extern M2C_UNK D_003626F8;
extern M2C_UNK func_0014f828;
extern M2C_UNK func_00172028;
extern M2C_UNK func_001732b0;
extern M2C_UNK func_00173360;
extern M2C_UNK func_00173478;
extern f32 D_00362674;
f32 func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK, s32);
void func_0017f178(void);

void func_00172d90(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x18) = 0x17;
    M2C_FIELD(arg1, M2C_UNK **, 0x1C) = &D_0035BE50;
    func_0014f830(0x32, 2, &func_00172028, &func_001732b0, &func_00173360, &func_00173478, &func_0014f828, 0, 0);
}

void func_00175e38(s32 arg0) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0 + 0xC;
    var_s1 = 0x3F;
    var_a0 = var_s0;
    do {
        var_s1 -= 1;
        func_00176340(var_a0);
        var_s0 += 0x3C;
        var_a0 = var_s0;
    } while (var_s1 >= 0);
}

void func_00175e80(s32 arg0) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0 + 0xC;
    var_s1 = 0x3F;
    var_a0 = var_s0;
    do {
        var_s1 -= 1;
        func_00176310(var_a0);
        var_s0 += 0x3C;
        var_a0 = var_s0;
    } while (var_s1 >= 0);
}

void func_00175ec8(s32 arg0) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0 + 0xC;
    var_s1 = 0x3F;
    var_a0 = var_s0;
    do {
        var_s1 -= 1;
        func_0017fae8(var_a0);
        var_s0 += 0x3C;
        var_a0 = var_s0;
    } while (var_s1 >= 0);
}

void func_00175f10(s32 arg0) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0 + 0xC;
    var_s1 = 0x3F;
    var_a0 = var_s0;
    do {
        var_s1 -= 1;
        func_0017fb40(var_a0);
        var_s0 += 0x3C;
        var_a0 = var_s0;
    } while (var_s1 >= 0);
}

s32 func_00176530(void *arg0, s32 *arg1) {
    s32 *var_a1;
    s32 temp_v0;
    s32 var_a2;
    s32 var_a3;
    void *var_v1;

    var_a1 = arg1;
    var_v1 = arg0 + 0x10;
    var_a2 = 0;
    var_a3 = 0;
    if (M2C_FIELD(arg0, s32 *, 0xC) > 0) {
        do {
            temp_v0 = M2C_FIELD(var_v1, s32 *, 8);
            var_v1 += 0x20;
            var_a2 += 1;
            var_a3 += 1;
            *var_a1 = temp_v0;
            var_a1 += 1;
        } while (var_a2 < M2C_FIELD(arg0, s32 *, 0xC));
    }
    return var_a3;
}

void func_0017f110(void) {
    M2C_FIELD(&D_00362660, f32 *, 0) = (f32) M2C_FIELD(&D_003626F8, f32 *, 0);
    M2C_FIELD(&D_00362660, f32 *, 0xC) = (f32) M2C_FIELD(&D_003626F8, f32 *, 4);
    D_00362674 = M2C_FIELD(&D_003626F8, f32 *, 8);
    func_0017f178();
}
#include "data/data_0036.h"
