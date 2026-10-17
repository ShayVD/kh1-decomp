/* 34w off (12 bytes short): nostrict. Loop 1 matches; original loop 2 (h<0) uses i in t0 and four address regs (addu a2,a1,a3 / addu v0,a3,a1 / move v1,a2 / move a1,v1), 1.0f store last. Tried pointer copies, inline helper, goto loop, fallthrough second loop, swapped branches. */
#include "common.h"
void func_00135a68(f32 (*v)[4], f32 r, f32 h) {
    s32 i;
    if (0.0f <= h) {
        h = -h;
        for (i = 0; i < 8; i++) {
            v[i][0] = r * (((i & 1) << 1) - 1);
            v[i][1] = h * ((i & 2) >> 1);
            v[i][2] = r * (((i & 4) >> 1) - 1);
            v[i][3] = 1.0f;
        }
    } else {
        for (i = 0; i < 8; i++) {
            v[i][0] = r * (((i & 1) << 1) - 1);
            v[i][1] = h * ((i & 2) - 1);
            v[i][2] = r * (((i & 4) >> 1) - 1);
            v[i][3] = 1.0f;
        }
    }
}
