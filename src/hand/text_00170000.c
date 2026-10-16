/* Hand-matched functions (session 3). Grouped by address like src/auto/;
 * the original translation units are not known yet. */
#include "common.h"

extern u8 D_00575788[]; /* bit array, 8 flags per byte */

/* Returns bit `bit` of the flag array. The first two arguments are unused. */
s32 func_00171a88(s32 arg0, s32 arg1, s32 bit) {
    return ((u32) D_00575788[bit >> 3] >> (bit & 7)) & 1;
}
