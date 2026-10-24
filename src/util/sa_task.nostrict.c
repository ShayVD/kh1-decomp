/* src/sa_task.c (docs/modules.md "Session 47"): the reset, built with
 * -fno-strict-aliasing: no task in any of the eight slots. */
#include "common.h"

extern s32 D_00669A18[8];

void func_0024b1f0(void) {
    s32 i;
    for (i = 0; i < 8; i++) D_00669A18[i] = 0;
}
