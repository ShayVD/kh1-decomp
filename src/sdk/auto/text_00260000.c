/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK RemoveDmacHandler(M2C_UNK, s32);
M2C_UNK free(s32);
M2C_UNK func_00258d10(M2C_UNK);
M2C_UNK func_00263db8(s32, s32);
M2C_UNK func_00263e50(s32, s32);
M2C_UNK func_00266ab0();
extern M2C_UNK D_0046C500;
extern M2C_UNK D_0066E6D8;
extern s32 D_0046A9C8;
extern s32 D_0046BE8C;
extern s32 D_0066E6D4;
extern s32 D_0066FAC8;
s32 func_00262bb8(void);
s32 func_00263ee8();
s32 malloc(M2C_UNK);

s32 func_002600a0(s32 arg0, s32 arg1) {
    s32 *temp_v0;

    temp_v0 = (M2C_FIELD(arg0, s32 *, 0x10) * 4) + M2C_FIELD(arg1, s32 *, 0x1C);
    *temp_v0 = M2C_FIELD(arg0, s32 *, 0x14);
    return (s32) temp_v0;
}

void func_002600c0(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x10);
}

M2C_UNK *func_00260108(void) {
    return &D_0066E6D8;
}

void func_00260398(void) {
    func_00258d10(5);
    RemoveDmacHandler(5, D_0066E6D4);
    D_0046BE8C = 0;
}

void func_00262c78(void) {
    if (D_0066FAC8 == 0) {
        D_0066FAC8 = 1;
        func_00262bb8();
    }
}

u8 *func_002636a8(u8 *arg0, s32 *arg1) {
    s32 var_a2;
    s32 var_a3;
    u8 *var_a0;
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = *arg0;
    var_a0 = arg0 + 1;
    var_a3 = 0;
    var_a2 = temp_v1 & 0x7F;
    if (temp_v1 & 0x80) {
        do {
            temp_v1_2 = *var_a0;
            var_a0 += 1;
            var_a3 += 7;
            var_a2 |= (temp_v1_2 & 0x7F) << var_a3;
        } while (temp_v1_2 & 0x80);
    }
    *arg1 = var_a2;
    return var_a0;
}

u8 *func_002636f0(u8 *arg0, s32 *arg1) {
    s32 temp_v0;
    s32 var_a4;
    u32 var_a3;
    u8 *var_a0;
    u8 temp_a2;

    var_a0 = arg0;
    var_a3 = 0;
    var_a4 = 0;
    do {
        temp_a2 = *var_a0;
        var_a0 += 1;
        temp_v0 = (temp_a2 & 0x7F) << var_a3;
        var_a3 += 7;
        var_a4 |= temp_v0;
    } while (temp_a2 & 0x80);
    if ((var_a3 < 0x20U) && (temp_a2 & 0x40)) {
        var_a4 |= -1 << var_a3;
    }
    *arg1 = var_a4;
    return var_a0;
}

void func_00263e20(s32 arg0) {
    func_00263db8(arg0, malloc(0x18));
}

void func_00263eb8(s32 arg0) {
    func_00263e50(arg0, malloc(0x18));
}

void func_00263fa8(void) {
    free(func_00263ee8());
}

M2C_UNK *func_002654e0(void) {
    return &D_0046C500;
}

s32 func_00266f20(s32 arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)0x1000E060;
    *(s32 *)0x1000E060 = arg0;
    return temp_v0;
}

s32 func_002671d8(u32 *arg0, s32 arg1) {
    if (arg1 == 1) {
        return ((u32) *arg0 >> 8) & 1;
    }
    func_00266ab0();
    return 0;
}

s32 func_002672e0(u32 *arg0, u32 arg1) {
    u32 temp_v0;

    temp_v0 = *arg0;
    *arg0 = arg1;
    return (temp_v0 >> 8) & 1;
}

void func_00267e40(void *arg0, void *arg1) {
    M2C_FIELD(arg0, f32 *, 0) = (f32) M2C_FIELD(arg1, f32 *, 0);
    M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 4);
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(arg1, f32 *, 8);
}

s32 func_00268230(void) {
    return 1;
}
