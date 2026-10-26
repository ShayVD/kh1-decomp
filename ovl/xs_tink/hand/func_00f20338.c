/* xs_tink.x func_00f20338: matched by hand (session 131b). */
#include "ovl.h"

extern f32 D_00F20EC0, D_00F20EC4, D_00F20EC8;
extern OvlVec D_00F20EA0, D_00F20EB0;
extern u8 *D_00F20D84;
extern u8 **D_00F20E90;
extern f32 D_002BBDFC, D_002C5970;
f32 func_00176850(void);
f32 func_00120c88(f32);
f32 func_00120bf8(f32 *);
void func_00121fc4(f32 *, f32 *);
f32 sinf(f32);
f32 cosf(f32);
f32 atan2f(f32, f32);
void func_00f20338(void) {
    OvlVec v;
    f32 r, y, s, w;

    if (D_00F20EC0 >= 0.0f) {
        D_00F20EC0 -= D_002BBDFC;
        if (D_00F20EC0 < 0.0f) {
            r = func_00176850() * 30.0f + 50.0f;
            D_00F20EC4 = func_00120c88(D_00F20EC4 + (func_00176850() * 3.1415928f + 1.5707964f));
            D_00F20EB0[0] = r * sinf(D_00F20EC4);
            D_00F20EB0[1] = -(func_00176850() * 50.0f + 100.0f);
            D_00F20EB0[2] = r * cosf(D_00F20EC4);
            D_00F20EB0[3] = 0.0f;
        }
    } else {
        PlatVu0AddVector(v, D_00F20D84 + 0x10, D_00F20EB0);
        PlatVu0SubVector(v, v, D_00F20EA0);
        if (func_00120bf8(v) < 20.0f) {
            D_00F20EC0 = func_00176850() * 20.0f + 10.0f;
        } else {
            PlatVu0ScaleVector(v, v, D_002C5970);
            y = v[1];
            v[1] = 0.0f;
            func_00121fc4(v, v);
            w = v[3];
            y = y * 50.0f / w * 0.1f;
            if (y > 4.0f) {
                y = 4.0f;
            } else if (y < -4.0f) {
                y = -4.0f;
            }
            s = w * 0.1f;
            PlatVu0ScaleVector(v, v, s < 20.0f ? s : 20.0f);
            v[1] = y;
            PlatVu0ScaleVector(v, v, D_002BBDFC);
            PlatVu0AddVector(D_00F20EA0, D_00F20EA0, v);
            PlatVu0SubVector(v, D_00F20EA0, D_00F20D84 + 0x10);
            if (D_00F20E90 != NULL) {
                M2C_FIELD(D_00F20E90[1], s32 *, 4) = (u16)(s32)(atan2f(v[0], v[2]) / 6.2831855f * 65536.0f);
            }
        }
    }
    D_00F20EA0[1] += sinf(D_00F20EC8);
    D_00F20EC8 = func_00120c88(D_00F20EC8 + D_002BBDFC * 3.1415928f / 10.0f);
}
