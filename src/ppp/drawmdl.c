/* The pppDrawMdlTs2 and pppDrawMdlTs3 classes' Cons, default flags
 * (docs/modules.md "Session 50"); the rest of the model draw classes are in
 * drawmdl.nostrict.c.  Read from the code, not proved by a boot. */

/* pppDrawMdlTs2Con (from hand/ppp.c). */
#include "ppp.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
void pppDrawMdlTs2Con(void *obj, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);

    w[0] = w[1] = w[2] = w[3] = w[4] = w[5] = 0.0f;
}

/* pppDrawMdlTs3Con (from hand/ppp.c). */
void pppDrawMdlTs3Con(void *obj, PppEntry *e) {
    f32 *w = PPP_WORK(f32, obj, e, 2);

    w[0] = w[1] = w[2] = w[3] = w[4] = w[5] = 0.0f;
}

