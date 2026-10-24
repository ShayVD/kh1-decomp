#include "common.h"
/* func_00126f18: MATCH hand/nostrict (func_0014cc88 takes (o, f32): the 5.0f goes in f12 as its argument) */

/* func_00172998: MATCH hand/nostrict. Shared labels against if-conversion: r0 (return 0) reached from the p90 test, r1 (the final return 1) from the x90 test and after the range tests; r = 0 before the range tests (w13). */
typedef struct { f32 x, y, z, w; } V4_29;
typedef struct { u8 pad0[0x30]; V4_29 v30; u8 pad40[0x30]; s32 w70; u8 pad74[0x1C]; u64 x90; } Ob29;

static inline s32 inl_free(Ob29 *o) {
    s32 r = 1;
    if (o->x90 != 0) r = 0;
    return r;
}
