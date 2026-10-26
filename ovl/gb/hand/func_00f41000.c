/* gb.x func_00f41000: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x14]; s32 flags; u8 pad18[0x2E]; u8 b46; u8 pad47[1]; } E48;
extern E48 *D_00F70268;
s32 func_00f41000(void) {
    s32 i;
    E48 *e = D_00F70268;
    for (i = 0; i < 0x100; i++, e++) {
        if (!(e->flags & 3) && e->b46 == 0) {
            return i;
        }
    }
    return -1;
}
