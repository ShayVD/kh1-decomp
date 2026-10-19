#include "common.h"

/* func_001e1838: hand/nofill (no-fill TU, see session11 NOTES s11w24), natural, no context.
   Image pointer in a local (buf), row/column byte offsets as ints; byte 0 through (buf + row)[col],
   bytes 1-2 through buf[col + row + k]. */
extern u64 D_003DB028;
extern s32 D_003DB070;
extern u8 D_003DB050[];
extern u8 D_00F20000[];
double sqrt(double);
double sin(double);
void func_001e1480(void);
void func_001e14e0(void);
void func_001e05a8(void *);

s32 func_001e1838(void) {
    s32 yy, y, x, d, w, sx, sy;
    u8 *buf;

    if (D_003DB070 == 0) {
        D_003DB070 = 512;
        return 4;
    }
    D_003DB070 -= 2;
    D_003DB028 = 0x180808080LL;
    func_001e1480();
    buf = D_00F20000;
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
            {
                s32 sr0 = (192 + sy) * 1536, sr1 = (191 - sy) * 1536;
                s32 sc0 = (256 + sx) * 3, sc1 = (255 - sx) * 3;
                s32 dr0 = (192 + y) * 1536, dr1 = (191 - y) * 1536;
                s32 dc0 = (256 + x) * 3, dc1 = (255 - x) * 3;
                (buf + dr0)[dc0] = (buf + sr0)[sc0];
                buf[dc0 + dr0 + 1] = buf[sc0 + sr0 + 1];
                buf[dc0 + dr0 + 2] = buf[sc0 + sr0 + 2];
                (buf + dr0)[dc1] = (buf + sr0)[sc1];
                buf[dc1 + dr0 + 1] = buf[sc1 + sr0 + 1];
                buf[dc1 + dr0 + 2] = buf[sc1 + sr0 + 2];
                (buf + dr1)[dc1] = (buf + sr1)[sc1];
                buf[dc1 + dr1 + 1] = buf[sc1 + sr1 + 1];
                buf[dc1 + dr1 + 2] = buf[sc1 + sr1 + 2];
                (buf + dr1)[dc0] = (buf + sr1)[sc0];
                buf[dc0 + dr1 + 1] = buf[sc0 + sr1 + 1];
                buf[dc0 + dr1 + 2] = buf[sc0 + sr1 + 2];
            }
        }
    }
    func_001e14e0();
    func_001e05a8(D_003DB050);
    return 0;
}
