/* wm.x func_00f7b9a0: matched by hand. */
#include "ovl.h"

typedef union {
    kh1_u128 q;
    u32 w[4];
} Qw;

extern Qw *D_0108FA60;
void FlushCache(int);

/* Ends the packet with a DMA end tag (0x70000000) and flushes the cache. */
void func_00f7b9a0(void) {
    Qw *p = D_0108FA60;
    p->q = KH1_Q(0);
    p->w[0] = 0x70000000;
    D_0108FA60 = p + 1;
    FlushCache(0);
}
