/* 0010ba98 34w (w20; hand strict, rodata jtbl 0x48cd30, right size 760 now; w16 draft 41w/776). Changes from w16: (1) `if (w->state != 3 || t->win->n12 != 0) break;` before the case-3 fallthrough: with w->n12 our cse/reorg reused the test's n12 value, case 2 jumped over the first insn of case 3 (b + align nop, +8 bytes); the orig falls straight through and reloads n12; (2) case 1 end/case 2: no `w = t->win;` after the cb call and `func_0010b6c0(t->win);` in case 2 (removes the extra lw a2/move a1,a2 PRE copy, -8 bytes). Left: in case 0 after func_0010b170 the orig keeps the c==0/c==3 n10 loads and the state/n/f50/f54 stores on the gcse PRE copy a0 of the t->win reload (ours: cprop folds them back into w/a1, and the copy lands in the jal slot instead of the switch-dispatch slot), FP order of the 1.0f/n10 divide (f0/f1 swapped), case-1 end store order f54/state/f50, cb argument order (orig loads a1 = p20->f24 before a0 = p20->e), a few v0/v1 swaps near func_0010ea00. Idea for the copy: a PRE copy survives only if it is made in the last gcse pass (no cprop after it), so the orig's t->win redundancy was probably exposed only by the first gcse pass. Rest is w16's header: */
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
extern void func_0010ea00(void);
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
            f = 1.0f / (f32)t->win->n10;
            t->dy = t->dx = f;
            break;
        case 1:
            f = 1.0f / (f32)(w->n10 - 2);
            t->dy = t->dx = f;
            break;
        case 2:
            f = 1.0f / (f32)(w->n10 - 1);
            t->dy = t->dx = f;
            break;
        case 3:
            f = 1.0f / (f32)t->win->n10;
            t->dy = t->dx = f;
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
        f = 1.0f / (f32)w->n12;
        t->dy = t->dx = f;
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


