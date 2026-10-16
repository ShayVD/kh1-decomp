/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0023cc80(s32 *);
extern M2C_UNK D_00425BD0;
extern s32 D_0044A820;
extern s32 D_00647FB0;

void func_002365e0(void) {
    (*(M2C_UNK (**)())((s32) &D_00425BD0 + (s32) ((D_00647FB0 * 4))))();
}

s32 func_0023ceb0(void) {
    if (D_0044A820 == 0) {
        return 0;
    }
    func_0023cc80(&D_0044A820);
    return 0;
}
