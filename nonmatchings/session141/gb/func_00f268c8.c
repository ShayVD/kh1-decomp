/* 67 words / score 88, size 288 vs 296: writing (x + 0x700) << 4 (not * 16) gives the duplicated x<<4 shifts. Left: the original copies h and w into s0/s4 first and adds in place (move s0,t3; addu s0,s1,s0); ours folds that into addu s2,t3,s0, which shifts every register. Tried h += y, h = y + h, new locals, nostrict, u32 params. */
#include "ovl.h"

void func_00f26458(void *, void *, s32);
extern u8 D_00F60EF0[];

void func_00f268c8(u64 *p, s32 a, s32 b, s32 c, s32 x, s32 y, s32 w, s32 h) {
    h += y;
    w += x;
    func_00f26458(p, D_00F60EF0, 0x130);
    //{
    p[12] = ((u64)a << 32) | 100;
    p[14] = ((u64)b << 1) | ((u64)c << 4) | 0x30001;
    p[22] = (x << 4) | ((u64)(y << 4) << 16);
    p[26] = (w << 4) | ((u64)(h << 4) << 16);
    p[28] = ((w + 0x700) << 4) | ((u64)((h + 0x740) << 4) << 16) | 0x100000000;
    p[24] = ((x + 0x700) << 4) | ((u64)((y + 0x740) << 4) << 16) | 0x100000000;
    //}
}
