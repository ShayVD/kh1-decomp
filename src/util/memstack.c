/* A downward memory stack (docs/modules.md "Session 48"),
 * 0x001bb438-0x001bb558: func_001bb438 starts it at the address
 * func_00113008 returns (D_0037A14C the top, D_0037A150 the current end,
 * D_0037A148 the lowest end reached); func_001bb500(n, align) takes n bytes
 * below the end,
 * aligned down, and returns them; func_001bb480 / func_001bb4b0 save and
 * restore the end on a 4-deep stack (D_00623200); func_001bb4f0 is the
 * lowest end less 0x400 bytes.  Read from the code, not proved by a boot. */
#include "common.h"
#include "data/data_0037.h"

extern s32 D_0037A148;
s32 D_00623200[0x4] ALIGNED(16);
s32 func_00113008(void);
u32 func_001bb780(u32 a, u32 b);

void func_001bb438(void) {
    s32 *p = &D_0037A14C;
    s32 v;
    D_0037A154 = 0;
    v = func_00113008();
    *p = v;
    D_0037A150 = v;
    D_0037A148 = v;
}

void func_001bb480(void) {
    D_00623200[D_0037A154] = D_0037A150;
    D_0037A154 += 1;
}

void func_001bb4b0(void) {
    s32 i;

    i = D_0037A154 - 1;
    D_0037A154 = i;
    D_0037A150 = D_00623200[i];
}

s32 func_001bb4e0(void) {
    return D_0037A150;
}

s32 func_001bb4f0(void) {
    return D_0037A148 - 0x400;
}

s32 func_001bb500(s32 n, s32 align) {
    s32 v;
    s32 e;

    e = D_0037A150 - n;
    D_0037A150 = e;
    v = func_001bb780(e, align);
    D_0037A150 = v;
    if ((u32)v < (u32)D_0037A148) {
        D_0037A148 = (u32)v;
    }
    return v;
}
