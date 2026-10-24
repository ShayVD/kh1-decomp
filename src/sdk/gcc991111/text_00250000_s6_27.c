#include "common.h"
typedef u32 T4;
typedef u32 T1;
typedef u32 T2;
typedef void * T3;
typedef u32 T5;
typedef struct { void (* func)(void *, void *); int data; } SifHandler;
typedef struct {
    T1 pbuf;
    T1 sbuf;
    T5 sysbuf;
    T2 htab;
    int hsize;
    T2 uhtab;
    int uhsize;
    T3 sreg;
} SifCtl;
typedef struct { u8 hdr[0xc]; u32 opt; u32 buf; } SifInitPkt;
extern int D_0046BE8C;
extern SifCtl D_0066E6D8;
extern int D_0066E6D4;
extern u8 D_0066E600[];
extern u8 D_0066E680[];
extern SifHandler D_0066E700[];
extern u32 D_0066E800[];
extern SifInitPkt D_0066E6C0;
int DIntr(void);
int EIntr(void);
void FlushCache(int);
void sceSifSetDChain(void);
int AddDmacHandler(int, void *, int);
int EnableDmac(int);
u32 sceSifGetReg(u32);
u32 sceSifSetReg(u32, u32);
void func_002600c0(void *, void *);
void func_002600a0(void *, void *);
int func_00260610(int);
void func_00260590(u32, void *, int, u32, u32, u32);

void func_00260118(void) {
    int i;
    DIntr();
    if (D_0046BE8C) {
        EIntr();
        return;
    }
    D_0046BE8C = 1;
    D_0066E6D8.pbuf = (T1)((u32) D_0066E600 | 0x20000000);
    D_0066E6D8.sbuf = (T1)((u32) D_0066E680 | 0x20000000);
    D_0066E6D8.sysbuf = 0;
    D_0066E6D8.htab = (T2) D_0066E700;
    D_0066E6D8.hsize = 32;
    D_0066E6D8.uhtab = 0;
    D_0066E6D8.uhsize = 0;
    D_0066E6D8.sreg = (T3) D_0066E800;
    for (i = 0; i < 32; i++) {
        D_0066E700[i].func = 0;
        D_0066E700[i].data = 0;
    }
    for (i = 0; i < 32; i++)
        D_0066E800[i] = 0;
    D_0066E700[0].func = (void *) func_002600c0;
    D_0066E700[0].data = (void *) &D_0066E6D8;
    D_0066E700[1].func = (void *) func_002600a0;
    D_0066E700[1].data = (void *) &D_0066E6D8;
    EIntr();
    FlushCache(0);
    if (*(volatile u32 *) 0x1000e010 & 0x20)
        *(volatile u32 *) 0x1000e010 = 0x20;
    if (!(*(volatile u32 *) 0x1000c000 & 0x100))
        sceSifSetDChain();
    D_0066E6D4 = AddDmacHandler(5, func_00260610, 0);
    EnableDmac(5);
    if ((D_0066E6D8.sysbuf = sceSifGetReg(0x80000000))) {
        D_0066E6C0.buf = (u32) D_0066E600;
        func_00260590(0x80000000, &D_0066E6C0, 20, 0, 0, 0);
        return;
    }
    while (!(sceSifGetReg(4) & 0x20000))
        ;
    D_0066E6D8.sysbuf = sceSifGetReg(2);
    sceSifSetReg(0x80000000, (u32) D_0066E6D8.sysbuf);
    sceSifSetReg(0x80000001, (u32) &D_0066E6D8);
    D_0066E6C0.buf = (u32) D_0066E600;
    D_0066E6C0.opt = 0;
    func_00260590(0x80000002, &D_0066E6C0, 20, 0, 0, 0);
}

void func_00260738(void *, s32);
s32 isceSifSetDma(void *, s32);
s32 sceSifSetDma(void *, s32);
extern u32 D_0066E6E0;
typedef struct { u32 psize:8; u32 dsize:24; u32 dest; s32 cid; u32 opt; } SifCmdPkt;
typedef struct { u32 src, dest; int size, attr; } SifDma;

s32 func_00260458(s32 cid, u32 mode, SifCmdPkt *pkt, u32 size, void *src, void *dest, s32 dsize) {
    SifDma dma[2];
    s32 n;
    if (size - 16 > 96) return 0;
    n = 0;
    if (dsize > 0) {
        n = 1;
        dma[0].src = (u32) src;
        dma[0].dest = (u32) dest;
        pkt->dsize = dsize;
        pkt->dest = (u32) dest;
        dma[0].size = dsize;
        dma[0].attr = 0;
        if (mode & 4) func_00260738(src, dsize);
    } else {
        pkt->dsize = 0;
        pkt->dest = 0;
    }
    dma[n].src = (u32) pkt;
    dma[n].dest = D_0066E6E0;
    dma[n].size = size;
    pkt->cid = cid;
    pkt->psize = size;
    dma[n].attr = 0x44;
    func_00260738(pkt, size);
    n++;
    if (mode & 1) return isceSifSetDma(dma, n);
    return sceSifSetDma(dma, n);
}

typedef kh1_u128 u128;
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

/* rodata */
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
    *(u128 *)&lp->giftag0 = 0;
    lp->giftag0.NLOOP = 4;
    lp->giftag0.NREG = 1;
    lp->giftag0.REGS0 = 0xe;
    lp->bitbltbuf = ((u64)dbp << 32) | ((u64)dbw << 48) | ((u64)dpsm << 56);
    lp->bitbltbufaddr = 0x50;
    lp->trxpos = ((u64)x << 32) | ((u64)y << 48);
    lp->trxposaddr = 0x51;
    lp->trxreg = (u64)w | ((u64)h << 32);
    lp->trxregaddr = 0x52;
    lp->trxdir = 0;
    lp->trxdiraddr = 0x53;
    *(u128 *)&lp->giftag1 = 0;
    lp->giftag1.NLOOP = qwc;
    lp->giftag1.EOP = 1;
    lp->giftag1.FLG = 2;
    __asm__ volatile("sync.l");
    return sizeof(GsLoadImage) / 16;
}

typedef struct {
    u32 vifcode[4];
    GifTag giftag;
    u64 bitbltbuf, bitbltbufaddr;
    u64 trxpos, trxposaddr;
    u64 trxreg, trxregaddr;
    u64 finish, finishaddr;
    u64 trxdir, trxdiraddr;
} GsStoreImage;

s32 sceGsSetDefStoreImage(GsStoreImage *sp, s16 sbp, s16 sbw, s16 spsm, s16 x, s16 y, s16 w, s16 h) {
    *(u128 *)&sp->giftag = 0;
    sp->vifcode[0] = 0;
    sp->vifcode[1] = 0x06008000;
    sp->vifcode[2] = 0x13000000;
    sp->vifcode[3] = 0x50000006;
    sp->giftag.NLOOP = 5;
    sp->giftag.EOP = 1;
    sp->giftag.NREG = 1;
    sp->giftag.REGS0 = 0xe;
    sp->bitbltbuf = (u64)sbp | ((u64)sbw << 16) | ((u64)spsm << 24);
    sp->bitbltbufaddr = 0x50;
    sp->trxpos = (u64)x | ((u64)y << 16);
    sp->trxposaddr = 0x51;
    sp->trxreg = (u64)w | ((u64)h << 32);
    sp->trxregaddr = 0x52;
    sp->finish = 0;
    sp->finishaddr = 0x61;
    sp->trxdir = 1;
    sp->trxdiraddr = 0x53;
    __asm__ volatile("sync.l");
    return sizeof(GsStoreImage) / 16;
}
