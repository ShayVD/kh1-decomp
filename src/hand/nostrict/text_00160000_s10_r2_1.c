#include "common.h"
#include "data/bss_0057.h"
/* func_0016ea58 (hand/nostrict): the target search is matched func_001711d0 written as a static inline helper (inl_001711d0, its exact body); the set1/set2 gotos written out as separate w1->w38 |= 8 / w2->w38 |= 8 statements (jump2 cross-jumps them; the extra refs give w1/w2 s4/s5 over the hoisted const 2), the d2<d1 arm as one && / || condition, w2 = 0 before w1 = 0. */

#include "data/types/nostrict_text_00160000_s10_r2_1.h"
typedef struct { u8 pad[0xC8]; f32 fC8; } PrmEA;

extern ChrEA *D_0035BD40[3];
extern ChrEA *D_002E26A0[3];
extern s32 D_00575088;
extern s32 D_0057508C;
extern V4EA D_00575090[40]; /* src/data/bss_0057.c: f32 D_00575090[40][4] */
extern u32 D_002C5958;
#include "data/pieces/D_002E3168.h"
extern LockEA D_002E31B0;
extern LockEA D_00575080;
extern f32 D_0035AF40;
extern f32 D_0048E950;
extern PrmEA D_0035AE80;
extern TalkEA D_00575310;
extern u8 D_002C5C60[];

extern s32 func_00122ff8(ChrEA *);
extern void func_00122768();
extern void func_001224c8(s32 *, void *, void *, f32);
extern EntEA *func_00123158(ChrEA *, EntEA *);
extern s32 func_00123368(EntEA *);
extern void func_0012ec60(EntEA *, s32, f32 *);
extern s32 func_0012ee70(EntEA *, s32);
extern s32 func_0012f040(void *, s32);
extern s32 func_00141200(EntEA *, s32);
extern s32 func_00153d78(ChrEA *);
extern f32 func_001629b0(V4EA *, V4EA *);
extern void func_0016e0d0(s32);
extern void func_0016e3f8(void);
extern f32 func_00267390(void *, void *);
extern void func_00267530(void *, void *, void *);
extern void func_002675a8(void *, void *);

static inline void inl_001711d0(ChrEA *self, LockEA *out, f32 r) {
    f32 a[4];
    f32 b[4];
    EntEA *p;
    s32 i;
    f32 best, d;
    out->part = -1;
    out->tgt = 0;
    if (r <= 0.0f) best = D_0048E950;
    else best = r * r;
    p = 0;
    while ((p = func_00123158(self, p)) != 0) {
        if (((s32)(p->f370 >> 37) & 3) != 2) continue;
        if (!func_00123368(p)) continue;
        if (func_00141200(p, 0)) continue;
        for (i = -1; (i = func_0012ee70(p, i)) >= 0;) {
            if (!func_0012f040(p, i)) continue;
            func_0012ec60(p, i, a);
            func_00267530(b, a, &self->pos);
            d = func_00267390(b, b);
            if (d < best) {
                out->tgt = p;
                best = d;
                out->part = i;
            }
        }
    }
}

static inline s32 inl_dead(ChrEA *c) {
    if (func_00153d78(c) || (c->flags & 0x200)) return 1;
    return 0;
}

