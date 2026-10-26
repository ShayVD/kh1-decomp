/* wm.x func_00f68b48: the twin of gb.x func_00f41a50 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { s32 a; s32 b; u8 pad[8]; OvlVec v10; OvlVec v20; OvlVec v30; OvlVec v40; } E50;
typedef struct { u8 pad[0x10]; E50 e[1]; } H50;
void func_00f68418(void *, f32 *, f32 *);
s32 func_00f68b48(void *arg0, f32 *arg1, s32 arg2, H50 *arg3) {
    E50 *e = arg3->e;
    sceVu0UnitMatrix(arg0);
    e += arg2;
    func_00f68418(arg0, e->v10, e->v20);
    PlatVu0CopyVector(arg1, e->v30);
    return e->b;
}
