/* wm.x func_00f2ccf8: matched by hand. */
#include "ovl.h"

typedef struct { u8 used; u8 a; s16 pad; s16 b; s16 c; s16 d; u8 pad2[0x86]; } S;
extern S D_00FBEBC0[];
s32 func_00f2ccf8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    for (i = 0; i < 384; i++) {
        S *s = &D_00FBEBC0[i];
        if (s->used == 0) continue;
        if (arg0 >= 0 && s->a != arg0) continue;
        if (arg1 >= 0 && s->b != arg1) continue;
        if (arg2 >= 0 && s->c != arg2) continue;
        if (arg3 >= 0 && s->d != arg3) continue;
        return i;
    }
    return -1;
}
