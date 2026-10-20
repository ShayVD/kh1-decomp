#include "common.h"
/* func_00106000 (hand, rodata jtbl 0x48cc80: verified with rr.py). rgba inline computes w = r | 1<<32 before v; the else-branch D_002A6658 store goes through a block-local u64 *q; case 2 computes x/y after the [4]/[6] stores. */
typedef struct { s32 r, g, b; volatile s32 a; } Col;
extern Col D_002BC0B0, D_002BC070;
extern s32 D_002BC730, D_002A6208, D_002A6B80, D_002BBE04, D_002BC740, D_002BC744;
s32 D_00494A78 ALIGNED(8);
extern volatile s32 D_002BBDF8;
extern u64 D_002A6970[], D_002A68A0[], D_002A6658;
extern u8 D_002A69D0[], D_002A61E0[], D_002A6540[], D_002A6890[], D_002A6580[], D_002A6960[], D_002A65C0[];
s32 func_0010ffe0(void);
void func_00102da8(s32);
s32 func_00106b18(void *);
void func_0010ff60(s32);
void func_00105fc8(void);
s32 func_001110d0(void);
void func_0010fee8(s32, s32);
static inline u64 rgba(Col *c) { u64 w = (u64)c->r | 0x100000000; u64 v = (u64)c->b << 16 | (u64)c->g << 8; return (w | v) | ((u64)c->a << 24); }
/* rodata */
void func_00106000(s32 a) {
    func_0010ffe0();
    switch (a) {
    case 1:
    case 4:
        func_00102da8(a);
        break;
    case 0:
    default:
        D_002BC730 = 0;
        break;
    }
    if (D_002BC0B0.a != 0) {
        D_002A6970[9] = rgba(&D_002BC0B0);
        D_002A6970[10] = 0x174007000;
        D_002A6970[11] = 0x18C009000;
        func_00106b18(D_002A69D0);
    }
    if (D_002A6208 != 0) {
        func_00106b18(D_002A61E0);
    }
    switch (a) {
    case 3:
        func_0010ff60(0);
        D_002BBE04 = 0;
    case 0:
    case 1:
    case 4:
        func_00106b18(D_002A6540);
        if (D_002BC740 == 1) {
            u64 *q = &D_002A6658;
            *q = 0x100000000;
            func_00106b18(D_002A6890);
            if (D_002BC744 == 0) {
                D_00494A78 = D_002BBDF8;
            }
            if ((u32)(D_002BBDF8 - D_00494A78) > 120) {
                func_00105fc8();
            }
        } else {
            u64 *q = &D_002A6658;
            *q = rgba(&D_002BC070);
            func_00106b18(D_002A6890);
        }
        if (D_002A6B80 != 0) {
            D_002A6970[9] = 0x180FEFEFE;
            D_002A6970[10] = 0x174007000;
            D_002A6970[11] = 0x190009000;
            func_00106b18(D_002A69D0);
        }
        break;
    case 2: {
        s32 v, k, w, x, y;
        v = func_001110d0();
        func_0010fee8(v, 448);
        func_00106b18(D_002A6580);
        switch (v) {
        case 512: k = 9; break;
        case 640: k = 10; break;
        default: k = 1; break;
        }
        w = v / 64;
        D_002A68A0[4] = ((u64)w << 16) | 0x1000000;
        D_002A68A0[6] = ((u64)w << 14) | ((u64)k << 26) | 0x2008000240101180;
        x = v * 16;
        y = x + 0x7000;
        D_002A68A0[22] = (u64)(x + 8) | 0x1c080000;
        D_002A68A0[23] = (u64)y | 0xFFFFFFFE90000000;
        func_00106b18(D_002A6960);
        if (D_002A6B80 != 0) {
            D_002A6970[9] = 0x180FEFEFE;
            D_002A6970[10] = 0x174007000;
            D_002A6970[11] = (u64)y | 0x190000000;
            func_00106b18(D_002A69D0);
        }
        break;
    }
    }
    func_00106b18(D_002A65C0);
}
#include "data/data_002A.h"
#include "data/data_002B.h"
