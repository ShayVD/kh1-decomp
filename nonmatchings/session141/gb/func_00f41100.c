/* 7 words / score 14 (matrix to euler; rz = 0.0f initialised, in-place scale order found by hill-climb). Left: the original keeps c = cosf(ry) in f12 (and the 1.0f clamp constant in f1); ours puts c in f1. Tried declaration order, a block scope, and nostrict. */
#include "ovl.h"

f32 acosf(f32);
f32 asinf(f32);
f32 atan2f(f32, f32);
f32 cosf(f32);

void func_00f41100(f32 *pos, s32 *rot, OvlMtx m) {
    f32 rx, ry, c;
    f32 rz = 0.0f;
    pos[0] = m[3][0];
    pos[1] = m[3][1];
    pos[2] = m[3][2];
    pos[3] = 1.0f;
    ry = -asinf(m[0][2]);
    c = cosf(ry);
    if (c > -0.001f && c < 0.001f) {
        if (m[0][2] < 0.0f) {
            ry = 1.5707963f;
            rx = 0.0f;
            rz = acosf(m[1][1]);
            if (m[2][1] < 0.0f)
                rz = -rz;
        } else {
            ry = -1.5707963f;
            rx = 0.0f;
            rz = acosf(m[1][1]);
            if (m[2][1] > 0.0f)
                rz = -rz;
        }
    } else {
        rz = m[0][1] / c;
        if (rz > 1.0f)
            rz = 1.0f;
        if (rz < -1.0f)
            rz = -1.0f;
        rx = atan2f(m[1][2], m[2][2]);
        rz = asinf(rz);
        if (m[0][0] < 0.0f)
            rz = 3.1415926f - rz;
    }
    rz *= 10430.378f;
    ry *= 10430.378f;
    rx *= 10430.378f;
    rot[3] = 1;
    rot[0] = rx;
    rot[1] = ry;
    rot[2] = rz;
    if (rot[0] < 0)
        rot[0] += 0x10000;
    if (rot[1] < 0)
        rot[1] += 0x10000;
    if (rot[2] < 0)
        rot[2] += 0x10000;
}
