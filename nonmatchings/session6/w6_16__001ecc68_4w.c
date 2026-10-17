/* 4w off (all modes): call arg moves t3/t1 order swapped (jal slot), and lw D_00633640 vs ld ra order at the end. strict hand */
#include "common.h"
extern s32 D_003E3C80;
extern s32 D_00633640;
void func_001ed000(s32, u8 *, s32, s32, s32, s32, s32, s32);

s32 func_001ecc68(u8 *p, s32 a, s32 b, s32 c) {
    s32 v, x, y;
    v = p[16] << 24 | p[17] << 16;
    v |= p[18] << 8;
    v |= p[19];
    v = v * 4096 / 48000;
    x = p[30];
    y = p[31];
    if (!(D_003E3C80 & 4)) func_001ed000(18, p, a, b, c, v, x, y);
    return D_00633640;
}
