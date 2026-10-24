#include "common.h"
#include "data/pieces/D_00425F70.h"

#include "platform/math.h"
#include "data/bss_0064.h"
typedef f32 MTX[4][4] __attribute__((aligned(16)));
typedef f32 VEC[4] __attribute__((aligned(16)));
#include "data/pieces/D_00425CE0.h"
f32 atan2f(f32, f32);
void func_00236d48(void *, void *, void *);
void func_002672f8(void *, void *, void *);
void func_00267768(void *, void *, f32);
void func_00267810(void *, void *, f32);
void func_00267930(void *, void *, void *, void *);
void sceVu0UnitMatrix(void *);
void sceVu0MulMatrix(void *, void *, void *);
void func_002673b8(void *, void *);

#define C D_00425F70
void func_00236a58(void) {
    MTX m;
    VEC v;
    VEC a;
    VEC b;
    f32 dx, dy, dz;
    if (C->x1e0 == 0) {
        dx = C->tx - C->px;
        dz = C->tz - C->pz;
        dy = C->ty - C->py;
        C->rz = 0;
        C->rx = atan2f(-dy, PlatSqrtf(dx * dx + dz * dz));
        C->ry = atan2f(dx, dz);
    } else {
        func_00236d48(m, D_00425CE0, &C->rx);
        v[0] = 0;
        v[1] = 0;
        v[2] = C->dist;
        v[3] = 1.0f;
        func_002672f8(v, m, v);
        C->px = C->tx + v[0];
        dx = C->tx - C->px;
        C->py = C->ty + v[1];
        dy = C->ty - C->py;
        C->pz = C->tz + v[2];
        dz = C->tz - C->pz;
    }
    func_00267768(m, D_00425CE0, C->rx);
    func_00267810(m, m, C->ry);
    func_002672f8(a, m, C->v160);
    func_002672f8(b, m, C->v170);
    func_00267930(C->m80, &C->px, a, b);
    sceVu0UnitMatrix(C->mc0);
    func_00236d48(C->mc0, C->mc0, &C->rx);
    sceVu0MulMatrix(C->m0, C->m40, C->m80);
    C->v190[0] = dx;
    C->v190[1] = dy;
    C->v190[2] = dz;
    C->v190[3] = 1.0f;
    func_002673b8(C->v190, C->v190);
}
#undef C

void func_002370c8(u64 *p) {
    p[2] = 0xF000000000000001ULL;
    p[3] = 0xEEEEEEEEEEEEEEEEULL;
    p[4] = 0x800D0ULL;
    p[5] = 0x4CULL;
    p[6] = 0x31000070ULL;
    p[7] = 0x4EULL;
    p[8] = 0x740000007000ULL;
    p[9] = 0x18ULL;
    p[10] = 0x17F000001FF0000ULL;
    p[11] = 0x40ULL;
    p[12] = 0x50003ULL;
    p[13] = 0x47ULL;
    p[14] = 0x8000000044ULL;
    p[15] = 0x42ULL;
    p[16] = 0;
    p[17] = 0x4AULL;
    p[18] = 0x20000045DD308002ULL;
    p[19] = 6;
    p[20] = 0x60ULL;
    p[21] = 0x14ULL;
    p[22] = 0x2000000001300000ULL;
    p[23] = 0x16ULL;
    p[24] = 0;
    p[25] = 0x34ULL;
    p[26] = 0;
    p[27] = 0x36ULL;
    p[28] = 0;
    p[29] = 8;
    p[30] = 1;
    p[31] = 0x1AULL;
    p[32] = 1;
    p[33] = 0x46ULL;
    p[34] = 0x4000000000008001ULL;
    p[35] = 0xEEEEEEEEEEEEEEEEULL;
    p[36] = 0;
    p[37] = 0x45ULL;
    p[38] = -4;
    p[39] = 0x44ULL;
    p[40] = 0;
    p[41] = 0x49ULL;
    p[42] = 0x8000000080ULL;
    p[43] = 0x3BULL;
}

extern u64 D_006480D0[];
void func_00237018(void *, s32, s32);

void func_00237318(void) {
    D_006480D0[2] = 0xF000000000000001ULL;
    D_006480D0[3] = 0xEEEEEEEEEEEEEEEEULL;
    D_006480D0[4] = 0x800D0ULL;
    D_006480D0[5] = 0x4CULL;
    D_006480D0[6] = 0x31000070ULL;
    D_006480D0[7] = 0x4EULL;
    D_006480D0[8] = 0x740000007000ULL;
    D_006480D0[9] = 0x18ULL;
    D_006480D0[10] = 0x17F000001FF0000ULL;
    D_006480D0[11] = 0x40ULL;
    D_006480D0[12] = 0x5000DULL;
    D_006480D0[13] = 0x47ULL;
    D_006480D0[14] = 0x44ULL;
    D_006480D0[15] = 0x42ULL;
    D_006480D0[16] = 0;
    D_006480D0[17] = 0x4AULL;
    D_006480D0[18] = 0x20000045DD308002ULL;
    D_006480D0[19] = 6;
    D_006480D0[20] = 0x60ULL;
    D_006480D0[21] = 0x14ULL;
    D_006480D0[22] = 0x2000000001300000ULL;
    D_006480D0[23] = 0x16ULL;
    D_006480D0[24] = 0;
    D_006480D0[25] = 0x34ULL;
    D_006480D0[26] = 0;
    D_006480D0[27] = 0x36ULL;
    D_006480D0[28] = 5;
    D_006480D0[29] = 8;
    D_006480D0[30] = 1;
    D_006480D0[31] = 0x1AULL;
    D_006480D0[32] = 1;
    D_006480D0[33] = 0x46ULL;
    D_006480D0[34] = 0x4000000000008001ULL;
    D_006480D0[35] = 0xEEEEEEEEEEEEEEEEULL;
    D_006480D0[36] = 0;
    D_006480D0[37] = 0x45ULL;
    D_006480D0[38] = -4;
    D_006480D0[39] = 0x44ULL;
    D_006480D0[40] = 0;
    D_006480D0[41] = 0x49ULL;
    D_006480D0[42] = 0x8000000080ULL;
    D_006480D0[43] = 0x3BULL;
    func_00237018(D_006480D0, 22, 1);
}

#include "data/data_003F.h"
#include "data/data_0042.h"
