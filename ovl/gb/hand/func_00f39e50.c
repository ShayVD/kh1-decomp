/* gb.x func_00f39e50: matched by hand. */
#include "ovl.h"

extern u8 *D_00F56DC0;

s32 func_00f39e50(s32 arg0) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (D_00F56DC0[i] == arg0) {
            return 1;
        }
    }
    return 0;
}
