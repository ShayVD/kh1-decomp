/* wm.x func_00f35e10: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; f32 v2; s32 dir; } Sub;
typedef struct { f32 m0[4][4]; f32 m1[4][4]; f32 m2[4][4]; f32 m3[16][4][4]; f32 m4[2][4][4]; Sub s; u8 pad2[0x590 - 0x558]; } W;
typedef struct { f32 f0; u8 kind; u8 pad; u16 flag; u8 e[44]; f32 sp; f32 f56; f32 f60; } K;
typedef struct { s32 w0; s32 w4; u8 pad[24]; f32 v32[4]; u8 pad2[32]; f32 v80[4]; } O;
extern W *D_00F864C0;
extern s32 D_00F8C2E0, D_00F8C2E4;
f32 *func_00f2c848(void);
s32 func_00f40c98(void);
s32 func_00f3b480(void);
O *func_00f3b460(s32);
K *func_00f3f260(s32, s32);
s32 func_00f3cb90(f32 *, f32 *, f32 *, f32 *, f32);
s32 func_00f3cdd0(f32 *, f32 *, f32 (*)[4], f32 *, f32 *, f32);
K *func_00f35a88(K *, s32);
s32 func_00f35980(f32);
void func_00f411e0(s32, s32, s32);
void func_00f41188(s32, s32, s32);
void func_00f46cb8(s32, s32);
void func_00f42818(void);

void func_00f35e10(void) {
    f32 v[4];
    f32 b1[4];
    f32 b2[2][4];
    f32 *p;
    O *o;
    K *k;
    u8 *e;
    s32 i;
    f32 t;

    p = func_00f2c848();
    v[0] = p[0];
    v[1] = p[1];
    v[2] = p[2];
    v[3] = 1.0f;
    if (func_00f40c98()) return;
    for (i = 0; i < func_00f3b480(); i++) {
        o = func_00f3b460(i);
        k = func_00f3f260(o->w4, D_00F864C0->s.id);
        if (k == NULL) continue;
        if (k->kind != 1) continue;
        if ((u16)(k->flag & 1)) continue;
        D_00F8C2E0 = 0;
        if (k->sp == 0.0f) {
            t = k->f0;
            if (D_00F864C0->s.dir == 0) {
                if (t < D_00F864C0->s.v2) continue;
                if (D_00F864C0->s.val < t) continue;
            } else {
                if (D_00F864C0->s.v2 < t) continue;
                if (t < D_00F864C0->s.val) continue;
            }
        } else if (k->flag & 0x80) {
            b1[0] = k->sp * 0.5f;
            b1[1] = k->f56 + k->f56;
            b1[2] = k->f60 * 0.5f;
            b1[3] = 1.0f;
            if (!func_00f3cb90(v, o->v80, b1, o->v32, 100.0f)) continue;
            k = func_00f35a88(k, D_00F864C0->s.dir);
        } else {
            b1[0] = k->sp * 0.5f;
            b1[1] = k->f56 * 0.5f;
            b1[2] = k->f60 * 0.5f;
            b1[3] = 1.0f;
            if (1499.0f < b1[1] && b1[1] < 1501.0f) b1[1] = 2000.0f;
            b2[0][0] = k->sp * 0.5f;
            b2[0][1] = k->f56;
            b2[0][2] = k->f60 * 0.5f;
            b2[0][3] = 1.0f;
            if (2999.0f < b2[0][1] && b2[0][1] < 3001.0f) b2[0][1] = 4000.0f;
            b2[1][0] = o->v80[0];
            b2[1][1] = o->v80[0];
            b2[1][2] = o->v80[0];
            b2[1][3] = 1.0f;
            if (!func_00f3cdd0(v, o->v80, b2, b1, o->v32, 100.0f)) continue;
        }
        for (e = k->e; e[0] != 0; e += 4) {
            switch (e[0]) {
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                if (func_00f40c98()) break;
                D_00F8C2E4 = D_00F8C2E0;
                if (func_00f35980(k->f0)) {
                    func_00f411e0(e[1], 0, e[2]);
                } else {
                    func_00f41188(e[1], 0, e[2]);
                }
                break;
            case 5:
                func_00f46cb8(e[1], 2);
                func_00f42818();
                break;
            case 6:
                break;
            }
        }
        k->flag |= 1;
    }
}
