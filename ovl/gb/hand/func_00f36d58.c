/* gb.x func_00f36d58: matched by hand. */
#include "ovl.h"

s32 func_00f3f6c0(s32, void *, s32);
extern u8 D_00F616D0[];
extern u8 D_00F61780[];

void func_00f36d58(s32 *arg0, s32 arg1) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (arg1 == 0) {
            arg0[i] = func_00f3f6c0(arg0[i], D_00F616D0, 6);
        } else {
            arg0[i] = func_00f3f6c0(arg0[i], D_00F61780, 6);
        }
    }
}
