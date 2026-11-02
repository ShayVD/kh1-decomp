/* wm.x func_00f670c8: matched by hand. */
#include "ovl.h"
#include "platform/dma.h"

void FlushCache(s32);
s32 sceDmaSync(s32, s32, s32);
s32 sceGsSyncPath(s32, s32);

void func_00f670c8(u32 arg0) {
    s32 ch = (s32)sceDmaGetChan(2);
    sceDmaSync(ch, 0, 0);
    PlatDmaPutGifQwc(0);
    PlatDmaPutGifTadr(PLAT_DMA_ADDR(arg0));
    PlatDmaPutStat(4);
    FlushCache(0);
    PlatDmaPutGifChcr(0x145);
    sceDmaSync(ch, 0, 0);
    sceGsSyncPath(0, 0);
}
