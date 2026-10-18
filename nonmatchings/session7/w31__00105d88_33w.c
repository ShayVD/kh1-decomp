// 00105d88 hand 33w (424 vs 416): locals q/n/base (s32 counts) fix loop-1 shape; left: loop-2 D_002A62B4 hoist + count-down (hoisting via local ptr gives 396b, orig keeps s2 frame), loop-1 regs t0/a1/a0 vs t1/t0/a1
#include "common.h"
extern u8 *D_002A62AC, *D_002A62B0, *D_002A62B4, *D_002A62B8, *D_002A62C4, *D_002A62C8, *D_002A62CC;
extern s32 *D_002A62BC;
extern u8 *D_002A62C0;
extern u32 D_002A62D0, D_002A62D4, D_002A62D8, D_002A62DC, D_002A62E0, D_002A62E4;
void func_00105d88(u8 *h) {
    u32 *w = (u32 *)h;
    s32 *p;
    s32 *q;
    s32 n;
    u8 *base;
    s32 i;
    s32 j, m;
    D_002A62AC = h + w[0];
    D_002A62B0 = h + w[6];
    D_002A62D0 = w[7] / 20;
    D_002A62CC = h + w[8];
    D_002A62E0 = w[9] / 16;
    D_002A62B4 = h + w[10];
    D_002A62DC = w[11] / 4;
    D_002A62BC = q = (s32 *)(h + w[12]);
    D_002A62E4 = n = w[13] / 4;
    D_002A62C4 = h + w[2];
    D_002A62D4 = w[3] / 12;
    D_002A62C8 = h + w[4];
    D_002A62D8 = w[5] / 8;
    D_002A62B8 = h + w[14];
    D_002A62C0 = base = h + w[16];
    for (i = 0; i < n; i++) q[i] += (s32)base;
    m = D_002A62DC;
    for (j = 0; j < m; j++) {
        if (((s32 *)D_002A62B4)[j] != -1) ((s32 *)D_002A62B4)[j] += (s32)D_002A62B8;
    }
}
