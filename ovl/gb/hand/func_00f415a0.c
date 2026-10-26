/* gb.x func_00f415a0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x48]; } E48;
f32 *func_00176630(E48 *);
extern E48 *D_00F70268;

s32 func_00f415a0(f32 *out, f32 *half, s32 idx) {
    f32 *m;
    f32 a[4], b[4];
    if (idx < 0) return 0;
    m = func_00176630(&D_00F70268[idx]);
    a[0] = m[4]; a[1] = m[9]; a[2] = m[14];
    b[0] = m[0]; b[1] = m[13]; b[2] = m[10];
    half[0] = (b[0] - a[0]) * 0.5f; half[1] = (b[1] - a[1]) * 0.5f; half[2] = (b[2] - a[2]) * 0.5f; out[0] = a[0] + half[0]; out[1] = a[1] + half[1]; out[2] = a[2] + half[2];
    return 1;
}
