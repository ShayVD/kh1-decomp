/* The two image filters of src/screen/screen.c that need nofill. */
#include "common.h"
#include "data/data_003D.h"

extern u8 D_00F20000[];
double sqrt(double);
double sin(double);
int abs(int);
void func_001e1480(void);
void func_001e14e0(void);
void func_001e05a8(void *);

/* Every frame: a ripple from the centre (s11_w66: the image pointer in a
 * local, row / column byte offsets as ints; byte 0 through
 * (buf + row)[col], bytes 1-2 through buf[col + row + k]). */
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

/* Every frame: an edge filter (Sobel) over the middle of the frame
 * (s12w18; its kx / ky initialisers are D_00490840 / D_00490868). */
typedef struct { u8 r, g, b; } RGB;
#define IMG ((RGB *)D_00F20000)
#define P(o) (&img[y * 512 + x])[o]
#define Q(o) line[x + (o)]
s32 func_001e1c20(void) {
    RGB tl;
    RGB res;
    s32 kx[9] = { 1, 1, 1, 0, 0, 0, -1, -1, -1 };
    s32 ky[9] = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };
    s32 y, x;
    RGB *img;
    RGB *line;
    s32 r, g, b;

    D_003DB028 = 0x180808080LL;
    func_001e1480();
    img = IMG;
    line = &img[99 * 512];
    for (y = 100; y < 284; y++) {
        tl = line[0];
        line[0] = img[y * 512];
        for (x = 200; x < 312; x++) {
            r = abs(tl.r * kx[0] + Q(0).r * kx[1] + Q(1).r * kx[2] + Q(-1).r * kx[3] + P(0).r * kx[4] + P(1).r * kx[5] + P(511).r * kx[6] + P(512).r * kx[7] + P(513).r * kx[8]) + abs(tl.r * ky[0] + Q(0).r * ky[1] + Q(1).r * ky[2] + Q(-1).r * ky[3] + P(0).r * ky[4] + P(1).r * ky[5] + P(511).r * ky[6] + P(512).r * ky[7] + P(513).r * ky[8]);
            g = abs(tl.g * kx[0] + Q(0).g * kx[1] + Q(1).g * kx[2] + Q(-1).g * kx[3] + P(0).g * kx[4] + P(1).g * kx[5] + P(511).g * kx[6] + P(512).g * kx[7] + P(513).g * kx[8]) + abs(tl.g * ky[0] + Q(0).g * ky[1] + Q(1).g * ky[2] + Q(-1).g * ky[3] + P(0).g * ky[4] + P(1).g * ky[5] + P(511).g * ky[6] + P(512).g * ky[7] + P(513).g * ky[8]);
            b = abs(tl.b * kx[0] + Q(0).b * kx[1] + Q(1).b * kx[2] + Q(-1).b * kx[3] + P(0).b * kx[4] + P(1).b * kx[5] + P(511).b * kx[6] + P(512).b * kx[7] + P(513).b * kx[8]) + abs(tl.b * ky[0] + Q(0).b * ky[1] + Q(1).b * ky[2] + Q(-1).b * ky[3] + P(0).b * ky[4] + P(1).b * ky[5] + P(511).b * ky[6] + P(512).b * ky[7] + P(513).b * ky[8]);


            tl = Q(0);
            Q(0) = P(0);
            res.r = (r < 256) ? r : 255;
            res.g = (g < 256) ? g : 255;
            res.b = (b < 256) ? b : 255;
            P(0) = res;

        }
    }
    func_001e14e0();
    func_001e05a8(D_003DB050);
    return 0;
}
