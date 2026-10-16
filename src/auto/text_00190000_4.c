/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

M2C_UNK func_001a5ca0(void *);
extern u8 D_00372708;
extern void *D_00615E60;

void pppKeLnsLpTCon(s32 arg0, PppEntry *arg1) {
    void *temp_s0;

    temp_s0 = arg0 + arg1->offsets[0] + 0xA0;
    func_001a5ca0(temp_s0);
    M2C_FIELD(temp_s0, s32 *, 0x9C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0xA8) = 0;
    M2C_FIELD(temp_s0, u8 *, 0x8C) = (u8) D_00372708;
    M2C_FIELD(temp_s0, s8 *, 0x8D) = 2;
    M2C_FIELD(temp_s0, s8 *, 0xC0) = 0;
    M2C_FIELD(temp_s0, s8 *, 0xC1) = 0;
    D_00372708 += 1;
}

void pppRyjDrawShipolyBoneCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[1];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s8 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s8 *, 5) = 1;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(D_00615E60, s8 *, 0xB3) = 1;
}
