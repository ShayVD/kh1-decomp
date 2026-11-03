/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001ba708(s32);
M2C_UNK func_001c0310(M2C_UNK, M2C_UNK *, s32, s32, s32);
M2C_UNK func_00f20248(M2C_UNK);
M2C_UNK func_00f29450(M2C_UNK);
M2C_UNK func_00f29470(M2C_UNK);
M2C_UNK func_00f29480(M2C_UNK);
M2C_UNK func_00f29518(M2C_UNK);
M2C_UNK func_00f2e238(M2C_UNK);
M2C_UNK func_00f2e280(M2C_UNK);
M2C_UNK func_00f32778(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK func_00f25fa8;
extern s32 D_00F613AC;
extern s32 D_00F80580;

void func_00f21c38(void) {
    func_00f29450(0);
    func_00f29470(0);
    func_00f29480(0);
    func_00f2e238(0);
    func_00f2e280(0);
    func_00f32778(-1, 0x80, 0x80, 0x80, 0);
    func_00f32778(0, 0x80, 0x80, 0x80, 0x80);
    func_00f32778(2, 0x80, 0x80, 0x80, 0x80);
    func_00f32778(1, 0x80, 0x80, 0x80, 0);
    func_00f20248(0xB);
    func_00f20248(0xC);
}

void func_00f25f60(s32 arg0) {
    func_001ba708(arg0);
}

void func_00f26010(s32 arg0, s32 arg1, s32 arg2) {
    func_001c0310(-1, &func_00f25fa8, arg0, arg1, arg2);
}

void func_00f294b0(s32 arg0) {
    if (arg0 != 0) {
        func_00f29518(0x80);
    } else {
        func_00f29518(0x46);
    }
    func_00f29480(0x80);
    func_00f29470(0x80);
    func_00f29450(0x80);
    D_00F80580 = 1;
    D_00F613AC = -1;
}

void func_00f2e2a0(void) {
    func_00f2e238(0x80);
    func_00f2e280(0x80);
}
