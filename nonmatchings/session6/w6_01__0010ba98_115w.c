/* func_0010ba98: 115 words off (struct diff 26), hand/nostrict, rodata jump table 0x48cd30 (use wqb03_rr.py). Off: original keeps a copy of w (move a0,a1) at dispatch/case 0; 1.0f in f0 vs conversion f1 reversed; store/branch-likely scheduling; case 3 order. */
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
        func_0010b170(w);
        w = t->win;
        switch (w->c) {
        case 0:
            f = 1.0f / (f32)w->n10;
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
            f = 1.0f / (f32)w->n10;
            t->dy = t->dx = f;
            break;
        }
        w->state = 1;
        t->n = w->n10;
        w->f50 = 0.0f;
        w->f54 = 0.0f;
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
        w = t->win;
    case 2:
        func_0010b6c0(w);
        w = t->win;
        if (w->cb && t->p20->f4) {
            func_0010ea00();
            if (D_002BC740 == 1) {
                func_0010e3f0(t->p20);
            }
            w = t->win;
        }
        if (w->state != 3 || w->n12 != 0) break;
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


