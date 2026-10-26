/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00304B7C;
extern M2C_UNK D_00304B80;
extern M2C_UNK func_00f20250;
extern M2C_UNK func_00f20380;
extern s32 D_002E26A0;
extern s32 D_00F21384;
extern s32 D_00F21388;
extern s32 D_00F2138C;
extern s32 D_00F21398;
s32 func_0011ef10(s32, s32);
s32 func_00123488(s32);
s32 func_00130340(s32, s32, f32);
void func_0012cab8(s32);
void func_00131500(s32);
void func_00241c00(s32, s32, s32, s32, s32);
void func_00f20aa8();
void func_00f20fb0(void);

void func_00f20430(void) {
    D_00F21384 = D_002E26A0;
    func_00131500(D_002E26A0);
    func_00130340(D_00F21384, 0x40000000, 0);
    D_00F21388 = func_00123488(0x70004);
    func_00f20fb0();
    func_00241c00(&D_00304B7C, 0, &D_00304B80, 0, D_00F21388);
    D_00F2138C = 1;
    D_00F21398 = 0;
    func_00f20aa8();
    func_0012cab8(&func_00f20380);
    func_0011ef10(0xC350, &func_00f20250);
}
