/* gb.x func_00f20208: matched by hand. */
#include "ovl.h"

extern s32 D_00F74228[16];
void func_00f20208(void) {
    s32 i;
    s32 v = -1;
    for (i = 15; i >= 0; i--) {
        D_00F74228[i] = v;
    }
}
