/* The random numbers of src/util/rand.c that need -fno-strict-aliasing and
 * -fno-fill (docs/modules.md "Session 44"): func_002366d8(k, n) steps seed
 * k and returns 0 .. n-1, func_002367f8(p, n) the same on a caller's seed. */
#include "common.h"

extern s32 D_00648038[];

s32 func_002366d8(s32 i, s32 n) {
    s32 v = ((s64)D_00648038[i] * 0x41C64E6D + 12345) & 0x7FFFFFFF;
    D_00648038[i] = v;
    return ((v / 65536) * n + ((s64)(v & 0xFFFF) * n) / 65536) / 32768;
}

s32 func_002367f8(s32 *p, s32 n) {
    s32 v = ((s64)*p * 0x41C64E6D + 12345) & 0x7FFFFFFF;
    *p = v;
    return ((v / 65536) * n + ((s64)(v & 0xFFFF) * n) / 65536) / 32768;
}
