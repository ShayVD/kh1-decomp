/* xs_dumbo.x func_00f21138: matched by hand. */
#include "ovl.h"

typedef struct { f32 *v; s32 f4; f32 *f8; f32 *fC; } Eff;
typedef struct { u8 pad[0x10]; OvlVec pos; } Obj;
Eff *func_00147c98(s32, s32, s32);
void func_00147d50(Eff *, f32 *);
extern Obj *D_00F23200;
extern s32 D_00F23208;
extern f32 D_00F2BAB8;
extern f32 D_00F2BABC;
extern Eff *D_00F44AA0;
extern f32 D_00F44AA4;
void func_00f21138(f32 *pos, f32 *dir) {
    OvlVec d;
    f32 t;
    if (D_00F44AA0 == 0) {
        D_00F44AA0 = func_00147c98(D_00F23208, 5, 20000);
        D_00F44AA0->fC[0] = 1.0f;
        D_00F44AA0->fC[1] = 1.0f;
        D_00F44AA0->fC[2] = 1.0f;
        D_00F44AA0->fC[3] = D_00F44AA4;
    }
    D_00F44AA4 = 1.0f;
    PlatVu0CopyVector(D_00F44AA0->v, pos);
    PlatVu0ScaleVectorXYZ(dir, dir, -1.0f);
    func_00147d50(D_00F44AA0, dir);
    PlatVu0SubVector(d, pos, D_00F23200->pos);
    { f32 k = 490000.0f; t = D_00F2BAB8 * (1.0f - D_00F2BABC) + D_00F2BAB8 * ((d[0] * d[0] + d[1] * d[1] + d[2] * d[2]) / k) * D_00F2BABC; }
    D_00F44AA0->f8[0] = t;
    D_00F44AA0->f8[1] = t;
    D_00F44AA0->f8[2] = t;
    D_00F44AA0->f8[3] = 1.0f;
}
