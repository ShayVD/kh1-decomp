/* gb.x func_00f26520: matched by hand. */
#include "ovl.h"

s32 func_00f26458(void *, void *, s32);
extern u8 D_00F60DC0[];

s32 func_00f26520(u64 *p, s32 tbp, s32 w, s32 h, s32 f) {
    s32 cx = 2048 - w / 2;
    s32 cy = 2048 - h / 2;
    s32 r = func_00f26458(p, D_00F60DC0, 0x110);
    p[2] = tbp | ((u64)(w / 64) << 16);
    p[10] = ((u64)(w - 1) << 16) | ((u64)(h - 1) << 48);
    p[12] = ((u64)(w - 1) << 16) | ((u64)(h - 1) << 48);
    p[16] = 0x01000070;
    p[26] = 0x110001000;
    p[32] = (cx * 16) | ((u64)(cy * 16) << 32);
    p[28] = ((u64)f << 17) | 0x10000;
    return r;
}
