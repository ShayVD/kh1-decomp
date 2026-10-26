/* gb.x func_00f3fa98: matched by hand. */
#include "ovl.h"

extern u64 *D_00F82878;

void func_00f3fa98(u64 *p) {
    u64 *t = D_00F82878; t[1] = 14; t[0] = (u32)((((u32)p - (u32)t) >> 4) - 1 | 0x8000) | 0x1000000000000000;
}
