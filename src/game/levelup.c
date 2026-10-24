/* Level-up, default flags (docs/modules.md "Session 52"): func_0015b438.
 * The rest is in levelup.nostrict.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"

/* func_0015b438 (from auto/text_00150000_3.c). */
M2C_UNK func_00148768(s32, M2C_UNK, s32 *, M2C_UNK, f32);
s32 *func_0013daf8();
s32 func_00122ff8(s32 *);
void func_0015b438(u32 id) {
    s32 *temp_v0;

    temp_v0 = func_0013daf8(id);
    if ((func_00122ff8(temp_v0) != 0) && (*temp_v0 & 0x8000)) {
        func_00148768(D_00350CE0, 0x15, temp_v0, 0x8003, 0);
    }
}

