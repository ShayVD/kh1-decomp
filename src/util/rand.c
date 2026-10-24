/* Random numbers (docs/modules.md "Session 44"), 0x00236618-0x00236a58.
 * Five seeds D_00648038[0..4] for the LCG x = x * 0x41C64E6D + 12345 (31
 * bits; func_00236618 seeds them, func_002366a8 / func_002366c0 set and read
 * one, func_002367a0 steps one, func_002368b0 steps a caller's seed;
 * rand.nostrict_nofill.c's func_002366d8(k, n) / func_002367f8(p, n) step
 * and return 0 .. n-1, src/text/textwin.c draws window styles with seed 4)
 * and five float seeds D_00648050[0..4] (func_002368f8 / func_00236910 set
 * and read one, func_00236928 steps one: (x * 69069 + 1) / 2^32).
 * rand.nofill.c's func_00236970 / func_002369e8 step a 32-bit seed and
 * return it as a float in [0, 1). */
#include "common.h"

extern s32 D_00648038[5]; /* src/data/bss_0064.c: s32 D_00648038[0x6] */
extern f32 D_00648050[5];

void func_00236618(void) {
    D_00648038[0] = 1484;
    D_00648038[1] = 12345;
    D_00648038[2] = 54321;
    D_00648038[3] = 765;
    D_00648038[4] = 9999;
    D_00648050[0] = 1.234f;
    D_00648050[1] = 2.345f;
    D_00648050[2] = 3.456f;
    D_00648050[3] = 4.567f;
    D_00648050[4] = 5.678f;
}

void func_002366a8(s32 arg0, s32 arg1) {
    D_00648038[arg0] = arg1;
}

s32 func_002366c0(s32 arg0) {
    return D_00648038[arg0];
}

void func_002367a0(s32 arg0) {
    D_00648038[arg0] = ((s64)D_00648038[arg0] * 0x41C64E6D + 12345) & 0x7FFFFFFF;
}

void func_002368b0(s32 *arg0) {
    *arg0 = ((s64)*arg0 * 0x41C64E6D + 12345) & 0x7FFFFFFF;
}

void func_002368f8(s32 arg0, f32 fparg0) {
    D_00648050[arg0] = fparg0;
}

f32 func_00236910(s32 arg0) {
    return D_00648050[arg0];
}

void func_00236928(s32 arg0) {
    f32 *p = &D_00648050[arg0];

    *p = ((*p * 69069.0f) + 1.0f) * 2.32830644e-10f;
}
