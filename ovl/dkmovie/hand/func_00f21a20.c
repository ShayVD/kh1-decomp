/* dkmovie.x func_00f21a20: matched by hand. */
#include "ovl.h"

void *memcpy(void *, const void *, u32);
void func_00f21998(u8 *, s16 *, s32);
void func_00f21910(void *, u8 *);

void func_00f21a20(u8 *src, u8 *w) {
    u8 *dst = *(u8 **)(w + 0x3DDAC);
    s32 i;

    for (i = 0; i < 50; i++) {
        if (src[0] == 0) {
            memcpy(dst, src + 1, 512);
            src += 513;
        } else {
            s32 len = src[1] + (src[2] << 8);
            func_00f21998(src + 3, (s16 *)dst, len);
            src = src + len + 5;
        }
        dst += 512;
    }
    func_00f21910(*(void **)(w + 0x3DDAC), w);
}
