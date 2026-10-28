/* gb.x func_00f365b8: near miss (session 141), 73 words: the box-outline drawer; the code and order match, but the packet pointer lives in t1 across the loop in the original (copied to t0 for each call) and ours in t0. */
#include "ovl.h"
kh1_u128 *func_00f36470(f32 *, f32 *, s32, s32, kh1_u128 *);
void func_00f365b8(s32 sx, s32 sy, s32 sz, s32 c, s32 d, kh1_u128 *pk) {
    OvlVec a, b;
    f32 ex = sx * 200.0f;
    f32 ey = sy * 200.0f;
    f32 ez = sz * 200.0f;
    kh1_u128 *tag = pk;
    s32 n = 0;
    s32 i, j, k;
    pk++;
    a[3] = 1.0f;
    b[3] = 1.0f;
    for (j = 0; j < 2; j++) {
        for (k = 0; k < 2; k++) {
            for (i = 0; i < 2; i++) {
                f32 x = i ? ex : 0.0f;
                f32 y = j ? ey : 0.0f;
                f32 z = k ? ez : 0.0f;
                f32 x2 = i ? x + -100.0f : x + 100.0f;
                f32 y2 = j ? y + -100.0f : y + 100.0f;
                f32 z2 = k ? z + -100.0f : z + 100.0f;
                a[0] = x;
                a[1] = y;
                a[2] = z;
                b[0] = x2;
                b[1] = y;
                b[2] = z;
                pk = func_00f36470(a, b, c, d, pk);
                n++;
                b[0] = x;
                b[1] = y2;
                pk = func_00f36470(a, b, c, d, pk);
                n++;
                b[1] = y;
                b[2] = z2;
                pk = func_00f36470(a, b, c, d, pk);
                n++;
            }
        }
    }
    {
        union { kh1_u128 q; u32 w[4]; } *t = (void *)tag;
        t->q = KH1_Q(0);
        t->w[3] = 0;
        t->w[0] = n | 0x8000;
        t->w[2] = 0x44E;
        t->w[1] = 0x3020C000;
    }
}
