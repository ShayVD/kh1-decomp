/* GS packets, the sender (docs/modules.md "Session 45"; the rest is in
 * gspkt.c).  func_00237018(p, n, wait) makes p[0] a DMA tag for the n - 1
 * qwords after it (id end, 0x70000000), takes the GIF channel (libdma,
 * func_00266c08(2)), flushes the data cache, waits for the GS path and sends
 * p (bit 31 set for the scratchpad, 0x70000000 and up).  Platform code: the
 * Vita build replaces it (include/platform/ candidate, docs/portability.md). */
#include "common.h"

typedef int u128 __attribute__((mode(TI)));
s32 func_00266c08(s32);
void func_00266f38(s32, u32);
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);

void func_00237018(u128 *p, s32 n, s32 wait) {
    s32 ch;
    u32 hi = 0x80000000;
    n--;
    if (n > 0) {
        *p = 0;
        *(s32 *)p = n | 0x70000000;
        if ((u32)p < 0x70000000) {
            hi = 0;
        }
        ch = func_00266c08(2);
        FlushCache(0);
        sceGsSyncPath(0, 0);
        func_00266f38(ch, (u32)p | hi);
        if (wait) {
            do {
                sceGsSyncPath(0, 0);
            } while (0);
        }
    }
}
