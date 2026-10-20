/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern void *D_0063F744; /* src/data/bss_0063.c: u8 *D_0063F744 */
extern void *D_0063F748; /* src/data/bss_0063.c: u16 *D_0063F748 */

void func_001efb30(void *arg0) {
    D_0063F744 = arg0 + M2C_FIELD(arg0, s32 *, 0x14);
    D_0063F748 = arg0 + M2C_FIELD(arg0, s32 *, 0x10);
}
