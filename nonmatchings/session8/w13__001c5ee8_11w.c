/* func_001c5ee8 11w (hand, 952 = right size; was 67w/48 lcs). New: D_003C5500 = *(s32 *)&D_0037A380.ent[256] + 1 (a second read of n through a different address expression: cse1 keeps it separate, reload_cse turns it into the original's move t0,a0 + addiu t0,t0,1); the tail V4 copies through union { f32 f[4]; Ent *p[4]; } so the sd stores conflict with t/first/last (dep counts tie, LUID decides); tail order re-annealed. Left: loop-init global-alloc order only (orig lk base B+448 gets a3 first; ours B copy 104 and i*224 376 [7 refs/136, .1029] beat lk 233 [5 refs/132, .0758]); needs lk >= 7 refs or B/i224 <= 5. -fno-expensive-optimizations gives 7w (B right, lk/i224 swapped). */
#include "common.h"
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
void *memcpy(void *, const void *, u32);
typedef struct { u8 b[4]; } C4;
typedef struct { u8 b[16]; } B16;
typedef struct Ent {
    C4 c0;
    C4 c4;
    s32 n;
    u8 padc[4];
    B16 v[11];
    f32 f[4];
    struct Lk { f32 f4, f5; struct Ent *next; struct Ent *prev; } lk;
} Ent;
static inline void cp16(B16 *d, B16 *s) {
    *d = *s;
}
static inline void cpm(void *d, void *s) {
    memcpy(d, s, 16);
}
static inline void lk_init(struct Lk *l) {
    l->prev = 0;
    l->next = 0;
}
typedef struct {
    f32 t;
    u8 pad4[0xc];
    V4 a;
    V4 b;
    V4 c;
    V4 d;
    V4 e;
    f32 f60;
    u8 pad64[0xF0 - 0x64];
    Ent ent[256];
    u8 padx[0xE0F0 - 0xF0 - 256 * 224];
    s32 n;
    f32 fE0F4;
    Ent *first;
    Ent *last;
} Cam;
extern Cam D_0037A380;
extern s32 D_003C5500;
typedef union { f32 f[4]; Ent *p[4]; } __attribute__((aligned(16))) A16;
static inline void inl_cpy(V4 *d, V4 *s) {
    *(A16 *)d = *(A16 *)s;
}
s32 func_001c5db8(void);
void func_0011ef10(s32, void *);
void func_001c5ee8(s32 *p) {
    s32 i;
    D_0037A380.n = *p++;
    for (i = 0; i < D_0037A380.n; i++) {
        Ent *e = &D_0037A380.ent[i];
        e->c0 = *(C4 *)p; p++;
        e->c4 = *(C4 *)p; p++;
        D_0037A380.ent[i].n = *p; p++;
        cpm(&D_0037A380.ent[i].v[0], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[1], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[2], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[3], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[4], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[5], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[6], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[7], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[8], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[9], (B16 *)p); p += 4;
        cpm(&D_0037A380.ent[i].v[10], (B16 *)p); p += 4;
        e->f[0] = *(f32 *)p; p++;
        e->f[1] = *(f32 *)p; p++;
        e->f[2] = *(f32 *)p; p++;
        D_0037A380.ent[i].f[3] = *(f32 *)p; p++;
        e->lk.f4 = *(f32 *)p; p++;
        e->lk.f5 = *(f32 *)p; p++;
        if (i == 0) {
            lk_init(&D_0037A380.ent[i].lk);
        } else {
            D_0037A380.ent[i - 1].lk.next = &D_0037A380.ent[i];
            D_0037A380.ent[i].lk.next = 0;
            e->lk.prev = &D_0037A380.ent[i - 1];
        }
    }
/*P*/
    D_0037A380.e.x = 0;
    D_0037A380.e.y = 0;
    D_0037A380.first = &D_0037A380.ent[0];
    D_0037A380.last = &D_0037A380.ent[D_0037A380.n - 1];
    D_0037A380.t = (f32)D_0037A380.ent[0].n;
    inl_cpy(&D_0037A380.a, (V4 *)&D_0037A380.ent[0].v[5]);
    D_0037A380.e.z = 0;
    inl_cpy(&D_0037A380.b, (V4 *)&D_0037A380.ent[0].v[6]);
    inl_cpy(&D_0037A380.c, (V4 *)&D_0037A380.ent[0].v[7]);
    inl_cpy(&D_0037A380.d, (V4 *)&D_0037A380.ent[0].v[10]);
    D_0037A380.f60 = D_0037A380.ent[0].f[2];
    D_0037A380.e.w = 0;
    D_0037A380.fE0F4 = D_0037A380.ent[0].lk.f5;
    D_003C5500 = *(s32 *)&D_0037A380.ent[256] + 1;
/*Q*/
    func_0011ef10(50000, func_001c5db8);
    i = 0;
}
