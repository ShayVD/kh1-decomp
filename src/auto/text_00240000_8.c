/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00249370(void *, void *, s32);
M2C_UNK func_0024b5c8(M2C_UNK);
M2C_UNK func_00267518(s32, s32, M2C_UNK *);
M2C_UNK func_00267578(s32, void *, s32);
M2C_UNK func_002675a8(void *);
M2C_UNK func_00267620(void *);
M2C_UNK func_00267e90(M2C_UNK *, void *, f32);

void func_002493c0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[16];
    func_00267620(sp);
    func_00249370(sp, sp, arg2);
    func_00267578(arg0, sp, arg1);
}

void func_002497b8(s32 arg0, f32 fparg0) {
    s32 sp[8];
    func_002675a8(sp);
    M2C_FIELD(sp, s32 *, 0xC) = 0;
    func_00267e90(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, fparg0);
    func_00267518(arg0, arg0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
}

void func_0024b610(void) {
    func_0024b5c8(0);
}

void func_0024b628(void) {
    func_0024b5c8(1);
}

void func_0024b640(void) {
    func_0024b5c8(2);
}

void func_0024b658(void) {
    func_0024b5c8(3);
}

void func_0024b670(void) {
    func_0024b5c8(4);
}

void func_0024b688(void) {
    func_0024b5c8(5);
}

void func_0024b6a0(void) {
    func_0024b5c8(6);
}

void func_0024b6b8(void) {
    func_0024b5c8(7);
}
