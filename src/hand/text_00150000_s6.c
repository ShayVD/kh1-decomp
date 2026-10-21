#include "common.h"

#include "data/pieces/D_00351BC8.h"
void iFlushCache(s32);
void FlushCache(s32);
s32 func_0015ea98(void);

/* Runs func_0015ea98 with the interrupt-safe cache flush installed in the
 * flush hook, then restores FlushCache and re-enables interrupts. */
s32 func_0015efc0(void)
{
    void **p = ((void **)&D_00351BC8);

    *p = iFlushCache;
    func_0015ea98();
    *p = FlushCache;
    __asm__ volatile("sync\n\tei");
    return 0;
}
