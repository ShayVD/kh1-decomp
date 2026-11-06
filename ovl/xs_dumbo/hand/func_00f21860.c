/* xs_dumbo.x func_00f21860: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; s32 pad[11]; } A;
typedef struct { s32 pad[4]; s16 f10; s16 pad12; s32 f14; s32 pad2[2]; } B;
typedef struct { f32 f0; s32 f4; s32 f8; } G;
void func_00105a30(s32, s16, OvlVec);
void func_00f21138(B *, OvlVec);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00f213f8(OvlVec, s32, f32);
#else
void func_00f213f8(OvlVec, f32); /* the definition never reads the s32 (a1) */
static __inline__ void ee_00f213f8(f32 *x0, s32 x1, f32 x2) { (void)x1; func_00f213f8(x0, x2); }
#undef func_00f213f8
#define func_00f213f8 ee_00f213f8
#endif
void func_00f21550(s32, s32, s32);
void func_00f216b0(A *, s32, s32);
void func_00f22b28(OvlVec, s32);
extern f32 D_00F23210;
extern f32 D_00F2BAC0;
extern f32 D_00F2BAC4;
extern G D_00F44A90;
void func_00f21860(f32 *arg0, s32 arg1) {
    OvlVec v;
    A a;
    B b;
    OvlVec c;
    s32 n, m, less;
    PlatVu0CopyVector(v, arg0);
    v[1] += D_00F2BAC0;
    func_00f213f8(v, arg1, D_00F2BAC4);
    func_00f22b28(v, arg1);
    func_00f216b0(&a, D_00F44A90.f8, D_00F44A90.f4);
    n = a.f0 + 1;
    m = D_00F44A90.f4 * D_00F23210;
    less = n < m;
    if (less) {
        m = n;
    }
    func_00f21550(D_00F44A90.f8, 0, m);
    D_00F44A90.f0 = (f32)m / (f32)D_00F44A90.f4;
    if (less) {
        func_00105a30(b.f14, b.f10, c);
        func_00f21138(&b, c);
    }
}
