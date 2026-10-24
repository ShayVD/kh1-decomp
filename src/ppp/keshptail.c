/* The ppp shape-tail classes' default-flag functions (docs/modules.md
 * "Session 50"): the Cons and Resets of pppKeShpTail / Tail2 / Tail3 (Tail3
 * seeds its random phase with rand()), and the classes pppKeShpTailPht and
 * pppKeShpTailLc, whose frames and draws are empty.  The frames and draws of
 * Tail2 and Tail3 are in keshptail.nostrict.c, the "X" variants in
 * keshptailx*.c.  Read from the code, not proved by a boot. */

/* pppKeShpTailCon (from auto/text_00190000_9.c). */
#include "m2c.h"
#include "ppp.h"
void pppKeShpTailCon(s32 arg0, PppEntry *arg1) {
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

/* pppKeShpTail2Con (from auto/text_00190000_9.c). */
void pppKeShpTail2Con(s32 arg0, PppEntry *arg1) {
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

/* pppKeShpTail3Con (from auto/text_00190000_9.c). */
s16 rand();
void pppKeShpTail3Con(s32 arg0, PppEntry *arg1) {
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

/* pppKeShpTail3Reset (from auto/text_00190000_5.c). */
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

/* pppKeShpTailPhtFrame (from auto/text_00190000.c). */
void pppKeShpTailPhtFrame(void) {

}

/* pppKeShpTailPhtDraw (from auto/text_00190000.c). */
void pppKeShpTailPhtDraw(void) {

}

/* pppKeShpTailPhtCon (from auto/text_00190000.c). */
void pppKeShpTailPhtCon(void) {

}

/* pppKeShpTailPhtReset (from auto/text_00190000.c). */
void pppKeShpTailPhtReset(void) {

}

/* pppKeShpTailLcFrame (from auto/text_00190000.c). */
void pppKeShpTailLcFrame(void) {

}

/* pppKeShpTailLcDraw (from auto/text_00190000.c). */
void pppKeShpTailLcDraw(void) {

}

/* pppKeShpTailLcCon (from auto/text_00190000_5.c). */
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

