/* xs_dh_break.x func_00f20080: matched by hand. */
#include "ovl.h"

u64 *func_0011fb38(s32, u64, u64 *);
void func_0011fb78(u64 *, s32, u64 *);
extern u64 D_00FA2000[];
void func_00f20080(void) {
    u64 *p = D_00FA2000;
    u64 *base = p;
    p += 2;
    p[0] = 0x1000000000008003;
    p[1] = 0xE;
    p = func_0011fb38(0x47, 0x4000C, p + 2);
    p = func_0011fb38(6, 0x2000000264120000, p);
    p = func_0011fb38(0x14, 0x61, p);
    p = func_0011fb38(0x3F, 0, p);
    func_0011fb78(base, 7, p);
}
