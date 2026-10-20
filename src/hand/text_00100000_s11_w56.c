/* func_00105d88 (hand), s11w56. FLAGGED DEAD CODE: the four `if (n <cmp> 0) { m = 1; m = 2; } else { m = 1; m = 2; }` tests in loop 1 are dead (m is reloaded before loop 2; identical multi-set arms keep each branch alive through sched2, jump2 removes them, no code). They give the shared counter n (loop-1 count-down and loop-2 reversed counter, one variable) 8 extra loop-depth-weighted refs, so global-alloc allocates n before the loop-2 pointer giv: a1 for both counters as in the original. From session8 w12/w8 7w draft. */
#include "common.h"
extern u8 *D_002A62AC, *D_002A62B0, *D_002A62C4, *D_002A62C8, *D_002A62CC;
typedef struct { s32 v; } SV; extern SV *D_002A62B4;
extern s32 D_002A62B8;
extern SV *D_002A62BC;
extern u8 *D_002A62C0;
extern u32 D_002A62D0, D_002A62D4, D_002A62D8, D_002A62DC, D_002A62E0, D_002A62E4;
void func_00105d88(u8 *h) {
    u32 *w = (u32 *)h;
    s32 n;
    s32 i;
    s32 m;
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
    for (i = 0; n != 0; n--, i++) {
        D_002A62BC[i].v += (s32)D_002A62C0;
        if (n < 0) { m = 1; m = 2; } else { m = 1; m = 2; }
        if (n > 0) { m = 1; m = 2; } else { m = 1; m = 2; }
        if (n >= 0) { m = 1; m = 2; } else { m = 1; m = 2; }
        if (n <= 0) { m = 1; m = 2; } else { m = 1; m = 2; }
    }
    m = D_002A62DC;
    for (n = 0; n < m; n++) {
        if (D_002A62B4[n].v != -1) {
            D_002A62B4[n].v += D_002A62B8;
        }
    }
}
#include "data/data_002A.h"
