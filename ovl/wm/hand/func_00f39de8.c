/* wm.x func_00f39de8: matched by hand. */
#include "ovl.h"

typedef struct {
    f32 m[3][4];
    f32 pos[4];
    f32 dir[4];
    f32 vel[4];
    f32 m60[4][4];
    f32 ma0[4][4];
    u8 pade0[0x18];
    f32 speed;
} WmCam;
extern f32 D_002BBDEC;
void func_00f39de8(WmCam *c) {
    PlatVu0CopyMatrix(c, c->ma0);
    PlatVu0MulMatrix(c, c, c->m60);
    c->vel[0] += c->dir[0] * c->speed * D_002BBDEC;
    c->vel[1] += c->dir[1] * c->speed * D_002BBDEC;
    c->vel[2] += c->dir[2] * c->speed * D_002BBDEC;
    c->pos[0] += c->vel[0];
    c->pos[1] += c->vel[1];
    c->pos[2] += c->vel[2];
}
