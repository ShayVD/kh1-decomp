/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0057.h"
extern s32 D_003626B0;
extern s32 D_00574FB4;
#include "data/pieces/D_00362438.h"

s32 func_00170e30(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_00574FB4;
    D_00574FB4 = arg0;
    return temp_v0;
}

s32 func_00170f90(void *arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x4C) == M2C_FIELD(arg0, s32 *, 0x164);
}

s32 func_00171f30(void) {
    return 0;
}

void func_00171f38(s32 arg0, s32 *arg1) {
    if ((arg1 != NULL) && (*arg1 == arg0)) {
        *arg1 = 0;
    }
}

void func_0017d1e0(void) {
    if (!(M2C_FIELD(D_00362438, s32 *, 0x18) & 0x10)) {
        D_003626B0 = 1;
    }
}
#include "data/data_0036.h"
