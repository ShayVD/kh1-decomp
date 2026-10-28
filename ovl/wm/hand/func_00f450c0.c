/* wm.x func_00f450c0: matched by hand. */
#include "ovl.h"

s32 func_00f20ac8(void);
s32 func_00f35070(void);

s32 func_00f450c0(s32 arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        if (func_00f20ac8() != arg0) {
            break;
        }
        return 1;
    case 1:
        if (func_00f20ac8() == arg0) {
            break;
        }
        return 1;
    case 2:
        if (func_00f35070() != arg0) {
            break;
        }
        return 1;
    case 3:
        if (func_00f35070() == arg0) {
            break;
        }
        return 1;
    }
    return 0;
}
