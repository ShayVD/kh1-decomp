#include "common.h"
typedef f32 V4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));
static inline s32 vsubflags(void *a, void *b) {
    s32 f;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2 %0, $vi17\n"
        : "=&r"(f) : "r"(a), "r"(b));
    return f;
}
