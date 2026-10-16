/* libgcc2.c, L_umoddi3. sdk segment. */
#define CLZ_TAB D_00492730
#include "libgcc2.h"

UDItype __umoddi3(UDItype u, UDItype v) {
    UDItype w;

    (void) __udivmoddi4(u, v, &w);

    return w;
}
