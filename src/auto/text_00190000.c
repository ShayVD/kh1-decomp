/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

M2C_UNK func_00183b20(s32, s32);
M2C_UNK func_001a5ca0(void *);
M2C_UNK func_001a62a8(s32);
M2C_UNK func_001a6538(s32);
M2C_UNK func_001a67a0(s32);
extern s32 D_00615E64;

void pppKeShpTailPhtFrame(void) {

}

void pppKeShpTailPhtDraw(void) {

}

void pppKeShpTailPhtCon(void) {

}

void pppKeShpTailPhtReset(void) {

}

void pppKeShpTailLcFrame(void) {

}

void pppKeShpTailLcDraw(void) {

}

void pppKeShpDttFrame(void) {

}

void pppKeLnsLpCon(s32 arg0, PppEntry *arg1) {
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[0] + 0xA0;
    func_001a5ca0(temp_s0);
    M2C_FIELD(temp_s0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0xA8) = 0;
}

void pppKeLnsArndCon(s32 arg0, PppEntry *arg1) {
    func_001a62a8(arg0 + arg1->offsets[0] + 0xA0);
}

void pppKeLnsCrnCon(s32 arg0, PppEntry *arg1) {
    func_001a6538(arg0 + arg1->offsets[0] + 0xA0);
}

void pppKeLnsFlsCon(s32 arg0, PppEntry *arg1) {
    func_001a67a0(arg0 + arg1->offsets[0] + 0xA0);
}

void pppKeLnsLpTDes(void) {

}

void pppKeLnsClmTDes(void) {

}

void pppKeHmgEffCon(void) {

}

void pppKeGrvTgtCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[1]), s32 *, 0xA8) = 0;
}

void pppKeGrvEffCon(void) {

}

void pppKeHitBallCon(void) {

}

void pppKeHitBornCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[2]), s8 *, 0xA0) = 0;
}

void pppKeHitChkPxBCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[2] + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xC) = 1.0f;
    M2C_FIELD(temp_a0, s8 *, 0x10) = 0;
}

void pppKeDrctFrame(void *arg0, void *arg1, void *arg2) {
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

void pppKeDrctCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), f32 *, 0xAC) = 1.0f;
}

void pppRyjDrawShipolyDes(s32 arg0, PppEntry *arg1) {
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[2] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 8);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
    }
}

void pppRyjDrawShipolyBoneFrame(void) {

}

void pppRyjDrawShipolyBoneDes(s32 arg0, PppEntry *arg1) {
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[1] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 8);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
    }
}
#include "data/bss_0061_mixed.h"
