/* wm.x func_00f5d8e0: first draft (session 142, for the native overlay), written from the asm.
 * Not a match: not tried against objdiff yet.
 *
 * A wire box from lo to hi (two corners, w set to 1) as GS packets after `p`: for each axis i and
 * each of its two faces (i = lo[i], then hi[i]), one GIF packet of 11 registers, A+D RGBAQ = rgbaq
 * and 10 XYZF2, the face's outline drawn as a closed strip of 5 corners, each corner followed by a
 * point pulled in by D_00FA5E40 along the face's two other axes (sceVu0RotTransPers projects each
 * one with m). Each XYZF2 then gets z + 256 (word 2) and word 3 = 0x10. Ends with an empty
 * EOP GIFtag; returns the packet's end. */
#include "ovl.h"

typedef struct {
    u64 lo;
    u64 hi;
} Qw;

typedef struct {
    f32 v[4];
} V4;

extern f32 D_00FA5E40;
void sceVu0RotTransPers(s32 *, f32 (*)[4], f32 *, s32);

Qw *func_00f5d8e0(V4 *lo, V4 *hi, u64 rgbaq, f32 (*m)[4], Qw *p) {
    V4 cur, tmp, base;
    s32 i, side, j1, j2, k;
    Qw *pt;

    lo->v[3] = 1.0f;
    hi->v[3] = 1.0f;
    for (i = 0; i < 3; i++) {
        for (side = 0; side < 2; side++) {
            p[0].lo = 0xB062400000000001ULL;
            p[0].hi = 0x044444444444444EULL;
            p[1].lo = rgbaq;
            p[1].hi = 1;
            p += 2;
            if (side == 0) {
                base = *lo;
            } else {
                base.v[i] = hi->v[i];
            }
            j1 = (i + 1) % 3;
            j2 = (i + 2) % 3;
            pt = p;

            cur = base;
            sceVu0RotTransPers((s32 *)p++, m, cur.v, 0);
            tmp = cur;
            tmp.v[j1] += D_00FA5E40;
            tmp.v[j2] += D_00FA5E40;
            sceVu0RotTransPers((s32 *)p++, m, tmp.v, 0);

            cur.v[j1] = hi->v[j1];
            sceVu0RotTransPers((s32 *)p++, m, cur.v, 0);
            tmp = cur;
            tmp.v[j1] -= D_00FA5E40;
            tmp.v[j2] += D_00FA5E40;
            sceVu0RotTransPers((s32 *)p++, m, tmp.v, 0);

            cur.v[j2] = hi->v[j2];
            sceVu0RotTransPers((s32 *)p++, m, cur.v, 0);
            tmp = cur;
            tmp.v[j1] -= D_00FA5E40;
            tmp.v[j2] -= D_00FA5E40;
            sceVu0RotTransPers((s32 *)p++, m, tmp.v, 0);

            cur.v[j1] = lo->v[j1];
            sceVu0RotTransPers((s32 *)p++, m, cur.v, 0);
            tmp = cur;
            tmp.v[j1] += D_00FA5E40;
            tmp.v[j2] -= D_00FA5E40;
            sceVu0RotTransPers((s32 *)p++, m, tmp.v, 0);

            cur = base;
            sceVu0RotTransPers((s32 *)p++, m, cur.v, 0);
            tmp = cur;
            tmp.v[j1] += D_00FA5E40;
            tmp.v[j2] += D_00FA5E40;
            sceVu0RotTransPers((s32 *)p++, m, tmp.v, 0);

            for (k = 9; k >= 0; k--, pt++) {
                ((s32 *)pt)[3] = 0x10;
                ((s32 *)pt)[2] += 0x100;
            }
        }
    }
    p[0].hi = 0;
    p[0].lo = 0x8000;
    return p + 1;
}
