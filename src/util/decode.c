/* src/decode.c (its assert names the file; docs/modules.md "Session 47"),
 * 0x0024b0c8-0x0024b1f0.  A packed block: byte 0 the method, bytes 1-4 the
 * unpacked size (little-endian), then the data.  func_0024b138 unpacks one
 * through the method table D_00469FC8 (0: a copy, func_0024b0c8; 1 and 2:
 * the hand-written decoders func_0024e75c / func_0024e8d4 in
 * src/asm/text_0024e0a4.s) and returns the size; func_0024b178 returns the
 * size of a method-1 block.  func_0024b1e8 is an empty assert handler
 * (expression, file, line) that sa_task.c calls too. */
#include "common.h"

typedef s32 (*DecodeFn)(u8 *src, u8 *dst, s32 *size);

void *memcpy(void *, const void *, u32);
void func_0024b1e8(const char *, const char *, s32);
extern char D_00491878[], D_00491880[];
extern DecodeFn D_00469FC8[];

static inline s32 blk_size(u8 *b) {
    u32 lo = b[1];
    return lo + (b[4] << 0x18) + ((b[3] << 0x10) + (b[2] << 8));
}

s32 func_0024b0c8(u8 *src, u8 *dst, s32 *size) {
    s32 n = blk_size(src);
    memcpy(dst, src + 5, n);
    *size = n;
    return n;
}

s32 func_0024b138(u8 *dst, u8 *src) {
    s32 size[4];
    D_00469FC8[*src](src, dst, size);
    return size[0];
}

s32 func_0024b178(u8 *src) {
    if (src[0] != 1) {
        func_0024b1e8(D_00491878, D_00491880, 0x3F);
    }
    return blk_size(src);
}

void func_0024b1e8(const char *expr, const char *file, s32 line) {
}

s32 func_0024e75c(u8 *, u8 *, s32 *);
s32 func_0024e8d4(u8 *, u8 *, s32 *);
DecodeFn D_00469FC8[0x4] ALIGNED(8) = {
    func_0024b0c8, func_0024e75c, func_0024e8d4, 0,
};
