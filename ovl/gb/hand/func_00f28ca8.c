/* gb.x func_00f28ca8: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; f32 b; s16 c; s16 d; } E4f;
typedef struct { u8 pad[4]; u16 n; u8 pad2[6]; } C4f;
typedef struct { u8 pad[9]; u8 x; } R4f;
R4f *func_001bb658(s32);
s32 func_00f23908(s32);
s16 func_00f3e068(s32, s32);
extern u8 *D_00F56DC0;
extern E4f D_00F7F540[];

void func_00f28ca8(f32 f) {
    C4f *h;
    C4f *c;
    s32 i;
    R4f *r;

    h = (C4f *)(D_00F56DC0 + 0xA0);
    c = (C4f *)(D_00F56DC0 + 0x110);
    for (i = 0; i < h->n; i++, c++) {
        r = func_001bb658(c->n - 1);
        if (D_00F7F540[i].c == 0) {
            D_00F7F540[i].c = 1;
            D_00F7F540[i].a = 0;
            D_00F7F540[i].b = f;
            if (r->x != 0xFF) {
                D_00F7F540[i].d = func_00f3e068(func_00f23908(r->x), -1);
            } else {
                D_00F7F540[i].d = 0;
            }
        }
    }
}
