/* Types that several moved type headers (include/data/types/) need: each is
 * defined once here, so a bss_XXXX_typed.h that includes two of those headers
 * does not see a typedef twice (phase 4, session 19). */
#ifndef KH1_DATA_TYPES_SHARED_H
#define KH1_DATA_TYPES_SHARED_H

#include "common.h"

/* A 128-bit EE register / quadword (lq/sq). */
typedef unsigned int u128 __attribute__((mode(TI)));
/* A 4x4 VU0 matrix (ppp). */
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));

#endif /* KH1_DATA_TYPES_SHARED_H */
