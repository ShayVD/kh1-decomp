/* wm.x func_00f67b08: the twin of gb.x func_00f40a10 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { s32 w[0xF70 / 4]; } Big;
void FlushCache(s32);
void func_00f632e8(s32, s32, s32);
void func_001bfac8(void);
Big *func_001ba9d8(s32);
extern Big *D_0108F048;
s32 func_00f67b08(s32 a, s32 b) {
    s32 i;
    FlushCache(0);
    for (i = 1; i >= 0; i--) {
        func_00f632e8(256, 192, a + 8);
        func_001bfac8();
    }
    if (a == 0) *func_001ba9d8(b) = *D_0108F048;
    return 1;
}
