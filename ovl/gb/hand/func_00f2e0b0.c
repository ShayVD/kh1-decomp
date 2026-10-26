/* gb.x func_00f2e0b0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x50]; u8 b50; u8 pad2[0x2D]; s16 h7e; u16 h80; } St;
extern St *D_00F56DC0;
extern s32 D_00F806C8;
void func_00f2e0b0(void) {
    St *s = D_00F56DC0;
    s->h7e = ((u8 *)s)[D_00F806C8];
    s->b50 = s->h7e;
    D_00F56DC0->h80 = D_00F806C8;
}
