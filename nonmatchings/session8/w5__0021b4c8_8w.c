/* 0021b4c8 8w, mode hand (strict), no context. Statement order found by hill-climb (was 9w). Off: local-alloc register numbers of the h-192 temp and two %hi() luis (t5/a3/t3 vs t3/a1...), and the x30FC/x59A4 store pair order. One basic block, ~16 quantities: local-alloc order follows sched1 lifetimes. */
#include "common.h"
extern s32 D_003F50E0[];
extern f32 D_003F53C0[];
extern u16 D_003F56A0[];
extern u16 D_003F5810[];
extern s32 D_003F59A4;
extern f32 D_003F59B0;
extern s32 D_003F59B4;
extern s32 D_003F59B8;
extern s32 D_006430F0;
extern s32 D_006430F4;
extern s32 D_006430F8;
extern s32 D_006430FC;
extern s32 D_00643100;
extern s32 D_00643104;
extern s32 D_00643108;
extern s32 D_0064310C;
extern s32 D_003F3504;

void func_0021b4c8(s32 n) {
    s32 *p;
    s32 h, h2, k;
    D_006430F4 = n;
    D_003F59A4 = 0;
    k = D_003F50E0[n];
    D_006430FC = k;
    h2 = D_003F5810[n];
    D_003F59B0 = D_003F53C0[n];
    h = D_003F56A0[n];
    D_00643108 = 256;
    p = &D_006430F0;
    D_0064310C = h;
    D_003F59B4 = 0;
    D_003F59B8 = h - 192;
    D_00643104 = h2;
    if (*p == 0) {
        *p = 1;
        D_006430F8 = -1;
        D_00643100 = 0;
        D_003F3504 = 0;
    } else if (*p == 4 && D_006430F8 != k) {
        *p = 1;
        D_00643100 = 0;
        D_003F3504 = 0;
    }
}
