/* dktitle.x func_00f26898: matched by hand. */
#include "ovl.h"

void FlushCache(s32);
u8 *func_00f26898(u8 *p) {
    *(kh1_u128 *)p = KH1_Q(0);
    *(u32 *)p = 0x70000000;
    p += 16;
    FlushCache(0);
    return p;
}
