/* Round 41 wwm2: score 38 -> 30 (408 vs 416). Uses the copy family of gb func_00f37270: tex = base; o = tex; tex = o + 208; f = (f32 *)tex; s.p0 = tex; tex = o + 480; with the call taking (o, tex). This gives the original's base copy and the v1 = a2 colour pointer copy. The 255.0f chain is written f[6] = f[5] = f[4]. Left: the copy lands in a2 instead of v0, so +208, +480 and the a1 argument are ordered differently. The original's c2 else-arm also reloads s.p0 from the stack (lw v0,16(sp)), which neither f = s.p0 in the else, a g local, nor ((f32 *)s.p0)[k] chains in all 24 orders reproduce. */
/* score 38: one of a family (func_00f5e368, func_00f5e540, func_00f67530, func_00f676b8 call func_00f65480 / func_00f651d0 the same way). The original copies `base` into a fresh pseudo (move v0,s3) and computes base+480 / base before the colour branch, like an inlined helper whose parameters are copied; an inline helper did not reproduce it. OvlVec pad gives the 112 frame. */
#include "ovl.h"

typedef struct {
    u8 *p0;
    s32 n;
    u8 *p2;
} S12;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} T12;

s32 func_00f4a958(s32);
s32 func_00f4aa00(s32);
void func_00f65480(s32, u8 *, u8 *, S12 *, s32, s32, T12 *, f32);

void func_00f5dfd8(s32 arg0, u8 *base, s32 a, s32 b, u8 *c1, u8 *c2) {
    T12 t;
    S12 s;
    s32 h1;
    s32 h2;
    f32 *f;
    OvlVec pad;
    u8 *tex;
    u8 *o;

    h1 = func_00f4a958(a - 1);
    h2 = 0;
    if (b > 0) {
        h2 = func_00f4aa00(b - 1);
    }
    tex = base;
    o = tex;
    tex = o + 208;
    f = (f32 *)tex;
    s.p0 = tex;
    tex = o + 480;
    s.n = 0;
    s.p2 = NULL;
    if (c1 != NULL) {
        f[4] = c1[0];
        f[5] = c1[1];
        f[6] = c1[2];
        f[7] = c1[3];
    } else {
        f[6] = f[5] = f[4] = 255.0f;
        f[7] = 128.0f;
    }
    f = (f32 *)s.p0;
    if (c2 != NULL) {
        f[8] = c2[0];
        f[9] = c2[1];
        f[10] = c2[2];
        f[11] = c2[3];
    } else {
        f[11] = f[8] = f[9] = f[10] = 128.0f;
    }
    t.a = 5;
    t.c = 1;
    t.b = 1;
    func_00f65480(arg0, o, tex, &s, h1, h2, &t, 0.0f);
}
