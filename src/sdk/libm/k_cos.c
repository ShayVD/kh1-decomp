/* newlib k_cos.c. sdk segment. Coefficients become per-use .rodata literals
 * (li.d); constants are written as the right operand (see k_sin.c). */
#include "fdlibm.h"

static const double
    one = 1.00000000000000000000e+00,
    C1 = 4.16666666666666019037e-02,
    C2 = -1.38888888888741095749e-03,
    C3 = 2.48015872894767294178e-05,
    C4 = -2.75573143513906633035e-07,
    C5 = 2.08757232129817482790e-09,
    C6 = -1.13596475577881948265e-11;

double __kernel_cos(double x, double y) {
    double a, hz, z, r, qx;
    __int32_t ix;

    GET_HIGH_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix < 0x3e400000) {
        if (((int) x) == 0) {
            return one;
        }
    }
    z = x * x;
    r = z * (z * (z * (z * (z * (z * C6 + C5) + C4) + C3) + C2) + C1);
    if (ix < 0x3FD33333) {
        return one - (z * 0.5 - (z * r - x * y));
    } else {
        if (ix > 0x3fe90000) {
            qx = 0.28125;
        } else {
            INSERT_WORDS(qx, ix - 0x00200000, 0);
        }
        hz = z * 0.5 - qx;
        a = one - qx;
        return a - (hz - (z * r - x * y));
    }
}
