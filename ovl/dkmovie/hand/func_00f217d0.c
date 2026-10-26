/* dkmovie.x func_00f217d0: matched by hand. */
#include "ovl.h"

void *memcpy(void *, const void *, u32);
#define IDX (*(s32 *)(w + 0x3DDA4))

void func_00f217d0(void *src, u8 *w) {
    s32 w8 = (s32)(w + 8);
    if (*(s8 *)(IDX + w8 + 0x3DF60) != 0) {
        return;
    }
    memcpy(*(void **)(w + IDX * 4 + 0x3DD94), src, 0x6400);
    *(s8 *)(IDX + w8 + 0x3DF60) = 1;
    IDX = (IDX + 1) % 4;
}
