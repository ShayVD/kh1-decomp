/* gb.x func_00f41888: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; f32 *v; u8 pad2[0x38]; } E48;
s32 func_00f41048(s32);
extern E48 *D_00F70268;
f32 *func_00f41888(s32 arg0, f32 *arg1) {
    f32 *d = (f32 *)func_00f41048(arg0);
    if (d != NULL) {
        E48 *e;
        e = D_00F70268 + arg0;
        d = e->v;
        d[0] = arg1[0];
        d[1] = arg1[1];
        d[2] = arg1[2];
        d[3] = arg1[3];
    }
    return d;
}
