/* gcc991111: 2 words off: the original puts the final dsra32 (int truncation of the u64 result) in the jr delay slot; every ee-gcc tried emits truncdisi2 as one 2-word insn, so reorg cannot split it. */
#include "common.h"
int func_002594a0(unsigned long x) {
    long e;
    e = (x << 1) >> 53;
    e -= 1075;
    if (e < -53) return 0;
    if (e >= 13) return 9999;
    x = (x << 12) >> 12; x |= 0x8000UL << 37;
    if (e < 0) {
        e = -e;
        x >>= e - 2;
        if ((x & 3) == 3) x = (x >> 2) + 1;
        else x >>= 2;
    } else
        x <<= e;
    return ((long)x << 32) >> 32;
}
