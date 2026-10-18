/* func_0010b390: 22w off, hand/nostrict (s6 draft 24w): storing o[1] directly in each anim branch (no yy join var) fixes the o[1] store placement. Still off: FP regs in the anim branches: orig D in f4 and (f32)anim in f3, result in f2; here D f3, conversion f2. Block-local D/f, decl order, inlined D expressions tried. */
#include "common.h"
typedef struct {
    s32 id;
    s16 pad4;
    s16 f6;
    u16 anim;
    u16 kind;
    u8 padc[0x10];
    f32 f1c;
    u8 pad20[0x10];
    f32 x, y;
    u8 pad38[8];
    f32 w, h;
    u8 pad48[0x18];
    u8 m60[0x40];
} Win;
extern u8 D_002E26C0[];
extern void func_00267df8(s32 *, void *, void *, s32);
extern void func_002673b8(f32 *, f32 *);
extern void func_00133830(s32, void *);
void func_0010b390(Win *w, f32 *o) {
    s32 t[4];
    f32 a[4];
    f32 b[4];
    s32 x, y;
    f32 lim;
    u32 k;
    s32 id;
    f32 W, H, D, f, yy;
    f32 zero = 0.0f, one = 1.0f;

    o[0] = zero;
    o[3] = one;
    o[2] = zero;
    id = w->id;
    o[1] = w->h * 0.5f * 24.0f;
    if (id != -1) {
        w->f6 = 0;
        func_00267df8(t, D_002E26C0, w->m60, 1);
        x = w->x + 256.0f;
        y = w->y + 192.0f;
        t[0] = (t[0] >> 4) - 1792;
        t[1] = (t[1] >> 4) - 1856;
        o[0] = t[0] - x;
        if (o[0] < -w->w * 0.5f * 24.0f) {
            o[0] = -w->w * 0.5f * 24.0f;
        }
        lim = w->w * 0.5f * 24.0f;
        if (lim < o[0]) {
            o[0] = lim;
        }
        a[0] = x;
        a[1] = y;
        a[2] = zero;
        a[3] = one;
        b[0] = t[0];
        b[1] = t[1];
        b[2] = zero;
        b[3] = one;
        func_002673b8(a, a);
        func_002673b8(b, b);
        w->f1c = zero;
        if (t[2] <= 0) w->f6 = 0;
        if (t[0] < 0) w->f6 = 1;
        if (t[0] > 512) w->f6 = 1;
        if (t[1] < 0) w->f6 = 1;
        if (t[1] > 384) w->f6 = 1;
        func_00133830(w->id, w->m60);
        return;
    }
    if (w->anim < 5) {
        D = w->w * 0.5f * 24.0f;
        o[0] = D * 0.5f * (f32)w->anim - D;
        o[1] = -(w->h * 0.5f * 24.0f);
    } else if (w->anim < 10) {
        f = (f32)(w->anim - 5);
        o[0] = w->w * 0.5f * 24.0f;
        D = w->h * 0.5f * 24.0f;
        o[1] = D * 0.5f * f - D;
    } else if (w->anim < 15) {
        f = (f32)abs(14 - w->anim);
        D = w->w * 0.5f * 24.0f;
        o[0] = D * 0.5f * f - D;
        o[1] = w->h * 0.5f * 24.0f;
    } else {
        f = (f32)abs(19 - w->anim);
        o[0] = -(w->w * 0.5f * 24.0f);
        D = w->h * 0.5f * 24.0f;
        o[1] = D * 0.5f * f - D;
    }
}

