/* newlib k_sin.c. sdk segment. Each use of a coefficient is an `li.d` that the
 * assembler turns into its own .rodata literal (S1 twice), and half becomes
 * an immediate. A constant is the second operand of a commutative soft-float
 * call in the retail build, so sums and products are written with it on the
 * right. */
#include "fdlibm.h"

static const double
    half = 5.00000000000000000000e-01,
    S1 = -1.66666666666666324348e-01,
    S2 = 8.33333333332248946124e-03,
    S3 = -1.98412698298579493134e-04,
    S4 = 2.75573137070700676789e-06,
    S5 = -2.50507602534068634195e-08,
    S6 = 1.58969099521155010221e-10;

double __kernel_sin(double x, double y, int iy) {
    double z, r, v;
    __int32_t ix;

    GET_HIGH_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix < 0x3e400000) {
        if ((int) x == 0) {
            return x;
        }
    }
    z = x * x;
    v = z * x;
    r = z * (z * (z * (z * S6 + S5) + S4) + S3) + S2;
    if (iy == 0) {
        return x + v * (z * r + S1);
    } else {
        return x - ((z * (y * half - v * r) - y) - v * S1);
    }
}
