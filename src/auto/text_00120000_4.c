/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_001236f8();
M2C_UNK func_001238d0(s32, s32);
M2C_UNK func_0012fc20();
extern M2C_UNK func_0012fcd0;
f32 func_0012ec60(s32, s32, s32);
s32 func_0011ef38(M2C_UNK *);
s32 func_00123488();

void func_00123760(void *arg0) {
    func_001236f8();
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 0x374) = 0;
}

void func_00123a88(s32 arg0, s32 arg1) {
    func_001238d0(func_00123488(), arg1);
}

void func_0012ec88(s32 arg0, s32 arg1) {
    func_0012ec60(arg0, 0, arg1);
}

void func_0012ff80(void) {
    func_0012fc20();
    if (func_0011ef38(&func_0012fcd0) == 0) {
        func_0011ef10(0x14C08, &func_0012fcd0);
    }
}
