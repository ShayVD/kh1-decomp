#include "common.h"
void func_00260738(void *, s32);
s32 isceSifSetDma(void *, s32);
s32 sceSifSetDma(void *, s32);
extern void *D_0066E6E0;
typedef struct { u32 psize:8; u32 dsize:24; void *dest; s32 cid; u32 opt; } SifCmdPkt;
typedef struct { void *src; void *dest; s32 size; s32 attr; } SifDma;

s32 func_00260458(s32 cid, u32 mode, SifCmdPkt *pkt, u32 size, void *src, void *dest, s32 dsize) {
    SifDma dma[2];
    s32 n;
    if (size - 16 > 96) return 0;
    n = 0;
    if (dsize > 0) {
        n = 1;
        pkt->dsize = dsize;
        pkt->dest = dest;
        dma[0].src = src;
        dma[0].dest = dest;
        dma[0].size = dsize;
        dma[0].attr = 0;
        if (mode & 4) func_00260738(src, dsize);
    } else {
        pkt->dsize = 0;
        pkt->dest = 0;
    }
    dma[n].src = pkt;
    dma[n].dest = D_0066E6E0;
    dma[n].size = size;
    dma[n].attr = 0x44;
    pkt->cid = cid;
    pkt->psize = size;
    func_00260738(pkt, size);
    n++;
    if (mode & 1) return isceSifSetDma(dma, n);
    return sceSifSetDma(dma, n);
}
