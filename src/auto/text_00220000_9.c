/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_006469B8;
extern void *D_00425BC8;
s32 func_001f4338();
void func_0011d768(M2C_UNK);
void func_001f36b8(s32);

void func_0022d400(s32 arg0) {
    if ((func_001f4338() != 0) && (M2C_FIELD(D_00425BC8, s32 *, 8) & 8)) {
        func_001f36b8(arg0);
        func_0011d768(3);
        M2C_FIELD(&D_006469B8, f32 *, 0) = 1.0f;
        M2C_FIELD(&D_006469B8, f32 *, 4) = 1.0f;
        M2C_FIELD(&D_006469B8, f32 *, 8) = 3.0f;
        M2C_FIELD(&D_006469B8, f32 *, 0xC) = 5.0f;
        M2C_FIELD(&D_006469B8, f32 *, 0x10) = 7.0f;
        M2C_FIELD(&D_006469B8, f32 *, 0x14) = 9.0f;
    }
}
