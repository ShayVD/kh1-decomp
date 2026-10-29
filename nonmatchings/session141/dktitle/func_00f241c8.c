/* 2 words differ, score 3. Only diff: orig schedules dsra32 t1 (reg>>32 for q[1] at pk+6) before dsll32 a3,a3,16 (dy<<48 of pos). Tried: moving pos everywhere (before/after/inside the pk+6 line, at decl), splitting pos into = and |=, s64/u64 casts on pos and reg, swapped q[0]/q[1] order, greedy permutation of the pk+6 statements; all stay at 3 or get worse. */
#include "ovl.h"

u64 *func_00f241c8(u64 *pk, u32 addr, s32 dx, s32 dy, s32 w, s32 h, s32 dbp, s32 dpsm, s32 dbw, s32 bpp) {
    s32 qwc = w * h * bpp / 128;
    u64 bb = (s64)dpsm << 56 | (s64)dbw << 48 | (s64)dbp << 32;
    u64 reg = (s64)h << 32 | (u64)(u32)w;
    s32 k;
    u64 pos;
    u32 *q;
    pk[0] = 0x10000003;
    q = (u32 *)(pk + 2); q[0] = 2; q[1] = 0x10000000; q[2] = 0xE; q[3] = 0;
    q = (u32 *)(pk + 4); q[0] = bb; q[1] = bb >> 32; q[2] = 0x50; q[3] = 0;
    q = (u32 *)(pk + 6); q[1] = reg >> 32; q[0] = reg & 0xFFFFFFFF; q[2] = 0x52; q[3] = 0;
    pos = (s64)dy << 48 | (s64)dx << 32;
    pk[8] = 0x10000004;
    q = (u32 *)(pk + 10); q[0] = 2; q[1] = 0x10000000; q[2] = 0xE; q[3] = 0;
    q = (u32 *)(pk + 12); q[0] = pos; q[1] = pos >> 32; q[2] = 0x51; q[3] = 0;
    q = (u32 *)(pk + 14); q[0] = 0; q[1] = 0; q[2] = 0x53; q[3] = 0;
    q = (u32 *)(pk + 16); q[0] = qwc | 0x8000; q[1] = 0x08000000; q[2] = 0; q[3] = 0;
    k = 0x30000000;
    pk[18] = (u64)(u32)qwc | k | (u64)(addr & ~0xF) << 32;
    return pk + 20;
}
