/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ea40(s32, void *);
M2C_UNK func_0011eae0(s32, void *);
M2C_UNK func_00120748(void *, M2C_UNK *, M2C_UNK *, M2C_UNK);
extern M2C_UNK D_00F20000;
extern M2C_UNK func_001e8060;
extern M2C_UNK func_001e8388;
extern s32 D_006314CC;
extern s32 D_006314D0;
extern s64 D_00389C90[];

s32 func_001e80d0(void *arg0) {
    s32 sp[64];
    s32 temp_a1;
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    func_0011eae0(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180), sp);
    func_00120748(sp, &D_00F20000, &func_001e8060, 0);
    D_00389C90[1550] = (s64) (D_00389C90[1550] | ((s64) 0x8000 << 0x29));
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x180);
    D_006314D0 = M2C_FIELD(((temp_a1 * 4) + temp_s1), s32 *, 0x17C) - 1;
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (temp_a1 - 2);
    return 2;
}

s32 func_001e83f8(void *arg0) {
    s32 sp[64];
    s32 temp_a1;
    s32 temp_s1;

    temp_s1 = arg0 + 4;
    func_0011ea40(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + temp_s1), s32 *, 0x180), sp);
    func_00120748(sp, &D_00F20000, &func_001e8388, 0);
    D_00389C90[1550] = (s64) (D_00389C90[1550] | ((s64) 0x8000 << 0x24));
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x180);
    D_006314CC = M2C_FIELD(((temp_a1 * 4) + temp_s1), s32 *, 0x17C) - 1;
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (temp_a1 - 2);
    return 2;
}
