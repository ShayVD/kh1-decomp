/* wm.x func_00f621b0: the twin of gb.x func_00f3b0b8 (tools/ovl/twins.py). */
#include "ovl.h"

extern s32 D_0108EE80[][4];
void func_001bfac8(void);
void func_00f621b0(s32 i, s32 *c) {
    s32 j;
    D_0108EE80[i][3] = 128;
    for (j = 0; j < 8; j++) {
        D_0108EE80[i][0] = c[0] * j / 8;
        D_0108EE80[i][1] = c[1] * j / 8;
        D_0108EE80[i][2] = c[2] * j / 8;
        func_001bfac8();
    }
    for (j = 0; j < 8; j++) {
        D_0108EE80[i][0] = -c[0] * j / 8 + c[0];
        D_0108EE80[i][1] = -c[1] * j / 8 + c[1];
        D_0108EE80[i][2] = -c[2] * j / 8 + c[2];
        func_001bfac8();
    }
    {
        /* pinned: plain C picks $2 for this address, the original uses $3 */
        register s32 *p asm("$3") = D_0108EE80[i];
        p[3] = 0;
    }
}
