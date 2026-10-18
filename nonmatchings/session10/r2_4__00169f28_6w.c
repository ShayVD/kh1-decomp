/* 00169f28: 6 words off (wqb03_rr 0048E8E0; was 12), plain hand (strict), right size 1228. From s10 w12 draft: the whole search loop in a static inline inl_find(e, w) returning bi, with the arrays as loop-body block locals and plain 'continue' for the early fails (frame addresses of an inlined function's locals go straight into the arg regs, so nothing is hoisted, and the fails now branch straight to the i += 10 increment like the orig). Equivalent: a void inline loop body taking &best/&bi (.r2_4_d shape). Left: only best/0.1f f20/f21 swap: global-alloc best (5 refs, live 77) prio .13 vs hoisted const (5 refs, live 144-148) .07; best needs <=3 refs or live >144. Tried: lim local before loop/in loop, decl orders, set orders, best init before func_00135838 (moves the load). */
#include "common.h"
typedef f32 Mtx[4][4];
typedef struct { u8 pad[0x18]; f32 x18; } S130;
typedef struct {
    u32 x0;
    u8 pad4[0xC];
    f32 pos[4];
    u8 pad20[0x50];
    s32 x70;
    u8 pad74[0x5C];
    Mtx mD0;
    u8 pad110[0x20];
    s32 x130;
    u8 pad134[0x30];
    s32 x164;
    u8 pad168[0x158];
    f32 x2C0;
    f32 x2C4;
    u8 pad2C8[0xA8];
    u64 x370;
} E9F;
typedef struct {
    u8 pad0[0x34];
    f32 f34;
    u32 b0:6;
    u32 b6:1;
    u32 b7:25;
    u32 hi;
    u8 pad40[0xC];
    s32 w4C;
    u8 pad50[8];
    u32 w58;
    u8 pad5C[4];
    u32 w60;
    u8 pad64[0xC];
    f32 f70;
    u8 pad74[0x70];
    f32 fE4;
    u8 padE8[8];
    f32 vF0[4];
    u8 pad100[0x20];
    u8 x120[0x10];
} __attribute__((aligned(8))) W9F;
typedef struct { f32 a[4]; f32 b[4]; f32 c0; f32 c1; s32 c2; s32 c3; u8 pad[0x50]; } Q9F;
typedef struct { u8 pad[0x10]; f32 pos[4]; } Chr9F;

extern s32 D_00574FB4;
extern s32 D_0057508C;
extern f32 D_002BBDFC;
extern f32 D_0048E8D4;
extern f32 D_00575090[][4];
extern Chr9F *D_0035BD40[];
extern Mtx D_002BBFA0;
extern f32 D_002C58B0[];
extern s32 D_002E27A8;
s32 func_00137618(E9F *);
s32 func_00153d78(E9F *);
void func_0013dfb8(E9F *, void *);
s32 func_00135838(E9F *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);
void func_00135b88(E9F *, f32 (*)[4]);
void sceVu0CopyMatrix(Mtx, Mtx);
void func_002675a8(f32 *, f32 *);
void func_00162c5c(Mtx, Mtx, Mtx);
s32 func_0024edf0(Mtx, f32 (*)[4]);
void func_00116660(Q9F *);
u64 func_001166e8(Q9F *);
f32 func_001629b0(f32 *, f32 *);
void func_00124060(E9F *, f32 *);
void func_00135800(E9F *, f32, f32);
void func_001373f8(E9F *, f32);

static inline s32 inl_a(s32 v, W9F *b) {
    s32 w = v;
    if (w < 3 && v >= 0) return 1;
    return v == b->w4C;
}
static inline s32 inl_b(s32 v, W9F *b) {
    s32 w = v;
    if (v < 124 && w >= 117) return 1;
    return v == b->w4C;
}
static inline s32 inl_c(s32 v, W9F *b) {
    s32 w = v;
    if (v >= 0 && (v < 3 || (v < 131 && w >= 124))) return 1;
    return v == b->w4C;
}
static inline s32 inl_d(s32 v, W9F *b) {
    s32 w = v;
    if (v < 49 && w >= 45) return 1;
    return v == b->w4C;
}
static inline void inl_rst(E9F *e, W9F *w) {
    if (e->x70 != 2) func_0013dfb8(e, w->x120);
}

