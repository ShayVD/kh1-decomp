/* Party heal objects, default flags (docs/modules.md "Session 52"):
 * func_00156c28.  The rest is in objheal.nostrict.c and
 * objheal.nostrict_nogcse.c.  Read from the code, not proved by a boot. */
#include "m2c.h"

/* func_00156c28 (from auto/text_00150000_1.c). */
M2C_UNK func_001247e8(void *);
M2C_UNK func_0013c2a0(s16, M2C_UNK);
void *func_00123488();
void func_00156c28(u32 id) {
    void *temp_v0;

    temp_v0 = func_00123488(id);
    func_0013c2a0(M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x130), s16 *, 0x48), 1);
    func_001247e8(temp_v0);
}

