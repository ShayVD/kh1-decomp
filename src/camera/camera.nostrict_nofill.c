/* The event camera: func_001c53c8, the one function of src/camera/ that
 * needs -fno-strict-aliasing and gas without delay slot filling
 * (docs/modules.md "Flags").  func_001c5168, which it calls, is in
 * camera.c.
 *
 * Interpolate the camera path (D_0037A380.scn) at time `t`: find the key
 * pair around t and set the output vectors q10..q40, x60 and xE0F4 by
 * Hermite interpolation (key mode 2) or along the keys' view directions
 * (modes 0-2 of byte 3), then apply func_001c5168.
 *
 * Match notes (session 10, r2_9, from r2_6__001c53c8_42w.c): (1) `u = (t -
 * c0) / dt;` instead of reassigning x (c0 outlives x, so cse keeps c0 in the
 * sub: FP regs exact); (2) `k = 0;` before the block-local `Elem *m =
 * e->next;` (move a3,zero first); (3) the b==2 arm writes out the q20/q30
 * memcpys + call + return instead of `goto tail` (jump2 merges them; +2 refs
 * each lifts &q20/&q30 over the loop base copy: s5/s6/s7). */
#include "common.h"
#include "camera/camera.h"
#include "data/pieces/D_0037A380.h"

typedef Vec_37A380 Vec;
typedef Elem_37A380 Elem;

void func_001e9fe8(void *dst, void *src);
void func_001e9f18(void *dst, void *a, void *b, f32 t);
f32 func_001e9e58(void *a, void *b);
void func_001e9d00(void *d, void *a, void *b, f32 t);

/* Cubic Hermite interpolation of p0 -> p1 with tangents m0, m1 over dt. */
static inline f32 herm(f32 u, f32 u2, f32 u3, f32 dt, f32 p0, f32 p1, f32 m0, f32 m1) {
    f32 h1 = 2.0f * u3 - 3.0f * u2 + 1.0f;
    f32 h2 = -2.0f * u3 + 3.0f * u2;
    f32 h3 = u3 - 2.0f * u2 + u;
    f32 h4 = u3 - u2;
    return h1 * p0 + h2 * p1 + (h3 * m0 + h4 * m1) * dt;
}

void func_001c53c8(f32 t) {
    Vec q0;
    Vec q1;
    Vec r;
    Elem *e, *n;
    s32 i, k;
    f32 c0, c1, dt, u, u2, u3;
    f32 x;
    if (t < (f32)D_0037A380.scn.first->c) return;
    if ((f32)D_0037A380.scn.last->c < t) return;
    e = D_0037A380.scn.first;
    for (i = 0; i < D_0037A380.scn.n; i++) {
        x = (f32)e->c;
        if (t == x) {
            __builtin_memcpy(&D_0037A380.scn.q10, &e->m[5], 16);
            __builtin_memcpy(&D_0037A380.scn.q20, &e->m[6], 16);
            __builtin_memcpy(&D_0037A380.scn.q30, &e->m[7], 16);
            __builtin_memcpy(&D_0037A380.scn.q40, &e->m[10], 16);
            D_0037A380.scn.x60 = e->f[2];
            D_0037A380.scn.xE0F4 = e->f[5];
            func_001c5168();
            return;
        }
        n = e->next;
        c1 = (f32)n->c;
        if (t < c1) {
            if (((s8 *)&e->b)[1] == 2) {
                c0 = x;
                dt = c1 - c0;
                u = (t - c0) / dt;
                u2 = u * u;
                u3 = u * u2;
                for (k = 0; k < 3; k++) {
                    D_0037A380.scn.q10[k] = herm(u, u2, u3, dt, e->m[5][k], n->m[5][k], e->m[4][k], n->m[3][k]);
                    D_0037A380.scn.q40[k] = herm(u, u2, u3, dt, e->m[10][k], n->m[10][k], e->m[9][k], n->m[8][k]);
                }
                D_0037A380.scn.x60 = herm(u, u2, u3, dt, e->f[2], n->f[2], e->f[1], n->f[0]);
                D_0037A380.scn.xE0F4 = herm(u, u2, u3, dt, e->f[5], n->f[5], e->f[4], n->f[3]);
                __builtin_memcpy(&D_0037A380.scn.q20, &e->m[6], 16); __builtin_memcpy(&D_0037A380.scn.q30, &e->m[7], 16); func_001c5168(); return;
            }
            switch (((s8 *)&e->b)[3]) {
            case 0:
            case 1:
                c0 = x;
                dt = c1 - c0;
                u = (t - c0) / dt;
                u2 = u * u;
                u3 = u * u2;
                func_001e9fe8(&r, &e->m[10]);
                func_001e9f18(&q0, &e->m[5], &r, e->f[2]);
                func_001e9fe8(&r, &e->next->m[10]);
                func_001e9f18(&q1, &e->next->m[5], &r, e->next->f[2]);
                k = 0; { Elem *m = e->next;
                for (; k < 3; k++) {
                    D_0037A380.scn.q10[k] = herm(u, u2, u3, dt, e->m[5][k], m->m[5][k], e->m[4][k], m->m[3][k]);
                    q0[k] = herm(u, u2, u3, dt, q0[k], q1[k], e->m[1][k], m->m[0][k]);
                }
                D_0037A380.scn.q40[2] = herm(u, u2, u3, dt, e->m[10][2], m->m[10][2], e->m[9][2], m->m[8][2]); }
                D_0037A380.scn.x60 = func_001e9e58(&q0, &D_0037A380.scn.q10);
                func_001e9d00(&D_0037A380.scn.q40, &D_0037A380.scn.q10, &q0, D_0037A380.scn.q40[2]);
                D_0037A380.scn.xE0F4 = herm(u, u2, u3, dt, e->f[5], e->next->f[5], e->f[4], e->next->f[3]);
                __builtin_memcpy(&D_0037A380.scn.q20, &e->m[6], 16);
                __builtin_memcpy(&D_0037A380.scn.q30, &e->m[7], 16);
                func_001c5168();
                return;
            case 2:
                c0 = x;
                dt = c1 - c0;
                u = (t - c0) / dt;
                u2 = u * u;
                u3 = u * u2;
                func_001e9fe8(&r, &e->m[10]);
                func_001e9f18(&q0, &e->m[5], &r, e->f[2]);
                func_001e9fe8(&r, &e->next->m[10]);
                func_001e9f18(&q1, &e->next->m[5], &r, e->next->f[2]);
                k = 0; { Elem *m = e->next;
                for (; k < 3; k++) {
                    q0[k] = herm(u, u2, u3, dt, q0[k], q1[k], e->m[1][k], m->m[0][k]);
                    D_0037A380.scn.q40[k] = herm(u, u2, u3, dt, e->m[10][k], m->m[10][k], e->m[9][k], m->m[8][k]);
                }
                D_0037A380.scn.x60 = herm(u, u2, u3, dt, e->f[2], m->f[2], e->f[1], m->f[0]);
                D_0037A380.scn.xE0F4 = herm(u, u2, u3, dt, e->f[5], m->f[5], e->f[4], m->f[3]); }
                __builtin_memcpy(&D_0037A380.scn.q20, &e->m[6], 16);
                __builtin_memcpy(&D_0037A380.scn.q30, &e->m[7], 16);
                func_001e9fe8(&r, &D_0037A380.scn.q40);
                func_001e9f18(&D_0037A380.scn.q10, &q0, &r, -D_0037A380.scn.x60);
                func_001c5168();
                return;
            }
        }
        e = e->next;
    }
}
