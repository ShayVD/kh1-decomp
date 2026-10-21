/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_001315c0(s32, s32, M2C_UNK *, f32);
M2C_UNK func_001318e8(s32, s32, void *);
M2C_UNK func_001376e8();
M2C_UNK func_00147e08(s32, void *);
M2C_UNK func_002675a8(s32, void *);
M2C_UNK func_002675b8(s32, void *);
M2C_UNK func_00267e90(s32, void *, f32);
extern f32 D_002BBDFC;
void *func_00148438(s32, s32);

void *func_00148600(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    s32 sp[16];    void *temp_v0;

    func_001318e8(arg1, arg2 & 0xFFFEFFFF, sp);
    func_001315c0(arg1, arg2, &M2C_FIELD(sp, M2C_UNK *, 0x30), fparg0);
    func_00147e08(arg0, sp);
    temp_v0 = func_00148438(arg0, arg1);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 8) = arg2;
        M2C_FIELD(temp_v0, s8 *, 4) = 3;
        M2C_FIELD(temp_v0, f32 *, 0xC) = fparg0;
        func_002675b8(temp_v0 + 0x30, sp);
    }
    return temp_v0;
}

void func_0014f6f8(s32 arg0, void *arg1) {
    if (M2C_FIELD(arg1, f32 *, 0xC) > 0.0f) {
        func_001376e8();
    }
    func_002675a8(arg0 + 0x20, arg1);
}

void func_0014f748(void *arg0, s32 arg1) {
    func_00267e90(arg1, arg0 + 0x20, M2C_FIELD(arg0, f32 *, 0x2C) * D_002BBDFC);
}
#include "data/pieces/D_002BBDFC.h"
