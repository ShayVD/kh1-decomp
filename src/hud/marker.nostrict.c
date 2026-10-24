/* Markers over actors (docs/modules.md "Session 46"), nostrict part:
 * func_0023c4d8 takes a free marker (func_0023c228), gives it the marker
 * sprite D_00651300, the kind a1, a2 / a3 and the actor pair *a0, and
 * returns its index (-1 when all ten are in use). */
#include "common.h"
#include "data/types/nostrict_text_00230000_s6_24_p2.h"

extern Slot D_00651310[10];
extern B192 *D_00651300; /* src/data/bss_0065.c: u8 *D_00651300 */
Slot *func_0023c228(void);

s32 func_0023c4d8(P8 *a0, s32 a1, s32 a2, s32 a3) {
    Slot *e = func_0023c228();
    if (e == 0) return -1; { B192 *s = D_00651300; e->x8 = a1; e->blk = *s; } e->xd0 = a2; e->xd4 = a3; e->xd8 = *a0;
    return e - D_00651310;
}
