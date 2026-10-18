/* 001e1838: 163w LCS in hand (161 for the r2_2 draft in hand, 154 in nofill), finding only. hand mode (the original fills delay slots: jal func_001e1480/move s7,zero; bnez/addiu; b/sw, so not a nofill TU). New: yy = y * y in the outer loop gives the original's mult in the outer loop + mtlo/madd before __floatsidf. Off: orig keeps the 192*1536 row constant (0x48000) in a spilled register and adds 768 to the column separately (no displacement folding), dest q1/q2 byte 0 is (base+row)+col while bytes 1/2 use a strength-reduced pointer; tried flat u8[], [384][1536], row pointers, index variables, 3-byte struct copy: none closer. */
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
    s32 yy, y, x, d, w, sx, sy;
    if (D_003DB070 == 0) {
        D_003DB070 = 512;
        return 4;
    }
    D_003DB070 -= 2;
    D_003DB028 = 0x180808080LL;
    func_001e1480();
    for (y = 0; y < 48; y++) {
        yy = y * y;
        for (x = 0; x < 64; x++) {
            d = sqrt(yy + x * x);
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
