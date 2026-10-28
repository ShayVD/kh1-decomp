/* gb.x func_00f26a78: near miss (session 141), ~68 words: sprite packet (UV / XYZ2 pairs); the lq/sq are caller-save spills of x and u across the call. The y/v/h/w shifts must be computed before the call (they are in the original); register order still differs. */
#include "ovl.h"
extern u8 D_00F610A0[];
void func_00f26458(u64 *, void *, s32, s32);
void func_00f26a78(u64 *p, s32 x, s32 y, s32 z, s32 w, s32 h, s32 u, s32 v, s32 uw, s32 vh, u64 a, u64 b) {
    s32 ys, vs, hs, ws, vhs;
    ys = y << 4;
    vs = v << 4;
    hs = ys + (h << 4);
    ws = w << 4;
    vhs = vs + (vh << 4);
    func_00f26458(p, D_00F610A0, 208, u);
    p[20] = (u64)((u << 4) + (uw << 4)) | ((u64)vhs << 16);
    p[4] = 342;
    p[14] = a;
    p[18] = (u64)(x << 4) | ((u64)ys << 16) | ((u64)(z << 4) << 32);
    p[22] = (u64)((x << 4) + ws) | ((u64)hs << 16) | ((u64)(z << 4) << 32);
    p[16] = (u64)(u << 4) | ((u64)vs << 16);
    p[12] = b;
}
