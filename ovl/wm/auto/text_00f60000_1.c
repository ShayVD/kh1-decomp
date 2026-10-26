/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001bfac8();
M2C_UNK func_001ed4b8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_001efb18(s32, s32);
M2C_UNK func_00f681f8(void *, M2C_UNK *, s32);
M2C_UNK func_00f688c8(s32, void *, M2C_UNK *);
extern s32 D_00FA66DC;
extern s32 D_00FB49E8;
s32 func_00f60428();
s32 func_00f60438();
s32 func_00f63270();
s32 func_00f68140();
void func_00176310(s32);
void func_00f688a0(s32);

s32 func_00f632a8(void) {
    return func_00f63270() * D_00FA66DC;
}

void func_00f68070(void) {
    func_001ed4b8(0, 0x3000, 0x3000, 0, 0, 0);
    func_001bfac8();
}

void func_00f689f0(s32 arg0, s32 arg1) {
    s32 sp[8];
    func_00f681f8(sp, &M2C_FIELD(sp, M2C_UNK *, 0x10), arg1);
    func_00f688c8(arg0, sp, &M2C_FIELD(sp, M2C_UNK *, 0x10));
}

void func_00f68a40(s32 arg0) {
    if (func_00f68140() == 0) {
        if (arg0 >= 0) {
            func_00f688a0(arg0);
            return;
        }
        return;
    }
    func_00f688a0(arg0);
    func_00176310(D_00FB49E8 + (arg0 * 0x48));
}

void func_00f6a448(void) {
    s32 temp_s0;

    temp_s0 = func_00f60428();
    func_001efb18(temp_s0, func_00f60438());
}
