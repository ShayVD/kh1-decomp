/* wm.x func_00f2ab48: matched by hand. */
#include "ovl.h"

typedef struct { s16 id; s16 pad; s32 x; } WmId8;
extern WmId8 D_00F8BC98[];
s32 func_00f2ab48(s32 arg0) {
    s32 i;
    for (i = 0; D_00F8BC98[i].id >= 0; i++) {
        if (D_00F8BC98[i].id == arg0) {
            return i;
        }
    }
    return -1;
}
