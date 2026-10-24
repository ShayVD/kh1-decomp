/* The pppDrawShapeX and pppKeShpTailX / Tail2X / Tail3X classes' Cons and
 * Reset, default flags (docs/modules.md "Session 50"): they clear the work
 * areas (Tail3X seeds its random phase with rand()).  The frames and draws
 * are in keshptailx.nostrict.c.  Read from the code, not proved by a boot. */

/* pppDrawShapeXCon (from auto/text_00190000_2.c). */
#include "m2c.h"
#include "ppp.h"
void pppDrawShapeXCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
    M2C_FIELD(temp_a0, s16 *, 0xA0) = 0;
}

/* pppKeShpTailXCon (from auto/text_00190000_9.c). */
void pppKeShpTailXCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s8 *, 0xA0) = 0x1F;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 6) = 0;
    M2C_FIELD(temp_a0_2, s8 *, 1) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
}

/* pppKeShpTail2XCon (from auto/text_00190000_9.c). */
void pppKeShpTail2XCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s8 *, 0xA0) = 0x1F;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 6) = 0;
    M2C_FIELD(temp_a0_2, s8 *, 1) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
}

/* pppKeShpTail3XCon (from auto/text_00190000_9.c). */
s16 rand();
void pppKeShpTail3XCon(s32 arg0, PppEntry *arg1) {
    s16 temp_v0;
    void *temp_s0;
    void *temp_s0_2;

    temp_s0 = arg0 + arg1->offsets[0];
    temp_s0_2 = temp_s0 + 0xA0;
    M2C_FIELD(temp_s0_2, s8 *, 0x1FA) = 0;
    M2C_FIELD(temp_s0_2, s16 *, 0x1F4) = 0;
    M2C_FIELD(temp_s0_2, s32 *, 0x1F0) = 0;
    temp_v0 = rand();
    M2C_FIELD(temp_s0, s64 *, 0xA0) = 0;
    M2C_FIELD(temp_s0_2, s64 *, 0x28) = 0;
    M2C_FIELD(temp_s0_2, s64 *, 8) = 0;
    M2C_FIELD(temp_s0_2, s64 *, 0x10) = 0;
    M2C_FIELD(temp_s0_2, s64 *, 0x18) = 0;
    M2C_FIELD(temp_s0_2, s64 *, 0x20) = 0;
    M2C_FIELD(temp_s0_2, s16 *, 0x1F8) = temp_v0;
}

/* pppKeShpTail3XReset (from auto/text_00190000_5.c). */
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

