/* dkmovie.x func_00f26540: matched by hand. */
#include "ovl.h"

void func_00f205a4(s32);
void func_00f26a80(s32, s32, s32);
extern s32 D_00F28460;
extern s32 D_00F28464;
#define F(w, o) (*(s32 *)((w) + (o)))
#define DMA_BUSY() ((*(volatile u32 *)0x1000D000 >> 9) & 1)

void func_00f26540(s32 idx, s32 x, s32 y) {
    s32 f[4];
    s32 w;
    s32 n;
    s32 px;
    s32 py;
    s32 blk;
    s32 i;
    s32 off;
    s32 by;
    s32 fy;
    s32 bx;
    s32 fx;
    s32 r;
    s32 q;

    by = y / 16;
    w = D_00F28460;
    fy = 0;
    if (y % 16 < 0) fy = 1;
    n = F(w, 0x3DD18);
    q = idx / n;
    r = idx % n;
    bx = x / 16;
    fx = 0;
    if (x % 16 < 0) fx = 1;
    px = r * 16 + x;
    py = q * 16 + y;
    blk = (q + by - fy) * n + (r + bx - fx);
    func_00f26a80(D_00F28464 + 0x4F0, F(w, 0x3DD08) + blk * 0x300, 0x600);
    while (DMA_BUSY()) {
    }
    func_00f26a80(D_00F28464 + 0xAF0, F(D_00F28460, 0x3DD08) + (blk + F(D_00F28460, 0x3DD18)) * 0x300, 0x600);
    if (px < 0 || F(D_00F28460, 0x3DD20) - 16 < px || py < 0 || F(D_00F28460, 0x3DD24) - 16 < py) {
        while (DMA_BUSY()) {
        }
        f[0] = 0;
        f[1] = 0;
        f[2] = 0;
        f[3] = 0;
        if (px < 0) {
            f[0] = 1;
            f[2] = 1;
        }
        if (py < 0) {
            f[0] = 1;
            f[1] = 1;
        }
        if (px < -15) {
            f[1] = 1;
            f[3] = 1;
        }
        if (py < -15) {
            f[2] = 1;
            f[3] = 1;
        }
        if (F(D_00F28460, 0x3DD20) - 16 < px) {
            f[1] = 1;
            f[3] = 1;
        }
        if (F(D_00F28460, 0x3DD24) - 16 < py) {
            f[2] = 1;
            f[3] = 1;
        }
        if (px >= F(D_00F28460, 0x3DD20)) {
            f[0] = 1;
            f[2] = 1;
        }
        if (py >= F(D_00F28460, 0x3DD24)) {
            f[0] = 1;
            f[1] = 1;
        }
        off = 0;
        for (i = 0; i < 4; i++) {
            if (f[i] != 0) {
                func_00f205a4(D_00F28464 + off + 0x4F0);
            }
            off += 0x300;
        }
    }
}
