/* wm.x func_00f421a8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x544]; s32 x1; s32 x2; u8 pad2[0xAD4 - 0x54C]; s32 y1; s32 y2; } S;
extern S D_00F86500;

void func_00f421a8(void) {
    s32 t;
    t = D_00F86500.x1;
    D_00F86500.x1 = D_00F86500.y1;
    D_00F86500.y1 = t;
    t = D_00F86500.x2;
    D_00F86500.x2 = D_00F86500.y2;
    D_00F86500.y2 = t;
}
