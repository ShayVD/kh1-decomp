/* func_00120cf8: 7 words off (nostrict or strict, same). Only t0/t1 swap: hoisted divisor constant 3 vs &m[i][i] in the cross-product loop. */
#include "common.h"
f32 sinf(f32);
f32 cosf(f32);
void func_00267560(f32 *, f32 *, f32);
void func_00120cf8(f32 *axis, f32 m[4][4], f32 angle) {
    f32 t[3][4];
    f32 s[4];
    f32 c;
    s32 i, j;
    for (i = 0; i < 3; i++) {
        m[i][3] = m[3][i] = 0.0f;
    }
    m[3][3] = 1.0f;
    func_00267560(s, axis, sinf(angle));
    c = cosf(angle);
    for (i = 0; i < 3; i++) func_00267560(t[i], axis, axis[i]);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j) {
                m[i][j] = c;
            } else {
                s32 k = i - j + 3;
                f32 v = s[3 - i - j];
                if (k % 3 == 1) v = -v;
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
