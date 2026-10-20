/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00105a30(M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_001247e8(void *);
M2C_UNK func_00156260(s32, void *);
M2C_UNK func_0015aa30(void *, s32);
M2C_UNK func_00267370(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_002673b8(M2C_UNK *, M2C_UNK *);
M2C_UNK func_00267530(void *, s32, s32);
M2C_UNK func_002675a8(void *, s32);
extern M2C_UNK D_00351BB0;
extern s32 D_002E26A0;
f32 func_00120bf8(void *);
s32 func_00122ff8(s32);

void func_001533d0(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_002675a8(sp, arg1 + 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = 30.0f;
    func_00156260(arg0, sp);
}

void func_0015ab50(void *arg0) {
    s32 sp[4];
    s32 temp_s0;

    temp_s0 = D_002E26A0;
    if (func_00122ff8(temp_s0) != 0) {
        func_00267530(sp, arg0 + 0x10, temp_s0 + 0x10);
        if (func_00120bf8(sp) < M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), f32 *, 0x44)) {
            func_0015aa30(arg0, temp_s0);
            func_001247e8(arg0);
        }
    }
}

void func_0015dcc8(void *arg0, M2C_UNK *arg1) {
    s32 sp[8];
    func_00105a30(-1, M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), s32 *, 0x120), sp);
    func_00267370(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, &D_00351BB0);
    func_002673b8(&M2C_FIELD(sp, M2C_UNK *, 0x10), &M2C_FIELD(sp, M2C_UNK *, 0x10));
    func_00267370(arg1, &D_00351BB0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
    func_002673b8(arg1, arg1);
}
#include "data/data_0035.h"
