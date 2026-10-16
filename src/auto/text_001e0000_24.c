/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001ed000(M2C_UNK, s32, s32, s32, s32, s32, s32, M2C_UNK);
extern s32 D_003E3C80;
extern s32 D_00633640;

s32 func_001ed4b8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (D_003E3C80 & 1) {
        return D_00633640;
    }
    func_001ed000(0xC, arg0, arg1, arg2, arg3, arg4, arg5, 0);
    return D_00633640;
}
