/* Full-screen effects (sceneeff.c), its nostrict part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"

/* func_00103058 (from hand/nostrict/text_00100000_h51.c). */
extern s32 D_002A61F8;
extern s32 D_002A61FC;
extern u64 D_002A5430[];
extern u64 D_002A52B0[];
extern u64 D_002A5620[];
extern u64 D_002A5A90[];
extern u64 D_002A5AC0[];
void func_00106b18(void *);
#define XYZ(x, y, z) ((u64)(x) | ((u64)(y) << 16) | ((u64)(z) << 32))
s32 func_00103058(void) {
    s32 z = D_002A61FC;
    D_002A5430[5] = XYZ(0x6fe0, 0x73e0, z);
    D_002A5430[7] = XYZ(0x8fe0, 0x8be0, z);
    D_002A5430[11] = XYZ(0x6fc0, 0x73c0, z);
    D_002A5430[13] = XYZ(0x8fc0, 0x8bc0, z);
    D_002A5430[17] = XYZ(0x7000, 0x7400, z);
    D_002A5430[19] = XYZ(0x9000, 0x8c00, z);
    D_002A5430[23] = XYZ(0x6fc0, 0x7400, z);
    D_002A5430[25] = XYZ(0x8fc0, 0x8c00, z);
    D_002A5430[29] = XYZ(0x7000, 0x73c0, z);
    D_002A5430[31] = XYZ(0x9000, 0x8bc0, z);
    D_002A5430[35] = XYZ(0x6fe0, 0x73c0, z);
    D_002A5430[37] = XYZ(0x8fe0, 0x8bc0, z);
    D_002A5430[41] = XYZ(0x6fc0, 0x73e0, z);
    D_002A5430[43] = XYZ(0x8fc0, 0x8be0, z);
    D_002A5430[47] = XYZ(0x6fe0, 0x7400, z);
    D_002A5430[49] = XYZ(0x8fe0, 0x8c00, z);
    D_002A5430[53] = XYZ(0x7000, 0x73e0, z);
    D_002A5430[55] = XYZ(0x9000, 0x8be0, z);
    if (D_002A61F8 != 0) {
        D_002A52B0[4] = XYZ(0x7000, 0x7400, z);
        D_002A52B0[5] = XYZ(0x9000, 0x8c00, z);
        func_00106b18(D_002A5620);
        func_00106b18(D_002A5AC0);
    } else {
        func_00106b18(D_002A5A90);
        func_00106b18(D_002A5AC0);
    }
    return 4;
}
#undef XYZ

