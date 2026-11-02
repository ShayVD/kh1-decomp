/* wm.x func_00f671d8: matched by hand. */
#include "ovl.h"
#include "platform/dma.h"

void FlushCache(s32);
s32 sceDmaSync(s32, s32, s32);
s32 sceGsSyncPath(s32, s32);

void func_00f671d8(u32 arg0) {
    PlatDmaPutVif1Qwc(0);
    PlatDmaPutVif1Tadr(PLAT_DMA_ADDR(arg0));
    PlatDmaPutStat(2);
    FlushCache(0);
    PlatDmaPutVif1Chcr(0x145);
    sceDmaSync(sceDmaGetChan(1), 0, 0);
    sceGsSyncPath(0, 0);
}
