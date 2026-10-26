/* gb.x func_00f47c88: matched by hand. */
#include "ovl.h"

void func_0024cde8(void *, s32);
extern s16 D_00F82AD8[];
void func_00f47c88(s32 arg0) {
    s32 i;
    s32 v = -1;
    for (i = 7; i >= 0; i--) {
        D_00F82AD8[i] = v;
    }
    if (arg0 != 0) {
        func_0024cde8(D_00F82AD8, arg0);
    }
}
