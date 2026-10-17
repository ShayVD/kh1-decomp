/* Proposed mode sdk/gcc991111_as296: ee-gcc 2.9-991111a cc1, but assembled with the
 * ee-gcc2.96 toolchain assembler (it fills jr delay slots that 991111a gas leaves
 * empty). Every existing src/sdk/gcc991111*, libkernl file still matches 100% with
 * the 2.96 assembler, so the whole 991111 group can switch. Both functions below
 * MATCH that way (checked with checkfile + ASCC switch). */
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

int func_00259380(int c) {
    while (*(volatile int *) 0x1000F130 & 0x8000)
        ;
    *(volatile char *) 0x1000F180 = c;
    return c;
}
