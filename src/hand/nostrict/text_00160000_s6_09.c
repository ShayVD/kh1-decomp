#include "common.h"

/* 0016ce10 */
typedef struct { u8 pad[0x80]; u8 b80; } Prm6x;
extern Prm6x D_0035AE80;
#include "data/pieces/D_0035BD40.h"
typedef Hp6C_35BD40 Hp6C;
typedef Act6C_35BD40 Act6C;
s32 func_00133000(Act6C *, s32);

static inline s32 inl_ok(Act6C *e, s32 K) {
    switch (e->w70) {
    case 0:
    case 8:
    case 24:
        if (func_00133000(e, K) == 0) break;
        return 1;
    }
    return 0;
}

static inline s32 inl_alive(Act6C *a) {
    s32 k = D_0035AE80.b80;
    if (a->flags & 0x200) return 0;
    if (a->p6C->w40 * k < a->p6C->w3C * 255) return 0;
    return 1;
}

/* 001713f8 */

/* 00171e50 */

/* 00172028 */

/* 00173478 */

/* 001752a0 */

/* 00175be0 */
typedef int u128 __attribute__((mode(TI)));
typedef struct { s32 x0; void *x4; s32 x8; void *xc; u8 pad10[4]; s32 x14; u8 pad18[4]; void *x1c; u8 pad20[0xC]; u8 *x2c; u8 pad30[0xC]; } Ent5B;
typedef struct { s32 x0; void *x4; void *x8; Ent5B ent[64]; s32 idx[64]; u8 pad[4]; f32 vec[64][4]; } W5B;

CONTEXT_ONLY s32 func_00175ba0(W5B *w) {
    s32 i;
    for (i = 0; i < 64; i++) {
        if (!(w->ent[i].x14 & 3)) return i;
    }
    return -1;
}

/* 00176960 */

/* 001784c8 */

/* 0017b308 */
#include "data/data_0035.h"
#include "data/data_0036.h"
