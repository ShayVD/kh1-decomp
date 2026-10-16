/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "compclass.h"

M2C_UNK func_00183b20(s32, s32);
M2C_UNK func_001a5ca0(void *);
M2C_UNK func_001a62a8(s32);
M2C_UNK func_001a6538(s32);
M2C_UNK func_001a67a0(s32);
M2C_UNK func_00250054(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_0035C710;
extern s32 D_00615E64;
extern void *D_00615E60;

void func_00191ab0(void) {

}

void func_00191ab8(void) {

}

void func_00191ac0(void) {

}

void func_00191ac8(void) {

}

void func_00191ad0(void) {

}

void func_00191ad8(void) {

}

void func_00191b10(void) {

}

void func_00191f68(s32 arg0, CompClass *arg1) {
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[0] + 0xA0;
    func_001a5ca0(temp_s0);
    M2C_FIELD(temp_s0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0xA8) = 0;
}

void func_001921e0(s32 arg0, CompClass *arg1) {
    func_001a62a8(arg0 + arg1->offsets[0] + 0xA0);
}

void func_001926e0(s32 arg0, CompClass *arg1) {
    func_001a6538(arg0 + arg1->offsets[0] + 0xA0);
}

void func_00192930(s32 arg0, CompClass *arg1) {
    func_001a67a0(arg0 + arg1->offsets[0] + 0xA0);
}

void func_00192f70(void) {

}

void func_00193400(void) {

}

void func_00193c20(void) {

}

void func_00193c78(s32 arg0, CompClass *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[1]), s32 *, 0xA8) = 0;
}

void func_00193e10(void) {

}

void func_00193e60(void) {

}

void func_00193fc8(s32 arg0, CompClass *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[2]), s8 *, 0xA0) = 0;
}

void func_00194200(s32 arg0, CompClass *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[2] + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xC) = 1.0f;
    M2C_FIELD(temp_a0, s8 *, 0x10) = 0;
}

void func_00194228(void *arg0, void *arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    if (M2C_FIELD(arg0, s32 *, 0xC) == M2C_FIELD(arg1, s32 *, 0)) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_v0_2 = temp_v0 + 0xA0;
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) M2C_FIELD(arg1, f32 *, 4);
        M2C_FIELD(temp_v0_2, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 8);
        M2C_FIELD(temp_v0_2, f32 *, 8) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
    }
}

void func_00194268(s32 arg0, CompClass *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), f32 *, 0xAC) = 1.0f;
}

void func_0019a7e0(s32 arg0, CompClass *arg1) {
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[2] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 8);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
    }
}

void func_0019b458(void) {

}

void func_0019bab0(s32 arg0, CompClass *arg1) {
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[1] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 8);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
    }
}

void func_0019d920(void *arg0, void *arg1) {
    if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
        M2C_FIELD(D_00615E60, u8 *, 0xB2) = (u8) M2C_FIELD(arg1, u8 *, 4);
        M2C_FIELD(D_00615E60, u8 *, 0xB1) = (u8) M2C_FIELD(arg1, u8 *, 5);
        M2C_FIELD(D_00615E60, u8 *, 0xB0) = (u8) M2C_FIELD(arg1, u8 *, 6);
    }
}

void func_0019df80(void) {
    func_00250054(&D_0035C710, 0, 0x2000);
    M2C_FIELD(D_00615E60, s8 *, 0xB3) = 1;
    M2C_FIELD(D_00615E60, s8 *, 0xB0) = 1;
}
