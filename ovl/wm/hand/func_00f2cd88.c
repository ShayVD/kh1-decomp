/* wm.x func_00f2cd88: matched by hand. */
#include "ovl.h"

typedef struct { u8 used; u8 a; s16 pad; s16 b; s16 c; s16 d; u8 pad2[4]; u16 snd; u8 pad3[0x80]; } S;
extern S D_00FBEBC0[];
s32 func_00f2cd88(s32 arg0, s32 arg1, s32 arg2) {
    s8 used[256];
    s32 i;
    S *s;
    for (i = 0; i < 256; i++) used[i] = 0;
    for (i = 0, s = D_00FBEBC0; i < 384; i++, s++) {
        if (s->used == 0) continue;
        if (arg0 >= 0 && s->b != arg0) continue;
        if (arg1 >= 0 && s->c != arg1) continue;
        if (arg2 >= 0 && s->d != arg2) continue;
        used[s->a] = 1;
    }
    for (i = 0; i < 256; i++) {
        if (used[i] == 0) return i;
    }
    return 0;
}
