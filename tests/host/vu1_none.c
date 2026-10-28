/* What host/null/dmawalk.c takes from host/port/vu1.c (session 137v), for the host tests that link
 * the chain walk without the VU1 path: kh1_dma_vu1 stays 0 in them, so VIF1's codes never reach
 * these, and with no clock the walk is not timed.  A call means a test turned the VU1 path on
 * without linking vu1.c: it stops the test. */
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void (*kh1_vu1_kick)(const u32 *q, u32 nqw);
u32 (*kh1_vu1_clock)(void);

static void none(const char *what) {
    printf("vu1_none: %s called with the VU1 path off (link host/port/vu1.c)\n", what);
    exit(1);
}

void kh1_vif1_code(u32 w) { none("kh1_vif1_code"); }
void kh1_vif1_data(u32 w) { none("kh1_vif1_data"); }
