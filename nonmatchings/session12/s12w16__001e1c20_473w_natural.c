/* 001e1c20: 473 words off (true LCS), hand (strict), RO=00490840, no context. FINDING: each sum is the natural chain tl.r*kx[0] + q[0].r*kx[1] + ... + p[513].r*kx[8]; gcc 2.96 fold reassociates a 9-term chain into ((t0+t7)+(t5+t2))+((t1+t3)+(t4+t6))+t8 and expands kx in order 0,7,5,2,1,3,4,6,8, exactly the original's kernel spill-slot order (144,164,176,184,200,212,224,228,240). p (= &IMG[y*512+x], separate base so p+1536 etc. are pseudos) and q (row-99 buffer pointer, q++) are pointer locals. Off: q spilled (original keeps q in s8; our block-local pressure uses s8), regalloc of the big block, size 2004 vs 2128. */
#include "common.h"

typedef struct { u8 r, g, b; } RGB;
extern u64 D_003DB028;
extern u8 D_003DB050[];
extern RGB D_00F20000[];
#define IMG D_00F20000
void func_001e1480(void);
void func_001e14e0(void);
void func_001e05a8(void *);

s32 func_001e1c20(void) {
    RGB tl;
    RGB res;
    s32 kx[9] = { 1, 1, 1, 0, 0, 0, -1, -1, -1 };
    s32 ky[9] = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };
    s32 y, x;
    RGB *q, *p;
    s32 xr, xg, xb, yr, yg, yb;

    D_003DB028 = 0x180808080LL;
    func_001e1480();
    for (y = 100; y < 284; y++) {
        tl = IMG[99 * 512];
        IMG[99 * 512] = IMG[y * 512];
        q = &IMG[99 * 512 + 200];
        for (x = 200; x < 312; x++) {
            p = &IMG[y * 512 + x];
            xr = tl.r * kx[0] + q[0].r * kx[1] + q[1].r * kx[2] + q[-1].r * kx[3] + p[0].r * kx[4] + p[1].r * kx[5] + p[511].r * kx[6] + p[512].r * kx[7] + p[513].r * kx[8];
            yr = tl.r * ky[0] + q[0].r * ky[1] + q[1].r * ky[2] + q[-1].r * ky[3] + p[0].r * ky[4] + p[1].r * ky[5] + p[511].r * ky[6] + p[512].r * ky[7] + p[513].r * ky[8];
            xg = tl.g * kx[0] + q[0].g * kx[1] + q[1].g * kx[2] + q[-1].g * kx[3] + p[0].g * kx[4] + p[1].g * kx[5] + p[511].g * kx[6] + p[512].g * kx[7] + p[513].g * kx[8];
            yg = tl.g * ky[0] + q[0].g * ky[1] + q[1].g * ky[2] + q[-1].g * ky[3] + p[0].g * ky[4] + p[1].g * ky[5] + p[511].g * ky[6] + p[512].g * ky[7] + p[513].g * ky[8];
            xb = tl.b * kx[0] + q[0].b * kx[1] + q[1].b * kx[2] + q[-1].b * kx[3] + p[0].b * kx[4] + p[1].b * kx[5] + p[511].b * kx[6] + p[512].b * kx[7] + p[513].b * kx[8];
            yb = tl.b * ky[0] + q[0].b * ky[1] + q[1].b * ky[2] + q[-1].b * ky[3] + p[0].b * ky[4] + p[1].b * ky[5] + p[511].b * ky[6] + p[512].b * ky[7] + p[513].b * ky[8];
            if (yg < 0) yg = -yg;
            if (yb < 0) yb = -yb;
            if (xg < 0) xg = -xg;
            if (xb < 0) xb = -xb;
            xb += yb;
            xg += yg;
            if (xr < 0) xr = -xr;
            if (yr < 0) yr = -yr;
            xr += yr;
            tl = q[0];
            q[0] = p[0];
            res.r = (xr < 256) ? xr : 255;
            res.g = (xg < 256) ? xg : 255;
            res.b = (xb < 256) ? xb : 255;
            p[0] = res;
            q++;
        }
    }
    func_001e14e0();
    func_001e05a8(D_003DB050);
    return 0;
}
