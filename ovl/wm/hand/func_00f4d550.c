/* wm.x func_00f4d550: the twin of gb.x func_00f26458 (tools/ovl/twins.py). */
#include "ovl.h"

kh1_u128 *func_00f4d550(kh1_u128 *d, kh1_u128 *s, s32 n) {
    s32 i;
    for (i = 0; i < n / 16; i++) *d++ = *s++;
    return d;
}
