#include "common.h"
extern volatile u32 D_002BBDF8;

/* rodata */
void func_00182270(void) {
    f32 f = (f32)D_002BBDF8 * 1.3435446;
    __asm__ volatile(
        "mfc1 $3, %0\n"
        "qmtc2 $3, $vf1\n"
        "vrinit R, $vf1x\n"
        "qmtc2 %1, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrget.x $vf1x, R\n"
        "qmfc2 $8, $vf1\n"
        :
        : "f"(f), "r"(-1)
        : "$3", "$8");
}
