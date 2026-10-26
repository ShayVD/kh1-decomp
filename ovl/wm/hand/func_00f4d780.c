/* wm.x func_00f4d780: matched by hand. */
#include "ovl.h"

void *func_00f4d550(void *, void *, s32);
extern u8 D_00FA5650[];

void *func_00f4d780(u8 *p, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    void *r = func_00f4d550(p, D_00FA5650, 32);
    *(u64 *)(p + 0x10) = a1 | ((u64)(a2 / 64) << 16) | ((a3 | ((a4 | ((a5 | ((u64)a6 << 8)) << 8)) << 8)) << 32);
    return r;
}
