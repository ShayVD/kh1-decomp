/* 00120cf8 3w LCS (11 pos), hand (strict), no context, NATURAL (no flagged trick). s12w2: divisor as a user variable n set twice: `n = 3;` at the top of the outer body AND `n = 3;` at the top of the inner body (k % n). Pass 1 inner moves the inner set to the inner preheader; the outer loop then has two sets of n so pass 1 AND pass 2 refuse it (both sets survive: no cse runs between the loop passes, only delete_trivially_dead_insns). This fixes w42's outer giv (sll v1,s1,4 now as orig) without the dead FP test. Left: li t0,3 stays in the inner preheader (orig: outer preheader after move t2,zero, i.e. moved by loop pass 2) -> li/nop placement + one bnez offset. Needs a second set of n that is removed between loop pass 1 and 2 (only trivially-dead deletion runs there). Same 3w with the extra set after the inner loop instead. */
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
            n = 3;
            if (i == j) {
                m[i][j] = c;
            } else {
                s32 k = i - j + 3;
                f32 v = s[3 - i - j];
                if (k % n == 1) v = -v;
                m[i][j] = v;
            }
        }
    }
    c = 1.0f - c;
    for (i = 0; i < 3; i++) func_00267560(t[i], t[i], c);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) m[i][j] += t[i][j];
    }
}
