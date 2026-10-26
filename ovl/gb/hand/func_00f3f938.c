/* gb.x func_00f3f938: matched by hand. */
#include "ovl.h"

void *sceDmaGetChan(s32);
void sceDmaSend(void *, void *);
s32 sceGsSyncPath(s32, u16);
void FlushCache(s32);
void iFlushCache(s32);
typedef union { kh1_u128 q; u32 w[4]; } Q;
void func_00f3f938(u32 a, Q *p, s32 intr) {
    void *ch = sceDmaGetChan(2);
    p->q = KH1_Q(0);
    p->w[0] = a | 0x70000000;
    if (intr) iFlushCache(0);
    else FlushCache(0);
    sceDmaSend(ch, p);
    sceGsSyncPath(0, 0);
}
