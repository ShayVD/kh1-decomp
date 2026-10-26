/* wm.x func_00f4fda0: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; f32 b; s16 c; s16 d; } E4f;
typedef struct { u8 pad[4]; u16 n; u8 pad2[6]; } C4f;
typedef struct { u8 pad[9]; u8 x; } R4f;
R4f *func_001bb658(s32);
s32 func_00f4aa00(s32);
s16 func_00f65160(s32, s32);
extern u8 *D_00F9B540;
extern E4f D_0108BD00[];

void func_00f4fda0(f32 f) {
    C4f *h;
    C4f *c;
    s32 i;
    R4f *r;

    h = (C4f *)(D_00F9B540 + 0xA0);
    c = (C4f *)(D_00F9B540 + 0x110);
    for (i = 0; i < h->n; i++, c++) {
        r = func_001bb658(c->n - 1);
        if (D_0108BD00[i].c == 0) {
            D_0108BD00[i].c = 1;
            D_0108BD00[i].a = 0;
            D_0108BD00[i].b = f;
            if (r->x != 0xFF) {
                D_0108BD00[i].d = func_00f65160(func_00f4aa00(r->x), -1);
            } else {
                D_0108BD00[i].d = 0;
            }
        }
    }
}
