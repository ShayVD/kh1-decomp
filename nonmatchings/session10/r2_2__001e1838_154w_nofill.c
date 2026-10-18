/* 001e1838: 154w LCS (888 vs 960; 161 in hand), mode hand/nofill: session7 w5 far draft unchanged, only the mode. */
#include "common.h"
extern u64 D_003DB028;
extern s32 D_003DB070;
extern u8 D_003DB050[];
extern u8 D_00F20000[384][512][3];
double sqrt(double);
double sin(double);
void func_001e1480(void);
void func_001e14e0(void);
void func_001e05a8(void *);
s32 func_001e1838(void) {
    s32 y, x, d, w, sx, sy;
    if (D_003DB070 == 0) {
        D_003DB070 = 512;
        return 4;
    }
    D_003DB070 -= 2;
    D_003DB028 = 0x180808080LL;
    func_001e1480();
    for (y = 0; y < 48; y++) {
        for (x = 0; x < 64; x++) {
            d = sqrt(y * y + x * x);
            w = sin((f32)((d + D_003DB070) * 20) * 3.1415927f / 180.0f) * 4.0;
            if (d == 0) {
                sx = 0;
                sy = 0;
            } else {
                sx = x + w * x / d;
                sy = y + w * y / d;
            }
            if (sx < 0) sx = 0;
            else if (sx >= 256) sx -= 512;
            if (sy < 0) sy = 0;
            else if (sy >= 256) sy -= 384;
            D_00F20000[192 + y][256 + x][0] = D_00F20000[192 + sy][256 + sx][0];
            D_00F20000[192 + y][256 + x][1] = D_00F20000[192 + sy][256 + sx][1];
            D_00F20000[192 + y][256 + x][2] = D_00F20000[192 + sy][256 + sx][2];
            D_00F20000[192 + y][255 - x][0] = D_00F20000[192 + sy][255 - sx][0];
            D_00F20000[192 + y][255 - x][1] = D_00F20000[192 + sy][255 - sx][1];
            D_00F20000[192 + y][255 - x][2] = D_00F20000[192 + sy][255 - sx][2];
            D_00F20000[191 - y][255 - x][0] = D_00F20000[191 - sy][255 - sx][0];
            D_00F20000[191 - y][255 - x][1] = D_00F20000[191 - sy][255 - sx][1];
            D_00F20000[191 - y][255 - x][2] = D_00F20000[191 - sy][255 - sx][2];
            D_00F20000[191 - y][256 + x][0] = D_00F20000[191 - sy][256 + sx][0];
            D_00F20000[191 - y][256 + x][1] = D_00F20000[191 - sy][256 + sx][1];
            D_00F20000[191 - y][256 + x][2] = D_00F20000[191 - sy][256 + sx][2];
        }
    }
    func_001e14e0();
    func_001e05a8(D_003DB050);
    return 0;
}
