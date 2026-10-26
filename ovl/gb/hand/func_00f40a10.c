/* gb.x func_00f40a10: matched by hand. */
#include "ovl.h"

typedef struct { s32 w[0xF70 / 4]; } Big;
void FlushCache(s32);
void func_00f3c1f0(s32, s32, s32);
void func_001bfac8(void);
Big *func_001ba9d8(s32);
extern Big *D_00F82888;
s32 func_00f40a10(s32 a, s32 b) {
    s32 i;
    FlushCache(0);
    for (i = 1; i >= 0; i--) {
        func_00f3c1f0(256, 192, a + 8);
        func_001bfac8();
    }
    if (a == 0) *func_001ba9d8(b) = *D_00F82888;
    return 1;
}
