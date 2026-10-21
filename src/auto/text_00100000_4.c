/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0049.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK sceGsExecLoadImage(M2C_UNK *, s32);
M2C_UNK sceGsSetDefLoadImage(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK D_002BC1B0;
extern M2C_UNK D_002BC320;
#include "data/pieces/D_002BC720.h"
extern M2C_UNK func_00106460;
extern M2C_UNK func_00109360;
extern f32 D_00494A88;
extern f32 D_00494A8C;
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002B6778.h"
extern s32 D_0035C6F0;
extern s32 D_00494A7C;
extern s32 D_00494A80;
extern s32 D_00494A84;
s32 func_0011ef10(s32, s32);
s32 func_002675a8(s32, s32);
void func_001103a0(void);
void func_0011efa8(s32, s32, s32, s32);
void func_00175918(void);
void func_00175980(void);

s32 func_00105c98(s32 arg0, s32 arg1) {
    return func_002675a8(arg1, D_002A3F48 + (((u32) M2C_FIELD(((arg0 * 0x14) + D_002A6238), u32 *, 0x10) >> 7) & 0xF0));
}

void func_001065a8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00494A7C = (arg2 * 0x10) + 0x7000;
    D_00494A80 = (arg3 * 0x10) + 0x7400;
    D_00494A8C = 1.0f;
    D_00494A88 = (800.0f / (f32) arg1) / (f32) (arg0 - 1);
    D_00494A84 = arg1;
    func_0011ef10(0x2E646, (s32) &func_00106460);
}

void func_001094f0(void) {
    func_001103a0();
    func_00175918();
    func_00175980();
    D_0035C6F0 = 1;
    func_0011efa8((s32) (M2C_UNK *)&D_002BC720, (s32) &D_002BC320, 0x20, 0x20);
    func_0011ef10(0x2E662, (s32) &func_00109360);
}

void func_0010a470(void) {
    sceGsSetDefLoadImage(&D_002BC1B0, 0x3600, 4, 1, 0, 0, 0x100, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_002BC1B0, D_002B6778);
}
#include "data/bss_0049_mixed.h"
#include "data/data_0035.h"
#include "data/data_002B.h"
