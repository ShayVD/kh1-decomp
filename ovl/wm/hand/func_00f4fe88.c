/* wm.x func_00f4fe88: matched by hand. */
#include "ovl.h"

typedef struct { f32 a; f32 b; s16 c; s16 d; } E4f;
typedef struct { u8 pad[4]; u16 n; } C4f;
extern u8 *D_00F9B540;
extern E4f D_0108BD00[];

void func_00f4fe88(void) {
    C4f *h = (C4f *)(D_00F9B540 + 0xA0);
    s32 i;
    for (i = 0; i < h->n; i++) {
        if (D_0108BD00[i].c != 0 && D_0108BD00[i].d != 0) {
            if (D_0108BD00[i].d < D_0108BD00[i].a) {
                D_0108BD00[i].c = 0;
                D_0108BD00[i].a = 0;
            } else {
                D_0108BD00[i].a += D_0108BD00[i].b;
            }
        }
    }
}
