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
    f32 f50[4];
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
void func_001c62a0(u8 *p, f32 *add, f32 *set) {
    s32 i, k;
    f32 *h;
    Lk *l;
    D_0037A380.n = *(s32 *)p;
    p += 4;
    for (i = 0; i < D_0037A380.n; i++) {
        __builtin_memcpy(&D_0037A380.ent[i].c0, p, 4); p += 4;
        __builtin_memcpy(&D_0037A380.ent[i].c4, p, 4); p += 4;
        D_0037A380.ent[i].x8 = *(s32 *)p; p += 4;
        __builtin_memcpy(&D_0037A380.ent[i].a[0], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].a[1], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].a[2], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].a[3], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].a[4], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].b[0], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].b[1], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].b[2], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].b[3], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].b[4], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.ent[i].b[5], p, 16); p += 16;
        for (k = 0; k < 3; k++) {
            D_0037A380.ent[i].b[0].v[k] += add[k];
            D_0037A380.f50[k] = set[k];
        }
        h = D_0037A380.ent[i].h;
        h[0] = *(f32 *)p; p += 4;
        h[1] = *(f32 *)p; p += 4;
        h[2] = *(f32 *)p; p += 4;
        h[3] = *(f32 *)p; p += 4;
        l = &D_0037A380.ent[i].lk;
        l->a = *(f32 *)p; p += 4;
        l->b = *(f32 *)p; p += 4;
        if (i == 0) {
            l = &D_0037A380.ent[0].lk;
            l->prev = 0;
            l->next = 0;
        } else {
            l->prev = &D_0037A380.ent[i - 1];
            D_0037A380.ent[i - 1].lk.next = &D_0037A380.ent[i];
            l->next = 0;
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
    do { func_0011ef10(50000, func_001c5db8); } while (0);
}
