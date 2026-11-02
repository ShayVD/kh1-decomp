/* wm.x func_00f3f718: matched by hand. */
#include "ovl.h"

typedef struct { f32 v; u8 k; u8 pad[0x1B]; u16 id; } A;
typedef struct { u16 a; u16 b; } R;
s32 func_00f62b90(s32);
A *func_00f62b98(s32, s32);
R *func_00f62c78(u16, s32);

f32 func_00f3f718(s32 arg0) {
    s32 i;
    s32 n = func_00f62b90(arg0);
    for (i = 0; i < n; i++) {
        A *a = func_00f62b98(i, arg0);
        s32 k = a->k;
        if (k == 2 && func_00f62c78(a->id, arg0)->b == k) {
            return a->v;
        }
    }
    return -1.0f;
}
