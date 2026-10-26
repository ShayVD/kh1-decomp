/* xs_genie.x func_00f22598: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; OvlVec pos; } Obj;
f32 func_00120c18(f32 *);
s32 rand(void);
s32 func_00f22598(Obj *a, Obj **b) {
    OvlVec d;
    f32 r = (f32)(rand() & 0x7FFF) / 32767.0f;
    PlatVu0SubVector(d, a->pos, (*b)->pos);
    if (func_00120c18(d) < 500.0f) {
        if (r < 0.199999992549f) return 4;
        if (r < 0.349999973178f) return 6;
        if (r < 0.499999949336f) return 5;
        if (r < 0.749999958277f) return 1;
        if (r < 0.949999946356f) return 2;
        return 3;
    }
    if (r < 0.25f) return 4;
    if (r < 0.549999970198f) return 6;
    if (r < 0.799999970198f) return 5;
    if (r < 0.899999934435f) return 1;
    if (r < 0.969999927282f) return 2;
    return 3;
}
