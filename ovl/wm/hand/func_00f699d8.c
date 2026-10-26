/* wm.x func_00f699d8: the twin of gb.x func_00f428e0 (tools/ovl/twins.py). */
#include "ovl.h"

void FlushCache(s32);
extern kh1_u128 *D_0108F248[];
void func_00f699d8(s32 i) {
    union { kh1_u128 q; u32 w[4]; } *p = (void *)D_0108F248[i]; p->q = KH1_Q(0); p->w[0] = 0x70000000; D_0108F248[i] = (void *)(p + 1);
    FlushCache(0);
}
