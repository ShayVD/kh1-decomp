/* gb.x func_00f428e0: matched by hand. */
#include "ovl.h"

void FlushCache(s32);
extern kh1_u128 *D_00F82A88[];
void func_00f428e0(s32 i) {
    union { kh1_u128 q; u32 w[4]; } *p = (void *)D_00F82A88[i]; p->q = KH1_Q(0); p->w[0] = 0x70000000; D_00F82A88[i] = (void *)(p + 1);
    FlushCache(0);
}
