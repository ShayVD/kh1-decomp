#include "common.h"
#include "data/bss_0049.h"
#include "data/types/nostrict_text_00100000_s11_w45.h"
typedef struct { s32 a, b; } P8;
extern s32 D_00351BD0;
extern Ent16 *D_00494BA8;
extern s32 D_00494BB0;
extern Ent16 D_00482290[];
extern Ent16 D_0047E250[];
extern P8 D_0047A1D0;

s32 func_00107c48(s32 i) {
    Ent16 *arg;
    Ent16 *base;
    Ent16 *dst;
    u32 tbl;
    Ent16 *q;
    s32 *p;
    s32 *r;
    s32 n;
    u8 buf[64];

    arg = (Ent16 *)i;
    /* FLAGGED dead FP test (s11w45): `(f32)(s32)&D_00351BD0 < 0.0f` builds the address from the shared %hi
     * (lo_sum takes v0) while the hi stays live for the D_00351BD0 load in the next block, so global-alloc gives the hi v1; the then-arm before the else is the
     * explicit jump that keeps the test alive through both allocators (flow2 deletes it). i is reset to 0 below. */
    if ((f32)(s32)&D_00351BD0 < 0.0f) i = 0;
    /* FLAGGED dead set (s11w34): both sets die (i = 0 and n = 0 follow); the test keeps i live past the copy until combine */
    else if (i != 0) { i = 0; n = 0; }
    if (D_00351BD0 != 0) {
        base = D_00482290;
    } else {
        base = D_0047E250;
    }
    i = 0;
    tbl = arg->w4 + (s32)arg;
    n = 0;
    for (; i < D_00494BB0; ) {
        arg = (Ent16 *)(i << 4);
        p = (s32 *)((u32)&D_00494BA8->w12 + (u32)arg);
        i++;
        if (*p != 0) {
            q = (Ent16 *)((u32)(i * 16) + tbl);
            r = &q->w8;
            if (*r != 0) {
                *p = 3;
                base[n].w0 = *r; base[n].w4 = q->w12; n++;
            }
        }
    }

    base[n].w0 = D_0047A1D0.a;
    base[n].w4 = D_0047A1D0.b;
    return n;
}
#include "data/bss_0049_typed.h"
#include "data/data_0035.h"
#include "data/pieces/D_0047E220.h"
#include "data/pieces/D_00482260.h"
