/* newlib sf_atan.c. sdk segment. The atanhi/atanlo/aT tables are the
 * original's, in .data. */
#include "fdlibm.h"

extern const float D_00493F38[4]; /* atanhi */
extern const float D_00493F48[4]; /* atanlo */
extern const float D_00493F58[11]; /* aT */
#define atanhi D_00493F38
#define atanlo D_00493F48
#define aT D_00493F58

static const float one = 1.0, huge = 1.0e30;

float fabsf(float);

float atanf(float x) {
    float w, s1, s2, z;
    __int32_t ix, hx, id;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix >= 0x50800000) {
        if (hx > 0) {
            return atanhi[3] + atanlo[3];
        } else {
            return -atanhi[3] - atanlo[3];
        }
    }
    if (ix < 0x3ee00000) {
        if (ix < 0x31000000) {
            if (huge + x > one) {
                return x;
            }
        }
        id = -1;
    } else {
        x = fabsf(x);
        if (ix < 0x3f980000) {
            if (ix < 0x3f300000) {
                id = 0;
                x = ((float) 2.0 * x - one) / ((float) 2.0 + x);
            } else {
                id = 1;
                x = (x - one) / (x + one);
            }
        } else {
            if (ix < 0x401c0000) {
                id = 2;
                x = (x - (float) 1.5) / (one + (float) 1.5 * x);
            } else {
                id = 3;
                x = -(float) 1.0 / x;
            }
        }
    }
    z = x * x;
    w = z * z;
    s1 = z * (aT[0] + w * (aT[2] + w * (aT[4] + w * (aT[6] + w * (aT[8] + w * aT[10])))));
    s2 = w * (aT[1] + w * (aT[3] + w * (aT[5] + w * (aT[7] + w * aT[9]))));
    if (id < 0) {
        return x - x * (s1 + s2);
    } else {
        z = atanhi[id] - ((x * (s1 + s2) - atanlo[id]) - x);
        return (hx < 0) ? -z : z;
    }
}
