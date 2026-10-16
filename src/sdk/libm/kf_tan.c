/* newlib kf_tan.c. sdk segment. T[] is the original's table in .data. */
#include "fdlibm.h"

static const float
    one = 1.0000000000e+00,
    pio4 = 7.8539812565e-01,
    pio4lo = 3.7748947079e-08;

extern const float D_00493EC0[13];
#define T D_00493EC0

float fabsf(float);

float __kernel_tanf(float x, float y, int iy) {
    float z, r, v, w, s;
    __int32_t ix, hx;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix < 0x31800000) {
        if ((int) x == 0) {
            if ((ix | (iy + 1)) == 0) {
                return one / fabsf(x);
            } else {
                return (iy == 1) ? x : -one / x;
            }
        }
    }
    if (ix >= 0x3f2ca140) {
        if (hx < 0) {
            x = -x;
            y = -y;
        }
        z = pio4 - x;
        w = pio4lo - y;
        x = z + w;
        y = 0.0;
    }
    z = x * x;
    w = z * z;
    r = T[1] + w * (T[3] + w * (T[5] + w * (T[7] + w * (T[9] + w * T[11]))));
    v = z * (T[2] + w * (T[4] + w * (T[6] + w * (T[8] + w * (T[10] + w * T[12])))));
    s = z * x;
    r = y + z * (s * (r + v) + y);
    r += T[0] * s;
    w = x + r;
    if (ix >= 0x3f2ca140) {
        v = (float) iy;
        return (float) (1 - ((hx >> 30) & 2)) * (v - (float) 2.0 * (x - (w * w / (w + v) - r)));
    }
    if (iy == 1) {
        return w;
    } else {
        float a, t;
        __int32_t i;
        z = w;
        GET_FLOAT_WORD(i, z);
        SET_FLOAT_WORD(z, i & 0xfffff000);
        v = r - (z - x);
        t = a = -(float) 1.0 / w;
        GET_FLOAT_WORD(i, t);
        SET_FLOAT_WORD(t, i & 0xfffff000);
        s = (float) 1.0 + t * z;
        return t + a * (s + t * v);
    }
}
