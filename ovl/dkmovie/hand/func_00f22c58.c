/* dkmovie.x func_00f22c58: matched by hand. */
#include "ovl.h"

void func_00f22c58(u64 *p, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6) {
    *p = ((u64)a1 << 63) | ((u64)(a2 & ~0xF) << 32) | ((u64)a3 << 31) | ((u64)a4 << 28) | ((u64)a5 << 26) | (u64)a6;
}
