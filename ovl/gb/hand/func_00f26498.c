/* gb.x func_00f26498: matched by hand. */
#include "ovl.h"

void *func_00f26458(void *, void *, s32);
extern u8 D_00F60CF0[];

void *func_00f26498(u8 *arg0, s32 arg1, s32 arg2) {
    void *r = func_00f26458(arg0, D_00F60CF0, 0x60);
    *(s64 *)(arg0 + 0x10) = arg1 | ((s64)(arg2 / 64) << 16);
    return r;
}
