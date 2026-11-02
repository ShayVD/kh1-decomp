/* gb.x func_00f3ff48: matched by hand. */
#include "ovl.h"
#include "platform/dma.h"

typedef struct { u8 pad[0x10]; u32 v; } Task;
void iFlushCache(s32);
extern u32 D_00F8287C;

s32 func_00f3ff48(Task *t) {
    u32 v;
    sceDmaGetChan(2);
    v = t->v;
    D_00F8287C = v;
    PlatDmaPutGifQwc(0);
    PlatDmaPutGifTadr(PLAT_DMA_ADDR(v));
    PlatDmaPutStat(4);
    iFlushCache(0);
    PlatDmaPutGifChcr(0x145);
    return 2;
}
