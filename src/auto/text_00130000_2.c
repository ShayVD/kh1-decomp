/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001394a8(s32, s32);
M2C_UNK func_001394e8(s32, s32);
#include "data/pieces/D_00304B6C.h"
#include "data/pieces/D_00304BE8.h"
f32 func_0026b9a8(f32, f32);
s32 func_0014f5c8();
s32 func_0014f600(s32);

void func_001376e8(void *arg0, void *arg1) {
    M2C_FIELD(arg0, f32 *, 0x150) = func_0026b9a8(M2C_FIELD(arg1, f32 *, 0), M2C_FIELD(arg1, f32 *, 8));
}

u16 func_00138858(s32 arg0) {
    return M2C_FIELD(((arg0 * 2) + ((s32)D_00304BE8)), u16 *, 0x580);
}

s32 func_001388e8(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) == 0x190;
}

void func_00139568(s32 arg0, s32 arg1) {
    if ((func_0014f5c8() != 0) || (func_0014f600(arg0) != 0)) {
        func_001394e8(arg0, arg1);
        return;
    }
    func_001394a8(arg0, arg1);
}

s32 func_0013a430(s32 *arg0, s32 *arg1) {
    return *arg0 - *arg1;
}

void func_0013ab08(void) {
    if ((*(M2C_UNK (*(*))())&D_00304B6C) != NULL) {
        (*(M2C_UNK (*(*))())&D_00304B6C)();
    }
}

s32 func_0013fc68(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 0;
    if (arg1 != 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

void func_0013fd10(s32 *arg0) {
    *arg0 |= 0x30;
}

void func_0013fd20(s32 *arg0) {
    *arg0 &= ~0x30;
}

void func_0013fd38(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) | 0x200000);
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) & ~1);
}
