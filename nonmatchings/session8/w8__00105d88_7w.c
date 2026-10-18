/* 00105d88 hand, 7w (session-7 draft 33w), same size. Fixed: D_002A62B4/D_002A62BC as pointers to a one-field struct (SV *): an s32 store does not alias them, so loop.c hoists their loads (a plain s32 * global is reloaded every iteration); loop 1 reads D_002A62BC/D_002A62C0 directly (CSE turns the hoisted loads into the orig's 'move v1,a0; move a0,t0') and counts n down: for (i = 0; n != 0; n--, i++). Left: loop 2 counter a2/p a1 vs orig a1/a2 (global-alloc: giv p 9 refs/13 > reversed j 7/11). */
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
