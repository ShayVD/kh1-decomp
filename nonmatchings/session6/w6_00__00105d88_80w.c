/* ~80 words off (hand): orig uses 3 s-regs for hoisted luis; loop copies (move v1,a0; move a0,t0) suggest inlined helpers; first loop counts down on u32 n. */
#include "common.h"
extern s32 D_002A62AC, D_002A62B0, D_002A62B4, D_002A62B8, D_002A62BC, D_002A62C0, D_002A62C4, D_002A62C8, D_002A62CC;
extern u32 D_002A62D0, D_002A62D4, D_002A62D8, D_002A62DC, D_002A62E0, D_002A62E4;
void func_00105d88(u32 *h) {
    u32 i, n;
    s32 *p;
    s32 base;
    D_002A62AC = (s32)h + h[0];
    D_002A62B0 = (s32)h + h[6];
    D_002A62D0 = h[7] / 20;
    D_002A62CC = (s32)h + h[8];
    D_002A62E0 = h[9] / 16;
    D_002A62B4 = (s32)h + h[10];
    D_002A62DC = h[11] / 4;
    D_002A62BC = (s32)(p = (s32 *)((s32)h + h[12]));
    D_002A62E4 = n = h[13] / 4;
    D_002A62C4 = (s32)h + h[2];
    D_002A62D4 = h[3] / 12;
    D_002A62C8 = (s32)h + h[4];
    D_002A62D8 = h[5] / 8;
    D_002A62B8 = (s32)h + h[14];
    D_002A62C0 = base = (s32)h + h[16];
    for (i = 0; i < n; i++) {
        *p++ += base;
    }
    {
        s32 m = D_002A62DC;
        s32 j;
        p = (s32 *)D_002A62B4;
        for (j = 0; j < m; j++) {
            if (*p != -1) *p += D_002A62B8;
            p++;
        }
    }
}
