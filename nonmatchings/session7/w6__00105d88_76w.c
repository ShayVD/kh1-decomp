/* 00105d88 hand 76w (size 404 vs 416). Orig: loop 1 is count-down (if(n) do..while(--n) form) with late copies 'move v1,a0 (base); move a0,t0 (p)' before the loop and 3 s-regs for hoisted luis; ours coalesces differently. Loop-body nops are gas r5900 short-loop fixes. Flagsweep: nothing. */
#include "common.h"
extern u8 *D_002A62AC, *D_002A62B0, *D_002A62B4, *D_002A62B8, *D_002A62C4, *D_002A62C8, *D_002A62CC;
extern s32 *D_002A62BC;
extern u8 *D_002A62C0;
extern u32 D_002A62D0, D_002A62D4, D_002A62D8, D_002A62DC, D_002A62E0, D_002A62E4;
void func_00105d88(u8 *h) {
    u32 *w = (u32 *)h;
    s32 *p;
    u32 i;
    s32 j, m;
    D_002A62AC = h + w[0];
    D_002A62B0 = h + w[6];
    D_002A62D0 = w[7] / 20;
    D_002A62CC = h + w[8];
    D_002A62E0 = w[9] / 16;
    D_002A62B4 = h + w[10];
    D_002A62DC = w[11] / 4;
    D_002A62BC = (void *)(h + w[12]);
    D_002A62E4 = w[13] / 4;
    D_002A62C4 = h + w[2];
    D_002A62D4 = w[3] / 12;
    D_002A62C8 = h + w[4];
    D_002A62D8 = w[5] / 8;
    D_002A62B8 = h + w[14];
    D_002A62C0 = (void *)(h + w[16]);
    { s32 *q = (s32 *)D_002A62BC; u32 n = D_002A62E4; if (n) do { *q++ += (s32)D_002A62C0; } while (--n); }
    m = D_002A62DC;
    p = (s32 *)D_002A62B4;
    for (j = 0; j < m; j++) {
        if (*p != -1) *p += (s32)D_002A62B8;
        p++;
    }
}
