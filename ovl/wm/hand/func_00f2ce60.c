/* wm.x func_00f2ce60: matched by hand. */
#include "ovl.h"

typedef struct { u8 used; u8 a; s16 pad; s16 b; s16 c; s16 d; u8 pad2[4]; u16 snd; u8 pad3[0x80]; } S;
void func_00f68a40(u16);
extern S D_00FBEBC0[];
extern s32 D_00FCC3C0;
void func_00f2ce60(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    S *s;
    for (i = 0, s = D_00FBEBC0; i < 384; i++, s++) {
        if (i == D_00FCC3C0) continue;
        if (s->used == 0) continue;
        if (arg0 >= 0 && arg0 != s->a) continue;
        if (arg1 >= 0 && s->b != arg1) continue;
        if (arg2 >= 0 && s->c != arg2) continue;
        if (arg3 >= 0 && s->d != arg3) continue;
        if (s->snd != 0xFFFF) func_00f68a40(s->snd);
        s->used = 0;
    }
    D_00FCC3C0 = -1;
}
