/* gb.x func_00f23d50: matched by hand. */
#include "ovl.h"

s32 func_001ba3f0(s32);
s32 func_001bb720(void);
s32 func_001bb730(void);

s32 func_00f23d50(s32 cur) {
    s32 n, i, k;
    n = func_001bb720() + func_001bb730(); if (cur >= 128) cur = cur + func_001bb720() - 128; for (i = 0; i < n; i++) { cur = (cur + n - 1) % n; k = cur; if (k >= func_001bb720()) k = k - func_001bb720() + 128; if (k == 49) continue; if (func_001ba3f0(k) > 0) return k; }
    return 0;
}
