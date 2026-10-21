#include "common.h"
/* 001fe1b8 MATCH (hand, s11w33). From w27__001fe1b8_2w.c plus a dead one-path set `if (a <= 0) a = 0;` after `Scr *o = (Scr *)a;` (flagged: dead statement, s11w22 lever). */
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
    s32 t, f, g, u;
    s32 b;
    s32 r = 0;
    Scr *o = (Scr *)a;
    /* s11w33 (flagged): dead one-path set `if (a <= 0) a = 0;` (s11w22 lever).
     * The test reads a after `o = a`, so combine cannot fold the param copy
     * into `o = a0`; the set of a on one path stops gcse CPROP from rewriting
     * the first load through a. Life1 deletes the dead set, then the empty
     * test goes too. */
    if (a <= 0) a = 0;
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
#include "data/pieces/D_002BBDFC.h"
