/* 001fe1b8 2 LCS words (3 pos), mode hand, no context, right size 588. From s9 r2_2 59w draft: (1) param `s32 a` reused as v, `Scr *o = (Scr *)a;` after `s32 r = 0;`, and `a = r; return a;` at the end so P (a) outlives o -> P is cse canonical, so no cse swap/combine merge: P keeps the a0 copy preference, o has none -> move a1,a0 (o a1, a a0); (2) the 0xf mask var split per part (f part 1, g part 2) and t split (t part 1, u part 2): f/g 4 refs each rank below o, b ranks above t/u (a2/a3/t0 right); (3) part-2 lim as `a = (o->cc - o->ce) << 4;`. Left: the first load is `lhu a0,210(a0)` (via P, canonical) instead of `lhu a0,210(a1)` via o, which also lets sched2 put `move t1,zero` after the lh. Needs o canonical in cse1 while combine still keeps the `P = a0; o = P` copy. */
#include "common.h"
typedef struct {
    u8 pad0[0xcc];
    s16 cc;
    s16 ce;
    u16 d0;
    u16 d2;
    s16 d4;
    s16 d6;
} Scr;
extern f32 D_002BBDFC;

s32 func_001fe1b8(s32 a) {
    s32 r = 0;
    Scr *o = (Scr *)a;
    s32 t, f, g, u;
    s32 b;
    a = o->d2;
    b = a << 16;
    if (o->d4 < 0) {
        t = (s16)(a & 0xfff0);
        f = a & 0xf;
        if (f) {
            o->d2 = (s32)((b >> 16) - D_002BBDFC * 4.0f);
            if ((s16)o->d2 <= 0) {
                o->d2 = 0;
            } else if (t < (s16)o->d2) {
                goto next;
            } else {
                o->d2 = t;
            }
        }
        o->d4 = 0;
    } else if (o->d4 > 0) {
        t = (s16)(a & ~0xf) + 16;
        f = a & 0xf;
        a = (o->ce - 1) << 4;
        if (f) {
            o->d2 = (s32)((b >> 16) + D_002BBDFC * 4.0f);
            if ((s16)o->d2 >= a) {
                o->d2 = a;
            } else if ((s16)o->d2 < t) {
                goto next;
            } else {
                o->d2 = t;
            }
            r = 1;
        }
        o->d4 = 0;
    }
next:
    if (o->d6 < 0) {
        a = o->d0;
        u = (s16)(a & 0xfff0);
        g = a & 0xf;
        if (g) {
            o->d0 = (s32)((s16)a - D_002BBDFC * 4.0f);
            if ((s16)o->d0 <= 0) {
                o->d0 = 0;
                o->d6 = 0;
                goto end;
            }
            if (u < (s16)o->d0) goto end;
            o->d0 = u;
        }
        o->d6 = 0;
    } else if (o->d6 > 0) {
        b = o->d0;
        u = (s16)(b & 0xfff0) + 16;
        a = (o->cc - o->ce) << 4;
        g = b & 0xf;
        if (g) {
            o->d0 = (s32)((s16)b + D_002BBDFC * 4.0f);
            if ((s16)o->d0 >= a) {
                o->d0 = a;
            } else if ((s16)o->d0 < u) {
                goto end;
            } else {
                o->d0 = u;
            }
            r = 1;
        }
        o->d6 = 0;
    }
end:
    a = r;
    return a;
}
