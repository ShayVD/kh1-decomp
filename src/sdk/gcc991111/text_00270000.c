/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK DeleteSema(s32);
M2C_UNK SleepThread();
M2C_UNK func_00257ee0(s32, M2C_UNK *, s32);
extern M2C_UNK D_0046E090;
extern M2C_UNK D_00673600;
extern M2C_UNK D_00674BC0;
extern M2C_UNK func_00271530;
extern s32 D_0046E094;
s32 GetThreadId();

s32 func_00270d18(void) {
    if (D_0046E094 >= 0) {
        DeleteSema(D_0046E094);
        D_0046E094 = -1;
    }
    return 1;
}

M2C_UNK *func_00270d58(M2C_UNK **arg0, M2C_UNK **arg1) {
    *arg0 = &D_00674BC0;
    *arg1 = &D_0046E090;
    M2C_FIELD(&D_00674BC0, s32 *, 0x3C) = (s32) D_0046E094;
    return &D_00673600;
}

void func_00271558(s32 arg0) {
    func_00257ee0(arg0 & 0xFFFF, &func_00271530, GetThreadId());
    SleepThread();
}
