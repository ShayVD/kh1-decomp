#include "common.h"
typedef struct { s16 h0, h2, h4, h6; s32 x8; void *xc; } GsState;
void *func_002654e0(void);
s32 GsPutIMR(u64);
s32 DisableIntc(s32);
s32 RemoveIntcHandler(s32, void *);
void SetGsCrt(s16, s16, s16);
#define GS_CSR (*(volatile u64 *)0x12001000)

void func_00265350(s16 mode, s16 inter, s16 omode, s16 ffmd) {
    GsState *g;
    switch (mode) {
    case 0:
        g = func_002654e0();
        GS_CSR = 0x200;
        g->h0 = inter;
        g->h2 = omode;
        g->h6 = (u16)((GS_CSR >> 16) & 0xff);
        GsPutIMR(0xff00);
        g->h4 = ffmd != 0;
        if (g->x8) {
            DisableIntc(2);
            RemoveIntcHandler(2, g->xc);
            g->x8 = 0;
            g->xc = 0;
        }
        SetGsCrt(inter & 1, omode & 0xff, ffmd & 1);
        break;
    case 1:
        GS_CSR = 0x100;
        break;
    case 5:
        g = func_002654e0();
        g->h4 = ffmd != 0;
        g->h0 = inter;
        g->h2 = omode;
        g->h6 = (u16)((GS_CSR >> 16) & 0xff);
        SetGsCrt(inter & 1, omode & 0xff, ffmd & 1);
        break;
    }
}
