/* wm.x func_00f32718: matched by hand. */
#include "ovl.h"

typedef struct { s32 used; s32 id; u8 pad[0x18]; } S;
extern S D_00FBB5D0[];
extern s32 D_00FBB82C;

s32 func_00f32718(s32 arg0) {
    s32 i;
    for (i = 0; i < D_00FBB82C; i++) {
        if (D_00FBB5D0[i].used != 0 && D_00FBB5D0[i].id == arg0) return 1;
    }
    return 0;
}
