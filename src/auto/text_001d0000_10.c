/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s64 D_00389C90[];

s32 func_001d6c20(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] | ((s64) 0x8000 << 0x2C));
    return 2;
}

s32 func_001d6c48(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xF7FFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
    return 2;
}

void func_001d71f0(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xEFFFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

void func_001d75a0(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xDFFFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}

void func_001d7768(void) {
    D_00389C90[1550] = (s64) (D_00389C90[1550] & (((((s64) 0xBFFFFFFF << 0x10) | 0xFFFF) << 0x10) | 0xFFFF));
}
