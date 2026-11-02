/* wm.x func_00f67278: matched by hand. */
#include "ovl.h"

s32 func_00f65ac0(s32);
s32 func_00f65d18(s32, s32, s32, s32);
void *func_00f66d30(s32);

void *func_00f67278(s32 a, s32 b, s32 c) {
    s32 i;
    for (i = 0; i < func_00f65ac0(b); i++) {
        c = func_00f65d18(c, a, b, i);
        a = -1;
    }
    return func_00f66d30(c);
}
