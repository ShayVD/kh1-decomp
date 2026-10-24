/* Lookups into the game's data tables (D_00547BA0 ... D_00547BB0,
 * D_00533BA0, D_00308874, D_00308C70): func_00147860 an item's stat bonuses,
 * func_00147840 an item's record, func_001478e0 sets the tables up. Flag
 * mode: nofill (the other modes are in the sibling files). Read from the
 * code, not proved by a boot (docs/modules.md "Session 53"). */
#include "m2c.h"

/* func_001477c8 (from hand/nofill/text_00140000_1.c). */
extern M2C_UNK D_00533BA0;
void *func_001477c8(s32 arg0) {
    return (s8 *)&D_00533BA0 + arg0;
}

