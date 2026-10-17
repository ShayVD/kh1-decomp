#include "common.h"

typedef int u128 __attribute__((mode(TI)));
s32 func_00266c08(s32);
void func_00266f38(s32, u32);
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);

void func_00237018(u128 *p, s32 n, s32 wait) {
    s32 ch;
    u32 hi = 0x80000000;
    n--;
    if (n > 0) {
        *p = 0;
        *(s32 *)p = n | 0x70000000;
        if ((u32)p < 0x70000000) {
            hi = 0;
        }
        ch = func_00266c08(2);
        FlushCache(0);
        sceGsSyncPath(0, 0);
        func_00266f38(ch, (u32)p | hi);
        if (wait) {
            do {
                sceGsSyncPath(0, 0);
            } while (0);
        }
    }
}
