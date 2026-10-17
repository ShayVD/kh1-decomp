/* func_00259380 (SIO putc), sdk/libkernl (ee-gcc 2.9-991111a). 2 words off with the
 * 991111a assembler: the volatile sb is not moved into the jr delay slot. The
 * 991111a cc1 output below assembled with the ee-gcc2.96 assembler (ee-as of the
 * 2.96 toolchain) matches all 14 words exactly: needs a build mode "991111a cc1 +
 * 2.96 gas". */
#include "common.h"
int func_00259380(int c) {
    while (*(volatile int *) 0x1000F130 & 0x8000)
        ;
    *(volatile char *) 0x1000F180 = c;
    return c;
}
