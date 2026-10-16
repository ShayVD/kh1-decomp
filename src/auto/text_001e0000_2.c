/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_001efc10(M2C_UNK);
void *func_001478a0(s32);

s32 func_001ef540(s32 arg0) {
    if (arg0 != 0) {
        return M2C_FIELD(func_001478a0(arg0 & ~0x80), s32 *, 4);
    }
    return func_001efc10(0xB4);
}

s32 func_001ef580(s32 arg0) {
    if (arg0 != 0) {
        return M2C_FIELD(func_001478a0(arg0 & ~0x80), s32 *, 8);
    }
    return func_001efc10(0xB4);
}

u16 func_001ef5f8(s32 arg0) {
    if (arg0 != 0) {
        return M2C_FIELD(func_001478a0(arg0 & ~0x80), u16 *, 2);
    }
    return 0U;
}
