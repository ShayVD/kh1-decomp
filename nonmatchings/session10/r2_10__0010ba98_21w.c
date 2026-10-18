/* 0010ba98: 21w by rodata-aware LCS (RO 0048cd30; the s9 w10 27w draft scores 25 by the same count), mode hand (strict). s9 w10 draft with 'extern s32 func_0010ea00(void);' (was void; lever 2, r2_10 s10): -4w, fixes the case-2 beqzl register. Left: the gcse PRE copy of t->win folded by cprop2 (case-0 jal slot move a0,a1, a1 vs a0 in the c==0/3 arms and join stores) and the case-1 cb-call tail order (see the s10 w10 finding draft; combining it with the flip gives 26). */
/* func_0010ba98: 41w by LCS in hand (776 vs 760 bytes; s6 draft 46w/760 in hand/nostrict), rodata jtbl 0x48cd30. New: the orig's 'move a0,a1' copies are gcse PRE reaching-reg copies of the t->win load (insn 'copy expression ... to reg'): writing func_0010b170(t->win) and t->win-> in case 0 reproduces both copies (ours lands in a2, and cprop pass 2 folds the merge-block uses back into w; in the orig they stay on the copy, so w must be changed on some path between). Which accesses are w vs t->win inside case 0 does not matter (512 combos all 41w): CSE folds them. Left: copy register a2 vs a0, 1.0f f0/f1 order, +16 bytes. */
#include "common.h"
typedef struct {
    s32 id;
    s16 pad4;
    u16 f6;
    u16 anim;
    u16 kind;
    u16 c;
    u16 pade;
    u16 n10;
    u16 n12;
    void (*cb)();
    s32 state;
    f32 f1c;
    u8 pad20[0x10];
    f32 x, y;
    u8 pad38[8];
    f32 w, h;
    u8 pad48[8];
    f32 f50, f54;
} Win;
typedef struct { u8 pad0[4]; s32 f4; u8 pad8[6]; u16 e; u8 pad10[0x14]; s32 f24; } P20;
typedef struct { u8 pad0[0x10]; u16 n; u16 pad12; f32 dx; f32 dy; Win *win; P20 *p20; } Task;
extern void func_0010b170(Win *);
extern void func_0010b6c0(Win *);
extern s32 func_0010ea00(void);
extern void func_0010e3f0(P20 *);
extern s32 D_002BC740;
s32 func_0010ba98(Task *t) {
    Win *w = t->win;
    f32 f;

    switch (w->state) {
    case 0:
        func_0010b170(t->win);
        w = t->win;
        switch (w->c) {
        case 0:
            t->dy = t->dx = 1.0f / (f32)t->win->n10;
            break;
        case 1:
            t->dy = t->dx = 1.0f / (f32)(w->n10 - 2);
            break;
        case 2:
            t->dy = t->dx = 1.0f / (f32)(w->n10 - 1);
            break;
        case 3:
            t->dy = t->dx = 1.0f / (f32)t->win->n10;
            break;
        }
        t->win->state = 1;
        t->n = t->win->n10;
        t->win->f50 = 0.0f;
        t->win->f54 = 0.0f;
    case 1:
        if (t->n != 0) {
            if (w->c == 1 && t->n == w->c) {
                w->f50 -= t->dx * 0.5f;
                w->f54 -= t->dy * 0.5f;
            } else {
                w->f50 += t->dx;
                w->f54 += t->dy;
            }
            func_0010b6c0(w);
            t->n--;
            break;
        }
        w->f54 = 1.0f;
        w->state = 2;
        w->f50 = 1.0f;
        if (w->cb) {
            w->cb(t->p20->e, t->p20->f24);
        }
    case 2:
        func_0010b6c0(t->win);
        w = t->win;
        if (w->cb && t->p20->f4) {
            func_0010ea00();
            if (D_002BC740 == 1) {
                func_0010e3f0(t->p20);
            }
            w = t->win;
        }
        if (w->state != 3 || t->win->n12 != 0) break;
    case 3:
        t->n = w->n12;
        w->state = 4;
        t->dy = t->dx = 1.0f / (f32)w->n12;
    case 4:
        if (t->n != 0) {
            w->f50 -= t->dx;
            w->f54 -= t->dy;
            func_0010b6c0(w);
            t->n--;
            break;
        }
        w->f50 = 0.0f;
        w->state = 5;
        w->f54 = 0.0f;
    case 5:
        w->state = 0;
        if (w->cb) {
            w->cb();
        }
        return 4;
    }
    if (D_002BC740 == 1) {
        t->win->state = 0;
        return 4;
    }
    return 0;
}


