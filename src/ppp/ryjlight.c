/* The pppRyjLight class's Con and Des (docs/modules.md "Session 49"): the
 * work's light pointer starts empty and func_00122768 frees the light.
 * ryjlight.nostrict.c has the frame.  Read from the code. */
#include "m2c.h"
#include "ppp.h"

void pppRyjLightCon(s32 arg0, PppEntry *arg1) {
    M2C_FIELD((arg0 + arg1->offsets[2]), s32 *, 0xA0) = 0;
}

void func_00122768(void *);

void pppRyjLightDes(void *obj, PppEntry *e) {
    void **w = (void **) ((u8 *) obj + e->offsets[2] + 0xA0);

    if (*w) {
        func_00122768(*w);
        *w = NULL;
    }
}
