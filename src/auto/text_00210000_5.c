/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001f92b0(s32, M2C_UNK, M2C_UNK, s32, M2C_UNK, M2C_UNK);
extern s32 D_00642C2C;
s32 func_001ee5f0(s32);
s32 func_001ef658(s32);
s32 func_001ef720(s32);
s32 func_001f9438(s32, M2C_UNK, s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_001fb428(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK, s32, M2C_UNK, s32);

void func_002148d0(s32 arg0) {
    s32 temp_s0;

    func_001f92b0(arg0, 0, 0x10, func_001ee5f0(D_00642C2C), 0xF, 0x801EC8C8);
    func_001f9438(arg0, 0, 0x10, 0x22, 0x51, 0xE, 0x80E6E6E6);
    temp_s0 = func_001f9438(arg0, 0, func_001fb428(arg0, 0, 0, 0, 0x10, 0x36, func_001ef720(D_00642C2C), 0xE, 0x806464EC) + 2, 0x36, 0x54, 0xE, 0x596464EC);
    func_001fb428(arg0, 0, 0, 0, temp_s0 + 2, 0x36, func_001ef658(D_00642C2C), 0xE, 0x596464EC);
}
