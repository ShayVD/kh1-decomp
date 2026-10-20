/* 001c62a0 35w true DP LCS (hand/nostrict, right size 1148), s23m2. Not better than s22m1 15w; kept for its shape: the prologue is exact (i = 0 as the first statement of the function) and d is `addiu t2,base,80` inside the outer loop (no hoist/remat). Levers on top of s22m1 15w: (1) `c = &D_0037A380;` BEFORE `e = &D_0037A380.ent[i];` in the body (c is then a lo_sum, not cse1 `103 - 240`, so the associate rule no longer turns d = c+80 into 103-160); (2) loop test `c->n` (c last used there, so insn d = c+80 is not the last use of a movable and force_movables does not drag it out: savings 1 life 1, not desirable); (3) `i = 0;` at the top. Left: every &D+X in the body is now c-relative (v[k] = base+304.. instead of 103+64..) and the preheader permutation (ours b s1, base t5, 103 t8, lk0 s4; orig base s1, 103 t6, lk0 t8, b s4). FLAGGED as before (c4 probe, dead i = 0 after the call, d pin). */
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
    i = 0;
    D_0037A380.n = *p++;
    if (D_0037A380.n > 0) {
    b = (u8 *)&D_0037A380;
    do {
        Ent *e;
        c = &D_0037A380;
        e = &D_0037A380.ent[i];
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
