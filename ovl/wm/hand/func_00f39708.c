/* wm.x func_00f39708: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
extern f32 D_002BBDEC;
extern f32 D_00F8509C;

typedef struct { u8 pad[0xE0]; s32 e0; u8 pad2[0x18]; s32 fc; } A0;
typedef struct { u8 pad[0x18]; s32 a; s32 b; } A1;

void func_00f39708(A0 *arg0, A1 *arg1, s32 arg2) {
    f32 end;
    f32 start;
    s32 n;
    s32 i;

    n = (f32) arg1->a / D_002BBDEC;
    end = (f32) arg1->b * 0.00390625f;
    start = D_00F8509C;
    if (arg2 != 0) {
        for (i = 0; i < n; i++) {
            if (arg0->fc == 0) break;
            if (arg0->e0 == 0) return;
            D_00F8509C = (end - start) * i / n + start;
            func_001bfac8();
        }
    }
    D_00F8509C = end;
}
