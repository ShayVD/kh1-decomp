/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0021af38(s32);
M2C_UNK func_0021b800(s32);
M2C_UNK func_0021b820();
M2C_UNK func_0021ccd0(s32, M2C_UNK);
#include "data/pieces/D_003F34B8.h"

s32 func_0021add8(void) {
    return M2C_FIELD(D_003F34B8, s32 *, 0x74);
}

void func_0021cf90(s32 arg0) {
    func_0021b820();
    func_0021ccd0(arg0, 0);
    func_0021af38(arg0);
}

void func_0021dc20(s32 arg0) {
    func_0021b800(arg0 + 0x51);
}
#include "data/bss_0064_mixed.h"
