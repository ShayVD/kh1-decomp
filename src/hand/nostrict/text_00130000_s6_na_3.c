#include "common.h"

typedef struct { f32 x, y, z, w; } V4f;
typedef struct { u8 pad[0x4c]; u16 x4c; } T5i;
typedef struct {
    u32 flags;
    u8 pad4[0x50 - 4];
    V4f x50;
    u8 pad60[0x70 - 0x60];
    s32 x70;
    u8 pad74[0x88 - 0x74];
    u32 x88;
    u8 pad8c[0x130 - 0x8c];
    T5i *info;
} T5o;
void func_001315c0(T5o *o, s32 k, void *buf, f32 f);
void func_00267530(V4f *, V4f *, V4f *);
s32 func_0013c968(s32, s32);
f32 func_00267390(V4f *, V4f *);
s32 func_001453a8(T5o *o, V4f *p, s32 mode) {
    V4f t;
    f32 lim;
    s32 n;
    if (!(o->flags & 0x8000) || (o->x88 & 0x20)) return 0;
    switch (mode) {
    case 1:
        func_001315c0(o, 0x8003, &t, 0.0f);
        func_00267530(&t, &t, p);
        lim = 14400.0f;
        break;
    case 2:
        func_001315c0(o, 0x8003, &t, 0.0f);
        func_00267530(&t, &t, p);
        lim = 40000.0f;
        break;
    case 0:
    default:
        func_00267530(&t, p, &o->x50);
        t.y = fabsf(t.y);
        if (o->x70 == 33) t.y -= 50.0f;
        if (t.y > 30.0f) return 0;
        t.y = 0;
        lim = 6400.0f;
        break;
    }
    n = func_0013c968(5, o->info->x4c);
    if (n > 0) {
        lim = 40000.0f;
        if (n != 1) lim = 160000.0f;
    }
    if (lim < func_00267390(&t, &t)) return 0;
    return 1;
}
