#include "common.h"
#include "data/bss_0064.h"
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

/* func_0021b4c8: the 256 goes through a local (c) so its li is born before
 * the %hi of D_00643108 in sched1 (local-alloc order); order by hill-climb. */
void func_0021b4c8(s32 n) {
    s32 *p;
    s32 h, h2, k, c;
    k = D_003F50E0[n];
    D_006430F4 = n;
    c = 256;
    D_006430FC = k;
    h2 = D_003F5810[n];
    D_003F59B0 = D_003F53C0[n];
    h = D_003F56A0[n];
    D_003F59A4 = 0;
    D_00643108 = c;
    D_0064310C = h;
    p = &D_006430F0;
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
#include "data/bss_0064_mixed.h"
#include "data/data_003F.h"
