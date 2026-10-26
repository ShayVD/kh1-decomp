/* wm.x func_00f3fe68: matched by hand. */
#include "ovl.h"

typedef struct { f32 f0; u8 kind; u8 pad; u16 flag; u8 pad2[0x2C]; f32 sp; u8 pad3[4]; f32 g; } K;
s32 func_00f62b90(s32);
K *func_00f62b98(s32, s32);
void func_00f3fe68(K *arg0, s32 arg1) {
    s32 i, n, dx, dg;
    K *k;
    n = func_00f62b90(arg1);
    for (i = 0; i < n; i++) {
        k = func_00f62b98(i, arg1);
        if (arg0 == k) continue;
        if (k->kind != 1) continue;
        if (k->sp == 0.0f) continue;
        if (k->flag & 0x80) continue;
        dx = arg0->f0 - k->f0;
        dg = arg0->g - k->g;
        dx = __builtin_abs(dx);
        dg = __builtin_abs(dg);
        if (dx < 5 && dg < 200) {
            arg0->flag |= 0x80;
            k->flag |= 0x80;
            return;
        }
    }
}
