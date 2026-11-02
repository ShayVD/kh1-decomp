/* wm.x func_00f668d0: matched by hand. */
#include "ovl.h"
#include "platform/dma.h"

void iFlushCache(s32);
void FlushCache(s32);

void func_00f668d0(u32 arg0, s32 arg1) {
    PlatDmaPutVif1Qwc(0);
    PlatDmaPutVif1Tadr(PLAT_DMA_ADDR(arg0));
    PlatDmaPutStat(2);
    if (arg1 != 0) {
        iFlushCache(0);
    } else {
        FlushCache(0);
    }
    PlatDmaPutVif1Chcr(0x145);
}
