/* 00105d88: 7w, hand, code = session8/w8 draft. Finding (w12 s8): loop 2 is a global-alloc priority question: giv p (pseudo 214) 9 refs/13 live = 2.08 beats the reversed counter j (90) 7 refs/11 = 1.27; j needs an 8th ref (3*8/11 = 2.18). Tried: pointer walks, do-while with explicit counter (size changes, B4 lui not rehoisted), reusing i/n for loop 2, counting m down, temp for the load, continue, while form, u32 j: all 7w or worse. */
#include "common.h"
extern u8 *D_002A62AC, *D_002A62B0, *D_002A62C4, *D_002A62C8, *D_002A62CC;
typedef struct { s32 v; } SV; extern SV *D_002A62B4;
extern s32 D_002A62B8;
extern SV *D_002A62BC;
extern u8 *D_002A62C0;
extern u32 D_002A62D0, D_002A62D4, D_002A62D8, D_002A62DC, D_002A62E0, D_002A62E4;
void func_00105d88(u8 *h) {
    u32 *w = (u32 *)h;
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
    D_002A62B4 = (SV *)(h + w[10]);
    D_002A62DC = w[11] / 4;
    D_002A62BC = (SV *)(h + w[12]);
    D_002A62E4 = n = w[13] / 4;
    D_002A62C4 = h + w[2];
    D_002A62D4 = w[3] / 12;
    D_002A62C8 = h + w[4];
    D_002A62D8 = w[5] / 8;
    D_002A62B8 = (s32)(h + w[14]);
    D_002A62C0 = h + w[16];
    for (i = 0; n != 0; n--, i++) D_002A62BC[i].v += (s32)D_002A62C0;
    m = D_002A62DC;
    for (j = 0; j < m; j++) {
        if (D_002A62B4[j].v != -1) D_002A62B4[j].v += D_002A62B8;
    }
}
