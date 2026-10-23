/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_001fd858();
M2C_UNK func_001fdfd0(s32);
s32 func_001fe1b8();
s32 func_001fe5a0();

s32 func_001fd518(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s16 *, 0xD2) + (M2C_FIELD(arg0, u16 *, 0xD0) & 0xF) + 8) >> 4;
}

s32 func_001fd538(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s16 *, 0xDA) + 8) >> 4;
}

void func_001fd610(void *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xCE) = arg1;
}

s32 func_001fd638(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s16 *, 0xD2) + 8) >> 4;
}

void func_001fd648(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xD2) = (s16) (arg1 * 0x10);
}

s16 func_001fd658(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0xD8);
}

void func_001fd660(void *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0xD8) = arg1;
}

s32 func_001fd668(void *arg0) {
    return (s32) (M2C_FIELD(arg0, s16 *, 0xDA) + 8) >> 4;
}

void func_001fd678(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0xDA) = (s16) (arg1 * 0x10);
}

void func_001fe158(s32 arg0) {
    func_001fd858();
    func_001fdfd0(arg0);
}

void func_001fe180(void) {
    if (func_001fe1b8() != 0) {
        func_0011d768(1);
    }
}

s32 func_001fe570(void) {
    s32 var_v0;

    var_v0 = func_001fe5a0();
    if (var_v0 != 0) {
        func_0011d768(2);
        var_v0 = 1;
    }
    return var_v0;
}
