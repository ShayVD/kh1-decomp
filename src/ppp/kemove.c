/* The ppp motion classes' default-flag functions (docs/modules.md "Session
 * 50"): the Cons of pppKeHmgEff (homing), pppKeGrvEff (gravity towards a
 * target), pppKeHitBorn and pppKeHitChkPxB, and the small classes
 * pppKeGrvTgt and pppKeHitBall (each marks its owner as a target with two
 * strengths at its key's frame) and pppKeDrct (sets a direction).  The
 * motion frames are in kemove.nostrict.c.  Read from the code, not proved
 * by a boot. */

/* pppKeHmgEffCon (from auto/text_00190000.c). */
#include "m2c.h"
#include "ppp.h"
void pppKeHmgEffCon(void) {

}

/* pppKeGrvTgtFrame (from hand/text_00180000_h12.c). */
#include "common.h"
#include "data/pieces/D_00364130.h"
#include "data/types/text_00180000_h12.h"
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject;
typedef union {
    f32 f;
    s32 i;
} PppWord;
typedef struct {
    s32 frame;
    PppWord a, b;
} PppKeyF2;
typedef struct {
    PppWord a, b;
    s32 tgt;
} PppGrvTgt;
void pppKeGrvTgtFrame(PppObject *obj, PppKeyF2 *k, PppEntry *e) {
    if (obj->frame == k->frame) {
        PppGrvTgt *w = (PppGrvTgt *) ((u8 *) obj + e->offsets[1] + 0xA0);
        w->a.f = k->a.f;
        w->b.f = k->b.f;
        w->tgt = (s32) obj + e->offsets[0] + 0xA0;
    }
}

/* pppKeGrvTgtCon (from auto/text_00190000.c). */
void pppKeGrvTgtCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[1]), s32 *, 0xA8) = 0;
}

/* pppKeGrvEffCon (from auto/text_00190000.c). */
void pppKeGrvEffCon(void) {

}

/* pppKeHitBallFrame (from hand/text_00180000_h12.c). */
typedef struct {
    PppWord a;
    s32 tgt;
} PppHitBall;
void pppKeHitBallFrame(PppObject *obj, PppKeyF2 *k, PppEntry *e) {
    if (obj->frame == k->frame) {
        PppHitBall *w = (PppHitBall *) ((u8 *) obj + e->offsets[1] + 0xA0);
        w->tgt = (s32) obj + e->offsets[0] + 0xA0;
        w->a.f = k->a.f;
    }
}

/* pppKeHitBallCon (from auto/text_00190000.c). */
void pppKeHitBallCon(void) {

}

/* pppKeHitBornCon (from auto/text_00190000.c). */
void pppKeHitBornCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[2]), s8 *, 0xA0) = 0;
}

/* pppKeHitChkPxBCon (from auto/text_00190000.c). */
void pppKeHitChkPxBCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;

    temp_a0 = arg0 + arg1->offsets[2] + 0xA0;
    M2C_FIELD(temp_a0, f32 *, 0xC) = 1.0f;
    M2C_FIELD(temp_a0, s8 *, 0x10) = 0;
}

/* pppKeDrctFrame (from auto/text_00190000.c). */
void pppKeDrctFrame(void *arg0, void *arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    if (M2C_FIELD(arg0, s32 *, 0xC) == M2C_FIELD(arg1, s32 *, 0)) {
        temp_v0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC);
        temp_v0_2 = temp_v0 + 0xA0;
        M2C_FIELD(temp_v0, f32 *, 0xA0) = (f32) M2C_FIELD(arg1, f32 *, 4);
        M2C_FIELD(temp_v0_2, f32 *, 4) = (f32) M2C_FIELD(arg1, f32 *, 8);
        M2C_FIELD(temp_v0_2, f32 *, 8) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
    }
}

/* pppKeDrctCon (from auto/text_00190000.c). */
void pppKeDrctCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[0]), f32 *, 0xAC) = 1.0f;
}

#include "data/bss_0061_mixed.h"
#include "data/types/text_00180000_h12_p.h"
#include "data/data_0037.h"
