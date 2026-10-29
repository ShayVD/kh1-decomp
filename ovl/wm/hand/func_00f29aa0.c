/* wm.x func_00f29aa0: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0; u8 *x4; s32 x8, xC, x10; } Ctx29;
extern s32 D_00FBB56C;
extern f32 D_00F85180[4][4];
extern f32 D_00F87280[4][4];
void func_001bf048(OvlMtx, OvlMtx);
void sceVu0UnitMatrix(OvlMtx);
void sceVu0RotMatrixX(OvlMtx, OvlMtx, f32);
void sceVu0RotMatrix(OvlMtx, OvlMtx, OvlVec);
void sceVu0MulMatrix(OvlMtx, OvlMtx, OvlMtx);
void sceVu0CopyMatrix(OvlMtx, OvlMtx);
s32 func_00f64c10(s32);
s32 func_00f64c38(s32, s32);
s32 func_00f667b8(s32, s32, s32);
u8 *func_00f296d8(s32 *, u8 *, s32, s32);
f32 *func_00f65158(s32);
void func_00f67008(s32, s32);

s32 func_00f29aa0(s32 p, Ctx29 *c, s32 id, s32 addr, OvlVec *rot, OvlMtx mtx, f32 sc) {
    OvlMtx a;
    OvlMtx b;
    OvlMtx r;
    s32 i, j, k;
    s32 o;
    s32 t;
    f32 *d;

    func_001bf048(mtx, mtx);
    b[3][3] = sc;
    b[3][0] = 1.0f;
    b[3][1] = 1.0f;
    b[3][2] = 1.0f;
    b[0][0] = 0.0f;
    b[0][1] = 0.0f;
    b[0][2] = 0.0f;
    b[0][3] = 0.0f;
    b[1][0] = 0.0f;
    b[1][1] = 0.0f;
    b[1][2] = 0.0f;
    b[1][3] = 0.0f;
    b[2][0] = 0.0f;
    b[2][1] = 0.0f;
    b[2][2] = 0.0f;
    b[2][3] = 0.0f;
    sceVu0UnitMatrix(a);
    for (i = 2; i >= 0; i--) {
        a[i][i] = 4.0f;
    }
    for (i = 0; i < func_00f64c10(id); i++) {
        o = func_00f64c38(i, id);
        p += 2;
        sceVu0UnitMatrix(r);
        sceVu0RotMatrixX(r, r, 3.1415927f);
        sceVu0RotMatrix(r, r, rot[i]);
        t = c->x10;
        c->x8 = func_00f667b8(c->x8, addr, D_00FBB56C);
        c->xC = func_00f667b8(c->xC, addr, D_00FBB56C);
        c->x10 = func_00f667b8(c->x10, addr, D_00FBB56C);
        addr += 128;
        sceVu0MulMatrix((void *)(c->x4 + 144), D_00F85180, mtx);
        sceVu0MulMatrix((void *)(c->x4 + 144), (void *)(c->x4 + 144), a);
        sceVu0MulMatrix((void *)(c->x4 + 144), (void *)(c->x4 + 144), r);
        sceVu0CopyMatrix((void *)(c->x4 + 16), b);
        sceVu0CopyMatrix((void *)(c->x4 + 80), D_00F87280);
        c->x4 = func_00f296d8(&c->x8, c->x4, o, 0);
        c->x8 += 80;
        c->xC += 80;
        c->x10 += 80;
        d = func_00f65158(o);
        for (j = 0; j < 3; j++) {
            rot[i][j] += d[j];
            if (rot[i][j] < -3.1415927f) rot[i][j] += 6.28318505f;
            if (rot[i][j] > 3.1415927f) rot[i][j] -= 6.28318505f;
        }
        func_00f67008(p, t);
    }
    return p;
}
