/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_0011d7c0(M2C_UNK);
M2C_UNK func_00141348(s32 *, void *);
M2C_UNK func_00246a70(s32, s32, s32, s32);
extern s32 D_00651E50[];
f32 func_0011d790(M2C_UNK, s32);
s32 func_00122ff8(s32);

void func_0023c1b0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    if (func_00122ff8(*arg0) != 0) {
        func_00141348(arg0, sp);
        if ((M2C_FIELD(sp, M2C_UNK *, 0x0) != 0) && (M2C_FIELD(sp, M2C_UNK *, 0x0) != 2)) {
            func_00246a70(arg1, arg2, M2C_FIELD(sp, M2C_UNK *, 0x4), M2C_FIELD(sp, M2C_UNK *, 0x8));
        }
    }
}

void func_0023d1a0(void) {
    if (D_00651E50[4168] == 1) {
        func_0011d7c0(0x2D);
        D_00651E50[4168] = 0;
    }
}
#include "data/data_003F.h"
