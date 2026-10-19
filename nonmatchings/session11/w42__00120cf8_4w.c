/* 00120cf8 4w LCS (11 pos), hand (strict), no context. s11w42 finding, FLAGGED dead FP test: divisor as a user variable `n` set (`n = 3;`) at the top of the outer loop body, `k % n`, plus `if ((f32)n < 0.0f) n = 0;` after the inner loop. The second set keeps n non-invariant in the outer loop, so the divisor register comes out t0 and &m[i][i] t1 as in the original (the old .526/.484 global-alloc order is fixed). Left: `li t0,3` stays in the outer-loop body (inner preheader) instead of the outer preheader after `li t3,1; move t2,zero` (original: hoisted by loop pass 2), and the outer giv uses `sll v1,t2,2` instead of `sll v1,s1,4`. `if ((f32)n < 0.0f) n = 3;` gives the same 4w. */
#include "common.h"
f32 sinf(f32);
f32 cosf(f32);
void func_00267560(f32 *, f32 *, f32);
void func_00120cf8(f32 *axis, f32 m[4][4], f32 angle) {
    f32 t[3][4];
    f32 s[4];
    f32 c;
    s32 i, j, n;
    for (i = 0; i < 3; i++) {
        m[i][3] = m[3][i] = 0.0f;
    }
    m[3][3] = 1.0f;
    func_00267560(s, axis, sinf(angle));
    c = cosf(angle);
    for (i = 0; i < 3; i++) func_00267560(t[i], axis, axis[i]);
    for (i = 0; i < 3; i++) {
        n = 3;
        for (j = 0; j < 3; j++) {
            if (i == j) {
                m[i][j] = c;
            } else {
                s32 k = i - j + 3;
                f32 v = s[3 - i - j];
                if (k % n == 1) v = -v;
                m[i][j] = v;
            }
        }
        if ((f32)n < 0.0f) n = 0;
    }
    c = 1.0f - c;
    for (i = 0; i < 3; i++) func_00267560(t[i], t[i], c);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) m[i][j] += t[i][j];
    }
}
