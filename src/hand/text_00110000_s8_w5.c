#include "common.h"
#include "data/bss_004D.h"
#include "data/pieces/D_002BC0F0.h"
typedef CamS_2BC0F0 CamS;
extern f32 D_004D90F8;
extern u64 D_002BC9B0;
extern u8 D_002BC9F0[];
extern f32 D_002BC170[8];
extern f32 D_002BC120, D_002BC124;
extern f32 D_002BBDFC;
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
void func_00106bd8(void *, s32);
static inline void mk(u64 *o, s32 r, s32 g, s32 b) { *o = (u64)r | ((u64)g << 8) | ((u64)b << 16); }

/* the 32-byte frame comes from an unused 16-byte local */
void func_00110ce0(void) {
    f32 n, f, t, b, d, p, q;
    s32 i;
    s32 unused[4];
    n = D_002BC0F0.camS.a[0];
    f = D_002BC0F0.camS.a[1];
    b = D_002BC0F0.camS.a[2];
    t = D_002BC0F0.camS.a[3];
    D_004D90F8 = f;
    mk(&D_002BC9B0, D_002BC0F0.camS.b[0], D_002BC0F0.camS.b[1], D_002BC0F0.camS.b[2]);
    d = n - f;
    p = (n * f * (t - b)) / d;
    q = ((b - t) * (n + f) / d + (b + t)) * 0.5f;
    D_002BC120 = q;
    D_002BC124 = p;
    D_002BC170[3] = q;
    D_002BC170[7] = p;
    func_00106bd8(D_002BC9F0, 10010);
    for (i = 0; i < 16; i++) {
        D_002A3F60.f[i][0] += D_002A4060.f[i][0] * D_002BBDFC;
        if (D_002A3F60.f[i][0] > 1.0f) D_002A3F60.f[i][0] -= 1.0f;
        D_002A3F60.f[i][1] += D_002A4060.f[i][1] * D_002BBDFC;
        if (D_002A3F60.f[i][1] > 1.0f) D_002A3F60.f[i][1] -= 1.0f;
    }
}
#include "data/data_002B.h"
#include "data/pieces/D_002BBDFC.h"
