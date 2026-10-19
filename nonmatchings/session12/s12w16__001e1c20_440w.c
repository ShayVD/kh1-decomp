/* 001e1c20: 440 words off (true LCS, of 532), hand/nofill (441 hand), RO=00490840 (kernels kx/ky are local initialized arrays = rodata D_00490840/D_00490868), no context. Size 2180 vs 2128. Structure right (row buffer at row 99, tl/res 3-byte structs, kernel values hoisted and spilled in 144..312, clamp via movn); off: register allocation/spills of the ~300-insn pixel block, q not in s8, sum evaluation order (see 001e1c20_473w_natural.c). */
#include "common.h"

typedef struct { u8 r, g, b; } RGB;
extern u64 D_003DB028;
extern u8 D_003DB050[];
extern RGB D_00F20000[];
#define IMG D_00F20000
#define P (&IMG[y * 512 + x])
#define Q (&IMG[99 * 512 + x])
void func_001e1480(void);
void func_001e14e0(void);
void func_001e05a8(void *);

s32 func_001e1c20(void) {
    RGB tl;
    RGB res;
    s32 kx[9] = { 1, 1, 1, 0, 0, 0, -1, -1, -1 };
    s32 ky[9] = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };
    s32 y, x;
    s32 xr, xg, xb, yr, yg, yb;

    D_003DB028 = 0x180808080LL;
    func_001e1480();
    for (y = 100; y < 284; y++) {
        tl = IMG[99 * 512];
        IMG[99 * 512] = IMG[y * 512];
        for (x = 200; x < 312; x++) {
            xr = ((tl.r * kx[0] + P[512].r * kx[7]) + (P[1].r * kx[5] + Q[1].r * kx[2]))
               + ((Q[0].r * kx[1] + Q[-1].r * kx[3]) + (P[0].r * kx[4] + P[511].r * kx[6]))
               + P[513].r * kx[8];
            yr = ((tl.r * ky[0] + P[512].r * ky[7]) + (P[1].r * ky[5] + Q[1].r * ky[2]))
               + ((Q[0].r * ky[1] + Q[-1].r * ky[3]) + (P[0].r * ky[4] + P[511].r * ky[6]))
               + P[513].r * ky[8];
            xg = ((tl.g * kx[0] + P[512].g * kx[7]) + (P[1].g * kx[5] + Q[1].g * kx[2]))
               + ((Q[0].g * kx[1] + Q[-1].g * kx[3]) + (P[0].g * kx[4] + P[511].g * kx[6]))
               + P[513].g * kx[8];
            yg = ((tl.g * ky[0] + P[512].g * ky[7]) + (P[1].g * ky[5] + Q[1].g * ky[2]))
               + ((Q[0].g * ky[1] + Q[-1].g * ky[3]) + (P[0].g * ky[4] + P[511].g * ky[6]))
               + P[513].g * ky[8];
            xb = ((tl.b * kx[0] + P[512].b * kx[7]) + (P[1].b * kx[5] + Q[1].b * kx[2]))
               + ((Q[0].b * kx[1] + Q[-1].b * kx[3]) + (P[0].b * kx[4] + P[511].b * kx[6]))
               + P[513].b * kx[8];
            yb = ((tl.b * ky[0] + P[512].b * ky[7]) + (P[1].b * ky[5] + Q[1].b * ky[2]))
               + ((Q[0].b * ky[1] + Q[-1].b * ky[3]) + (P[0].b * ky[4] + P[511].b * ky[6]))
               + P[513].b * ky[8];
            if (yg < 0) yg = -yg;
            if (yb < 0) yb = -yb;
            if (xg < 0) xg = -xg;
            if (xb < 0) xb = -xb;
            xb += yb;
            xg += yg;
            if (xr < 0) xr = -xr;
            if (yr < 0) yr = -yr;
            xr += yr;
            tl = Q[0];
            Q[0] = P[0];
            res.r = (xr < 256) ? xr : 255;
            res.g = (xg < 256) ? xg : 255;
            res.b = (xb < 256) ? xb : 255;
            P[0] = res;
        }
    }
    func_001e14e0();
    func_001e05a8(D_003DB050);
    return 0;
}
