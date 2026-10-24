/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "actor.h"

M2C_UNK func_0011a0a0();
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
M2C_UNK func_0011f320(M2C_UNK *, s32);
M2C_UNK func_00135df0(void *, void *);
M2C_UNK func_00136428(void *, s32, s32, void *, f32);
M2C_UNK func_00137688(s32, f32);
#include "vm/script_vm.h"
M2C_UNK func_00267548(void *, void *, s32);
M2C_UNK D_00525430[0x180] ALIGNED(16);
extern M2C_UNK D_0052A100; /* src/data/bss_0052.c: u8 D_0052A100[0x10] */
extern M2C_UNK D_0052AA58; /* src/data/bss_0052.c: u8 D_0052AA58[0x10] */
extern s32 D_0052AE54;
f32 func_00135ca0(f32);
f32 func_001376e8();
s32 func_00130340(s32, s32, f32);

void func_001366d8(Actor *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    f32 temp_f20;

    temp_f20 = func_00135ca0(arg0->unk118);
    func_00135df0(arg0, sp);
    func_00267548(sp, sp, arg2);
    func_00136428(arg0, ~(1 << (arg1 - 1)), arg0->unk394, sp, temp_f20);
}

s32 func_00136c98(void) {
    func_0011f130(&D_0052A100, 0);
    return 0;
}

void func_001386f8(s32 arg0) {
    func_0011f320(&D_0052AA58, arg0);
}

s32 func_00138718(void) {
    func_0011a0a0();
    return 0;
}

void func_001394a8(s32 arg0) {
    func_00130340(arg0, 0x01000066, 0.0f);
    M2C_FIELD(arg0, f32 *, 0x404) = 68.0f;
}

void func_0013ba08(void) {
    D_0052AE54 = 2;
}

void func_0013bef0(s32 arg0) {
    func_00137688(arg0, func_001376e8());
}
#include "data/data_0030.h"
#include "data/data_002E.h"
