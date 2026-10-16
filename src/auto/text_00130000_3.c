/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0012ec60(s32, s32);
M2C_UNK func_001376e8(s32, void *);
M2C_UNK func_002673b8(void *, void *);
M2C_UNK func_00267530(void *, void *, s32);
M2C_UNK func_002675a8(void *, s32);

void func_0013ecf8(s32 arg0, void *arg1, void *arg2) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0);
    if ((temp_v0 != 0) && (temp_v0 != arg0)) {
        func_0012ec60(temp_v0, M2C_FIELD(arg1, s32 *, 4));
        func_00267530(arg2, arg2, arg0 + 0x10);
        M2C_FIELD(arg2, s32 *, 4) = 0;
        func_002673b8(arg2, arg2);
    } else {
        func_002675a8(arg2, arg0 + 0x30);
    }
    M2C_FIELD(arg2, s32 *, 0xC) = 0;
    func_001376e8(arg0, arg2);
}
