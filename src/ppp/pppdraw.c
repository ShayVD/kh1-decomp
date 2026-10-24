/* The pppDrawMdlTs and pppDrawShape classes' Cons, default flags
 * (docs/modules.md "Session 50"); the draws are in pppdraw.nostrict.c.  Read
 * from the code, not proved by a boot. */
#include "ppp.h"
#include "m2c.h"
#include "data/pieces/D_00364130.h"

/* pppDrawMdlTsCon (from hand/ppp.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
void pppDrawMdlTsCon(void *obj, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);

    w[0] = w[1] = w[2] = w[3] = w[4] = w[5] = 0.0f;
}
#undef PPP_WORK

/* pppDrawShapeCon (from auto/text_00180000_3.c). */
void pppDrawShapeCon(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[0];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
    M2C_FIELD(temp_a0, s16 *, 0xA0) = 0;
}

