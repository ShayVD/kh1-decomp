/* The pppKeMdlTfd3 and pppKeMdlTfdUv3 classes' Cons, default flags
 * (docs/modules.md "Session 50"); the draws are in kemdltfd3.nostrict.c.
 * Read from the code, not proved by a boot. */

/* pppKeMdlTfd3Con (from auto/text_00190000_2.c). */
#include "m2c.h"
#include "ppp.h"
void pppKeMdlTfd3Con(s32 arg0, PppEntry *arg1) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + arg1->offsets[2];
    temp_a0_2 = temp_a0 + 0xA0;
    M2C_FIELD(temp_a0, s32 *, 0xA0) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_a0_2, s32 *, 8) = 0;
}

/* pppKeMdlTfdUv3Con (from hand/ppp.c). */
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
void pppKeMdlTfdUv3Con(void *obj, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);

    w[0] = w[1] = w[2] = w[4] = w[5] = w[6] = w[7] = w[8] = w[9] = 0.0f;
}
#undef PPP_WORK

