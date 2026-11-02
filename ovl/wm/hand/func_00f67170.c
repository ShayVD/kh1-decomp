/* wm.x func_00f67170: matched by hand. */
#include "ovl.h"
#include "platform/dma.h"

void iFlushCache(s32);

s32 func_00f67170(u32 *arg0) {
    u32 a = arg0[4];
    PlatDmaPutVif1Qwc(0);
    PlatDmaPutVif1Tadr(PLAT_DMA_ADDR(a));
    PlatDmaPutStat(2);
    iFlushCache(0);
    PlatDmaPutVif1Chcr(0x145);
    return 2;
}
