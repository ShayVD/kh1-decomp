#include "common.h"

extern u32 *D_002BCC9C;

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



