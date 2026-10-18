/* func_001c62a0 120 LCS but 1160 vs 1148 bytes (hand/nostrict). Same as 001c62a0_153w.c with c0/n/v[10] through e-> and v[0]/v[5] through D_0037A380.ent[i]. (the orig giv grouping: c0, n, v[10] on the e giv t7; v[3..9] unreduced t4+(t6+K)): the loop head through v[9] is right up to register names. The +3 insns: e->f[0] and the f/lk block share base+i*224 with the else arm (move v1,v0; move a0,v1), and the c4 store still goes through e. */
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
static inline void inl_cpy(V4 *d, V4 *s) {
    *d = *s;
}
s32 func_001c5db8(void);
void func_0011ef10(s32, void *);
void func_001c62a0(s32 *p, f32 *add, f32 *set) {
    s32 i, j;
    D_0037A380.n = *p++;
    for (i = 0; i < D_0037A380.n; i++) {
        Ent *e = &D_0037A380.ent[i];
        e->c0 = *(C4 *)p; p++;
        D_0037A380.ent[i].c4 = *(C4 *)p; p++;
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
        { f32 *v = (f32 *)&D_0037A380.ent[i].v[5]; f32 *d = &D_0037A380.e.x;
        for (j = 0; j < 3; j++) {
            *v++ += add[j];
            *d++ = set[j];
        } }
        e->f[0] = *(f32 *)p; p++;
        D_0037A380.ent[i].f[1] = *(f32 *)p; p++;
        D_0037A380.ent[i].f[2] = *(f32 *)p; p++;
        D_0037A380.ent[i].f[3] = *(f32 *)p; p++;
        D_0037A380.ent[i].lk.f4 = *(f32 *)p; p++;
        D_0037A380.ent[i].lk.f5 = *(f32 *)p; p++;
        if (i == 0) {
            lk_init(&D_0037A380.ent[i].lk);
        } else {
            D_0037A380.ent[i - 1].lk.next = &D_0037A380.ent[i];
            D_0037A380.ent[i].lk.next = 0;
            D_0037A380.ent[i].lk.prev = &D_0037A380.ent[i - 1];
        }
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
