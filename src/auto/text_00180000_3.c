/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

extern M2C_UNK D_00364130;
extern void *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
s32 func_00180f18(s32, s32, s32, s32);
void func_00267620(s32);

void func_00181238(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_00180f18(arg0, 0xA, arg1, (s32) M2C_FIELD(arg1, u8 *, 0x91));
    if (temp_v0 < 0) {
        M2C_FIELD(arg1, s16 *, 0xA4) = 0;
        return;
    }
    M2C_FIELD(arg1, s16 *, 0xA4) = (s16) ((temp_v0 << 7) + 0x3800);
}

s32 func_00181318(void) {
    s8 *var_a0;
    s32 var_a1;
    s32 var_a2;
    u16 temp_v1;

    var_a2 = 0;
    var_a0 = &D_00364130;
    var_a1 = 0xFF;
    do {
        temp_v1 = M2C_FIELD(var_a0, u16 *, 0x86);
        if ((temp_v1 & 1 & 0xFFFF) && !(temp_v1 & 4)) {
            var_a2 += M2C_FIELD(M2C_FIELD(var_a0, void **, 0x8C), s32 *, 0xF0);
        }
        var_a1 -= 1;
        var_a0 += 0xC0;
    } while (var_a1 >= 0);
    return var_a2;
}

void pppAngleCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
}

void pppAngMoveCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
}

void pppAngAcceleCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
}

void pppMatrixLocFrame(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC) + 0xA0;
    func_00267620((s32) (D_00615E68 + 0x10));
    M2C_FIELD(D_00615E68, f32 *, 0x40) = (f32) M2C_FIELD(temp_s0, f32 *, 0);
    M2C_FIELD(D_00615E68, f32 *, 0x44) = (f32) M2C_FIELD(temp_s0, f32 *, 4);
    M2C_FIELD(D_00615E68, f32 *, 0x48) = (f32) M2C_FIELD(temp_s0, f32 *, 8);
}

void pppDrawShapeCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
    M2C_FIELD(temp_a0, s16 *, 0xA0) = 0;
}

void pppAngMoveLoopCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
}

void pppKeThTpCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0x1C) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xC) = 0;
}

void pppKeMdlTfdCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}

void pppKeMdlTfd2Con(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}
