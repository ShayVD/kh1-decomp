/* wm.x func_00f67380: matched by hand. */
#include "ovl.h"

s32 func_00f65ac0(s32);
s32 func_00f65d18(s32, s32, s32, s32);
s32 func_00f66d30(s32);
void func_00f670c8(s32);

s32 func_00f67380(s32 a, s32 b, s32 c) {
    /* register pins: gcc otherwise allocates s0-s4 in a different order */
    register s32 cur asm("s0") = c;
    register s32 prev asm("s1") = a;
    register s32 c0 asm("s4") = cur;
    register s32 i asm("s2");
    s32 r;
    for (i = 0; i < func_00f65ac0(b); i++) {
        cur = func_00f65d18(cur, prev, b, i);
        prev = -1;
    }
    r = func_00f66d30(cur);
    func_00f670c8(c0);
    return r;
}
