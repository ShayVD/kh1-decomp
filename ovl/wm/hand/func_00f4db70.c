/* wm.x func_00f4db70: matched by hand. */
#include "ovl.h"

void *func_00f4d550(void *, void *, s32);
extern u8 D_00FA5820[];

void *func_00f4db70(u8 *p, s32 x, s32 y, s32 z, s32 w, s32 h, s32 u, s32 v, s32 uw, s32 vh, u64 tex, u64 clamp) {
    void *r;

    r = func_00f4d550(p, D_00FA5820, 208);
    *(u64 *)(p + 0x20) = 342;
    *(u64 *)(p + 0x60) = clamp;
    *(u64 *)(p + 0x70) = tex;
    *(u64 *)(p + 0x90) = ((x << 4)) | ((u64)((y << 4)) << 16) | ((u64)((z << 4)) << 32);
    *(u64 *)(p + 0xB0) = ((x << 4) + (w << 4)) | ((u64)((y << 4) + (h << 4)) << 16) | ((u64)((z << 4)) << 32);
    *(u64 *)(p + 0x80) = ((u << 4)) | ((u64)((v << 4)) << 16);
    *(u64 *)(p + 0xA0) = ((u << 4) + (uw << 4)) | ((u64)((v << 4) + (vh << 4)) << 16);
    return r;
}
