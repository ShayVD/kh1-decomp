/* func_0010c720: 217w off (struct 70, same size), mode hand (strict). Logic complete; differences are mostly callee-saved register allocation (orig x->s2, row/col->s3/s4 shared with table ptrs e3/e0, w->s5; here row->s2, x->s5) which cascades, plus cross-jump splits (orig: cases 4/5 share a tail with stores; div-tail of case 0 shared). Declaration order, helper inlines, mode changes tried without effect. */
#include "common.h"
extern u16 D_002BB5C0[];
extern u8 D_002C4C20[];
extern void func_0010c410(void *);
extern void func_0010c5c8(u64 *, s32, s32);
#define ZF 0xFFFFFFFE00000000ULL

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
            sx = x * 16;
            sy = (y + off) * 16;
            p[3] = (sx + 0x7000) | ((u64)(sy + 0x7400) << 16) | ZF;
            p[5] = (sx + 0x7280) | ((u64)(sy + 0x7600) << 16) | ZF;
            break;
        case 5:
            off = (w == 20) ? -10 : -8;
            sx = x * 16;
            sy = (y + off) * 16;
            p[3] = (sx + 0x7000) | ((u64)(sy + 0x7400) << 16) | ZF;
            p[5] = (sx + 0x7280) | ((u64)(sy + 0x7680) << 16) | ZF;
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            func_0010c410(D_002C4C20);
            p[0] = 0x20078005DD413A00ULL;
            off = (w == 20) ? -2 : 0;
            sx = x * 16;
            sy = (y + off) * 16;
            p[2] = D_002BB5C0[k * 4 + 0] | ((u64)D_002BB5C0[k * 4 + 1] << 16);
            p[4] = D_002BB5C0[k * 4 + 2] | ((u64)D_002BB5C0[k * 4 + 3] << 16);
            p[3] = (sx + 0x7008) | ((u64)(sy + 0x7408) << 16) | ZF;
            p[5] = (sx + 0x7208) | ((u64)(sy + 0x7558) << 16) | ZF;
            break;
        default:
            off = (w == 20) ? -2 : 0;
            sx = x * 16;
            sy = (y + off) * 16;
            p[3] = (sx + 0x7000) | ((u64)(sy + 0x7400) << 16) | ZF;
            p[5] = (sx + 0x7180) | ((u64)(sy + 0x7580) << 16) | ZF;
            break;
        }
    } else {
        page = id / 441;
        switch (page) {
        case 0:
            n = id;
            row = n / 21;
            col = n % 21;
            break;
        case 1:
            n = id - 441;
            row = n / 21;
            col = n % 21;
            break;
        case 2:
            n = id - 882;
            row = n / 21;
            col = n % 21;
            break;
        case 3:
            n = id - 1323;
            row = n / 21;
            col = n % 21;
            break;
        }
        func_0010c5c8(p, page, arg4);
        if (id == 9999) {
            p[2] = 0;
            p[3] = 0xFFFFFFFE73C06FC0ULL;
            p[4] = 0;
            p[5] = 0xFFFFFFFE73C06FC0ULL;
        } else {
            p[2] = (col * 384 + 8) | ((u64)(row * 384 + 8) << 16);
            p[4] = (col * 384 + 392) | ((u64)(row * 384 + 392) << 16);
            p[3] = (x * 16 + 0x7000) | ((u64)(y * 16 + 0x7400) << 16) | ZF;
            p[5] = ((x + w) * 16 + 0x7000) | ((u64)((y + w) * 16 + 0x7400) << 16) | ZF;
        }
    }
    *pp = p + 6;
}
