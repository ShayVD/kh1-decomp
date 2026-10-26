/* gb.x func_00f41410: matched by hand. */
#include "ovl.h"

typedef struct { f32 *a; s32 *b; f32 *c; u8 pad[0x3C]; } E41410;
s32 func_00176488(s32, E41410 *, s32, s32);
s32 func_00f41000(void);
void *memset(void *, s32, u32);
extern E41410 *D_00F70268;

s32 func_00f41410(s32 arg0, s32 arg1, f32 *arg2, s32 *arg3, f32 *arg4, s32 arg5) {
    s32 idx;
    E41410 *e;

    idx = func_00f41000();
    if (idx < 0) {
        return -1;
    }
    memset(&D_00F70268[idx], 0, sizeof(E41410));
    e = &D_00F70268[idx];
    if (func_00176488(arg5, e, arg0, arg1) == 0) {
        return -1;
    }
    e->a[0] = arg2[0];
    e->a[1] = arg2[1];
    e->a[2] = arg2[2];
    e->a[3] = arg2[3];
    if (arg3 != NULL) {
        e->b[0] = arg3[0];
        e->b[1] = arg3[1];
        e->b[2] = arg3[2];
        e->b[3] = arg3[3];
    } else {
        e->b[3] = 1;
        e->b[1] = 0;
        e->b[2] = 0;
        e->b[0] = 0;
    }
    if (arg4 != NULL) {
        e->c[0] = arg4[0];
        e->c[1] = arg4[1];
        e->c[2] = arg4[2];
        e->c[3] = arg4[3];
    } else {
        e->c[3] = e->c[2] = e->c[1] = e->c[0] = 1.0f;
    }
    return idx;
}
