/* wm.x func_00f4d590: matched by hand. */
#include "ovl.h"

void *func_00f4d550(void *, void *, s32);
extern u8 D_00FA5470[];

void *func_00f4d590(u8 *arg0, s32 arg1, s32 arg2) {
    void *r = func_00f4d550(arg0, D_00FA5470, 0x60);
    *(s64 *)(arg0 + 0x10) = arg1 | ((s64)(arg2 / 64) << 16);
    return r;
}
