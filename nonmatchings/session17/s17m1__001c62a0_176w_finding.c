/* 001c62a0 FINDING (not the best draft; best stays session11/w64__001c62a0_56w.c): 176 orig words unmatched by true DP LCS (hand/nostrict, 1116 bytes vs 1148). s17m1: the f/lk block and the i==0 / else block now have exactly the original's shape (registers aside): f[0..3] through `s32 off = i * 224 + 432; f32 *f = (f32 *)((u8 *)&D_0037A380 + off);` gives `addiu v1,t4,432; addu v1,v1,a0` and stores at 0/4/8/12(v1); lk through a second offset `o2 = i * 224 + 448` gives `addiu v0,t4,448; addu a1,v0,a0`; the else arm `l->prev = &D.ent[i-1]; D.ent[i-1].lk.next = &D.ent[i]; l->next = 0;` gives the original's 7 insns (t4+(a0+16), t4+a0 at 232, t4+t6) and the then arm stores 8/12 off the hoisted &ent[0].lk. Written as `D.ent[i].f[k]` the +432 folds into %lo(D+432) or into the store offsets. Why the rest breaks: the pass-2 loop shrinks from 122 to 117 insns, so loop.c's decreasing move threshold (`threshold * savings * lifetime >= insn_count`, savings 1, life 1) hoists one more invariant (v[3]'s t6+64), v[3] joins the t5 giv group and every register shifts. Left: that, plus the original's spilled in-loop HIGH (lui s6 remat) and its s8. */
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
    D_0037A380.n = *p++;
    for (i = 0; i < D_0037A380.n; i++) {
        Ent *e = &D_0037A380.ent[i];
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
        { f32 *d = &D_0037A380.e.x; f32 *v = (f32 *)&e->v[5];
        for (j = 0; j < 3; j++) {
            *v++ += add[j];
            *d++ = set[j];
        } }
        {
        s32 off = i * 224 + 432;
        f32 *f = (f32 *)((u8 *)&D_0037A380 + off);
        struct Lk *l;
        f[0] = *(f32 *)p; p++;
        f[1] = *(f32 *)p; p++;
        f[2] = *(f32 *)p; p++;
        f[3] = *(f32 *)p; p++;
        { s32 o2 = i * 224 + 448; l = (struct Lk *)((u8 *)&D_0037A380 + o2); }
        p = rd2(l, p);

        if (i == 0) {
            lk_init(&D_0037A380.ent[i].lk);
        } else {
            l->prev = &D_0037A380.ent[i - 1];
            D_0037A380.ent[i - 1].lk.next = &D_0037A380.ent[i];
            l->next = 0;
        }
        }
    }
    if (add[0] < 0.0f) i = 0; else j = 0;
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
