/* LCS 52w (was 71) hand/nostrict, right size 1940. Changes vs w38 draft: history fill loop counter is the function-level i (fixes s0/s1); inline loop written as a goto do-while (p = 0; goto next; do {...goto next...; next: p = func_00123158(self, p);} while (p != 0)). No loop notes -> const 2 not hoisted (li v1,2 in-loop, orig li s6,2 hoisted) but w1/w2 now s4/s5 like orig. Mechanism (global-alloc): with the while form the hoisted const 2 has refs 6 (its block is in 4 natural loops: 3 continues + for-exit each a latch to the rotated test), prio 0.130 > w1/w2 0.103; orig needs 0.0836<prio<0.1022 (refs 4 = 2 latches). An inline bool helper for the 3 tests gives refs 4 (0.0816, just below) but leaves a v1 retval. Also left: d2<d1 arm ends bc1tl set1/b set2, orig bc1fl set2/b set1. */
/* 63w hand/nostrict, right size (w10 draft was 83w). New: the 40-entry history fill loop uses two index variables (`n = 39; for (i = 39; i >= 0; i--) { func_002675a8(&D_00575090[n--], ..); D_00575090[i].w = ..; }`) so each address giv has its own shift chain (benefit 4) and both are strength-reduced from base like the original (no -freduce-all-givs); the early exit is one `if (D[0] == 0 || (D[1] == 0 && D[2] == 0)) return 0;` (fixes the bnez/li a0,1 slot). Left: global-alloc order: the hoisted constant 2 of the inline's `!= 2` test (prio 0.13) is allocated before w1/w2 (0.103/0.102) and takes s4, so w1/w2 are s5/s6 instead of s4/s5; loop counter/pointer s0/s1 swapped; d2<d1 branch bc1tl vs bc1fl. */
#include "common.h"

typedef struct { f32 x, y, z, w; } V4EA;
typedef struct { u8 pad0[0x38]; u64 w38; u8 pad40[0x24]; f32 f64; u8 pad68[0x28]; void *p90; } WkEA;
typedef struct { u32 flags; u8 pad4[0xC]; V4EA pos; u8 pad20[0x1C]; f32 f3C; u8 pad40[0x104]; WkEA *p144; } ChrEA;
typedef struct { u8 pad0[0x10]; V4EA pos; u8 pad20[0x350]; u64 f370; } EntEA;
typedef struct { EntEA *tgt; s32 part; } LockEA;
typedef struct { u8 pad0[8]; s32 *p8; s32 (*fC)(ChrEA *, WkEA *); s32 *p10; s32 (*f14)(ChrEA *, WkEA *); } TalkEA;
typedef struct { u8 pad[0xC8]; f32 fC8; } PrmEA;

extern ChrEA *D_0035BD40[3];
extern ChrEA *D_002E26A0[3];
extern s32 D_00575088;
extern s32 D_0057508C;
extern V4EA D_00575090[40];
extern u32 D_002C5958;
extern u32 D_002E3168;
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
    goto next;
    do {
        if (((s32)(p->f370 >> 37) & 3) != 2) goto next;
        if (!func_00123368(p)) goto next;
        if (func_00141200(p, 0)) goto next;
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
    next:
        p = func_00123158(self, p);
    } while (p != 0);
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
    w1 = 0;
    w2 = 0;
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
                if (w2 != 0 && w1->f64 > 0.0f && w1->p90 == D_00575080.tgt) goto set2;
                goto set1;
            } else if (d2 < d1) {
                if (w1 != 0 && w2->f64 > 0.0f && w2->p90 == D_00575080.tgt) goto set1;
                goto set2;
            }
        } else if (w1 != 0) {
            if (w2 != 0) {
                d1 = func_001629b0(&D_0035BD40[0]->pos, &D_0035BD40[1]->pos);
                d2 = func_001629b0(&D_0035BD40[0]->pos, &D_0035BD40[2]->pos);
                k = D_0035AE80.fC8 * D_0035AE80.fC8;
                if (d1 < k && d2 < k) {
                    if (w2->f64 < w1->f64) goto set2;
                    goto set1;
                } else if (d2 < d1) {
                    if (!(w2->f64 > 0.0f)) goto set2;
                    if ((s32)w2->w38 & 1) goto set1;
                    if (!(d2 < D_0035AE80.fC8 * D_0035AE80.fC8)) goto set2;
                    goto set1;
                } else {
                    if (!(w1->f64 > 0.0f)) goto set1;
                    if ((s32)w1->w38 & 1) goto set2;
                    if (d1 < D_0035AE80.fC8 * D_0035AE80.fC8) goto set2;
                    goto set1;
                }
            }
        set1:
            w1->w38 |= 8;
        } else if (w2 != 0) {
        set2:
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
