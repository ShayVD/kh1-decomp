/* wm.x func_00f4d838: the twin of gb.x func_00f26740 (tools/ovl/twins.py). */
#include "ovl.h"

s32 func_00f4d550(void *, void *, s32);
extern u8 D_00FA5650[];
typedef struct { u8 pad[0x10]; u64 x; } S26740;

s32 func_00f4d838(S26740 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 r = func_00f4d550(arg0, D_00FA5650, 0x20);
    arg0->x = 0x80190 | ((arg1 | ((arg2 | ((arg3 | ((u64)arg4 << 8)) << 8)) << 8)) << 32);
    return r;
}
