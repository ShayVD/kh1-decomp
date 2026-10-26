/* gb.x func_00f4a598: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x14]; f32 x, y; } Obj;
extern s32 D_00F7063C;
extern s32 D_00F70644;
extern s32 D_00F7064C;
extern s32 D_00F82BF0;
extern Obj *D_00F82C30[];

void func_00f4a598(void) {
    s32 i;
    for (i = 0; i < D_00F82BF0; i++) { D_00F82C30[i]->x = D_00F7063C + (i & 1) * D_00F7064C; D_00F82C30[i]->y = D_00F70644 + (i / 2) * 28 - (D_00F82BF0 / 2) * 28 + 28; }
}
