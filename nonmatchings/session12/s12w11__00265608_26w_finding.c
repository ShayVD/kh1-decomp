/* 00265608 sceGsDefDispEnv FINDING, 26 LCS words (draft session9/w11 stays best at 9), sdk/gcc991111, size 884 right. The h0!=1 OR tree now matches the original ((M|W)|(X|H))|Y exactly (or a1,a1,a3 / or v0,v0,a0 / or v0,v0,a1 / or v0,v0,v1): fold reassociates the source tree, and the source ((M|X)|(Y|H))|W (inline or as u64 leaf locals) is what folds to it (98 of the 1680 ordered trees give the shape; w11's note that such trees break the h2==2->h2==3 cross-jump no longer holds: the jump is right). Left: allocation. gdb on gcc991111 local-alloc (s12w11 bq9.sh): qtys in the h2==3 h0!=1 block are magh/M/final (n17, v0), X chain incl. X|H (n10, bd10-48), Y chain (n10, bd12-50), H (n4, bd14-46), mult dx*magh (n2, bd28-36), W (n6, bd30-44). Original needs priority Y > W > X > mult > H, i.e. Y born >= 16, X <= 12, H <= 12: exactly what H-first scheduling gives (orig emits div, addiu a3 (H), lw a1, dsll32, lw v1). Ours issues both off[] loads before H in sched1 and sched2 (loads prio 10/9 > H 7; ready at t=2 after the trap_if at t=1). The original's order fits only if the loads became ready one cycle after the div (e.g. a div insn that is itself the memory barrier, or 509 w+2559 outside the block); no source shape found. Leaf-statement orders x the 98 shape trees: best 11 (wrong shape); orig-tree shapes 18-26. */
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
#define EXPR2(K) (((((u64)(magh - 1) << 23) | ((u64)((ox + dx * magh) & 0xfff))) | (((u64)((dy + off[1] + K) & 0xfff) << 12) | ((u64)(h - 1) << 44))) | ((u64)(dw) << 32))
#define EXPR2old(K) (((((u64)(magh - 1) << 23) | ((u64)(h - 1) << 44)) | (((u64)((dy + off[1] + K) & 0xfff) << 12) | ((u64)(dw) << 32))) | ((u64)((ox + dx * magh) & 0xfff)))
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
            s32 magh = (w + 2559) / w;
            s64 ox = off[0] + 636L;
            s32 dw = magh * w - 1;
            disp->display = EXPR2(25);
        }
    } else if (g->h2 == 3) {
        if (g->h0 == 1) {
            s32 magh = (w + 2559) / w;
            s64 ox = off[0] + 656L;
            s32 dw = magh * w - 1;
            disp->display = EXPR1(72);
        } else {
            s32 magh = (w + 2559) / w;
            s64 ox = off[0] + 656L;
            s32 dw = magh * w - 1;
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
