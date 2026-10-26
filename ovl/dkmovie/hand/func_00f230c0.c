/* dkmovie.x func_00f230c0: matched by hand. */
#include "ovl.h"

void func_00f230c0(u32 p, u32 addr, s32 size) {
    u64 *tag = (u64 *)(p | 0x20000000);
    s32 chunk;
    s32 id;
    while (size > 0) {
        chunk = (size > 0xFFFF0) ? 0xFFFF0 : size;
        size -= chunk;
        id = 0;
        if (size != 0) {
            id = 3;
        }
        *tag = ((u64)addr << 32) | ((u64)id << 28) | (u32)((chunk + 15) / 16);
        addr += chunk;
        tag += 2;
    }
}
