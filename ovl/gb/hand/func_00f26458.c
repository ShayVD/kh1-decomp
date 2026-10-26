/* gb.x func_00f26458: matched by hand. */
#include "ovl.h"

kh1_u128 *func_00f26458(kh1_u128 *d, kh1_u128 *s, s32 n) {
    s32 i;
    for (i = 0; i < n / 16; i++) *d++ = *s++;
    return d;
}
