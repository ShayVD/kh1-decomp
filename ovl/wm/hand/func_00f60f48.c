/* wm.x func_00f60f48: matched by hand. */
#include "ovl.h"

extern u8 *D_00F9B540;

s32 func_00f60f48(s32 arg0) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (D_00F9B540[i] == arg0) {
            return 1;
        }
    }
    return 0;
}
