/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001606d0();
M2C_UNK func_00267390(void *, void *);
M2C_UNK func_00267530(void *, s32, s32);
M2C_UNK func_002675a8(s32, s32);

void func_001621e0(void) {
    func_001606d0();
}

void func_001621f8(void *arg0) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s64 *, 0x48) = (s64) (M2C_FIELD(arg0, s64 *, 0x48) | 0x20000);
    }
}

void func_001624f8(void) {

}

void func_001629b0(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_00267530(sp, arg0, arg1);
    func_00267390(sp, sp);
}

void func_001676d8(s32 arg0, s32 arg1) {
    func_002675a8(arg1, arg0 + 0xC0);
}
