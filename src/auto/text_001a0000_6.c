/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

extern volatile void *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */

void pppRyjMegaBirthFilterCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s8 *, 0x12) = 1;
    M2C_FIELD(temp_a0_2, s32 *, 0x0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 0x10) = 0;
    M2C_FIELD(temp_a0_2, f32 *, 0xC) = 1.0f;
    M2C_FIELD(D_00615E60, s8 *, 0xB3) = 1;
}

void pppRyjMegaBirthModelFilterCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s8 *, 0x12) = 1;
    M2C_FIELD(temp_a0_2, s32 *, 0x0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 0x10) = 0;
    M2C_FIELD(temp_a0_2, f32 *, 0xC) = 1.0f;
    M2C_FIELD(D_00615E60, s8 *, 0xB3) = 1;
}
