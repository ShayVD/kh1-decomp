/* 001e1838: LCS 110 (was 154 nofill / 161 hand), hand, right size 960, no context. Changes: pi as 3.1415928f (0x40490fdb; 3.1415927f gives ...fda) (-2), yy = y * y in the outer loop (r2_5), byte 0 of every pixel through a flat u8 index and bytes 1-2 through a Px {u8 c[3];} [][512] cast (C/P mix = 132, right size), then a hill-climb over per-row access forms (unnatural mix: a probe). Left: loop.c giv structure. The original keeps outer givs (192+y)*1536 (int, spilled), base+(191-y)*1536 twice (sp20/sp24) and a spilled 0x48000; dest rows 192+y byte 0 = (base+row giv)+col giv, bytes 1-2 via fully folded pointer givs base+0x48300+1536y; rows 191-y one pointer per pixel; sources byte 0 = (base+row)+col, bytes 1-2 = base+(col+row). */
#include "common.h"
extern u64 D_003DB028;
extern s32 D_003DB070;
extern u8 D_003DB050[];
extern u8 D_00F20000[];
typedef struct { u8 c[3]; } Px;
double sqrt(double);
double sin(double);
void func_001e1480(void);
void func_001e14e0(void);
void func_001e05a8(void *);
#define D3 ((u8 (*)[512][3])D_00F20000)
#define D2 ((u8 (*)[1536])D_00F20000)
#define DP ((Px (*)[512])D_00F20000)
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
            w = sin((f32)((d + D_003DB070) * 20) * 3.1415928f / 180.0f) * 4.0;
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
            D_00F20000[(192 + y) * 1536 + (256 + x) * 3 + 0] = D_00F20000[(192 + sy) * 1536 + (256 + sx) * 3 + 0];
            DP[192 + y][256 + x].c[1] = DP[192 + sy][256 + sx].c[1];
            DP[192 + y][256 + x].c[2] = DP[192 + sy][256 + sx].c[2];
            (D_00F20000 + (192 + y) * 1536)[(255 - x) * 3 + 0] = D_00F20000[(192 + sy) * 1536 + (255 - sx) * 3 + 0];
            DP[192 + y][255 - x].c[1] = DP[192 + sy][255 - sx].c[1];
            DP[192 + y][255 - x].c[2] = DP[192 + sy][255 - sx].c[2];
            D2[191 - y][(255 - x) * 3 + 0] = D2[191 - sy][(255 - sx) * 3 + 0];
            DP[191 - y][255 - x].c[1] = DP[191 - sy][255 - sx].c[1];
            DP[191 - y][255 - x].c[2] = D2[191 - sy][(255 - sx) * 3 + 2];
            DP[191 - y][256 + x].c[0] = D_00F20000[(191 - sy) * 1536 + (256 + sx) * 3 + 0];
            DP[191 - y][256 + x].c[1] = DP[191 - sy][256 + sx].c[1];
            DP[191 - y][256 + x].c[2] = DP[191 - sy][256 + sx].c[2];
        }
    }
    func_001e14e0();
    func_001e05a8(D_003DB050);
    return 0;
}
