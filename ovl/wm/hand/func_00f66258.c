/* wm.x func_00f66258: the twin of gb.x func_00f3f160 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { kh1_u128 tag; u32 w[4]; u64 d[10]; } Pk;
void func_00f66a30(u32, Pk *, s32);
void func_00f66258(s32 r, s32 g, s32 b, s32 intr) {
    Pk p;
    p.w[0] = 0x8005;
    p.w[1] = 0x10000000;
    p.w[2] = 14;
    p.w[3] = 0;
    p.d[0] = 0x30000;
    p.d[1] = 71;
    p.d[2] = 6;
    p.d[3] = 0;
    p.d[4] = r | ((u64)g << 8) | ((u64)b << 16) | 0xFF000000 | 0x3F80000000000000;
    p.d[5] = 1;
    p.d[6] = 0x174007000;
    p.d[7] = 5;
    p.d[8] = 0x18C009000;
    p.d[9] = 5;
    func_00f66a30(6, &p, intr);
}
