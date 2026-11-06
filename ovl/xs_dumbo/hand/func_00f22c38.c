/* xs_dumbo.x func_00f22c38: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xB0]; } Tri;
typedef struct { s32 tex0; s32 tex1; s32 f8; s32 fc; u8 pad10[0xF40 - 0x10]; Tri g1[180]; u8 pad[0x8B00 - 0xF40 - 180 * 0xB0]; Tri g2[180]; } Pool;
typedef struct { u8 pad[0x60]; u64 tag; u8 pad68[0x160 - 0x68]; } Pkt;
void func_00249a48(s32, s32);
void func_002370c8(Pkt *);
void func_00237018(Pkt *, s32, s32);
f32 fmodf(f32, f32);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00f222f8(Tri *, f32, f32, f32, s32, f32);
#else
void func_00f222f8(Tri *, s32, f32, f32, f32, f32);
static __inline__ void ee_00f222f8(Tri *x0, f32 x1, f32 x2, f32 x3, s32 x4, f32 x5) { func_00f222f8(x0, x4, x1, x2, x3, x5); }
#undef func_00f222f8
#define func_00f222f8 ee_00f222f8
#endif
void func_00237600(void *);
void func_002376c8(void *, Tri *, void *);
void func_00238258(void *, s32, s32, s32, void *);
extern f32 D_00F2BAE8;
extern f32 D_00F2BAEC;
extern f32 D_00F2BAF0;
extern f32 D_00F2BAF4;
extern Pool D_00F2BB10;
extern u8 D_00F3C1D0[];
extern u8 D_002E26C0[];
void func_00f22c38(f32 a, f32 b) {
    Pkt pk;
    f32 step = 0.11111111f;
    f32 r;
    s32 rows;
    s32 i, j;
    Tri *t;

    func_00249a48(D_00F2BB10.tex0, 1);
    func_00249a48(D_00F2BB10.tex1, 1);
    func_002370c8(&pk);
    pk.tag = 0x51001;
    func_00237018(&pk, 22, 1);
    r = fmodf(b, step);
    rows = b * 9.0f;
    step = r / step;
    if (0.0f < r && rows != 9)
        rows++;
    t = D_00F2BB10.g1;
    func_00f222f8(t, D_00F2BAE8, D_00F2BAEC, a, rows, step);
    func_00237600(D_00F3C1D0);
    for (i = 0; i < rows; i++)
        for (j = 0; j < 20; j++)
            func_002376c8(D_00F3C1D0, t++, D_002E26C0);
    func_00238258(D_00F3C1D0, 180, D_00F2BB10.f8, D_00F2BB10.fc, D_002E26C0);
    t = D_00F2BB10.g2;
    func_00f222f8(t, D_00F2BAF0, D_00F2BAF4, a, rows, step);
    func_00237600(D_00F3C1D0);
    for (i = 0; i < rows; i++)
        for (j = 0; j < 20; j++)
            func_002376c8(D_00F3C1D0, t++, D_002E26C0);
    func_00238258(D_00F3C1D0, 180, D_00F2BB10.f8, D_00F2BB10.fc, D_002E26C0);
}
