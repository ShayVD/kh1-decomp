/* xs_dumbo.x func_00f21460: matched by hand. */
#include "ovl.h"

void func_001315c0(s32, s32, f32 *, f32);
void func_00147ed8(s32, s32, s32, f32 *);
extern s32 D_00F23208;
void func_00f21460(s32 arg0, f32 *pos, f32 r) {
    OvlVec out;
    OvlVec a;
    OvlVec d;
    OvlVec s;
    func_001315c0(arg0, 0x8003, a, 0.0f);
    PlatVu0SubVector(d, a, pos);
    if (d[0] * d[0] + d[1] * d[1] + d[2] * d[2] < r * r) {
        PlatVu0CopyVector(out, a);
    } else {
        PlatVu0Normalize(d, d);
        PlatVu0ScaleVectorXYZ(s, d, r);
        PlatVu0AddVector(out, pos, s);
    }
    func_00147ed8(D_00F23208, 2, -10000, out);
}
