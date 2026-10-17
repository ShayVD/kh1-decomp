/* func_0021b4c8: 9 words off in hand (strict; nostrict same). Global store order/register choice of the lui %hi() pairs only; control flow matches. */
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
    D_00643108 = 256;
    k = D_003F50E0[n];
    h2 = D_003F5810[n];
    h = D_003F56A0[n];
    D_006430FC = k;
    D_003F59B0 = D_003F53C0[n];
    D_003F59A4 = 0;
    D_006430F4 = n;
    D_0064310C = h;
    D_003F59B4 = 0;
    D_00643104 = h2;
    p = &D_006430F0;
    D_003F59B8 = h - 192;
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
