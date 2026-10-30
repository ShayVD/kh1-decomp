/* wm.x func_00f58300: matched by hand. */
#include "ovl.h"

void func_0011d140(s32, s32);
s32 func_00f58128(s32);
void func_00f59820(s32, s32);
void func_00f59870(s32, s32, s32, s32, s32);
void func_00f55358(s32);
void func_001bfac8(void);
extern s32 D_0108CE88;
extern u64 D_0108CE90[8];
extern u8 D_00379F28[][4];

#define RGBAQ(r, g, b, a) ((u64)(r) | ((u64)(g) << 8) | ((u64)(b) << 16) | ((u64)(a) << 24) | ((u64)0x3F800000 << 32))

void func_00f58300(void) {
    s32 i;
    s32 j;

    func_0011d140(0xE2D7, 0);
    for (i = 0; i < 40; i++) {
        for (j = 0; j < 8; j++) {
            s32 k = func_00f58128(D_0108CE88 + j);
            u8 b2 = D_00379F28[k][2];
            u8 g = D_00379F28[k][1];
            u8 r = D_00379F28[k][0];
            D_0108CE90[j] = RGBAQ(r / 2, g / 2, b2 / 2, (40 - i) * 102 / 40);
        }
        func_00f59820(7, (39 - i) / 2);
        func_00f59870(5, i * 93 / 40 + 35, i * 93 / 40 + 35, i * 63 / 40 + 65, 128);
        func_00f55358(i * 58 / 40 + 70);
        func_001bfac8();
    }
    func_00f59820(7, 0);
    func_00f59870(5, 128, 128, 128, 128);
    func_00f55358(128);
}
