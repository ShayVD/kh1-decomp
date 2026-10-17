#include "common.h"
typedef struct { f32 v[4]; } __attribute__((aligned(8))) V4;
typedef struct { u8 b[4]; } C4;
typedef struct Ent {
    C4 c0;
    C4 c4;
    s32 x8;
    V4 a[5];
    V4 b[6];
    f32 h[4];
    struct Lk { f32 a, b; struct Ent *next; struct Ent *prev; } lk;
} Ent;
typedef struct Lk Lk;
typedef struct {
    f32 f0;
    u8 pad4[12];
    V4 v[4];
    s32 x50, x54, x58, x5c;
    f32 f60;
    u8 pad64[0xF0 - 0x64];
    Ent ent[256];
    s32 n;
    f32 fE0F4;
    Ent *first;
    Ent *last;
} Cam;
extern Cam D_0037A380;
extern s32 D_003C5500;
void *func_0011ef10(s32, void *);
void func_001c5db8(void);
void func_001c5ee8(u8 *p) {
    s32 i;
    f32 *h;
    Lk *l;
    D_0037A380.n = *(s32 *)p;
    p += 4;
    for (i = 0; i < D_0037A380.n; i++) {
        Ent *e = &D_0037A380.ent[i];
        __builtin_memcpy(&e->c0, p, 4); p += 4;
        __builtin_memcpy(&e->c4, p, 4); p += 4;
        e->x8 = *(s32 *)p; p += 4;
        __builtin_memcpy(&e->a[0], p, 16); p += 16;
        __builtin_memcpy(&e->a[1], p, 16); p += 16;
        __builtin_memcpy(&e->a[2], p, 16); p += 16;
        __builtin_memcpy(&e->a[3], p, 16); p += 16;
        __builtin_memcpy(&e->a[4], p, 16); p += 16;
        __builtin_memcpy(&e->b[0], p, 16); p += 16;
        __builtin_memcpy(&e->b[1], p, 16); p += 16;
        __builtin_memcpy(&e->b[2], p, 16); p += 16;
        __builtin_memcpy(&e->b[3], p, 16); p += 16;
        __builtin_memcpy(&e->b[4], p, 16); p += 16;
        __builtin_memcpy(&e->b[5], p, 16); p += 16;
        e->h[0] = *(f32 *)p; p += 4;
        e->h[1] = *(f32 *)p; p += 4;
        e->h[2] = *(f32 *)p; p += 4;
        e->h[3] = *(f32 *)p; p += 4;
        e->lk.a = *(f32 *)p; p += 4;
        e->lk.b = *(f32 *)p; p += 4;
        if (i == 0) {
            l = &D_0037A380.ent[0].lk;
            l->prev = 0;
            l->next = 0;
        } else {
            D_0037A380.ent[i - 1].lk.next = e;
            e->lk.next = 0;
            e->lk.prev = &D_0037A380.ent[i - 1];
        }
    }
    D_003C5500 = D_0037A380.n + 1;
    D_0037A380.first = &D_0037A380.ent[0];
    D_0037A380.last = &D_0037A380.ent[D_0037A380.n - 1];
    D_0037A380.f0 = D_0037A380.ent[0].x8;
    __builtin_memcpy(&D_0037A380.v[0], &D_0037A380.ent[0].b[0], 16);
    __builtin_memcpy(&D_0037A380.v[1], &D_0037A380.ent[0].b[1], 16);
    __builtin_memcpy(&D_0037A380.v[2], &D_0037A380.ent[0].b[2], 16);
    __builtin_memcpy(&D_0037A380.v[3], &D_0037A380.ent[0].b[5], 16);
    D_0037A380.f60 = D_0037A380.ent[0].h[2];
    D_0037A380.fE0F4 = D_0037A380.ent[0].lk.b;
    D_0037A380.x50 = 0;
    D_0037A380.x54 = 0;
    D_0037A380.x58 = 0;
    D_0037A380.x5c = 0;
    do { func_0011ef10(50000, func_001c5db8); } while (0);
}
