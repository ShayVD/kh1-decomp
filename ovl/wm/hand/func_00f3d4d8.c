/* wm.x func_00f3d4d8: matched by hand. */
#include "ovl.h"

typedef struct { u8 b0; u8 pad; u16 h2; u8 pad2[14]; u8 b18; } K3d4d8;
typedef struct { u8 pad[176]; f32 a[3]; f32 b[3]; f32 f200; } T3d4d8;
typedef struct { u8 pad[28]; K3d4d8 *k; f32 m32[4][4]; u8 pad2[248 - 96]; f32 f248; u8 pad3[4]; f32 f256; T3d4d8 *t; } E3d4d8;
typedef struct { f32 *v; f32 w; s32 c; f32 (*m)[4]; s32 hit; } S3d4d8;
extern f32 D_00F8C240[4][4];
extern s32 D_00F87270;
s32 func_00f2c848(void);
f32 func_00f2c7f8(void);
E3d4d8 *func_00f3b460(s32);
s32 func_00f3b480(void);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
s32 func_00f3caf0(s32, f32, f32 *, f32);
#else
s32 func_00f3caf0(s32, f32 *, f32, f32);
static __inline__ s32 ee_00f3caf0(s32 x0, f32 x1, f32 * x2, f32 x3) { return func_00f3caf0(x0, x2, x1, x3); }
#undef func_00f3caf0
#define func_00f3caf0 ee_00f3caf0
#endif
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
s32 func_00f3cb90(s32, f32, f32 *, f32 *, f32 (*)[4]);
#else
s32 func_00f3cb90(s32, f32 *, f32 *, f32 (*)[4], f32);
static __inline__ s32 ee_00f3cb90(s32 x0, f32 x1, f32 * x2, f32 * x3, f32 (*x4)[4]) { return func_00f3cb90(x0, x2, x3, x4, x1); }
#undef func_00f3cb90
#define func_00f3cb90 ee_00f3cb90
#endif
void sceVu0ApplyMatrix(f32 *, f32 (*)[4], f32 *);
void sceVu0CopyVector(f32 *, f32 *);
s32 func_00f33a90(void);
f32 *func_00f35058(s32);
s32 func_00f650f0(s32, T3d4d8 *);
void func_0024e640(s32, s32, void *, S3d4d8 *);
void func_00f3d300(void);

s32 func_00f3d4d8(f32 *out, s32 *kind) {
    f32 v[4];
    f32 v2[4];
    S3d4d8 st;
    E3d4d8 *e;
    K3d4d8 *k;
    T3d4d8 *t;
    f32 *p;
    s32 q;
    f32 r;
    s32 i;
    s32 j;
    s32 ret;
    f32 w;

    q = func_00f2c848();
    r = func_00f2c7f8();
    for (i = 0; i < func_00f3b480(); i++) {
        e = func_00f3b460(i);
        if (e == NULL) continue;
        k = e->k;
        if (k == NULL) continue;
        if (k->b0 == 255) continue;
        *kind = k->b18;
        if (k->h2 >= 2) continue;
        if (e->f248 <= 0.0f) {
            ret = 1;
        } else {
            ret = 2;
        }
        t = e->t;
        if (!func_00f3caf0(q, r, e->m32[3], e->f256)) continue;
        if (t->f200 > 1500.0f) {
            v[0] = t->a[0];
            v[1] = t->a[1];
            v[2] = t->a[2];
            v[3] = 1.0f;
            v2[0] = t->b[0];
            v2[1] = t->b[1];
            v2[2] = t->b[2];
            v2[3] = 1.0f;
            sceVu0ApplyMatrix(v, e->m32, v);
            if (!func_00f3cb90(q, r, v, v2, e->m32)) continue;
        }
        for (j = 0; j < func_00f33a90(); j++) {
            p = func_00f35058(j);
            v[0] = p[0];
            v[1] = p[1];
            v[2] = p[2];
            v[3] = 1.0f;
            w = p[3];
            sceVu0ApplyMatrix(v, D_00F8C240, v);
            st.c = func_00f650f0(0, t);
            st.w = w;
            st.v = v;
            st.m = e->m32;
            func_0024e640(D_00F87270, 4096, func_00f3d300, &st);
            if (st.hit != 0) {
                sceVu0CopyVector(out, v);
                return ret;
            }
        }
    }
    return 0;
}
