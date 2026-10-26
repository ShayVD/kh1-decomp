/* dktitle.x func_00f206c8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x60]; } LI;
extern LI D_002BC1B0, D_002BC210;
void sceGsSetDefLoadImage(LI *lp, s16 dbp, s16 dbw, s16 dpsm, s16 x, s16 y, s16 w, s16 h);
s32 sceGsExecLoadImage(LI *lp, void *src);
s32 sceGsSyncPath(s32, s32);
void FlushCache(s32);
void func_00f206c8(void *img, void *clut, s32 dbp, s32 w, s32 h, s32 psm, s32 cbp) {
    s32 bw = (w < 64) ? 1 : w;
    if (psm == 8) {
        sceGsSetDefLoadImage(&D_002BC1B0, dbp, bw / 64, 19, 0, 0, w, h);
    } else {
        sceGsSetDefLoadImage(&D_002BC1B0, dbp, bw / 64, 20, 0, 0, w, h);
    }
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_002BC1B0, img);
    if (psm == 8) {
        sceGsSetDefLoadImage(&D_002BC210, cbp, 0, 0, 0, 0, 16, 16);
    } else {
        sceGsSetDefLoadImage(&D_002BC210, cbp, 0, 0, 0, 0, 8, 2);
    }
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_002BC210, clut);
}
