/* wm.x func_00f46690: matched by hand. */
#include "ovl.h"

void func_00f68508(s32, s32, f32 *, s32, s32, s32);
extern s32 D_00F87044;
extern s32 D_00F87048;
extern s32 D_00F87058;

void func_00f46690(s32 kind, s32 id, s32 x, s32 y, s32 z) {
    f32 v[4];
    s32 h;
    switch (kind) {
    case 0:
    default:
        h = D_00F87048;
        break;
    case 1:
        h = D_00F87044;
        break;
    case 2:
        h = D_00F87058;
        break;
    }
    v[3] = 1.0f;
    v[0] = x * 100.0f;
    v[1] = y * 100.0f;
    v[2] = z * 100.0f;
    func_00f68508(id, 1, v, 0, 0, h);
}
