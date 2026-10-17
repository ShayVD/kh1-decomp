/* libgcc2.c, L_udivdi3. sdk segment. */
#define CLZ_TAB D_00492630
#include "libgcc2.h"

UDItype __udivdi3(UDItype n, UDItype d) {
    return __udivmoddi4(n, d, (UDItype *) 0);
}
