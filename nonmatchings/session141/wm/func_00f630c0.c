/* score 81: the second loop in the original is entered at its test (b to slti 257) and (t - t0) is not hoisted; a goto loop gets the shape but not the registers; for/while loops get rotated and hoisted. The two doubles are literals in the original (ld via $at): write `len * 0.01 * 0.1f` once the code matches (extern doubles used here so try can diff). */
#include "ovl.h"

extern double D_00FB7A98;
extern double D_00FB7AA0;
void func_00f62ea0(OvlVec, f32, s32);
f32 func_00f63078(f32 *, f32 *);

f32 func_00f630c0(s32 id, f32 t0, f32 len) {
    OvlVec a;
    OvlVec b;
    OvlVec c;
    OvlVec p;
    f32 lsq;
    f32 t;
    f32 step;
    f32 sum;
    f32 u;
    s32 i;

    lsq = len * len;
    t = t0 + len * 0.01f;
    step = len * D_00FB7A98 * D_00FB7AA0;
    func_00f62ea0(a, t0, id);
    for (;;) {
        func_00f62ea0(b, t, id);
        if (lsq < func_00f63078(a, b)) {
            break;
        }
        t += step;
    }
    sum = 0.0f;
    p[0] = a[0];
    p[1] = a[1];
    p[2] = a[2];
    p[3] = 1.0f;
    i = 1;
loop:
    if (i < 257) {
        u = (t - t0) * (f32)i++ * 0.00390625f + t0;
        func_00f62ea0(c, u, id);
        sum += func_00f63078(p, c);
        if (!(lsq < sum)) {
            p[0] = c[0];
            p[1] = c[1];
            p[2] = c[2];
            goto loop;
        }
    }
    return u;
}
