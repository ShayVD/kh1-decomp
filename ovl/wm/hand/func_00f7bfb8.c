/* wm.x func_00f7bfb8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x94]; s32 x94; } Ctx;
extern Ctx D_00FB6498;
extern u8 D_0108F738[128];
u8 func_00f2b4b8(s32, s32);

void func_00f7bfb8(void) {
    s32 i;
    for (i = 0; i < 128; i++) {
        D_0108F738[i] = 0;
    }
    for (i = 2; i < 28; i++) {
        D_0108F738[i] = func_00f2b4b8(D_00FB6498.x94, i);
    }
    D_0108F738[D_00FB6498.x94] = 1;
}
