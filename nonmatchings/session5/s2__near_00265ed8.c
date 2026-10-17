#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
s32 scePrintf(const char *, ...);
extern char D_00492B30[];
typedef struct {
    u64 NLOOP:15; u64 EOP:1; u64 pad16:16; u64 id:14; u64 PRE:1; u64 PRIM:11; u64 FLG:2; u64 NREG:4;
    u64 REGS0:4; u64 REGS1:4; u64 REGS2:4; u64 REGS3:4; u64 REGS4:4; u64 REGS5:4; u64 REGS6:4; u64 REGS7:4;
    u64 REGS8:4; u64 REGS9:4; u64 REGS10:4; u64 REGS11:4; u64 REGS12:4; u64 REGS13:4; u64 REGS14:4; u64 REGS15:4;
} GifTag;
typedef struct {
    GifTag giftag0;
    u64 bitbltbuf, bitbltbufaddr;
    u64 trxpos, trxposaddr;
    u64 trxreg, trxregaddr;
    u64 trxdir, trxdiraddr;
    GifTag giftag1;
} GsLoadImage;

s32 sceGsSetDefLoadImage(GsLoadImage *lp, s16 dbp, s16 dbw, s16 dpsm, s16 x, s16 y, s16 w, s16 h) {
    s32 qwc = 0;
    switch (dpsm) {
    case 0: case 48:
        qwc = (w * h) >> 2;
        break;
    case 1: case 49:
        qwc = (w * h * 3) >> 4;
        break;
    case 2: case 10: case 50: case 58:
        qwc = (w * h) >> 3;
        break;
    case 19: case 27:
        qwc = (w * h) >> 4;
        break;
    case 20: case 36: case 44:
        qwc = (w * h) >> 5;
        break;
    }
    if (qwc > 32767) {
        scePrintf(D_00492B30);
        return 0;
    }
    *(u128 *)&lp->giftag1 = 0;
    *(u128 *)&lp->giftag0 = 0;
    lp->giftag1.NLOOP = qwc;
    lp->giftag0.NLOOP = 4;
    lp->giftag1.EOP = 1;
    lp->giftag0.NREG = 1;
    lp->giftag0.REGS0 = 0xe;
    lp->giftag1.FLG = 2;
    lp->bitbltbuf = ((u64)dbp << 32) | ((u64)dbw << 48) | ((u64)dpsm << 56);
    lp->bitbltbufaddr = 0x50;
    lp->trxpos = ((u64)x << 32) | ((u64)y << 48);
    lp->trxposaddr = 0x51;
    lp->trxreg = (u64)w | ((u64)h << 32);
    lp->trxregaddr = 0x52;
    lp->trxdiraddr = 0x53;
    lp->trxdir = 0;
    __asm__ volatile("sync.l");
    return sizeof(GsLoadImage) / 16;
}
