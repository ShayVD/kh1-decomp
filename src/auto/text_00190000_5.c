/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"


void pppKeShpTail3Reset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s64 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x10) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x18) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x20) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x28) = 0;
}

void pppKeShpTailLcCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s8 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s8 *, 1) = 0;
    M2C_FIELD(temp_a0, s8 *, 0xA0) = 0x1F;
}

void pppKeShpTail3XReset(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s64 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x10) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x18) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x20) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x28) = 0;
}
