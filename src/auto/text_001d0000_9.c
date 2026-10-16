/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK func_001daca8;
extern s64 D_00389C90[];
s32 func_00149c80(s32, M2C_UNK *);

s32 func_001dacc8(void *arg0) {
    if (func_00149c80(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184), &func_001daca8) != 0) {
        D_00389C90[1551] = (s64) (D_00389C90[1551] | 0x20);
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}
