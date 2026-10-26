/* wm.x func_00f2b298: matched by hand. */
#include "ovl.h"

void func_001c0da0(s32, s32, s8 *);
CONTEXT_ONLY s32 func_00f2ab98(s32 arg0) {
    s8 b[16];
    func_001c0da0(arg0 + 752, 1, b);
    return b[0];
}
s32 func_00f2b298(s32 arg0) {
    if (arg0 == 17 || arg0 == 12) {
        switch (func_00f2ab98(10)) {
        case 2: return 17;
        case 3: return 18;
        }
    }
    return arg0;
}
