/* xs_dumbo.x func_00f21978: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; f32 f10[4]; u8 pad2[0x10]; f32 f30[4]; u8 pad3[0x414 - 0x40]; f32 f414; } Obj;
void func_00f21860(f32 *, f32 *);
void func_00f22c38(f32, f32);
extern Obj *D_00F23200;
extern f32 D_00F23210;
extern s32 D_00F3C9D8;
extern f32 D_00F44A90;

s32 func_00f21978(void) {
    f32 a[4];
    f32 b[4];
    if (D_00F3C9D8 == 100 || D_00F3C9D8 == 101) {
        return 4;
    }
    if (D_00F23210 > 0.0f) {
        PlatVu0CopyVector(a, D_00F23200->f10);
        a[1] -= D_00F23200->f414 * 0.5f;
        a[3] = 1.0f;
        PlatVu0CopyVector(b, D_00F23200->f30);
        b[3] = 1.0f;
        func_00f21860(a, b);
        func_00f22c38(1.0f, D_00F44A90);
    }
    return 0;
}
