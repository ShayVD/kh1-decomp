/* The skeleton's bone matrices, without strict aliasing (docs/modules.md
 * "Session 52"): func_00163150 and func_00163490 build a model's bone
 * matrices (D_00573F10, D_00351E10).  func_001636d0 between them is one of
 * the nine unmatched functions and stays in asm.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/math.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00150000_h59.h"

/* func_00163150 (from hand/nostrict/text_00150000_s6_08.c). */
typedef f32 Mtx[4][4];
typedef struct { u8 pad[0x2c]; u32 x2c; } Bone;
typedef struct { u8 pad[0x10]; s32 x10; u8 pad14[0xc]; s32 x20; } MHdr;
typedef struct { s32 x0; Bone *bones; MHdr *h; } Mdl;
typedef struct { f32 a[4]; f32 s[4]; f32 r[4]; f32 t[4]; } Xf;
typedef struct {
    Mdl **mdl;
    u8 pad4[8];
    u32 xC;
    u8 pad10[0x78];
    f32 *x88;
    u8 pad8c[0x150 - 0x8c];
    Xf *x150;
    Mtx *x154;
    Mtx *x158;
} Obj;
extern Mtx D_00351E10[];
extern Mtx D_00573F10;
extern f32 D_00574F10[];
void func_001625c8(void *, void *);
void func_00162878(f32 *, void *, f32 *);
void func_00162c5c(void *, void *, void *);
void func_002673b8(f32 *, f32 *);
void func_00267e60(f32 *, f32 *, f32 *, f32);
void func_00267370(f32 *, f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);
void func_00163150(Obj *o, s32 i) {
    Mtx tmp;
    f32 d[4];
    f32 save[4];
    f32 a[4];
    f32 b[4];
    Mdl *m = *o->mdl;
    MHdr *h = m->h;
    if (i == h->x20 - 1 || (h->x20 == -1 && i == h->x10 - 1)) {
        f32 (*ml)[4];
        f32 (*par)[4];
        f32 (*tm)[4];
        f32 (*w)[4];
        f32 *s;
        u32 k; Bone *bn;
        f32 *r1, *r2;
        bn = &m->bones[i];
        save[0] = o->x154[i][3][0];
        tm = D_00351E10[i];
        save[1] = o->x154[i][3][1];
        save[2] = o->x154[i][3][2];
        k = bn->x2c & 0x3ff; //dep:4
        ml = o->x158[i];

        if (k == 0x3ff) {
            par = D_00573F10;
            func_001625c8(par, tmp);
        } else {
            par = D_00351E10[k];
            func_001625c8(o->x154[k], tmp);
        }
        if (o->xC & 4) {
            d[0] = o->x88[0] - (save[0] + D_00574F10[0]);
            d[1] = o->x88[1] - (save[1] + D_00574F10[1]);
            d[2] = o->x88[2] - (save[2] + D_00574F10[2]);
        } else {
            d[0] = o->x88[0];
            d[1] = o->x88[1];
            d[2] = o->x88[2];
        }
        d[3] = 0;
        func_00162878(d, tmp, d);
        r1 = ml[1];
        func_002673b8(d, d);
        func_002673b8(r1, r1);
        func_00267e60(r1, d, r1, o->x88[3]);
        func_002673b8(r1, r1);
        a[0] = ml[0][0];
        a[1] = ml[0][1];
        a[2] = ml[0][2];
        func_002673b8(a, a);
        b[0] = ml[2][0];
        b[1] = ml[2][1];
        b[2] = ml[2][2];
        func_002673b8(b, b);
        r2 = ml[2];
        func_00267370(r2, a, r1);
        func_002673b8(r2, r2);
        func_00267370(ml[0], r1, r2);
        func_002673b8(ml[0], ml[0]);
        func_00267370(r2, ml[0], r1);
        func_002673b8(r2, r2);
        func_00162c5c(tm, par, ml);
        w = (f32 (*)[4])((u32)(i << 6) + (u32)o->x154);
        s = ((Xf *)((u32)(i << 6) + (u32)o->x150))->s;
        func_00267e90(w[0], tm[0], s[0]);
        func_00267e90(w[1], tm[1], s[1]);
        func_00267e90(w[2], tm[2], s[2]);
        func_002675a8(w[3], tm[3]);
        o->x154[i][3][0] = save[0];
        o->x154[i][3][1] = save[1];
        o->x154[i][3][2] = save[2];
        func_00162c5c(ml, tmp, o->x154[i]);
    }
}

/* func_00163490 (from hand/nostrict/text_00150000_h59.c). */
typedef struct {
    Mdl59 **x0;
    u8 pad4[8];
    s32 xC;
    u8 pad10[0x150 - 0x10];
    M64_59 *x150;
    M64_59 *x154;
    M64_59 *x158;
} Ent63;
void func_001627d0(f32 *, f32 *, f32 *);
void func_00162848(f32 *, M64_59 *, f32 *);
void func_00162cd0(f32 *, f32 *, M64_59 *);
extern M64_59 D_00351E10_00163490[] __asm__("D_00351E10");
#define D_00351E10 D_00351E10_00163490
#define D_00573F10 (*(M64_59 (*)) &D_00573F10)
#define func_00162c5c ((void (*)(M64_59 *, M64_59 *, M64_59 *)) func_00162c5c)
#define func_00163150 ((void (*)(Ent63 *, s32)) func_00163150)
void func_00163490(Ent63 *e) {
    s32 i;
    S48_59 *s = (*e->x0)->src;
    f32 tmp[4];
    M64_59 *pm;
    M64_59 *g;
    M64_59 *w;
    M64_59 *d;
    f32 *sc;
    u32 p, q;
    for (i = 0; i < (*e->x0)->n; i++) {
        p = s[i].par & 0x3ff;
        if (p == 0x3ff) {
            pm = &D_00573F10;
            e->x150[i].m[1][0] = e->x150[i].m[0][0];
            e->x150[i].m[1][1] = e->x150[i].m[0][1];
            e->x150[i].m[1][2] = e->x150[i].m[0][2];
        } else {
            pm = &D_00351E10[p];
            func_001627d0(e->x150[i].m[1], e->x150[p].m[1], e->x150[i].m[0]);
        }
        q = s[i].par & 0x3ff;
        g = &D_00351E10[i];
        w = &e->x158[i];
        if (q == 0x3ff) {
            func_00162848(tmp, &D_00573F10, e->x150[i].m[3]);
        } else {
            func_00162848(tmp, &e->x154[q], e->x150[i].m[3]);
        }
        tmp[3] = 1.0f;
        func_00162cd0(e->x150[i].m[2], e->x150[i].m[3], w);
        func_00162c5c(g, pm, w);
        d = (M64_59 *)(i * 64 + (u32)e->x154);
        sc = ((M64_59 *)(i * 64 + (u32)e->x150))->m[1];
        func_00267e90(d->m[0], g->m[0], sc[0]);
        func_00267e90(d->m[1], g->m[1], sc[1]);
        func_00267e90(d->m[2], g->m[2], sc[2]);
        func_002675a8(d->m[3], g->m[3]);
        func_002675a8(e->x154[i].m[3], tmp);
        if (e->xC & 0xC) func_00163150(e, i);
    }
}
#undef D_00351E10
#undef D_00573F10
#undef func_00162c5c
#undef func_00163150

