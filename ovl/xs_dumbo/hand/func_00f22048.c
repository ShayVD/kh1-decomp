/* xs_dumbo.x func_00f22048: matched by hand. */
#include "ovl.h"

typedef struct { OvlMtx m[10]; f32 ang[10]; s32 pad[2]; OvlVec in[100]; OvlVec out[100]; } Wk;
typedef struct { s64 a, b; } Q;
extern Wk D_00F2BB20;
extern Q D_00F3CA20;
extern f32 D_00F2BADC;
extern f32 D_00F2BAE4;
void *memset(void *, s32, s32);
void func_00f21ef0(OvlVec *, f32, f32, s32, s32, f32);
void func_00249420(OvlMtx, Q *);
void func_00f21a48(f32 *);
void func_00f21c60(f32 *, OvlMtx, f32 *);
void func_00f22048(void) {
    Q q;
    OvlVec b;
    OvlVec c;
    s32 i, j;
    OvlVec *p;
    OvlMtx *m;
    q = D_00F3CA20;
    memset(b, 0, 16);
    b[3] = 1.0f;
    func_00f21ef0(D_00F2BB20.in, D_00F2BAE4, D_00F2BAE4, 10, 9, D_00F2BADC * 9.0f);
    m = D_00F2BB20.m;
    for (i = 0; i < 10; i++, m++) {
        func_00249420(*m, &q);
    }
    func_00f21a48(b);
    m = D_00F2BB20.m;
    p = D_00F2BB20.in;
    for (i = 0; i < 10; i++, m++) {
        for (j = 0; j < 10; j++, p++) {
            func_00f21c60(c, *m, *p);
            PlatVu0CopyVector(*p, c);
        }
    }
}
