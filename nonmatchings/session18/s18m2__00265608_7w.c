/* sceGsDefDispEnv 0x265608: 7 LCS words off (was 9, session9 w11), sdk/gcc991111, right size 884. s18m2: in both h0!=1 blocks H = (h-1)<<44 is a local register variable pinned to a3 (`register u64 HH asm("$7");`, set before magh; any of the 4 positions gives the same output) and EXPR2 uses HH: every register is now the original's (the addiu/dsll32 pair was a2, now a3). Left: the pair still issues after the off[] loads (orig: right after the div, sched priority, see session11 w67) and the final OR order (or a1,a1,a3 vs orig or a3,a3,a0). All 1680 OR trees of EXPR2 with HH: floor 7. Pinning the (H|W) OR result to a3 too breaks the h2==2/h2==3 cross-jump (37-49w). From the s9 w11 draft: */
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
#define EXPR1(K) (((((u64)(magh - 1) << 23) | (((u64)((ox + dx * magh) & 0xfff)) | ((u64)(g->h4 ? h * 2 - 1 : h - 1) << 44))) | ((u64)((dy + off[1] + K) & 0xfff) << 12)) | ((u64)(dw) << 32))
#define EXPR2(K) (((((u64)(magh - 1) << 23) | HH) | (((u64)((dy + off[1] + K) & 0xfff) << 12) | ((u64)(dw) << 32))) | ((u64)((ox + dx * magh) & 0xfff)))
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
            disp->display = EXPR1(50);
        } else {
            register u64 HH asm("$7");
            s32 magh;
            s64 ox;
            s32 dw;
            HH = (u64)(h - 1) << 44;
            magh = (w + 2559) / w;
            ox = off[0] + 636L;
            dw = magh * w - 1;
            disp->display = EXPR2(25);
        }
    } else if (g->h2 == 3) {
        if (g->h0 == 1) {
            s32 magh = (w + 2559) / w;
            s64 ox = off[0] + 656L;
            s32 dw = magh * w - 1;
            disp->display = EXPR1(72);
        } else {
            register u64 HH asm("$7");
            s32 magh;
            s64 ox;
            s32 dw;
            HH = (u64)(h - 1) << 44;
            magh = (w + 2559) / w;
            ox = off[0] + 656L;
            dw = magh * w - 1;
            disp->display = EXPR2(36);
        }
    } else if (g->h2 == 0x50) {
        s64 ox = (720 - w) / 2 * 2 + (s64)off[0]; s64 dd = dx * 2 + 232L;
        disp->display = ((((((u64)(h - 1) << 44) | ((u64)1 << 23)) | ((u64)((ox + dd) & 0xfff))) | ((u64)((dy + off[1] + 35) & 0xfff) << 12)) | ((u64)(w * 2 - 1) << 32));
    } else {
        scePrintf(D_00492930, g->h2);
    }
    disp->bgcolor = 0;
}
