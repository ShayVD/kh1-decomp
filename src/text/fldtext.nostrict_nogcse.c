/* The field's text (fldtext.c), its nostrict_nogcse part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/pieces/D_002BCC9C.h"

/* func_0010e610 (from hand/nostrict_nogcse/text_00100000_s6_01.c). */
void func_0010e610(u32 *a, u32 *b, s32 k) {
    s32 i, o;
    s32 o0, o1, o2, o3;
    k *= 16;
    o0 = k; o1 = k + 4; o2 = k + 8; o3 = k + 12;
    for (i = 0; i < 4; i++) {
        *a++ = *(u32 *)((u32)D_002BCC9C + o0);
        *a++ = *(u32 *)((u32)D_002BCC9C + o1);
        *a++ = *(u32 *)((u32)D_002BCC9C + o2);
        *a++ = *(u32 *)((u32)D_002BCC9C + o3);
    }
    o = k;
    for (i = 0; i < 4; i++) *b++ = *(u32 *)((u32)D_002BCC9C + o);
    o = k + 4;
    for (i = 0; i < 4; i++) *b++ = *(u32 *)((u32)D_002BCC9C + o);
    o = k + 8;
    for (i = 0; i < 4; i++) *b++ = *(u32 *)((u32)D_002BCC9C + o);
    k += 12;
    for (i = 0; i < 4; i++) *b++ = *(u32 *)((u32)D_002BCC9C + k);
}

