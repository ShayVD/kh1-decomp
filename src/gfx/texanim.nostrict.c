/* Texture animations (texanim.c), its nostrict part: the flag mode's functions (the rest is
 * in the files beside it). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"

/* func_00101a70 (from hand/nostrict/text_00100000_h51.c). */
typedef struct { u8 pad0[4]; u16 dx; u16 dy; u8 pad8[8]; u64 bitblt; s32 w; u8 pad28[4]; u16 sx; u16 sy; } CopyRect;
void func_00101a70(CopyRect *r, s32 y, s32 h, u64 *pk) {
    s32 m1 = y % h;
    s32 m2 = (h - y) % h;

    pk[2] = (u64)r->sx | (u64)(r->sy + m1) << 16 | (u64)r->dx << 32 | (u64)r->dy << 48;
    pk[4] = r->w | (u64)m2 << 32;
    pk[0] = r->bitblt;
    pk[1] = 0x50;
    pk[3] = 0x51;
    pk[5] = 0x52;
    pk[6] = 2;
    pk[7] = 0x53;
    if (y != 0) {
        pk[10] = (u64)r->sx | (u64)r->sy << 16 | (u64)r->dx << 32 | (u64)(r->dy + m2) << 48;
        pk[12] = r->w | (u64)y << 32;
    } else {
        pk[10] = (u64)r->sx | (u64)(r->sy + m1) << 16 | (u64)r->dx << 32 | (u64)r->dy << 48;
        pk[12] = r->w | (u64)m2 << 32;
    }
    pk[8] = r->bitblt;
    pk[9] = 0x50;
    pk[11] = 0x51;
    pk[13] = 0x52;
    pk[14] = 2;
    pk[15] = 0x53;
}

