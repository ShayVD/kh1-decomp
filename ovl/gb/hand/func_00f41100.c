/* gb.x func_00f41100: matched by hand. */
#include "ovl.h"

f32 asinf(f32);
f32 acosf(f32);
f32 cosf(f32);
f32 atan2f(f32, f32);

void func_00f41100(f32 *pos, s32 *ang, f32 (*m)[4]) {
    f32 a;
    f32 b;
    f32 c = 0.0f;
    f32 cy;
    f32 t;

    pos[0] = m[3][0];
    pos[1] = m[3][1];
    pos[2] = m[3][2];
    pos[3] = 1.0f;
    b = -asinf(m[0][2]);
    cy = cosf(b);
    if (cy > -0.001f && cy < 0.001f) {
        if (m[0][2] < 0.0f) {
            b = 1.5707963f;
            a = 0.0f;
            c = acosf(m[1][1]);
            if (m[2][1] < 0.0f) {
                c = -c;
            }
        } else {
            b = -1.5707963f;
            a = 0.0f;
            c = acosf(m[1][1]);
            if (0.0f < m[2][1]) {
                c = -c;
            }
        }
    } else {
        t = m[0][1] / cy;
        if (1.0f < t) {
            t = 1.0f;
        }
        if (t < -1.0f) {
            t = -1.0f;
        }
        a = atan2f(m[1][2], m[2][2]);
        c = asinf(t);
        if (m[0][0] < 0.0f) {
            c = 3.141592503f - c;
        }
    }
    ang[3] = 1;
    a *= 10430.378f;
    b *= 10430.378f;
    c *= 10430.378f;
    ang[0] = a;
    ang[1] = b;
    ang[2] = c;
    if (ang[0] < 0) {
        ang[0] += 0x10000;
    }
    if (ang[1] < 0) {
        ang[1] += 0x10000;
    }
    if (ang[2] < 0) {
        ang[2] += 0x10000;
    }
}
