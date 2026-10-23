/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 (*D_003773E8)(s32, void *);

s32 func_001dc280(s32 arg0) {
    void *temp_a1;

    temp_a1 = (M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0;
    if (!(D_003773E8(M2C_FIELD(temp_a1, s32 *, 0x184), temp_a1) != 0)) {
        return 4;
    }
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
    return 4;
}
#include "data/pieces/D_003773E0.h"
