/* Round 41 wwm2: score 35 -> 29. The second XYZ word is written with its y half first, as in its wm twin func_00f632e8 (same score there). Found by r41/orsweep.py. */
/* Round 35 (wgb): gb.x func_00f3c1f0 near miss: 55 words, score 37 -> 35. The RGBAQ word is 0x3F80000080202020 (Q = 1.0f, as in func_00f28aa8), not 0x3F8080202020: the target builds it with lui 0x3f80. Left: tx/ty in s2/s3 the wrong way round (-dg: both refs 2, but the registers come from the (bw - h) and (bh - h) temporaries, so swapping the two lines does not help), h << 5 scheduled after the first call. Tried: ty/tx in every order, the f28aa8 split-|= XYZ form (worse, 61-64 words), ctx2. Earlier header below. */
/* 55 words / score 37: logic matches; reusing the x/y params for the GS coords was the big step. Left: tx/ty regs swapped (s2/s3) and the target computes bw<<4 early but h<<5 late (after the first packet call). Tried all orders of the four position lines, bw/bh order, in-place x += bw<<4. */
#include "ovl.h"

extern u64 **D_00F61F58;
extern s32 D_00F61F5C;
void *func_00f3c1d8(void *);
s32 func_00f3c1b0(void *);
u64 *func_001f0798(u64 *, s32, u32, s32, s32, void *, s32);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
void func_00f3fe80(s32, u64 *);

void func_00f3c1f0(s32 x, s32 y, void *str) {
    u64 *q;
    s32 w, h;
    s32 bw, bh, tx, ty;
    q = *D_00F61F58;
    w = func_00f3c1b0(func_00f3c1d8(str));
    h = D_00F61F5C;
    bw = w + h;
    bh = h * 2;
    ty = y - (bh - h) / 2;
    tx = x - (bw - h) / 2;
    x = (x - bw / 2 + 0x700) << 4;
    y = (y - bh / 2 + 0x740) << 4;
    q = func_00f3fa80(func_00f3f9d0(q));
    q[0] = 0x740000007000;
    q[1] = 0x18;
    q += 2;
    q[0] = 0x30000;
    q[1] = 0x47;
    q += 2;
    q[0] = 0x46;
    q[1] = 0;
    q += 2;
    q[0] = 0x3F80000080202020;
    q[1] = 1;
    q += 2;
    q[0] = x | ((u64)y << 16) | 0x100000000;
    q[1] = 5;
    q += 2;
    q[0] = ((u64)(y + (bh << 4)) << 16) | (x + (bw << 4)) | 0x100000000;
    q[1] = 5;
    q += 2;
    func_00f3fa98(q);
    q = func_001f0798(q, 1, 0x80808080, tx, ty, func_00f3c1d8(str), D_00F61F5C);
    func_00f3fe80(0x9C40, func_00f3f9e8(q));
    *D_00F61F58 = q;
}
