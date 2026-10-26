/* wm.x func_00f363e0: matched by hand. */
#include "ovl.h"

typedef struct { u16 x; u16 y; u8 z; } Src;
typedef struct { s16 x; s16 y; s16 z; } Rot;
void func_001bbf38(OvlMtx, Rot *);
extern OvlMtx D_00FDF390;

void func_00f363e0(OvlMtx arg0, OvlMtx arg1, Src *arg2) {
    Rot r;
    OvlMtx m;
    s32 a, b, c;
    a = arg2->x;
    b = arg2->y;
    c = arg2->z;
    r.z = c;
    r.x = a;
    r.y = b;
    PlatVu0UnitMatrix(m);
    PlatVu0RotMatrixX(m, m, 3.141592503f);
    PlatVu0UnitMatrix(arg0);
    func_001bbf38(arg0, &r);
    PlatVu0MulMatrix(arg0, D_00FDF390, arg0);
    PlatVu0MulMatrix(arg0, arg0, m);
    PlatVu0MulMatrix(arg0, arg1, arg0);
}
