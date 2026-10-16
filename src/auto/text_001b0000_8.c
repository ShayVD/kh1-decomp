/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK puts(M2C_UNK *);
extern M2C_UNK D_0048FFF0;
extern M2C_UNK D_00490000;
extern M2C_UNK func_001ba7b8;
extern s32 D_003772D4;
extern s32 D_003772DC;
extern s32 D_003773EC;
void func_001b9c60(s32);
void func_001ba6f8(void);
void func_001ba910(s32);

void func_001ba7e0(void) {
    D_003773EC = 1;
    D_003772DC = 1;
    func_001ba6f8();
    puts(&D_0048FFF0);
    func_001b9c60((s32) &D_00490000);
    func_001ba910((s32) &func_001ba7b8);
    D_003772D4 += 1;
}

s32 func_001baf08(s32 *arg0) {
    s32 *var_a0;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v1;

    var_a0 = arg0;
    var_a1 = 0;
    var_v1 = 7;
    do {
        temp_v0 = *var_a0;
        var_a0 += 1;
        var_v1 -= 1;
        var_a1 += temp_v0;
    } while (var_v1 >= 0);
    return var_a1;
}

s32 func_001baf38(s32 arg0) {
    s32 *var_a0;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v1;

    var_a0 = arg0 + 8;
    var_a1 = 0;
    var_v1 = 5;
    do {
        temp_v0 = *var_a0;
        var_a0 += 1;
        var_v1 -= 1;
        var_a1 += temp_v0;
    } while (var_v1 >= 0);
    return var_a1;
}

void func_001be9f0(f32 *arg0) {
    f32 *var_a0;
    f32 temp_f0;
    f32 var_f1;
    s32 var_v0;

    var_a0 = arg0;
    var_v0 = 3;
    do {
        var_f1 = *var_a0;
        if (var_f1 < -3.141592503f) {
            temp_f0 = var_f1 + 6.28318501f;
            *var_a0 = temp_f0;
            var_f1 = temp_f0;
        }
        var_v0 -= 1;
        if (var_f1 > 3.141592503f) {
            *var_a0 = var_f1 - 6.28318501f;
        }
        var_a0 += 1;
    } while (var_v0 >= 0);
}

void func_001bf290(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0xC) = 1.0f;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
}
