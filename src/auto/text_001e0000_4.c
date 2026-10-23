/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0063.h"

#include "data/pieces/D_003DBA68.h"
extern s32 D_003F7A68;
extern s32 D_0063F740;
extern s32 D_0063F744; /* src/data/bss_0063.c: u8 *D_0063F744 */
extern s32 D_0063F748; /* src/data/bss_0063.c: u16 *D_0063F748 */

/* func_001e2a30, func_001e31b0, func_001e32c8, func_001e3728, func_001e39f0, func_001e3ef0 are in src/shop/shop.c. */

/* func_001e6578, func_001e6b70, func_001e7928, func_001e7a60, func_001e7b48 are in src/list/list.c. */

/* func_001e8e68 is in src/event/sound.c. */

/* func_001e9650 is in src/screen/wave.c. */

void func_001efb18(s32 arg0, s32 arg1) {
    D_0063F744 = arg0;
    D_0063F748 = arg1;
}

void func_001efb58(s32 arg0) {
    D_0063F740 = arg0 * 0x10;
}

s32 func_001efb68(void) {
    return (s32) D_0063F740 >> 4;
}
#include "data/data_003D.h"
#include "data/data_003F.h"
#include "data/pieces/D_003F7A68.h"
