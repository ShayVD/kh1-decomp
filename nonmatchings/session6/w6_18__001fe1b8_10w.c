/* fe1b8: hand (any mode same). Off: part1 branch2 mask should be li -16 + and (we get andi 0xfff0), and an unreachable nop after "b; sh lim" in part1 branch2 is missing (580 vs 588 bytes, ~10 normalized words). */
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

s32 func_001fe1b8(Scr *o) {
    s32 r = 0;
    s32 t, lim;
    u16 v = o->d2;
    s32 sv = v << 16;
    if (o->d4 < 0) {
        t = (s16)(v & 0xfff0);
        if (v & 0xf) {
            o->d2 = (s32)((sv >> 16) - D_002BBDFC * 4.0f);
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
        t = (s16)(v & ~0xf) + 16;
        lim = (o->ce - 1) << 4;
        if (v & 0xf) {
            o->d2 = (s32)((sv >> 16) + D_002BBDFC * 4.0f);
            if ((s16)o->d2 >= lim) {
                o->d2 = lim;
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
        v = o->d0;
        t = (s16)(v & 0xfff0);
        if (v & 0xf) {
            o->d0 = (s32)((s16)v - D_002BBDFC * 4.0f);
            if ((s16)o->d0 <= 0) {
                o->d0 = 0;
                o->d6 = 0;
                goto end;
            }
            if (t < (s16)o->d0) goto end;
            o->d0 = t;
        }
        o->d6 = 0;
    } else if (o->d6 > 0) {
        v = o->d0;
        t = (s16)(v & 0xfff0) + 16;
        lim = o->ce; lim = (o->cc - lim) << 4;
        if (v & 0xf) {
            o->d0 = (s32)((s16)v + D_002BBDFC * 4.0f);
            if ((s16)o->d0 >= lim) {
                o->d0 = lim;
            } else if ((s16)o->d0 < t) {
                goto end;
            } else {
                o->d0 = t;
            }
            r = 1;
        }
        o->d6 = 0;
    }
end:
    return r;
}