s32 func_0016ea58(void) {
    V4EA v;
    WkEA *w1;
    WkEA *w2;
    s32 i, j, n;
    f32 d1, d2, k;
    for (i = 2; i >= 0; i--) D_0035BD40[i] = 0;
    w2 = 0;
    w1 = 0;
    if (func_00122ff8(D_002E26A0[0])) D_0035BD40[0] = D_002E26A0[0];
    if (func_00122ff8(D_002E26A0[1]) && (w1 = D_002E26A0[1]->p144) != 0) D_0035BD40[1] = D_002E26A0[1];
    if (func_00122ff8(D_002E26A0[2]) && (w2 = D_002E26A0[2]->p144) != 0) D_0035BD40[2] = D_002E26A0[2];

    if (D_0035BD40[0] == 0 || (D_0035BD40[1] == 0 && D_0035BD40[2] == 0)) return 0;
    func_0016e0d0(1);
    D_0057508C = 0;
    if (D_00575088 == 0) {
        n = 39;
        for (i = 39; i >= 0; i--) {
            func_002675a8(&D_00575090[n--], &D_0035BD40[0]->pos);
            D_00575090[i].w = D_0035BD40[0]->f3C;
        }
        D_00575088 = 1;
    } else {
        func_00267530(&v, &D_00575090[0], &D_0035BD40[0]->pos);
        if (func_00267390(&v, &v) > 1600.0f) {
            D_0057508C = 1;
            for (i = 38; i >= 0; i--) func_002675a8(&D_00575090[i + 1], &D_00575090[i]);
            func_002675a8(&D_00575090[0], &D_0035BD40[0]->pos);
            D_00575090[0].w = D_0035BD40[0]->f3C;
        }
    }
    func_0016e3f8();
    if (w1 != 0 && inl_dead(D_0035BD40[1])) {
        w1->f64 = 0;
        w1 = 0;
    }
    if (w2 != 0 && inl_dead(D_0035BD40[2])) {
        w2->f64 = 0;
        w2 = 0;
    }
    if ((D_002C5958 & 1) && (D_002E3168 & 1)) {
        if (D_002E31B0.tgt != 0) {
            D_00575080 = D_002E31B0;
        } else {
            inl_001711d0(D_0035BD40[0], &D_00575080, D_0035AF40);
            if (D_00575080.part < 0) D_00575080.tgt = 0;
        }
        if (D_00575080.tgt != 0) {
            if (w1 != 0 && func_0012f040(D_0035BD40[1], -1)) d1 = func_001629b0(&D_00575080.tgt->pos, &D_0035BD40[1]->pos);
            else d1 = D_0048E950;
            if (w2 != 0 && func_0012f040(D_0035BD40[2], -1)) d2 = func_001629b0(&D_00575080.tgt->pos, &D_0035BD40[2]->pos);
            else d2 = D_0048E950;
            if (d1 < d2) {
                if (w2 != 0 && w1->f64 > 0.0f && w1->p90 == D_00575080.tgt) w2->w38 |= 8;
                else w1->w38 |= 8;
            } else if (d2 < d1) {
                if (w1 != 0 && w2->f64 > 0.0f && w2->p90 == D_00575080.tgt) w1->w38 |= 8;
                else w2->w38 |= 8;
            }
        } else if (w1 != 0) {
            if (w2 != 0) {
                d1 = func_001629b0(&D_0035BD40[0]->pos, &D_0035BD40[1]->pos);
                d2 = func_001629b0(&D_0035BD40[0]->pos, &D_0035BD40[2]->pos);
                k = D_0035AE80.fC8 * D_0035AE80.fC8;
                if (d1 < k && d2 < k) {
                    if (w2->f64 < w1->f64) w2->w38 |= 8;
                    else w1->w38 |= 8;
                } else if (d2 < d1) {
                    if (w2->f64 > 0.0f && ((s32)w2->w38 & 1 || d2 < D_0035AE80.fC8 * D_0035AE80.fC8)) w1->w38 |= 8;
                    else w2->w38 |= 8;
                } else {
                    if (!(w1->f64 > 0.0f)) w1->w38 |= 8;
                    else if ((s32)w1->w38 & 1) w2->w38 |= 8;
                    else if (d1 < D_0035AE80.fC8 * D_0035AE80.fC8) w2->w38 |= 8;
                    else w1->w38 |= 8;
                }
            } else w1->w38 |= 8;
        } else if (w2 != 0) {
            w2->w38 |= 8;
        }
    }
    if (D_00575310.p8 != 0 && *D_00575310.p8 != 1) D_00575310.p8 = 0;
    if (D_00575310.p10 != 0 && *D_00575310.p10 != 1) D_00575310.p10 = 0;
    if (D_00575310.p8 != 0) {
        if (w1 == 0 || D_00575310.fC == 0 || !D_00575310.fC(D_0035BD40[1], w1) || !(D_0035BD40[1]->flags & 0x8000)) {
            func_001224c8(D_00575310.p8, D_002C5C60, func_00122768, 30.0f);
            D_00575310.p8 = 0;
        }
    }
    if (D_00575310.p10 != 0) {
        if (w2 == 0 || D_00575310.f14 == 0 || !D_00575310.f14(D_0035BD40[2], w2) || !(D_0035BD40[2]->flags & 0x8000)) {
            func_001224c8(D_00575310.p10, D_002C5C60, func_00122768, 30.0f);
            D_00575310.p10 = 0;
        }
    }
    return 0;
}
#include "data/bss_0057_typed.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C5958.h"
