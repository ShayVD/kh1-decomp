/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

M2C_UNK func_00182368();
M2C_UNK func_00182ec0(s32);
M2C_UNK func_001837a8(s32);
M2C_UNK func_00183b20(s32, s32);
M2C_UNK func_00267328(s32, M2C_UNK *, s32);
extern M2C_UNK D_00616080; /* src/data/bss_0061.c: u8 D_00616080[0x40] */
extern s32 D_00370130;
extern s32 D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
extern s32 D_00615E64;
extern s32 D_00615E68;
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

f32 func_00187df0(f32 fparg0, f32 fparg1) {
    return (fparg0 * fparg1) - fparg0;
}

f32 func_00187f98(f32 fparg0, f32 fparg1) {
    return fparg0 * fparg1;
}

f32 func_00188148(f32 fparg0, f32 fparg1) {
    return fparg0 * fparg1;
}

s32 func_00188498(s32 arg0, f32 fparg0) {
    return (s32) ((f32) arg0 * fparg0);
}

s32 func_00188640(s32 arg0, f32 fparg0) {
    return (s32) ((f32) arg0 * fparg0);
}

s8 func_001887e8(s8 arg0, f32 fparg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    return (s8) (s32) ((temp_f0 * fparg0) - temp_f0);
}

s8 func_001889b0(s8 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

s8 func_00188b78(s8 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

s16 func_00188d40(s16 arg0, f32 fparg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    return (s16) (s32) ((temp_f0 * fparg0) - temp_f0);
}

s16 func_00188f08(s16 arg0, f32 fparg0) {
    return (s16) (s32) ((f32) arg0 * fparg0);
}

s16 func_001890d0(s16 arg0, f32 fparg0) {
    return (s16) (s32) ((f32) arg0 * fparg0);
}

f32 func_00189298(f32 fparg0, f32 fparg1) {
    return (fparg0 * fparg1) - fparg0;
}

f32 func_00189468(f32 fparg0, f32 fparg1) {
    return fparg0 * fparg1;
}

f32 func_00189640(f32 fparg0, f32 fparg1) {
    return fparg0 * fparg1;
}

s8 func_00189818(s8 arg0, f32 fparg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    return (s8) (s32) ((temp_f0 * fparg0) - temp_f0);
}

s8 func_00189a18(s8 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

s8 func_00189c20(s8 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

s8 func_00189e28(s16 arg0, f32 fparg0) {
    f32 temp_f0;

    temp_f0 = (f32) arg0;
    return (s8) (s32) ((temp_f0 * fparg0) - temp_f0);
}

s8 func_0018a028(s16 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

s8 func_0018a230(s16 arg0, f32 fparg0) {
    return (s8) (s32) ((f32) arg0 * fparg0);
}

void pppDrawShapeFieldDraw(void) {

}

void pppDrawShapeFieldCon(void) {

}

void pppDrawShapeFieldDes(void) {

}

void pppDrawMdlSeaDraw(void) {

}

void pppDrawMdlSeaCon(void) {

}

void pppDrawMdlSeaDes(void) {

}

void pppPointLoopCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s32 *, 0xAC) = 0;
}

void pppPointLoopReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    temp_v0 = M2C_FIELD(temp_a0_2, void **, 0xC);
    M2C_FIELD(temp_a0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_a0, f32 *, 0xA0) - M2C_FIELD(temp_v0, f32 *, 4));
    M2C_FIELD(temp_a0_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a0_2, f32 *, 4) - M2C_FIELD(temp_v0, f32 *, 8));
    M2C_FIELD(temp_a0_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a0_2, f32 *, 8) - M2C_FIELD(temp_v0, f32 *, 0xC));
}

void pppAngleLoopCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s32 *, 0xAC) = 0;
}

void pppAngleLoopReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a3;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    temp_a3 = M2C_FIELD(temp_a0_2, void **, 0xC);
    M2C_FIELD(temp_a0, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xA0) - M2C_FIELD(temp_a3, s32 *, 4));
    M2C_FIELD(temp_a0_2, s32 *, 4) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 4) - M2C_FIELD(temp_a3, s32 *, 8));
    M2C_FIELD(temp_a0_2, s32 *, 8) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 8) - M2C_FIELD(temp_a3, s32 *, 0xC));
}

void pppScaleLoopCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s32 *, 0xAC) = 0;
}

void pppScaleLoopReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    temp_v0 = M2C_FIELD(temp_a0_2, void **, 0xC);
    M2C_FIELD(temp_a0, f32 *, 0xA0) = (f32) (M2C_FIELD(temp_a0, f32 *, 0xA0) - M2C_FIELD(temp_v0, f32 *, 4));
    M2C_FIELD(temp_a0_2, f32 *, 4) = (f32) (M2C_FIELD(temp_a0_2, f32 *, 4) - M2C_FIELD(temp_v0, f32 *, 8));
    M2C_FIELD(temp_a0_2, f32 *, 8) = (f32) (M2C_FIELD(temp_a0_2, f32 *, 8) - M2C_FIELD(temp_v0, f32 *, 0xC));
}

void pppDrawMatrixLoopFrame(void) {
    func_00267328(D_00615E68 + 0x50, &D_00616080, D_00615E68 + 0x10);
}

void pppDrawMdlLoopCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[2]), s32 *, 0xA0) = 0;
}

void pppDrawMdlLoopDes(void) {

}

void pppDrawMdlLoopZCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[2]), s32 *, 0xA0) = 0;
}

void pppDrawMdlLoopZDes(void) {

}

void pppKeThDes(void) {

}

void pppKeThTp2Con(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xC) = 1.0f;
    M2C_FIELD(temp_a0, s32 *, 0x1C) = 0;
}

void pppKeThHitBornCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[1]), s8 *, 0xA0) = 0;
}

void pppKeBornRndCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s16 *, 0xA0) = 0;
}

void pppKeBornRnd2Con(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s16 *, 0xA0) = 0;
}

void pppKeBornRnd3Con(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s16 *, 0xA0) = 0;
}

void pppKeBornRnd4Con(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s16 *, 0xA0) = 0;
}

void pppKeBornPtCmplCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), s32 *, 0xA0) = 0;
}

void pppKeMdlBmpDraw(void) {

}

void pppKeMdlBmpCon(void) {

}

void pppKeMdlBmpReset(void) {

}

void pppKeAcmSolidFn18(void) {

}
