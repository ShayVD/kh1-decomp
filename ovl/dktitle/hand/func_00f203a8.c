/* dktitle.x func_00f203a8: matched by hand. */
#include "ovl.h"

typedef struct { s32 a, b, c, d; } Q;
extern Q *func_00f20090(void *, s32);
extern u64 *func_00f20038(s32);
extern u8 D_00F26DB0[];
extern Q *D_00F2C6F8;
void func_00f203a8(u64 tex0, s32 tex1, s32 alpha, s32 x, s32 y, s32 w, s32 h) {
    u64 *p;
    Q *q = func_00f20090(D_00F26DB0, 6);
    if (D_00F2C6F8 == 0) D_00F2C6F8 = q;
    p = func_00f20038(7);
    p[0] = 0x2000000000000001ULL;
    p[1] = 0xEE;
    p[2] = tex0;
    p[3] = 6;
    p[4] = (u32)tex1;
    p[5] = 0x42;
    p[6] = 0x6400000000008001ULL;
    p[7] = 0x535310;
    p[8] = 0x156;
    p[9] = ((u64)alpha << 24) | 0x100808080ULL;
    p[10] = 0;
    p[11] = (x * 16 + 0x7008) | ((u64)(y * 16 + 0x7408) << 16) | 0x100000000ULL;
    p[12] = (w * 16) | ((u64)(h * 16) << 16);
    p[13] = ((x + w) * 16 + 0x7008) | ((u64)((y + h) * 16 + 0x7408) << 16) | 0x100000000ULL;
    func_00f20090(p, 7);
}
