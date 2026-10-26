/* xs_dumbo.x func_00f229c8: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0, f4, f8, fC; OvlMtx m[10]; f32 ang[10]; } Wk;
extern Wk D_00F2BB10;
void *memset(void *, s32, s32);
void func_00f22048(void);
void func_00249420(OvlMtx, s32);
void func_00f21a48(s32);
s32 func_00249da0(s32);
void func_00f22178(void *, s32, f32, f32, f32);
void func_00237660(void *, void *, s32);
extern f32 D_00F2BAF8;
extern f32 D_00F2BAFC;
extern f32 D_00F2BB00;
extern f32 D_00F2BB04;
extern u8 D_00F2CA50[];
extern s32 D_00F3C1D0;
extern s32 D_00F3C1D8;
void func_00f229c8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 i;
    s32 a, b;
    f32 *pa;
    OvlMtx *pm;
    memset(&D_00F2BB10, 0, 0x106C0);
    D_00F2BB10.f8 = arg4;
    D_00F2BB10.fC = arg5;
    D_00F2BB10.f0 = arg2;
    D_00F2BB10.f4 = arg3;
    func_00f22048();
    pm = D_00F2BB10.m;
    pa = D_00F2BB10.ang;
    for (i = 0; i < 10; i++) {
        func_00249420(*pm++, arg1);
        *pa++ = 1.0f;
    }
    func_00f21a48(arg0);
    a = func_00249da0(arg2);
    b = func_00249da0(arg3);
    func_00f22178(D_00F2CA50, a, 1.0f, D_00F2BAF8, D_00F2BAFC);
    func_00f22178(D_00F2CA50 + 0x7BC0, b, 1.0f, D_00F2BB00, D_00F2BB04);
    func_00237660(&D_00F3C1D0, &D_00F3C1D8, 8);
}
