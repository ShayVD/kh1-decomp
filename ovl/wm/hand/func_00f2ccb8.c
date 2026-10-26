/* wm.x func_00f2ccb8: matched by hand. */
#include "ovl.h"

typedef struct { u8 used; u8 pad[0x8F]; } S;
extern S D_00FBEBC0[];
s32 func_00f2ccb8(void) {
    s32 i;
    for (i = 0; i < 384; i++) {
        if (D_00FBEBC0[i].used == 0) return i;
    }
    return -1;
}
