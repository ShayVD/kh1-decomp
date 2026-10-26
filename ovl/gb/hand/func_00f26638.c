/* gb.x func_00f26638: matched by hand. */
#include "ovl.h"

void *func_00f26458(void *, void *, s32);
extern u8 D_00F60DC0[];

void *func_00f26638(u8 *arg0, s32 arg1) {
    void *r = func_00f26458(arg0, D_00F60DC0, 0x110);
    *(s64 *)(arg0 + 0xE0) = ((s64)arg1 << 17) | 0x10000;
    return r;
}
