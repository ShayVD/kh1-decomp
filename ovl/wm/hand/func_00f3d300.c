/* wm.x func_00f3d300: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { f32 pos[3]; s32 rot[3]; f32 size[3]; s32 pad; s32 box; f32 rad; } E;
typedef struct { s32 pad; s32 n; E e[1]; } H;
typedef struct { f32 *p; f32 r; H *h; f32 (*m)[4]; s32 hit; } A;
s32 func_00f3caf0(f32 *, f32, f32 *, f32);
s32 func_00f3cb90(f32 *, f32 *, f32 *, OvlMtx, f32);

void func_00f3d300(A *arg0) {
    OvlVec pos;
    OvlVec rot;
    OvlVec size;
    OvlMtx m;
    H *h;
    E *e;
    s32 i;
    s32 *r;
    arg0->hit = 0;
    h = arg0->h;
    e = h->e;
    for (i = 0; i < h->n; i++, e++) {
        pos[0] = e->pos[0];
        pos[1] = e->pos[1];
        pos[2] = e->pos[2];
        pos[3] = 1.0f;
        PlatVu0CopyMatrix(m, arg0->m);
        PlatVu0ApplyMatrix(m[3], m, pos);
        if (h->n > 0 || e->box == 0) {
            if (func_00f3caf0(arg0->p, arg0->r, m[3], e->rad) == 0) continue;
            if (e->box == 0) goto hit;
        }
        size[0] = fabsf(e->size[0]);
        size[1] = fabsf(e->size[1]);
        size[2] = fabsf(e->size[2]);
        size[3] = 1.0f;
        r = e->rot;
        if (r[0] != 0 || r[1] != 0 || r[2] != 0) {
            rot[0] = ((f32 *)e->rot)[0];
            rot[1] = ((f32 *)e->rot)[1];
            rot[2] = ((f32 *)e->rot)[2];
            rot[3] = 1.0f;
            PlatVu0UnitMatrix(m);
            PlatVu0RotMatrix(m, m, rot);
            PlatVu0TransMatrix(m, m, pos);
            PlatVu0MulMatrix(m, arg0->m, m);
        }
        if (func_00f3cb90(arg0->p, m[3], size, m, arg0->r) == 0) continue;
    hit: /* shared hit exit */
        arg0->hit = 1;
        return;
    }
}
