/* func_0010c720: 26 words off (same size, was 217w), mode hand. Levers: (1) the screen/texture coordinates go through inline helpers that reassign their params (xyz: x = x*16 + 0x7000, uv: x = x*16 + 8 called with col*24 / col*24+24); combine leaves two identical shifts that reload-cse turns into `move` + in-place addiu, as in the original; (2) `*pp = p + 6; return;` at the end of the id >= 10000 branch too (jump2 merges the copies after sched2, which keeps the epilogue order). Still off: prologue sched2 order (dsll t1 = a<<24 scheduled first, li 0x100808080 chain one slot early) and the reorg beqz/beqzl choice in both switch decision trees (k>9 -> default is likely in the original, page>=2 is not). flagsweep: nothing better. */
#include "common.h"
extern u16 D_002BB5C0[];
extern u8 D_002C4C20[];
extern void func_0010c410(void *);
extern void func_0010c5c8(u64 *, s32, s32);
#define ZF 0xFFFFFFFE00000000ULL

static inline u64 xyz(s32 x, s32 y) {
    x = x * 16 + 0x7000;
    y = y * 16 + 0x7400;
    return (u64)x | ((u64)y << 16) | 0xFFFFFFFE00000000;
}

static inline u64 xyz8(s32 x, s32 y) {
    x = x * 16 + 0x7008;
    y = y * 16 + 0x7408;
    return (u64)x | ((u64)y << 16) | 0xFFFFFFFE00000000;
}

static inline u64 uv(s32 x, s32 y) {
    x = x * 16 + 8;
    y = y * 16 + 8;
    return (u64)x | ((u64)y << 16);
}

void func_0010c720(s32 x, s32 y, s32 id, u64 **pp, s32 arg4, u64 a, s32 w) {
    u64 *p;
    s32 row = 0, col = 0;
    s32 k, off, page, sx, sy, n;

    p = *pp;
    p[1] = (a << 24) | 0x100808080ULL;
    if (id >= 10000) {
        k = id - 10000;
        p[0] = 0x2007FE85E1B11800ULL;
        p[2] = D_002BB5C0[k * 4 + 0] | ((u64)D_002BB5C0[k * 4 + 1] << 16);
        p[4] = D_002BB5C0[k * 4 + 2] | ((u64)D_002BB5C0[k * 4 + 3] << 16);
        switch (k) {
        case 4:
            off = (w == 20) ? -6 : -4;
            p[3] = xyz(x, y + off);
            p[5] = xyz(x + 0x28, y + off + 0x20);
            break;
        case 5:
            off = (w == 20) ? -10 : -8;
            p[3] = xyz(x, y + off);
            p[5] = xyz(x + 0x28, y + off + 0x28);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            func_0010c410(D_002C4C20);
            p[0] = 0x20078005DD413A00ULL;
            off = (w == 20) ? -2 : 0;
            p[2] = D_002BB5C0[k * 4 + 0] | ((u64)D_002BB5C0[k * 4 + 1] << 16);
            p[4] = D_002BB5C0[k * 4 + 2] | ((u64)D_002BB5C0[k * 4 + 3] << 16);
            p[3] = xyz8(x, y + off);
            p[5] = xyz8(x + 0x20, y + off + 0x15);
            break;
        default:
            off = (w == 20) ? -2 : 0;
            p[3] = xyz(x, y + off);
            p[5] = xyz(x + 0x18, y + off + 0x18);
            break;
        }
        *pp = p + 6;
        return;
    } else {
        page = id / 441;
        switch (page) {
        case 0:
            k = id;
            col = k % 21;
            row = k / 21;
            break;
        case 1:
            k = id - 441;
            col = k % 21;
            row = k / 21;
            break;
        case 2:
            k = id - 882;
            col = k % 21;
            row = k / 21;
            break;
        case 3:
            k = id - 1323;
            col = k % 21;
            row = k / 21;
            break;
        }
        func_0010c5c8(p, page, arg4);
        if (id == 9999) {
            p[2] = 0;
            p[4] = 0;
            p[3] = 0xFFFFFFFE73C06FC0ULL;
            p[5] = 0xFFFFFFFE73C06FC0ULL;
        } else {
            p[2] = uv(col * 24, row * 24);
            p[4] = uv(col * 24 + 24, row * 24 + 24);
            p[3] = xyz(x, y);
            p[5] = xyz(x + w, y + w);
        }
    }
    *pp = p + 6;
}
