/* gb.x func_00f49f60: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x14]; f32 x; f32 y; } O71;
extern s32 D_00F7063C;
extern s32 D_00F70640;
extern s32 D_00F7064C;
extern s32 D_00F82B48;
extern O71 *D_00F82B78[];

void func_00f49f60(void) {
    s32 i;

    for (i = 0; i < D_00F82B48; i++) {
        D_00F82B78[i]->x = (i & 1) * D_00F7064C + D_00F7063C;
        D_00F82B78[i]->y = D_00F70640 + (i / 2) * 28;
    }
}
