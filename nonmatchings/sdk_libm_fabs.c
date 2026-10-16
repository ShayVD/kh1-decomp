/* fabs (0x0026B560), sdk segment: newlib s_fabs.c. Matches except the
 * final `move v0, a0`, which the original leaves out of the `jr ra` delay
 * slot (as if a label sat before it); ours fills the slot. See
 * docs/sdk.md. */
#include "../src/sdk/libm/fdlibm.h"

double fabs(double x) {
    __uint32_t high;
    GET_HIGH_WORD(high, x);
    SET_HIGH_WORD(x, high & 0x7fffffff);
    return x;
}

