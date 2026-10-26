/* wm.x func_00f32ac8: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; s32 c; u8 pad[0x14]; } W20;
extern W20 D_00FBB5D0[16];
void func_00f32ac8(void) {
    s32 i;
    s32 v = -1;
    for (i = 0; i < 16; i++) {
        D_00FBB5D0[i].a = 0;
        D_00FBB5D0[i].c = 0;
        D_00FBB5D0[i].b = v;
    }
}
