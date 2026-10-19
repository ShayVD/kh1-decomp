/* rodata (RO 0048cd30: jump table at 0x48cd30), mode hand (strict). Verified: wqb03_rr.py 0048cd30 MATCH.
 * func_0010ba98: s11w38 from w34's 2w. FLAGGED:
 *  (1) dead set `w = 0;` before func_0010b170(t->win) in case 0 (life1 deletes it; keeps the bb0 PRE copy) [w34];
 *  (2) redundant FP-condition set `if (t->dx < 0.0f) w = t->win;` at the start of the shared `case 0: case 3:` arm
 *      (w already equals t->win there, so it changes nothing). The FP test cannot be if-converted (no FP cmov),
 *      so the conditional set kills w on one path: the copy 212 = w no longer reaches the arm's t->win load, CPROP2
 *      leaves it on the PRE reg (lhu v0,16(a0)). The arm-end `w = t->win;` of w34 is gone; the test and the conditional set
 *      leave no code in the output (both hold t->win; deleted after allocation). */
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
extern s32 func_0010ea00(P20 *);
extern void func_0010e3f0(P20 *);
extern s32 D_002BC740;
s32 func_0010ba98(Task *t) {
    Win *w = t->win;
    f32 f;

    switch (w->state) {
    case 0:
        w = 0;
        func_0010b170(t->win);
        switch ((w = t->win)->c) {
        case 1:
            t->dy = t->dx = 1.0f / (f32)(t->win->n10 - 2);
            break;
        case 2:
            t->dy = t->dx = 1.0f / (f32)(t->win->n10 - 1);
            break;
        case 0:
        case 3:
            if (t->dx < 0.0f) w = t->win;
            t->dy = t->dx = 1.0f / (f32)t->win->n10;
            break;
        }
        t->win->state = 1;
        t->n = t->win->n10;
        t->win->f54 = 0.0f;
        t->win->f50 = 0.0f;
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
        w->f50 = 1.0f;
        w->f54 = 1.0f;
        w->state = 2;
        if (w->cb) {
            w->cb(t->p20->e, t->p20->f24);
            w = t->win;
        }
    case 2:
        func_0010b6c0(w);
        w = t->win;
        if (w->cb && t->p20->f4) {
            func_0010ea00(t->p20);
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


