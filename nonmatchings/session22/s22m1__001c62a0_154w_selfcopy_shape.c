/* 001c62a0 154w (hand/nostrict, size 1140, 8 bytes short): kept for its shape, not its count. `Cam *c` set after the guard (`c = &D; b = (u8 *)c;`), `d = &c->e.x;` (pinned t2), `while (i < c->n)`, plus a gcse self-copy in the body (`Cam *c2 = c;` after the e declaration, `c = c2;` after `b += 224;`). gcse cprop turns `c = c2` into `c = c`, so PRE can no longer hoist `c + 80`: d is `addiu t2,s1,80` inside the loop, and c s1, b s4, lk0 t8 are the original's registers. Wrong: t6 = s1+240 (original v1+240: cse2 makes c the first reg of the &D class because c lives longer than the prologue pseudo), the prologue &D is in t2 (original v1), and the hoisted HIGH keeps t9 (original spills it and rematerialises `lui s6`), which is the size gap and shifts every temp. FLAGGED (self-copy). */
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
static inline s32 *rd4(f32 *f, s32 *p) { f[0] = *(f32 *)p; p++; f[1] = *(f32 *)p; p++; f[2] = *(f32 *)p; p++; f[3] = *(f32 *)p; p++; return p; }
static inline s32 *rd1(f32 *f, s32 *p) { *f = *(f32 *)p; p++; return p; }
static inline s32 *rd2f(f32 *f, s32 *p) { f[0] = *(f32 *)p; p++; f[1] = *(f32 *)p; p++; return p; }
static inline s32 *rd2(struct Lk *l, s32 *p) { l->f4 = *(f32 *)p; p++; l->f5 = *(f32 *)p; p++; return p; }
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
static inline void inl_cpy(V4 *d, V4 *s) {
    *d = *s;
}
s32 func_001c5db8(void);
void func_0011ef10(s32, void *);
void func_001c62a0(s32 *p, f32 *add, f32 *set) {
    s32 i, j;
    Cam *c;
    u8 *b;
    D_0037A380.n = *p++;
    if (D_0037A380.n > 0) {
    c = &D_0037A380;
    b = (u8 *)c;
    i = 0;
    do {
        Ent *e = &D_0037A380.ent[i];
        Cam *c2 = c;
        D_0037A380.ent[i].c0 = *(C4 *)p; p++;
        *(C4 *)((u8 *)&D_0037A380.ent[i].v[2] - 44) = *(C4 *)p; p++;
        e->n = *p; p++;
        cpm(&D_0037A380.ent[i].v[0], p); p += 4;
        cpm(&D_0037A380.ent[i].v[1], p); p += 4;
        cpm(&D_0037A380.ent[i].v[2], p); p += 4;
        cpm(&D_0037A380.ent[i].v[3], p); p += 4;
        cpm(&D_0037A380.ent[i].v[4], p); p += 4;
        cpm(&D_0037A380.ent[i].v[5], p); p += 4;
        cpm(&D_0037A380.ent[i].v[6], p); p += 4;
        cpm(&D_0037A380.ent[i].v[7], p); p += 4;
        cpm(&D_0037A380.ent[i].v[8], p); p += 4;
        cpm(&D_0037A380.ent[i].v[9], p); p += 4;
        cpm(&e->v[10], p); p += 4;
        { register f32 *d asm("$10"); f32 *v; d = &c->e.x; v = (f32 *)(b + 336);
        for (j = 0; j < 3; j++) {
            *v++ += add[j];
            *d++ = set[j];
        } }
        {
        s32 off = i * 224 + 432;
        f32 *f = (f32 *)((u8 *)&D_0037A380 + off);
        struct Lk *l;
        p = rd1(&f[0], p);
        p = rd1(&f[1], p);
        p = rd1(&f[2], p);
        p = rd1(&f[3], p);
        { s32 o2 = i * 224 + 448; l = (struct Lk *)((u8 *)&D_0037A380 + o2); }
        p = rd1(&l->f4, p);
        p = rd1(&l->f5, p);

        if (i == 0) {
            lk_init(&D_0037A380.ent[0].lk);
        } else {
            l->prev = &D_0037A380.ent[i - 1];
            D_0037A380.ent[i - 1].lk.next = &D_0037A380.ent[i];
            l->next = 0;
        }
        }
        b += 224;
        c = c2;
        i++;
    } while (i < c->n);
    }
    D_0037A380.first = &D_0037A380.ent[0];
    D_0037A380.last = &D_0037A380.ent[D_0037A380.n - 1];
    D_0037A380.t = (f32)D_0037A380.ent[0].n;
    inl_cpy(&D_0037A380.a, (V4 *)&D_0037A380.ent[0].v[5]);
    inl_cpy(&D_0037A380.b, (V4 *)&D_0037A380.ent[0].v[6]);
    inl_cpy(&D_0037A380.c, (V4 *)&D_0037A380.ent[0].v[7]);
    inl_cpy(&D_0037A380.d, (V4 *)&D_0037A380.ent[0].v[10]);
    D_0037A380.f60 = D_0037A380.ent[0].f[2];
    D_0037A380.fE0F4 = D_0037A380.ent[0].lk.f5;
    D_003C5500 = D_0037A380.n + 1;
    func_0011ef10(50000, func_001c5db8);
    i = 0;
}
