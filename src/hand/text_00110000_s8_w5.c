#include "common.h"
#include "data/bss_004D.h"
typedef struct { f32 a[4]; s32 b[3]; } CamS;
extern CamS D_002BC0F0;
extern f32 D_004D90F8;
extern u64 D_002BC9B0;
extern u8 D_002BC9F0[];
extern f32 D_002BC170[8];
extern f32 D_002BC120, D_002BC124;
extern f32 D_002BBDFC;
extern f32 D_002A3F60[16][4];
extern f32 D_002A4060[16][4];
void func_00106bd8(void *, s32);
static inline void mk(u64 *o, s32 r, s32 g, s32 b) { *o = (u64)r | ((u64)g << 8) | ((u64)b << 16); }

/* the 32-byte frame comes from an unused 16-byte local */
void func_00110ce0(void) {
    f32 n, f, t, b, d, p, q;
    s32 i;
    s32 unused[4];
    n = D_002BC0F0.a[0];
    f = D_002BC0F0.a[1];
    b = D_002BC0F0.a[2];
    t = D_002BC0F0.a[3];
    D_004D90F8 = f;
    mk(&D_002BC9B0, D_002BC0F0.b[0], D_002BC0F0.b[1], D_002BC0F0.b[2]);
    d = n - f;
    p = (n * f * (t - b)) / d;
    q = ((b - t) * (n + f) / d + (b + t)) * 0.5f;
    D_002BC120 = q;
    D_002BC124 = p;
    D_002BC170[3] = q;
    D_002BC170[7] = p;
    func_00106bd8(D_002BC9F0, 10010);
    for (i = 0; i < 16; i++) {
        D_002A3F60[i][0] += D_002A4060[i][0] * D_002BBDFC;
        if (D_002A3F60[i][0] > 1.0f) D_002A3F60[i][0] -= 1.0f;
        D_002A3F60[i][1] += D_002A4060[i][1] * D_002BBDFC;
        if (D_002A3F60[i][1] > 1.0f) D_002A3F60[i][1] -= 1.0f;
    }
}
#include "data/data_002B.h"
