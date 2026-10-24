#include "common.h"
#include "data/bss_0066.h"

/* needs make: uses rodata (local initialisers from D_00491908/D_00491910) */
extern s32 D_00669A70;
extern s32 D_00669A78;
extern s32 D_00669A5C;
extern s32 D_0046A540;
extern s16 D_0046A580[], D_0046A588[], D_0046A590[], D_0046A598[], D_0046A5A0[];
extern s16 D_0046A5A8[];
extern u8 D_0046A080[];
extern u8 D_0046A0C0[];
void func_00206130(void *, s32, s32, s32, s32, s32);
void func_0024c8b8(void *, s16 *, s32, s32, s32, s32);
void func_001efb18(void *, void *);
void func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_002014a0(void *, s32, s32, s32, s32, s32, s32, void *, s32, s32);

void func_0024c460(void *a) {
    s32 c[2];
    s32 w[2] = { 17, 15 };
    s32 col[5] = { 0x0CFB8D2A, 0x0CF29829, 0x0CDFB128, 0x0CCBCB27, 0x0CC2D726 };
    s32 x, i, k;
    x = 156 - w[0];
    func_00206130(a, 0, x + D_00669A70, 512, 173, 0x59191202);
    if (D_00669A5C)
        func_00206130(a, 0, x + 173, 512, 211 - x, 0x59191202);
    c[0] = 0x4C00509A;
    c[1] = 0x4C2998FF;
    func_00206130(a, 187, D_00669A78 + 325, 47, 17, c[D_0046A540 == 0]);
    func_00206130(a, 239, D_00669A78 + 325, 47, 17, c[D_0046A540 == 1]);
    func_00206130(a, 291, D_00669A78 + 325, 47, 17, c[D_0046A540 == 2]);
    func_00206130(a, 343, D_00669A78 + 325, 47, 17, c[D_0046A540 == 3]);
    func_00206130(a, 395, D_00669A78 + 325, 47, 17, c[D_0046A540 == 4]);
    func_0024c8b8(a, D_0046A580, 189, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A588, 241, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A590, 293, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A598, 345, D_00669A78 + 326, 14, 0x4F000000);
    func_0024c8b8(a, D_0046A5A0, 397, D_00669A78 + 326, 14, 0x4F000000);
    func_001efb18(D_0046A080, D_0046A0C0);
    func_001f9438(a, 0, 147, D_00669A78 + 352, 2, 14, 0x4CFFFFFF);
    for (i = 0; i < 11; i++) {
        if (i & 1)
            func_00206130(a, 0, x + D_00669A70, 512, w[i & 1], col[i / 2]);
        x += w[i & 1];
    }
    func_00206130(a, 0, D_00669A70 - w[0] + 156, 512, 2, 0x80784040);
    func_001efb18(D_0046A080, D_0046A0C0);
    k = D_00669A5C ? 3 : 1;
    func_002014a0(a, 2, 2, 12, D_00669A70 + 127, 120, 70, D_0046A5A8, k, 16);
    func_00206130(a, 0, D_00669A70 - w[0] + 329, 512, 2, 0x80784040);
}
#include "data/data_0046.h"
