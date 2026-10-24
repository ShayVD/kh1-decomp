/* GS packets, the sender (docs/modules.md "Session 45"; the rest is in
 * gspkt.c).  func_00237018(p, n, wait) makes p[0] a DMA tag for the n - 1
 * qwords after it (id end, 0x70000000), takes the GIF channel (libdma,
 * PlatDmaGetChan(2)), flushes the data cache, waits for the GS path and sends
 * p (bit 31 set for the scratchpad, 0x70000000 and up).  Platform code: the
 * Vita build replaces it (include/platform/ candidate, docs/portability.md). */
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "platform/dma.h"

typedef kh1_s128 u128;

void func_00237018(u128 *p, s32 n, s32 wait) {
    PlatDmaChan *ch;
    u32 hi = PLAT_DMA_SPR;
    n--;
    if (n > 0) {
        *p = KH1_Q(0);
        *(s32 *)p = n | 0x70000000;
        if ((u32)p < PLAT_SPR_BASE) {
            hi = 0;
        }
        ch = PlatDmaGetChan(2);
        PlatFlushCache(0);
        PlatGsSyncPath(0, 0);
        PlatDmaSend(ch, (u32)p | hi);
        if (wait) {
            do {
                PlatGsSyncPath(0, 0);
            } while (0);
        }
    }
}
