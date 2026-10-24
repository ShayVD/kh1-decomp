/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

M2C_UNK func_00182368();
M2C_UNK func_00182ec0(s32);
M2C_UNK func_001837a8(s32);
M2C_UNK func_00183b20(s32, s32);
#include "data/pieces/D_00370130.h"
extern s32 D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
extern s32 D_00615E64;
s32 func_00180f18(s32, M2C_UNK, void *, u8);

s32 func_001803b8(s32 arg0) {
    return arg0 + 4;
}

void func_00180aa8(s32 arg0) {
    D_00370130 = arg0;
}

void func_00181280(s32 arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = func_00180f18(arg0 + 0x78, 6, arg1, M2C_FIELD(arg1, u8 *, 0x92));
    if (temp_v0 < 0) {
        M2C_FIELD(arg1, s16 *, 0xA6) = 0;
        return;
    }
    M2C_FIELD(arg1, s16 *, 0xA6) = (s16) ((temp_v0 << 5) + 0x3D40);
}

void func_00183840(s32 arg0) {
    D_00615E60 = arg0;
    func_00182368();
    func_001837a8(arg0);
    func_00182ec0(arg0);
}

void pppKeThLzFrame(void) {

}

void pppKeThLzCon(void) {

}

void pppKeThLzDes(void) {

}

void pppKeThCpFrame(void) {

}

void pppKeThCpCon(void) {

}

void pppKeThCpDes(void) {

}

void pppKeThCpSftFrame(void) {

}

void pppKeAccSpdSvFrame(void) {

}

void pppKeAccSpdSvCon(void) {

}

void pppSegmentApFrame(void) {

}

void pppFaceApFrame(void) {

}

void pppVtMimeDes(s32 arg0, PppEntry *arg1) {
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[0] + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 0xC);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
    }
}

void pppPointApCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[1]), s8 *, 0xA1) = 0;
}

void pppPointRApCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[1]), s8 *, 0xA1) = 0;
}
