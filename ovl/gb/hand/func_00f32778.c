/* gb.x func_00f32778: matched by hand. */
#include "ovl.h"

extern u64 D_00F80790[16];

void func_00f32778(s32 i, s32 r, s32 g, s32 b, s32 a) {
    s32 j;
    if (i >= 16) {
        return;
    }
    if (i < 0) {
        for (j = 0; j < 16; j++) {
            D_00F80790[j] = (u64)r | ((u64)g << 8) | ((u64)b << 16) | ((u64)a << 24) | ((u64)0x3F800000 << 32);
        }
    } else {
        D_00F80790[i] = (u64)r | ((u64)g << 8) | ((u64)b << 16) | ((u64)a << 24) | ((u64)0x3F800000 << 32);
    }
}
