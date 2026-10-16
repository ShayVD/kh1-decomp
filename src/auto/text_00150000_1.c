/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001247e8(void *);
M2C_UNK func_0013c2a0(s16, M2C_UNK);
M2C_UNK func_002583e0(M2C_UNK);
extern s32 D_00351A48;
s32 func_00158d30();
void *func_00123488();

void func_00156c28(void) {
    void *temp_v0;

    temp_v0 = func_00123488();
    func_0013c2a0(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x130), s16 *, 0x48), 1);
    func_001247e8(temp_v0);
}

void func_00158d70(void) {
    if (func_00158d30() != 0) {
        D_00351A48 = 5;
        return;
    }
    D_00351A48 = 0;
}

void func_00158db0(void) {
    if (func_00158d30() != 0) {
        func_002583e0(2);
        D_00351A48 = 3;
        return;
    }
    D_00351A48 = 0;
}
