/* wm.x func_00f551a8: the twin of gb.x func_00f2e0b0 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[0x50]; u8 b50; u8 pad2[0x2D]; s16 h7e; u16 h80; } St;
extern St *D_00F9B540;
extern s32 D_0108CE88;
void func_00f551a8(void) {
    St *s = D_00F9B540;
    s->h7e = ((u8 *)s)[D_0108CE88];
    s->b50 = s->h7e;
    D_00F9B540->h80 = D_0108CE88;
}
