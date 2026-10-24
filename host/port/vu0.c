/* VU0 state shared by every port platform (the host build and the Vita):
 * what the game's inline VU0 asm keeps in VU0 registers across calls.
 * include/platform/vu.h's off-EE side reads and writes it. Not part of the
 * PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/vu.h"

/* the random register R (vrinit / vrxor / vrnext / vrget): a float in [1, 2) */
u32 PlatVu0R = 0x3F800000;