static inline s32 inl_busy(E9F *e) { return func_00153d78(e) || (e->x0 & 0x200); }
static inline void inl_go(E9F *e, f32 *p) {
    func_00124060(e, p);
    func_00135800(e, 0.0f, 0.0f);
    func_00135800(e, 1.0f, 30.0f);
    ((S130 *)e->x130)->x18 = 1.0f;
    func_001373f8(e, 30.0f);
}
static inline s32 inl_find(E9F *e, W9F *w) {
    s32 i, bi;
    f32 best, d;
    f32 *p;
    best = D_0048E8D4;
    bi = -1;
    for (i = w->w60 + 1; i < 40; i += 10) {
        f32 v[4];
        f32 m10[8][4];
        Mtx m90;
        Q9F q;
        s32 vis;
        p = D_00575090[i];
        func_00267530(v, p, D_0035BD40[0]->pos);
        if (0.0999999940395355224609375f < v[1] * w->fE4) continue;
        v[1] = 0.0f;
        if (0.0999999940395355224609375f < func_00267390(v, w->vF0)) continue;
        func_00135b88(e, m10);
        sceVu0CopyMatrix(m90, e->mD0);
        func_002675a8(m90[3], p);
        m90[3][3] = 1.0f;
        func_00162c5c(m90, D_002BBFA0, m90);
        if (!func_0024edf0(m90, m10)) continue;
        func_00116660(&q);
        func_002675a8(q.a, p);
        func_002675a8(q.b, D_002C58B0);
        q.c0 = e->x2C0;
        q.c1 = e->x2C4;
        q.c2 = 0;
        vis = func_001166e8(&q) == 0;
        if (vis) {
            d = func_001629b0(e->pos, p);
            if (d < best) {
                best = d;
                bi = i;
            }
        }
    }
    return bi;
}
s32 func_00169f28(E9F *e, W9F *w) {
    s32 ok, t;
    s32 i, bi;
    f32 best, d;
    f32 *p;
    if (w->b6) {
        if (e->x0 & 0x80) goto r0;
        w->b6 = 0;
        ((S130 *)e->x130)->x18 = w->f34;
        goto r0;
    }
    ok = 0;
    if (D_00574FB4 != 1) {
        if (D_00574FB4 == 0) goto r0;
    } else if ((s32)(e->x370 >> 50) & 1) return 0;
    if (!func_00137618(e)) return 0;
    { s32 r = func_00153d78(e); s32 t2; if (r || (e->x0 & 0x200)) t2 = 1; else t2 = 0; if (t2) goto r0; }
    if (0.0f < w->f70) w->f70 -= D_002BBDFC;
    if (0.0f < w->f70) goto r0;
    if (w->w58 >= 240) ok = 1;
    else if (w->w58 >= 160 || (w->w58 >= 80 && D_0057508C != 0)) {
        s32 save = w->w4C;
        w->w4C = -1;
        switch (e->x70) {
        case 10: case 13: case 15: case 18: case 26: inl_rst(e, w); break;
        case 0: ok = inl_a(e->x164, w); break;
        case 8: ok = inl_b(e->x164, w); break;
        case 24: ok = inl_c(e->x164, w); break;
        case 17: ok = inl_d(e->x164, w); break;
        }
        w->w4C = save;
    }
    if (!ok) goto r0;
    if (func_00135838(e)) goto r0;
    bi = inl_find(e, w);
    if (bi >= 0) {
        inl_go(e, D_00575090[bi]);
        w->b6 = 1;
        w->w58 = 0;
        w->w60 = 0;
        if (D_002E27A8 == 2) w->f70 = 600.0f;
        else w->f70 = 240.0f;
        return 1;
    }
    w->w60++;
    if (w->w60 >= 10) w->w60 = 0;
    goto r0;
r0:
    return 0;
}
