/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK __malloc_lock(s32);
M2C_UNK __malloc_unlock(s32);
M2C_UNK func_002557d8(s32, s32);
extern s32 D_0046A9C8;
s32 func_0024f7e8(s32, s32);

s32 malloc(s32 arg0) {
    s32 temp_s1;

    __malloc_lock(D_0046A9C8);
    temp_s1 = func_0024f7e8(D_0046A9C8, arg0);
    __malloc_unlock(D_0046A9C8);
    return temp_s1;
}

void free(s32 arg0) {
    __malloc_lock(D_0046A9C8);
    func_002557d8(D_0046A9C8, arg0);
    __malloc_unlock(D_0046A9C8);
}
