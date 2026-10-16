/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "compclass.h"

M2C_UNK func_00183b20(s32, s32);
M2C_UNK func_001a9e90();
M2C_UNK func_001aa918();
M2C_UNK func_00265bc0(M2C_UNK, M2C_UNK);
M2C_UNK func_00266f38(s32, M2C_UNK *);
M2C_UNK func_002673b8(M2C_UNK *, M2C_UNK *);
M2C_UNK func_00267530(M2C_UNK *, M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_00373000;
extern M2C_UNK D_00373030;
extern M2C_UNK D_00575A00;
extern M2C_UNK D_00615F70;
extern M2C_UNK D_00615F80;
extern M2C_UNK D_0061E720;
extern M2C_UNK D_0061E730;
extern s32 D_00372908;
extern s32 D_00615E64;

void func_001a1f28(s32 arg0, CompClass *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[2]), s32 *, 0xA0) = 0;
}

void func_001a30d0(void) {

}

void func_001a3550(void) {
    func_00267530(&D_0061E720, &D_00615F80, &D_00615F70);
    func_002673b8(&D_0061E720, &D_0061E720);
    M2C_FIELD(&D_0061E720, f32 *, 0xC) = 1.0f;
}

void func_001a35f0(s32 arg0, CompClass *arg1) {
    s32 temp_a1;
    s32 temp_v0;
    void *temp_a0;
    void *temp_s0;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_s0 = temp_a0 + 0xA0;
    temp_v0 = M2C_FIELD(temp_a0, s32 *, 0xA0);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    }
    temp_a1 = M2C_FIELD(temp_s0, s32 *, 4);
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(temp_s0, s32 *, 4) = 0;
    }
}

void func_001a4a90(void) {

}

void func_001a4fd0(void) {
    func_00267530(&D_0061E730, &D_00615F80, &D_00615F70);
    func_002673b8(&D_0061E730, &D_0061E730);
    M2C_FIELD(&D_0061E730, f32 *, 0xC) = 1.0f;
}

void func_001a5070(s32 arg0, CompClass *arg1) {
    s32 temp_a1;
    s32 temp_v0;
    void *temp_a0;
    void *temp_s0;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_s0 = temp_a0 + 0xA0;
    temp_v0 = M2C_FIELD(temp_a0, s32 *, 0xA0);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    }
    temp_a1 = M2C_FIELD(temp_s0, s32 *, 4);
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(temp_s0, s32 *, 4) = 0;
    }
}

void func_001a60d0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_00575A00;
}

void func_001a9e70(void) {
    func_001a9e90();
    func_001aa918();
}

void func_001aaed0(void) {
    func_00265bc0(0, 0);
    func_00266f38(D_00372908, &D_00373000);
}

void func_001aaf00(void) {
    func_00265bc0(0, 0);
    func_00266f38(D_00372908, &D_00373030);
}
