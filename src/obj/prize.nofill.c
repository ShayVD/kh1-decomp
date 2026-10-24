/* Prizes, the HP / MP balls and munny an enemy drops (a guess from the
 * code): the drop table of an object (func_00144e88, func_00144eb0 spawns
 * d->cnt[i] of each of 7 kinds), the 0x3000-byte pool D_0052EB60 with its
 * per-prize records D_0035C710 and free list D_0052EB50 / D_0052EB58
 * (func_00146188 spawns one, func_00145ce8 updates one), the ground probe
 * D_00531B60, the drop rate D_00306844 / D_00306848, and an object's
 * attached effect (func_00145188, func_00145240). Flag mode: nofill (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 53"). */
#include "m2c.h"

/* func_00144e88 (from hand/nofill/text_00140000_1.c). */
extern M2C_UNK D_00304E40;
void *func_00144e88(s32 arg0) {
    return (s8 *)&D_00304E40 + (arg0 * 0xD);
}

