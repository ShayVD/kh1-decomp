/* gb.x func_00f28d90: matched by hand. */
#include "ovl.h"

typedef struct { f32 a; f32 b; s16 c; s16 d; } E4f;
typedef struct { u8 pad[4]; u16 n; } C4f;
extern u8 *D_00F56DC0;
extern E4f D_00F7F540[];

void func_00f28d90(void) {
    C4f *h = (C4f *)(D_00F56DC0 + 0xA0);
    s32 i;
    for (i = 0; i < h->n; i++) {
        if (D_00F7F540[i].c != 0 && D_00F7F540[i].d != 0) {
            if (D_00F7F540[i].d < D_00F7F540[i].a) {
                D_00F7F540[i].c = 0;
                D_00F7F540[i].a = 0;
            } else {
                D_00F7F540[i].a += D_00F7F540[i].b;
            }
        }
    }
}
