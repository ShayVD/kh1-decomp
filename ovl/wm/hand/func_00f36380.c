/* wm.x func_00f36380: matched by hand. */
#include "ovl.h"

typedef struct { s32 used; u8 pad[0xDC]; } S;
extern S D_00F8C530[];
s32 func_00f36380(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (D_00F8C530[i].used == 0) return i;
    }
    return -1;
}
