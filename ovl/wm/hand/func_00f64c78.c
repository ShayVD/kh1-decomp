/* wm.x func_00f64c78: matched by hand. */
#include "ovl.h"

void func_00f64c78(s32 arg0) {
    u32 var_a3;
    void *temp_a4;
    void *var_a0;
    void *var_a1;
    void *var_v1;

    var_a3 = 0;
    temp_a4 = M2C_FIELD(arg0, void **, 0xC) + arg0;
    var_a0 = M2C_FIELD(arg0, void **, 0x14) + arg0;
    var_a1 = M2C_FIELD(arg0, void **, 0x1C) + arg0;
    M2C_FIELD(arg0, void **, 0xC) = temp_a4;
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + arg0);
    M2C_FIELD(arg0, void **, 0x14) = var_a0;
    M2C_FIELD(arg0, void **, 0x1C) = var_a1;
    if (M2C_FIELD(arg0, u32 *, 8) != 0) {
        var_v1 = temp_a4;
        do {
            var_a3 += 1;
            M2C_FIELD(var_v1, s32 *, 8) = (s32) (M2C_FIELD(var_v1, s32 *, 8) + arg0);
            var_v1 += 0xC;
        } while (var_a3 < (u32) M2C_FIELD(arg0, u32 *, 8));
    }
    var_a3 = 0;
    if (M2C_FIELD(arg0, u32 *, 0x10) != 0) {
        do {
            var_a3 += 1;
            M2C_FIELD(var_a0, s32 *, 4) = (s32) (M2C_FIELD(var_a0, s32 *, 4) + arg0);
            var_a0 += 8;
        } while (var_a3 < (u32) M2C_FIELD(arg0, u32 *, 0x10));
    }
    var_a3 = 0;
    if (M2C_FIELD(arg0, u32 *, 0x18) != 0) {
        do {
            var_a3 += 1;
            M2C_FIELD(var_a1, s32 *, 8) = (s32) (M2C_FIELD(var_a1, s32 *, 8) + arg0);
            var_a1 += 0xC;
        } while (var_a3 < (u32) M2C_FIELD(arg0, u32 *, 0x18));
    }
}
