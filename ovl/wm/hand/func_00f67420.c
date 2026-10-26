/* wm.x func_00f67420: matched by hand. */
#include "ovl.h"

void func_00f66fe8(s32, s32);
s32 func_00f65ac0(s32);
s32 func_00f65d18(s32, s32, s32, s32);
void func_00f66d30(s32);

void func_00f67420(s32 x, s32 a, s32 b, s32 c) {
    /* register pin: gcc otherwise swaps the loop counter and a (s0/s1) */
    register s32 i asm("s1");
    func_00f66fe8(x, c);
    for (i = 0; i < func_00f65ac0(b); i++) {
        c = func_00f65d18(c, a, b, i);
        a = -1;
    }
    func_00f66d30(c);
}
