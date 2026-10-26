/* wm.x func_00f680f8: the twin of gb.x func_00f41000 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[0x14]; s32 flags; u8 pad18[0x2E]; u8 b46; u8 pad47[1]; } E48;
extern E48 *D_00FB49E8;
s32 func_00f680f8(void) {
    s32 i;
    E48 *e = D_00FB49E8;
    for (i = 0; i < 0x100; i++, e++) {
        if (!(e->flags & 3) && e->b46 == 0) {
            return i;
        }
    }
    return -1;
}
