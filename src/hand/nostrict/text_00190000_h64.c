/* ppp component callbacks around 0x193e00-0x1a0800 (worker 64). This
 * region was built without strict aliasing. */
#include "common.h"
#include "ppp.h"
#include "data/bss_0061.h"

typedef int u128 __attribute__((mode(TI)));
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 PppVec4[4] __attribute__((aligned(16)));

/* The current draw matrices. */

/* Models and shapes. */

/* Parameter block of func_001aaf88 (model draw). */

static inline void vu0ScaleRow(f32 *row, f32 s) {
    __asm__ volatile(
        "qmtc2 %1, $vf9\n"
        "lqc2 $vf10, 0(%0)\n"
        "vmulx.xyz $vf10xyz, $vf10xyz, $vf9x\n"
        "sqc2 $vf10, 0(%0)\n"
        : : "r"(row), "r"(s));
}

/* Hand-written VU0 routine: the asm body addresses its 16-byte work
 * buffer through $sp. */

/* Hand-written VU0 routine: the asm body addresses its 16-byte work
 * buffer through $sp. */

/* Quicksort of D_0061E310 by ->w, largest first. The second recursive
 * call is a tail call that gcc turns into a jump. */

/* needs make: uses rodata (switch jump table) */
