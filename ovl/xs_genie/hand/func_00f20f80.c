/* xs_genie.x func_00f20f80: matched by hand. */
#include "ovl.h"

typedef struct { s32 used; u8 pad[0x3C]; } Gn40;
extern Gn40 D_00FC1A60[10];
Gn40 *func_00f20f80(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (D_00FC1A60[i].used == 0) {
            D_00FC1A60[i].used = 1;
            return &D_00FC1A60[i];
        }
    }
    return NULL;
}
