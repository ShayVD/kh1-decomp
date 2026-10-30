/* gb.x func_00f319a8: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
extern u8 D_00379F28[][4];
extern u64 D_00F806D0[];

#define RGBAQ(r, g, b, a) ((u64)(r) | ((u64)(g) << 8) | ((u64)(b) << 16) | ((u64)(a) << 24) | ((u64)0x3F800000 << 32))

void func_00f319a8(s32 i, s32 c) {
    s32 n;
    u8 r = D_00379F28[c][0];
    u8 g = D_00379F28[c][1];
    u8 b = D_00379F28[c][2];
    s32 r2 = r + 80;
    s32 g2 = g + 80;
    s32 b2 = b + 80;
    if (r2 > 128) r2 = 255;
    if (g2 > 128) g2 = 255;
    if (b2 > 128) b2 = 255;
    D_00F806D0[i] = RGBAQ(r2 / 2, g2 / 2, b2 / 2, 0x66);
    for (n = 7; n >= 0; n--)
        func_001bfac8();
    D_00F806D0[i] = RGBAQ(r / 2, g / 2, b / 2, 0x66);
}
