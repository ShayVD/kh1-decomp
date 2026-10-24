/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001b9cb0();
extern M2C_UNK D_00009B38;
extern M2C_UNK D_00009B3C;
extern M2C_UNK D_00009B40;
extern M2C_UNK D_00009C00;
s32 func_00232cc0(M2C_UNK);

u8 func_001b9b78(s32 arg0) {
    return *(M2C_UNK *)((s8 *)&D_00009C00 + (arg0 + func_00232cc0(4)));
}

s32 func_001b9df0(s32 arg0) {
    s32 temp_s1;

    temp_s1 = func_00232cc0(4);
    func_001b9cb0();
    return *(M2C_UNK *)((s8 *)&D_00009B40 + ((arg0 * 4) + temp_s1));
}

void func_001b9e40(s32 arg0, s32 arg1) {
    *(M2C_UNK *)((s8 *)&D_00009B40 + ((arg0 * 4) + func_00232cc0(4))) = arg1;
}

s32 func_001bad78(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_00232cc0(4);
    switch (arg0) {                                 /* irregular */
    case 0:
        return *(M2C_UNK *)((s8 *)&D_00009B38 + temp_v0);
    case 1:
        return *(M2C_UNK *)((s8 *)&D_00009B3C + temp_v0);
    default:
        return 0;
    }
}
