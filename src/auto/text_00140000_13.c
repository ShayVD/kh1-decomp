/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00267370(void *, void *, void *);
M2C_UNK func_00267e90(void *, void *, f32);
extern f32 D_002BBDFC;
f32 func_002673b8(void *, void *);
s32 func_0014c4a8();

void func_0014c580(void *arg0) {
    void *temp_v0;

    if (func_0014c4a8() != 0) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x148);
        M2C_FIELD(temp_v0, s64 *, 0x100) = (s64) (M2C_FIELD(temp_v0, s64 *, 0x100) | ((s64) 0x8000 << 0x11));
    }
}

void func_0014f798(void *arg0, void *arg1) {
    s32 sp[4];
    void *temp_s2;

    temp_s2 = arg0 + 0xC0;
    func_00267370(sp, temp_s2, arg0 + 0x20);
    func_002673b8(sp, sp);
    func_00267370(arg1, sp, temp_s2);
    func_002673b8(arg1, arg1);
    func_00267e90(arg1, arg1, M2C_FIELD(arg0, f32 *, 0x2C) * D_002BBDFC);
}
