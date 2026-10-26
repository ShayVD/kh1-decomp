/* wm.x func_00f3c678: matched by hand. */
#include "ovl.h"

s32 func_00f68828(s32);
void func_00f68a40(s32);

void func_00f3c678(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        if (func_00f68828(i) & 0xF) {
            func_00f68a40(i);
        }
    }
}
