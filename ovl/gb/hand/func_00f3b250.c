/* gb.x func_00f3b250: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
extern s32 D_00F82640[][4];

void func_00f3b250(s32 arg0, s32 *a, s32 *b) {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_00F82640[arg0][0] = (b[0] - a[0]) * i / 10 + a[0];
        D_00F82640[arg0][1] = (b[1] - a[1]) * i / 10 + a[1];
        D_00F82640[arg0][2] = (b[2] - a[2]) * i / 10 + a[2];
        func_001bfac8();
    }
}
