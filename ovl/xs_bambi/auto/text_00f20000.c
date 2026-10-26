/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00f20348();
M2C_UNK sceVu0CopyVector(s32, s32);
extern M2C_UNK *D_00304B6C;
extern M2C_UNK D_00F20A10;
extern M2C_UNK func_00f203d8;
extern void *D_00F20900;
s32 func_00f20838(s32, s32, s32);
void func_0013aaa0(void);

void func_00f20390(s32 arg0) {
    if (M2C_FIELD(D_00F20900, s32 *, 0x70) == 8) {
        func_0013aaa0();
        return;
    }
    func_00f20838((s32) &D_00F20A10, 1, arg0 + 0x10);
}

void func_00f20550(void) {
    func_00f20348();
    D_00304B6C = &func_00f203d8;
}

void func_00f20600(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg2;
    sceVu0CopyVector(arg1, arg3);
}
