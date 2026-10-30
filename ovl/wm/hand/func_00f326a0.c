/* wm.x func_00f326a0: matched by hand. */
#include "ovl.h"

/* wm.x func_00f326a0: matched by hand (oldest used slot by time). */
#include "ovl.h"
typedef struct { s32 used; s32 val; u32 time; u8 pad[20]; } E326a0;
extern E326a0 D_00FBB5D0[16];

s32 func_00f326a0(void) {
    s32 i;
    u32 best = -1;
    s32 idx = -1;
    E326a0 *e;
    for (i = 0; i < 16; i++) {
        e = &D_00FBB5D0[i];
        if (e->used != 0) {
            if ((s32)best < 0 || e->time < best) {
                best = e->time;
                idx = i;
            }
        }
    }
    if (idx < 0) {
        return -1;
    }
    return (D_00FBB5D0 + idx)->val;
}
