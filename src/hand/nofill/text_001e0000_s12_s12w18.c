#include "common.h"

typedef struct { u8 r, g, b; } RGB;
extern u64 D_003DB028;
extern u8 D_003DB050[];
extern RGB D_00F20000[];
#define IMG D_00F20000
#define P(o) (&img[y * 512 + x])[o]
#define Q(o) line[x + (o)]
int abs(int);
void func_001e1480(void);
void func_001e14e0(void);
void func_001e05a8(void *);

/* rodata: kx/ky initialisers are D_00490840/D_00490868 (RO=00490840) */
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
