/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

extern M2C_UNK D_003701D0;
extern M2C_UNK D_003701E0;
extern void *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
void func_00183be0(s32, s32);
void func_001a5250(s32, s32);
void func_001a52e0(s32, s32);
void func_001a5370(s32, s32);
void func_001a5400(s32, s32);
void func_001a5490(s32, s32);
void func_001a5fd0(s32, s32, s32);
void func_001a60d0(s32);

void pppKeLnsLpReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA8) = 0;
}

void func_00192208(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v1_2;
    void *temp_a2;
    void *temp_s0;
    void *temp_v1;

    temp_a2 = M2C_FIELD(arg2, void **, 0xC);
    temp_v1 = arg0 + M2C_FIELD(temp_a2, s32 *, 0);
    temp_s0 = temp_v1 + 0xA0;
    if (M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0xC)) {
        M2C_FIELD(temp_v1, s32 *, 0xA0) = (s32) (arg0 + M2C_FIELD(temp_a2, s32 *, 4) + 0xA0);
        temp_v1_2 = M2C_FIELD(arg1, s32 *, 4);
        if (temp_v1_2 == 0xFFFF) {
            M2C_FIELD(temp_s0, s32 *, 4) = 0;
        } else {
            temp_v0 = M2C_FIELD(D_00615E64, s32 *, 0x14) + (temp_v1_2 * 8);
            if (temp_v0 != M2C_FIELD(temp_s0, s32 *, 4)) {
                func_001a5fd0((s32) temp_s0, temp_v0, (s32) M2C_FIELD(arg1, u8 *, 0x16));
            }
        }
        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0x12);
        M2C_FIELD(temp_s0, u16 *, 0xC) = (u16) M2C_FIELD(arg1, u16 *, 0x10);
        M2C_FIELD(temp_s0, u8 *, 0xE) = (u8) M2C_FIELD(arg1, u8 *, 0x17);
    }
}

void pppKeLnsClmCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0;
    func_001a60d0(temp_s0);
    M2C_FIELD(temp_s0, s8 *, 8) = 4;
}

void pppKeLnsLpTReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA8) = 0;
}

void pppKeMatSNCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0x80) = 0;
    M2C_FIELD(temp_a0, s32 *, 0x84) = 0;
    M2C_FIELD(temp_a0, s32 *, 0x88) = 0;
}

void pppKeTkFadeCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}

void pppKeMdlTfd3Con(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}

void pppDrawShapeXCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
    M2C_FIELD(temp_a0, s16 *, 0xA0) = 0;
}

void pppRyjMatrixWorldCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_00183be0(temp_s0, (s32) &D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

void pppRyjMatrixWorldXZYCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a5250(temp_s0, (s32) &D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

void pppRyjMatrixWorldYXZCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a5370(temp_s0, (s32) &D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

void pppRyjMatrixWorldYZXCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a52e0(temp_s0, (s32) &D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

void pppRyjMatrixWorldZXYCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a5400(temp_s0, (s32) &D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

void pppRyjMatrixWorldZYXCon(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 0xC) + 0xA0;
    func_001a5490(temp_s0, (s32) &D_003701E0);
    M2C_FIELD(temp_s0, f32 *, 0x30) = (f32) M2C_FIELD(&D_003701D0, f32 *, 0);
    M2C_FIELD(temp_s0, f32 *, 0x34) = (f32) M2C_FIELD(&D_003701D0, f32 *, 4);
    M2C_FIELD(temp_s0, f32 *, 0x38) = (f32) M2C_FIELD(&D_003701D0, f32 *, 8);
}

void pppRyjDrawShipolyCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s8 *, 5) = 1;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s8 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}

void pppRyjMegaPlaceModelCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg1, void **, 0xC);
    temp_a0 = arg0 + M2C_FIELD(temp_v1, s32 *, 0) + 0xA0;
    M2C_FIELD((arg0 + M2C_FIELD(temp_v1, s32 *, 4)), s8 *, 0xA0) = 0;
    M2C_FIELD(temp_a0, s32 *, 4) = (s32) (M2C_FIELD(temp_a0, s32 *, 4) + 1);
}

void pppRyjMegaPlaceLampCon(s32 arg0, void *arg1) {
    void *temp_a0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg1, void **, 0xC);
    temp_a0 = arg0 + M2C_FIELD(temp_v1, s32 *, 0) + 0xA0;
    M2C_FIELD((arg0 + M2C_FIELD(temp_v1, s32 *, 4)), s8 *, 0xA0) = 0;
    M2C_FIELD(temp_a0, s32 *, 8) = (s32) (M2C_FIELD(temp_a0, s32 *, 8) + 1);
}
