/* gb.x func_00f3f9e8: matched by hand. */
#include "ovl.h"

extern u64 *D_00F82870;

u64 *func_00f3f9e8(u64 *p) {
    *D_00F82870 = (u32)((((u32)p - (u32)D_00F82870) >> 4) - 1 | 0x70000000); D_00F82870[1] = 0; return D_00F82870;
}
