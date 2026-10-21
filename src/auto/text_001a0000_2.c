/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

M2C_UNK func_00183b20(s32, s32);
#include "data/pieces/D_00372800.h"
extern M2C_UNK D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */
extern f32 D_002BC120;
extern f32 D_002BC124;
extern s32 D_00372760;
extern s32 D_00615E64;

void pppRyjMegaBirthModelDes(s32 arg0, PppEntry *arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[2] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 0x10);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
    }
    temp_a1 = M2C_FIELD(temp_s0, s32 *, 0x14);
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
    }
    temp_a1_2 = M2C_FIELD(temp_s0, s32 *, 0x18);
    if (temp_a1_2 != 0) {
        func_00183b20(D_00615E64, temp_a1_2);
        M2C_FIELD(temp_s0, s32 *, 0x18) = 0;
    }
}

void func_001a62a8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_00575A00;
}

void func_001a67a0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_00575A00;
}

void func_001a8f08(void) {
    D_00372760 = ((D_00372760 * 0x80D) + 7) & 0xFFFF;
}

void func_001aa8d0(void) {
    M2C_FIELD((M2C_UNK *)&D_00372800, f32 *, 0) = (f32) D_002BC120;
    M2C_FIELD((M2C_UNK *)&D_00372800, f32 *, 4) = (f32) D_002BC124;
}

void func_001aa8f8(void) {

}

void func_001aa900(void) {

}

void func_001aa908(void) {

}

void func_001aa910(void) {

}

void func_001aa948(void) {

}
#include "data/bss_0061_mixed.h"
#include "data/data_002B.h"
#include "data/data_0037.h"
