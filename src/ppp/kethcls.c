/* The pppKeTh classes' default-flag functions (docs/modules.md "Session
 * 50"): pppKeTh's Des, the Cons of pppKeThTp / Tp2, KeThHitBorn and KeThSft,
 * and the 24 pppKeThRes Cons, each of which sets up its owner's node pool
 * with keth.c's func_001a8920 for its size (8 ... 255 nodes, times 4 ...
 * 128 lists).  The frames and draws are in kethcls.nostrict.c.  Read from
 * the code, not proved by a boot. */
#include "m2c.h"
#include "ppp.h"
#include "data/pieces/D_00370130.h"
#include "data/pieces/D_00364130.h"
#include "data/pieces/D_002BBFA0.h"

/* pppKeThDes (from auto/text_00180000.c). */
void pppKeThDes(void) {

}

/* pppKeThTpCon (from auto/text_00180000_3.c). */
void pppKeThTpCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0x1C) = 0;
    M2C_FIELD(temp_a0, s32 *, 0xC) = 0;
}

/* pppKeThTp2Con (from auto/text_00180000.c). */
void pppKeThTp2Con(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[0] + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xC) = 1.0f;
    M2C_FIELD(temp_a0, s32 *, 0x1C) = 0;
}

/* pppKeThResCon (from auto/text_00180000_5.c). */
M2C_UNK func_001a8920(s32, M2C_UNK, M2C_UNK);
void pppKeThResCon(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 3);
}

/* pppKeThRes8Con (from auto/text_00180000_5.c). */
void pppKeThRes8Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 8);
}

/* pppKeThRes8x4Con (from auto/text_00180000_5.c). */
void pppKeThRes8x4Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 4, 8);
}

/* pppKeThRes8x128Con (from auto/text_00180000_5.c). */
void pppKeThRes8x128Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 0x80, 8);
}

/* pppKeThRes16Con (from auto/text_00180000_5.c). */
void pppKeThRes16Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 0x10);
}

/* pppKeThRes16x4Con (from auto/text_00180000_5.c). */
void pppKeThRes16x4Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 4, 0x10);
}

/* pppKeThRes16x64Con (from auto/text_00180000_5.c). */
void pppKeThRes16x64Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 0x40, 0x10);
}

/* pppKeThRes24Con (from auto/text_00180000_5.c). */
void pppKeThRes24Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 0x18);
}

/* pppKeThRes24x4Con (from auto/text_00180000_5.c). */
void pppKeThRes24x4Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 4, 0x18);
}

/* pppKeThRes32Con (from auto/text_00180000_5.c). */
void pppKeThRes32Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 0x20);
}

/* pppKeThRes32x4Con (from auto/text_00180000_5.c). */
void pppKeThRes32x4Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 4, 0x20);
}

/* pppKeThRes32x32Con (from auto/text_00180000_5.c). */
void pppKeThRes32x32Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 0x20, 0x20);
}

/* pppKeThRes40Con (from auto/text_00180000_5.c). */
void pppKeThRes40Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 0x28);
}

/* pppKeThRes40x4Con (from auto/text_00180000_5.c). */
void pppKeThRes40x4Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 4, 0x28);
}

/* pppKeThRes48Con (from auto/text_00180000_5.c). */
void pppKeThRes48Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 0x30);
}

/* pppKeThRes48x4Con (from auto/text_00180000_5.c). */
void pppKeThRes48x4Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 4, 0x30);
}

/* pppKeThRes64Con (from auto/text_00180000_5.c). */
void pppKeThRes64Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 0x40);
}

/* pppKeThRes64x4Con (from auto/text_00180000_5.c). */
void pppKeThRes64x4Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 4, 0x40);
}

/* pppKeThRes64x16Con (from auto/text_00180000_5.c). */
void pppKeThRes64x16Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 0x10, 0x40);
}

/* pppKeThRes128Con (from auto/text_00180000_5.c). */
void pppKeThRes128Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 0x80);
}

/* pppKeThRes128x4Con (from auto/text_00180000_5.c). */
void pppKeThRes128x4Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 4, 0x80);
}

/* pppKeThRes128x8Con (from auto/text_00180000_5.c). */
void pppKeThRes128x8Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 8, 0x80);
}

/* pppKeThRes255Con (from auto/text_00180000_5.c). */
void pppKeThRes255Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 1, 0xFF);
}

/* pppKeThRes255x4Con (from auto/text_00180000_5.c). */
void pppKeThRes255x4Con(s32 arg0, PppEntry *arg1) {
    func_001a8920(arg0 + arg1->offsets[0] + 0xA0, 4, 0xFF);
}

/* pppKeThHitBornCon (from auto/text_00180000.c). */
void pppKeThHitBornCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[1]), s8 *, 0xA0) = 0;
}

/* pppKeThSftCon (from auto/text_00180000_9.c). */
void pppKeThSftCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s32 *, 0x28) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0x20) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0x24) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 0x2C) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x0) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 8) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x10) = 0;
    M2C_FIELD(temp_a0_2, s64 *, 0x18) = 0;
}

