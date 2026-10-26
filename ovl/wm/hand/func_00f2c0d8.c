/* wm.x func_00f2c0d8: matched by hand. */
#include "ovl.h"

extern s32 D_00FBDBB8[128];
/* no return value when out of range (the original returns whatever is in v0) */
s32 func_00f2c0d8(u32 arg0) {
    if (arg0 < 128) {
        return ++D_00FBDBB8[arg0];
    }
}
