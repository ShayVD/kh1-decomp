/* gb.x func_00f26688: matched by hand. */
#include "ovl.h"

void *func_00f26458(void *, void *, s32);
extern u8 D_00F60ED0[];

void *func_00f26688(u8 *p, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    void *r = func_00f26458(p, D_00F60ED0, 32);
    *(u64 *)(p + 0x10) = a1 | ((u64)(a2 / 64) << 16) | ((a3 | ((a4 | ((a5 | ((u64)a6 << 8)) << 8)) << 8)) << 32);
    return r;
}
