/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001bfac8();
M2C_UNK func_001ed4b8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_00f41100(void *, M2C_UNK *, s32);
M2C_UNK func_00f417d0(s32, void *, M2C_UNK *);
extern s32 D_00F70268;
s32 func_00f41048(s32);
void func_00176310(s32);
void func_00f417a8(s32);

void func_00f40f78(void) {
    func_001ed4b8(0, 0x3000, 0x3000, 0, 0, 0);
    func_001bfac8();
}

void func_00f418f8(s32 arg0, s32 arg1) {
    s32 sp[8];
    func_00f41100(sp, &M2C_FIELD(sp, M2C_UNK *, 0x10), arg1);
    func_00f417d0(arg0, sp, &M2C_FIELD(sp, M2C_UNK *, 0x10));
}

void func_00f41948(s32 arg0) {
    if (func_00f41048(arg0) == 0) {
        if (arg0 >= 0) {
            func_00f417a8(arg0);
            return;
        }
        return;
    }
    func_00f417a8(arg0);
    func_00176310(D_00F70268 + (arg0 * 0x48));
}
