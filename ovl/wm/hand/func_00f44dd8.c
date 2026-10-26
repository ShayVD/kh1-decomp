/* wm.x func_00f44dd8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x18]; s32 x[2]; s32 y[4]; s32 z[4]; } C;
s32 func_001c01b0(s32, void (*)(void), ...);
extern C D_00FB6408;
extern s32 D_01080828[];
void func_00f44898(void);

void func_00f44dd8(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        D_00FB6408.z[0] = 0;
        D_00FB6408.x[0] = 16;
        D_00FB6408.y[0] = 16;
    } else {
        D_00FB6408.x[arg0] = 384;
        D_00FB6408.y[arg0] = 260;
        D_00FB6408.z[arg0] = 1;
    }
    D_01080828[arg0] = func_001c01b0(-1, func_00f44898, arg0, arg1);
}
