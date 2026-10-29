/* gb.x func_00f31048: matched by hand. */
#include "ovl.h"

void func_0011d140(s32, s32);
s32 func_00f31030(s32);
void func_00f32728(s32, s32);
void func_00f32778(s32, s32, s32, s32, s32);
void func_00f2e260(s32);
void func_001bfac8(void);
extern s32 D_00F806C8;
extern u64 D_00F806D0[8];
extern u8 D_00379F28[][4];

#define RGBAQ(r, g, b, a) ((u64)(r) | ((u64)(g) << 8) | ((u64)(b) << 16) | ((u64)(a) << 24) | ((u64)0x3F800000 << 32))

s32 func_00f31048(void) {
    s32 i;
    s32 j;
    s32 a = 0;
    s32 c = 0;
    s32 b = 0;
    u64 *d;
    u8 *t;

    func_0011d140(0xE2D6, 0);
    for (i = 0; i < 40; i++) {
        for (j = 0; j < 8; j++) {
            s32 k = func_00f31030(D_00F806C8 + j);
            u8 b2 = D_00379F28[k][2];
            u8 g = D_00379F28[k][1];
            u8 r = D_00379F28[k][0];
            D_00F806D0[j] = RGBAQ(r / 2, g / 2, b2 / 2, a / 40);
        }
        a += 102;
        func_00f32728(7, i / 2);
        func_00f32778(5, b / 40 + 128, b / 40 + 128, c / 40 + 128, 128);
        b -= 93;
        c -= 63;
        func_00f2e260(i * -58 / 40 + 128);
        func_001bfac8();
    }
    func_00f32778(5, 35, 35, 65, 128);
    func_00f2e260(70);
    return 1;
}
