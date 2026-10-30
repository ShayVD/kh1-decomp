/* wm.x func_00f2a4c0: matched by hand. */
#include "ovl.h"

typedef struct { s32 r; s32 g; s32 pad; s32 b; } C2a4c0;
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void sceVu0RotTransPers(s32 *, f32 (*)[4], f32 *, s32);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
s32 func_00f66ae0(u64 *);
void func_00f66f78(s32, s32);
extern u64 **D_00F85160;
extern f32 D_00F85200[4][4];
extern f32 D_00F85180[4][4];

static inline u64 *put2a4c0(u64 *p, u64 a, u64 b) {
    p[0] = a;
    p[1] = b;
    return p + 2;
}

void func_00f2a4c0(s32 id, C2a4c0 *c, f32 (*m)[4]) {
    f32 v[3][4];
    s32 out[3][4];
    s32 s[3][4];
    u64 **pp = D_00F85160;
    u64 *p;
    s32 k;

    sceVu0MulMatrix(m, D_00F85200, m);
    if (m[3][2] < 0.01f) {
        return;
    }
    k = 71;
    v[0][0] = 0.0f;
    v[0][1] = -100.0f;
    v[0][2] = 0.0f;
    v[0][3] = 1.0f;
    v[1][0] = -100.0f;
    v[1][1] = 100.0f;
    v[1][2] = 0.0f;
    v[1][3] = 1.0f;
    v[2][0] = 100.0f;
    v[2][1] = 100.0f;
    v[2][2] = 0.0f;
    v[2][3] = 1.0f;
    sceVu0MulMatrix(m, D_00F85180, m);
    sceVu0RotTransPers(out[0], m, v[0], 0);
    sceVu0RotTransPers(out[1], m, v[1], 0);
    sceVu0RotTransPers(out[2], m, v[2], 0);
    s[0][0] = out[0][0];
    s[0][1] = out[0][1];
    s[1][0] = out[1][0];
    s[1][1] = out[1][1];
    s[2][0] = out[2][0];
    s[2][1] = out[2][1];
    *pp = func_00f66ac8(*pp);
    p = func_00f66b78(*pp);
    put2a4c0(p + 0, 0, k);
    put2a4c0(p + 2, 3, 0);
    put2a4c0(p + 4, (u64)c->r | ((u64)c->g << 8) | ((u64)c->b << 16) | 0x3F80000000000000LL, 1);
    put2a4c0(p + 6, (u64)s[0][0] | ((u64)s[0][1] << 16), 5);
    put2a4c0(p + 8, (u64)s[1][0] | ((u64)s[1][1] << 16), 5);
    put2a4c0(p + 10, (u64)s[2][0] | ((u64)s[2][1] << 16), 5);
    put2a4c0(p + 12, 0x5000D, k);
    *pp = p + 14;
    func_00f66b90(p + 14);
    func_00f66f78(id, func_00f66ae0(*pp));
}
