/* wm.x func_00f3de10: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; u8 pad[0x28]; } W30;
extern W30 D_00F9A5C0[64];
void func_00f3de10(void) {
    s32 i;
    s32 v = -1;
    for (i = 0; i < 64; i++) {
        D_00F9A5C0[i].a = v;
        D_00F9A5C0[i].b = v;
    }
}
