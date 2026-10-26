/* wm.x func_00f66b90: the twin of gb.x func_00f3fa98 (tools/ovl/twins.py). */
#include "ovl.h"

extern u64 *D_0108F038;

void func_00f66b90(u64 *p) {
    u64 *t = D_0108F038; t[1] = 14; t[0] = (u32)((((u32)p - (u32)t) >> 4) - 1 | 0x8000) | 0x1000000000000000;
}
