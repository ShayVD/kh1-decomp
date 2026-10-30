/* wm.x func_00f7b9e0: matched by hand. */
#include "ovl.h"

typedef struct { u8 r, g, b, a; } Rgba;
extern f32 D_00FB5C34;
extern f32 D_00FB5C38;
extern f32 D_0108F6D8;
extern f32 D_0108F6DC;
extern u8 D_0108F910;
extern s32 D_0108F914;
extern f32 D_0108FA8C;
void func_00f79ca8(void);
void func_00f7a1a8(Rgba *, s32 *, s32 *, u32);
void func_00f7a350(void);
void func_00f7ad38(s32);

#define RGB4(R, G, B) c[0].r = R; c[1].r = R; c[2].r = R; c[3].r = R; c[0].g = G; c[1].g = G; c[2].g = G; c[3].g = G; c[0].b = B; c[1].b = B; c[2].b = B; c[3].b = B
#define XY4(X0, X1, Y0, Y1) x[0] = X0; y[0] = Y0; x[1] = X1; y[1] = Y0; x[2] = X0; y[2] = Y1; x[3] = X1; y[3] = Y1

void func_00f7b9e0(s32 arg)
{
    Rgba c[4];
    s32 x[4];
    s32 y[4];

    D_00FB5C34 = -(D_0108FA8C - D_0108F6D8) * 4.0f / (D_0108F6DC - D_0108F6D8) + D_00FB5C38;
    func_00f7ad38(arg);
    RGB4(0, 0, 0);
    c[0].a = 102; c[1].a = 102; c[2].a = 102; c[3].a = 102;
    XY4(0, 512, 344, 384);
    func_00f7a1a8(c, x, y, 68);
    XY4(311, 512, 0, 39);
    func_00f7a1a8(c, x, y, 68);
    c[0].r = 0; c[2].r = 0; c[0].g = 0; c[2].g = 0; c[0].b = 0; c[2].b = 0; c[0].a = 38; c[2].a = 38;
    c[1].r = 0; c[3].r = 0; c[1].g = 0; c[3].g = 0; c[1].b = 0; c[3].b = 0; c[1].a = 102; c[3].a = 102;
    x[2] = 0; y[2] = 0; x[3] = 311; y[3] = 0;
    x[0] = 0; y[0] = 39; x[1] = 311; y[1] = 39;
    func_00f7a1a8(c, x, y, 68);
    RGB4(135, 191, 76);
    c[0].a = 128; c[1].a = 128; c[2].a = 128; c[3].a = 128;
    XY4(0, 512, 39, 41);
    func_00f7a1a8(c, x, y, 68);
    y[0] = 344; y[1] = 344; y[2] = 346; y[3] = 346;
    func_00f7a1a8(c, x, y, 68);
    func_00f7a350();
    if (D_0108F914) {
        RGB4(0, 0, 0);
        c[0].a = D_0108F910; c[1].a = D_0108F910; c[2].a = D_0108F910; c[3].a = D_0108F910;
        XY4(0, 512, 0, 384);
        func_00f7a1a8(c, x, y, 68);
    }
    func_00f79ca8();
}
