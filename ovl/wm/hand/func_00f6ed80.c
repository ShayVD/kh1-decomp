/* wm.x func_00f6ed80: the twin of gb.x func_00f47c88 (tools/ovl/twins.py). */
#include "ovl.h"

void func_0024cde8(void *, s32);
extern s16 D_0108F298[];
void func_00f6ed80(s32 arg0) {
    s32 i;
    s32 v = -1;
    for (i = 7; i >= 0; i--) {
        D_0108F298[i] = v;
    }
    if (arg0 != 0) {
        func_0024cde8(D_0108F298, arg0);
    }
}
