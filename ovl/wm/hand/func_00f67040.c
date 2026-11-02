/* wm.x func_00f67040: matched by hand. */
#include "ovl.h"
#include "platform/dma.h"

void iFlushCache(s32);
extern u32 D_0108F03C;

s32 func_00f67040(u32 *arg0) {
    u32 a;
    sceDmaGetChan(2);
    a = arg0[4];
    D_0108F03C = a;
    PlatDmaPutGifQwc(0);
    PlatDmaPutGifTadr(PLAT_DMA_ADDR(a));
    PlatDmaPutStat(4);
    iFlushCache(0);
    PlatDmaPutGifChcr(0x145);
    return 2;
}
