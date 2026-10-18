/* 001fe1b8: 588 vs 588 bytes (old draft 580), lcs_s8 59 / pos 72 but ALL off words are register allocation only, mode hand, no context. Generic locals a/b reused (a: v then lim, b: sv then part-2 d0) kill combine nonzero_bits -> li -16; and + the missing nop now match. Left: global-alloc gives o a0 (no move) and a a1; orig has move a1,a0 (o->a1), a->a0, b->a3, t->t0, r->t1. Param/decl order/register/void* variants do not change it. */
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
    s32 t, f;
    s32 a, b;
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
        t = (s16)(a & 0xfff0);
        f = a & 0xf;
        if (f) {
            o->d0 = (s32)((s16)a - D_002BBDFC * 4.0f);
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
        b = o->d0;
        t = (s16)(b & 0xfff0) + 16;
        a = o->ce; a = (o->cc - a) << 4;
        f = b & 0xf;
        if (f) {
            o->d0 = (s32)((s16)b + D_002BBDFC * 4.0f);
            if ((s16)o->d0 >= a) {
                o->d0 = a;
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
