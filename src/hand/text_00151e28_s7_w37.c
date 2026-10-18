#include "common.h"

typedef struct { u8 pad[0x4c]; u16 x4c; } C130g;
typedef struct {
    u32 x0;
    u8 pad4[0x10 - 4];
    f32 pos[4];
    u8 pad20[0x30 - 0x20];
    f32 x30;
    u8 pad34[4];
    f32 x38;
    u8 pad3c[0x70 - 0x3c];
    s32 x70;
    u8 pad74[0x98 - 0x74];
    s32 x98;
    u8 pad9c[0x130 - 0x9c];
    C130g *x130;
} Tg;
typedef struct { u8 pad[8]; Tg *x8; u8 padc[4]; f32 pos[4]; } Og;
void func_00267530(f32 *, f32 *, f32 *);
f32 fabsf(f32);

s32 func_00151e28(Og *o) {
    f32 d[4];
    Tg *t = o->x8;
    f32 x;
    f32 lim;

    if (!t || t->x98 || t->x70 || t->x130->x4c || (t->x0 & 4)) return 0;
    func_00267530(d, o->pos, t->pos);
    lim = 10.0f;
    if (fabsf(d[1]) > lim) return 0;
    lim = 25.0f;
    x = d[0];
    if (fabsf(x) < lim) {
        f32 n = o->x8->x38;
        if (0.94f < n && 0.0f < d[2]) goto r1;
        if (!(n < -0.94f)) return 0;
        if (!(d[2] < 0.0f)) goto r0;
        return 1;
    } else if (fabsf(d[2]) < lim) {
        f32 n = o->x8->x30;
        if (0.94f < n && 0.0f < x) goto r1;
        if (!(n < -0.94f)) return 0;
        if (!(x < 0.0f)) goto r0;
        return 1;
    }
    return 0;
r1:
    return 1;
r0:
    return 0;
}
