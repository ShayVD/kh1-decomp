/* wm.x func_00f3af58: matched by hand. */
#include "ovl.h"

typedef struct { s32 bone; f32 x; f32 y; f32 z; f32 r; } H;
OvlMtx *func_001623e0(s32);
s32 func_00f20020(void);
s32 func_00f20030(void);
s32 func_00f3caf0(void *, f32, f32 *, f32);
extern H D_00F8C370[];
extern H D_00F8C460[];

s32 func_00f3af58(void *arg0, f32 f) {
    OvlMtx m;
    OvlVec v;
    OvlVec out;
    H *h;
    OvlMtx *mats;
    if (func_00f20020() == 0) {
        h = D_00F8C370;
    } else {
        h = D_00F8C460;
    }
    mats = func_001623e0(func_00f20030());
    for (; h->bone >= 0; h++) {
        v[0] = h->x;
        v[1] = h->y;
        v[2] = h->z;
        v[3] = 1.0f;
        PlatVu0ApplyMatrix(out, mats[h->bone], v);
        PlatVu0CopyMatrix(m, mats[h->bone]);
        PlatVu0CopyVector(m[3], out);
        if (func_00f3caf0(arg0, f, out, h->r) != 0) return 1;
    }
    return 0;
}
