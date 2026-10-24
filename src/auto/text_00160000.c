/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00161a08();

void func_00162058(void) {
    func_00161a08();
}

s16 func_00162338(s16 ***arg0) {
    return ***arg0;
}

s32 func_00162348(void ***arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 4) + M2C_FIELD(**arg0, s32 *, 8)), s32 *, 0x10);
}

void func_001623d0(void *arg0, s32 *arg1) {
    *arg1 = M2C_FIELD(arg0, s32 *, 0x30);
}

s32 func_001623e0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x154);
}

u32 func_001623e8(void *arg0) {
    return (u32) M2C_FIELD(arg0, u32 *, 0xC) >> 4;
}

s32 func_00167680(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

s32 func_00167698(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (arg0 != NULL) {
        var_v0 = M2C_FIELD(arg0, s32 *, 4);
    }
    return var_v0;
}

void func_001676b0(void *arg0, void *arg1) {
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x90);
    M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD(arg0, f32 *, 0x94);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD(arg0, f32 *, 0x98);
    M2C_FIELD(arg1, f32 *, 0xC) = (f32) M2C_FIELD(arg0, f32 *, 0x9C);
}
