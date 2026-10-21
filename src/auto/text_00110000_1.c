/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK D_00F20000(M2C_UNK, M2C_UNK);
M2C_UNK func_00101628();
M2C_UNK func_00109558(M2C_UNK);
M2C_UNK func_00112fd0(M2C_UNK);
M2C_UNK func_00113e28(M2C_UNK);
M2C_UNK func_00114820();
M2C_UNK func_0011c850(M2C_UNK, s32, M2C_UNK);
M2C_UNK func_0011c9a0();
M2C_UNK func_0011f090(M2C_UNK *, s32, s32);
M2C_UNK func_0011f320(M2C_UNK *, s32);
M2C_UNK func_001edb48(M2C_UNK);
extern M2C_UNK D_004E3A48; /* src/data/bss_004E.c: u8 D_004E3A48[0x10] */
#include "data/pieces/D_002BCB60.h"
s32 func_0011f2e0(M2C_UNK *, s32);

void func_00111060(void) {
    func_00113e28(2);
    func_001edb48(0x7B);
    D_00F20000(1, 0);
}

void func_001110d0(void) {
    D_00F20000(3, 0);
}

void func_001110f0(void) {
    D_00F20000(8, 0);
}

void func_00111110(void) {
    D_00F20000(9, 0);
}

void func_00111130(void) {
    D_00F20000(4, 0);
}

void func_00111190(void) {
    D_00F20000(7, 0);
}

void func_001117b8(void) {
    if (((void *)D_002BCB60) != NULL) {
        M2C_FIELD(((void *)D_002BCB60), s32 *, 0x15C) = (s32) (M2C_FIELD(((void *)D_002BCB60), s32 *, 0x15C) + 1);
    }
}

void func_00112fe0(void) {
    func_00114820();
    func_00112fd0(1);
    func_00109558(8);
}

void func_0011d7c0(s32 arg0) {
    func_0011c850(2, arg0, 0);
}

void func_0011e5f0(void) {
    func_0011c9a0();
    func_00101628();
}

void func_0011ef10(s32 arg0, s32 arg1) {
    func_0011f090(&D_004E3A48, arg0, arg1);
}

void func_0011ef58(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_0011f2e0(&D_004E3A48, arg0);
    if (temp_v0 != 0) {
        func_0011f320(&D_004E3A48, temp_v0);
    }
}
