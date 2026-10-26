/* wm.x func_00f30210: matched by hand. */
#include "ovl.h"

typedef struct { u16 f; u16 k; u8 pad[8]; } I;
typedef struct { s32 n; u8 pad[0x32]; I items[1]; } L;
extern L D_00F85240;
s32 func_00f2cfd8(s32, s32, s32, s32, s32, s32, f32 *, void (*)(void), s32, s32);
void func_00f30210(void) {
    s32 i;
    for (i = 0; i < D_00F85240.n; i++) {
        s32 k = D_00F85240.items[i].k - 1;
        s32 t = -1;
        switch (k) {
        case 56: t = 31; break;
        case 57: t = 32; break;
        }
        if (t >= 0) func_00f2cfd8(0, i, k, t, 2, t, 0, 0, 0, -1);
    }
}
