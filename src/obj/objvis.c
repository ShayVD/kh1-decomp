/* Whether an object is drawn: its bounding box corners (func_00135a68), the
 * on-screen test func_00135bb0, the distance fade curve func_00135ca0
 * (D_002BC0F0, D_002BC120, D_002BC124) and its colour fade (func_00135d38,
 * func_00135df0; a CONTEXT_ONLY copy of func_00135d38 stays in
 * hand/text_00130000_h32.c for func_00136bc0). Flag mode: default (the other
 * modes are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_00304BE8.h"
#include "common.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/text_00130000_h32.h"
#include "data/pieces/D_002E26A0.h"

/* func_00135b88 (from auto/text_00130000.c). */
M2C_UNK func_00135a68(s32, f32, f32);
void func_00135b88(Actor *arg0, s32 arg1) {
    func_00135a68(arg1, arg0->unk410, arg0->unk414);
}

/* func_00135ca0 (from hand/text_00130000_h6.c). */
extern f32 D_002BC120;
extern f32 D_002BC124;
f32 func_00135ca0(f32 x) {
    f32 r;
    if (D_002BC0F0.f[0] <= x) {
        return D_002BC120;
    }
    if (D_002BC0F0.f[1] < x) {
        r = D_002BC120 + D_002BC124 / x;
        if (r < 0.0f) {
            r = 0.0f;
        } else if (255.0f < r) {
            r = 255.0f;
        }
    } else {
        r = 255.0f;
    }
    return r;
}

/* func_00135d38 (from hand/text_00130000_h32.c). */
typedef struct {
    u32 flags;
    u8 pad004[0x1C - 0x4];
    f32 x1c;
    u8 pad020[0x60 - 0x20];
    f32 x60;
    u8 pad064[0xA0 - 0x64];
    f32 xa0[4];
    u8 pad0b0[0xD0 - 0xB0];
    f32 xd0[4][4];
    f32 x110[2];
    f32 x118;
    f32 x11c;
    u8 pad120[0x154 - 0x120];
    s32 x154;
    u8 pad158[0x350 - 0x158];
    s32 tgt[4];
    u8 pad360[0x370 - 0x360];
    union {
        u64 x;
        u8 c[4];
    } u370;
    u8 pad378[0x38C - 0x378];
    s32 x38c;
    u8 pad390[0x394 - 0x390];
    s32 x394;
} W32Col;
void func_00135d38(W32Col *o) {
    s32 i;
    if ((s32)(o->u370.x >> 46) & 1) {
        for (i = 0; i < 4; i++) {
            u8 *q = &o->u370.c[i];
            s32 cur = *q;
            s32 d = o->tgt[i] - cur;
            s32 c;
                        if (d >= -4) c = cur + (d < 5 ? d : 4);
            else c = cur - 4;
            *q = c;
        }
    } else {
        for (i = 0; i < 4; i++) o->u370.c[i] = o->tgt[i];
    }
    o->u370.x |= 1ULL << 46;
}

/* func_00135df0 (from hand/text_00130000_h32.c). */
f32 func_0017f440(W32Col *o);
void func_00135df0(W32Col *o, f32 *out) {
    s32 i;
    if ((s32)(o->u370.x >> 52) & 1) {
        for (i = 0; i < 3; i++) out[i] = o->xa0[i] * 128.0f;
    } else {
        for (i = 0; i < 3; i++) out[i] = o->u370.c[i] * o->xa0[i];
    }
    out[3] = o->xa0[3] * 128.0f * o->x60;
    out[3] *= func_0017f440(o);
}

