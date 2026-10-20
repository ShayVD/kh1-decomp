#include "common.h"
extern u16 D_002BB5C0[];
extern u8 D_002C4C20[];
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

extern void func_00109230(void *, void *);
/* CONTEXT_ONLY callees above: both fix reorg's beqz/beqzl choice in the two switch trees. */
CONTEXT_ONLY void func_0010c410(u8 *a) {
    u8 *p = a + 16;
    s32 n = *(s32 *)(p + 8);
    p += *(u16 *)(p + 12);
    func_00109230(p, p + n);
}
CONTEXT_ONLY void func_0010c5c8(u64 *p, s32 mode, s32 psm) {
    s32 tbp;
    switch (psm) {
    case 0x11: tbp = 0x3FEC; break;
    case 0x12: tbp = 0x3FEE; break;
    case 0x13: tbp = 0x3FF0; break;
    case 0x14: tbp = 0x3FF2; break;
    default: tbp = 0x3FDC; break;
    case 0x22: tbp = 0x3FDE; break;
    case 0x23: tbp = 0x3FE0; break;
    case 0x24: tbp = 0x3FE2; break;
    case 0x31: tbp = 0x3FE4; break;
    case 0x32: tbp = 0x3FE6; break;
    case 0x33: tbp = 0x3FE8; break;
    case 0x34: tbp = 0x3FEA; break;
    }
    switch (mode) {
    case 0: *p = (u64)tbp << 37 | 0x2000000665423600; break;
    case 1: *p = (u64)(tbp + 1) << 37 | 0x2000000665423600; break;
    case 2: *p = (u64)tbp << 37 | 0x2000000665423800; break;
    case 3: *p = (u64)(tbp + 1) << 37 | 0x2000000665423800; break;
    }
}

/* `a` is an s32 param shifted as u64: the sign extension keeps dsll out of cycle 0 in sched2. */
void func_0010c720(s32 x, s32 y, s32 id, u64 **pp, s32 arg4, s32 a, s32 w) {
    u64 *p;
    s32 row = 0, col = 0;
    s32 k, off, page;

    p = *pp;
    p[1] = ((u64)a << 24) | 0x100808080ULL;
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
#include "data/data_002B.h"
#include "data/data_002C.h"
