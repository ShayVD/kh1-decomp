/* wm.x func_00f4d730: matched by hand. */
#include "ovl.h"

void *func_00f4d550(void *, void *, s32);
extern u8 D_00FA5540[];

void *func_00f4d730(u8 *arg0, s32 arg1) {
    void *r = func_00f4d550(arg0, D_00FA5540, 0x110);
    *(s64 *)(arg0 + 0xE0) = ((s64)arg1 << 17) | 0x10000;
    return r;
}
