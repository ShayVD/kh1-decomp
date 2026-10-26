/* gb.x func_00f35810: matched by hand. */
#include "ovl.h"

void func_00f22338(s32, s32, s32, s32);
void func_00f35810(u32 m) {
    s32 buf[4];
    s32 n = 0;
    if (m & 1) buf[n++] = 161;
    if (m & 2) buf[n++] = 162;
    if (m & 4) buf[n++] = 163;
    if (n) func_00f22338(3, buf[0], buf[1], 0x806168f4);
    else func_00f22338(2, 160, 0x80e19664, 0);
}
