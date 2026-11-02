/* wm.x func_00f296d8: matched by hand. */
#include "ovl.h"

typedef struct { f32 du, dv, u, v; } Scr296d8;
typedef struct { f32 u, v, p0, p1; } UV296d8;
typedef struct {
    u8 pad[0xD0];
    s32 fD0[4];
    UV296d8 uv[16];
    u8 f1E0[16];
} Obj296d8;
typedef struct { s32 a, b, c; } Blk296d8;
Scr296d8 *func_00f650e8(s32);
void *func_00f65480(s32, Obj296d8 *, void *, Blk296d8 *, s32, s32, Blk296d8 *, f32);
extern f32 D_002BBDFC;

void *func_00f296d8(s32 arg0, Obj296d8 *obj, s32 arg2, s32 arg3) {
    Blk296d8 b0;
    Blk296d8 b1;
    Scr296d8 *s;
    Scr296d8 *p;
    s32 i;
    f32 *dt;
    s32 *d0;
    u8 *e0;
    p = func_00f650e8(arg2);
    s = p;
    d0 = obj->fD0;
    e0 = obj->f1E0;
    {
        f32 *q = &obj->uv[0].v;
        for (i = 0; i < 15; i++) {
            q[-1] = p->u;
            q[0] = p->v;
            p++;
            q += 4;
        }
    }
    dt = &D_002BBDFC;
    p = s;
    for (i = 0; i < 16; i++) {
        p->u += p->du * *dt;
        p->v += p->dv * *dt;
        if (p->u > 1.0f) {
            p->u -= 1.0f;
        }
        if (p->v > 1.0f) {
            p->v -= 1.0f;
        }
        p++;
    }
    b1.a = 0;
    b1.b = (s32)d0;
    b1.c = (s32)d0;
    b0.a = 0;
    b0.b = 0;
    b0.c = 0;
    return func_00f65480(arg0, obj, e0, &b1, arg2, arg3, &b0, 0.0f);
}
