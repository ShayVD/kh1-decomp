/* 001c62a0 39w true DP LCS (39 orig words unmatched, 39 ours; hand/nostrict, right size 1148, no context; was 55-56w, session11/w64). FLAGGED: c4 address probe `*(C4 *)((u8 *)&D.ent[i].v[2] - 44)` (s11w24) and the dead store `i = 0;` after the call (it stops the sibcall: without it the call becomes `j` and the size drops to 1144). The old dead FP test after the loop is gone. s17m1 changes: (1) f[0..3] and lk through integer offsets `s32 off = i * 224 + 432; f32 *f = (f32 *)((u8 *)&D_0037A380 + off);` and `o2 = i * 224 + 448` (gives the original's `addiu v1,t4,432; addu v1,v1,a0` and the 7-insn else arm); (2) each float copied by an inline `p = rd1(&f[k], p)` (also for lk.f4/f5): the inline's param/return copies add pass-2 loop insns that vanish later, which keeps loop.c's decreasing move threshold from hoisting v[3]'s base (with plain stores the loop has 117 insns and v[3] joins the t5 group); (3) a pointer biv `u8 *b` (b = &D_0037A380 in an explicit `if (D.n > 0)` guard, `b += 224` per iteration) for the j-loop pointer `v = (f32 *)(b + 336)`: the original's s4 giv; it raises register pressure so the hoisted in-loop HIGH copy is spilled and reloaded as `lui s6` like the original; (4) the loop as `if (n > 0) { b = ...; i = 0; do { ... i++; } while (i < n); }`. Left: b is `move s1,v1` and the hoisted base copy is `move t8,s1` (original: base copy `move s1,v1` first, b = `move s4,s1` among the giv inits); i's `move s0,zero` sits after the guard (original: in the prologue); d pointer from t6-160 (original s1+80); &ent[0].lk in s4 (original t8); i*224 giv t3 vs ldl temp t4 swapped. */

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
    u8 *b;
    D_0037A380.n = *p++;
    if (D_0037A380.n > 0) {
    b = (u8 *)&D_0037A380;
    i = 0;
    do {
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
        { f32 *d = &D_0037A380.e.x; f32 *v = (f32 *)(b + 336);
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
    } while (i < D_0037A380.n);
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
