/* wm.x func_00f36218: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xE0]; s32 used; u8 pad2[0x2C]; } S;
extern S D_00FCE390[];
s32 func_00f36218(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00FCE390[i].used == 0) return i;
    }
    return -1;
}
