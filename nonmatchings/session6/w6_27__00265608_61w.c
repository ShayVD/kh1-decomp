/* sceGsDefDispEnv 0x265608, sdk/gcc991111, same size, 61 words off: in the DISPLAY computation the original evaluates magh*w (mult) before dx*magh (mult1) and ORs as ((M|W)|(X|H))|Y; ours swaps the two mults -> register swaps a0/a1. smode2/dispfb parts match. */
#include "common.h"
typedef struct { s16 h0, h2, h4, h6; s32 x8; } GsState;
typedef struct { u64 pmode, smode2, dispfb, display, bgcolor; } DispEnv;
void *func_002654e0(void);
s32 func_00265558(void);
void func_002655f8(s32, s32 *, s32 *, s32 *, s32 *);
s32 scePrintf(const char *, ...);
extern char D_00492930[];
#define SET_DISPFB(fbp, fbw, psm, dbx, dby) ((u64)(fbp) | ((u64)(fbw) << 9) | ((u64)(psm) << 15) | ((u64)(dbx) << 32) | ((u64)(dby) << 43))
#define SET_DISPLAY(dx, dy, magh, magv, dw, dh) ((u64)(dx) | ((u64)(dy) << 12) | ((u64)(magh) << 23) | ((u64)(magv) << 27) | ((u64)(dw) << 32) | ((u64)(dh) << 44))

#define DISP(X, Y, M, W, H) ((u64)(H) << 44 | (u64)(W) << 32 | (u64)(M) << 23 | (u64)(Y) << 12 | (u64)(X))
void sceGsDefDispEnv(DispEnv *disp, s16 psm, s16 w, s16 h, s16 dx, s16 dy) {
    GsState *g = func_002654e0();
    s32 off[4];
    if (!(g->h2 == 2 || g->h2 == 3) && func_00265558()) {
        func_002655f8(g->h2, &off[0], &off[1], &off[2], &off[3]);
    } else {
        off[3] = 0;
        off[2] = 0;
        off[1] = 0;
        off[0] = 0;
    }
    disp->pmode = 0x66;
    if (g->h0) { if (g->h4) disp->smode2 = 3; else disp->smode2 = 1; } else disp->smode2 = 2;
    disp->dispfb = ((u64)(psm & 0xf) << 15) | ((u64)(((w + 63) >> 6) & 0x3f) << 9);
    if (g->h2 == 2) {
        if (g->h0 == 1) {
            s32 magh = (w + 2559) / w;
            s64 ox = off[0] + 636L;
            s32 dw = magh * w - 1;
            disp->display = DISP(((ox + dx * magh) & 0xfff), ((dy + off[1] + 50) & 0xfff), (magh - 1), dw, (g->h4 ? h * 2 - 1 : h - 1));
        } else {
            s32 magh = (w + 2559) / w;
            s64 ox = off[0] + 636L;
            disp->display = DISP(((ox + dx * magh) & 0xfff), ((dy + off[1] + 25) & 0xfff), (magh - 1), (magh * w - 1), (h - 1));
        }
    } else if (g->h2 == 3) {
        if (g->h0 == 1) {
            s32 magh = (w + 2559) / w;
            s64 ox = off[0] + 656L;
            disp->display = DISP(((ox + dx * magh) & 0xfff), ((dy + off[1] + 72) & 0xfff), (magh - 1), (magh * w - 1), (g->h4 ? h * 2 - 1 : h - 1));
        } else {
            s32 magh = (w + 2559) / w;
            s64 ox = off[0] + 656L;
            disp->display = DISP(((ox + dx * magh) & 0xfff), ((dy + off[1] + 36) & 0xfff), (magh - 1), (magh * w - 1), (h - 1));
        }
    } else if (g->h2 == 0x50) {
        disp->display = SET_DISPLAY(((720 - w) / 2 * 2 + off[0] + (dx * 2 + 232L)) & 0xfff, (dy + off[1] + 35) & 0xfff, 1, 0, w * 2 - 1, h - 1);
    } else {
        scePrintf(D_00492930, g->h2);
    }
    disp->bgcolor = 0;
}
