/* wm.x func_00f2a1e0: matched by hand. */
#include "ovl.h"

typedef struct { u8 b0; u8 b1; u16 kind; u16 h4; u16 h6; } K2a1e0;
typedef struct { u8 pad[4]; u8 b4; u8 pad5; u16 h6; } P2a1e0;
typedef struct { s32 type; s32 f4; s32 id; u8 pad[12]; P2a1e0 *p; K2a1e0 *k; f32 m0[4][4]; f32 m1[4][4]; } E2a1e0;
extern f32 D_00F8509C;
extern s32 D_00F85098, D_00F87020;
E2a1e0 *func_00f3b460(s32);
s32 func_00f3b480(void);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void func_00f20d08(s32, f32 (*)[4], f32 (*)[4], f32);
s32 func_00f40c98(void);
f32 func_00f3b318(s32);
s32 func_00f20048(s32);
void func_00f294a0(s32, s32, s32);
s32 func_00f64c38(s32, s32);
void func_00f29dc0(s32, f32 (*)[4], f32 (*)[4], s32, f32, f32, s32);
s32 func_00f2ac10(s32);
void func_00f651c0(s32);

void func_00f2a1e0(f32 a, f32 b) {
    f32 m0[4][4];
    f32 m1[4][4];
    f32 v[4];
    E2a1e0 *e;
    K2a1e0 *k;
    s32 i;
    s32 id;
    s32 r;
    s32 t;
    f32 s;
    f32 sc;

    for (i = 0; i < func_00f3b480(); i++) {
        e = func_00f3b460(i);
        id = e->id;
        if (id < 0) continue;
        if (e == NULL) continue;
        sceVu0CopyMatrix(m0, e->m0);
        sceVu0CopyMatrix(m1, e->m1);
        if (e->f4 < 0) {
            func_00f20d08(id + 20001, m0, m1, a * D_00F8509C);
            continue;
        }
        sc = 1.0f;
        if (func_00f40c98() == 0 && e->p->b4 >= 2 && (e->p->h6 & 8)) {
            sc = 10.0f;
            e->p->h6 ^= 8;
        }
        if (e->type >= 4) continue;
        if (e->type < 2) continue;
        k = e->k;
        if (k->kind == 0) {
            s = b * func_00f3b318(i);
        } else {
            s = a * func_00f3b318(i);
        }
        if ((u16)(k->kind - 3) < 2) {
            if (D_00F85098 != 0) continue;
            func_00f20d08(id + 20001, m0, m1, s);
            continue;
        }
        if (k->b0 == 255) continue;
        if (k->b1 >= 2) {
            t = func_00f20048(k->b1 - 1);
            id += 20001;
            func_00f294a0(id, 13824, t);
        } else {
            id += 20001;
        }
        r = func_00f64c38(k->b0, D_00F87020);
        if (k->kind != 2) {
            if (k->kind == 1) {
                func_00f29dc0(id, m0, m1, r, s, sc, 2);
            } else {
                func_00f29dc0(id, m0, m1, r, s, sc, 0);
            }
        } else {
            if (k->h6 == 13) {
                func_00f651c0((func_00f2ac10(7) & 0x80) ? 3 : 1);
            }
            func_00f29dc0(id, m0, m1, r, s, sc, 1);
            func_00f651c0(-1);
        }
    }
}
