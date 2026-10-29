/* gb.x func_00f25518: matched by hand. */
#include "ovl.h"

/* wm.x func_00f25518: matched by hand. The byte at 0x5C holds two u16 bitfields (lo:4, lv:4); the u64 pad gives the struct 8-byte alignment, so gcc reads it with ld; dsrl32; andi 0xffff; andi 0xf. The two a.v stores come before the D_00F56DC0 load, because they may alias it. */
#include "ovl.h"
typedef struct {
    u64 pad[0x58 / 8];
    u32 x58;
    u16 lo : 4, lv : 4, hi : 8;
    u16 x5e;
    u8 pad60[0x88 - 0x60];
    f32 f88;
    u8 pad8c[0xA6 - 0x8C];
    u16 w;
    u16 pad2;
    u16 h;
    u8 padac[0x10D4 - 0xAC];
    s32 ry;
    s32 rx;
} W4c610;
typedef struct { f32 v[4]; } V4c610;
typedef struct { V4c610 a, b, c, d; f32 x, y, z, w; f32 rx, ry, rz, rw; } O4c610;
extern W4c610 *D_00F56DC0;

void func_00f25518(O4c610 *o) {
    W4c610 *w;

    o->a.v[0] = 0;
    o->a.v[1] = 0;
    w = D_00F56DC0;
    o->a.v[2] = w->f88;
    o->a.v[3] = 0;
    o->b.v[0] = 0;
    o->x = -(w->w * 200.0f) * 0.5f;
    o->b.v[1] = 0;
    o->b.v[2] = 1.0f;
    o->b.v[3] = 1.0f;
    o->c.v[0] = 0;
    o->c.v[1] = 1.0f;
    o->c.v[2] = 0;
    o->c.v[3] = 1.0f;
    o->d.v[0] = 0;
    o->d.v[1] = 0;
    o->d.v[2] = 0;
    o->d.v[3] = 0;
    o->y = (w->lv & 0xF) * 200.0f + 100.0f;
    o->w = 1.0f;
    o->rz = 0;
    o->z = -(w->h * 200.0f) * 0.5f;
    o->rx = w->ry * 3.1415925026f * (1.0f / 2048.0f);
    o->ry = w->rx * 3.1415925026f * (1.0f / 2048.0f);
    o->rw = 1.0f;
}
