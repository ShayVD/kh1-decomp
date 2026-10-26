/* gb.x func_00f23bd0: matched by hand. */
#include "ovl.h"

s32 func_001ba3f0(s32);
s32 func_001bb720(void);
s32 func_001bb730(void);

s32 func_00f23bd0(void) {
    s32 i;
    for (i = 0; i < func_001bb720(); i++) {
        if (i != 49 && func_001ba3f0(i) > 0) {
            return i;
        }
    }
    for (i = 128; i < func_001bb730() + 128; i++) {
        if (func_001ba3f0(i) > 0) {
            return i;
        }
    }
    return 0;
}
