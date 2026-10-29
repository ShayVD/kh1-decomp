/* 94 words / score 52 (440 vs 448 bytes). Same pointer-copy idiom as f3b348: the original reads the three colour bytes through v1, a2 and v0 copies of one pointer. It also hoists &D_00379F28 into s5 and the RGBAQ Q constant into s8, where ours hoists hi(D_00F806C8). Tried a plain pointer, an inline mkcol helper (with and without temporaries), and an inline col_of per component. */
#include "ovl.h"

void func_0011d140(s32, s32);
s32 func_00f31030(s32);
void func_00f32728(s32, s32);
void func_00f32778(s32, s32, s32, s32, s32);
void func_00f2e260(s32);
void func_001bfac8(void);
extern u8 D_00379F28[];
extern s32 D_00F806C8;
extern u64 D_00F806D0[8];

static inline u64 mkcol(u8 *c, s32 a) {
    u64 r = (u64)c[0] >> 1;
    u64 g = (u64)c[1] >> 1;
    u64 b = (u64)c[2] >> 1;
    return r | (g << 8) | (b << 16) | ((u64)a << 24) | ((u64)0x3F800000 << 32);
}

s32 func_00f31048(void) {
    s32 i, j;
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;
    u8 *col;
    func_0011d140(0xE2D6, 0);
    for (i = 0; i < 40; i++) {
        for (j = 0; j < 8; j++) {
            D_00F806D0[j] = mkcol(&D_00379F28[func_00f31030(D_00F806C8 + j) * 4], a / 40);
        }
        a += 102;
        func_00f32728(7, i / 2);
        func_00f32778(5, b / 40 + 128, b / 40 + 128, c / 40 + 128, 128);
        c -= 63;
        b -= 93;
        func_00f2e260(i * -58 / 40 + 128);
        func_001bfac8();
    }
    func_00f32778(5, 35, 35, 65, 128);
    func_00f2e260(70);
    return 1;
}
