#include "common.h"
f32 sinf(f32);
f32 cosf(f32);
void func_00267560(f32 *, f32 *, f32);
/* FLAGGED: no-op save/restore of the divisor (`s32 e = n; ... n = e;` in the inner body: gcse cprop turns `n = e` into a self-copy, so loop pass 1 sees two sets of n and pass 2 hoists `n = 3` after the giv inits). The `== 1` arms each store (`m[i][j] = -v` / `m[i][j] = v`, cross-jumped by jump2) are plain C. */
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
            s32 e = n;
            if (i == j) {
                m[i][j] = c;
            } else {
                s32 k = i - j + 3;
                f32 v = s[3 - i - j];
                if (k % n == 1) { m[i][j] = -v; } else { m[i][j] = v; }
            }
            n = e;
        }
    }
    c = 1.0f - c;
    for (i = 0; i < 3; i++) func_00267560(t[i], t[i], c);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) m[i][j] += t[i][j];
    }
}
