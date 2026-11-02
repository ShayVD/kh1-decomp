/* gb.x func_00f40078: matched by hand. */
#include "ovl.h"
#include "platform/dma.h"

typedef struct { u8 pad[0x10]; u32 v; } Task;
void iFlushCache(s32);

s32 func_00f40078(Task *t) {
    u32 v = t->v;
    PlatDmaPutVif1Qwc(0);
    PlatDmaPutVif1Tadr(PLAT_DMA_ADDR(v));
    PlatDmaPutStat(2);
    iFlushCache(0);
    PlatDmaPutVif1Chcr(0x145);
    return 2;
}
