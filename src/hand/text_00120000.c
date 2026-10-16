/* Hand-matched functions (session 3). Grouped by address like src/auto/;
 * the original translation units are not known yet. */
#include "m2c.h"

/* *slot holds an object pointer; replace it with bit 35 of the object's
 * 64-bit flag word at +0x370. */
void func_0012a030(s32 *slot) {
    *slot = (s32) (M2C_FIELD(*slot, u64 *, 0x370) >> 35) & 1;
}
